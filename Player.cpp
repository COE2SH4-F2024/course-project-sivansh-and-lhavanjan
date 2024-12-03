#include "Player.h"
#include "MacUILib.h"

int hasInput = 0;

// Constructor for Player class
Player::Player(GameMechs *thisGMRef, Food *thisFoodRef, int initialLength) {
    mainGameMechsRef = thisGMRef; // Initialize game mechanics reference
    foodRef = thisFoodRef; // Initialize food reference
    playerdirection = STOP; // Set initial player direction to STOP

    playerPosList = new objPosArrayList(); // Create a new objPosArrayList for player positions

    int startX = mainGameMechsRef->getBoardSizeX() / 2; // Calculate starting X position
    int startY = mainGameMechsRef->getBoardSizeY() / 2; // Calculate starting Y position

    // Initialize player position list with initial length
    for (int i = 0; i < initialLength; i++) {
        objPos segment(startX - i, startY, '@'); // Create a new segment
        playerPosList->insertHead(segment); // Insert segment at the head of the list
    }
}

// Copy constructor for Player class
Player::Player(const Player &a) {
    mainGameMechsRef = a.mainGameMechsRef; // Copy game mechanics reference
    foodRef = a.foodRef; // Copy food reference
    playerdirection = a.playerdirection; // Copy player direction

    playerPosList = new objPosArrayList(*a.playerPosList); // Copy player position list
}

// Assignment operator for Player class
Player &Player::operator=(const Player &a) {
    if (this != &a) { // Check for self-assignment
        this->mainGameMechsRef = a.mainGameMechsRef; // Copy game mechanics reference
        this->foodRef = a.foodRef; // Copy food reference
        this->playerdirection = a.playerdirection; // Copy player direction

        this->playerPosList = new objPosArrayList(*a.playerPosList); // Copy player position list
    }
    return *this; // Return the current object
}

// Destructor for Player class
Player::~Player() {
    delete playerPosList; // Deallocate memory for player position list
}

// Get the current player position list
objPosArrayList *Player::getPlayerPos() const {
    return playerPosList; // Return the player position list
}

// Update the player direction based on input
void Player::updatePlayerDir() {
    char input = mainGameMechsRef->getInput(); // Get input from game mechanics
    if (input != 0) { // Check if there is input
        switch (input) {
            case 'W':
            case 'w':
                if (playerdirection != DOWN) { // Check if current direction is not DOWN
                    playerdirection = UP; // Set direction to UP
                    hasInput = 1; // Set hasInput flag
                }
                break;
            case 'S':
            case 's':
                if (playerdirection != UP) { // Check if current direction is not UP
                    playerdirection = DOWN; // Set direction to DOWN
                    hasInput = 1; // Set hasInput flag
                }
                break;
            case 'A':
            case 'a':
                if (playerdirection != RIGHT) { // Check if current direction is not RIGHT
                    playerdirection = LEFT; // Set direction to LEFT
                    hasInput = 1; // Set hasInput flag
                }
                break;
            case 'D':
            case 'd':
                if (playerdirection != LEFT) { // Check if current direction is not LEFT
                    playerdirection = RIGHT; // Set direction to RIGHT
                    hasInput = 1; // Set hasInput flag
                }
                break;
            default:
                break;
        }
        input = 0; // Reset input
    }
}

