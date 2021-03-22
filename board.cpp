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

Board::Board(){}
Board::Board(vector<int> cfg) {

    //0. number of columns | 1. number of rows | 2. window width | 3. window height | 4. tile count | 5. mineCount

    //sets the config to variables within the board
    numColumns = cfg.at(0);
    numRows = cfg.at(1);
	windowWidth = cfg.at(2);
	windowHeight = cfg.at(3);
    tileCount = cfg.at(4);
    mineCount = cfg.at(5);


    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _numColumns = numColumns;
    _numRows = numRows;
    _tileCount = tileCount;
    _mineCount = mineCount;


    int count = 0;


    //initiliazes the board with blank tiles
    for (int i = 0; i < numRows; ++i) {
        vector<Tile> tempTileVec;
        for (int j = 0; j < numColumns; ++j) {
            vector<int> tileType;
            tempTileVec.push_back(Tile(j, i));
        }
        tiles.push_back(tempTileVec);
    }


    //initializes bombs onto the board
    while (count != mineCount) {
            int bombX = 0;
            int bombY = 0;
            bombX = Random::Number(0,numRows - 1);
            bombY = Random::Number(0,numColumns - 1);

            /*cout << "(" << bombX << "," << bombY << ")" << endl;
            cout << "(" << numRows << "," << numColumns << ")" << endl;*/

            int maxColBomb = mineCount / numColumns;
            int colBomb = 0;

            if (tiles[bombX][bombY].CheckBomb() == 0 && count != mineCount && colBomb != maxColBomb) {
                tiles[bombX][bombY].SetBomb(1);
                /*cout << "bomb set" << endl;*/
                ++count;
                ++colBomb;
            }
            else if (count == mineCount) {
                break;
            }
    }

    //Sets the neighbor values
    for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRows; ++j) {

            bool bomb = false;

            if (j != 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);

            }

            else if (j == 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {
                
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
            }
            else if (j == 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {

                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
            }
            else if (j != 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {
                 //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j >= numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {
                
                 //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j >= numRows - 1 && i >= numColumns - 1) {

                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j == 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
            }
            else if (j != 0 && i == 0 && j >= numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
                
            }


        }
    }

    //temp print statement for the bombs in command line
   /* for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRows; ++j) {
            cout << tiles[j][i].CheckBomb();
        }
        cout << endl;
    }
    for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRows; ++j) {

            cout << tiles[j][i].CheckNeighbors() << endl;
        }
    }*/

    


    tileRevealed.loadFromFile("images/tile_revealed.png");
    tileHidden.loadFromFile("images/tile_hidden.png");
    num1.loadFromFile("images/number_1.png");
    num2.loadFromFile("images/number_2.png");
    num3.loadFromFile("images/number_3.png");
    num4.loadFromFile("images/number_4.png");
    num5.loadFromFile("images/number_5.png");
    num6.loadFromFile("images/number_6.png");
    num7.loadFromFile("images/number_7.png");
    num8.loadFromFile("images/number_8.png");
    mine.loadFromFile("images/mine.png");
    flag.loadFromFile("images/flag.png");

    hiddenTileTexture.loadFromImage(tileHidden);
    revealedTileTexture.loadFromImage(tileRevealed);
    bombTexture.loadFromImage(mine);
    numOne.loadFromImage(num1);
    numTwo.loadFromImage(num2);
    numThree.loadFromImage(num3);
    numFour.loadFromImage(num4);
    numFive.loadFromImage(num5);
    numSix.loadFromImage(num6);
    numSeven.loadFromImage(num7);
    numEight.loadFromImage(num8);

    fHappy.loadFromFile("images/face_happy.png");
    fLose.loadFromFile("images/face_lose.png");
    fWin.loadFromFile("images/face_win.png");

    face_happy.loadFromImage(fHappy);
    face_lose.loadFromImage(fLose);
    face_win.loadFromImage(fWin);
   
    test1.loadFromFile("images/test_1.png");
    test2.loadFromFile("images/test_2.png");
    test3.loadFromFile("images/test_3.png");
    iDebug.loadFromFile("images/debug.png");

    testOne.loadFromImage(test1);
    testTwo.loadFromImage(test2);
    testThree.loadFromImage(test3);
    debug.loadFromImage(iDebug);


    iFlag.loadFromFile("images/flag.png");
    tFlag.loadFromImage(iFlag);


    digits.loadFromFile("images/digits.png");
    tDZero.loadFromImage(digits, sf::IntRect(0, 0, 21, 32));
    tDOne.loadFromImage(digits, sf::IntRect(21, 0, 21, 32));
    tDTwo.loadFromImage(digits, sf::IntRect(42, 0, 21, 32));
    tDThree.loadFromImage(digits, sf::IntRect(63, 0, 21, 32));
    tDFour.loadFromImage(digits, sf::IntRect(84, 0, 21, 32));;
    tDFive.loadFromImage(digits, sf::IntRect(105, 0, 21, 32));;
    tDSix.loadFromImage(digits, sf::IntRect(126, 0, 21, 32));;
    tDSeven.loadFromImage(digits, sf::IntRect(147, 0, 21, 32));;
    tDEight.loadFromImage(digits, sf::IntRect(168, 0, 21, 32));;
    tDNine.loadFromImage(digits, sf::IntRect(189, 0, 21, 32));;
    tDMinus.loadFromImage(digits, sf::IntRect(210, 0, 21, 32));;


}


