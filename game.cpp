// Group 4: Lawrence Rede, Christopher Andrade, Amaan Ahmed, Ivan Dorantes,
// Karlee Wilkinson
#include <iostream>
#include <string>
// Helps with pig latin
#include <algorithm>
// Used to make user input lowercase
#include <fstream>
// Used to do save files
using namespace std;
const int MAX_ITEMS_CARRIED=3;
// Should be able to be changed and still work properly
const string VOWELS = "AEIOUYaeiouy";  // Used in pig latin function
enum Location 
// no_room should always be the last room
{QUARTERS,HOLD,GALLEY,BRIG,WHEEL,BANANA_TREE,UDECK,LDECK,ISLAND,NO_ROOM};
struct dir
{
    string north;
    string south;
    string east;
    string west;
    string up;
    string down;
};
struct locInfo{
    string name;
    string description;
    string droppedItems[MAX_ITEMS_CARRIED];
    // Contains any items dropped in the room
    dir nextRoom;
    Location rawLoc;
    // Makes checking location easier
};
struct CharInfo{
    string item[MAX_ITEMS_CARRIED];
    locInfo playerLocation;
    string name;
    bool SAID_KEYWORD, GAVE_TREASURE, SEEN_NATIVES, GAVE_BANANA, SEEN_I, SEEN_L,
    SEEN_Q, SEEN_W, SEEN_G, SEEN_H, SEEN_B, OPENED_TRUNK, BROKE_TRUNK,
    UNLOCKED_CELL, OPENED_CELL, DROPPED_KNIFE, DROPPED_KEY, DROPPED_TREASURE,
    GOT_KEY_EARLY, BONKED, EGG_ONE;
    // Bools make keeping track of game events easier
};
void startNewGame(CharInfo, locInfo[]);
void CaptainsQuarters(CharInfo, locInfo[]);
void CargoHold(CharInfo, locInfo[]);
void Galley(CharInfo, locInfo[]);
void Brig(CharInfo, locInfo[]);
void ShipsWheel(CharInfo, locInfo[]);
void BananaTree(CharInfo, locInfo[]);
void UpperDeck(CharInfo, locInfo[]);
void LowerDeck(CharInfo, locInfo[]);
void Island(CharInfo, locInfo[]);
void ProcessCommand(CharInfo, locInfo[]);
void Look(CharInfo, locInfo[], string);
void Take(CharInfo, locInfo[], string);
void Drop(CharInfo, locInfo[], string);
void Give(CharInfo, locInfo[], string);
void Eat(CharInfo, locInfo[], string);
void Cut(CharInfo, locInfo[], string);
void Unlock(CharInfo, locInfo[], string);
void Open(CharInfo, locInfo[], string);
void Navigate(CharInfo, locInfo[], string);
void goToLoc(CharInfo, locInfo[], string);
bool inventoryContains(string[], string);
bool InventoryFull(string[]);
void getItem(CharInfo, locInfo[], string);
void pickupItem(CharInfo, locInfo[], string);
void removeItem(CharInfo, locInfo[], string);
void dropItem(CharInfo, locInfo[], string);
string pigLatin(string);
void getDroppedItems(CharInfo, locInfo[]);
void saveData(CharInfo, locInfo[]);
string boolNum(bool);
void loadData(CharInfo, locInfo[]);
bool numBool(string);
Location printRawLoc(string);

