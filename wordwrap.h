//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_WORDWRAP_H
#define TEXTADV_WORDWRAP_H


#include <string>

/**
 * Initializes word wrapping.
 */
void initWordWrap();

/**
 * Output a string with word wrap.
 * @param text Pointer to the string to output.
 */
void wrapOut(const std::string *text);

/**
 * Ends a paragraph of word wrapped output.
 */
void wrapEndPara();


#endif //TEXTADV_WORDWRAP_H