void Board::RestartBoard() {
    tiles.clear();
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;
    numColumns = _numColumns;
    numRows = _numRows;
    tileCount = _tileCount;
    mineCount = _mineCount;
    int count = 0;

    for (int i = 0; i < numRows; ++i) {
        vector<Tile> tempTileVec;
        for (int j = 0; j < numColumns; ++j) {
            vector<int> tileType;
            tempTileVec.push_back(Tile(j, i));
        }
        tiles.push_back(tempTileVec);
    }


    //initializes bombs onto the board
    while (count != mineCount) {
        int bombX = 0;
        int bombY = 0;
        bombX = Random::Number(0, numRows - 1);
        bombY = Random::Number(0, numColumns - 1);

        /*cout << "(" << bombX << "," << bombY << ")" << endl;
        cout << "(" << numRows << "," << numColumns << ")" << endl;*/

        int maxColBomb = mineCount / numColumns;
        int colBomb = 0;

        if (tiles[bombX][bombY].CheckBomb() == 0 && count != mineCount && colBomb != maxColBomb) {
            tiles[bombX][bombY].SetBomb(1);
            /*cout << "bomb set" << endl;*/
            ++count;
            ++colBomb;
        }
        else if (count == mineCount) {
            break;
        }
    }

    //Sets the neighbor values
    for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRows; ++j) {

            bool bomb = false;

            if (j != 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);

            }

            else if (j == 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {

                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
            }
            else if (j == 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {

                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
            }
            else if (j != 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j >= numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j >= numRows - 1 && i >= numColumns - 1) {

                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j == 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
            }
            else if (j != 0 && i == 0 && j >= numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);

            }


        }
    }

    

}

void Board::ClearBoard() {
    tiles.clear();
    windowWidth = 0;
    windowHeight = 0;
    //Tile Stuff
    numColumns = 0;
    numRows = 0;
    tileCount = 0;
    mineCount = 0;
}

