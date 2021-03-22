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
#include "board.h"
#include "Random.h"
using namespace std;


class Tile {
public:
	Tile(int _x, int _y);
	int CheckTile();
	void SetTile(int _tileType);
	int CheckBomb();
	void SetBomb(int _bomb);
	void SetNeighbors(int num, bool bomb);
	int CheckNeighbors();
	int CheckDebug();
	void SetDebug();
	void SetFlag(int _flagType);
	int CheckFlag();
	void SetPrevFlag(int _flagType);
	int CheckPrevFlag();
	void SetExplode();
	int CheckExplode();
	

private:
	
	int x;
	int y;

	//0. Hidden | 1. Revealed
	int tileType = 0;
	
	//0. No Bomb | 1. Bomb
	int bomb = 0;

	//0. Debug Off| 1. Debug On
	int debug = 0;

	//0. No Flag| 1. Flag
	int flag = 0;
	int prevFlag = 0;

	//0.No Explode |1. Explode
	int explode = 0;

	//Neighbors
	bool neiOne = false;
	bool neiTwo = false;
	bool neiThree = false;
	bool neiFour = false;
	bool neiFive = false;
	bool neiSix = false;
	bool neiSeven = false;
	bool neiEight = false;

	int numBombNeighbors = 0;

};