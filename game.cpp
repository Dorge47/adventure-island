#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
const int MAX_ITEMS_CARRIED=3;
enum Location 
//no_room should always be the last room
{quarters,hold,galley,brig,wheel,banana_tree,uDeck,lDeck,island,no_room};
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
    OPENED_CELL, GOT_KEY_EARLY, BONKED;
};
void startGame(CharInfo, locInfo[]);
void CaptainsQuarters(CharInfo, locInfo[]);
void CargoHold(CharInfo, locInfo[]);
void Galley(CharInfo, locInfo[]);
void Brig(CharInfo, locInfo[]);
int ShipsWheel(CharInfo, locInfo[]);
void BananaTree(CharInfo, locInfo[]);
void UpperDeck(CharInfo, locInfo[]);
void LowerDeck(CharInfo, locInfo[]);
void Island(CharInfo, locInfo[]);
void ProcessCommand(CharInfo, locInfo[]);
void Look(CharInfo, locInfo[], string);
void Navigate(CharInfo, locInfo[], string);
void goToLoc(CharInfo, locInfo[], string);
bool inventoryContains(string[], string);

int main()
{
    CharInfo cInfo;
    locInfo room[no_room];
    bool WIN_GAME;
    int x;
    cout<<"What is your name?\n\n";
    getline(cin,cInfo.name);
    cout << endl;
    cout<<"You have just awakened on a strange island with a terrible headache."
    <<" You can't remember anything about yourself or where you are.\n\n";
    startGame(cInfo, room);
    while(not WIN_GAME)
    {
        cout<<"to end program enter 1"<<endl;
        cin>>WIN_GAME;
    }
    if (WIN_GAME)
           {
           cout<<"You win. CRAB RAVE"<<endl;
           }
    return 0;
}
void startGame(CharInfo cInfo, locInfo lInfo[]){
    lInfo[island].name = "island";
    lInfo[island].rawLoc = island;
    lInfo[island].description = "You are on the island. There is a tree with ";
    lInfo[island].description += "ripe bananas to your north, and a gangplank ";
    lInfo[island].description += "to the ship to the south.";
    lInfo[island].nextRoom.north = "banana_tree";
    lInfo[island].nextRoom.south = "uDeck";
    lInfo[island].nextRoom.east = "no_room";
    lInfo[island].nextRoom.west = "no_room";
    lInfo[island].nextRoom.up = "no_room";
    lInfo[island].nextRoom.down = "no_room";
    lInfo[banana_tree].name = "banana_tree";
    lInfo[banana_tree].rawLoc = banana_tree;
    lInfo[banana_tree].description = "There is a large banana tree here, and ";
    lInfo[banana_tree].description += "thick forest to all sides except the ";
    lInfo[banana_tree].description += "south.";
    lInfo[banana_tree].nextRoom.north = "no_room";
    lInfo[banana_tree].nextRoom.south = "island";
    lInfo[banana_tree].nextRoom.east = "no_room";
    lInfo[banana_tree].nextRoom.west = "no_room";
    lInfo[banana_tree].nextRoom.up = "no_room";
    lInfo[banana_tree].nextRoom.down = "no_room";
    lInfo[uDeck].name = "uDeck";
    lInfo[uDeck].rawLoc = uDeck;
    lInfo[uDeck].description = "There is a wheel at the east end of the ship, ";
    lInfo[uDeck].description += "and a ladder down to the lower deck. The ";
    lInfo[uDeck].description += "captain's quarters are to the west and there ";
    lInfo[uDeck].description += "is a gangplank leading back to the island to ";
    lInfo[uDeck].description += "the north.";
    lInfo[uDeck].nextRoom.north = "island";
    lInfo[uDeck].nextRoom.south = "no_room";
    lInfo[uDeck].nextRoom.east = "wheel";
    lInfo[uDeck].nextRoom.west = "quarters";
    lInfo[uDeck].nextRoom.up = "no_room";
    lInfo[uDeck].nextRoom.down = "lDeck";
    lInfo[wheel].name = "wheel";
    lInfo[wheel].rawLoc = wheel;
    lInfo[wheel].description = "The gorilla still blocks the wheel. The deck ";
    lInfo[wheel].description += "is to the west.";
    lInfo[wheel].nextRoom.north = "no_room";
    lInfo[wheel].nextRoom.south = "no_room";
    lInfo[wheel].nextRoom.east = "no_room";
    lInfo[wheel].nextRoom.west = "uDeck";
    lInfo[wheel].nextRoom.up = "no_room";
    lInfo[wheel].nextRoom.down = "no_room";
    lInfo[lDeck].name = "lDeck";
    lInfo[lDeck].rawLoc = lDeck;
    lInfo[lDeck].description = "There are doors to your north and south, and a";
    lInfo[lDeck].description += " trapdoor below you.";
    lInfo[lDeck].nextRoom.north = "hold";
    lInfo[lDeck].nextRoom.south = "galley";
    lInfo[lDeck].nextRoom.east = "no_room";
    lInfo[lDeck].nextRoom.west = "no_room";
    lInfo[lDeck].nextRoom.up = "uDeck";
    lInfo[lDeck].nextRoom.down = "brig";
    lInfo[galley].name = "galley";
    lInfo[galley].rawLoc = galley;
    lInfo[galley].description = "There is a parrot in the corner of the room, ";
    lInfo[galley].description += "and a doorway to your north.";
    lInfo[galley].nextRoom.north = "lDeck";
    lInfo[galley].nextRoom.south = "no_room";
    lInfo[galley].nextRoom.east = "no_room";
    lInfo[galley].nextRoom.west = "no_room";
    lInfo[galley].nextRoom.up = "no_room";
    lInfo[galley].nextRoom.down = "no_room";
    lInfo[brig].name = "brig";
    lInfo[brig].rawLoc = brig;
    lInfo[brig].description = "The prisoner is still locked in his cell. There";
    lInfo[brig].description += " is nothing else in the room besides a ladder ";
    lInfo[brig].description += "leading back up.";
    lInfo[brig].nextRoom.north = "no_room";
    lInfo[brig].nextRoom.south = "no_room";
    lInfo[brig].nextRoom.east = "no_room";
    lInfo[brig].nextRoom.west = "no_room";
    lInfo[brig].nextRoom.up = "lDeck";
    lInfo[brig].nextRoom.down = "no_room";
    lInfo[quarters].name = "quarters";
    lInfo[quarters].rawLoc = quarters;
    lInfo[quarters].description = "Inside the captain's quarters, there is a ";
    lInfo[quarters].description += "bed and a table.";
    lInfo[quarters].nextRoom.north = "no_room";
    lInfo[quarters].nextRoom.south = "no_room";
    lInfo[quarters].nextRoom.east = "uDeck";
    lInfo[quarters].nextRoom.west = "no_room";
    lInfo[quarters].nextRoom.up = "no_room";
    lInfo[quarters].nextRoom.down = "no_room";
    lInfo[hold].name = "hold";
    lInfo[hold].rawLoc = hold;
    lInfo[hold].description = "Inside the cargo hold, there are barrels, ";
    lInfo[hold].description += "various tools, and ";
    lInfo[hold].nextRoom.north = "no_room";
    lInfo[hold].nextRoom.south = "lDeck";
    lInfo[hold].nextRoom.east = "no_room";
    lInfo[hold].nextRoom.west = "no_room";
    lInfo[hold].nextRoom.up = "no_room";
    lInfo[hold].nextRoom.down = "no_room";
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
    cInfo.OPENED_CELL = false;
    cInfo.GOT_KEY_EARLY = false;
    cInfo.BONKED = false;
    Island(cInfo, lInfo);
}
void CaptainsQuarters(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
CaptainsQuarters will happen.*/
    {
        cInfo.playerLocation = lInfo[quarters];
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
        cInfo.playerLocation = lInfo[hold];
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
        cInfo.playerLocation = lInfo[galley];
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
        cInfo.playerLocation = lInfo[brig];
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
        else {
            cout << cInfo.playerLocation.description << endl;
        }
        ProcessCommand(cInfo, lInfo);
    }
int ShipsWheel(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
ShipsWheel will happen.*/
    {
        cInfo.playerLocation = lInfo[wheel];
        if (not cInfo.SEEN_W) {
            cout<<"There is a large gorilla by the ship's wheel. This gorilla "
            <<"is hostile. You can't touch the wheel. The deck is to the west."
            <<endl;
            cInfo.SEEN_W = true;
        }
        else
        {
            cout << cInfo.playerLocation.description << endl;
        }
        ProcessCommand(cInfo, lInfo);
        return 0;
    }
void BananaTree(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
BananaTree will happen.*/
    {
        cInfo.playerLocation = lInfo[banana_tree];
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
    cInfo.playerLocation = lInfo[uDeck];
    cout << cInfo.playerLocation.description << endl;
    ProcessCommand(cInfo, lInfo);
}
void LowerDeck(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
LowerDeck will happen.*/
{
    cInfo.playerLocation = lInfo[lDeck];
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
    cInfo.playerLocation = lInfo[island];
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
    string commands, word_one, word_two;
    int spaceholder;
    bool one_word = false;
    Location rL = cInfo.playerLocation.rawLoc;
    cout << endl;
    getline(cin, commands);
    cout << endl;
    transform(commands.begin(), commands.end(), commands.begin(), ::tolower);
    spaceholder = commands.find(" ");
    word_one = commands.substr(0,spaceholder);
    word_two = commands.substr(spaceholder+1);
    if (spaceholder == -1)
    {
        one_word = true;
    }
    if (word_one == "go" or word_one == "move" or word_one == "walk")
    {
        Navigate(cInfo, lInfo, word_two);
    }
    else if (word_one == "n" or word_one == "e" or word_one == "s" or word_one
    == "w" or word_one == "u" or word_one == "d" or word_one == "north" or
    word_one == "east" or word_one == "south" or word_one == "west" or word_one
    == "up" or word_one == "down")
    {
        Navigate(cInfo, lInfo, word_one);
    }
    else if (word_one == "look")
    {
        if (one_word or word_two == "room" or word_two == "around")
        {
            goToLoc(cInfo, lInfo, cInfo.playerLocation.name);
        }
        else if (word_two == "ladder" and cInfo.playerLocation.rawLoc == lDeck and
        not cInfo.BONKED)
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
    else if (word_one == "quit" or word_one == "exit" or word_one == "close")
    {
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
    Location rL = cInfo.playerLocation.rawLoc;
    if (objLook == "up")
    {
        if (rL == island or rL == banana_tree)
        {
            cout << "You look up to see a clear blue sky. It's a nice day out."
            << endl;
        }
        else if (rL == hold)
        {
            cout << "I really don't think the ceiling is the most interesting "
            << "part of this room\n";
        }
        else if (rL == quarters or rL == galley)
        {
            cout << "There is a wooden ceiling inches above your face.\n";
        }
        else if (rL == wheel or rL == uDeck)
        {
            cout << "There are sails above you.\n";
        }
        else if (rL == lDeck)
        {
            cout << "There is a ladder leading up to the upper deck.\n";
        }
        else if (rL == brig)
        {
            cout << "There is a trapdoor above you. It didn't close on you, if "
            << "that's what you're worried about.\n";
        }
    }
    else if (objLook == "down")
    {
        if (rL == island)
        {
            cout << "You are standing on sand. Good luck getting that out of "
            << "your shoes.\n";
        }
        else if (rL == banana_tree)
        {
            cout << "There is fertile soil here. Perfect for growing bananas."
            << endl;
        }
        else if (rL == uDeck)
        {
            cout << "There is a ladder down to the lower deck. You can't see "
            << "in from here.\n";
        }
        else if (rL == lDeck)
        {
            cout << "There is a trapdoor below you.\n";
        }
        else if (rL == wheel or rL == galley or rL == quarters or rL == brig)
        {
            cout << "The floor here is made up of sturdy wooden boards.\n";
        }
        else if (rL == hold)
        {
            cout << "The floor is littered with various tools and coins.\n";
            // The tools and coins are glued to the floor as a practical joke
        }
    }
    else if (objLook == "gorilla")
    {
        if (rL == wheel and cInfo.GAVE_BANANA == false)
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
        if (inventoryContains(cInfo.item, "knife") or rL == quarters)
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
        else if (rL == banana_tree)
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
        else if (rL == hold)
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
        if (rL == quarters or rL == galley or rL == hold)
        {
            cout << "I'll be honest with you, there's nothing that special "
            << "about the " << objLook << ".\n";
        }
        else if (rL == lDeck)
        {
            cout << "There are two " << objLook << "s, one to the north and one"
            << " to the south.\n";
        }
        else if (rL == brig)
        {
            if (cInfo.OPENED_CELL)
            {
                cout << "The cell door is open.\n";
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
        if (rL == brig)
        {
            if (cInfo.OPENED_CELL)
            {
                cout << "The cell door is open.\n";
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
        if (rL == hold)
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
        if (rL == galley)
        {
            if (cInfo.GOT_KEY_EARLY)
            {
                cout << "The parrot left because you didn't say hi to him. I "
                << "hope you're happy.\n";
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
        if (rL == island)
        {
            cout << "There is a large ship to your south. Something about it "
            << "seems familiar, but you can't quite place it... Have you seen "
            << "this ship before?\n";
        }
        else if (rL == banana_tree)
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
        if (cInfo.SAID_KEYWORD and rL == quarters)
        {
            cout << "The key was under the captain's bed, just like the parrot "
            << "said it would be.\n";
        }
        else
        {
            cout << "There are no keys here.\n";
        }
    }
    else if (objLook == "ladder")
    {
        if (rL == uDeck)
        {
            cout << "There is a ladder going down to the lower deck.\n";
        }
        else if (rL == lDeck)
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
        if (rL == banana_tree)
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
        else if (rL == island)
        {
            cout << "The trees around you have green bananas on them. Probably "
            << "best to leave them alone.\n";
        }
        else
        {
            cout << "There are no trees nearby.\n";
        }
    }
    else if (objLook == "trapdoor")
    {
        if (rL == lDeck)
        {
            cout << "The trapdoor at your feet leads below.\n";
        }
        else if (rL == brig)
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
void goToLoc(CharInfo cInfo, locInfo lInfo[], string locToGo)
{
    Location rL = cInfo.playerLocation.rawLoc;
    if (locToGo == "island")
    {
        if (rL == uDeck)
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
    else if (drctn == "up" or drctn == "u")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.up);
    }
    else if (drctn == "down" or drctn == "d")
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
    for (int i = 0; i <= MAX_ITEMS_CARRIED; i++)
    {
        if (inventory[i] == item)
        {
            return true;
        }
    }
    return false;
}

// Copyright 2020 Greg Jamison's 2020 Spring CSCI 40 Class

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


