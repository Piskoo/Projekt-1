#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
	
	
const int TabWidth = 25; // Board width
const int TabHeight = 25; // Board height
std::string GameTab[TabWidth][TabHeight]; //Definion of array that will contain game elements
int SnakePointWidth;
int SnakePointHeight;
int FoodTabWidth;
int FoodTabHeight;


int main() 
{

	// Main game board

	for (int i = 0; i < TabWidth; i++) { // Top border
		std::cout << "--";
	}

	for (int i = 0; i < TabHeight; i++) { // Left border
		std::cout << std::endl << "||";
		for (int j = 0; j < TabWidth-2; j++) { // Space between borders - play field
			std::cout << "  ";
		}
		std::cout << "||"; // Right border
	}
	std::cout << std::endl;
	for (int i = 0; i < TabWidth; i++) { // Bottom border
		std::cout << "--";
	}

	// Game fields 'logical' definitions

	// Empty fields

	for (int i = 0; i < TabWidth; i++) { // Filling array with empty fields
		for (int j = 0; j < TabHeight; j++){
			GameTab[i][j] = "empty"; // Filling with word 'empty'
		}
	}

	// Snake start point

	SnakePointWidth = TabWidth / 2 + 0.5; // Middle
	SnakePointHeight = TabHeight / 2 + 0.5; // Middle
	GameTab[SnakePointWidth][SnakePointHeight] = "snake"; // Filling snake start point with word 'snake'

	// Food location

	srand(time(NULL)); // True RNG

	FoodTabWidth = rand() % TabWidth; // Randomized table width
	FoodTabHeight = rand() % TabHeight; // Randomized table height
	GameTab[SnakePointWidth][SnakePointHeight] = "food"; // Filling one field with word 'food'




	_getch();

    return 0;
}

