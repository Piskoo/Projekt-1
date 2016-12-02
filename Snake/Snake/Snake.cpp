#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <cmath>

const int TabWidth = 25; // Board width //
const int TabHeight = 25; // Board height //
std::string GameTab[TabHeight][TabWidth]; //Definion of array that will contain game elements //
int SnakePointHeight; // Snake height coordinate //
int SnakePointWidth; // Snake width coordinate //
int FoodTabHeight; // Food height coordinate //
int FoodTabWidth; // Food width coordinate //
std::string LogicEmpty = "empty"; // GameTab values //
std::string LogicSnake = "snake"; // GameTab values //
std::string LogicFood = "food"; // GameTab values //
int TabMiddleHeight = TabHeight / 2; // Snake starting point - middle //
int TabMiddleWidth = TabWidth / 2; // Snake starting point - middle //
int Button; // Controls //
char WKey = (char)119; // W //
char SKey = (char)115; // S //
char AKey = (char)97; // A //
char DKey = (char)100; // D //
char Direction = 'd'; // Snake direction; w - up, s - down, a - left, d - right(default) //
char UpDirection = 'w'; // Snake direction up //
char DownDirection = 's'; // Snake direction down //
char LeftDirection = 'a'; // Snake direction left //
char RightDirection = 'd'; // Snake direction right //
int SnakeMoves = 0; // Amount of moves that snake do during the game //
int SnakeLength = 2; // Base snake length //
int OldSnakeHeight[5000]; // Previous moves //
int OldSnakeWidth[5000]; // Previous moves //
int GameDifficulty = 2; // Game difficulty //
char EasyDifficulty = '1'; // Easy //
char NormalDifficulty = '2'; // Normal //
char HardDifficulty = '3'; // Hard //
char InsaneDifficulty = '4'; // Insane //
int GameSpeed; // Time in ms that is used in sleep function inside endless loop //
int GameSpeedEasy = 300; // Game speed in easy difficulty //
int GameSpeedNormal = 200; // Game speed in normal difficulty // 
int GameSpeedHard = 100; // Game speed in hard difficulty //
int GameSpeedInsane = 50; // Game speed in insane difficulty //
float Score = 0; // Endgame score, float because of the multipliers //

// Game Visuals // 

char EmptyCode = (char)255;
char SnakeCode = (char)219;
char FoodCodePart1 = (char)64;
char FoodCodePart2 = (char)175;
char LeftRightBorder = (char)186;
char TopBottomBorder = (char)205;
char TopLeftCorner = (char)201;
char TopRightCorner = (char)187;
char BottomLeftCorner = (char)200;
char BottomRightCorner = (char)188;

