//
// Created by DrMark on 10/2/2017.
// Modified by Panagiotis Stathopoulos (19064087)
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include <vector>
#include "Room.h"
#include "strings.h"
#include "wordwrap.h"

using namespace std;

class State {
    /**
     * A pointer that points to the current room
     */
    Room *currentRoom;
public:
    /**
     * Constructor.
     * @param startRoom Pointer to the room to start in.
     */
    explicit State(Room *startRoom);

    /**
     * Player Inventory able to store GameObjects
     */
    static list<GameObject*> Inventory;

    /**
     * An array that holds all the GameObjects in the game (object library)
     */
    static vector<GameObject*> GAME_OBJECTS_LIBRARY;

    /**
     * Adds a GameObject to the player inventory
     * @param gameObject item to be added
     */
    static void addToInventory(GameObject *gameObject);

    /**
     * Removes a GameObject from the player inventory
     * @param keyword unique searchable keyword
     * @return the object that got removed, else nullptr if not found
     */
    static GameObject* removeFromInventory(const string *keyword);

    /**
     * Searches through the player inventory to find a specific GameObject using the given parameters
     * @param keyword unique searchable keyword
     * @return the object if found, else nullptr if not
     */
    static GameObject* searchInventory(const string *keyword);

    /**
     * Move to a specified room and print its description.
     * @param target Pointer to the room to move to.
     */
    void goTo(Room *target);

    /**
     * Display the description of the room the player is in.
     */
    void announceLoc() const;

    /**
     * Saves the current state of the game to a file
     * @param filename Filename to SaveGame to
     * @return true if successful, false if not
     */
    bool SaveGame(string *filename);

    /**
     * Load a SaveGame from a file
     * @param filename Filename to LoadGame from
     * @return true if successful, false if not
     */
    bool LoadGame(string *filename);

    /**
     * Getters
     */
    Room* getCurrentRoom() const;
};


#endif //TEXTADV_STATE_H
