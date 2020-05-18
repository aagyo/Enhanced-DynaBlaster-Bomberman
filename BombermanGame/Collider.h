#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& hitBoxBody);
	~Collider() = default;

public:
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetHalfSize() const;
	void MoveObject(float dx, float dy);
	bool CheckCollision(Collider& other);

private:
	sf::RectangleShape& m_objectHitBox;
};