// Move the player based on the current direction
void Player::movePlayer() {
    int maxWidth = (mainGameMechsRef->getBoardSizeX() - 1); // Get maximum width of the board
    int maxHeight = (mainGameMechsRef->getBoardSizeY() - 1); // Get maximum height of the board

    if (hasInput != 0) { // Check if there is input
        int newX = playerPosList->getHeadElement().pos->x; // Get current head X position
        int newY = playerPosList->getHeadElement().pos->y; // Get current head Y position

        // Update new position based on direction
        switch (playerdirection) {
            case UP:
                newY = (newY - 1 + maxHeight) % maxHeight; // Move up
                if (newY == 0) {
                    newY = maxHeight - 1; // Wrap around if necessary
                }
                break;
            case DOWN:
                newY = (newY + 1) % maxHeight; // Move down
                if (newY == 0) {
                    newY = 1; // Wrap around if necessary
                }
                break;
            case LEFT:
                newX = (newX - 1 + maxWidth) % maxWidth; // Move left
                if (newX == 0) {
                    newX = maxWidth - 1; // Wrap around if necessary
                }
                break;
            case RIGHT:
                newX = (newX + 1) % maxWidth; // Move right
                if (newX == 0) {
                    newX = 1; // Wrap around if necessary
                }
                break;
        }

        // Check for self-collision
        if (checkSelfCollision()) {
            mainGameMechsRef->setLoseFlag(); // Set lose flag
            mainGameMechsRef->setExitTrue(); // Exit game
            return;
        }

        // Check for food consumption
        if (checkFoodConsumption(foodRef)) {
            objPosArrayList *foodBucket = foodRef->getFoodBucket(); // Get food bucket
            objPos headPosition = objPos(newX, newY, '@'); // Create new head position

            // Check if head position matches any food position
            for (int i = 0; i < foodBucket->getSize(); i++) {
                objPos food = foodBucket->getElement(i);
                if (headPosition.pos->x == food.pos->x && headPosition.pos->y == food.pos->y) {
                    applySpecialFoodEffect(food.getSymbol()); // Apply special food effect
                    foodBucket->removeHead(); // Remove food from bucket
                    break;
                }
            }
            increasePlayerLength(newX, newY); // Increase player length
            foodRef->generateFood(playerPosList, 5); // Generate new food
        } else {
            increasePlayerLength(newX, newY); // Increase player length
            playerPosList->removeTail(); // Remove tail segment
        }
    }
}

// Control the speed of the player
void Player::speedControl() {
    // Set delay amount based on speed
    switch (mainGameMechsRef->getSpeed()) {
        case 1:
            mainGameMechsRef->setDelayAmount(150000);
            break;
        case 2:
            mainGameMechsRef->setDelayAmount(125000);
            break;
        case 3:
            mainGameMechsRef->setDelayAmount(100000);
            break;
        case 4:
            mainGameMechsRef->setDelayAmount(75000);
            break;
        case 5:
            mainGameMechsRef->setDelayAmount(50000);
            break;
        default:
            mainGameMechsRef->setDelayAmount(100000);
            break;
    }

    MacUILib_printf("Speed: %d, Delay: %d", mainGameMechsRef->getSpeed(), mainGameMechsRef->getDelayAmount()); // Print speed and delay
}

// Check if the player has consumed food
bool Player::checkFoodConsumption(Food *foodRef) {
    objPos headPosition = playerPosList->getHeadElement(); // Get head position
    objPosArrayList *foodBucket = foodRef->getFoodBucket(); // Get food bucket

    // Check if head position matches any food position
    for (int i = 0; i < foodBucket->getSize(); i++) {
        objPos food = foodBucket->getElement(i);
        if (headPosition.pos->x == food.pos->x && headPosition.pos->y == food.pos->y) {
            applySpecialFoodEffect(food.getSymbol()); // Apply special food effect
            foodBucket->removeHead(); // Remove food from bucket
            return true;
        }
    }

    return false; // No food consumed
}

// Increase the length of the player
void Player::increasePlayerLength(int newX, int newY) {
    objPos newSegment(newX, newY, '@'); // Create new segment
    playerPosList->insertHead(newSegment); // Insert new segment at the head
}

// Check if the player has collided with itself
bool Player::checkSelfCollision() {
    if (playerPosList->getSize() > 1) { // Check if player has more than one segment
        int headX = playerPosList->getHeadElement().pos->x; // Get head X position
        int headY = playerPosList->getHeadElement().pos->y; // Get head Y position

        // Check if head position matches any body segment position
        for (int i = 1; i < playerPosList->getSize(); i++) {
            int bodyX = playerPosList->getElement(i).pos->x;
            int bodyY = playerPosList->getElement(i).pos->y;

            if (headX == bodyX && headY == bodyY) {
                return true; // Collision detected
            }
        }
    }
    return false; // No collision
}

// Apply special effect based on food symbol
void Player::applySpecialFoodEffect(char foodSymbol) {
    switch (foodSymbol) {
        case '?':
            mainGameMechsRef->incrementScore(10); // Increment score by 10
            break;
        case 'o':
            mainGameMechsRef->incrementScore(1); // Increment score by 1
            break;
        default:
            break;
    }
}