//
// Created by Panagiotis Stathopoulos (19064087) on 13/11/2021.
//

#include <string>
#include "GameObject.h"
#include "Room.h"

using std::string;

/**
 * Constructors/Destructors
 */
GameObject::GameObject(const string* _name, const string* _description, const string* _keyword) :
name(_name), description(_description), keyword(_keyword) {}

GameObject::~GameObject() {
    delete(this);
}

/**
 * Getters
 */
const string* GameObject::getName() {
    return this->name;
}
const string* GameObject::getDescription() {
    return this->description;
}
const string* GameObject::getKeyword() {
    return this->keyword;
}
