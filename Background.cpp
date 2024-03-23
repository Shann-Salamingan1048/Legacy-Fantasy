#include "Background.h"

void Background::initTrees()
{
	// Golden Trees
	this->Gold_Tree_Texture.loadFromFile("Pictures/Trees/Golden-Tree.png");
	this->Gold_Tree_Sprite.setTexture(this->Gold_Tree_Texture); 
	this->Gold_Tree_Sprite.setTextureRect(sf::IntRect(0,0, 110,380));
	sf::Rect<float> size = this->Gold_Tree_Sprite.getGlobalBounds();
	this->Gold_Tree_Sprite.setOrigin(size.width / 2, size.height / 2);
	this->Gold_Tree_Sprite.setScale(2.f, 2.f);

	sf::Sprite Golden_Tree1 = this->Gold_Tree_Sprite;
	sf::Sprite Golden_Tree2 = this->Gold_Tree_Sprite;
	sf::Sprite Golden_Tree3 = this->Gold_Tree_Sprite;
	Golden_Tree1.setPosition(600, 600);
	Golden_Tree2.setPosition(700, 600);
	Golden_Tree3.setPosition(800, 600);

	this->golden_Trees_V.push_back(Golden_Tree1);
	this->golden_Trees_V.push_back(Golden_Tree2);
	this->golden_Trees_V.push_back(Golden_Tree3);
	
}

void Background::initTiles()
{
	this->Tiles.loadFromFile("Pictures/Assets/Tiles.png");
	this->Tiles_Sprite.setTexture(this->Tiles);
}
void Background::initTileMap()
{
	this->tiles_V = {
		{0,0,0,1,1,2,1,2,1},
		{2,2,1,2,2,1}
	};
}
Background::Background()
{
	this->initTileMap();
	this->initTrees();
	this->initTiles();
}

void Background::renderBackground(sf::RenderWindow& window)
{
	for(const auto& tree : this->golden_Trees_V)
		window.draw(tree);
	for (uint8_t y = 0; y < this->tiles_V.size(); y++)
	{
		for (uint8_t x = 0; x < this->tiles_V[y].size(); x++)
		{
			if (this->tiles_V[y][x] != 0)
			{
				if (this->tiles_V[y][x] == 1)
				{
					this->Tiles_Sprite.setTextureRect(sf::IntRect(0, 10, 80, 70));
				}
				else if (this->tiles_V[y][x] == 2)
				{
					this->Tiles_Sprite.setTextureRect(sf::IntRect(0, 90, 80, 70));
				}
				sf::Rect<float> size = this->Tiles_Sprite.getGlobalBounds();
				//this->Tiles_Sprite.setOrigin(size.width / 2, size.height / 2);
				this->Tiles_Sprite.setScale(3.f, 3.f);
				this->Tiles_Sprite.setPosition(static_cast<float>(x * 240),static_cast<float>(575 + (y * 400))); // x , y
				window.draw(this->Tiles_Sprite);
			}
		}
	}

}
