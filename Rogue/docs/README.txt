****************************************************
Filip Hasson		0878596
CIS2500			Assignment 3 Rouge
01/16/2015
****************************************************

************
Compilation
************
	gcc -Wall -pedantic -std=c99 ./src/main.c ./src/parse.c ./src/drawGame.c ./src/debug.c ./src/preGame.c ./src/gameplay.c ./src/inventory.c -Iinclude -lncurses -lm -o ./bun/runMe

***********************
Running the program(s)
***********************
	./bin/runMe <filePath> <flags>

Possible flags:
-p displays parse output
-b1,-b2,-b3 displays different levels of borders when drawing
-d dumps the stored data in text and csv documents
-h displays hallway information as its being drawn for debugging

*****************
Known Limitations
*****************
Cannot enter more than 150 characters per line in the input file
Each rooms size must be included
If there is a stray character that is not one of the defined characters is entered without being followed by a location, the program will segfault

********
Controls
********


*****************
Testing Done
*****************
See Running the Program, possible flahs
See testing.txt


****************
Bonus Objectives
****************
MAIN:
-Flags added to command line running for debugging
PARSING:
-(py,x) Becomes one of 8 randomly generated potions, of strength or health, that are usable ingame

	NAME:				Hp Healed
	Minor Health Potion		10
	Lesser Health Potion		15
	Greater Health Potion		20
	Major Health Potion		40
					Strength Boost	Duration (moves)
	Minor Potion of Strength	5		20
	Lesser Potion of Strength	10		40
	Potion of Strength		15		60
	Greater Potion of Strength	25		80 

-(my,x) Becomes one of 8 randomly generated magic enchantments of strength or health that permenantly augment hero stats

	NAME:				HP Increased
	Minor Health Enchant		5
	Lesser Health Enchant		10
	Greater Health Enchant		16
	Major Health Enchant		22
					Strength Increased
	Minor Strength Enchant		2
	Lesser Strength Enchant		4
	Strength Enchant		7
	Major Strength Enchant		10

-(My,x) Becomes one of 6 randomly generated monsters with unique scaling, health and damage

	NAME:		Health		Damage
	Snake		15		3
	Bat		20		4
	Giant Rat	25		5
	Goblin		30		9
	Orc		50		15
	Corrupt Elf	90		30
	
-(wy,x) Becomes one of 45 different equipable weapons each with their own stats to improve hero damage
	Weapons carry a type and a material, the type has a base damage, multiplied by the material, the name is <Material> <Type>
	
	TYPE:		BaseDamage	MATERIAL:	Multiplier:	
	Dagger		1		Iron		1		
	Short Sword	2		Steel		2		
	Long Sword	4		Silver		3		
	Claymore	5		Orcish		4
	War Axe		3		Elvish		5
	Battle Axe	5
	Mace		3
	War Hammer	5
	Spear		4

a breakdown of these items/monsters being generated can be printed with the -p flag

DRAWING:
-All 6 rooms have their location randomized within their 6th of the game board, as rooms must appear 2x3
	These borders can be seen with the -b2 or -b3 flag
-Algorithm connects each door to its closest unpaired door
-Algorithm to craw hallways between each pair of doors
-Algorithm to ensure all rooms are still conected regardless of number of doors/door pairs

INVENTORY:
-The inventory can be view with the <I> key
	The inventory has 4 sub menus
	-Gold
	-Weapons
	-Potions
	-Magic
	Each submenu displays all items currently collected, and can be navigated with WASD
-Weapons in the inventory submenu can be equipped with the <E> key augmenting the players damage
-Potions in the inventory submenu can be used with the <E> key providing the advertized stat boost
-Magic Enchantments in the inventory submenu can be used with the <E> key providing the advertized permenant stat augmentation

GAMEPLAY:
-Combat implemented when player attempts to move onto a tile that is occupied by a monster, messages tell the player details of the fight
-Player has a level, and levels up while fighting mosnters, leveling up naturally increases their stats
-Player has a health bar that is displayed in Green Yellow or Red depending on the % of their health remaining

MONSTERS:
-Six different types of monsters displayed by (S, B, R, G, O, E)
-Each monster has its own movement pattern (or lack there of in the snakes case)
