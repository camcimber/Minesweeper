#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "TextureManager.h"
using namespace sf;
using namespace std;

class Tile {
public:
    Sprite tileSprite;
    Sprite backTile;
    Sprite flagSprite;
    Sprite mineSprite;
    Sprite number1Sprite;
    Sprite number2Sprite;
    Sprite number3Sprite;
    Sprite number4Sprite;
    Sprite number5Sprite;
    Sprite number6Sprite;
    Sprite number7Sprite;
    Sprite number8Sprite;
    bool isMine;
    bool isRevealed;
    bool isFlag;
    int adjMine, flagCount;
    int value;
    bool left;
    bool right;
    bool above;
    bool below;
    bool topRight;
    bool topLeft;
    bool bottomLeft;
    bool bottomRight;
    int row, col; //use for location of the sprite
    Tile(){
        number1Sprite = Sprite (TextureManager::GetTexture("number_1"));
        number2Sprite = Sprite (TextureManager::GetTexture("number_2"));
        number3Sprite = Sprite (TextureManager::GetTexture("number_3"));
        number4Sprite = Sprite (TextureManager::GetTexture("number_4"));
        number5Sprite = Sprite (TextureManager::GetTexture("number_5"));
        number6Sprite = Sprite (TextureManager::GetTexture("number_6"));
        number7Sprite = Sprite (TextureManager::GetTexture("number_7"));
        number8Sprite = Sprite (TextureManager::GetTexture("number_8"));
        flagSprite = Sprite (TextureManager::GetTexture("flag"));
        tileSprite = Sprite (TextureManager::GetTexture("tile_hidden"));
        backTile = Sprite (TextureManager::GetTexture("tile_revealed"));
        mineSprite = Sprite (TextureManager::GetTexture("mine"));

        isMine = false;
        isRevealed = false;
        isFlag = false;
        adjMine = 0;
        flagCount = 0;
        value = 0;
    }

    Tile(int row, int col){
        isMine = false;
        isRevealed = false;
        isFlag = false;
        adjMine = 0;
        flagCount = 0;
        value = 0;
        this->row = row;
        this->col = col;
        number1Sprite = Sprite (TextureManager::GetTexture("number_1"));
        number2Sprite = Sprite (TextureManager::GetTexture("number_2"));
        number3Sprite = Sprite (TextureManager::GetTexture("number_3"));
        number4Sprite = Sprite (TextureManager::GetTexture("number_4"));
        number5Sprite = Sprite (TextureManager::GetTexture("number_5"));
        number6Sprite = Sprite (TextureManager::GetTexture("number_6"));
        number7Sprite = Sprite (TextureManager::GetTexture("number_7"));
        number8Sprite = Sprite (TextureManager::GetTexture("number_8"));
        mineSprite = Sprite (TextureManager::GetTexture("mine"));
        flagSprite = Sprite (TextureManager::GetTexture("flag"));
        tileSprite = Sprite (TextureManager::GetTexture("tile_hidden"));
        backTile = Sprite (TextureManager::GetTexture("tile_revealed"));
        tileSprite.setPosition(32 * col, 32 * row);
    }
    void setPos(Sprite s){
        s.setPosition(32* col, 32* row);
    }
    void setSprite(Sprite s){
        tileSprite = s;
    }

    void setTileNumber(int num) {
        this->adjMine = num;
    }

    int getTileNum(){
        return adjMine;
    }
    void setLeft(bool left){
        this->left = left;
    }
    void setRight(bool right){
        this->right = right;
    }
    void setAbove(bool above){
        this->above = above;
    }
    void setBelow(bool below){
        this->below = below;
    }
    void setTopRight(bool topRight){
        this->topRight = topRight;
    }
    void setTopLeft(bool topLeft){
        this->topLeft = topLeft;
    }
    void setBottomLeft(bool bottomLeft){
        this->bottomLeft = bottomLeft;
    }
    void setBottomRight(bool bottomRight){
        this->bottomRight = bottomRight;
    }
};

