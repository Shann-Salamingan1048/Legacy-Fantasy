#include "Player.h"

Player::Player() {
    // Load textures
    this->player_Idle.loadFromFile("Pictures/Character/Idle/Idle-Sheet.png");
    this->player_Run.loadFromFile("Pictures/Character/Run/Run-Sheet.png");
    this->player_Attack.loadFromFile("Pictures/Character/Attack-01/Attack-01-Sheet.png");
    this->player_Jump.loadFromFile("Pictures/Character/Jump-All/Jump-All-Sheet.png");
    // Populate vector_Animations
    this->vector_Animations.push_back(this->player_Idle);
    this->vector_Animations.push_back(this->player_Run);
    this->vector_Animations.push_back(this->player_Attack);
    this->vector_Animations.push_back(this->player_Jump);
    // Initialize variables
    this->phase_Animate = {0, 0, 0, 0}; // Idle, Run, Attack, Jump
    this->animationDelay = { 80,30, 80,50};
    this->framesHeight = { 80,80,80,64 };
    this->frameWidths = {64, 80, 96, 64};
    this->framesV = {4, 8, 8, 14};
    this->isJump = false;

    // Initialize starting POV
    this->player_Sprite.setTexture(this->player_Idle);
    this->player_Sprite.setTextureRect(sf::IntRect(20, 14, 64, 64));
    sf::Rect<float> size = this->player_Sprite.getGlobalBounds();
    this->player_Sprite.setOrigin(size.width / 2, size.height / 2);
    this->player_Sprite.setPosition(100, 900);

    this->scalePlayer_x = this->scaleValue;
    this->scalePlayer_y = this->scaleValue;
    this->player_Sprite.setScale(this->scalePlayer_x, this->scalePlayer_y);
    this->isNegaScale_X = 0.f;
}

void Player::loopFrame(uint8_t& choosePhase_animation) {
        for (uint8_t i = 0; i < this->phase_Animate.size(); i++) {
            if (i != choosePhase_animation) {
                this->phase_Animate[i] = 0;
            }
        }
        if (choosePhase_animation == 2 and this->phase_Animate[choosePhase_animation] == 0) // ignore first frame sa Attack kay nag tindogay ra
            this->phase_Animate[choosePhase_animation] = 1;
        // Set the texture rect based on the current animation phase
        this->player_Sprite.setTextureRect(sf::IntRect(
            this->frameWidths[choosePhase_animation] * this->phase_Animate[choosePhase_animation],
            0,
            this->frameWidths[choosePhase_animation],
            this->framesHeight[choosePhase_animation]));
        // Increment the current animation phase
        this->phase_Animate[choosePhase_animation] = (this->phase_Animate[choosePhase_animation] + 1) % this->framesV[choosePhase_animation];
}
void Player::legalMoves(sf::Vector2f& movePlayerPos, sf::VideoMode& videoMode) { // check if it is outside of the screen
    sf::Vector2f intendedPlayerPosition = this->player_Sprite.getPosition() + movePlayerPos;

    // Check if the intended position is outside the bounds of the window except for the top
    if (intendedPlayerPosition.y < this->player_Sprite.getGlobalBounds().height / 2) {
        // If moving upwards, limit the movement to keep the player within the top boundary
        if (movePlayerPos.y < 0.f) {
            movePlayerPos.y = 0.f;
        }
    }
    else if (intendedPlayerPosition.y > videoMode.height - this->player_Sprite.getGlobalBounds().height / 3) { // bot
        if (movePlayerPos.y > 0.f) {
            movePlayerPos.y = 0.f;
        }
    }
    if (intendedPlayerPosition.x < this->player_Sprite.getGlobalBounds().width / 3) { // left
        if (movePlayerPos.x < 0.f) {
            movePlayerPos.x = 0.f;
        }
    }
    else if (intendedPlayerPosition.x > videoMode.width - this->player_Sprite.getGlobalBounds().width / 3) { // right
        if (movePlayerPos.x > 0.f) {
            movePlayerPos.x = 0.f;
        }
    }


}
const bool Player::willLand(uint8_t& i, uint8_t& choosePhase_animation) const
{
    return i == this->framesV[choosePhase_animation]/2;
}
void Player::updatePlayer(uint8_t choosePhase_animation, sf::Vector2f& movementsPlayer, sf::RenderWindow& window, sf::VideoMode& vidMode) {
    // Set the correct texture for the animation phase
    this->player_Sprite.setTexture(this->vector_Animations[choosePhase_animation]);
    
    if (this->isJump) {
        for (uint8_t i = 0; i < this->framesV[choosePhase_animation]; i++) 
        {
            if (willLand(i, choosePhase_animation))
                movementsPlayer.y = 35.f;
            legalMoves(movementsPlayer, vidMode);
            loopFrame(choosePhase_animation);
            this->player_Sprite.move(movementsPlayer);
            std::cout << "Height: " << this->player_Sprite.getGlobalBounds().height << ", Width: "
                << this->player_Sprite.getGlobalBounds().width << ", Y-Axis: " << movementsPlayer.y << std::endl;
            window.clear();
            this->bg.renderBackground(window);
            window.draw(this->player_Sprite); // Draw the player in each frame of the jump animation  
            window.display();
            sf::sleep(sf::milliseconds(this->animationDelay[choosePhase_animation]));
        }
        this->isJump = false;
    }
    else {
        legalMoves(movementsPlayer, vidMode);
        loopFrame(choosePhase_animation);
        this->player_Sprite.move(movementsPlayer);
        // Draw the player
        
        window.clear();
        this->bg.renderBackground(window);
        window.draw(this->player_Sprite); // Draw the player in each frame of the jump animation  
        window.display();
        sf::sleep(sf::milliseconds(this->animationDelay[choosePhase_animation]));
    }
}
void Player::setScale(float x, float y) {
    this->player_Sprite.setScale(x, y);
}
