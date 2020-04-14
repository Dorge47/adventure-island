// Group 4: Lawrence Rede, Christopher Andrade, Amaan Ahmed, Ivan Dorantes,
// Karlee Wilkinson, Ernest
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
const int MAX_ITEMS_CARRIED=3;
const string VOWELS = "AEIOUYaeiouy";
enum Location 
//no_room should always be the last room
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
    dir nextRoom;
    Location rawLoc;
};
struct CharInfo{
    int itemsAmnt;
    string item[MAX_ITEMS_CARRIED];
    locInfo playerLocation;
    string name;
    bool SAID_KEYWORD, GAVE_TREASURE, WIN_GAME, SEEN_NATIVES, GAVE_BANANA,
    SEEN_I, SEEN_L, SEEN_Q, SEEN_W, SEEN_G, SEEN_H, SEEN_B, OPENED_TRUNK,
    BROKE_TRUNK, UNLOCKED_CELL, OPENED_CELL, GOT_KEY_EARLY, BONKED, EGG_ONE;
};
void startGame(CharInfo, locInfo[]);
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
void removeItem(CharInfo, locInfo[], string);
string pigLatin(string);

int main()
{
    CharInfo cInfo;
    locInfo room[NO_ROOM];
    cout<<"What is your name?\n\n";
    getline(cin,cInfo.name);
    cout << endl;
    cout<<"You have just awakened on a strange island with a terrible headache."
    <<" You can't remember anything about yourself or where you are.\n\n";
    startGame(cInfo, room);
    return 0;
}
void startGame(CharInfo cInfo, locInfo lInfo[]){
    int i;  // Iterator for later
    lInfo[ISLAND].name = "island";
    lInfo[ISLAND].rawLoc = ISLAND;
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
    lInfo[UDECK].description = "There is a wheel at the east end of the ship, ";
    lInfo[UDECK].description += "and a ladder down to the lower deck. The ";
    lInfo[UDECK].description += "captain's quarters are to the west and there ";
    lInfo[UDECK].description += "is a gangplank leading back to the island to ";
    lInfo[UDECK].description += "the north.";
    lInfo[UDECK].nextRoom.north = "island";
    lInfo[UDECK].nextRoom.south = "no_room";
    lInfo[UDECK].nextRoom.east = "wheel";
    lInfo[UDECK].nextRoom.west = "quarters";
    lInfo[UDECK].nextRoom.up = "no_room";
    lInfo[UDECK].nextRoom.down = "lDeck";
    lInfo[WHEEL].name = "wheel";
    lInfo[WHEEL].rawLoc = WHEEL;
    lInfo[WHEEL].description = "The gorilla still blocks the wheel. The deck ";
    lInfo[WHEEL].description += "is to the west.";
    lInfo[WHEEL].nextRoom.north = "no_room";
    lInfo[WHEEL].nextRoom.south = "no_room";
    lInfo[WHEEL].nextRoom.east = "no_room";
    lInfo[WHEEL].nextRoom.west = "uDeck";
    lInfo[WHEEL].nextRoom.up = "no_room";
    lInfo[WHEEL].nextRoom.down = "no_room";
    lInfo[LDECK].name = "lDeck";
    lInfo[LDECK].rawLoc = LDECK;
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
    lInfo[BRIG].description = "The prisoner is still locked in his cell. There";
    lInfo[BRIG].description += " is nothing else in the room besides a ladder ";
    lInfo[BRIG].description += "leading back up.";
    lInfo[BRIG].nextRoom.north = "no_room";
    lInfo[BRIG].nextRoom.south = "no_room";
    lInfo[BRIG].nextRoom.east = "no_room";
    lInfo[BRIG].nextRoom.west = "no_room";
    lInfo[BRIG].nextRoom.up = "lDeck";
    lInfo[BRIG].nextRoom.down = "no_room";
    lInfo[QUARTERS].name = "quarters";
    lInfo[QUARTERS].rawLoc = QUARTERS;
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
    lInfo[HOLD].description = "Inside the cargo hold, there are barrels, ";
    lInfo[HOLD].description += "various tools, and ";
    lInfo[HOLD].nextRoom.north = "no_room";
    lInfo[HOLD].nextRoom.south = "lDeck";
    lInfo[HOLD].nextRoom.east = "no_room";
    lInfo[HOLD].nextRoom.west = "no_room";
    lInfo[HOLD].nextRoom.up = "no_room";
    lInfo[HOLD].nextRoom.down = "no_room";
    cInfo.SAID_KEYWORD = false;
    cInfo.GAVE_TREASURE = false;
    cInfo.WIN_GAME = false;
    cInfo.SEEN_NATIVES = false;
    cInfo.GAVE_BANANA = false;
    cInfo.SEEN_I = false;
    cInfo.SEEN_L = false;
    cInfo.SEEN_Q = false;
    cInfo.SEEN_W = false;
    cInfo.SEEN_G = false;
    cInfo.SEEN_H = false;
    cInfo.SEEN_B = false;
    cInfo.OPENED_TRUNK = false;
    cInfo.BROKE_TRUNK = false;
    cInfo.UNLOCKED_CELL = false;
    cInfo.OPENED_CELL = false;
    cInfo.GOT_KEY_EARLY = false;
    cInfo.BONKED = false;
    cInfo.EGG_ONE = false;
    for (i = 0; i <= MAX_ITEMS_CARRIED; i++)
    {
        cInfo.item[i] = "empty";
    }
    Island(cInfo, lInfo);
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
        else {
            cout << cInfo.playerLocation.description;
            if (not inventoryContains(cInfo.item, "knife"))
            {
                cout << " On the table is a knife.";
            }
            cout << endl;
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
                inventoryContains(cInfo.item, "treasure"))
                {
                    cout << "an open trunk, with gleaming treasure inside.";
                }
                else
                {
                    cout << "an empty trunk.";
                }
            }
            else if (cInfo.BROKE_TRUNK)
            {
                cout << "an empty trunk.";
            }
            else
            {
                cout << "a trunk.";
            }
            cout << " There is a doorway to the south.\n";
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
            cout << cInfo.playerLocation.description << endl;
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
        {
            cout << "The cell is open and empty. There is nothing else in the "
            << "room besides a ladder leading back up.\n";
        }
        else
        {
            cout << cInfo.playerLocation.description << endl;
        }
        ProcessCommand(cInfo, lInfo);
    }
