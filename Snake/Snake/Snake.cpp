#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <cmath>
	
// Anti-flickering script - Carriage return //

void Carriage(int y, int x) {
	HANDLE hCon;
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

const int TabWidth = 25; // Board width //
const int TabHeight = 25; // Board height //
std::string GameTab[TabHeight][TabWidth]; //Definion of array that will contain game elements //
int SnakePointHeight; // Snake height coordinate //
int SnakePointWidth; // Snake width coordinate //
int FoodTabHeight; // Food height coordinate //
int FoodTabWidth; // Food width coordinate //
int button; // Controls //
char direction = 'd'; // Snake direction; w - up, s - down, a - left, d - right(default) //
int SnakeMoves = 0; // Amount of moves that snake do during the game //
int SnakeLength = 2; // Base snake length //
int OldSnakeHeight[5000]; // Previous moves //
int OldSnakeWidth[5000]; // Previous moves //
int GameDifficulty = 2; // Game difficulty //
int GameSpeed = 300;
float Score = 0;

// Game Visuals // 

char SnakeCode = 219;
char LeftRightBorder = 186;
char TopBottomBorder = 205;
char TopLeftCorner = 201;
char TopRightCorner = 187;
char BottomLeftCorner = 200;
char BottomRightCorner = 188;
char FoodCode = 175;

int main() 
{
	
	// How to control snake instructions //

	std::cout << "Controls:" << std::endl << "w - up" << std::endl << "s - down" << std::endl << "a - left" << std::endl << "d - right" << std::endl;
	std::cout << std::endl << "Press any key to continue...";
	_getch();
	system("cls");

	// Game difficulty //

	std::cout << "Choose game difficulty (1 - easy, 2 - normal, 3 - hard, 4 - insane)" << std::endl << "Difficulty score multipliers:" << std::endl << "0.5x - easy" << std::endl << "1.0x - normal" << std::endl << "1.5x - hard" << std::endl << "2.0x - insane" << std::endl;
	GameDifficulty = _getch(); 
	if (GameDifficulty == '1') GameSpeed = 300; // Setting sleep value for each of the difficulties //
	else if (GameDifficulty == '2') GameSpeed = 200;
	else if (GameDifficulty == '3') GameSpeed = 100;
	else if (GameDifficulty == '4') GameSpeed = 50;
	else if (GameDifficulty != '1' || GameDifficulty != '2' || GameDifficulty != '3' || GameDifficulty != '4') {
		GameDifficulty = '2';
	}

	// Start when you're ready //

	system("cls");
	std::cout << "Press any key to start...";
	_getch();
	system("cls");


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

	Carriage(0, 0);

	// Main game board //

	std::cout << TopLeftCorner;
	for (int i = 0; i < TabWidth; i++) { // Top border //
		std::cout << TopBottomBorder << TopBottomBorder;
	}
	std::cout << TopRightCorner;

	for (int i = 0; i < TabHeight; i++) { // Left border //
		std::cout << std::endl << LeftRightBorder;
		for (int j = 0; j < TabWidth; j++) { // Space between borders - play field //
			if (GameTab[i][j] == "empty") std::cout << "  "; // Filling board with empty spaces //
			if (GameTab[i][j] == "snake") std::cout << SnakeCode << SnakeCode; // Filling board with snake fields //
			if (GameTab[i][j] == "food") std::cout << "@" << FoodCode; // Filling board with food field //

		}
		std::cout << LeftRightBorder; // Right border //
	}
	std::cout << std::endl;
	std::cout << BottomLeftCorner;
	for (int i = 0; i < TabWidth; i++) { // Bottom border //
		std::cout << TopBottomBorder << TopBottomBorder;
	}
	std::cout << BottomRightCorner;

	for (;;) {
		
		// Snake length //

		SnakeMoves++; // Amount of moves that snake do //
		OldSnakeHeight[SnakeMoves] = SnakePointHeight; // History of moves height coordinate // 
		OldSnakeWidth[SnakeMoves] = SnakePointWidth; // History of moves width coordinate // 

		// Eating //

		if (GameTab[SnakePointHeight][SnakePointWidth] == GameTab[FoodTabHeight][FoodTabWidth]) {
			SnakeLength++;
			do {
				FoodTabHeight = rand() % (TabHeight - 2) + 1; // Randomize food height location from 1 to TabHeight-2 //
				FoodTabWidth = rand() % (TabWidth - 2) + 1; // Randomize food width location from 1 to TabWidth-2 //
			} while (GameTab[FoodTabHeight][FoodTabWidth] != "empty"); // Cannot roll same height and width as snake //

			GameTab[FoodTabHeight][FoodTabWidth] = "food"; // Filling one field with word 'food' //
			Carriage(FoodTabHeight + 1, FoodTabWidth * 2 + 1); // Overwrite old values with food //
			std::cout << "@" << FoodCode;
			
		}

		GameTab[SnakePointHeight][SnakePointWidth] = "snake"; // First segment of snake, it's head //
		Carriage(SnakePointHeight + 1, SnakePointWidth * 2 + 1); // Overwrite old values with snake //
		std::cout << SnakeCode << SnakeCode;

		GameTab[OldSnakeHeight[SnakeMoves - SnakeLength]][OldSnakeWidth[SnakeMoves - SnakeLength]] = "empty"; // Old coordinates should be empty when snake moves //
		Carriage(OldSnakeHeight[SnakeMoves - SnakeLength] + 1, OldSnakeWidth[SnakeMoves - SnakeLength] * 2 + 1); // Overwrite old values with double empty space //
		std::cout << "  ";

		Sleep(GameSpeed);

		// Controls //

		if (_kbhit()) {
			button = _getch();

			if (button == 119 && (direction == 'a' || direction == 'd')) direction = 'w'; // If player hit 'w' then snake direction will be up //
			if (button == 115 && (direction == 'a' || direction == 'd')) direction = 's'; // If player hit 's' then snake direction will be down //
			if (button == 97 && (direction == 'w' || direction == 's')) direction = 'a'; // If player hit 'a' then snake direction will be left //
			if (button == 100 && (direction == 'w' || direction == 's')) direction = 'd'; // If player hit 'd' then snake direction will be right //
		}

		// Snake shift //

		if (direction == 'w') SnakePointHeight--;
		if (direction == 's') SnakePointHeight++;
		if (direction == 'a') SnakePointWidth--;
		if (direction == 'd') SnakePointWidth++;

		// Game over rules //

		if (SnakePointWidth == TabWidth) break; // Right border //
		if (SnakePointWidth == -1) break; // Left border //
		if (SnakePointHeight == TabHeight) break; // Bottom border //
		if (SnakePointHeight == -1) break; // Top border //
		if (GameTab[SnakePointHeight][SnakePointWidth] == "snake") break; // Eats itself // 

	}

	// Game over messages //

	Carriage(TabHeight - 13, TabWidth - 3);
	std::cout << "GAME OVER";
	Carriage(TabHeight - 12, TabWidth - 1);
	std::cout << "SCORE";

	// Score multipliers //

	if (GameDifficulty == '1')
		Score = SnakeLength * 0.5;
	if (GameDifficulty == '2')
		Score = SnakeLength;
	if (GameDifficulty == '3')
		Score = SnakeLength * 1.5;
	if (GameDifficulty == '4')
		Score = SnakeLength * 2;

	// Different carriage locations if score is decimal fraction //

	if (fmod(Score,1) == 0)
		Carriage(TabHeight - 11, TabWidth + 1);
	else
		Carriage(TabHeight - 11, TabWidth);
	std::cout << Score;
	Carriage(TabHeight + 1, 0);

	_getch();

	// Anti 'close game by accident' //

	Sleep(500);
	_getch();

    return 0;
}

