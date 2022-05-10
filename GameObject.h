//
// Created by Panagiotis Stathopoulos (19064087) on 13/11/2021.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H


#include <string>
class Room;

using std::string;

class GameObject {
    /**
     * Short object name
     */
    const string* name;

    /**
     * Long object description
     */
    const string* description;

    /**
     * A unique keyword to use when searching for the object
     */
    const string* keyword;
public:
    /**
     * Points to the room the GameObject is in, nullptr if it is in player inventory
     */
    const Room* inRoom;

    /**
     * The index number that represents the GameObject position in the gameObjectLibrary list
     */
    uint16_t index;

    /**
     * Constructor
     * @param _name short name
     * @param _description long description
     * @param _keyword unique searchable keyword
     */
    GameObject(const string* _name, const string* _description, const string* _keyword);

    /**
     * Destructor
     */
    ~GameObject();

    /**
     * Getters
     */
    const string* getName();
    const string* getDescription();
    const string* getKeyword();
};


#endif //TEXTADV_GAMEOBJECT_H
