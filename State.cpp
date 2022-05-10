//
// Created by DrMark on 10/2/2017.
// Modified by Panagiotis Stathopoulos (19064087)
//

#include <iostream>
#include <fstream>
#include "State.h"

using std::cout;
using std::endl;
using std::vector;

/**
 * Variables
 */
list<GameObject*> State::Inventory;
vector<GameObject*> State::GAME_OBJECTS_LIBRARY;
string saveFileFormat = ".textadv"; //The file format used to save and load game states
char inventoryDelimiter = '#';
char roomDelimiter = '@';
char endOfLine = '*';

/**
 * Constructors/Destructors
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Methods
 */
void State::addToInventory(GameObject *gameObject) {
    Inventory.push_back(gameObject);
    cout << *gameObject->getName() << " picked up and added to inventory!" << endl;
}

GameObject* State::removeFromInventory(const string *keyword) {
    GameObject* gameObject = searchInventory(keyword);
    if (gameObject != nullptr) {
        Inventory.remove(gameObject);
        return gameObject;
    }
    return nullptr;
}

GameObject* State::searchInventory(const string *keyword) {
    for (auto gameObject : Inventory) {
        if (*gameObject->getKeyword() == *keyword)
        return gameObject;
    }
    return nullptr;
}

void State::announceLoc() const {
    this->currentRoom->describe();
}

void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

bool State::SaveGame(string *filename) {
    /**
     * Create the file
     */
    bool success = true;
    string fn = *filename;
    if (fn.find('.') != -1) { // checks if the file name provided contains a file format
        wrapOut(&badFilename);
        wrapEndPara();
        return false;
    }
    string file = *filename + saveFileFormat;
    ofstream save(file);

    /**
     * File validation
     */
    if (!save.is_open()) return false;

    /**
     * Write data in save file
     */
    //Save inventory (indexes)
    uint8_t count = 0;
    save << inventoryDelimiter << " "; // Used to recognize player inventory when loading file
    if (!save.good()) success = false;
    for (int i = 0; i < GAME_OBJECTS_LIBRARY.size(); i++) {
        if (GAME_OBJECTS_LIBRARY.at(i)->inRoom == nullptr) { // check if object is in player inventory
            save << i << " ";
            if (!save.good()) success = false;
            count++;
        }
    }
    if (count == 0) {
        save << "-1 ";
        if (!save.good()) success = false;
    }
    save << endOfLine << endl;
    if (!save.good()) success = false;

    //Save objects in rooms (indexes)
    for (auto room : Room::rooms) {
        save << roomDelimiter << " ";
        if (!save.good()) success = false;
        count = 0;
        for (auto gameObject : room->gameObjectsInRoom) {
            save << gameObject->index << " ";
            if (!save.good()) success = false;
            count++;
        }
        if (count == 0) {
            save << "-1 ";
            if (!save.good()) success = false;
        }
        save << endOfLine << endl;
        if (!save.good()) success = false;
    }

    //Save player position
    for (int i = 0; i < Room::rooms.size(); i++) {
        if (Room::rooms.at(i) == getCurrentRoom()) {
            save << "% " << i << " *" << endl;
            if (!save.good()) success = false;
        }
    }

    save.close();
    return success;
}

bool State::LoadGame(string *filename) {
    /**
     * Find and load the save file
     */
    string fn = *filename;
    if (fn.find('.') != -1) { // checks if the file name provided contains a file format
        wrapOut(&badFilename);
        wrapEndPara();
        return false;
    }
    string file = *filename + saveFileFormat;
    ifstream load(file);
    string index;

    /**
     * File validation
     */
    uint16_t inv = 0, rmP = 0, rm = 0, eofs = -1;
    if (!load.is_open()) return false;
    while (!load.eof()) {
        load >> index;
        if (index == "#")
            inv++;
        else if (index == "%")
            rmP++;
        else if (index == "@")
            rm++;
        else if (index == "*")
            eofs++;
        else
            try {
                std::stoi(index); // try to convert the string to an int, if it fails then catch the error and return false
            }
            catch (...) {
                load.close();
                return false;
            }
    }
    // Checks if there is the right amount of "#@%*" in the save file (if not, then the save file is invalid/corrupted/tampered with)
    if (inv != 1 || rmP != 1 || rm != Room::rooms.size() || eofs != inv + rmP + rm) {
        load.close();
        return false;
    }

    /**
     * Process the save file
     */
    //Clear all rooms with game objects
    for (auto room : Room::rooms)
        room->gameObjectsInRoom.clear();

    //Clear player inventory
    State::Inventory.clear();

    //Load the data
    load.clear();
    load.seekg(0, std::ios::beg);
    uint8_t roomIndex = -1;
    bool openPosition, openInventory, openRooms;
    while (!load.eof()) {
        load >> index;
        if (index == "#") { //Inventory
            openInventory = true;
            continue;
        } else if (index == "@") { //Rooms
            openRooms = true;
            roomIndex++;
            continue;
        } else if (index == "%") { //Player position
            openPosition = true;
            continue;
        } else if (index == "*") { //End of index
            openInventory = false;
            openRooms = false;
            openPosition = false;
            continue;
        }

        if (openInventory && index != "-1") { //Add to inventory
            State::Inventory.push_back(GAME_OBJECTS_LIBRARY.at(std::stoi(index)));
        } else if (openRooms && index != "-1") { //Add to room
            Room::rooms.at(roomIndex)->gameObjectsInRoom.push_back(GAME_OBJECTS_LIBRARY.at(std::stoi(index)));
        } else if (openPosition) { //Go to room
            State::goTo(Room::rooms.at(std::stoi(index)));
        }
    }

    load.close();
    return true;
}

/**
 * Getters
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}
