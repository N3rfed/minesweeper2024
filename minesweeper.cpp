//
// Created by jaden on 11/18/2024.
//
#include "minesweeper.h"
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}


void runWelcomeScreen(int& columns, int& rows, int& width, int& height, int& mine_count) {
    // Welcome Window
    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper");
    sf::Color welcomeBackground(0, 0, 255);
    sf::Font font;
    font.loadFromFile("font.ttf");
    std::string nameInput;
    while(welcomeWindow.isOpen()) {
        welcomeWindow.clear(welcomeBackground);
        sf::Text welcomeText;
        sf::Text instructionText;
        sf::Text usernameText;
        sf::Event textEvent;

        welcomeText.setString("WELCOME TO MINESWEEPER!");
        instructionText.setString("Enter your name:");
        usernameText.setString("|");

        welcomeText.setFont(font);
        instructionText.setFont(font);
        usernameText.setFont(font);

        welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
        instructionText.setStyle(sf::Text::Bold);
        usernameText.setStyle(sf::Text::Bold);

        welcomeText.setCharacterSize(24);
        instructionText.setCharacterSize(20);
        usernameText.setCharacterSize(18);

        welcomeText.setFillColor(sf::Color(255,255,255));
        instructionText.setFillColor(sf::Color(255,255,255));
        usernameText.setFillColor(sf::Color(255,255,0));


        setText(welcomeText, (width / 2), float((height / 2) - 150));
        setText(instructionText, (width / 2), float((height / 2) - 75));
        // setText(usernameText, (width / 2), float((height / 2) - 45));

        while(welcomeWindow.pollEvent(textEvent)) {
            if(textEvent.type == sf::Event::Closed) {
                welcomeWindow.close();
            }

            if(textEvent.type == sf::Event::TextEntered) {
                if(textEvent.text.unicode < 128) {
                    if(textEvent.text.unicode == 8 && nameInput.size() != 0) {
                        nameInput.pop_back();
                    }
                    else if(textEvent.text.unicode == '\r' && nameInput.size() > 0) {
                        // close welcome window, open game window
                        Player currentPlayer("0", nameInput);
                        welcomeWindow.close();
                        runGameScreen(columns, rows, width, height, mine_count);
                        break;
                    }
                    else {
                        if(std::isalpha(textEvent.text.unicode) && nameInput.size() < 10) {
                            if(nameInput.size() == 0) {
                                nameInput += std::toupper(static_cast<char>(textEvent.text.unicode));
                            }
                            else if(nameInput.size() > 0) {
                                nameInput += std::tolower(static_cast<char>(textEvent.text.unicode));
                            }
                            else {
                                nameInput += static_cast<char>(textEvent.text.unicode);
                                std::cout << nameInput << " " << nameInput.size() << std::endl;
                            }
                        }
                    }
                }
            }
        }
        usernameText.setString(nameInput + '|');
        setText(usernameText, (width / 2), float((height / 2) - 45));

        // welcomeText.setString()
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(instructionText);
        welcomeWindow.draw(usernameText);
        welcomeWindow.display();
    }
}

