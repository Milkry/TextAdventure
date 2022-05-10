//
// Created by DrMark on 10/2/2017.
// Modified by Panagiotis Stathopoulos (19064087)
//

#include <iostream>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"

using std::cout;
using std::endl;

/**
 * Variables
 */
std::vector<Room*> Room::rooms;

/**
 * Constructors/Destructors
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), west(nullptr), east(nullptr) {}

Room::~Room() {
    for (int i = 0; i < Room::rooms.size(); i++)
        if (Room::rooms.at(i) == this)
            Room::rooms.erase(Room::rooms.begin() + i);
}

/**
 * Methods
 */
void Room::describe() const {
    uint16_t counter = 0;

    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    if (!gameObjectsInRoom.empty()) {
        cout << "Objects in Room: [";
        for (auto item : gameObjectsInRoom) {
            if (counter != gameObjectsInRoom.size() - 1) {
                cout << *item->getName() << ", ";
                counter++;
            }
            else
                cout << *item->getName();
        }
        cout << "]" << endl;
        wrapEndPara();
    }
}

Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

void Room::registerToRoom(const string *objectName, const string *objectDescription, const string *keyword) {
    auto *gameObject = new GameObject(objectName, objectDescription, keyword);
    registerToRoom(gameObject);
}

void Room::registerToRoom(GameObject *gameObject) {
    gameObject->index = State::GAME_OBJECTS_LIBRARY.size();
    State::GAME_OBJECTS_LIBRARY.push_back(gameObject);
    addToRoom(gameObject);
}

void Room::addToRoom(const string* objectName, const string* objectDescription, const string* keyword) {
    auto *gameObject = new GameObject(objectName, objectDescription, keyword);
    addToRoom(gameObject);
}

void Room::addToRoom(GameObject* gameObject) {
    gameObject->inRoom = this;
    gameObjectsInRoom.push_back(gameObject);
}

GameObject* Room::removeFromRoom(const string *keyword) {
    GameObject* gameObject = searchRoom(keyword);
    if (gameObject != nullptr) {
        gameObject->inRoom = nullptr; // this means it is no longer in any room, but in the player inventory
        gameObjectsInRoom.remove(gameObject);
        return gameObject;
    }
    return nullptr;
}

GameObject* Room::searchRoom(const string *keyword) {
    for (auto gameObject : gameObjectsInRoom) {
        if (*gameObject->getKeyword() == *keyword)
            return gameObject;
    }
    return nullptr;
}

GameObject* Room::lookForObject(const string *keyword) {
    GameObject* inRoom = searchRoom(keyword);
    GameObject* inInv = State::searchInventory(keyword);
    if (inRoom != nullptr)
        return inRoom;
    else if (inInv != nullptr)
        return inInv;
    else
        return nullptr;
}

/**
 * Getters
 */
Room* Room::getNorth() const {
    return this->north;
}
Room* Room::getSouth() const {
    return this->south;
}
Room* Room::getWest() const {
    return this->west;
}
Room* Room::getEast() const {
    return this->east;
}

/**
 * Setters
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}
void Room::setSouth(Room* _south) {
    this->south = _south;
}
void Room::setWest(Room* _west) {
    this->west = _west;
}
void Room::setEast(Room* _east) {
    this->east = _east;
}