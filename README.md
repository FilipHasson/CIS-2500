#CIS-2500 Intermediate Programming

Completed this class in the 2nd semester of first year (Winter 2015)
The course focused on C programming and implementing linux terminal based
applications using a Curses library for a user interface.

Assignments
-----------

###1. Obstruction

Played on a 6x6 grid players take turns placing down Xs and Os. 
When a marker is placed all of the surrounding tiles are ubstructed and a marker cannot be placLod in them.
The winner of the game is the last player to succesfully place a marker.
As part of the assignment we needed to implement a basic computer opponent.
In this case the AI simlpy places a marker in the first open tile.

###2. Logo Interpretter

Logo is a programming language based around moving a drawing turtle.
This assignment required us to support basic features of the language in a terminal window.

###3. Rogue

The assignment was based off of the 1980 video game rogue. 
The requirements were to read a text file describing a level containing:
6 rooms on a 3x2 grid, up to 4 doors for each room. locations of monsters(M), magic(m), potions(p), gold(g) and weapons (w).
The player had to be able to move around and collect the items. Interaction with Monsters was not necessary. 
Hallways connecting rooms were not part of the initial assignment,but there had to be some way to traverse room
(ie, doors teleport you to the next room or let you choose).

Optional objectives for the assignment were to: implement hallways, combat, allow monsters to move, have different types of
monsters, have an inventory list the items you picked up.

Additional objectives I undertook were: to make all items usable with at least 8 unique possibilities for the specifics of 
the item Weapon could be Iron Short Sword or Steel Battle-Axe, ect.. Have the inventory be visually appealing and easy to use
and incoprerate a experience/leveling system based off of combat. 
