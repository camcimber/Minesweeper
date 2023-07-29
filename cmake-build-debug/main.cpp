#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Board.h"
#include "TextureManager.h"
#include "Random.h"
using namespace std;
using namespace sf;



int main()
{
    //store board in main

    ifstream file;
    string numCol, numRow , numMines;
    int numCol2, numRow2 , numMines2;
    file.open("config.cfg");
    getline(file,numCol);
    numCol2 = stoi(numCol);
    getline(file,numRow);
    numRow2 = stoi(numRow);
    getline(file,numMines);
    numMines2 = stoi(numMines);

    int width, height, mineCount, tileCount;

    width = numCol2 * 32;
    height = (numRow2 * 32) + 100;
    mineCount = numMines2;
    tileCount = numCol2 * numRow2;

    file.close();


    //Make a sprite AND load its texture


    sf::Sprite faceLoseSprite(TextureManager::GetTexture("face_lose"));
    sf::Sprite faceWinSprite(TextureManager::GetTexture("face_win"));
    sf::Sprite flagSprite(TextureManager::GetTexture("flag"));
    sf::Sprite mineSprite(TextureManager::GetTexture("mine"));
    sf::Sprite number1Sprite(TextureManager::GetTexture("number_1"));
    sf::Sprite number2Sprite(TextureManager::GetTexture("number_2"));
    sf::Sprite number3Sprite(TextureManager::GetTexture("number_3"));
    sf::Sprite number4Sprite(TextureManager::GetTexture("number_4"));
    sf::Sprite number5Sprite(TextureManager::GetTexture("number_5"));
    sf::Sprite number6Sprite(TextureManager::GetTexture("number_6"));
    sf::Sprite number7Sprite(TextureManager::GetTexture("number_7"));
    sf::Sprite number8Sprite(TextureManager::GetTexture("number_8"));

    sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tileRevealedSprite(TextureManager::GetTexture("tile_revealed"));

    sf::Sprite test1Sprite(TextureManager::GetTexture("test_1"));
    test1Sprite.setPosition(sf::Vector2f( 608,(float)(height-100)));

    sf::Sprite test2Sprite(TextureManager::GetTexture("test_2"));
    test2Sprite.setPosition(sf::Vector2f(672,(float)(height - 100)));

    sf::Sprite test3Sprite(TextureManager::GetTexture("test_3"));
    test3Sprite.setPosition(sf::Vector2f(736,(float)(height - 100)));

    sf::Sprite faceHappySprite(TextureManager::GetTexture("face_happy"));
    faceHappySprite.setPosition(sf::Vector2f(416,(float)(height - 100)));

    sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
    debugSprite.setPosition(sf::Vector2f(544,(float)(height - 100)));

    Board board = Board(numRow2,numCol2,numMines2);

    sf::RenderWindow window(sf::VideoMode(width,height),"Minesweeper" );

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            auto coords = sf::Mouse::getPosition(window); // returns x and y
            //use to search in vector for exact tiles
            int x = coords.x / 32; // in terms of the x and y -> tile position, not pixel position
            int y = coords.y / 32;
            board.tileBoard[x][y];
            if(event.type == Event::MouseButtonPressed ){
              //  sf::Vector2f mousePos(sf::Mouse::getPosition(window)); // returns x and y
                if(event.mouseButton.button  == sf::Mouse::Left) {
                    //coord clicked -> turn into row and col -> divide by 32 -> use tile - check mine is there
                    //remove sprite or set = to hidden tile

                    cout << "the left button was pressed" << endl;
                    if(debugSprite.getGlobalBounds().contains(coords.x,coords.y)){
                        cout << "debug was clicked" << endl;
                        board.debugMode = !board.debugMode;

                    }
                    if(test1Sprite.getGlobalBounds().contains(coords.x,coords.y)){
                        cout << "test1 was clicked" << endl;
                        board.newGameMode("Test1");

                    }
                    if(test2Sprite.getGlobalBounds().contains(coords.x,coords.y)){
                        cout << "test2 was clicked" << endl;
                        board.newGameMode("Test2");

                    }
                    if(test3Sprite.getGlobalBounds().contains(coords.x,coords.y)){
                        cout << "test3 was clicked" << endl;
                        board.newGameMode("Test3");

                    }
                    //call recursive reveal inside this -> if i click
                    for (int r = 0; r < numRow2; r++) {
                        for (int c = 0; c < numCol2; c++) {

                            if (board.tileBoard[r][c].tileSprite.getGlobalBounds().contains(coords.x,coords.y) && (board.gameOver != 1)){
                                board.RecursiveReveal( r, c);

                                //if there !isflag = false and  ismine = true -> end game
                                if(!board.tileBoard[r][c].isFlag && board.tileBoard[r][c].isMine){
                                    board.gameOver = 1;
                                    board.debugMode = true;

                                }
//                                if(!board.tileBoard[r][c].isFlag && board.tileBoard[r][c].isMine){
//                                    board.gameOver = 2;
//                                }

                            }


                        }
                    }

                    if(faceHappySprite.getGlobalBounds().contains(coords.x, coords.y)){
                        //create a new game
                        board.gameOver = 0;
                        cout << "happy sprite was clicked" << endl;
                        board = Board(numRow2,numCol2,numMines2);

                        board.newGameMode("NewGame");
                    }


                }
                else if(event.mouseButton.button  == sf::Mouse::Right){ // checks if its a right click
                    cout << "the right button was pressed" << endl;
                    for (int r = 0; r < numRow2; r++) {
                        for (int c = 0; c < numCol2; c++) {
                            if (board.tileBoard[r][c].tileSprite.getGlobalBounds().contains(coords.x,coords.y) && (board.gameOver != 1)) { // find the tile that was right clicked
                                //if not a flag and right clicked -> make one
                                if (!board.tileBoard[r][c].isFlag && !board.tileBoard[r][c].isRevealed) {

                                    board.tileBoard[r][c].isFlag = true;
                                    board.tileBoard[r][c].flagCount++;
                                    board.flagCount++;

                                    if(board.tileBoard[r][c].isMine){
                                        board.numFlagsOnMines++;
                                        cout << board.numMines2 << " ";
                                        if(board.numFlagsOnMines == board.numMines2){ //set game equal to win
                                            board.gameOver = 2;
                                        }
                                    }
                                }
                                    //if it is a flag -> remove the flag and remove from flag count
                                else {
                                    board.tileBoard[r][c].isFlag = false;
                                    board.tileBoard[r][c].flagCount--;
                                    if(board.tileBoard[r][c].isMine){
                                        board.numFlagsOnMines--;
                                       // cout << board.numFlagsOnMines << endl;
                                    }

                                }
                                //board.setCounter(window,board.numFlagsOnMines);

                            }
                        }
                    }

                }

            }
            
        }
        window.clear();

        for(int r = 0; r < numRow2; r++){
            for(int c = 0; c < numCol2; c++){

                board.tileBoard[r][c].backTile.setPosition(c*32, r*32);
                window.draw(board.tileBoard[r][c].backTile);

                if(board.tileBoard[r][c].isMine){
                    board.tileBoard[r][c].mineSprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].mineSprite);
                }
                //draw digits -> check value of curr tile
                int tileNum = board.tileBoard[r][c].getTileNum();
                if(tileNum == 1){
                    board.tileBoard[r][c].number1Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number1Sprite);
                }
                else if(tileNum == 2){
                    board.tileBoard[r][c].number2Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number2Sprite);
                }
                else if(tileNum == 3){
                    board.tileBoard[r][c].number3Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number3Sprite);
                }
                else if(tileNum == 4){
                    board.tileBoard[r][c].number4Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number4Sprite);
                }
                else if(tileNum == 5){
                    board.tileBoard[r][c].number5Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number5Sprite);
                }
                else if(tileNum == 6){
                    board.tileBoard[r][c].number6Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number6Sprite);
                }
                else if(tileNum == 7){
                    board.tileBoard[r][c].number7Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number7Sprite);
                }
                else if(tileNum == 8){
                    board.tileBoard[r][c].number8Sprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].number8Sprite);
                }

                if(!board.tileBoard[r][c].isRevealed) {
                    board.tileBoard[r][c].tileSprite.setPosition(c * 32, r * 32);
                    window.draw(board.tileBoard[r][c].tileSprite);
                }

                if(board.tileBoard[r][c].isFlag && !board.tileBoard[r][c].isRevealed ){
                    board.tileBoard[r][c].flagSprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].flagSprite);
                }

                if((board.tileBoard[r][c].isMine && board.debugMode)){ //draw mine on top of it

                    board.tileBoard[r][c].mineSprite.setPosition(c*32, r*32);
                    window.draw(board.tileBoard[r][c].mineSprite);

                    //end the game here -> when the current tile is revealed and has mine
                    //check if debug mode is true -> then dont end the game
                    //if flag and on debug mode -> make disappear
                    //display numbers on debug mode
                }

                if (board.gameOver == 0){
                    faceHappySprite.setPosition(sf::Vector2f(416,(float)(height - 100)));
                    window.draw(faceHappySprite);
                }
                else if(board.gameOver == 1){ //user lost
                    faceLoseSprite.setPosition(sf::Vector2f(416,(float)(height - 100)));
                    window.draw(faceLoseSprite);
                    if (board.tileBoard[r][c].isMine)
                    board.tileBoard[r][c].isRevealed = true;


                }
                else if(board.gameOver == 2){ //user win
                    faceWinSprite.setPosition(sf::Vector2f(416,(float)(height - 100)));
                    window.draw(faceWinSprite);
                }

                board.setCounter(window);

                //for the flag counter
//                board.counter1Sprite = Sprite(TextureManager::GetTexture("digits"));
//                board.counter1Sprite.setTextureRect(sf::IntRect(21, 0, 21, 32));
//                board.counter1Sprite.setPosition(40, (float)(height - 100));
//                window.draw(board.counter1Sprite);
//
//                board.counter2Sprite = Sprite(TextureManager::GetTexture("digits"));
//                board.counter2Sprite.setTextureRect(sf::IntRect(102, 0, 21, 32));
//                board.counter2Sprite.setPosition(20, (float)(height - 100));
//                window.draw(board.counter2Sprite);
//
//                board.counter3Sprite = Sprite(TextureManager::GetTexture("digits"));
//                board.counter3Sprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
//                board.counter3Sprite.setPosition(0, (float)(height - 100));
//                window.draw(board.counter3Sprite);

            }
        }

        window.draw(debugSprite);

        window.draw(test1Sprite);
        window.draw(test2Sprite);
        window.draw(test3Sprite);

        window.display();
    }

    //Clear out any textures before the program ends
    TextureManager::Clear();
    return 0;
}