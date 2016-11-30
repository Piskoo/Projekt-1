#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
	
	
const int TabWidth = 25; // Board width //
const int TabHeight = 25; // Board height //
std::string GameTab[TabHeight][TabWidth]; //Definion of array that will contain game elements //
int SnakePointHeight; // Snake height coordinate //
int SnakePointWidth; // Snake width coordinate //
int FoodTabHeight; // Food height coordinate //
int FoodTabWidth; // Food width coordinate //
int button; // Controls //
char direction = 'd'; // Snake direction; w - up, s - down, a - left, d - right //
int SnakeMoves = 0; // Amount of moves that snake do during the game //
int SnakeLength = 5; // Base snake length //
int OldSnakeHeight[5000]; // Previous moves //
int OldSnakeWidth[5000]; // Previous moves //


int main() 
{

	// Game fields 'logical' definitions //

	// Empty fields //

	for (int i = 0; i < TabHeight; i++) { // Filling array with empty fields //
		for (int j = 0; j < TabWidth; j++) {
			GameTab[i][j] = "empty"; // Filling with word 'empty' //
		}
	}

	// Snake start point //

	SnakePointHeight = TabHeight - 13; // Middle //
	SnakePointWidth = TabWidth - 13; // Middle //
	GameTab[SnakePointHeight][SnakePointWidth] = "snake"; // Filling snake start point with word 'snake' //


	// Food location //

	srand(time(NULL)); // True RNG //

	do {
		FoodTabHeight = rand() % (TabHeight - 2) + 1; // Randomize food height location from 1 to TabHeight-2 //
		FoodTabWidth = rand() % (TabWidth - 2) + 1; // Randomize food width location from 1 to TabWidth-2 //
	} while (GameTab[FoodTabHeight][FoodTabWidth] != "empty"); // Cannot roll same height and width as snake //

	GameTab[FoodTabHeight][FoodTabWidth] = "food"; // Filling one field with word 'food' //


	for (;;) {
		
		// Snake length //

		SnakeMoves++; // Amount of moves that snake do //
		OldSnakeHeight[SnakeMoves] = SnakePointHeight; // History of moves height coordinate // 
		OldSnakeWidth[SnakeMoves] = SnakePointWidth; // History of moves width coordinate // 

		// Endgame rules //

		if (SnakePointWidth == TabWidth) break; // Right border //
		if (SnakePointWidth == -1) break; // Left border //
		if (SnakePointHeight == TabHeight) break; // Bottom border //
		if (SnakePointHeight == -1) break; // Top border //

		GameTab[SnakePointHeight][SnakePointWidth] = "snake"; // First segment of snake, it's head //

		GameTab[OldSnakeHeight[SnakeMoves - SnakeLength]][OldSnakeWidth[SnakeMoves - SnakeLength]] = "empty"; // Old coordinates should be empty when snake moves //

		system("CLS");


		// Main game board //

		for (int i = 0; i < TabWidth+1; i++) { // Top border //
			std::cout << "--";
		}

		for (int i = 0; i < TabHeight; i++) { // Left border //
			std::cout << std::endl << "|";
			for (int j = 0; j < TabWidth; j++) { // Space between borders - play field //
				if (GameTab[i][j] == "empty") std::cout << "  "; // Filling board with empty spaces //
				if (GameTab[i][j] == "snake") std::cout << "@@"; // Filling board with snake fields //
				if (GameTab[i][j] == "food") std::cout << "XX"; // Filling board with food field //

			}
			std::cout << "|"; // Right border //
		}
		std::cout << std::endl;
		for (int i = 0; i < TabWidth+1; i++) { // Bottom border //
			std::cout << "--";
		}

		Sleep(500);

		// Controls //

		if (_kbhit()) {
			button = _getch();

			if (button == 119) direction = 'w';
			if (button == 115) direction = 's';
			if (button == 97) direction = 'a';
			if (button == 100) direction = 'd';
		}

		if (direction == 'w') SnakePointHeight--;
		if (direction == 's') SnakePointHeight++;
		if (direction == 'a') SnakePointWidth--;
		if (direction == 'd') SnakePointWidth++;

	}

	_getch();

    return 0;
}