void runGameScreen(int& columns, int& rows, int& width, int& height, int& mine_count) {
    // Variables
    bool isPaused = false;
    Button pauseButton;
    Button leaderboardButton;
    Button resetButton;
    Button debugButton;
    Board gameBoard(columns, rows, mine_count);

    // Game Window
    sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper");
    sf::Color gameBackground(255, 255, 255);

    // Game Textures
    sf::Texture gameTileTexture;
    sf::Texture happyFaceTexture;
    sf::Texture debugTexture;
    sf::Texture pauseTexture;
    sf::Texture leaderboardTexture;
    sf::Texture playTexture;
    sf::Texture revealedTileTexture;

    if(!gameTileTexture.loadFromFile("images/tile_hidden.png") ||
        !gameTileTexture.loadFromFile("images/tile_revealed.png") ||
        !happyFaceTexture.loadFromFile("images/face_happy.png") ||
        !debugTexture.loadFromFile("images/debug.png") ||
        !pauseTexture.loadFromFile("images/pause.png") ||
        !playTexture.loadFromFile("images/play.png") ||
        !leaderboardTexture.loadFromFile("images/leaderboard.png")) {
        std::cerr << "ERROR LOADING TILE_FILE" << std::endl;
    }
    sf::Sprite gameTileSprite;
    sf::Sprite happyFaceSprite;
    sf::Sprite debugSprite;
    sf::Sprite leaderboardSprite;
    sf::Sprite revealedTileSprite;



    gameTileSprite.setTexture(gameTileTexture);
    revealedTileSprite.setTexture(revealedTileTexture);
    resetButton.setBtnTexture(happyFaceTexture);
    resetButton.setBtnPosition((columns / 2.0 * 32) - 32, 32 * (rows + 0.5));
    debugButton.setBtnTexture(debugTexture);
    debugButton.setBtnPosition(columns * 32 - 304, 32 * (rows + 0.5));
    pauseButton.setBtnTexture(pauseTexture);
    pauseButton.setBtnPosition(columns * 32 - 240, 32 * (rows + 0.5));
    leaderboardButton.setBtnTexture(leaderboardTexture);
    leaderboardButton.setBtnPosition(columns * 32 - 176, 32 * (rows + 0.5));


    gameWindow.clear(gameBackground);
    gameBoard.fillBoard(rows, columns);
    gameBoard.numberBoard(rows, columns);
    gameBoard.printBoard(rows, columns);
    gameBoard.resetBoard(rows, columns);

    // for(int row = 0; row < rows; row++) {
    //     for(int col = 0; col < columns; col++) {
    //         revealedTileSprite.setPosition(col*32, row*32);
    //         gameWindow.draw(revealedTileSprite);
    //     }
    // }

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            Tile& gameTile = gameBoard.getBoardTile(row, col);
            gameTile.setPosition(col*32, row*32);
            gameWindow.draw(gameTile.getBackgroundSprite());
            gameWindow.draw(gameTile.getSprite());
        }
    }

    gameWindow.draw(resetButton.getSprite());
    gameWindow.draw(debugButton.getSprite());
    gameWindow.draw(pauseButton.getSprite());
    gameWindow.draw(leaderboardButton.getSprite());


    gameWindow.display();


    while(gameWindow.isOpen()) {
        gameWindow.draw(pauseButton.getSprite());
        sf::Event gameEvent;
        while(gameWindow.pollEvent(gameEvent)) {
            if(gameEvent.type == sf::Event::Closed) {
                gameWindow.close();
            }
            if(gameEvent.type == sf::Event::MouseButtonPressed) {
                if(pauseButton.isBtnPressed(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                    if (!isPaused) {
                        pauseButton.setBtnTexture(playTexture);
                        isPaused = true;
                    }

                    else if (isPaused) {
                        pauseButton.setBtnTexture(pauseTexture);
                        isPaused = false;
                    }
                    gameWindow.clear(gameBackground);
                    gameWindow.draw(pauseButton.getSprite());
                }
                if(resetButton.isBtnPressed(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                    gameBoard.resetBoard(rows, columns);
                    std::cout << "reset button pressed" << std::endl;
                }
                if(leaderboardButton.isBtnPressed(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                    std::cout << "leaderboard pressed" << std::endl;
                    leaderboardScreen(columns, rows);
                }
                if(debugButton.isBtnPressed(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                    gameBoard.debugBoard(rows, columns, 9);
                    std::cout << "debug pressed" << std::endl;
                }
                for(int row = 0; row < rows; row++) {
                    for(int col = 0; col < columns; col++) {
                        // Tile& gameTile = gameBoard.getBoardTile(row, col);
                        if(gameBoard.getBoardTile(row,col).isClicked(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                            gameBoard.revealTile(row,col);
                            std::cout << "Tile at position (" << row << "," << col << ") was clicked" << std::endl;
                        }
                        if(gameBoard.getBoardTile(row,col).isRightClicked(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                            if(!gameBoard.getBoardTile(row, col).isFlagged()) {
                                gameBoard.getBoardTile(row,col).flag();
                            }
                            else {
                                gameBoard.getBoardTile(row,col).unflag();
                            }
                            std::cout << "Tile at position (" << row << "," << col << ") was clicked" << std::endl;
                        }
                    }
                }

            }
        }
        gameWindow.clear(gameBackground);

        // for(int row = 0; row < rows; row++) {
        //     for(int col = 0; col < columns; col++) {
        //         revealedTileSprite.setPosition(col*32, row*32);
        //         gameWindow.draw(revealedTileSprite);
        //     }
        // }

        for(int row = 0; row < rows; row++) {
            for(int col = 0; col < columns; col++) {
                Tile& gameTile = gameBoard.getBoardTile(row, col);
                gameTile.setPosition(col*32, row*32);
                gameWindow.draw(gameTile.getBackgroundSprite());
                gameWindow.draw(gameTile.getSprite());
            }
        }

        gameWindow.draw(resetButton.getSprite());
        gameWindow.draw(debugButton.getSprite());
        gameWindow.draw(pauseButton.getSprite());
        gameWindow.draw(leaderboardButton.getSprite());


        gameWindow.display();

    }
}

void leaderboardScreen(int &columns, int &rows) {
    std::ifstream configFile("leaderboard.txt");
    std::ifstream fontFile("font.ttf");
    if (!configFile.is_open() || !fontFile.is_open()) {
        std::cerr << "Error opening file(s)" << std::endl;
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(configFile, line)) {
        lines.push_back(line);
    }
    std::string time = lines.at(0);
    std::string name = lines.at(1);

    sf::RenderWindow leaderboardWindow(sf::VideoMode((columns * 16), (rows * 16) + 50), "Minesweeper");
    sf::Color welcomeBackground(0, 0, 255);
    sf::Font font;
    font.loadFromFile("font.ttf");
    std::string nameInput;
    while(leaderboardWindow.isOpen()) {
        leaderboardWindow.clear(welcomeBackground);
        sf::Text leaderboardHeader;
        sf::Text contentText;
        sf::Event leaderboardTextEvent;

        leaderboardHeader.setString("LEADERBOARD");

        leaderboardHeader.setFont(font);

        leaderboardHeader.setStyle(sf::Text::Bold | sf::Text::Underlined);

        leaderboardHeader.setCharacterSize(20);

        leaderboardHeader.setFillColor(sf::Color(255,255,255));

        setText(leaderboardHeader, ((columns * 16) / 2), float(((rows * 16 + 50) / 2) - 120));

        while(leaderboardWindow.pollEvent(leaderboardTextEvent)) {
            if(leaderboardTextEvent.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
        leaderboardWindow.draw(leaderboardHeader);
        leaderboardWindow.display();

    }
}


// Button class implementation
void Button::setBtnPosition(float xPosition, float yPosition) {
    this->sprite.setPosition(xPosition,yPosition);
}

bool Button::isBtnPressed(float xPosition, float yPosition) {
    sf::FloatRect buttonClick = this->sprite.getGlobalBounds();
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(buttonClick.contains(xPosition, yPosition)) {
            return true;
        }
    }
    return false;
}
void Button::setBtnTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
}

sf::Sprite& Button::getSprite() {
    return this->sprite;
}

// Tile class implementation
void Tile::setTexture(sf::Texture &texture) {
    this->foregroundSprite.setTexture(texture);
}

void Tile::setBackgroundTexture(sf::Texture &texture) {
    this->backgroundSprite.setTexture(texture);
}

sf::Sprite& Tile::getSprite() {
    return this->foregroundSprite;
}

sf::Sprite &Tile::getBackgroundSprite() {
    return this->backgroundSprite;
}


void Tile::setTile(int type) {
    this->type = type;
    this->backgroundTexture.loadFromFile("images/tile_revealed.png");
    this->texture.loadFromFile("images/tile_hidden.png");
    this->foregroundSprite.setTexture(this->texture);
    this->backgroundSprite.setTexture(this->backgroundTexture);
}

int Tile::getTile() {
    return this->type;
}

bool Tile::isRevealed() {
    return this->shown;
}

bool Tile::isFlagged() {
    return this->flagged;
}

void Tile::reveal() {
    if(!isRevealed()) {
        shown = true;
        backgroundTexture.loadFromFile("images/tile_revealed.png");
        backgroundSprite.setTexture(backgroundTexture);
        switch(type) {
            case 0:
                texture.loadFromFile("images/tile_revealed.png");
                break;
            case 1:
                texture.loadFromFile("images/number_1.png");
                break;
            case 2:
                texture.loadFromFile("images/number_2.png");
                break;
            case 3:
                texture.loadFromFile("images/number_3.png");
                break;
            case 4:
                texture.loadFromFile("images/number_4.png");
                break;
            case 5:
                texture.loadFromFile("images/number_5.png");
                break;
            case 6:
                texture.loadFromFile("images/number_6.png");
                break;
            case 7:
                texture.loadFromFile("images/number_7.png");
                break;
            case 8:
                texture.loadFromFile("images/number_8.png");
                break;
            case 9:
                texture.loadFromFile("images/mine.png");
                break;
            default:
                break;
        }
        foregroundSprite.setTexture(texture);
    }
}
void Tile::hide() {
    this->shown = false;
    this->texture.loadFromFile("images/tile_hidden.png");
    this->foregroundSprite.setTexture(this->texture);
}


void Tile::flag() {
    if(!this->shown && !this->flagged) {
        flagged = true;
        backgroundTexture.loadFromFile("images/tile_hidden.png");
        texture.loadFromFile("images/flag.png");
        backgroundSprite.setTexture(backgroundTexture);
        foregroundSprite.setTexture(texture);
    }
}

void Tile::unflag() {
    if(!this->shown && this->flagged) {
        flagged = false;
        texture.loadFromFile("images/tile_hidden.png");
        foregroundSprite.setTexture(texture);
    }
}

void Tile::resetTile() {
    this->type = 0;
    this->shown = false;
    this->flagged = false;
}

void Tile::setPosition(float xPosition, float yPosition) {
    this->backgroundSprite.setPosition(xPosition, yPosition);
    this->foregroundSprite.setPosition(xPosition, yPosition);
}

bool Tile::isClicked(float mouseXPosition, float mouseYPosition) {
    sf::FloatRect tileClick = this->foregroundSprite.getGlobalBounds();
    if(!flagged) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(tileClick.contains(mouseXPosition, mouseYPosition)) {
                return true;
            }
        }
    }
    return false;
}

bool Tile::isRightClicked(float mouseXPosition, float mouseYPosition) {
    sf::FloatRect tileClick = this->foregroundSprite.getGlobalBounds();
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if(tileClick.contains(mouseXPosition, mouseYPosition)) {
            return true;
        }
    }
    return false;
}


const sf::Vector2f Tile::getPosition() {
    return foregroundSprite.getPosition();
}

void Tile::toggleDebug() {
    debug = !debug;
    if(debug) {
        backgroundTexture.loadFromFile("images/tile_hidden.png");
        backgroundSprite.setTexture(backgroundTexture);
        if (type == 9) {
            texture.loadFromFile("images/mine.png");
            foregroundSprite.setTexture(texture);
        }
    }
    else {
        if(type == 9) {
            if(flagged) {
                backgroundTexture.loadFromFile("images/tile_hidden.png");
                texture.loadFromFile("images/flag.png");
                backgroundSprite.setTexture(backgroundTexture);
                foregroundSprite.setTexture(texture);
            }
            else {
                texture.loadFromFile("images/tile_hidden.png");
                foregroundSprite.setTexture(texture);
            }
        }
    }
}


// Board class implementation
void Board::fillBoard(int rows, int columns) {
    // insert random placement
    int placedMines = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            if(tiles[row][col].getTile() != 9) {
                tiles[row][col].setTile(0);
            }
        }
    }
    while(placedMines < mines) {
        int row = std::rand() % rows;
        int col = std::rand() % columns;
        if(tiles[row][col].getTile() != 9) {
            tiles[row][col].setTile(9);
            placedMines++;
        }
    }
}

