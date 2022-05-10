//
// Modified by Panagiotis Stathopoulos (19064087)
//

#include <map>
#include <iostream>
#include <iterator>
#include <memory>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"

using std::cout;
using std::endl;

/**
 * Variables
 */
string commandBuffer;
State *currentState;
bool static commandOk;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    cout << "> ";
    getline(cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() { // The body of this method would be different if more rooms would have to be implemented!
    //Display a helpful game tip to the player
    wrapOut(&helpfulNote);
    wrapEndPara();

    //Create and add rooms
    auto *r1 = new Room(&r1name, &r1desc);
    auto *r2 = new Room(&r2name, &r2desc);
    auto *r3 = new Room(&r3name, &r3desc);
    auto *r4 = new Room(&r4name, &r4desc);
    auto *r5 = new Room(&r5name, &r5desc);

    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);

    //Setup room layout
    r1->setNorth(r2);
    r2->setSouth(r3);
    r3->setWest(r4);
    r4->setEast(r5);

    //Registers GameObjects to rooms
    r1->registerToRoom(&name00, &desc00, &keyword00);
    r1->registerToRoom(&name01, &desc01, &keyword01);
    r1->registerToRoom(&name02, &desc02, &keyword02);
    r2->registerToRoom(&name03, &desc03, &keyword03);
    r4->registerToRoom(&name04, &desc04, &keyword04);
    r4->registerToRoom(&name05, &desc05, &keyword05);
    r5->registerToRoom(&name06, &desc06, &keyword06);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}

/**
 * Handles room exits by checking if they exist or not
 * @param direction Compass direction (north, south, west, east)
 */
void handleRoom(char direction) {
    commandOk = true;
    Room *nextRoom;

    /*Switch case to find out which direction the next room should be */
    switch (direction) {
        case 'n':
            nextRoom = currentState->getCurrentRoom()->getNorth();
            break;

        case 's':
            nextRoom = currentState->getCurrentRoom()->getSouth();
            break;

        case 'w':
            nextRoom = currentState->getCurrentRoom()->getWest();
            break;

        case 'e':
            nextRoom = currentState->getCurrentRoom()->getEast();
            break;

        default:
            break;
    }

    /* If the direction provided is not an option then display a bad exit message. Else go to the next room */
    if (nextRoom == nullptr) {
        wrapOut(&badExit);
        wrapEndPara();
    }
    else {
        currentState->goTo(nextRoom);
    }
}

/**
 * Finds the target GameObject in the current room or player inventory using a given keyword as a parameter
 * @param keyword unique searchable keyword
 */
void FindObject(string *keyword) {
    bool foundRoom = false, foundInventory = false;
    commandOk = true;
    GameObject* gameObject;

    //Look in the current room
    gameObject = currentState->getCurrentRoom()->searchRoom(keyword);
    if (gameObject != nullptr)
        foundRoom = true;

    //Look in the player inventory
    gameObject = State::searchInventory(keyword);
    if (gameObject != nullptr)
        foundInventory = true;

    if (!foundRoom && !foundInventory)
        cout << *keyword << " was not found anywhere..." << endl;
    else if (foundRoom)
        cout << *keyword << " was found in the room!" << endl;
    else
        cout << *keyword << " was found in the inventory!" << endl;
}

/**
 * Displays all GameObjects in player inventory using their short names
 */
void DisplayInventory() {
    commandOk = true;
    uint16_t counter = 0;
    if (!State::Inventory.empty()) {
        cout << "Items: " << State::Inventory.size() << endl;
        cout << "[";
        for (auto item : State::Inventory) {
            if (counter != State::Inventory.size() - 1) {
                cout << *item->getName() << ", ";
                counter++;
            }
            else
                cout << *item->getName();
        }
        cout << "]" << endl;
        wrapEndPara();
    }
    else {
        wrapOut(&emptyInventory);
        wrapEndPara();
    }
}

/**
 * Extracts the second word in a command
 * @return the word
 */
string ExtractKeyword(int &command) {
    commandBuffer.erase(0, command + 1);
    return commandBuffer.substr(0, commandBuffer.find(' '));
}

/**
 * Checks if the key is valid (an empty space)
 * @param key string to be checked
 * @return true if valid, false if not
 */
bool keyIsValid(const string *key) {
    commandOk = true;
    if (key->empty()) {
        wrapOut(&wrongSyntax);
        wrapEndPara();
        return false;
    }
    return true;
}

/**
 * Removes a GameObject from the current room and adds it to the player inventory
 * @param keyword used for searching the object
 */
