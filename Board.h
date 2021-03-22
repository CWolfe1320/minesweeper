#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <sstream>
#include <vector>
#include "tile.h"
#include "Random.h"
using namespace std;


class Board {

public:

	Board();
	Board(vector<int> cfg);
	void RestartBoard();
	void RenderWindow();
	void ClearBoard();
	void TestBoard(string filename);

private:
	//Board Stuff
	unsigned int windowWidth = 0;
	unsigned int windowHeight = 0;
	//Tile Stuff
	unsigned int numColumns = 0;
	unsigned int numRows = 0;
	unsigned int tileCount = 0;
	unsigned int mineCount = 0;

	sf::Image tileRevealed;
	sf::Image tileHidden;
	sf::Image num1;
	sf::Image num2;
	sf::Image num3;
	sf::Image num4;
	sf::Image num5;
	sf::Image num6;
	sf::Image num7;
	sf::Image num8;
	sf::Image mine;
	sf::Image flag;
	
	sf::Texture hiddenTileTexture;
	sf::Texture revealedTileTexture;
	sf::Texture bombTexture;

	sf::Texture numOne;
	sf::Texture numTwo;
	sf::Texture numThree;
	sf::Texture numFour;
	sf::Texture numFive;
	sf::Texture numSix;
	sf::Texture numSeven;
	sf::Texture numEight;



	sf::Texture face_happy;
	sf::Image fHappy;
	sf::Texture face_lose;
	sf::Image fLose;
	sf::Texture face_win;
	sf::Image fWin;

	sf::Image iDebug;
	sf::Texture debug;

	sf::Image test1;
	sf::Texture testOne;
	sf::Image test2;
	sf::Texture testTwo;
	sf::Image test3;
	sf::Texture testThree;

	sf::Image iFlag;
	sf::Texture tFlag;


	sf::Image digits;
	sf::Texture tDZero;
	sf::Texture tDOne;
	sf::Texture tDTwo;
	sf::Texture tDThree;
	sf::Texture tDFour;
	sf::Texture tDFive;
	sf::Texture tDSix;
	sf::Texture tDSeven;
	sf::Texture tDEight;
	sf::Texture tDNine;
	sf::Texture tDMinus;

	vector <vector<Tile>> tiles;


	//Locked CFG Settings
	//Board Stuff
	unsigned int _windowWidth = 0;
	unsigned int _windowHeight = 0;
	//Tile Stuff
	unsigned int _numColumns = 0;
	unsigned int _numRows = 0;
	unsigned int _tileCount = 0;
	unsigned int _mineCount = 0;

};