void Board::numberBoard(int rows, int columns) {
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            if(tiles[row][col].getTile() == 9) {
                continue;
            }
            int surroundingMines = 0;
            // assuming the current tile is (0,0), look at the surrounding tiles ranging from
            // -1 to 1 and checks if any of them are mines
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    int rowPos = row + i;
                    int colPos = col + j;
                    if(rowPos >= 0 && rowPos < rows && colPos >= 0 && colPos < columns) {
                        if(tiles[rowPos][colPos].getTile() == 9) {
                            surroundingMines++;
                        }
                    }
                }
            }
            tiles[row][col].setTile(surroundingMines);
        }
    }
}

void Board::revealBoard(int rows, int columns) {
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            tiles[row][col].reveal();
        }
    }
}

int Board::revealTile(int row, int col) {
    // Out of bounds, helps for recursive calls
    if(row < 0 || col < 0 || row >= height || col >= width) {
        return -1;
    }
    Tile& tile = tiles[row][col];
    // std::cout << "Tile at (" << row << ", " << col << ") has a number of " << tile.getTile() << std::endl;
    // std::cout << tile.isRevealed() << " is the current revealed state" << std::endl;

    if(tile.isRevealed()) {
        return tile.getTile();
    }
    tile.reveal();
    // std::cout << "Tile at (" << row << ", " << col << ") revealed\n"; // Debug line

    // Check if the revealed tile is a mine
    if(tile.getTile() == 9) {
        return -1;
    }
    // Recursively check other tiles
    if(tile.getTile() == 0) {
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                // check if i and j are 0, which it is the current tile so we should skip it
                if(i == 0 && j == 0) {
                    continue;
                }

                int rowPos = row + i;
                int colPos = col + j;
                // Out of bounds, helps for recursive calls
                if(rowPos < 0 || colPos < 0 || rowPos >= height || colPos >= width) {
                    continue;
                }
                revealTile(rowPos, colPos);
            }
        }
    }
    return tile.getTile();
}

void Board::resetBoard(int rows, int columns) {
    for(int row  = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            // std::cout << "tile at position (" << row << ", " << col << ") was reset" << std::endl;
            tiles[row][col].resetTile();
        }
    }
    fillBoard(rows, columns);
    numberBoard(rows, columns);
    printBoard(rows, columns);
}

void Board::endGame(int rows, int columns) {
    revealBoard(rows, columns);
}

void Board::printBoard(int rows, int columns) {
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            std::cout << tiles[row][col].getTile() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Tile& Board::getBoardTile(int rows, int columns) {
    return tiles[rows][columns];
}

void Board::debugBoard(int rows, int columns, int type) {
    static bool debugState = false;
    debugState = !debugState;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            type = tiles[row][col].getTile();
            if(type == 9) {
                tiles[row][col].toggleDebug();
            }
        }
    }
}


// Number class
