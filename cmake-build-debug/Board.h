#include <random>
#include <vector>
#include <map>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include "Tile.h"
using namespace std;

class Board {

public:
    Sprite digitsSprite = Sprite(TextureManager::GetTexture("digits"));
    Sprite counter1Sprite;
    Sprite counter2Sprite;
    Sprite counter3Sprite;

    int numMines2, numCol2, numRow2;
    int gameOver = 0; //0 - happy/default, 1 - lose, 2 - win
    bool debugMode = false;
    int flagCount = 0;
    int numFlags = 0;
    bool isLose = false;
    int numFlagsOnMines = 0; //whenever there is a flag clicked on a mine tile ++
    bool revealMode = false;

    Board();
    Board(int numRow, int numCol, int numMines);
    void randMines();
    void setTilePtrs();
    void RecursiveReveal( int j, int k);
    void newGameMode(string test);
    void readFiles(string fileName);
    void setCounter(RenderWindow& window);
    vector<vector<Tile>> tileBoard;
};
