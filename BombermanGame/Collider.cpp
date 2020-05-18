#include "Collider.h"

Collider::Collider(sf::RectangleShape& hitBoxBody) : m_objectHitBox(hitBoxBody)
{
	// empty
}

sf::Vector2f Collider::GetPosition() const
{
	return m_objectHitBox.getPosition();
}

sf::Vector2f Collider::GetHalfSize() const
{
	return m_objectHitBox.getSize() / 2.0f;
}

void Collider::MoveObject(float dx, float dy)
{
	m_objectHitBox.move(dx, dy);
}

bool Collider::CheckCollision(Collider& other)
{
	sf::Vector2f halfSizeMyObject = GetHalfSize();
	sf::Vector2f halfSizeOtherObject = other.GetHalfSize();

	float deltaX = other.GetPosition().x - GetPosition().x;
	float deltaY = other.GetPosition().y - GetPosition().y;

	float intersectsX = abs(deltaX) - (halfSizeMyObject.x + halfSizeOtherObject.x);
	float intersectsY = abs(deltaY) - (halfSizeMyObject.y + halfSizeOtherObject.y);

	if (intersectsX < 0.0f && intersectsY < 0.0f)
	{
		if (intersectsX > intersectsY)
		{
			if (deltaX > 0.0f)
			{
				MoveObject(0.0f, 0.0f);
				other.MoveObject(-intersectsX, 0.0f);
			}
			else
			{
				MoveObject(0.0f, 0.0f);
				other.MoveObject(intersectsX, 0.0f);
			}

			if (deltaY < 0.f)
			{
				other.MoveObject(0.0f, -1.0f);
			}
			else
			{
				other.MoveObject(0.0f, 1.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				MoveObject(0.0f, 0.0f);
				other.MoveObject(0.0f, -intersectsY);
			}
			else
			{
				MoveObject(0.0f, 0.0f);
				other.MoveObject(0.0f, intersectsY);
			}

			if (deltaX < 0.f)
			{
				other.MoveObject(-1.0, -0.0f);
			}
			else
			{
				other.MoveObject(1.0f, 0.0f);
			}
		}
	}

	return false;
}