void Board::TestBoard(string filename) {
    ifstream inFile(filename);
    string boardLine;
    vector<int> rawTiles;
    vector<vector<int>> mapInt;
    string tempString;
    int counter = 0;
    int tempNum = 0;
    if (inFile.is_open()) {



        while (getline(inFile, boardLine)) {
            counter++;
            for (int i = 0; i < boardLine.size(); ++i) {

                tempString = boardLine.at(i);

                tempNum = stoi(tempString);
                rawTiles.push_back(tempNum);
            }


        }
    }
    
    for (int i = 0; i < rawTiles.size(); i++) {
            if (rawTiles.at(i) == 1) {
                mineCount++;
            }
        }

    numRows = counter;
    numColumns = rawTiles.size()/numRows;
    tileCount = numRows * numColumns;
    windowWidth = numColumns * 32;
    windowHeight = (numRows * 32) + 88;
    
    
    

    

    //initiliazes the board with blank tiles
    for (int i = 0; i < numRows; ++i) {
        vector<Tile> tempTileVec;
        for (int j = 0; j < numColumns; ++j) {
            vector<int> tileType;
            tempTileVec.push_back(Tile(j, i));
        }
        tiles.push_back(tempTileVec);
    }

    int testCount = 0;
    vector<int> tempVector;
    for (int i = 0; i < tileCount; ++i) {
        ++testCount;
        tempVector.push_back(rawTiles[i]);
        if (testCount == numColumns) {
            testCount = 0;
            mapInt.push_back(tempVector);
            tempVector.clear();
        }
        
    }


   

    //Sets bombs supposedly
    int tileCounter = 0;
    for (int i = 0; i < numColumns; i++) {
        for (int j = 0; j < numRows; j++) {
            tiles[j][i].SetBomb(mapInt[j][i]);
        }
    }


    //Sets the neighbor values
    for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRows; ++j) {

            bool bomb = false;

            if (j != 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);

            }

            else if (j == 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {

                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
            }
            else if (j == 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {

                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
            }
            else if (j != 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 3
                if (tiles[j + 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(3, bomb);
                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j >= numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j != 0 && i != 0 && j >= numRows - 1 && i >= numColumns - 1) {

                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
                //Neighbor 7
                if (tiles[j - 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(7, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);
            }
            else if (j == 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                //Neighbor 4
                if (tiles[j + 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(4, bomb);
                //Neighbor 5
                if (tiles[j + 1][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j + 1][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(5, bomb);
                //Neighbor 6
                if (tiles[j][i - 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i - 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(6, bomb);
            }
            else if (j != 0 && i == 0 && j >= numRows - 1 && i < numColumns - 1) {
                //Neighbor 1
                if (tiles[j - 1][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(1, bomb);
                //Neighbor 2
                if (tiles[j][i + 1].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j][i + 1].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(2, bomb);
                //Neighbor 8
                if (tiles[j - 1][i].CheckBomb() == 1) {
                    bomb = true;
                }
                else if (tiles[j - 1][i].CheckBomb() == 0) {
                    bomb = false;
                }
                tiles[j][i].SetNeighbors(8, bomb);

            }


        }
    }



}


void Board::RenderWindow() {
	
	
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
    
    sf::Sprite tile;
    vector<sf::Sprite> m_tiles;

    sf::Sprite mine;
    sf::Sprite number;
    sf::Sprite vicCondition;
    sf::Sprite spriteDebug;
    sf::Sprite spriteTest1;
    sf::Sprite spriteTest2;
    sf::Sprite spriteTest3;
    sf::Sprite counter1;
    sf::Sprite counter10;
    sf::Sprite counter100;
    sf::Sprite counter_;
    sf::Sprite flag;
    int counter = mineCount;
    vector<int> countingVector;
    string ones;
    string tens;
    string hundreds;
    bool game = true;
    bool win = false;

    int winTiles = _tileCount - mineCount;
    int winCount = 0;

    


    while (window.isOpen())
    {

        if (game) {
            vicCondition.setTexture(face_happy);
        }
        else if (!game && win) {
            vicCondition.setTexture(face_win);
        }
        else if (!game) {
            vicCondition.setTexture(face_lose);
        }
        
        vicCondition.setPosition((windowWidth / 2) - 32, windowHeight - 88);
        spriteDebug.setTexture(debug);
        spriteDebug.setPosition(windowWidth - 256, windowHeight - 88);

        spriteTest1.setTexture(testOne);
        spriteTest1.setPosition(windowWidth - 192, windowHeight - 88);
        spriteTest2.setTexture(testTwo);
        spriteTest2.setPosition(windowWidth - 128, windowHeight - 88);
        spriteTest3.setTexture(testThree);
        spriteTest3.setPosition(windowWidth - 64, windowHeight - 88);



        string sCounter = to_string(counter);

        if (sCounter.size() == 1) {
            ones = sCounter;
        }
        else if (sCounter.size() == 2) {
            if (sCounter.at(0) == '-') {
                ones = sCounter.at(1);
            }
            else {
                ones = sCounter.at(1);
                tens = sCounter.at(0);
            }
        }
        else if (sCounter.size() == 3) {
            if (sCounter.at(0) == '-') {
                ones = sCounter.at(2);
                tens = sCounter.at(1);
            }
            else {
                ones = sCounter.at(2);
                tens = sCounter.at(1);
                hundreds = sCounter.at(0);
            }
        }
        else if (sCounter.size() == 4) {
            ones = sCounter.at(3);
            tens = sCounter.at(2);
            hundreds = sCounter.at(1);
        }
        if (sCounter.size() > 0) {
            countingVector.push_back(stoi(ones));
        }
        if (sCounter.size() > 1 && counter > 0) {
            countingVector.push_back(stoi(tens));
        }
        if (sCounter.size() > 2 && counter < 0) {
            countingVector.push_back(stoi(tens));
        }
        if (sCounter.size() > 2 && counter > 0) {
            countingVector.push_back(stoi(hundreds));
        }
        if (sCounter.size() > 3 && counter < 0) {
            countingVector.push_back(stoi(hundreds));
        }

        if (sCounter.size() == 1) {
            counter10.setTexture(tDZero);
            counter100.setTexture(tDZero);
            switch (countingVector.at(0)) {
            case 0:
                counter1.setTexture(tDZero);
                break;
            case 1:
                counter1.setTexture(tDOne);
                break;
            case 2:
                counter1.setTexture(tDTwo);
                break;
            case 3:
                counter1.setTexture(tDThree);
                break;
            case 4:
                counter1.setTexture(tDFour);
                break;
            case 5:
                counter1.setTexture(tDFive);
                break;
            case 6:
                counter1.setTexture(tDSix);
                break;
            case 7:
                counter1.setTexture(tDSeven);
                break;
            case 8:
                counter1.setTexture(tDEight);
                break;
            case 9:
                counter1.setTexture(tDNine);
                break;
            }
        }
        else if (sCounter.size() == 2 && counter > 0) {
            counter100.setTexture(tDZero);
            switch (countingVector.at(0)) {
            case 0:
                counter1.setTexture(tDZero);
                break;
            case 1:
                counter1.setTexture(tDOne);
                break;
            case 2:
                counter1.setTexture(tDTwo);
                break;
            case 3:
                counter1.setTexture(tDThree);
                break;
            case 4:
                counter1.setTexture(tDFour);
                break;
            case 5:
                counter1.setTexture(tDFive);
                break;
            case 6:
                counter1.setTexture(tDSix);
                break;
            case 7:
                counter1.setTexture(tDSeven);
                break;
            case 8:
                counter1.setTexture(tDEight);
                break;
            case 9:
                counter1.setTexture(tDNine);
                break;
            }
            switch (countingVector.at(1)) {
            case 0:
                counter10.setTexture(tDZero);
                break;
            case 1:
                counter10.setTexture(tDOne);
                break;
            case 2:
                counter10.setTexture(tDTwo);
                break;
            case 3:
                counter10.setTexture(tDThree);
                break;
            case 4:
                counter10.setTexture(tDFour);
                break;
            case 5:
                counter10.setTexture(tDFive);
                break;
            case 6:
                counter10.setTexture(tDSix);
                break;
            case 7:
                counter10.setTexture(tDSeven);
                break;
            case 8:
                counter10.setTexture(tDEight);
                break;
            case 9:
                counter10.setTexture(tDNine);
                break;
            }
        }
        else if (sCounter.size() == 2 && counter < 0) {
            counter100.setTexture(tDZero);
            counter10.setTexture(tDZero);
            switch (countingVector.at(0)) {
            case 0:
                counter1.setTexture(tDZero);
                break;
            case 1:
                counter1.setTexture(tDOne);
                break;
            case 2:
                counter1.setTexture(tDTwo);
                break;
            case 3:
                counter1.setTexture(tDThree);
                break;
            case 4:
                counter1.setTexture(tDFour);
                break;
            case 5:
                counter1.setTexture(tDFive);
                break;
            case 6:
                counter1.setTexture(tDSix);
                break;
            case 7:
                counter1.setTexture(tDSeven);
                break;
            case 8:
                counter1.setTexture(tDEight);
                break;
            case 9:
                counter1.setTexture(tDNine);
                break;
            }

        }
        else if (sCounter.size() >= 3 && counter > 0) {
            switch (countingVector.at(0)) {
            case 0:
                counter1.setTexture(tDZero);
                break;
            case 1:
                counter1.setTexture(tDOne);
                break;
            case 2:
                counter1.setTexture(tDTwo);
                break;
            case 3:
                counter1.setTexture(tDThree);
                break;
            case 4:
                counter1.setTexture(tDFour);
                break;
            case 5:
                counter1.setTexture(tDFive);
                break;
            case 6:
                counter1.setTexture(tDSix);
                break;
            case 7:
                counter1.setTexture(tDSeven);
                break;
            case 8:
                counter1.setTexture(tDEight);
                break;
            case 9:
                counter1.setTexture(tDNine);
                break;
            }
            switch (countingVector.at(1)) {
            case 0:
                counter10.setTexture(tDZero);
                break;
            case 1:
                counter10.setTexture(tDOne);
                break;
            case 2:
                counter10.setTexture(tDTwo);
                break;
            case 3:
                counter10.setTexture(tDThree);
                break;
            case 4:
                counter10.setTexture(tDFour);
                break;
            case 5:
                counter10.setTexture(tDFive);
                break;
            case 6:
                counter10.setTexture(tDSix);
                break;
            case 7:
                counter10.setTexture(tDSeven);
                break;
            case 8:
                counter10.setTexture(tDEight);
                break;
            case 9:
                counter10.setTexture(tDNine);
                break;
            }
            switch (countingVector.at(2)) {
            case 0:
                counter100.setTexture(tDZero);
                break;
            case 1:
                counter100.setTexture(tDOne);
                break;
            case 2:
                counter100.setTexture(tDTwo);
                break;
            case 3:
                counter100.setTexture(tDThree);
                break;
            case 4:
                counter100.setTexture(tDFour);
                break;
            case 5:
                counter100.setTexture(tDFive);
                break;
            case 6:
                counter100.setTexture(tDSix);
                break;
            case 7:
                counter100.setTexture(tDSeven);
                break;
            case 8:
                counter100.setTexture(tDEight);
                break;
            case 9:
                counter100.setTexture(tDNine);
                break;
            }
        }
        else if (sCounter.size() == 3 && counter < 0) {
            counter100.setTexture(tDZero);
            switch (countingVector.at(0)) {
            case 0:
                counter1.setTexture(tDZero);
                break;
            case 1:
                counter1.setTexture(tDOne);
                break;
            case 2:
                counter1.setTexture(tDTwo);
                break;
            case 3:
                counter1.setTexture(tDThree);
                break;
            case 4:
                counter1.setTexture(tDFour);
                break;
            case 5:
                counter1.setTexture(tDFive);
                break;
            case 6:
                counter1.setTexture(tDSix);
                break;
            case 7:
                counter1.setTexture(tDSeven);
                break;
            case 8:
                counter1.setTexture(tDEight);
                break;
            case 9:
                counter1.setTexture(tDNine);
                break;
            }
            switch (countingVector.at(1)) {
            case 0:
                counter10.setTexture(tDZero);
                break;
            case 1:
                counter10.setTexture(tDOne);
                break;
            case 2:
                counter10.setTexture(tDTwo);
                break;
            case 3:
                counter10.setTexture(tDThree);
                break;
            case 4:
                counter10.setTexture(tDFour);
                break;
            case 5:
                counter10.setTexture(tDFive);
                break;
            case 6:
                counter10.setTexture(tDSix);
                break;
            case 7:
                counter10.setTexture(tDSeven);
                break;
            case 8:
                counter10.setTexture(tDEight);
                break;
            case 9:
                counter10.setTexture(tDNine);
                break;
            }
        }
        else if (sCounter.size() == 4 && counter < 0) {
            switch (countingVector.at(0)) {
            case 0:
                counter1.setTexture(tDZero);
                break;
            case 1:
                counter1.setTexture(tDOne);
                break;
            case 2:
                counter1.setTexture(tDTwo);
                break;
            case 3:
                counter1.setTexture(tDThree);
                break;
            case 4:
                counter1.setTexture(tDFour);
                break;
            case 5:
                counter1.setTexture(tDFive);
                break;
            case 6:
                counter1.setTexture(tDSix);
                break;
            case 7:
                counter1.setTexture(tDSeven);
                break;
            case 8:
                counter1.setTexture(tDEight);
                break;
            case 9:
                counter1.setTexture(tDNine);
                break;
            }
            switch (countingVector.at(1)) {
            case 0:
                counter10.setTexture(tDZero);
                break;
            case 1:
                counter10.setTexture(tDOne);
                break;
            case 2:
                counter10.setTexture(tDTwo);
                break;
            case 3:
                counter10.setTexture(tDThree);
                break;
            case 4:
                counter10.setTexture(tDFour);
                break;
            case 5:
                counter10.setTexture(tDFive);
                break;
            case 6:
                counter10.setTexture(tDSix);
                break;
            case 7:
                counter10.setTexture(tDSeven);
                break;
            case 8:
                counter10.setTexture(tDEight);
                break;
            case 9:
                counter10.setTexture(tDNine);
                break;
            }
            switch (countingVector.at(2)) {
            case 0:
                counter100.setTexture(tDZero);
                break;
            case 1:
                counter100.setTexture(tDOne);
                break;
            case 2:
                counter100.setTexture(tDTwo);
                break;
            case 3:
                counter100.setTexture(tDThree);
                break;
            case 4:
                counter100.setTexture(tDFour);
                break;
            case 5:
                counter100.setTexture(tDFive);
                break;
            case 6:
                counter100.setTexture(tDSix);
                break;
            case 7:
                counter100.setTexture(tDSeven);
                break;
            case 8:
                counter100.setTexture(tDEight);
                break;
            case 9:
                counter100.setTexture(tDNine);
                break;
            }
        }
        else {
            counter1.setTexture(tDZero);

        }

        //counter1.setTexture(tDZero);
        counter1.setPosition(63, windowHeight - 88);

        //counter10.setTexture(tDZero);
        counter10.setPosition(42, windowHeight - 88);

        //counter100.setTexture(tDZero);
        counter100.setPosition(21, windowHeight - 88);

        counter_.setTexture(tDMinus);
        counter_.setPosition(0, windowHeight - 88);

        sf::Event event;


        window.clear(sf::Color::White);

        window.draw(vicCondition);
        window.draw(spriteTest3);
        window.draw(spriteTest2);
        window.draw(spriteTest1);
        window.draw(spriteDebug);
        window.draw(counter1);
        window.draw(counter10);
        window.draw(counter100);
        if (counter < 0) {
            window.draw(counter_);
        }

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {


                    
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (mouse.y < windowHeight - 88) {
                        if (tiles[mouse.y / 32][mouse.x / 32].CheckFlag() == 0 && tiles[mouse.y / 32][mouse.x / 32].CheckTile() == 0 && game) {
                            tiles[mouse.y / 32][mouse.x / 32].SetFlag(1);
                            --counter;
                            countingVector.clear();
                            ones.clear();
                            tens.clear();
                            hundreds.clear();

                        }
                        else if (tiles[mouse.y / 32][mouse.x / 32].CheckFlag() == 1 && game) {

                            tiles[mouse.y / 32][mouse.x / 32].SetFlag(0);
                            tiles[mouse.y / 32][mouse.x / 32].SetPrevFlag(1);

                            ++counter;
                            countingVector.clear();
                            ones.clear();
                            tens.clear();
                            hundreds.clear();
                        }
                    }
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                
                sf::FloatRect debugBounds = spriteDebug.getGlobalBounds();
                sf::FloatRect vicConBounds = vicCondition.getGlobalBounds();
                sf::FloatRect test1Bounds = spriteTest1.getGlobalBounds();
                sf::FloatRect test2Bounds = spriteTest2.getGlobalBounds();
                sf::FloatRect test3Bounds = spriteTest3.getGlobalBounds();

                
                if (debugBounds.contains(mouse) && game)
                {
                    for (int i = 0; i < numColumns; ++i) {
                        for (int j = 0; j < numRows; ++j) {
                            tiles[j][i].SetDebug();
                        }
                    }
                }

                if (vicConBounds.contains(mouse))
                {
                    RestartBoard();
                    counter = mineCount;
                    countingVector.clear();
                    ones.clear();
                    tens.clear();
                    hundreds.clear();
                    game = true;
                    win = false;
                    winCount = 0;
                    winTiles = _tileCount - mineCount;
                }
                if (test1Bounds.contains(mouse))
                {
                    ClearBoard();
                    TestBoard("boards/testboard1.brd");
                    counter = mineCount;
                    countingVector.clear();
                    ones.clear();
                    tens.clear();
                    hundreds.clear();
                    game = true;
                    win = false;
                    winCount = 0;
                    winTiles = _tileCount - mineCount;
                }
                if (test2Bounds.contains(mouse))
                {
                    ClearBoard();
                    TestBoard("boards/testboard2.brd");
                    counter = mineCount;
                    countingVector.clear();
                    ones.clear();
                    tens.clear();
                    hundreds.clear();
                    game = true;
                    win = false;
                    winCount = 0;
                    winTiles = _tileCount - mineCount;
                }
                if (test3Bounds.contains(mouse))
                {
                    ClearBoard();
                    TestBoard("boards/testboard3.brd");
                    counter = mineCount;
                    countingVector.clear();
                    ones.clear();
                    tens.clear();
                    hundreds.clear();
                    game = true;
                    win = false;
                    winCount = 0;
                    winTiles = _tileCount - mineCount;
                }

            }

        }

        for (int i = 0; i < numColumns; ++i) {
            
            for (int j = 0; j < numRows; ++j) {

                

                //draws unrevealed tiles
                if (tiles[j][i].CheckTile() == 0 || tiles[j][i].CheckFlag() == 1) {
                    tile.setTexture(hiddenTileTexture);
                    tile.setPosition(i * 32, j * 32);
                    window.draw(tile);

                    if (tiles[j][i].CheckDebug() % 2 != 0 && tiles[j][i].CheckBomb() == 1) {
                        mine.setTexture(bombTexture);
                        mine.setPosition(i * 32, j * 32);
                        window.draw(mine);
                    }
                    if (tiles[j][i].CheckFlag() % 2 != 0) {
                        flag.setTexture(tFlag);
                        flag.setPosition(i * 32, j * 32);
                        window.draw(flag);
                    }

                }
                else if (tiles[j][i].CheckTile() == 1 && tiles[j][i].CheckFlag() == 0) {
                    tile.setTexture(revealedTileTexture);
                    tile.setPosition(i * 32, j * 32);
                    window.draw(tile);
                    //draws bombs
                    if (tiles[j][i].CheckBomb() == 1) {
                        mine.setTexture(bombTexture);
                        mine.setPosition(i * 32, j * 32);
                        window.draw(mine);
                    }
                    //draws numbers
                    else if (tiles[j][i].CheckNeighbors() != 0) {

                        switch (tiles[j][i].CheckNeighbors()) {
                        case 1:
                            number.setTexture(numOne);
                            break;
                        case 2:
                            number.setTexture(numTwo);
                            break;
                        case 3:
                            number.setTexture(numThree);
                            break;
                        case 4:
                            number.setTexture(numFour);
                            break;
                        case 5:
                            number.setTexture(numFive);
                            break;
                        case 6:
                            number.setTexture(numSix);
                            break;
                        case 7:
                            number.setTexture(numSeven);
                            break;
                        case 8:
                            number.setTexture(numEight);
                            break;
                        }
                        number.setPosition(i * 32, j * 32);
                        window.draw(number);
                    }
                }
                if (tiles[j][i].CheckTile() == 1 && tiles[j][i].CheckFlag() == 1 && !game && tiles[j][i].CheckBomb() == 1) {
                    tile.setTexture(revealedTileTexture);
                    tile.setPosition(i * 32, j * 32);
                    window.draw(tile);
                    //draws bombs
                    if (tiles[j][i].CheckBomb() == 1) {
                        mine.setTexture(bombTexture);
                        mine.setPosition(i * 32, j * 32);
                        window.draw(mine);
                    }
                    if (tiles[j][i].CheckFlag() % 2 != 0) {
                        flag.setTexture(tFlag);
                        flag.setPosition(i * 32, j * 32);
                        window.draw(flag);
                    }
                }
                if (win && tiles[j][i].CheckBomb() == 1) {
                    flag.setTexture(tFlag);
                    flag.setPosition(i * 32, j * 32);
                    window.draw(flag);
                    tiles[j][i].SetFlag(1);
                    counter = 0;
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        

                        for (int y = 0; y < numColumns; ++y) {
                            for (int z = 0; z < numRows; ++z) {
                                tiles[z][y].SetPrevFlag(0);
                            }
                        }

                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        
                        sf::FloatRect bounds = tile.getGlobalBounds();

                       
                        if (bounds.contains(mouse) && game)
                        {
                            if (tiles[j][i].CheckFlag() == 0) {
                                tiles[mouse.y / 32][mouse.x / 32].SetTile(1);

                            }
                            if (tiles[j][i].CheckBomb() == 1 && tiles[j][i].CheckFlag() == 0) {
                                tiles[j][i].SetExplode();
                                for (int y = 0; y < numColumns; ++y) {
                                    for (int z = 0; z < numRows; ++z) {
                                        if (tiles[z][y].CheckBomb() == 1) {
                                            tiles[z][y].SetTile(1);
                                            game = false;
                                        }
                                    }
                                }
                            }
                        }
                        }
                    }



                    //This is my reveal algorithm. It is very sad. Please no judge
                    if (tiles[j][i].CheckTile() == 1 && tiles[j][i].CheckNeighbors() == 0 && tiles[j][i].CheckBomb() == 0 && tiles[j][i].CheckPrevFlag() == 0) {

                        if (j != 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {
                            //Neighbor 1
                            if (tiles[j - 1][i + 1].CheckBomb() == 0 && tiles[j - 1][i + 1].CheckFlag() == 0 && tiles[j - 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j - 1][i + 1].SetTile(1);
                            }
                            //Neighbor 2
                            if (tiles[j][i + 1].CheckBomb() == 0 && tiles[j][i + 1].CheckFlag() == 0 && tiles[j][i + 1].CheckPrevFlag() == 0) {
                                tiles[j][i + 1].SetTile(1);
                            }
                            //Neighbor 3
                            if (tiles[j + 1][i + 1].CheckBomb() == 0 && tiles[j + 1][i + 1].CheckFlag() == 0 && tiles[j + 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i + 1].SetTile(1);
                            }
                            //Neighbor 4
                            if (tiles[j + 1][i].CheckBomb() == 0 && tiles[j + 1][i].CheckFlag() == 0 && tiles[j + 1][i].CheckPrevFlag() == 0) {
                                tiles[j + 1][i].SetTile(1);
                            }
                            //Neighbor 5
                            if (tiles[j + 1][i - 1].CheckBomb() == 0 && tiles[j + 1][i - 1].CheckFlag() == 0 && tiles[j + 1][i - 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i - 1].SetTile(1);
                            }
                            //Neighbor 6
                            if (tiles[j][i - 1].CheckBomb() == 0 && tiles[j][i - 1].CheckFlag() == 0 && tiles[j][i - 1].CheckPrevFlag() == 0) {
                                tiles[j][i - 1].SetTile(1);
                            }
                            //Neighbor 7
                            if (tiles[j - 1][i - 1].CheckBomb() == 0 && tiles[j - 1][i - 1].CheckFlag() == 0 && tiles[j - 1][i - 1].CheckPrevFlag() == 0) {
                                tiles[j - 1][i - 1].SetTile(1);
                            }
                            //Neighbor 8
                            if (tiles[j - 1][i].CheckBomb() == 0 && tiles[j - 1][i].CheckFlag() == 0 && tiles[j - 1][i].CheckPrevFlag() == 0) {
                                tiles[j - 1][i].SetTile(1);
                            }

                        }

                        else if (j == 0 && i != 0 && j < numRows - 1 && i < numColumns - 1) {
                            //Neighbor 2
                            if (tiles[j][i + 1].CheckBomb() == 0 && tiles[j][i + 1].CheckFlag() == 0 && tiles[j][i + 1].CheckPrevFlag() == 0) {
                                tiles[j][i + 1].SetTile(1);
                            }
                            //Neighbor 3
                            if (tiles[j + 1][i + 1].CheckBomb() == 0 && tiles[j + 1][i + 1].CheckFlag() == 0 && tiles[j + 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i + 1].SetTile(1);
                            }
                            //Neighbor 4
                            if (tiles[j + 1][i].CheckBomb() == 0 && tiles[j + 1][i].CheckFlag() == 0 && tiles[j + 1][i].CheckPrevFlag() == 0) {
                                tiles[j + 1][i].SetTile(1);
                            }
                            //Neighbor 5
                            if (tiles[j + 1][i - 1].CheckBomb() == 0 && tiles[j + 1][i - 1].CheckFlag() == 0 && tiles[j + 1][i - 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i - 1].SetTile(1);
                            }
                            //Neighbor 6
                            if (tiles[j][i - 1].CheckBomb() == 0 && tiles[j][i - 1].CheckFlag() == 0 && tiles[j][i - 1].CheckPrevFlag() == 0) {
                                tiles[j][i - 1].SetTile(1);
                            }
                        }
                        else if (j == 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {
                            //Neighbor 2
                            if (tiles[j][i + 1].CheckBomb() == 0 && tiles[j][i + 1].CheckFlag() == 0 && tiles[j][i + 1].CheckPrevFlag() == 0) {
                                tiles[j][i + 1].SetTile(1);
                            }
                            //Neighbor 3
                            if (tiles[j + 1][i + 1].CheckBomb() == 0 && tiles[j + 1][i + 1].CheckFlag() == 0 && tiles[j + 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i + 1].SetTile(1);
                            }
                            //Neighbor 4
                            if (tiles[j + 1][i].CheckBomb() == 0 && tiles[j + 1][i].CheckFlag() == 0 && tiles[j + 1][i].CheckPrevFlag() == 0) {
                                tiles[j + 1][i].SetTile(1);
                            }
                        }
                        else if (j != 0 && i == 0 && j < numRows - 1 && i < numColumns - 1) {
                            //Neighbor 1
                            if (tiles[j - 1][i + 1].CheckBomb() == 0 && tiles[j - 1][i + 1].CheckFlag() == 0 && tiles[j - 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j - 1][i + 1].SetTile(1);
                            }
                            //Neighbor 2
                            if (tiles[j][i + 1].CheckBomb() == 0 && tiles[j][i + 1].CheckFlag() == 0 && tiles[j][i + 1].CheckPrevFlag() == 0) {
                                tiles[j][i + 1].SetTile(1);
                            }
                            //Neighbor 3
                            if (tiles[j + 1][i + 1].CheckBomb() == 0 && tiles[j + 1][i + 1].CheckFlag() == 0 && tiles[j + 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i + 1].SetTile(1);
                            }
                            //Neighbor 4
                            if (tiles[j + 1][i].CheckBomb() == 0 && tiles[j + 1][i].CheckFlag() == 0 && tiles[j + 1][i].CheckPrevFlag() == 0) {
                                tiles[j + 1][i].SetTile(1);
                            }
                            //Neighbor 8
                            if (tiles[j - 1][i].CheckBomb() == 0 && tiles[j - 1][i].CheckFlag() == 0 && tiles[j - 1][i].CheckPrevFlag() == 0) {
                                tiles[j - 1][i].SetTile(1);
                            }
                        }
                        else if (j != 0 && i != 0 && j >= numRows - 1 && i < numColumns - 1) {
                            //Neighbor 1
                            if (tiles[j - 1][i + 1].CheckBomb() == 0 && tiles[j - 1][i + 1].CheckFlag() == 0 && tiles[j - 1][i + 1].CheckPrevFlag() == 0) {
                                tiles[j - 1][i + 1].SetTile(1);
                            }
                            //Neighbor 2
                            if (tiles[j][i + 1].CheckBomb() == 0 && tiles[j][i + 1].CheckFlag() == 0 && tiles[j][i + 1].CheckPrevFlag() == 0) {
                                tiles[j][i + 1].SetTile(1);
                            }
                            //Neighbor 6
                            if (tiles[j][i - 1].CheckBomb() == 0 && tiles[j][i - 1].CheckFlag() == 0 && tiles[j][i - 1].CheckPrevFlag() == 0) {
                                tiles[j][i - 1].SetTile(1);
                            }
                            //Neighbor 7
                            if (tiles[j - 1][i - 1].CheckBomb() == 0 && tiles[j - 1][i - 1].CheckFlag() == 0 && tiles[j - 1][i - 1].CheckPrevFlag() == 0) {
                                tiles[j - 1][i - 1].SetTile(1);
                            }
                            //Neighbor 8
                            if (tiles[j - 1][i].CheckBomb() == 0 && tiles[j - 1][i].CheckFlag() == 0 && tiles[j - 1][i].CheckPrevFlag() == 0) {
                                tiles[j - 1][i].SetTile(1);
                            }
                        }
                        else if (j != 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                            //Neighbor 4
                            if (tiles[j + 1][i].CheckBomb() == 0 && tiles[j + 1][i].CheckFlag() == 0 && tiles[j + 1][i].CheckPrevFlag() == 0) {
                                tiles[j + 1][i].SetTile(1);
                            }
                            //Neighbor 5
                            if (tiles[j + 1][i - 1].CheckBomb() == 0 && tiles[j + 1][i - 1].CheckFlag() == 0 && tiles[j + 1][i - 1].CheckPrevFlag() == 0) {
                                tiles[j + 1][i - 1].SetTile(1);
                            }
                            //Neighbor 6
                            if (tiles[j][i - 1].CheckBomb() == 0 && tiles[j][i - 1].CheckFlag() == 0 && tiles[j][i - 1].CheckPrevFlag() == 0) {
                                tiles[j][i - 1].SetTile(1);
                            }
                            //Neighbor 7
                            if (tiles[j - 1][i - 1].CheckBomb() == 0 && tiles[j - 1][i - 1].CheckFlag() == 0 && tiles[j - 1][i - 1].CheckPrevFlag() == 0) {
                                tiles[j - 1][i - 1].SetTile(1);
                            }
                            //Neighbor 8
                            if (tiles[j - 1][i].CheckBomb() == 0 && tiles[j - 1][i].CheckFlag() == 0 && tiles[j - 1][i].CheckPrevFlag() == 0) {
                                tiles[j - 1][i].SetTile(1);
                            }
                        }
                        else if (j != 0 && i != 0 && j >= numRows - 1 && i >= numColumns - 1) {

                            //Neighbor 6
                            if (tiles[j][i - 1].CheckBomb() == 0 && tiles[j][i - 1].CheckFlag() == 0) {
                                tiles[j][i - 1].SetTile(1);
                            }
                            //Neighbor 7
                            if (tiles[j - 1][i - 1].CheckBomb() == 0 && tiles[j - 1][i - 1].CheckFlag() == 0) {
                                tiles[j - 1][i - 1].SetTile(1);
                            }
                            //Neighbor 8
                            if (tiles[j - 1][i].CheckBomb() == 0 && tiles[j - 1][i].CheckFlag() == 0) {
                                tiles[j - 1][i].SetTile(1);
                            }
                        }
                        else if (j == 0 && i != 0 && j < numRows - 1 && i >= numColumns - 1) {

                            //Neighbor 4
                            if (tiles[j + 1][i].CheckBomb() == 0 && tiles[j + 1][i].CheckFlag() == 0) {
                                tiles[j + 1][i].SetTile(1);
                            }
                            //Neighbor 5
                            if (tiles[j + 1][i - 1].CheckBomb() == 0 && tiles[j + 1][i - 1].CheckFlag() == 0) {
                                tiles[j + 1][i - 1].SetTile(1);
                            }
                            //Neighbor 6
                            if (tiles[j][i - 1].CheckBomb() == 0 && tiles[j][i - 1].CheckFlag() == 0) {
                                tiles[j][i - 1].SetTile(1);
                            }
                        }
                        else if (j != 0 && i == 0 && j >= numRows - 1 && i < numColumns - 1) {
                            //Neighbor 1
                            if (tiles[j - 1][i + 1].CheckBomb() == 0 && tiles[j - 1][i + 1].CheckFlag() == 0) {
                                tiles[j - 1][i + 1].SetTile(1);
                            }
                            //Neighbor 2
                            if (tiles[j][i + 1].CheckBomb() == 0 && tiles[j][i + 1].CheckFlag() == 0) {
                                tiles[j][i + 1].SetTile(1);
                            }
                            //Neighbor 8
                            if (tiles[j - 1][i].CheckBomb() == 0 && tiles[j - 1][i].CheckFlag() == 0) {
                                tiles[j - 1][i].SetTile(1);
                            }
                        }




                    }
                    //todo make more if statements to check other of the tiles

                   
                    /*cout << winCount << endl;*/
                }
            }
            for (int y = 0; y < numColumns; ++y) {
                for (int z = 0; z < numRows; ++z) {
                    if (tiles[z][y].CheckTile() == 1) {
                        ++winCount;
                    }
                    if (winCount == winTiles) {
                        game = false;
                        win = true;
                        winCount = 0;
                    }
                    
                }
            }
            winCount = 0;
            window.display();

        }
    
}