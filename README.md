# Fantasy Fighter

A top-down, turn-based, role-playing, fighting game created for Ludem Dare 41!

This game requires SFML to compile and play. On Ubuntu and Linux Mint, you can
install SFML using,
```
$ sudo apt install libsfml-dev
```
You can then compile the code with the command
```
$ g++ main.cpp -o application -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
Then running the application script will start the game.
The game hasn't yet been tested when not compiled from source.

# TODO
1. Lock character motion to the center of each square [completed]
	- Give ability to move both character and enemy  
2. Have turns for character and enemy
3. Add logic to enemy
4. Add Combat actions to Character and Enemy
5. Tie Character and enemy to profiles for increasing experience and health
6. Add screen/portal to gain additional powers
7. ...
 - Add obstacles

# Combat Mechanics
Three levels of space: Normal, Croutch, and Jump
You can light or Heavy attack normal, low, or high
High attacks hit high and normal, while low attacks hit low and normal
High attacks are the default attack height
Blocks block all heights of attack; but do not affect heavy attacks
Speed of actions: Light - 1 turn, Heavy - 2 turns, Jump takes 1 turn and lasts 2 turns, 
	croutch takes 1 turn and negates motion, Block - 1 turn and negates motion
With any action, except block and croutch, you can also move to another square
Heavy attack direction can be changed until it is unleased


# Mechanics

-
-
-