int main()
// Sets up CharInfo and locInfo objects, gets the player's name, and starts the
// game
{
    CharInfo cInfo;
    locInfo room[NO_ROOM];
    cout<<"What is your name?\n\n";
    getline(cin,cInfo.name);
    cout << endl;
    cout<<"You have just awakened on a strange island with a terrible headache."
    <<" You can't remember anything about yourself or where you are.\n\n";
    startNewGame(cInfo, room);
    return 0;
}
void startNewGame(CharInfo cInfo, locInfo lInfo[]){
    // Sets the names, rawLocs, and descriptions for every room, as well as
    // using a "for" loop to set up the droppedItems arrays
    int i;  // Iterator for later
    lInfo[ISLAND].name = "island";
    lInfo[ISLAND].rawLoc = ISLAND;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[ISLAND].droppedItems[i] = "empty";
    }
    lInfo[ISLAND].description = "You are on the island. There is a tree with ";
    lInfo[ISLAND].description += "ripe bananas to your north, and a gangplank ";
    lInfo[ISLAND].description += "to the ship to the south.";
    lInfo[ISLAND].nextRoom.north = "banana_tree";
    lInfo[ISLAND].nextRoom.south = "uDeck";
    lInfo[ISLAND].nextRoom.east = "no_room";
    lInfo[ISLAND].nextRoom.west = "no_room";
    lInfo[ISLAND].nextRoom.up = "no_room";
    lInfo[ISLAND].nextRoom.down = "no_room";
    lInfo[BANANA_TREE].name = "banana_tree";
    lInfo[BANANA_TREE].rawLoc = BANANA_TREE;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[BANANA_TREE].droppedItems[i] = "empty";
    }
    lInfo[BANANA_TREE].description = "There is a large banana tree here, and ";
    lInfo[BANANA_TREE].description += "thick forest to all sides except the ";
    lInfo[BANANA_TREE].description += "south.";
    lInfo[BANANA_TREE].nextRoom.north = "no_room";
    lInfo[BANANA_TREE].nextRoom.south = "island";
    lInfo[BANANA_TREE].nextRoom.east = "no_room";
    lInfo[BANANA_TREE].nextRoom.west = "no_room";
    lInfo[BANANA_TREE].nextRoom.up = "no_room";
    lInfo[BANANA_TREE].nextRoom.down = "no_room";
    lInfo[UDECK].name = "uDeck";
    lInfo[UDECK].rawLoc = UDECK;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[UDECK].droppedItems[i] = "empty";
    }
    lInfo[UDECK].description = "There is a wheel at the east end of the ship, ";
    lInfo[UDECK].description += "and a ladder down to the lower deck. The ";
    lInfo[UDECK].description += "captain's quarters are to the west and there ";
    lInfo[UDECK].description += "is a gangplank leading back to the island to ";
    lInfo[UDECK].description += "the north. The crow's nest is above you.";
    lInfo[UDECK].nextRoom.north = "island";
    lInfo[UDECK].nextRoom.south = "off_ship";
    lInfo[UDECK].nextRoom.east = "wheel";
    lInfo[UDECK].nextRoom.west = "quarters";
    lInfo[UDECK].nextRoom.up = "crows_nest";
    // Easter egg, not actually a room
    lInfo[UDECK].nextRoom.down = "lDeck";
    lInfo[WHEEL].name = "wheel";
    lInfo[WHEEL].rawLoc = WHEEL;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[WHEEL].droppedItems[i] = "empty";
    }
    lInfo[WHEEL].description = "The gorilla still blocks the wheel. The deck ";
    lInfo[WHEEL].description += "is to the west.";
    lInfo[WHEEL].nextRoom.north = "off_ship";
    lInfo[WHEEL].nextRoom.south = "off_ship";
    lInfo[WHEEL].nextRoom.east = "off_ship";
    lInfo[WHEEL].nextRoom.west = "uDeck";
    lInfo[WHEEL].nextRoom.up = "no_room";
    lInfo[WHEEL].nextRoom.down = "no_room";
    lInfo[LDECK].name = "lDeck";
    lInfo[LDECK].rawLoc = LDECK;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[LDECK].droppedItems[i] = "empty";
    }
    lInfo[LDECK].description = "There are doors to your north and south, and a";
    lInfo[LDECK].description += " trapdoor below you.";
    lInfo[LDECK].nextRoom.north = "hold";
    lInfo[LDECK].nextRoom.south = "galley";
    lInfo[LDECK].nextRoom.east = "no_room";
    lInfo[LDECK].nextRoom.west = "no_room";
    lInfo[LDECK].nextRoom.up = "uDeck";
    lInfo[LDECK].nextRoom.down = "brig";
    lInfo[GALLEY].name = "galley";
    lInfo[GALLEY].rawLoc = GALLEY;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[GALLEY].droppedItems[i] = "empty";
    }
    lInfo[GALLEY].description = "There is a parrot in the corner of the room, ";
    lInfo[GALLEY].description += "and a doorway to your north.";
    lInfo[GALLEY].nextRoom.north = "lDeck";
    lInfo[GALLEY].nextRoom.south = "no_room";
    lInfo[GALLEY].nextRoom.east = "no_room";
    lInfo[GALLEY].nextRoom.west = "no_room";
    lInfo[GALLEY].nextRoom.up = "no_room";
    lInfo[GALLEY].nextRoom.down = "no_room";
    lInfo[BRIG].name = "brig";
    lInfo[BRIG].rawLoc = BRIG;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[BRIG].droppedItems[i] = "empty";
    }
    lInfo[BRIG].description = "The prisoner is still locked in his cell. There";
    lInfo[BRIG].description += " is a ladder leading back up.";
    lInfo[BRIG].nextRoom.north = "no_room";
    lInfo[BRIG].nextRoom.south = "no_room";
    lInfo[BRIG].nextRoom.east = "no_room";
    lInfo[BRIG].nextRoom.west = "no_room";
    lInfo[BRIG].nextRoom.up = "lDeck";
    lInfo[BRIG].nextRoom.down = "no_room";
    lInfo[QUARTERS].name = "quarters";
    lInfo[QUARTERS].rawLoc = QUARTERS;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[QUARTERS].droppedItems[i] = "empty";
    }
    lInfo[QUARTERS].description = "Inside the captain's quarters, there is a ";
    lInfo[QUARTERS].description += "bed and a table.";
    lInfo[QUARTERS].nextRoom.north = "no_room";
    lInfo[QUARTERS].nextRoom.south = "no_room";
    lInfo[QUARTERS].nextRoom.east = "uDeck";
    lInfo[QUARTERS].nextRoom.west = "no_room";
    lInfo[QUARTERS].nextRoom.up = "no_room";
    lInfo[QUARTERS].nextRoom.down = "no_room";
    lInfo[HOLD].name = "hold";
    lInfo[HOLD].rawLoc = HOLD;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        lInfo[HOLD].droppedItems[i] = "empty";
    }
    lInfo[HOLD].description = "Inside the cargo hold, there are barrels, ";
    lInfo[HOLD].description += "various tools, and ";
    // Description cut short intentionally, the rest is appended later so we can
    // modify it based on whether the trunk is open, and if it is, whether it
    // contains treasure
    lInfo[HOLD].nextRoom.north = "no_room";
    lInfo[HOLD].nextRoom.south = "lDeck";
    lInfo[HOLD].nextRoom.east = "no_room";
    lInfo[HOLD].nextRoom.west = "no_room";
    lInfo[HOLD].nextRoom.up = "no_room";
    lInfo[HOLD].nextRoom.down = "no_room";
    cInfo.SAID_KEYWORD = false;
    // Keyword for the parrot
    cInfo.GAVE_TREASURE = false;
    // Has the player given the treasure to the natives
    cInfo.SEEN_NATIVES = false;
    // Has the player tried to leave the ship
    cInfo.GAVE_BANANA = false;
    // Has the player given the banana to the gorilla
    cInfo.SEEN_I = false;
    cInfo.SEEN_L = false;
    cInfo.SEEN_Q = false;
    cInfo.SEEN_W = false;
    cInfo.SEEN_G = false;
    cInfo.SEEN_H = false;
    cInfo.SEEN_B = false;
    // These are used to determine whether we should print the full description
    // of a room or the shortened version
    cInfo.OPENED_TRUNK = false;
    // Has the player opened the treasure trunk
    cInfo.BROKE_TRUNK = false;
    // Easter egg
    cInfo.UNLOCKED_CELL = false;
    cInfo.OPENED_CELL = false;
    // Both of these should do the same thing, fix later
    cInfo.DROPPED_KNIFE = false;
    cInfo.DROPPED_KEY = false;
    cInfo.DROPPED_TREASURE = false;
    // Unlike the banana, these items cannot be gotten again from their original
    // location after they've been dropped, so we need to keep track of them to
    // avoid accidental duplicates
    cInfo.GOT_KEY_EARLY = false;
    // Easter egg
    cInfo.BONKED = false;
    // Easter egg
    cInfo.EGG_ONE = false;
    // Easter egg, but more official
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        cInfo.item[i] = "empty";
    }
    // Set up the inventory array
    Island(cInfo, lInfo);
    // Move the player to the island and begin the game
}
void CaptainsQuarters(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
CaptainsQuarters will happen.*/
    {
        cInfo.playerLocation = lInfo[QUARTERS];
        if (not cInfo.SEEN_Q)
        {
            cout<<"These are the captain's quarters. There is a bed and a table"
            <<" in this room. On the table is a knife, presumably belonging to "
            <<"the captain.\n";
            cInfo.SEEN_Q = true;
        }
        else
        {
            cout << cInfo.playerLocation.description;
            if (not inventoryContains(cInfo.item, "knife") and
            not cInfo.DROPPED_KNIFE)
            // If the knife is not on the player and has not been dropped
            // somewhere else, it must be on the table
            {
                cout << " On the table is a knife.";
            }
            getDroppedItems(cInfo, lInfo);
            // Append dropped items in the room to the room's description. Not
            // needed for the initial description, as a room cannot have dropped
            // items before it has been visisted
        }
        ProcessCommand(cInfo, lInfo);
    }
void CargoHold(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
CargoHold will happen.*/
    {
        cInfo.playerLocation = lInfo[HOLD];
        if (not cInfo.SEEN_H)
        {
            cout<<"The cargo hold is where all the ship's supplies and loot are"
            <<" kept. There are barrels of varying sizes, various tools, and a "
            <<"trunk. There is a doorway to the south.\n";
            cInfo.SEEN_H = true;
        }
        else
        {
            cout << cInfo.playerLocation.description;
            if (cInfo.OPENED_TRUNK)
            {
                if (not cInfo.GAVE_TREASURE and not 
                inventoryContains(cInfo.item, "treasure") and
                not cInfo.DROPPED_TREASURE)
                // The treasure cannot be anywhere except for inside the trunk
                {
                    cout << "an open trunk, with gleaming treasure inside.";
                }
                else
                // The treasure is somewhere else
                {
                    cout << "an empty trunk.";
                }
            }
            else if (cInfo.BROKE_TRUNK)
            {
                cout << "an empty trunk with a hole in the top.";
            }
            else
            // The trunk has not been opened
            {
                cout << "a trunk.";
            }
            cout << " There is a doorway to the south.";
            getDroppedItems(cInfo, lInfo);
        }
        ProcessCommand(cInfo, lInfo);
    }
void Galley(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
Galley will happen.*/
    {
        cInfo.playerLocation = lInfo[GALLEY];
        if (not cInfo.SEEN_G)
        {
            cout<<"This is the galley. It is mostly empty, but in a shadowy "
            <<"corner you see a parrot sitting on a perch.\n";
            cInfo.SEEN_G = true;
        }
        else
        {
            cout << cInfo.playerLocation.description;
            getDroppedItems(cInfo, lInfo);
        }
        ProcessCommand(cInfo, lInfo);
    }
void Brig(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
Brig will happen.*/
    {
        cInfo.playerLocation = lInfo[BRIG];
        if (not cInfo.SEEN_B)
        {
            cout<<"In this room there is a prisoner in a locked cell. He says, "
            <<"\""<<cInfo.name<<", I'm so glad you're alive. The captain locked"
            <<" me up for cheating at cards, which is the only reason the "
            <<"islanders didn't capture me. They killed everyone else. Now I "
            <<"guess we're the only two left, which makes you captain since you"
            <<" were first mate. Go find the keys to unlock this door, and we "
            <<"can sail out of here.\"\n";
            cInfo.SEEN_B = true;
        }
        else if (cInfo.OPENED_CELL)
        // The prisoner has already been freed and left the room
        {
            cout << "The cell is open and empty. There is a ladder leading back"
            << " up.";
            getDroppedItems(cInfo, lInfo);
        }
        else
        {
            cout << cInfo.playerLocation.description;
            getDroppedItems(cInfo, lInfo);
        }
        ProcessCommand(cInfo, lInfo);
    }
void ShipsWheel(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
ShipsWheel will happen.*/
    {
        cInfo.playerLocation = lInfo[WHEEL];
        if (not cInfo.SEEN_W)
        {
            cout<<"There is a large gorilla by the ship's wheel. This gorilla "
            <<"is hostile. You can't touch the wheel. The deck is to the west."
            <<endl;
            cInfo.SEEN_W = true;
        }
        else
        {
            if (cInfo.GAVE_BANANA)
            // The gorilla is gone
            {
                if (cInfo.OPENED_CELL)
                // The prisoner has been freed
                {
                    cout << "From the wheel you can see the prisoner sitting on"
                    << " the ropes that connect the sails. He seems to know how"
                    << " to work them. If you wish, you could set sail, or "
                    << "return west to the deck.";
                }
                else
                // The gorilla is gone but the prisoner is still in the brig
                {
                    cout << "There is a wheel here. The deck is to the west.";
                }
            }
            else
            {
                cout << cInfo.playerLocation.description;
            }
            getDroppedItems(cInfo, lInfo);
        }
        ProcessCommand(cInfo, lInfo);
    }
void BananaTree(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
BananaTree will happen.*/
    {
        cInfo.playerLocation = lInfo[BANANA_TREE];
        cout << cInfo.playerLocation.description;
        if (not inventoryContains(cInfo.item, "banana"))
        // The player does not have a banana in their inventory
        {
            cout << " There is one bunch of ripe bananas on the tree within "
            << "reach.";
        }
        getDroppedItems(cInfo, lInfo);
        ProcessCommand(cInfo, lInfo);
    }
void UpperDeck(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
UpperDeck will happen.*/
{
    cInfo.playerLocation = lInfo[UDECK];
    cout << cInfo.playerLocation.description;
    getDroppedItems(cInfo, lInfo);
    ProcessCommand(cInfo, lInfo);
}
void LowerDeck(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
LowerDeck will happen.*/
{
    cInfo.playerLocation = lInfo[LDECK];
    if (not cInfo.SEEN_L)
    {
        cout<<"The deck below is dimly lit, and smells musty. You can make out "
        <<"three doors. One is to the north, one is to the south, and one is a "
        <<"trapdoor below you.\n";
        cInfo.SEEN_L = true;
    }
    else
    {
        cout << cInfo.playerLocation.description;
        getDroppedItems(cInfo, lInfo);
    }
    ProcessCommand(cInfo, lInfo);
}
void Island(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
Island will happen.*/
{
    cInfo.playerLocation = lInfo[ISLAND];
    if (not cInfo.SEEN_I)
    {
        cout<<"The island is forested with banana trees. Most of the bananas "
        <<"are green, but one tree to your north might have ripe bananas. There"
        <<" are ominous drums in the background. There is a ship to your south "
        <<"with a gangplank to the shore. In front of the ship is a sign.\n";
        cInfo.SEEN_I = true;
    }
    else
    {
        cout << cInfo.playerLocation.description;
        getDroppedItems(cInfo, lInfo);
    }
    ProcessCommand(cInfo, lInfo);
}
void ProcessCommand(CharInfo cInfo, locInfo lInfo[])
// Separates the command into two strings, word_one and word_two, then calls the
// appropriate functions to handle the command
{
    string commands, word_one, word_two, parrot_resp, pig_lat;
    // "commands" stores the player's input commands, word_one is the first word
    // of the input, word_two is the rest of the input, "parrot_resp" is a
    // 1-to-1 copy of "commands" used for pig latin processing, and "pig_lat"
    // stores the pig latin response before we send it to the player
    int spaceholder;
    // Used to store the location of a space character in the case of multiple
    // words, so we can split "commands" into "word_one" and "word_two"
    bool one_word = false;
    // Stores whether the command contains only one word
    cout << endl;
    // Makes the spacing look better
    getline(cin, commands);
    cout << endl;
    // Makes the spacing look better
    transform(commands.begin(), commands.end(), commands.begin(), ::tolower);
    // Makes all input lowercase
    spaceholder = commands.find(" ");
    word_one = commands.substr(0,spaceholder);
    word_two = commands.substr(spaceholder+1);
    if (spaceholder == -1)
    // C++ overflows the result of a find() call to -1 if nothing was found, so
    // if spaceholder is -1 then there was no space found and the command was
    // only one word
    {
        one_word = true;
    }
    spaceholder = word_two.find(" ");
    // Used to find out if there are more than two words
    if (word_one == "quit" or word_one == "exit" or word_one == "close")
    {
        cout << "Goodbye.\n";
        // ProcessCommand() is missing from this response, so the game will end
        // as soon as it is given
    }
    else if ((word_one == "polly" or word_one == "hello" or
    word_one == "cracker" or word_one == "hi") and
    cInfo.playerLocation.rawLoc == GALLEY and not cInfo.SAID_KEYWORD and not
    cInfo.GOT_KEY_EARLY)
    // The player is in the galley and hadn't said a keyword yet, but just did
    {
        cout << "The parrot lets out a delighted squawk and replies \"You "
        << "figured it out! In exchange for solving my puzzle, I'll tell you "
        << "where the captain hides the key to the brig: It's under the bed in "
        << "the Captain's Quarters. Good luck!\"\n";
        cInfo.SAID_KEYWORD = true;
        ProcessCommand(cInfo, lInfo);
    }
    else if (cInfo.playerLocation.rawLoc == GALLEY and not cInfo.SAID_KEYWORD
    and not cInfo.GOT_KEY_EARLY)
    // The player said something in front of the parrot that wasn't a keyword
    {
        parrot_resp = commands;
        if (one_word)
        // Easy peasy, just repeat the one word in pig latin
        {
            cout << "The parrot replies: \"" << pigLatin(word_one) << "\".\n";
        }
        else
        // NOT EASY PEASY VERY MUCH NOT EASY PEASY (the player said more than
        // one word, each of which must be converted to pig latin and repeated)
        {
            pig_lat = "";
            cout << "The parrot replies: \"";
            // We'll append the rest of the response later
            while (not (parrot_resp.find(" ") == -1))  // While there is a space
            // meaning there are more words to parse
            {
                spaceholder = parrot_resp.find(" ");
                // Find the space in parrot_resp. Doesn't interfere with later
                // use of spaceholder since anything else that would use it
                // would prevent the else if statement on line 543 from running
                pig_lat += pigLatin(parrot_resp.substr(0, spaceholder)) + " ";
                // Take the substring from the start of parrot_resp to the first
                // space (i.e. the first word of parrot_resp), convert it to pig
                // latin, and append the pig latin word plus a space to pig_lat
                parrot_resp.erase(0, spaceholder+1);
                // Remove from parrot_resp the word that we just processed, as
                // well as the space that followed it
            }
            // The while loop stops before the last word is processed, which
            // lets us process the last word here without adding a space to the
            // end like we have with the other words
            pig_lat += pigLatin(parrot_resp);
            // Convert the last word to pig latin and add it to pig_lat
            cout << pig_lat << "\".\n";
            // Send pig_lat and the end of the response
        }
        ProcessCommand(cInfo, lInfo);
    }
    else if (not (spaceholder == -1))
    // There are more than two words and the player is not doing the parrot
    // puzzle, which is the only place in the game we allow more than two words
    {
        cout << "Please enter up to two words at a time.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (word_one == "go" or word_one == "move" or word_one == "walk")
    // Navigation commands
    {
        Navigate(cInfo, lInfo, word_two);
    }
    else if (word_one == "n" or word_one == "e" or word_one == "s" or word_one
    == "w" or word_one == "u" or word_one == "d" or word_one == "north" or
    word_one == "east" or word_one == "south" or word_one == "west" or word_one
    == "up" or word_one == "down" or word_one == "climb")
    // Raw directions trigger the navigation command
    {
        Navigate(cInfo, lInfo, word_one);
    }
    else if (word_one == "look" or word_one == "inspect")
    // Look commands
    {
        if (one_word or word_two == "room" or word_two == "around")
        // The player typed "look room" or "look around" or just "look"
        {
            goToLoc(cInfo, lInfo, cInfo.playerLocation.name);
            // Gets the room description by placing the player at their current
            // location and triggering that room's function
        }
        else if (word_two == "ladder" and cInfo.playerLocation.rawLoc == LDECK
        and not cInfo.BONKED)
        // Easter egg :)
        {
            cout << "You turn around and smack your head into the ladder, "
            << "forgetting how close you were to it. That's gonna leave a "
            << "bruise.\n";
            cInfo.BONKED = true;
            ProcessCommand(cInfo, lInfo);
        }
        else
        // The player wants to look at something specific, or typed random
        // gibberish after "look"
        {
            Look(cInfo, lInfo, word_two);
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (word_one == "take" or word_one == "get" or word_one == "grab"
    or word_one == "pickup")
    // Take commands
    {
        if (one_word)
        {
            cout << "You must specify something to take.\n";
            ProcessCommand(cInfo,lInfo);
        }
        else
        {
            Take(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "drop")
    {
        if (one_word)
        {
            Navigate(cInfo, lInfo, word_one);
        }
        else
        {
            Drop(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "give" or word_one == "present")
    // Give commands, used to give the treasure to the natives or a banana to
    // the gorilla
    {
        if (one_word)
        {
            cout << "You must specify something to give.\n";
            ProcessCommand(cInfo,lInfo);
        }
        else
        {
            Give(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "eat")
    // The player can eat the banana, or the key if they've already freed the
    // prisoner
    {
        if (one_word)
        {
            cout << "You must specify something to eat, as food isn't readily "
            << "available on a random island.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            Eat(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "cut")
    // The player can cut a banana from the banana tree
    {
        if (one_word)
        {
            cout << "You must specify something to cut.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (not inventoryContains(cInfo.item, "knife"))
        // The player does not have the knife and cannot cut anything
        {
            cout << "You have nothing with which to cut the " << word_two
            << ".\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            Cut(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "unlock")
    // The player can unlock the prisoner's cell if they have the key
    {
        if (one_word)
        {
            cout << "You must specify something to unlock.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            Unlock(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "open")
    // The player can open the prisoner's cell or the treasure trunk
    {
        if (one_word)
        {
            cout << "You must specify something to open.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            Open(cInfo, lInfo, word_two);
        }
    }
    else if (word_one == "sail")
    // Ends the game if the player gave the gorilla a banana and freed the
    // prisoner from the brig
    {
        if (cInfo.playerLocation.rawLoc == WHEEL)
        // The player is at the wheel
        {
            if (cInfo.GAVE_BANANA)
            // The gorilla is gone
            {
                if (cInfo.OPENED_CELL)
                // The prisoner is free
                {
                    cout << "Eager to leave the island behind, you and the "
                    << "former prisoner get ready to set sail. As the anchor is"
                    << " lifted and the sails are adjusted to the wind, ready "
                    << "to carry you wherever you want to go, you look back at "
                    << "the island one last time. ";
                    if (not cInfo.EGG_ONE)
                    {
                        cout << "You're ending your journey with many questions"
                        << " unanswered. Who you are, how you got here, and "
                        << "where the rest of the crew went are all still "
                        << "mysteries to you. But perhaps all that matters now "
                        << "is that you can finally return home...\nWhere do "
                        << "you live, again?\n\nEND\n\n";
                    }
                    else
                    {
                        cout << "A strange place filled with talking gorillas, "
                        << "among other things. You're thankful to leave.\n\n"
                        << "END\n\n";
                    }
                    // ProcessCommand() is missing from all of these responses,
                    // so the game will end as soon as one of them is given
                }
                else
                // The gorilla is gone but the prisoner has not been freed
                {
                    cout << "You have no idea how to sail a ship.\n";
                    ProcessCommand(cInfo, lInfo);
                }
            }
            else
            // The gorilla is still blocking the wheel
            {
                cout << "The gorilla blocks the wheel.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        // The player is not at the wheel
        {
            cout << "You can't sail the ship from here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (word_one == "help")
    {
        cout << "Commands may be one or two words depending on which command is"
        << " used. Available first words include \"go\", \"look\",\"take\", "
        << "\"give\", \"drop\", \"cut\", and \"eat\", as well as several "
        << "synonyms for those words.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (word_one == "save" and one_word)
    {
        saveData(cInfo, lInfo);
        ProcessCommand(cInfo, lInfo);
    }
    else if (word_one == "load" and one_word)
    {
        loadData(cInfo, lInfo);
    }
    else
    // The player entered an unknown command
    {
        cout << "I didn't recognize that command. Please try again or say \""
        <<"help\" for available commands.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Look(CharInfo cInfo, locInfo lInfo[], string objLook)
// Look function gets passed cInfo and lInfo so we can see information about the
// player, and objLook is what the player is trying to look at
{
    Location rL = cInfo.playerLocation.rawLoc;
    // Shorten location so we don't have to use "cInfo.playerLocation.rawLoc"
    if (objLook == "up")
    {
        if (rL == ISLAND or rL == BANANA_TREE)
        {
            cout << "You look up to see a clear blue sky. It's a nice day out."
            << endl;
        }
        else if (rL == HOLD)
        {
            cout << "I really don't think the ceiling is the most interesting "
            << "part of this room\n";
        }
        else if (rL == QUARTERS or rL == GALLEY)
        {
            cout << "There is a wooden ceiling inches above your face.\n";
        }
        else if (rL == WHEEL or rL == UDECK)
        {
            cout << "There are sails above you.\n";
        }
        else if (rL == LDECK)
        {
            cout << "There is a ladder leading up to the upper deck.\n";
        }
        else if (rL == BRIG)
        {
            cout << "There is a trapdoor above you. It didn't close on you, if "
            << "that's what you're worried about.\n";
        }
    }
    else if (objLook == "down")
    {
        if (rL == ISLAND)
        {
            cout << "You are standing on sand. Good luck getting that out of "
            << "your shoes.";
        }
        else if (rL == BANANA_TREE)
        {
            cout << "There is fertile soil here. Perfect for growing bananas.";
        }
        else if (rL == UDECK)
        {
            cout << "There is a ladder down to the lower deck. You can't see "
            << "in from here.";
        }
        else if (rL == LDECK)
        {
            cout << "There is a trapdoor below you.";
        }
        else if (rL == WHEEL or rL == GALLEY or rL == QUARTERS or rL == BRIG)
        {
            cout << "The floor here is made up of sturdy wooden boards.";
        }
        else if (rL == HOLD)
        {
            cout << "The floor is littered with various tools and coins.";
            // The tools and coins are glued to the floor as a practical joke
        }
        getDroppedItems(cInfo, lInfo);
        // The player should see the items they've dropped in the room if they
        // look down
    }
    else if (objLook == "gorilla")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        // The player is at the wheel but has not given the gorilla a banana, so
        // the gorilla is still blocking the wheel
        {
            cout << "The gorilla looks hostile. Probably best to leave it "
            << "alone.\n";
        }
        else
        // The player isn't at the wheel, or has already given the gorilla a
        // banana
        {
            cout << "The gorilla isn't here.\n";
        }
    }
    else if (objLook == "knife")
    {
        if (inventoryContains(cInfo.item, "knife") or (rL == QUARTERS and
        not cInfo.DROPPED_KNIFE) or
        inventoryContains(cInfo.playerLocation.droppedItems, "knife"))
        // The player has the knife in their inventory, or they're in the
        // quarters and haven't dropped the knife elsewhere, or they've dropped
        // the knife on the floor of the room they're in
        {
            cout << "Upon closer inspection, it appears the knife is actually "
            << "incredibly dull. It would be useless as a weapon, but good for "
            << "cutting.\n";
        }
        else
        // The player doesn't have the knife, and the knife isn't in the same
        // room as the player
        {
            cout << "There is no knife here.\n";
        }
    }
    else if (objLook == "banana" or objLook == "bananas")
    {
        if (inventoryContains(cInfo.item, "banana")
        or inventoryContains(cInfo.playerLocation.droppedItems, "banana"))
        // The player has a banana, or they've dropped one on the floor of the
        // room they're in
        {
            cout << "The banana is still ripe and ready to eat.\n";
        }
        else if (rL == BANANA_TREE)
        // The player doesn't have a banana nor have they dropped one in the
        // room they're in, but they're at the banana tree
        {
            cout << "There is one bunch of ripe bananas on the tree within "
            << "reach.\n";
        }
        else
        // The player doesn't have a banana, there aren't any in the room
        // they're in, and they're not at the banana tree
        {
            cout << "There are no bananas here.\n";
        }
    }
    else if (objLook == "treasure")
    {
        if (inventoryContains(cInfo.item, "treasure")
        or inventoryContains(cInfo.playerLocation.droppedItems, "treasure"))
        // The player has the treasure, or they've dropped the treasure on the
        // floor of the room they're in
        {
            cout << "The treasure is very shiny, and small enough to carry "
            << "around.\n";
        }
        else if (rL == HOLD)
        // The player doesn't have the treasure and it's not on the floor of the
        // room they're in, but they are in the cargo hold
        {
            if (cInfo.OPENED_TRUNK or cInfo.BROKE_TRUNK)
            // The trunk is open
            {
                if (not cInfo.GAVE_TREASURE)
                // The player has not given the treasure to the natives
                {
                    if (not cInfo.DROPPED_TREASURE)
                    // The player has not dropped the treasure in another room
                    {
                        cout << "The treasure is very shiny, and small enough "
                        << "to carry around.\n";
                    }
                    else
                    // The player has dropped the treasure in another room
                    {
                        cout << "The treasure is not here.\n";
                    }
                }
                else
                {
                    cout << "You've already given the treasure to the natives"
                    << "...\n";
                }
            }
            else
            // The trunk has not been opened
            {
                cout << "The trunk may have treasure, but it's closed.\n";
            }
        }
        else
        // The player is not in the cargo hold
        {
            cout << "There is no treasure here.\n";
        }
    }
    else if (objLook == "door" or objLook == "doorway")
    {
        if (rL == QUARTERS or rL == GALLEY or rL == HOLD)
        {
            cout << "I'll be honest with you, there's nothing that special "
            << "about the " << objLook << ".\n";
        }
        else if (rL == LDECK)
        {
            cout << "There are two " << objLook << "s, one to the north and one"
            << " to the south.\n";
        }
        else if (rL == BRIG)
        {
            if (cInfo.OPENED_CELL)
            // The player has freed the prisoner
            {
                cout << "The cell door is open.\n";
            }
            else if (cInfo.UNLOCKED_CELL)
            // The player has unlocked the cell door but it is still closed. Fix
            // later
            {
                cout << "The cell door is still closed.\n";
            }
            else
            // The player has not unlocked the cell
            {
                cout << "The cell door is still locked.\n";
            }
        }
        else
        // The player is not in the captain's quarters, the galley, the hold,
        // the lower deck, nor the brig
        {
            cout << "There are no " << objLook << "s here.\n";
            // Clever way to repeat whichever word the player used, door or
            // doorway
        }
    }
    else if (objLook == "cell")
    {
        if (rL == BRIG)
        {
            if (cInfo.OPENED_CELL)
            // The player has freed the prisoner
            {
                cout << "The cell door is open.\n";
            }
            else if (cInfo.UNLOCKED_CELL)
            // The player unlocked the cell but didn't open it. Fix later
            {
                cout << "The cell door is still closed.\n";
            }
            else
            // The player hasn't unlocked the cell
            {
                cout << "The cell door is still locked.\n";
            }
        }
        else
        // The player is not in the brig
        {
            cout << "There is no cell here.\n";
        }
    }
    else if (objLook == "trunk")
    {
        if (rL == HOLD)
        {
            if (cInfo.OPENED_TRUNK or cInfo.BROKE_TRUNK)
            // The player has opened the trunk
            {
                if (not inventoryContains(cInfo.item, "treasure") and not
                cInfo.GAVE_TREASURE and not cInfo.DROPPED_TREASURE)
                // The player does not have the treasure, hasn't given it to the
                // natives, and hasn't dropped it in another room
                {
                    cout << "Inside the trunk is a very shiny, very portable "
                    << "treasure.\n";
                }
                else
                // The player has removed the treasure from the trunk
                {
                    cout << "The trunk is empty.\n";
                }
            }
            else
            // The player hasn't opened the trunk
            {
                cout << "The trunk is closed.\n";
            }
        }
        else
        // The player is not in the cargo hold
        {
            cout << "There is no trunk here.\n";
        }
    }
    else if (objLook == "parrot")
    {
        if (rL == GALLEY)
        {
            if (cInfo.GOT_KEY_EARLY)
            {
                cout << "The parrot looks crestfallen, probably because you "
                << "didn't say hi to him. I hope you're happy.\n";
            }
            else
            {
                cout << "The parrot looks happy.\n";
            }
        }
        else
        {
            cout << "The parrot isn't here.\n";
        }
    }
    else if (objLook == "ship")
    {
        if (rL == ISLAND)
        {
            cout << "There is a large ship to your south. Something about it "
            << "seems familiar, but you can't quite place it... Have you seen "
            << "this ship before?\n";
        }
        else if (rL == BANANA_TREE)
        {
            cout << "You can just barely make out the ship from here.\n";
        }
        else
        // The player is somewhere on the ship
        {
            cout << "You're on a boat!\n";
        }
    }
    else if (objLook == "keys" or objLook == "key")
    {
        if (inventoryContains(cInfo.item, "key")
        or inventoryContains(cInfo.playerLocation.droppedItems, "key"))
        // The player has the key or it is on the ground in the room the player
        // is in
        {
            cout << "The key is golden, with a \"" << cInfo.name[0] << "\" on "
            << "one side.\n";
        }
        else if (cInfo.SAID_KEYWORD and rL == QUARTERS
        and not cInfo.DROPPED_KEY)
        // The key is in the captain's quarters and the parrot has told the
        // player where it is
        {
            cout << "The key was under the captain's bed, just like the parrot "
            << "said it would be.\n";
        }
        else if (rL == QUARTERS)
        // The parrot has not told the player where the key is
        {
            cout << "You don't see a key anywhere.\n";
        }
        else
        // The player is not in the captain's quarters
        {
            cout << "There is no key here.\n";
        }
    }
    else if (objLook == "ladder")
    {
        if (rL == UDECK)
        {
            cout << "There is a ladder going down to the lower deck.\n";
        }
        else if (rL == LDECK)
        {
            cout << "The ladder goes up to the upper deck.\n";
        }
        else
        {
            cout << "There is no ladder here.\n";
        }
    }
    else if (objLook == "tree")
    {
        if (rL == BANANA_TREE)
        {
            if (not inventoryContains(cInfo.item, "banana"))
            // The player does not have a banana
            {
                cout << "There is one bunch of ripe bananas on the tree within "
                << "reach.\n";
            }
            else
            // The player already has a banana
            {
                cout << "The tree has been picked clean of ripe bananas.\n";
            }
        }
        else if (rL == ISLAND)
        {
            cout << "The trees around you have green bananas on them. Probably "
            << "best to leave them alone.\n";
        }
        else
        // The player is on the ship
        {
            cout << "There are no trees nearby.\n";
        }
    }
    else if (objLook == "stem")
    {
        if (rL == BANANA_TREE)
        {
            if (not inventoryContains(cInfo.item, "banana"))
            // The player does not have a banana
            {
                cout << "There is one bunch of ripe bananas on the tree within "
                << "reach.\n";
            }
            else
            // The player already has a banana
            {
                cout << "The tree has been picked clean of ripe bananas.\n";
            }
        }
        else if (rL == ISLAND)
        {
            cout << "The trees around you have green bananas on them. Probably "
            << "best to leave them alone.\n";
        }
        else
        // The player is on the ship
        {
            cout << "There are no banana trees nearby.\n";
        }
    }
    else if (objLook == "trapdoor")
    {
        if (rL == LDECK)
        {
            cout << "The trapdoor at your feet leads below.\n";
        }
        else if (rL == BRIG)
        {
            cout << "It didn't close on you, if that's what you're worried "
            << "about.\n";
        }
        else
        {
            cout << "There is no trapdoor here.\n";
        }
    }
    else if (objLook == "sign")
    {
        if (rL == ISLAND)
        {
            cout << "The sign reads \"BEWARE OF SAVAGE NATIVES\" in messy "
            << "handwriting, almost as if someone had written it in a hurry.\n";
        }
        else
        {
            cout << "There is no sign here.\n";
        }
    }
    else
    {
        cout << "I only understood you as far as wanting to look.\n";
    }
}
void Take(CharInfo cInfo, locInfo lInfo[], string objTake)
// Take function gets passed cInfo and lInfo so we can see information about the
// player, and objTake is what the player is trying to take
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objTake == "bananas")
    // Redefine possible synonym
    {
        objTake = "banana";
    }
    if (objTake == "keys")
    // Redefine possible synonym
    {
        objTake = "key";
    }
    if (inventoryContains(cInfo.item, objTake))
    // Explain why the player can't get duplicate items
    {
        cout << "You already have the " << objTake << ".\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (InventoryFull(cInfo.item))
    // Respect MAX_ITEMS_CARRIED
    {
        cout << "Inventory is full.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objTake == "gorilla")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        // The gorilla is at the wheel
        {
            cout << "You cannot.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The gorilla isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "knife")
    {
        if (inventoryContains(cInfo.playerLocation.droppedItems, "knife"))
        // The player is taking the knife back from where they dropped it
        {
            cout << "You got the knife.\n";
            cInfo.DROPPED_KNIFE = false;
            pickupItem(cInfo, lInfo, "knife");
        }
        else if (rL == QUARTERS and not cInfo.DROPPED_KNIFE)
        {
            cout << "You got the knife.\n";
            getItem(cInfo, lInfo, "knife");
        }
        else
        {
            cout << "There is no knife here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "banana")
    {
        if (inventoryContains(cInfo.playerLocation.droppedItems, "banana"))
        // The player is taking a banana back from where they dropped it
        {
            cout << "You got a banana.\n";
            pickupItem(cInfo, lInfo, "banana");
        }
        else if (rL == BANANA_TREE)
        {
            if (inventoryContains(cInfo.item, "knife"))
            // The player has the knife
            {
                cout << "You got a banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
            // The player does not have the knife
            {
                cout << "You cannot separate the banana from the tree.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There are no bananas here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "stem")
    {
        if (rL == BANANA_TREE)
        {
            if (inventoryContains(cInfo.playerLocation.droppedItems, "banana"))
            // The player is taking a banana back from where they dropped it
            {
                cout << "You got a banana.\n";
                pickupItem(cInfo, lInfo, "banana");
            }
            else if (inventoryContains(cInfo.item, "knife"))
            // The player has the knife
            {
                cout << "You got a banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
            // The player does not have the knife
            {
                cout << "The stem of the banana tree is too tough.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There are no banana trees nearby.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "treasure")
    {
        if (inventoryContains(cInfo.playerLocation.droppedItems, "treasure"))
        // The player is taking the treasure back from where they dropped it
        {
            cout << "You got the treasure.\n";
            cInfo.DROPPED_TREASURE = false;
            pickupItem(cInfo, lInfo, "treasure");
        }
        else if (rL == HOLD and not cInfo.DROPPED_TREASURE)
        {
            if (not cInfo.GAVE_TREASURE)
            // The treasure is in the trunk
            {
                if (cInfo.OPENED_TRUNK)
                {
                    cout << "You got the treasure.\n";
                    getItem(cInfo, lInfo, "treasure");
                }
                else
                // Joke about forgetting to open the trunk first
                {
                    cout << "You punch through the closed trunk and spend a "
                    << "great deal of time and effort pulling the treasure "
                    << "through the hole you created. After several minutes you"
                    << " manage to remove your splinter-ridden hand from the "
                    << "trunk, clutching the treasure. The force with which you"
                    << " remove your hand pushes the top of the trunk open. You"
                    << " realize it was never locked, and you could have just "
                    << "opened the trunk first...\n\nYou got the treasure.\n";
                    cInfo.BROKE_TRUNK = true;
                    getItem(cInfo, lInfo, "treasure");
                }
            }
            else
            {
                cout << "You've already given the treasure to the natives"
                << "...\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There is no treasure here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "trunk")
    {
        if (rL == HOLD)
        {
            cout << "The trunk is too heavy to carry.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no trunk here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "door")
    {
        if (rL == QUARTERS or rL == GALLEY or rL == HOLD)
        {
            cout << "You cannot remove the door from the frame, and frankly I "
            << "don't understand why you would want to.";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == UDECK or rL == LDECK)
        {
            cout << "There are no doors within reach.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There are no doors here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "cell")
    {
        if (rL == BRIG)
        {
            cout << "Not physically possible.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no cell here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "parrot")
    {
        if (rL == GALLEY)
        {
            cout << "The parrot seems opposed to the idea.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The parrot isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "ship")
    {
        cout << "That's the goal, but it wouldn't be any fun if it were that "
        << "easy.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objTake == "key")
    {
        if (inventoryContains(cInfo.playerLocation.droppedItems, "key"))
        // The player is taking the key back from where they dropped it
        {
            cout << "You got the key.\n";
            cInfo.DROPPED_KEY = false;
            pickupItem(cInfo, lInfo, "key");
        }
        else if (rL == QUARTERS and not cInfo.DROPPED_KEY)
        // The key has not been taken from the quarters
        {
            if (cInfo.SAID_KEYWORD)
            // Player solved the parrot puzzle
            {
                cout << "You got the key.\n";
                getItem(cInfo, lInfo, "key");
            }
            else
            // Player took the key without solving the parrot puzzle
            {
                cout << "You were in such a rush to finish the game without "
                << "properly solving the puzzles that you decided to ignore the"
                << " parrot completely and just go straight for the key. "
                << "Nobody is happy about this.\n";
                cInfo.GOT_KEY_EARLY = true;
                getItem(cInfo, lInfo, "key");
            }
        }
        else
        {
            cout << "There is no key here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "room")
    {
        if (rL == QUARTERS or rL == GALLEY or rL == HOLD)
        {
            cout << "What? How? Why? I don't understand how that would even "
            << "work. No.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no room here. Also I don't think that's "
            << "possible.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "ladder")
    {
        if (rL == UDECK)
        {
            cout << "The ladder is a part of the ship.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == LDECK)
        {
            cout << "The ladder is a part of the ship. You cannot remove it "
            << "from the wall.";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no ladder here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "tree")
    {
        if (rL == ISLAND or rL == BANANA_TREE)
        {
            cout << "The trees are rooted and probably wouldn't fit in your "
            << "pockets.\n";
        }
        else
        {
            cout << "There are no trees here.\n";
        }
    }
    else if (objTake == "trapdoor")
    {
        if (rL == LDECK or rL == BRIG)
        {
            cout << "Please don't.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no trapdoor here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objTake == "sign")
    {
        if (rL == ISLAND)
        {
            cout << "You get the feeling that's a bad idea...\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no sign here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else
    {
        cout << "I only understood you as far as wanting to take.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Drop(CharInfo cInfo, locInfo lInfo[], string objDrop)
// Drop function gets passed cInfo and lInfo so we can see information about the
// player, and objDrop is what the player is trying to drop
{
    if (objDrop == "bananas")
    {
        objDrop = "banana";
    }
    if (objDrop == "keys")
    {
        objDrop = "key";
    }
    // Redefine possible synonyms
    if (not (objDrop == "banana") and not (objDrop == "knife") and not
    (objDrop == "key") and not (objDrop == "treasure"))
    // The player is trying to drop something that is not an item
    {
        cout << "I only understood you as far as wanting to drop an item.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (not inventoryContains(cInfo.item, objDrop))
    // The player does not have the item they're trying to drop
    {
        cout << "You don't have a " << objDrop << ".\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (InventoryFull(cInfo.playerLocation.droppedItems))
    {
        cout << "There is no room here to drop any more items.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objDrop == "banana")
    {
        cout << "You dropped a banana on the floor.\n";
        // We don't use a bool to keep track of whether the player has dropped a
        // banana since the player can get another one even if they did drop one
        dropItem(cInfo, lInfo, "banana");
        // We use dropItem() rather than removeItem() because we need to add the
        // dropped object to the room's inventory
    }
    else if (objDrop == "knife")
    {
        cout << "You dropped the knife on the floor.\n";
        cInfo.DROPPED_KNIFE = true;
        dropItem(cInfo, lInfo, "knife");
    }
    else if (objDrop == "key")
    {
        cout << "You dropped the key on the floor.\n";
        cInfo.DROPPED_KEY = true;
        dropItem(cInfo, lInfo, "key");
    }
    else if (objDrop == "treasure")
    {
        cout << "You dropped the treasure on the floor.\n";
        cInfo.DROPPED_TREASURE = true;
        dropItem(cInfo, lInfo, "treasure");
    }
}
void Give(CharInfo cInfo, locInfo lInfo[], string objGive)
// Give function gets passed cInfo and lInfo so we can see information about the
// player, and objGive is what the player is trying to give
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objGive == "bananas")
    {
        objGive = "banana";
    }
    if (objGive == "keys")
    {
        objGive = "key";
    }
    if (not (objGive == "banana") and not (objGive == "knife") and not
    (objGive == "key") and not (objGive == "treasure"))
    // The player is trying to give something that is not an item
    {
        cout << "I only understood you as far as wanting to give.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (not inventoryContains(cInfo.item, objGive))
    // The player tried to give something they don't have
    {
        cout << "You don't have a " << objGive << ".\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objGive == "knife")
    // There is no scenario where the player should be able to give the knife
    {
        cout << "You should probably keep the knife.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objGive == "banana")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        // The player and gorilla are both at the wheel
        {
            cout << "You gave the gorilla the banana. He seems offended for "
            << "some reason, but takes it anyway.\n";
            cInfo.GAVE_BANANA = true;
            removeItem(cInfo, lInfo, "banana");
        }
        else if (rL == GALLEY)
        {
            cout << "The parrot doesn't seem to want the banana.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == BRIG and not cInfo.OPENED_CELL)
        // The prisoner is still in the cell
        {
            cout << "The prisoner is allergic to bananas, so best not.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == UDECK and not cInfo.GAVE_TREASURE and cInfo.SEEN_NATIVES)
        // The player is trying to give a banana to the natives
        {
            cout << "The natives probably have their own supply of bananas.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is nobody here to whom you can give the banana.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objGive == "key")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        // The gorilla is at the wheel
        {
            cout << "The gorilla doesn't seem to want the key.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == GALLEY)
        {
            cout << "The parrot doesn't seem to want the key.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == BRIG and not cInfo.OPENED_CELL)
        // The prisoner is still in the cell
        {
            cout << "The prisoner says \"You found the key! I don't have a "
            << "keyhole on this side, so go ahead and unlock that side and get "
            << "me out of here.\"\n";
            // The player must unlock the cell, not give the prisoner the key
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == UDECK and cInfo.SEEN_NATIVES and not cInfo.GAVE_TREASURE)
        // The player is trying to give the key to the natives
        {
            cout << "The natives have no interest in a key.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is nobody here to whom you can give the key.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objGive == "treasure")
    {
        if (rL == UDECK and cInfo.SEEN_NATIVES)
        // The player is giving the treasure to the natives
        {
            cout << "You lay the treasure at the base of the gangplank. One of "
            << "the natives steps forward, picks it up, and looks it over. He "
            << "gives you a brief nod of approval and shouts something in his "
            << "language. He and the rest of the natives disperse, clearing a "
            << "way back to the island.\n";
            cInfo.GAVE_TREASURE = true;
            removeItem(cInfo, lInfo, "treasure");
        }
        else if (rL == WHEEL and not cInfo.EGG_ONE and not cInfo.GAVE_BANANA)
        // The player is trying to give the treasure to the gorilla
        {
            cout << "The gorilla takes the treasure from you and examines it. "
            << "He says \"I believe I've seen something like this before among "
            << "the island natives. They take great pride in their treasure, "
            << "and would likely love to have it back.\" He returns it to you "
            << "before remembering that gorillas can't talk.\n";
            cInfo.EGG_ONE = true;
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == WHEEL and not cInfo.GAVE_BANANA)
        // :)
        {
            cout << "The gorilla doesn't seem to want the treasure.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == GALLEY)
        {
            cout << "The parrot doesn't seem to want the treasure.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == BRIG and not cInfo.OPENED_CELL)
        // The prisoner is still in the cell and the player is trying to give
        // them the treasure
        {
            cout << "The prisoner is taking a nap right now, though I'm sure "
            << "he'd be flattered that you thought of him.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is nobody here to whom you can give the treasure.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
}
void Eat(CharInfo cInfo, locInfo lInfo[], string objEat)
// Eat function gets passed cInfo and lInfo so we can see information about the
// player, and objEat is what the player is trying to eat
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objEat == "bananas")
    {
        objEat = "banana";
    }
    if (objEat == "keys")
    {
        objEat == "key";
    }
    if (objEat == "banana")
    {
        if (not inventoryContains(cInfo.item, "banana"))
        {
            cout << "You don't have a banana.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "You eat the banana.\n";
            removeItem(cInfo, lInfo, "banana");
        }
    }
    else if (objEat == "key")
    {
        if (not inventoryContains(cInfo.item, "key"))
        {
            cout << "You don't have a key.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (cInfo.OPENED_CELL)
        {
            cout << "Through great effort, you manage to swallow the key. Not "
            << "sure why you would, but you did.\n";
            cInfo.DROPPED_KEY = true;
            removeItem(cInfo, lInfo, "key");
            // Setting the key to dropped and removing it from the player's
            // inventory means they will never be able to get it again, so they
            // must first open the prisoner's cell
        }
        else
        // The player has not yet opened the prisoner's cell
        {
            cout << "I wouldn't.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objEat == "knife")
    {
        if (not inventoryContains(cInfo.item, "knife"))
        {
            cout << "You don't have a knife, sicko.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "You are not trained in the strange art of knife and sword "
            << "eating, and decide not to.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objEat == "treasure")
    {
        if (not inventoryContains(cInfo.item, "treasure"))
        {
            cout << "You don't have a treasure.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "You get the feeling you shouldn't.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objEat == "parrot")
    {
        if (rL == GALLEY)
        {
            cout << "The parrot would disagree with you, both from a moral "
            << "standpoint and a digestive one.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The parrot isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objEat == "gorilla")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        {
            cout << "Good luck.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The gorilla isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objEat == "prisoner")
    {
        if (rL == BRIG and not cInfo.OPENED_CELL)
        // The prisoner is still in the cell
        {
            cout << "Cannibalism is never the answer on a banana-filled "
            << "island.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The prisoner isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else
    {
        cout << "I only understood you as far as wanting to eat.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Cut(CharInfo cInfo, locInfo lInfo[], string objCut)
// Cut function gets passed cInfo and lInfo so we can see information about the
// player, and objCut is what the player is trying to cut
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objCut == "bananas")
    {
        objCut = "banana";
    }
    if (objCut == "keys")
    {
        objCut = "key";
    }
    if (objCut == "banana")
    {
        if (inventoryContains(cInfo.item, "banana"))
        {
            cout << "The knife looks too dirty to cut food.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == BANANA_TREE)
        {
            if (not InventoryFull(cInfo.item))
            {
                cout << "You got a banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
            {
                cout << "Inventory is full.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else if (inventoryContains(cInfo.playerLocation.droppedItems, "banana"))
        // There is a banana on the floor of the room the player is in
        {
            cout << "The knife looks too dirty to cut food.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no banana here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objCut == "stem")
    {
        if (rL == BANANA_TREE)
        {
            if (inventoryContains(cInfo.item, "banana"))
            {
                cout << "You already have a banana.\n";
            }
            else if (not InventoryFull(cInfo.item))
            {
                cout << "You got a banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
            {
                cout << "Inventory is full.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else if (rL == ISLAND)
        {
            cout << "There are no banana trees nearby.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There are no banana trees here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objCut == "gorilla")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        // The player and the gorilla are at the wheel
        {
            cout << "That would only make it more angry.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The gorilla isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objCut == "parrot")
    {
        if (rL == GALLEY)
        {
            cout << "That's messed up. No.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "The parrot, thankfully, isn't here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else
    {
        cout << "I only understood you as far as wanting to cut.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Open(CharInfo cInfo, locInfo lInfo[], string objOpen)
// Open function gets passed cInfo and lInfo so we can see information about the
// player, and objOpen is what the player is trying to open
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objOpen == "door" and rL == BRIG)
    {
        objOpen = "cell";
    }
    if (objOpen == "cell")
    {
        if (rL == BRIG)
        {
            if (cInfo.UNLOCKED_CELL)
            // Change later to just check for the player having the key
            {
                cout << "You open the cell door. The prisoner says \"Oh thank "
                << "God, I needed some fresh air. I'm gonna head to the wheel, "
                << "let me know when you're ready to leave this stupid island."
                << "\"\n";
                cInfo.OPENED_CELL = true;
                ProcessCommand(cInfo, lInfo);
            }
            else
            {
                cout << "The cell is locked.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There is no cell door here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objOpen == "door")
    {
        if (rL == QUARTERS or rL == GALLEY or rL == HOLD)
        {
            cout << "The door is already open. Looks like the crew left in a "
            << "hurry.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == UDECK or rL == LDECK)
        {
            cout << "There are no doors within reach.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There are no doors here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objOpen == "trunk")
    {
        if (rL == HOLD)
        {
            if (cInfo.OPENED_TRUNK or cInfo.BROKE_TRUNK)
            {
                cout << "The trunk is already open.\n";
                ProcessCommand(cInfo, lInfo);
            }
            else
            {
                cout << "You opened the trunk. There is a gleaming treasure "
                << "inside\n";
                cInfo.OPENED_TRUNK = true;
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There is no trunk here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objOpen == "trapdoor")
    {
        if (rL == LDECK)
        {
            cout << "The trapdoor is already open.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == BRIG)
        {
            cout << "The trapdoor is still open.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There is no trapdoor here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else
    {
        cout << "I only understood you as far as wanting to open.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Unlock(CharInfo cInfo, locInfo lInfo[], string objUnlock)
// Unlock function gets passed cInfo and lInfo so we can see information about
// the player, and objUnlock is what the player is trying to unlock. Merge with
// Open() later
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objUnlock == "cell")
    {
        if (rL == BRIG)
        {
            if (inventoryContains(cInfo.item, "key"))
            {
                cout << "You unlock the cell.\n";
                cInfo.UNLOCKED_CELL = true;
                ProcessCommand(cInfo, lInfo);
            }
            else
            {
                cout << "You don't have the key.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There is no cell here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objUnlock == "door")
    {
        if (rL == UDECK or rL == LDECK)
        {
            cout << "There are no doors within reach.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == QUARTERS or rL == GALLEY or rL == HOLD)
        {
            cout << "The door is already open.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            cout << "There are no doors here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (objUnlock == "trunk")
    {
        if (rL == HOLD)
        {
            if (cInfo.OPENED_TRUNK or cInfo.BROKE_TRUNK)
            {
                cout << "The trunk is already open.\n";
                ProcessCommand(cInfo, lInfo);
            }
            else
            {
                cout << "You don't see a keyhole anywhere on the trunk.\n";
                // The player doesn't need to unlock the trunk, only to open it
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "There is no trunk here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else
    {
        cout << "I only understood you as far as wanting to unlock.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void goToLoc(CharInfo cInfo, locInfo lInfo[], string locToGo)
// Sends the player to locToGo or explains why the player cannot go there
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (locToGo == "island")
    {
        if (rL == UDECK)
        // The player is trying to go from the upper deck to the island
        {
            if (cInfo.GAVE_TREASURE)
            // The natives do not block the path
            {
                Island(cInfo, lInfo);
            }
            else
            // The natives block the path
            {
                if (not cInfo.SEEN_NATIVES)
                // The player has not yet got the message that natives are
                // blocking the path
                {
                    cout << "The island's natives have apparently noticed your "
                    << "arrival, and have blocked your way off the ship. One of"
                    << " them shouts something. Unfortunately, you do not speak"
                    << " their language.\n";
                    cInfo.SEEN_NATIVES = true;
                    ProcessCommand(cInfo, lInfo);
                }
                else
                // The player has already got the message that the natives are
                // blocking the path
                {
                    cout << "The natives still block your path.\n";
                    ProcessCommand(cInfo, lInfo);
                }
            }
        }
        else
        {
            Island(cInfo, lInfo);
        }
    }
    else if (locToGo == "banana_tree")
    {
        BananaTree(cInfo, lInfo);
    }
    else if (locToGo == "uDeck")
    {
        UpperDeck(cInfo, lInfo);
    }
    else if (locToGo == "wheel")
    {
        ShipsWheel(cInfo, lInfo);
    }
    else if (locToGo == "lDeck")
    {
        LowerDeck(cInfo, lInfo);
    }
    else if (locToGo == "galley")
    {
        Galley(cInfo, lInfo);
    }
    else if (locToGo == "brig")
    {
        Brig(cInfo, lInfo);
    }
    else if (locToGo == "quarters")
    {
        CaptainsQuarters(cInfo, lInfo);
    }
    else if (locToGo == "hold")
    {
        CargoHold(cInfo, lInfo);
    }
    else if (locToGo == "no_room")
    // The player tried to move off the map
    {
        cout << "There is nowhere to go in that direction.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (locToGo == "crows_nest")
    {
        cout << "You try to climb to the crow's nest, but quickly realize there"
        << " is nothing on which to climb. The crew must've been very good at"
        << " acrobatics.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (locToGo == "off_ship")
    {
        if (rL == UDECK)
        {
            cout << "This ship has no plank to walk. What kind of pirates don't"
            << " have a plank?";
        }
        else if (cInfo.GAVE_BANANA)
        {
            cout << "You walk to the edge of the ship and look out to see a "
            << "blue sea. Nowhere to go except shark-infested waters.\n";
        }
        else
        {
            cout << "The gorilla steps in front of you and puts a hand out. He "
            << "says \"There isn't currently a lifeguard on duty. You'd better "
            << "stay out of the water.\"\n";
        }
        ProcessCommand(cInfo, lInfo);
    }
}
void Navigate(CharInfo cInfo, locInfo lInfo[], string drctn)
// Handles navigation commands by calling goToLoc() with the desired location
// using the player's current location and the direction they wanted to move
// (drctn)
{
    int spaceholder = drctn.find(" ");
    if (not (spaceholder == -1))
    // If the direction passed to the function is more than one word
    {
        drctn = drctn.substr(spaceholder+1);
        // Use the second word as the actual direction (in case of commands like
        // "move north" or "go down")
    }
    if (drctn == "north" or drctn == "n")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.north);
    }
    else if (drctn == "east" or drctn == "e")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.east);
    }
    else if (drctn == "south" or drctn == "s")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.south);
    }
    else if (drctn == "west" or drctn == "w")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.west);
    }
    else if (drctn == "up" or drctn == "u" or drctn == "climb")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.up);
    }
    else if (drctn == "down" or drctn == "d" or drctn == "drop")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.down);
    }
    else
    // The string drctn wasn't recognized as a valid direction
    {
        cout<<"Invalid direction. Please enter a cardinal direction, \"up\", or"
        <<" \"down\".\n\n";
        getline(cin, drctn);
        cout << endl;
        // Makes the spacing look better
        transform(drctn.begin(), drctn.end(), drctn.begin(), ::tolower);
        // Makes all input lowercase
        Navigate(cInfo, lInfo, drctn);
        // Function recurses with new direction
    }
}
bool inventoryContains(string inventory[], string item)
// Check whether the inventory "inventory[]" contains the item "item"
{
    int i;  // Iterator for the loop on the next line
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    // Iterates through every inventory space (note that inventory is 0-indexed)
    {
        if (inventory[i] == item)
        // The inventory contains the specified item at inventory[i]
        {
            return true;
            // The function returns true to its call and stops further function
            // execution to prevent the later return false statement
        }
    }
    // If the function reaches this point, the item was not found in the given
    // inventory, so we return false
    return false;
}
bool InventoryFull(string inventory[])
// Check whether the inventory is full. Responds gracefully in the event
// MAX_ITEMS_CARRIED is changed
{
    int i;
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        if (inventory[i] == "empty")
        // There is an empty space in the inventory at inventory[i]
        {
            return false;
        }
    }
    return true;
}
void getItem(CharInfo cInfo, locInfo lInfo[], string objGet)
// Used to put an item in the player's inventory. Should check for a full
// inventory beforehand to avoid overflow
{
    int i;
    int spaceNumber = -1;
    for (i = MAX_ITEMS_CARRIED - 1; i >= 0; i--)
    // The loop counts backwards from MAX_ITEMS_CARRIED but still finds the
    // lowest available space because it does not exit after finding the first
    // empty space
    {
        if (cInfo.item[i] == "empty")
        {
            spaceNumber = i;
        }
    }
    if (spaceNumber == -1)
    {
        cout << "ERROR: Inventory overflow\n";
        abort();
        // The inventory is somehow full despite inventoryFull() saying
        // otherwise. Kill the program to avoid unforeseen consequences
    }
    else
    {
        cInfo.item[spaceNumber] = objGet;
        // Put the item objGet into the first open inventory space
        ProcessCommand(cInfo, lInfo);
    }
}
void pickupItem(CharInfo cInfo, locInfo lInfo[], string objPick)
// Used to put an item in the player's inventory. Should check for a full
// inventory beforehand to avoid overflow. Different from getItem() in that this
// function is used to retrieve dropped items, and thus removes them from the
// room's inventory after giving them to the player
{
    int i;
    int spaceNumber = -1;
    for (i = MAX_ITEMS_CARRIED - 1; i >= 0; i--)
    // The loop counts backwards from MAX_ITEMS_CARRIED but still finds the
    // lowest available space because it does not exit after finding the first
    // instance of the item
    {
        if (cInfo.playerLocation.droppedItems[i] == objPick)
        {
            spaceNumber = i;
        }
    }
    if (spaceNumber == -1)
    {
        cout << "ERROR: No item\n";
        abort();
        // Item was not found in the current room despite that being a
        // requirement for this function to run. Kill the program to avoid
        // unforeseen consequences
    }
    else
    {
        cInfo.playerLocation.droppedItems[spaceNumber] = "empty";
        // Empty the space in the room where the item was
        lInfo[cInfo.playerLocation.rawLoc].droppedItems[spaceNumber] = "empty";
        // Also remove the item from lInfo since that object is used to populate
        // cInfo.playerLocation
        getItem(cInfo, lInfo, objPick);
    }
}
void removeItem(CharInfo cInfo, locInfo lInfo[], string objRem)
{
    int i;
    int spaceNumber = -1;
    for (i = MAX_ITEMS_CARRIED - 1; i >= 0; i--)
    // The loop counts backwards from MAX_ITEMS_CARRIED but still finds the
    // lowest available space because it does not exit after finding the first
    // instance of the item
    {
        if (cInfo.item[i] == objRem)
        {
            spaceNumber = i;
        }
    }
    if (spaceNumber == -1)
    {
        cout << "ERROR: No item\n";
        abort();
        // Item was not found in the player's inventory despite that being a
        // requirement for this function to run. Kill the program to avoid
        // unforeseen consequences
    }
    else
    {
        cInfo.item[spaceNumber] = "empty";
        // Remove the item from the player's inventory at the index spaceNumber
        ProcessCommand(cInfo, lInfo);
    }
}
void dropItem(CharInfo cInfo, locInfo lInfo[], string objPut)
{
    int i;
    int spaceNumber = -1;
    for (i = MAX_ITEMS_CARRIED - 1; i >= 0; i--)
    // The loop counts backwards from MAX_ITEMS_CARRIED but still finds the
    // lowest available space because it does not exit after finding the first
    // empty space
    {
        if (cInfo.playerLocation.droppedItems[i] == "empty")
        {
            spaceNumber = i;
        }
    }
    if (spaceNumber == -1)
    {
        cout << "ERROR: droppedItems overflow\n";
        abort();
        // The room's inventory is somehow full despite inventoryFull() saying
        // otherwise. Kill the program to avoid unforeseen consequences
    }
    else
    {
        cInfo.playerLocation.droppedItems[spaceNumber] = objPut;
        // Drop the item to the room's inventory at the index spaceNumber
        lInfo[cInfo.playerLocation.rawLoc].droppedItems[spaceNumber] = objPut;
        // Also add the item to lInfo since that object is used to populate
        // cInfo.playerLocation
        removeItem(cInfo, lInfo, objPut);
    }
}
string pigLatin(string inp)
// Takes a string input and returns the pig latin equivalent. ProcessCommand()
// ensures that this function is only ever passed one word at a time
{
    int vowelSpace;
    // Used to store the location of the first vowel in the word
    string temp_one, temp_two, out;
    // temp_one and temp_two are used to store the first and second parts of the
    // word, respectively, in the event that the word contains consonants before
    // the first vowel. "out" is where we put the output to ensure it ends up as
    // a string before we return it, just in case
    vowelSpace = inp.find_first_of(VOWELS);
    if (vowelSpace == -1)
    // The word contains no vowels, somehow. Probably just random typing
    {
        out = inp + "ay";
        // Append "ay" and return the result
        return out;
    }
    else if (vowelSpace == 0)
    // The first letter in the word is a vowel
    {
        out = inp + "way";
        // Append "way" and return the result
        return out;
    }
    else
    {
        temp_one = inp.substr(0,vowelSpace);
        // Store the first part of the word up to but not including the first
        // vowel
        temp_two = inp.substr(vowelSpace);
        // Store the second part of the word starting with the first vowel
        out = temp_two + temp_one + "ay";
        // Store the second part of the word, the first consonants of the word,
        // and "ay", in that order
        return out;
    }
    
}
void getDroppedItems(CharInfo cInfo, locInfo lInfo[])
// Tell the player what dropped items the room contains
{
    int i;  // Iterator for loops
    int num_items = 0;
    // Number of dropped items. Setting it to 0 here acts as a default value
    string floorItems[MAX_ITEMS_CARRIED];
    // Array of items on the floor
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    // Order doesn't actually matter here in terms of functionality alone, but
    // we still start from 0 so that the items are described in the order that
    // they were dropped
    {
        if (not (cInfo.playerLocation.droppedItems[i] == "empty"))
        // There is an item at the indicated space
        {
            floorItems[num_items] = cInfo.playerLocation.droppedItems[i];
            // Add the item at the indicated space to floorItems
            num_items++;
            // Use num_items in conjunction with the fact that floorItems is
            // 0-indexed to keep track of what space of floorItems should be
            // populated
        }
    }
    switch (num_items)
    // Update later to support MAX_ITEMS_CARRIED being a number greater than 3
    {
        case 0:
        cout << endl;
        break;
        case 1:
        cout << " On the ground is a " << floorItems[0] << ".\n";
        break;
        case 2:
        cout << " On the ground is a " << floorItems[0] << " and a "
        << floorItems[1] << ".\n";
        break;
        case 3:
        cout << " On the ground is a " << floorItems[0] << ", a "
        << floorItems[1] << ", and a " << floorItems[2] << ".\n";
        break;
    }
}
void saveData(CharInfo cInfo, locInfo lInfo[])
{
    int i;  // Iterator
    string out;
    ofstream saveFile;
    saveFile.open("save0", std::ofstream::out | std::ofstream::trunc);
    out = cInfo.name + "\n";  // 1
    out += cInfo.playerLocation.name + "\n";  // 2
    out += to_string(MAX_ITEMS_CARRIED) + "\n";  // 3
    out += boolNum(cInfo.SAID_KEYWORD) + "\n";  // 4
    out += boolNum(cInfo.GAVE_TREASURE) + "\n";  // 5
    out += boolNum(cInfo.SEEN_NATIVES) + "\n";  // 6
    out += boolNum(cInfo.GAVE_BANANA) + "\n";  // 7
    out += boolNum(cInfo.SEEN_I) + "\n";  // 8
    out += boolNum(cInfo.SEEN_L) + "\n";  // 9
    out += boolNum(cInfo.SEEN_Q) + "\n";  // 10
    out += boolNum(cInfo.SEEN_W) + "\n";  // 11
    out += boolNum(cInfo.SEEN_G) + "\n";  // 12
    out += boolNum(cInfo.SEEN_H) + "\n";  // 13
    out += boolNum(cInfo.SEEN_B) + "\n";  // 14
    out += boolNum(cInfo.OPENED_TRUNK) + "\n";  // 15
    out += boolNum(cInfo.BROKE_TRUNK) + "\n";  // 16
    out += boolNum(cInfo.UNLOCKED_CELL) + "\n";  // 17
    out += boolNum(cInfo.OPENED_CELL) + "\n";  // 18
    out += boolNum(cInfo.DROPPED_KNIFE) + "\n";  // 19
    out += boolNum(cInfo.DROPPED_KEY) + "\n";  // 20
    out += boolNum(cInfo.DROPPED_TREASURE) + "\n";  // 21
    out += boolNum(cInfo.GOT_KEY_EARLY) + "\n";  // 22
    out += boolNum(cInfo.BONKED) + "\n";  // 23
    out += boolNum(cInfo.EGG_ONE) + "\n";  // 24
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += cInfo.item[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[ISLAND].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*2
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[BANANA_TREE].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*3
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[UDECK].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*4
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[WHEEL].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*5
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[LDECK].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*6
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[GALLEY].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*7
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[BRIG].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*8
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[QUARTERS].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*9
    for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
    {
        out += lInfo[HOLD].droppedItems[i] + "\n";
    }  // 24 + MAX_ITEMS_CARRIED*10
    saveFile << out;
    saveFile.close();
    cout << "Data saved to file \"save0\".\n";
}
string boolNum(bool boolToNum)
{
    string numOfBool;
    if (boolToNum)
    {
        numOfBool = "1";
    }
    else
    {
        numOfBool = "0";
    }
    return numOfBool;
}
void loadData(CharInfo cInfo, locInfo lInfo[])
{
    int tempMax, lineHolder, i;
    string line, entireSave;
    Location rL;
    ifstream saveFile("save0");
    if (saveFile.is_open())
    {
        while (getline(saveFile, line))
        {
            entireSave += line + "\n";
        }
        saveFile.close();
        lineHolder = entireSave.find_first_of("\n");
        cInfo.name = entireSave.substr(0, lineHolder);
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        rL = printRawLoc(entireSave.substr(0, lineHolder));
        cInfo.playerLocation = lInfo[rL];
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        tempMax = stoi(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        if (not (tempMax == MAX_ITEMS_CARRIED))
        {
            cout << "You have loaded a save file that is not compatible with "
            << "this version of the game. There is no way to recover from "
            << "this.\n";
            abort();
        }
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SAID_KEYWORD = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.GAVE_TREASURE = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_NATIVES = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.GAVE_BANANA = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_I = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_L = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_Q = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_W = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_G = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_H = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.SEEN_B = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.OPENED_TRUNK = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.BROKE_TRUNK = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.UNLOCKED_CELL = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.OPENED_CELL = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.DROPPED_KNIFE = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.DROPPED_KEY = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.DROPPED_TREASURE = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.GOT_KEY_EARLY = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.BONKED = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        lineHolder = entireSave.find_first_of("\n");
        cInfo.EGG_ONE = numBool(entireSave.substr(0, lineHolder));
        entireSave.erase(0, lineHolder + 1);
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            cInfo.item[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[ISLAND].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[BANANA_TREE].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[UDECK].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[WHEEL].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[LDECK].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[GALLEY].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[BRIG].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[QUARTERS].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        for (i = 0; i <= MAX_ITEMS_CARRIED - 1; i++)
        {
            lineHolder = entireSave.find_first_of("\n");
            lInfo[HOLD].droppedItems[i] = entireSave.substr(0, lineHolder);
            entireSave.erase(0, lineHolder + 1);
        }
        cout << "File loaded successfully.\n\n";
        goToLoc(cInfo, lInfo, cInfo.playerLocation.name);
    }
    else
    {
        cout << "Unable to open file.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
bool numBool(string numToBool)
{
    if (numToBool == "1")
    {
        return true;
    }
    else if (numToBool == "0")
    {
        return false;
    }
    else
    {
        cout << "ERROR: Missing bool\n";
        abort();
    }
}
Location printRawLoc(string locToPrint)
{
    if (locToPrint == "island")
    {
        return ISLAND;
    }
    else if (locToPrint == "banana_tree")
    {
        return BANANA_TREE;
    }
    else if (locToPrint == "uDeck")
    {
        return UDECK;
    }
    else if (locToPrint == "wheel")
    {
        return WHEEL;
    }
    else if (locToPrint == "lDeck")
    {
        return LDECK;
    }
    else if (locToPrint == "galley")
    {
        return GALLEY;
    }
    else if (locToPrint == "brig")
    {
        return BRIG;
    }
    else if (locToPrint == "quarters")
    {
        return QUARTERS;
    }
    else if (locToPrint == "hold")
    {
        return HOLD;
    }
    else
    {
        cout << "ERROR: invalid location on line 3 of save0\n";
        abort();
    }
}

// Copyright 2020 Christopher Andrade, Lawrence Rede, Amaan Ahmed,
// Ivan Dorantes, Karlee Wilkinson

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


