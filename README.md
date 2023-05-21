# Virtual World Simulation in c++
Simulation of virtual world implemented in c++. Contains multiple organism such as animals and plants. 
World is represented as set of tiles; one tile stands for given organism. Organism can interact with each other following specified rules. 
They can eat, fight, die and reproduce. Simulation is tour-based with console output

## Table of contests
 * [General Information](#General-information)
 * [Status](#Status)
 * [Compiler Information](#Compiler-Information)
 * [Simulation Rules](#Simulation-Rules)
 * [How it's buided](#How-it's-buided)
 * [Controls](#File-Information)
 * [File Information](#Author)
 * [Author](#Author)
 
## General Information
This project was created for a college subject: objected oriented programming at Gdańsk University of technology.
This version is made entirely in c++ with console ASCII output and requires keybord for input. I also have another 
made entirely in Java

## Status
Right now this repository is all finished and won't be further modified.

## Compiler Information
 * gcc (Rev10, Built by MSYS2 project) 11.2.0
 * Copyright (C) 2021 Free Software Foundation, Inc.

## Simulation rules:
The goal of the project implementation of a simple virtual world simulator, which have the character of a two-dimensional grid
with dimensions NxN (default size is 20x20). In this world, there are simple life forms with different behaviors. 
Each organism occupies exactly one cell in the grid, and each cell can contain at most one organism (in case of a collision, 
one of them is removed or moved).

The simulator have a turn-based nature. In each turn, all existing organisms in the world performs an action 
appropriate to their type. Some of them will move (animal organisms), while others will remain stationary (plant organisms). 
In the case of a collision (when one organism occupies the same cell as another), one organism prevails by killing (e.g., a wolf)
or repelling (e.g., a turtle) the competitor. The order of organism movements in a turn depends on their initiative. 
Animals with the highest initiative move first. In the case of animals with the same initiative, the principle of seniority 
decides the order (the longer-living one moves first). The outcome of an encounter depends on the strength of the organism,
although there will be exceptions to this rule (see: Table 1). In the case of equal strength, the attacking organism prevails.

Upon launching the program, the board displays several animals and plants assigned to the student. 
The program window containa a field where information about the results of battles, plant consumption, and other events 
occurring in the world are displayed.

#### Table1: ==Animals==
| Id | Animal   | Strength | Initiative | Action Method Specifics                                                                      | Collision Method Specifics                                                                                          |
|----|----------|----------|------------|---------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|
| 1  | Wolf     | 9        | 5          | None                                                                                        | None                                                                                                                |
| 2  | Sheep    | 4        | 4          | None                                                                                        | None                                                                                                                |
| 3  | Fox      | 3        | 7          | Good sense of smell: The fox never moves to a cell occupied by a stronger organism          | None                                                                                                                |
| 4  | Snake    | 2        | 3          | None                                                                                        | Dies in collision with a stronger opponent but poisons and kills its slayer                                          |
| 5  | Turtle   | 2        | 1          | In 75% of cases, it doesn't change its position.                                            | Repels attacks from animals with strength < 5. The attacker must return to its previous cell.                      |
| 6  | Snail    | 1        | 1          | In 90% of cases, it doesn't change its position.                                            | Insensitive to attacks from animals with strength < 2. Has a 60% chance of going unnoticed by animals with strength > 4. In both cases, the attacker moves to an unoccupied cell. |
| 7  | Antelope | 4        | 4          | Movement range is 2 cells.                                                                  | 50% chance of escaping from a fight. If successful, it moves to an unoccupied neighboring cell.                    |
| 8  | Hedgehog | 2        | 3          | None                                                                                        | When killed, inflicts such severe injuries on its slayer that it cannot move for the next two turns.                |
| 9  | Lion     | 11       | 7          | None                                                                                        | The king of the animals: No animal with strength < 5 dares to enter a cell occupied by a lion.                      |
| 10 | Mouse    | 1        | 6          | None                                                                                        | Can escape to an adjacent unoccupied cell if available. Doesn't work if the enemy is a snake.                       |
| 11 | Mosquito | 1        | 1          | +1 to initiative and +1 to strength for each adjacent mosquito                              | If defeated, has a 50% chance of survival (returns to the previous cell).                                           |
| 12 | Sloth    | 2        | 1          | Never moves twice in a row in consecutive turns                                             | None                                                                                                                |
#### Table2:  ==Plants==
| Plant       | Strength | Action Method Specifics                                                                      | Collision Method Specifics                                                                                          |
|-------------|----------|---------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|
| Grass       | 0        | None                                                                                        | None                                                                                                                |
| Dandelion   | 0        | Attempts to spread three times in one turn                                                   | None                                                                                                                |
| Nettle      | 0        | None                                                                                        | The animal that eats this plant gets an extra move in the next turn.                                               |
| Guaraná     | 0        | None                                                                                        | Increases the strength of the animal that eats it by 3.                                                             |
| Deadly Nightshade | 0  | None                                                                                        | The animal that eats this plant dies.                                                                               |
| Thistle     | 2        | Attempts to spread always succeed                                                            | None                                                                                                                |


## How it's builded

I've created a class called "World" that contains a dynamin two-dimensional array of references to objects of the "Organism" class. 
Implemented the course of a turn by invoking the "action()" method for all organisms and the "collision()" method for organisms in the same field. 
Organisms have the ability to affect the state of the world. I've ensured that the "World" class defines only those fields and methods as public 
members that are necessary for other application objects to function. Encapsulated the remaining functionality of the world within private members.

## Controls
Press `enter` in order to simulate a turn. Simulation starts with organism initialized manually in worl class metho. Fell free to change them.

## File Information
main.cpp contains main function, canva files contains way of displaying 2d board to the screen. 

## Author
> + _Created by Miłosz Skobejko_
> + _Published on github 9.03.2023_
> + _currect version: v0.0_

> Created in Atom text editor, later on moved to Xcode editor
