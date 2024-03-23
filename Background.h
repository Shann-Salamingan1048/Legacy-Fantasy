#pragma once
#include <SFML/Graphics.hpp>

class Background
{
private:
	sf::Texture Gold_Tree_Texture;
	sf::Sprite Gold_Tree_Sprite;
	std::vector<sf::Sprite> golden_Trees_V;
	sf::Texture Tiles;
	sf::Sprite Tiles_Sprite;
	
	void initTrees();
	void initTileMap();
	void initTiles();
public:
	Background();
	void renderBackground(sf::RenderWindow& window);
	std::vector<std::vector<uint8_t>> tiles_V;
};
