#include <random>
#include <vector>
#include <map>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Board.h"
#include "Random.h"
using namespace std;

void Board::randMines() {
    int uniqueMine = 0;
    while (uniqueMine < 50) {
        int y = Random::Int(0, numCol2 - 1);
        int x = Random::Int(0, numRow2 - 1);
        if(!tileBoard[x][y].isMine) {
            this->tileBoard[x][y].isMine = true;
            uniqueMine++;
        }
    }
}

void Board::setTilePtrs(){
    for (int r = 0; r < numRow2; r++) {
        for (int c = 0; c < numCol2; c++) {
            int adjMine = 0;
            if(!tileBoard[r][c].isMine){
                if(!((r-1) < 0)){ //!top row (cannot have a pointer above)
                    if(tileBoard[r-1][c].isMine){
                        tileBoard[r][c].setAbove(true);
                        adjMine++;
                    }
                }
                if((r+1) != numRow2){
                    if(tileBoard[r+1][c].isMine) {
                        tileBoard[r][c].setBelow(true);
                        adjMine++;
                    }
                }
                if(!((c-1) < 0)){
                    if(tileBoard[r][c-1].isMine){
                        tileBoard[r][c].setLeft(true);
                        adjMine++;
                    }
                }
                if((r+1) != numCol2){
                    if(tileBoard[r][c+1].isMine){
                        tileBoard[r][c].setRight(true);
                        adjMine++;
                    }
                }
                if(!((r-1) < 0) && (c+1) != numCol2) {
                    if (tileBoard[r-1][c+1].isMine) {
                        tileBoard[r][c].setTopRight(true);
                        adjMine++;
                    }
                }
                if(!((r-1) < 0) && !((c-1) < 0)) {
                    if (tileBoard[r-1][c-1].isMine) {
                        tileBoard[r][c].setTopLeft(true);
                        adjMine++;
                    }
                }
                if((r+1) != numRow2 && (c+1) != numCol2) {
                    if (tileBoard[r+1][c+1].isMine) {
                        tileBoard[r][c].setBottomRight(true);
                        adjMine++;
                    }
                }
                if((r+1) != numRow2 && !((c-1) < 0)) {
                    if (tileBoard[r+1][c-1].isMine) {
                        tileBoard[r][c].setBottomLeft(true);
                        adjMine++;
                    }
                }
            }
            tileBoard[r][c].setTileNumber(adjMine);
        }
    }
}

void Board::RecursiveReveal(int j, int k){
            if (!tileBoard[j][k].isRevealed && !tileBoard[j][k].isFlag && !tileBoard[j][k].isMine){
                tileBoard[j][k].isRevealed = true;

                if(tileBoard[j][k].getTileNum() == 0){ // no # with a mine nearby
                    if(!(j-1) < 0){ //!top row
                        RecursiveReveal(j - 1, k);
                    }
                    if((j+1) < numRow2){
                        RecursiveReveal( j + 1, k);
                    }
                    if(!((k-1) < 0)){
                        RecursiveReveal( j , k - 1);
                    }
                    if((k+1) < numCol2){
                        RecursiveReveal( j , k + 1);
                    }
                    if(!((j-1) < 0) && (k+1) < numCol2) {
                        RecursiveReveal( j - 1, k + 1);
                    }
                    if(!((j-1) < 0) && !((k-1) < 0)) {
                        RecursiveReveal( j - 1, k - 1);
                    }
                    if((j+1) < numRow2 && (k+1) < numCol2) {
                        RecursiveReveal( j + 1, k + 1);

                    }
                    if((j+1) < numRow2 && !((k-1) < 0)) {
                        RecursiveReveal(j + 1, k - 1);

                    }

                }

    }
}

void Board::setCounter(RenderWindow& window){
    int remainingMines = numMines2 - flagCount;
    //cout << numMines2 - flagCount;
    int positive;
    if(remainingMines < 0){
        positive = remainingMines * -1;
    }
    if(remainingMines >= 0){ //if non-negative
        counter1Sprite = Sprite(TextureManager::GetTexture("digits"));
        counter1Sprite.setPosition(40, 512);
        counter1Sprite.setTextureRect(IntRect(21 * (remainingMines % 10), 0, 21, 32));

        counter2Sprite = Sprite(TextureManager::GetTexture("digits"));
        counter2Sprite.setPosition(20, 512);
        counter2Sprite.setTextureRect(IntRect(21 * (remainingMines / 10), 0, 21, 32));

        counter3Sprite = Sprite(TextureManager::GetTexture("digits"));
        counter3Sprite.setPosition(0, 512);
        counter3Sprite.setTextureRect(IntRect(21 * (remainingMines / 100), 0, 21, 32));
        
    }
    else{
        int absRemainingMines = abs(remainingMines);
        counter1Sprite.setTextureRect(IntRect(21 * (absRemainingMines % 10), 0, 21, 32));
        counter2Sprite.setTextureRect(IntRect(21 * (absRemainingMines / 10), 0, 21, 32));
        counter3Sprite.setTextureRect(IntRect(208, 0, 21, 32));
    }
    window.draw(counter1Sprite);
    window.draw(counter2Sprite);
    window.draw(counter3Sprite);

}

Board::Board(){

}


Board::Board(int numRow2, int numCol2, int numMines2){
    this->numRow2 = numRow2;
    this->numCol2 = numCol2;
    this->numMines2 = numMines2;
    gameOver = 0;
    for(int r = 0; r < numRow2; r++) {
        vector<Tile> t;
        for (int c = 0; c < numCol2; c++) {
            Tile tempTile;
            t.push_back(tempTile);
        }
        tileBoard.push_back(t);
    }
    randMines();
    setTilePtrs();
    //setCounter();
}

void Board::readFiles(string fileName){
    this->tileBoard.clear();
    numMines2 = 0;
    vector<string> boolData; //store each line from the testboard file
    ifstream file2(fileName);
    if(file2.is_open() ){
        string s;
        while(getline(file2,s)){
            boolData.push_back(s);
        }
    }
    vector<Tile> tempRow;

    for(int r = 0; r < numRow2; r++){
        for(int c = 0; c < numCol2; c++){
            Tile addingTile(r,c);
            if(boolData[r].at(c) == '1'){ //check if mine is true or not
                addingTile.isMine = true;
                numMines2++;
            }
            tempRow.push_back(addingTile);

        }
        this->tileBoard.push_back(tempRow); //push rows into the tile board
        tempRow.clear();
    }
    setTilePtrs();
    //setCounter();

    // use for test 2/3
}

void Board::newGameMode(string test){
//reset board and game tiles
    this->tileBoard.clear();
     gameOver = 0; //0 - happy/default, 1 - lose, 2 - win
     debugMode = false;
     isLose = false;
     numFlags = 0;
     revealMode = false;
    if (test == "NewGame"){
      //  randMines();
       // setTilePtrs();
    }
    else if(test == "Test1"){
        readFiles("boards/testboard1.brd");
    }
    else if(test == "Test2"){
        readFiles("boards/testboard2.brd");
    }
    else if(test == "Test3"){
        readFiles("boards/testboard3.brd");
    }
}
