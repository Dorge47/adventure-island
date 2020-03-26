#include <iostream>
#include <string>
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
};
void setRoom(CharInfo, locInfo[]);
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
void goToLoc(int);


int main()
{
    CharInfo cInfo;
    locInfo room[no_room];
    bool WIN_GAME, HAS_BANANA, SAID_KEYWORD, GAVE_TREASURE, HAS_KEY, HAS_KNIFE;
    int x;
    cout<<"What is your name?\n";
    getline(cin,cInfo.name);
    cout<<"You have just awakened on a strange island with a terrible headache."
    <<" You can't remember anything about yourself or where you are.\n";
    setRoom(cInfo, room);
    Island(cInfo, room);


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
void setRoom(CharInfo cInfo, locInfo lInfo[]){
    lInfo[island].name = "island";
    lInfo[island].rawLoc = island;
    lInfo[island].description = "The island is forested with banana trees. Most of the bananas are green, but one tree to your north might have ripe bananas. There are ominous drums in the background. There is a ship to your south with a gangplank to the shore.\n";
    lInfo[island].nextRoom.north = "banana_tree";
    lInfo[island].nextRoom.south = "uDeck";
    lInfo[island].nextRoom.east = "no_room";
    lInfo[island].nextRoom.west = "no_room";
    lInfo[island].nextRoom.up = "no_room";
    lInfo[island].nextRoom.down = "no_room";
    lInfo[banana_tree].name = "banana_tree";
    lInfo[banana_tree].rawLoc = banana_tree;
    lInfo[banana_tree].description = "There is a large banana tree here.\n";
    lInfo[banana_tree].nextRoom.north = "no_room";
    lInfo[banana_tree].nextRoom.south = "island";
    lInfo[banana_tree].nextRoom.east = "no_room";
    lInfo[banana_tree].nextRoom.west = "no_room";
    lInfo[banana_tree].nextRoom.up = "no_room";
    lInfo[banana_tree].nextRoom.down = "no_room";
    lInfo[uDeck].name = "uDeck";
    lInfo[uDeck].rawLoc = uDeck;
    lInfo[uDeck].description = "The top deck has a wheel at the east end of the ship, and there is a ladder down to the lower deck.  The captain's quarters are to the west.\n";
    lInfo[uDeck].nextRoom.north = "no_room";
    lInfo[uDeck].nextRoom.south = "no_room";
    lInfo[uDeck].nextRoom.east = "wheel";
    lInfo[uDeck].nextRoom.west = "quarters";
    lInfo[uDeck].nextRoom.up = "no_room";
    lInfo[uDeck].nextRoom.down = "lDeck";
    lInfo[wheel].name = "wheel";
    lInfo[wheel].rawLoc = wheel;
    lInfo[wheel].description = "There is a large gorilla by the ship's wheel.  This gorilla is hostile.  You can't touch the wheel.\n";
    lInfo[wheel].nextRoom.north = "no_room";
    lInfo[wheel].nextRoom.south = "no_room";
    lInfo[wheel].nextRoom.east = "no_room";
    lInfo[wheel].nextRoom.west = "uDeck";
    lInfo[wheel].nextRoom.up = "no_room";
    lInfo[wheel].nextRoom.down = "no_room";
    lInfo[lDeck].name = "lDeck";
    lInfo[lDeck].rawLoc = lDeck;
    lInfo[lDeck].description = "The deck below is dimly lit, and smells musty. You can make out three doors.  One is to the north, one is to the south, and one is a trapdoor below you.\n";
    lInfo[lDeck].nextRoom.north = "hold";
    lInfo[lDeck].nextRoom.south = "galley";
    lInfo[lDeck].nextRoom.east = "no_room";
    lInfo[lDeck].nextRoom.west = "no_room";
    lInfo[lDeck].nextRoom.up = "uDeck";
    lInfo[lDeck].nextRoom.down = "brig";
    lInfo[galley].name = "galley";
    lInfo[galley].rawLoc = galley;
    lInfo[galley].description = "This is the galley.  It is mostly empty, but in a shadowy corner you see a parrot sitting on a perch.\n";
    lInfo[galley].nextRoom.north = "lDeck";
    lInfo[galley].nextRoom.south = "no_room";
    lInfo[galley].nextRoom.east = "no_room";
    lInfo[galley].nextRoom.west = "no_room";
    lInfo[galley].nextRoom.up = "no_room";
    lInfo[galley].nextRoom.down = "no_room";
    lInfo[brig].name = "brig";
    lInfo[brig].rawLoc = brig;
    lInfo[brig].description = "In this room there is a prisoner in a locked cell.  He says, \"";
    lInfo[brig].description += cInfo.name;
    lInfo[brig].description += ", I'm so glad you're alive.  The captain locked me up for cheating at cards, which is the only reason the islanders didn't capture me.  They killed everyone else.  Now I guess we're the only two left, which makes you captain since you were first mate.  Go find the keys to unlock this door, and we can sail out of here.\"\n";
    lInfo[brig].nextRoom.north = "no_room";
    lInfo[brig].nextRoom.south = "no_room";
    lInfo[brig].nextRoom.east = "no_room";
    lInfo[brig].nextRoom.west = "no_room";
    lInfo[brig].nextRoom.up = "lDeck";
    lInfo[brig].nextRoom.down = "no_room";
    lInfo[quarters].name = "quarters";
    lInfo[quarters].rawLoc = quarters;
    lInfo[quarters].description = "These are the captain's quarters.  There is a bed and a table in this room.\n";
    lInfo[quarters].nextRoom.north = "no_room";
    lInfo[quarters].nextRoom.south = "no_room";
    lInfo[quarters].nextRoom.east = "uDeck";
    lInfo[quarters].nextRoom.west = "no_room";
    lInfo[quarters].nextRoom.up = "no_room";
    lInfo[quarters].nextRoom.down = "no_room";
    lInfo[hold].name = "hold";
    lInfo[hold].rawLoc = hold;
    lInfo[hold].description = "You've entered the cargo hold.  There are barrels, a pile of tools, and a trunk.\n";
    lInfo[hold].nextRoom.north = "no_room";
    lInfo[hold].nextRoom.south = "lDeck";
    lInfo[hold].nextRoom.east = "no_room";
    lInfo[hold].nextRoom.west = "no_room";
    lInfo[hold].nextRoom.up = "no_room";
    lInfo[hold].nextRoom.down = "no_room";
}
void CaptainsQuarters(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
CaptainsQuarters will happen.*/
    {
        cInfo.playerLocation = lInfo[quarters];
        cout << cInfo.playerLocation.description;
        ProcessCommand(cInfo, lInfo);
    }
void CargoHold(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
CargoHold will happen.*/
    {
        cInfo.playerLocation = lInfo[hold];
        cout << cInfo.playerLocation.description;
        ProcessCommand(cInfo, lInfo);
    }
void Galley(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
Galley will happen.*/
    {
        cInfo.playerLocation = lInfo[galley];
        cout << cInfo.playerLocation.description;
        ProcessCommand(cInfo, lInfo);
    }
void Brig(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
Brig will happen.*/
    {
        cInfo.playerLocation = lInfo[brig];
        cout << cInfo.playerLocation.description;
        ProcessCommand(cInfo, lInfo);
    }
int ShipsWheel(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
ShipsWheel will happen.*/
    {
        cInfo.playerLocation = lInfo[wheel];
        cout << cInfo.playerLocation.description;
        ProcessCommand(cInfo, lInfo);
        return 0;
    }
void BananaTree(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
BananaTree will happen.*/
    {
        cInfo.playerLocation = lInfo[banana_tree];
        cout << cInfo.playerLocation.description;
        ProcessCommand(cInfo, lInfo);
    }
void UpperDeck(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
UpperDeck will happen.*/
{
    cInfo.playerLocation = lInfo[uDeck];
    cout << cInfo.playerLocation.description;
    ProcessCommand(cInfo, lInfo);
}
void LowerDeck(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
LowerDeck will happen.*/
{
    cInfo.playerLocation = lInfo[lDeck];
    cout << cInfo.playerLocation.description;
    ProcessCommand(cInfo, lInfo);
}
void Island(CharInfo cInfo, locInfo lInfo[])
/*the function in which all of the player's interaction with the
Island will happen.*/
{
    cInfo.playerLocation = lInfo[island];
    cout << cInfo.playerLocation.description;
    ProcessCommand(cInfo, lInfo);
}
void ProcessCommand(CharInfo cInfo, locInfo lInfo[])
// Separates the command into two strings: word_one and word_two
{
    string commands, word_one, word_two;
    int spaceholder;
    bool one_word = false;
    getline(cin, commands);
    spaceholder = commands.find(" ");
    word_one = commands.substr(0,spaceholder);
    word_two = commands.substr(spaceholder+1);
    if (spaceholder == -1)
    {
        one_word = true;
    }
    if (word_one == "go" or word_one == "move")
    {
        Navigate(cInfo, lInfo, word_two);
    }
    else if (word_one == "n" or word_one == "e" or word_one == "s" or word_one
    == "w" or word_one == "north" or word_one == "east" or word_one == "south"
    or word_one == "west")
    {
        Navigate(cInfo, lInfo, word_one);
    }
    else if (word_one == "look")
    {
        if (one_word)
        {
            cout << cInfo.playerLocation.description;
        }
        else
        {
            Look(cInfo, lInfo, word_two);
        }
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
            cout << "You look up to see a clear blue sky. It's a nice day out.";
            cout << endl;
        }
        else if (rL == hold)
        {
            cout << "I really don't think the ceiling is the most interesting ";
            cout << "part of this room\n";
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
            cout << "There is a trapdoor above you. It didn't close on you, if";
            cout << " that's what you're worried about.\n";
        }
    }
}
void goToLoc(CharInfo cInfo, locInfo lInfo[], string locToGo)
{
    if (locToGo == "island")
    {
        Island(cInfo, lInfo);
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
        cout << "There is nothing in that direction.\n";
        ProcessCommand(cInfo, lInfo);
    }
}
void Navigate(CharInfo cInfo, locInfo lInfo[], string direction)
{
    int spaceholder = direction.find(" ");
    if (spaceholder != -1)
    {
        direction = direction.substr(spaceholder+1);
    }
    if (direction == "north" or direction == "n")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.north);
    }
    else if (direction == "east" or direction == "e")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.east);
    }
    else if (direction == "south" or direction == "s")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.south);
    }
    else if (direction == "west" or direction == "w")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.west);
    }
    else if (direction == "up" or direction == "u")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.up);
    }
    else if (direction == "down" or direction == "d")
    {
        goToLoc(cInfo, lInfo, cInfo.playerLocation.nextRoom.down);
    }
    else
    {
        cout<<"Invalid direction. Please enter a cardinal direction, \"up\", or"
        <<" \"down\".\n";
        getline(cin, direction);
        Navigate(cInfo, lInfo, direction);
    }
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


