#pragma once
#include "SFML/Graphics.hpp"
class AnimationPlayer
{
public:

	AnimationPlayer() = default;
	AnimationPlayer(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	~AnimationPlayer();

	void Update(int row, float deltaTime, bool faceRight);

private:


public:
	sf::IntRect uVRect;

private:

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

};