void ShipsWheel(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
ShipsWheel will happen.*/
    {
        cInfo.playerLocation = lInfo[WHEEL];
        if (not cInfo.SEEN_W) {
            cout<<"There is a large gorilla by the ship's wheel. This gorilla "
            <<"is hostile. You can't touch the wheel. The deck is to the west."
            <<endl;
            cInfo.SEEN_W = true;
        }
        else
        {
            if (cInfo.GAVE_BANANA)
            {
                if (cInfo.OPENED_CELL)
                {
                    cout << "From the wheel you can see the prisoner sitting on"
                    << " the ropes that connect the sails. He seems to know how"
                    << " to work them. If you wish, you could set sail, or "
                    << "return west to the deck.\n";
                }
                else
                {
                    cout << "There is a wheel here. The deck is to the west.\n";
                }
            }
            else
            {
                cout << cInfo.playerLocation.description << endl;
            }
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
        {
            cout << " There is one bunch of ripe bananas on the tree within "
            << "reach.";
        }
        cout << endl;
        ProcessCommand(cInfo, lInfo);
    }
void UpperDeck(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
UpperDeck will happen.*/
{
    cInfo.playerLocation = lInfo[UDECK];
    cout << cInfo.playerLocation.description << endl;
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
        cout << cInfo.playerLocation.description << endl;
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
        <<"with a gangplank to the shore.\n";
        cInfo.SEEN_I = true;
    }
    else {
        cout << cInfo.playerLocation.description << endl;
    }
    ProcessCommand(cInfo, lInfo);
}
void ProcessCommand(CharInfo cInfo, locInfo lInfo[])
// Separates the command into two strings: word_one and word_two
{
    string commands, word_one, word_two, parrot_resp, pig_lat;
    int spaceholder;
    bool one_word = false;
    Location rL = cInfo.playerLocation.rawLoc;
    cout << endl;
    getline(cin, commands);
    cout << endl;
    transform(commands.begin(), commands.end(), commands.begin(), ::tolower);
    // Make all input lowercase
    spaceholder = commands.find(" ");
    word_one = commands.substr(0,spaceholder);
    word_two = commands.substr(spaceholder+1);
    if (spaceholder == -1)
    {
        one_word = true;
    }
    spaceholder = word_two.find(" ");
    if (not (spaceholder == -1) and not (cInfo.playerLocation.rawLoc == GALLEY
    and not cInfo.SAID_KEYWORD))
    {
        cout << "Please enter up to two words at a time.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (word_one == "go" or word_one == "move" or word_one == "walk")
    {
        Navigate(cInfo, lInfo, word_two);
    }
    else if (word_one == "n" or word_one == "e" or word_one == "s" or word_one
    == "w" or word_one == "u" or word_one == "d" or word_one == "north" or
    word_one == "east" or word_one == "south" or word_one == "west" or word_one
    == "up" or word_one == "down" or word_one == "climb" or word_one == "drop")
    {
        Navigate(cInfo, lInfo, word_one);
    }
    else if (word_one == "look" or word_one == "inspect")
    {
        if (one_word or word_two == "room" or word_two == "around")
        {
            goToLoc(cInfo, lInfo, cInfo.playerLocation.name);
        }
        else if (word_two == "ladder" and cInfo.playerLocation.rawLoc == LDECK
        and not cInfo.BONKED)
        {
            cout << "You turn around and smack your head into the ladder, "
            << "forgetting how close you were to it. That's gonna leave a "
            << "bruise.\n";
            cInfo.BONKED = true;
            ProcessCommand(cInfo, lInfo);
        }
        else
        {
            Look(cInfo, lInfo, word_two);
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if (word_one == "take" or word_one == "get" or word_one == "grab")
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
    else if (word_one == "give" or word_one == "present")
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
    {
        if (one_word)
        {
            cout << "You must specify something to cut.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (not inventoryContains(cInfo.item, "knife"))
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
    {
        if (rL == WHEEL)
        {
            if (cInfo.GAVE_BANANA)
            {
                if (cInfo.OPENED_CELL)
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
                }
                else
                {
                    cout << "You have no idea how to sail a ship.\n";
                    ProcessCommand(cInfo, lInfo);
                }
            }
            else
            {
                cout << "The gorilla blocks the wheel.\n";
                ProcessCommand(cInfo, lInfo);
            }
        }
        else
        {
            cout << "You can't sail the ship from here.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
    else if ((word_one == "polly" or word_one == "hello" or
    word_one == "cracker" or word_one == "hi") and
    cInfo.playerLocation.rawLoc == GALLEY and not cInfo.SAID_KEYWORD)
    {
        cout << "The parrot lets out a delighted squawk and replies \"You "
        << "figured it out! In exchange for solving my puzzle, I'll tell you "
        << "where the captain hides the key to the brig: It's under the bed in "
        << "the Captain's Quarters. Good luck!\"\n";
        cInfo.SAID_KEYWORD = true;
        ProcessCommand(cInfo, lInfo);
    }
    else if (word_one == "quit" or word_one == "exit" or word_one == "close")
    {
        cout << "Goodbye.\n";
    }
    else if (cInfo.playerLocation.rawLoc == GALLEY and not cInfo.SAID_KEYWORD)
    {
        parrot_resp = commands;
        if (one_word)
        {
            cout << "The parrot replies: \"" << pigLatin(word_one) << "\".\n";
        }
        else
        {
            pig_lat = "";
            cout << "The parrot replies: \"";
            while (not (parrot_resp.find(" ") == -1))  // While there is a space
            // meaning there are more words to parse
            {
                spaceholder = parrot_resp.find(" ");
                pig_lat += pigLatin(parrot_resp.substr(0, spaceholder)) + " ";
                parrot_resp.erase(0, spaceholder+1);
            }
            pig_lat += pigLatin(parrot_resp);
            cout << pig_lat << "\".\n";
        }
        ProcessCommand(cInfo, lInfo);
    }
    else
    {
        cout << "I didn't recognize that command. Please try again or say \""
        <<"help\" for available commands.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Look(CharInfo cInfo, locInfo lInfo[], string objLook)
{
    // Shorten location so we don't have to use "cInfo.playerLocation.rawLoc"
    Location rL = cInfo.playerLocation.rawLoc;
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
            << "your shoes.\n";
        }
        else if (rL == BANANA_TREE)
        {
            cout << "There is fertile soil here. Perfect for growing bananas."
            << endl;
        }
        else if (rL == UDECK)
        {
            cout << "There is a ladder down to the lower deck. You can't see "
            << "in from here.\n";
        }
        else if (rL == LDECK)
        {
            cout << "There is a trapdoor below you.\n";
        }
        else if (rL == WHEEL or rL == GALLEY or rL == QUARTERS or rL == BRIG)
        {
            cout << "The floor here is made up of sturdy wooden boards.\n";
        }
        else if (rL == HOLD)
        {
            cout << "The floor is littered with various tools and coins.\n";
            // The tools and coins are glued to the floor as a practical joke
        }
    }
    else if (objLook == "gorilla")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
        {
            cout << "The gorilla looks hostile. Probably best to leave it "
            << "alone.\n";
        }
        else
        {
            cout << "The gorilla isn't here.\n";
        }
    }
    else if (objLook == "knife")
    {
        if (inventoryContains(cInfo.item, "knife") or rL == QUARTERS)
        {
            cout << "Upon closer inspection, it appears the knife is actually "
            << "incredibly dull. It would be useless as a weapon, but good for "
            << "cutting.\n";
        }
        else
        {
            cout << "There is no knife here.\n";
        }
    }
    else if (objLook == "banana" or objLook == "bananas")
    {
        if (inventoryContains(cInfo.item, "banana"))
        {
            cout << "The bananas are still ripe and ready to eat.\n";
        }
        else if (rL == BANANA_TREE)
        {
            cout << "There is one bunch of ripe bananas on the tree within "
            << "reach.\n";
        }
        else
        {
            cout << "There are no bananas here.\n";
        }
    }
    else if (objLook == "treasure")
    {
        if (inventoryContains(cInfo.item, "treasure"))
        {
            cout << "The treasure is very shiny, and small enough to carry "
            << "around.\n";
        }
        else if (rL == HOLD)
        {
            if (cInfo.OPENED_TRUNK)
            {
                if (not cInfo.GAVE_TREASURE)
                {
                    cout << "The treasure is very shiny, and small enough to "
                    << "carry around.\n";
                }
                else
                {
                    cout << "You've already given the treasure to the natives"
                    << "...\n";
                }
            }
            else
            {
                cout << "The trunk may have treasure, but it's closed.\n";
            }
        }
        else
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
            {
                cout << "The cell door is open.\n";
            }
            else if (cInfo.UNLOCKED_CELL)
            {
                cout << "The cell door is still closed.\n";
            }
            else
            {
                cout << "The cell door is still locked.\n";
            }
        }
        else {
            cout << "There are no " << objLook << "s here.\n";
        }
    }
    else if (objLook == "cell")
    {
        if (rL == BRIG)
        {
            if (cInfo.OPENED_CELL)
            {
                cout << "The cell door is open.\n";
            }
            else if (cInfo.UNLOCKED_CELL)
            {
                cout << "The cell door is still closed.\n";
            }
            else
            {
                cout << "The cell door is still locked.\n";
            }
        }
        else
        {
            cout << "There is no cell here.\n";
        }
    }
    else if (objLook == "trunk")
    {
        if (rL == HOLD)
        {
            if (cInfo.OPENED_TRUNK)
            {
                if (not inventoryContains(cInfo.item, "treasure") and not
                cInfo.GAVE_TREASURE)
                {
                    cout << "Inside the trunk is a very shiny, very portable "
                    << "treasure.\n";
                }
                else {
                    cout << "The trunk is empty.\n";
                }
            }
            else
            {
                cout << "The trunk is closed.\n";
            }
        }
        else
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
            else if (cInfo.SAID_KEYWORD)
            {
                cout << "The parrot looks happy.\n";
            }
            else
            {
                cout << "The parrot is sitting patiently on his perch.\n";
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
        {
            cout << "You're on a boat!\n";
        }
    }
    else if (objLook == "keys" or objLook == "key")
    {
        if (inventoryContains(cInfo.item, "key"))
        {
            cout << "The key is golden, with a \"" << cInfo.name[0] << "\" on "
            << "one side.\n";
        }
        else if (cInfo.SAID_KEYWORD and rL == QUARTERS)
        {
            cout << "The key was under the captain's bed, just like the parrot "
            << "said it would be.\n";
        }
        else if (rL == QUARTERS)
        {
            cout << "You don't see a key anywhere.\n";
        }
        else
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
            {
                cout << "There is one bunch of ripe bananas on the tree within "
                << "reach.\n";
            }
            else
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
        {
            cout << "There are no trees nearby.\n";
        }
    }
    else if (objLook == "stem")
    {
        if (rL == BANANA_TREE)
        {
            if (not inventoryContains(cInfo.item, "banana"))
            {
                cout << "There is one bunch of ripe bananas on the tree within "
                << "reach.\n";
            }
            else
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
    else
    {
        cout << "I only understood you as far as wanting to look.\n";
    }
}
void Take(CharInfo cInfo, locInfo lInfo[], string objTake)
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objTake == "bananas")
    {
        objTake = "banana";
    }
    if (objTake == "keys")
    {
        objTake = "key";
    }
    if (inventoryContains(cInfo.item, objTake))
    {
        cout << "You already have the " << objTake << ".\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (InventoryFull(cInfo.item))
    {
        cout << "Inventory is full.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objTake == "gorilla")
    {
        if (rL == WHEEL)
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
        if (rL == QUARTERS)
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
        if (rL == BANANA_TREE)
        {
            if (inventoryContains(cInfo.item, "banana"))
            {
                cout << "You already have the banana.\n";
                ProcessCommand(cInfo, lInfo);
            }
            else if (inventoryContains(cInfo.item, "knife"))
            {
                cout << "You got the banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
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
            if (inventoryContains(cInfo.item, "banana"))
            {
                cout << "You already have the banana.\n";
                ProcessCommand(cInfo, lInfo);
            }
            else if (inventoryContains(cInfo.item, "knife"))
            {
                cout << "You got the banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
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
        if (rL == HOLD)
        {
            if (not cInfo.GAVE_TREASURE)
            {
                if (cInfo.OPENED_TRUNK)
                {
                    cout << "You got the treasure.\n";
                    getItem(cInfo, lInfo, "treasure");
                }
                else
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
        if (rL == QUARTERS)
        {
            if (cInfo.SAID_KEYWORD)
            {
                cout << "You got the key.\n";
                getItem(cInfo, lInfo, "key");
            }
            else
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
    else
    {
        cout << "I only understood you as far as wanting to take.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Give(CharInfo cInfo, locInfo lInfo[], string objGive)
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objGive == "bananas")
    {
        objGive = "banana";
    }
    if (objGive == "keys")
    {
        objGive == "key";
    }
    if (not (objGive == "banana") and not (objGive == "knife") and not
    (objGive == "key") and not (objGive == "treasure"))
    {
        cout << "I only understood you as far as wanting to give.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (not inventoryContains(cInfo.item, objGive))
    {
        cout << "You don't have a " << objGive << ".\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objGive == "knife")
    {
        cout << "You should probably keep the knife.\n";
        ProcessCommand(cInfo, lInfo);
    }
    else if (objGive == "banana")
    {
        if (rL == WHEEL and not cInfo.GAVE_BANANA)
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
        {
            cout << "The prisoner is allergic to bananas, so best not.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == UDECK and not cInfo.GAVE_TREASURE and cInfo.SEEN_NATIVES)
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
        {
            cout << "The prisoner says \"You found the key! I don't have a "
            << "keyhole on this side, so go ahead and unlock that side and get "
            << "me out of here.\"\n";
            ProcessCommand(cInfo, lInfo);
        }
        else if (rL == UDECK and cInfo.SEEN_NATIVES and not cInfo.GAVE_TREASURE)
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
        {
            cout << "The prisoner is taking a nap right now, though I'm sure "
            << "he'd be flattered that you thought of him.\n";
            ProcessCommand(cInfo, lInfo);
        }
        else {
            cout << "There is nobody here to whom you can give the treasure.\n";
            ProcessCommand(cInfo, lInfo);
        }
    }
}
void Eat(CharInfo cInfo, locInfo lInfo[], string objEat)
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
            removeItem(cInfo, lInfo, "key");
        }
        else
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
                cout << "You got the banana.\n";
                getItem(cInfo, lInfo, "banana");
            }
            else
            {
                cout << "Inventory is full.\n";
                ProcessCommand(cInfo, lInfo);
            }
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
                cout << "You got the banana.\n";
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
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (objOpen == "cell")
    {
        if (rL == BRIG)
        {
            if (cInfo.UNLOCKED_CELL)
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
                cout << "You opened the trunk.\n";
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
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (locToGo == "island")
    {
        if (rL == UDECK)
        {
            if (cInfo.GAVE_TREASURE)
            {
                Island(cInfo, lInfo);
            }
            else
            {
                if (not cInfo.SEEN_NATIVES)
                {
                    cout << "The island's natives have apparently noticed your "
                    << "arrival, and have blocked your way off the ship. One of"
                    << " them shouts something. Unfortunately, you do not speak"
                    << " their language.\n";
                    cInfo.SEEN_NATIVES = true;
                    ProcessCommand(cInfo, lInfo);
                }
                else
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
    {
        cout << "There is nowhere to go in that direction.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Navigate(CharInfo cInfo, locInfo lInfo[], string drctn)
{
    int spaceholder = drctn.find(" ");
    if (spaceholder != -1)
    {
        drctn = drctn.substr(spaceholder+1);
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
    {
        cout<<"Invalid direction. Please enter a cardinal direction, \"up\", or"
        <<" \"down\".\n\n";
        getline(cin, drctn);
        cout << endl;
        transform(drctn.begin(), drctn.end(), drctn.begin(), ::tolower);
        Navigate(cInfo, lInfo, drctn);
    }
}
bool inventoryContains(string inventory[], string item)
{
    int i;
    for (i = 0; i <= MAX_ITEMS_CARRIED; i++)
    {
        if (inventory[i] == item)
        {
            return true;
        }
    }
    return false;
}
bool InventoryFull(string inventory[])
{
    int i;
    for (i = 0; i <= MAX_ITEMS_CARRIED; i++)
    {
        if (inventory[i] == "empty")
        {
            return false;
        }
    }
    return true;
}
void getItem(CharInfo cInfo, locInfo lInfo[], string objGet)
{
    int i;
    int spaceNumber = -1;
    for (i = MAX_ITEMS_CARRIED; i >= 0; i--)
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
    }
    else
    {
        cInfo.item[spaceNumber] = objGet;
        ProcessCommand(cInfo, lInfo);
    }
}
void removeItem(CharInfo cInfo, locInfo lInfo[], string objRem)
{
    int i;
    int spaceNumber = -1;
    for (i = MAX_ITEMS_CARRIED; i >= 0; i--)
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
    }
    else
    {
        cInfo.item[spaceNumber] = "empty";
        ProcessCommand(cInfo, lInfo);
    }
}
string pigLatin(string inp)
{
    int vowelSpace;
    string temp_one, temp_two, out;
    vowelSpace = inp.find_first_of(VOWELS);
    if (vowelSpace == -1)
    {
        out = inp + "ay";
        return out;
    }
    else if (vowelSpace == 0)
    {
        out = inp + "way";
        return out;
    }
    else
    {
        temp_one = inp.substr(0,vowelSpace);
        temp_two = inp.substr(vowelSpace);
        out = temp_two + temp_one + "ay";
        return out;
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


