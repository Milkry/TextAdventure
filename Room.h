//
// Created by DrMark on 10/2/2017.
// Modified by Panagiotis Stathopoulos (19064087)
//

#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H


#include <list>
#include <vector>
#include "GameObject.h"

using std::string;

class Room {
    /**
     * Short name used as a header.
     */
    const string* name;

    /**
     * Full description of the room.
     */
    const string* description;

    /**
     * Pointer to room that is north of this one.
     */
    Room* north;

    /**
     * Pointer to room that is south of this one.
     */
    Room* south;

    /**
     * Pointer to room that is west of this one.
     */
    Room* west;

    /**
     * Pointer to room that is east of this one.
     */
    Room* east;

public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name, description, and all the GameObjects of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::vector<Room*> rooms;

    /**
     * List storing all GameObjects in a room
     */
    std::list<GameObject*> gameObjectsInRoom;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);

    /**
     * Registers GameObjects at the start of the game
     * @param objectName Short objectName
     * @param objectDescription Long objectDescription
     * @param keyword A keyword for the player to use when typing commands
     */
    void registerToRoom(const string* objectName, const string* objectDescription, const string* keyword);
    void registerToRoom(GameObject* gameObject);

    /**
     * Creates a new GameObject with the given parameters and adds it to the gameObjects list
     * @param objectName Short objectName
     * @param objectDescription Long objectDescription
     * @param keyword A keyword for the player to use when typing commands
     */
    void addToRoom(const string* objectName, const string* objectDescription, const string* keyword);
    void addToRoom(GameObject* gameObject);

    /**
     * Removes a GameObject from the list of gameObjects in a room
     * @param keyword used to find the gameObject
     * @return the removed GameObject or nullptr if not found
     */
    GameObject* removeFromRoom(const string* keyword);

    /**
     * Searches the room to find a specific GameObject using the following parameters
     * @param keyword used for searching the object
     * @return the GameObject or nullptr if not found
     */
    GameObject* searchRoom(const string *keyword);

    /**
     * Looks through the current room and player inventory for an object
     * @param keyword used for searching the object
     * @return the GameObject or nullptr if not found
     */
    GameObject* lookForObject(const string *keyword);


    /**
     * Getters
     */
    Room* getNorth() const;
    Room* getSouth() const;
    Room* getWest() const;
    Room* getEast() const;

    /**
     * Setters
     */
    void setNorth(Room* _north);
    void setSouth(Room* _south);
    void setWest(Room* _west);
    void setEast(Room* _east);
};


#endif //TEXTADV_ROOM_H
