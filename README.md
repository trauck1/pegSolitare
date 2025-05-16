Peg Solitaire Game Implementation

CMSC 341 - Fall 2024 - Project 0

This project implements the classic Peg Solitaire game in C++, supporting both Diamond and English board layouts.
Overview
Peg Solitaire is a classic single-player board game where the objective is to remove as 
many marbles (or pegs) as possible from the board by making valid moves. A valid move consists 
of jumping one marble over another adjacent marble into an empty hole, removing the jumped-over marble from the board.
Features

Two different board layouts:

Diamond Board: A diamond-shaped board with 41 initial marbles
English Board: A cross-shaped board with 32 initial marbles


Game mechanics:

Marble jumping and removal
Board state tracking
Move validation


Game utilities:

Board visualization
Marble count reporting
Board type switching




How to Play

Create a Solitaire object with either the DIAMOND or ENGLISH board shape
Use the play() method to make moves
A move requires:

Origin coordinates (where the marble is)
Destination coordinates (where you want to move it)


The move is only valid if:

The origin has a marble
The destination has a hole
There is a marble in between them (which will be removed)
The move is horizontal or vertical (no diagonal moves)
The destination is exactly 2 spaces away from the origin
