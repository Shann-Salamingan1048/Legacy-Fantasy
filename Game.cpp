#include "Game.h"

void Game::initWindow()
{
	this->videoMode.height = 1200;
	this->videoMode.width = 2000;
	this->window = new sf::RenderWindow(this->videoMode, "Legacy Fantasy", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(80);
}
void Game::initVar()
{
	this->chosenPhase = 0;
}
Game::Game()
{
	this->initWindow();
}

Game::~Game() // destructor
{
	delete this->window;
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
            break;  // Exit the loop when the window is closed
        }
        else if (this->event.type == sf::Event::KeyReleased)
        {
            switch (this->event.key.code)
            {
            case sf::Keyboard::A:
            case sf::Keyboard::D:
            case sf::Keyboard::W:
            case sf::Keyboard::S:
            case sf::Keyboard::Space:
                this->movementsPlayer.x = 0.f;
                this->movementsPlayer.y = 0.f;
                this->chosenPhase = 0; // Set to idle when a movement key is released
                break;
            }
        }
        else if (this->event.type == sf::Event::KeyPressed)
        {
            switch (this->event.key.code)
            {
            case sf::Keyboard::A: // face and move to the left
                this->player.scalePlayer_x = -this->player.scaleValue;
                this->player.scalePlayer_y = this->player.scaleValue;
                this->movementsPlayer.x = -15.f;
                this->movementsPlayer.y = 0.f;
                this->chosenPhase = 1;
                break;
            case sf::Keyboard::D: // face and move to the right
                this->player.scalePlayer_x = this->player.scaleValue;
                this->player.scalePlayer_y = this->player.scaleValue;
                this->movementsPlayer.x = 15.f;
                this->movementsPlayer.y = 0.f;
                this->chosenPhase = 1;
                break;
            case sf::Keyboard::W: // Jump
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
                {
                    if (!this->player.isJump)
                    {
                        this->player.isJump = true;
                        this->player.isNegaScale_X = (this->player.scalePlayer_x < 0) ? -1.f : 1.f;
                        this->player.scalePlayer_x = this->player.scaleValue * this->player.isNegaScale_X;
                        this->player.scalePlayer_y = this->player.scaleValue;
                        this->movementsPlayer.y = -35.f;
                        this->chosenPhase = 3;
                    }
                    // Handle horizontal movement
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        this->movementsPlayer.x = 15.f;                   
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        this->movementsPlayer.x = -15.f;                       
                }
                break;
            case sf::Keyboard::Space: // Attack
                    this->player.isNegaScale_X = (this->player.scalePlayer_x < 0) ? -1.f : 1.f;
                    this->player.scalePlayer_x = this->player.scaleValue * this->player.isNegaScale_X;
                    this->player.scalePlayer_y = this->player.scaleValue;
                    this->chosenPhase = 2;     
                break;
            }
        }
        this->player.setScale(this->player.scalePlayer_x, this->player.scalePlayer_y);
    }
}
void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
    this->player.updatePlayer(this->chosenPhase, this->movementsPlayer, *this->window, this->videoMode); // jari na ang clear og display lol
}
