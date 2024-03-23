#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Background.h"
#include <iostream>
class Player {
private:
    Background bg;

    sf::Sprite player_Sprite;
    sf::Texture player_Idle;
    sf::Texture player_Run;
    sf::Texture player_Attack;
    sf::Texture player_Jump;

    std::vector<uint16_t> animationDelay;
    std::vector<sf::Texture> vector_Animations;
    std::vector<uint16_t> frameWidths;
    std::vector<uint8_t> phase_Animate;
    std::vector<uint8_t> framesV;
    std::vector<uint16_t> framesHeight;
    void loopFrame(uint8_t& choosePhase_animation);
    void legalMoves(sf::Vector2f& movePlayerPos, sf::VideoMode& videoMode);
    const bool willLand(uint8_t& i, uint8_t& choosePhase_animation) const;
public:
    Player();
    void updatePlayer(uint8_t choosePhase_animation,sf::Vector2f& movementsPlayer, sf::RenderWindow& window, sf::VideoMode& vidMode);
    void setScale(float x, float y);
    bool isJump;

    float scalePlayer_x;
    float scalePlayer_y;
    const float scaleValue = 3.f;
    float isNegaScale_X;
};

