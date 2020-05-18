#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& hitBoxBody);
	~Collider() = default;


	Collider(const Collider& other) = default;
	Collider(Collider && other) noexcept = default;
	Collider& operator=(const Collider & other) = default;
	Collider& operator=(Collider && other) noexcept = default;


public:
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetHalfSize() const;
	void MoveObject(float dx, float dy);
	bool CheckCollision(Collider& other);

private:
	sf::RectangleShape& m_objectHitBox;
};