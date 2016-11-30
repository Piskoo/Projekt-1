#include "stdafx.h"
#include <iostream>
#include <conio.h>
	
	
const int TabWidth = 25; // Board width
const int TabHeight = 25; // Board height


int main() 
{
	// Main game board

	for (int i = 0; i < TabWidth; i++) { // Top border
		std::cout << "--";
	}

	for (int i = 0; i < TabHeight; i++) { // Left border
		std::cout << std::endl << "||";
		for (int j = 0; j < TabWidth-2; j++) { // Space between borders
			std::cout << "  ";
		}
		std::cout << "||"; // Right border
	}
	std::cout << std::endl;
	for (int i = 0; i < TabWidth; i++) { // Bottom border
		std::cout << "--";
	}

	_getch();

    return 0;
}

