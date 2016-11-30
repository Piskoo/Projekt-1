#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
	
	
const int TabWidth = 25; // Board width
const int TabHeight = 25; // Board height
std::string GameTab[TabWidth][TabHeight]; //Definion of array that will contain game elements
int SnakePointWidth; //
int SnakePointHeight;
int FoodTabWidth;
int FoodTabHeight;


int main() 
{

		// Game fields 'logical' definitions

		// Empty fields

		for (int i = 0; i < TabWidth; i++) { // Filling array with empty fields
			for (int j = 0; j < TabHeight; j++) {
				GameTab[i][j] = "empty"; // Filling with word 'empty'
			}
		}

		// Snake start point

		SnakePointWidth = TabWidth - 13; // Middle
		SnakePointHeight = TabHeight - 13; // Middle
		GameTab[SnakePointWidth][SnakePointHeight] = "snake"; // Filling snake start point with word 'snake'

		// Food location

		srand(time(NULL)); // True RNG

		do {
			FoodTabWidth = rand() % (TabWidth - 2) + 1; // Randomize food width location from 1 to TabWidth-2
			FoodTabHeight = rand() % (TabHeight - 2) + 1; // Randomize food height location from 1 to TabHeight-2
		} while (GameTab[FoodTabWidth][FoodTabHeight] != "empty"); // Cannot roll same width and height as snake

		GameTab[FoodTabWidth][FoodTabHeight] = "food"; // Filling one field with word 'food'

		for (;;) {

			system("CLS");

		// Main game board

		for (int i = 0; i < TabWidth; i++) { // Top border
			std::cout << "--";
		}

		for (int i = 0; i < TabHeight; i++) { // Left border
			std::cout << std::endl << "||";
			for (int j = 0; j < TabWidth - 2; j++) { // Space between borders - play field
				if (GameTab[i][j] == "empty") std::cout << "  "; // Filling board with empty spaces
				if (GameTab[i][j] == "snake") std::cout << "@@"; // Filling board with snake fields
				if (GameTab[i][j] == "food") std::cout << "XX"; // Filling board with food field

			}
			std::cout << "||"; // Right border
		}
		std::cout << std::endl;
		for (int i = 0; i < TabWidth; i++) { // Bottom border
			std::cout << "--";
		}
		Sleep(500);
	}





	_getch();

    return 0;
}