void Carriage(int y, int x) { // Anti-flickering script - Carriage return //
	HANDLE hCon;
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

void HowToControl() { // How to control snake instructions //
	std::cout << "Controls:" << std::endl << "w - up" << std::endl << "s - down" << std::endl << "a - left" << std::endl << "d - right" << std::endl;
	std::cout << std::endl << "Press any key to continue...";
	_getch();
	system("cls");
}

void Difficulty() { // Game difficulty //
	std::cout << "Choose game difficulty (1 - easy, 2 - normal, 3 - hard, 4 - insane)" << std::endl << "Difficulty score multipliers:" << std::endl << "0.5x - easy" << std::endl << "1.0x - normal" << std::endl << "1.5x - hard" << std::endl << "2.0x - insane" << std::endl;
	GameDifficulty = _getch();
	if (GameDifficulty == EasyDifficulty) GameSpeed = GameSpeedEasy; // Setting refresh rate for each of the difficulties //
	else if (GameDifficulty == NormalDifficulty) GameSpeed = GameSpeedNormal;
	else if (GameDifficulty == HardDifficulty) GameSpeed = GameSpeedHard;
	else if (GameDifficulty == InsaneDifficulty) GameSpeed = GameSpeedInsane;
	else if (GameDifficulty != EasyDifficulty || GameDifficulty != NormalDifficulty || GameDifficulty != HardDifficulty || GameDifficulty != InsaneDifficulty) {
		GameDifficulty = NormalDifficulty;
	}
}

void Ready() { // Start when you're ready //
	system("cls");
	std::cout << "Press any key to start...";
	_getch();
	system("cls");
	std::cout << "Prepare";
	Sleep(2000);
	system("cls");
	std::cout << "3";
	Sleep(1000);
	system("cls");
	std::cout << "2";
	Sleep(1000);
	system("cls");
	std::cout << "1";
	Sleep(1000);
	system("cls");
}

// Game fields 'logical' definitions //

void EmptyTable() { // Empty fields //
	for (int i = 0; i < TabHeight; i++) { // Filling array with empty fields //
		for (int j = 0; j < TabWidth; j++) {
			GameTab[i][j] = LogicEmpty; // Filling with word 'empty' //
		}
	}
}

void SnakeStartLocation() { 
	SnakePointHeight = TabMiddleHeight; // Middle //
	SnakePointWidth = TabWidth - TabMiddleWidth; // Middle //
	GameTab[SnakePointHeight][SnakePointWidth] = LogicSnake; // Filling snake start point with word 'snake' //
}

void FoodLocation() {
	do {
		FoodTabHeight = rand() % (TabHeight - 2) + 1; // Randomize food height location from 1 to TabHeight-2 //
		FoodTabWidth = rand() % (TabWidth - 2) + 1; // Randomize food width location from 1 to TabWidth-2 //
	} while (GameTab[FoodTabHeight][FoodTabWidth] != LogicEmpty); // Cannot roll same height and width as snake //
	GameTab[FoodTabHeight][FoodTabWidth] = LogicFood; // Filling one field with word 'food' //
}

void DrawBoard() { // Main game board //
	std::cout << TopLeftCorner; // Top border //
	for (int i = 0; i < TabWidth; i++) {
		std::cout << TopBottomBorder << TopBottomBorder;
	}
	std::cout << TopRightCorner;
	for (int i = 0; i < TabHeight; i++) { // Left border //
		std::cout << std::endl << LeftRightBorder;
		for (int j = 0; j < TabWidth; j++) { // Space between borders - play field //
			if (GameTab[i][j] == LogicEmpty) std::cout << EmptyCode << EmptyCode; // Filling board with empty spaces //
			if (GameTab[i][j] == LogicSnake) std::cout << SnakeCode << SnakeCode; // Filling board with snake fields //
			if (GameTab[i][j] == LogicFood) std::cout << FoodCodePart1 << FoodCodePart2; // Filling board with food field //
		}
		std::cout << LeftRightBorder; // Right border //
	}
	std::cout << std::endl;
	std::cout << BottomLeftCorner; // Bottom border //
	for (int i = 0; i < TabWidth; i++) {
		std::cout << TopBottomBorder << TopBottomBorder;
	}
	std::cout << BottomRightCorner;
}

void SnakeLengthHistory() { // Snake length //
	SnakeMoves++; // Amount of moves that snake did //
	OldSnakeHeight[SnakeMoves] = SnakePointHeight; // History of moves height coordinate // 
	OldSnakeWidth[SnakeMoves] = SnakePointWidth; // History of moves width coordinate // 
}

void Eating() {
	if (GameTab[SnakePointHeight][SnakePointWidth] == GameTab[FoodTabHeight][FoodTabWidth]) { // If snake ate food then //
		SnakeLength++; // Increase snake length //
		FoodLocation();
		Carriage(FoodTabHeight + 1, FoodTabWidth * 2 + 1); // Overwrite old values with food //
		std::cout << FoodCodePart1 << FoodCodePart2;
	}
	GameTab[SnakePointHeight][SnakePointWidth] = LogicSnake; // First segment of snake, it's head //
	Carriage(SnakePointHeight + 1, SnakePointWidth * 2 + 1); // Overwrite old values with snake //
	std::cout << SnakeCode << SnakeCode;
	GameTab[OldSnakeHeight[SnakeMoves - SnakeLength]][OldSnakeWidth[SnakeMoves - SnakeLength]] = LogicEmpty; // Old coordinates should be empty when snake moves //
	Carriage(OldSnakeHeight[SnakeMoves - SnakeLength] + 1, OldSnakeWidth[SnakeMoves - SnakeLength] * 2 + 1); // Overwrite old values with double empty space //
	std::cout << EmptyCode << EmptyCode;
}

void Controls() { 
	if (_kbhit()) { // When key was hit then //
		Button = _getch();
		if (Button == WKey && (Direction == LeftDirection || Direction == RightDirection)) Direction = UpDirection; // If player hit 'w' then snake direction will be up //
		if (Button == SKey && (Direction == LeftDirection || Direction == RightDirection)) Direction = DownDirection; // If player hit 's' then snake direction will be down //
		if (Button == AKey && (Direction == UpDirection || Direction == DownDirection)) Direction = LeftDirection; // If player hit 'a' then snake direction will be left //
		if (Button == DKey && (Direction == UpDirection || Direction == DownDirection)) Direction = RightDirection; // If player hit 'd' then snake direction will be right //
	}
}

void SnakeShift() {
	if (Direction == UpDirection) SnakePointHeight--; // Start moving up //
	if (Direction == DownDirection) SnakePointHeight++; // Start moving down //
	if (Direction == LeftDirection) SnakePointWidth--; // Start moving left //
	if (Direction == RightDirection) SnakePointWidth++; // Start moving right //
}

void GameOverMessages() {
	Carriage(TabHeight - 13, TabWidth - 3);
	std::cout << "GAME OVER";
	Carriage(TabHeight - 12, TabWidth - 1);
	std::cout << "SCORE";

	// Score multipliers //

	if (GameDifficulty == EasyDifficulty)
	Score = SnakeLength * 0.5;
	if (GameDifficulty == NormalDifficulty)
	Score = SnakeLength;
	if (GameDifficulty == HardDifficulty)
	Score = SnakeLength * 1.5;
	if (GameDifficulty == InsaneDifficulty)
	Score = SnakeLength * 2;

	// Different carriage locations if score is decimal fraction //

	if (fmod(Score,1) == 0)
	Carriage(TabHeight - 11, TabWidth + 1);
	else
	Carriage(TabHeight - 11, TabWidth);
	std::cout << Score;
	Carriage(TabHeight + 1, 0);
}

int main() 
{
	
	HowToControl();
	Difficulty();
	Ready();
	EmptyTable();
	SnakeStartLocation();
	srand(time(NULL)); // True RNG //
	FoodLocation();
	Carriage(0, 0);
	DrawBoard();

	for (;;) { // Endless loop //
		SnakeLengthHistory();
		Eating();
		Sleep(GameSpeed); // Refresh rate //
		Controls();
		SnakeShift();

		// Game over rules //

		if (SnakePointWidth == TabWidth) break; // Right border //
		if (SnakePointWidth == -1) break; // Left border //
		if (SnakePointHeight == TabHeight) break; // Bottom border //
		if (SnakePointHeight == -1) break; // Top border //
		if (GameTab[SnakePointHeight][SnakePointWidth] == LogicSnake) break; // Eats itself // 
	}

	GameOverMessages();
	_getch();
	Sleep(1000); // Anti 'close game by accident' //
	_getch();

    return 0;
}

