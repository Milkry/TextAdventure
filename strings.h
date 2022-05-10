//
// Created by DrMark on 10/4/2017.
// Modified by Panagiotis Stathopoulos (19064087)
//

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

using std::string;

/**
 * Rooms
 */
const string r1name = "First Room";
const string r2name = "Blue Room";
const string r3name = "Red Room";
const string r4name = "Green Room";
const string r5name = "White Room";

const string r1desc = "You are in the first room. It's really quite boring, but then, it's just for testing really. There's a passage to the north.";
const string r2desc = "You are in the blue room. You know because it's blue. That's about all though. There's a passage to the south.";
const string r3desc = "Looks like this is the red room. Makes you wonder what the upcoming rooms look like. There seems to be a way out by heading west.";
const string r4desc = "A green room. Hmm, this color reminds me of nature. Looks like there's an exit to the east.";
const string r5desc = "This plain looking white room you are in feels quite peaceful. Let's stay here...";

/**
 * GameObjects
 */
const string name00 = "Wooden Box";
const string desc00 = "A plain looking wooden box";
const string keyword00 = "wooden_box";

const string name01 = "Iron Pickaxe";
const string desc01 = "An iron pickaxe used for mining";
const string keyword01 = "iron_pickaxe";

const string name02 = "Empty Bottle";
const string desc02 = "An empty plastic bottle";
const string keyword02 = "empty_bottle";

const string name03 = "Iron Sword";
const string desc03 = "A plain looking iron sword, nothing special about it";
const string keyword03 = "iron_sword";

const string name04 = "Old Bow";
const string desc04 = "An antique piece of wood and a string attached to it";
const string keyword04 = "old_bow";

const string name05 = "Torch";
const string desc05 = "A burning torch";
const string keyword05 = "torch";

const string name06 = "Mysterious Potion";
const string desc06 = "A very mysterious looking potion";
const string keyword06 = "mysterious_potion";

/**
 * Command outputs and error messages
 */
const string commandList = "####################################################################################################\n"
                           "> (n)orth/(s)outh/(w)est/(e)ast - Directions the player can use to move throughout the rooms\n"
                           "> find <keyword> - Searches for an object in the current room and player inventory\n"
                           "> get <keyword> - Picks up an object from the current room and stores it in the player inventory\n"
                           "> drop <keyword> - Drops an object from the player inventory to the floor (current room)\n"
                           "> inventory/inv - Displays player inventory\n"
                           "> examine/ex <keyword> - Prints out the description of an object\n"
                           "> save - Saves the current game state\n"
                           "> load/restore - Loads a previous game state from an existing save file\n"
                           "> quit - Quits the game\n"
                           "####################################################################################################";

const string badExit = "Uh oh! You can't go that way.";
const string badCommand = "I don't understand that. Use (commands) or (cmds) to see all available commands.";
const string wrongSyntax = "Incorrect command syntax/input.";
const string saveGameSuccess = " <!> Game saved! <!> ";
const string saveGameFail = " <X> Game failed to save... <X> \n"
                            " <X> Continuing without saving. <X> ";
const string loadGameSuccess = " <!> Save loaded! <!> ";
const string loadGameFail = " <X> Oops. Something went wrong... <X> \n"
                            " <X> Continuing with the current game progress. <X> ";
const string helpfulNote = "###################################################################################################################################\n"
                           "[TIP]: The <keyword> parameter for some commands is the object name in lower case characters and replacing space with an underscore\n"
                           "Example: [Iron Pickaxe] to a keyword will be [iron_pickaxe]\n"
                           "###################################################################################################################################";
const string save_AskForFilename = "Give a name to your save file (DO NOT INCLUDE A FILE FORMAT e.g. '.txt')";
const string load_AskForFilename = "Enter the name of the save file you want to load from (DO NOT INCLUDE A FILE FORMAT e.g. '.txt')";
const string badFilename = "ERROR: The file name should NOT contain a file format...";
const string emptyInventory = "Inventory is empty :(";


#endif //TEXTADV_STRINGS_H
