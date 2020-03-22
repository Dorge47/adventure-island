#include <iostream>
#include <string>
using namespace std;
const int MAX_ITEMS_CARRIED=3;
enum location {quarters,hold,galley,brig,wheel,tree,uDeck,lDeck,gPlank,island
,no_room};
struct character{
    int itemsAmnt;
    string item[MAX_ITEMS_CARRIED];
    location charLocation;
};
void CaptiansQuarters();
void CargoHold();
void Galley();
void Brig();
int ShipsWheel();
void BananaTree();
void UpperDeck();
void LowerDeck();
void Gangplank();
void Island();
void ProcessCommand();
int Navigate(string);


int main()
{
    character player;
    player.charLocation = island;
    bool WIN_GAME, HAS_BANANA, SAID_KEYWORD, GAVE_TREASURE, HAS_KEY, HAS_KNIFE;
    int x;
    cout<<"You have just awakened on a strange island with a terrible headache."
	<<" You can't remember anything about yourself or where you are.\n";
    Island();


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
void CaptiansQuarters()
/*the function in which all of the player's interaction with the
CaptiansQuarters will happen.*/
    {
        
    }
void CargoHold()
/*the function in which all of the player's interaction with the
CargoHold will happen.*/
    {
        
    }
void Galley()
/*the function in which all of the player's interaction with the
Galley will happen.*/
    {
        
    }
void Brig()
/*the function in which all of the player's interaction with the
Brig will happen.*/
    {
        
    }
int ShipsWheel()
/*the function in which all of the player's interaction with the
ShipsWheel will happen.*/
    {
        
        return 0;
    }
void BananaTree()
/*the function in which all of the player's interaction with the
BananaTree will happen.*/
    {
        cout<<"There is a large banana tree here. (There is one bunch of ripe"
		<<" bananas on the tree within reach.)\n";
    }
void UpperDeck()
/*the function in which all of the player's interaction with the
UpperDeck will happen.*/
{
    
}
void LowerDeck()
/*the function in which all of the player's interaction with the
LowerDeck will happen.*/
{
    
}
void Gangplank()
/*the function in which all of the player's interaction with the
Gangplank will happen.*/
{
    
}
void Island()
/*the function in which all of the player's interaction with the
Island will happen.*/
{
    ProcessCommand();
}
void ProcessCommand()
// Separates the command into two strings: word_one and word_two
{
    string commands, word_one, word_two;
    int spaceholder;
    getline(cin, commands);
    spaceholder = commands.find(" ");
    word_one = commands.substr(0,spaceholder);
    word_two = commands.substr(spaceholder+1);
    if (word_one == "go" or word_one == "move")
    {
        Navigate(word_two);
    }
}
int Navigate(string direction)
{
    if (direction == "north" or direction == "n")
    {
        return 0;
    }
    else if (direction == "east" or direction == "e")
    {
        return 1;
    }
    else if (direction == "south" or direction == "s")
    {
        return 2;
    }
    else if (direction == "west" or direction == "w")
    {
        return 3;
    }
    else if (direction == "up" or direction == "u")
    {
        return 4;
    }
    else if (direction == "down" or direction == "d")
    {
        return 5;
    }
    else
    {
        cout<<"Invalid direction. Please enter a cardinal direction, \"up\", or"
        <<" \"down\".\n";
        getline(cin, direction);
        return navigate(direction);
    }
}
void moveTo(location nextLoc)
{
    switch (nextLoc) {
        case 0:
            CaptainsQuarters();
            break;
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            
            break;
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
