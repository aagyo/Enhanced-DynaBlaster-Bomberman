#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->totalTime = totalTime;
	totalTime = 0.f;
	currentImage.x = 0;

	uVRect.width = texture->getSize().x / float(imageCount.x);
	uVRect.height = texture->getSize().y / float(imageCount.y);
}

AnimationPlayer::~AnimationPlayer()
{
}

void AnimationPlayer::Update(int row, float deltaTime, bool faceRight)
{

	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= deltaTime)
	{
		totalTime -= 1;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;

		}
	}

	uVRect.top = currentImage.y * uVRect.height;

	if (faceRight)
	{
		uVRect.left = currentImage.x * uVRect.width;
		uVRect.width = abs(uVRect.width);
	}
	else
	{
		uVRect.left = (currentImage.x + 1) * abs(uVRect.width);
		uVRect.width = -abs(uVRect.width);
	}

}