void PickupObject(string *keyword) {
    commandOk = true;
    GameObject* gameObject = currentState->getCurrentRoom()->removeFromRoom(keyword);
    if (gameObject == nullptr) {
        cout << *keyword << " is not in this room..." << endl;
        return;
    }
    State::addToInventory(gameObject);
}

/**
 * Removes a GameObject from the player inventory and adds it to the current room
 * @param keyword used for searching the object
 */
void DropObject(string *keyword) {
    commandOk = true;
    GameObject* gameObject = State::removeFromInventory(keyword);
    if (gameObject == nullptr) {
        cout << *keyword << " is not in your inventory..." << endl;
        return;
    }
    currentState->getCurrentRoom()->addToRoom(gameObject);
    cout << *keyword << " was dropped on the floor!" << endl;
}

/**
 * Prints out the GameObject's long description
 * @param keyword used for searching the object
 */
void ExamineObject(string *keyword) {
    commandOk = true;
    GameObject* gameObject = currentState->getCurrentRoom()->lookForObject(keyword);
    if (gameObject != nullptr)
        cout << *gameObject->getName() << ": " << *gameObject->getDescription() << endl;
    else
        cout << "No such item exists here..." << endl;
}

/**
 * Displays a list of available commands the player can use
 */
void DisplayCommands() {
    commandOk = true;
    wrapOut(&commandList);
    wrapEndPara();
}

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver = false;
    while (!gameOver) {
        /* Ask for a command. */
        commandOk = false;
        string key, filename;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        int command = static_cast<uint8_t>(commandBuffer.find(' '));

        /* Command */
        if ((commandBuffer.compare(0, command, "north") == 0) || (commandBuffer.compare(0, command, "n") == 0)) {
            handleRoom('n');
        } else if ((commandBuffer.compare(0, command, "south") == 0) || (commandBuffer.compare(0, command, "s") == 0)) {
            handleRoom('s');
        } else if ((commandBuffer.compare(0, command, "west") == 0) || (commandBuffer.compare(0, command, "w") == 0)) {
            handleRoom('w');
        } else if ((commandBuffer.compare(0, command, "east") == 0) || (commandBuffer.compare(0, command, "e") == 0)) {
            handleRoom('e');
        } else if (commandBuffer.compare(0, command, "find") == 0) {
            key = ExtractKeyword(command);
            if (keyIsValid(&key))
                FindObject(&key);
        } else if (commandBuffer.compare(0, command, "get") == 0) {
            key = ExtractKeyword(command);
            if (keyIsValid(&key))
                PickupObject(&key);
        } else if (commandBuffer.compare(0, command, "drop") == 0) {
            key = ExtractKeyword(command);
            if (keyIsValid(&key))
                DropObject(&key);
        } else if ((commandBuffer.compare(0, command, "inventory") == 0) || (commandBuffer.compare(0, command, "inv") == 0)) {
            DisplayInventory();
        } else if (commandBuffer.compare(0, command, "examine") == 0 || (commandBuffer.compare(0, command, "ex") == 0)) {
            key = ExtractKeyword(command);
            if (keyIsValid(&key))
                ExamineObject(&key);
        } else if (commandBuffer.compare(0, command, "commands") == 0 || (commandBuffer.compare(0, command, "cmds") == 0)) {
            DisplayCommands();
        } else if (commandBuffer.compare(0, command, "save") == 0) {
            wrapOut(&save_AskForFilename);
            inputCommand(&commandBuffer);
            filename = commandBuffer.substr(0, commandBuffer.find(' '));
            if (keyIsValid(&filename))
                if (currentState->SaveGame(&filename)) {
                    wrapOut(&saveGameSuccess);
                    wrapEndPara();
                }
                else {
                    wrapOut(&saveGameFail);
                    wrapEndPara();
                }
        } else if (commandBuffer.compare(0, command, "load") == 0 || (commandBuffer.compare(0, command, "restore") == 0)) {
            wrapOut(&load_AskForFilename);
            inputCommand(&commandBuffer);
            filename = commandBuffer.substr(0, commandBuffer.find(' '));
            if (keyIsValid(&filename))
                if (currentState->LoadGame(&filename)) {
                    wrapOut(&loadGameSuccess);
                    wrapEndPara();
                }
                else {
                    wrapOut(&loadGameFail);
                    wrapEndPara();
                }
        }

        /* Quit command */
        if ((commandBuffer.compare(0, command, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}

int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();

    return 0;
}