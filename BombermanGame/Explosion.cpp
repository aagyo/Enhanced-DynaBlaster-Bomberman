#include "Explosion.h"
#include <array>


Explosion::Explosion(const sf::Vector2f& bombPosition, const uint16_t& radius, Map* map)
	:m_explosionShape(sf::Vector2f(48, 48)), m_center(bombPosition), m_radius(radius), m_map(map)
{
	m_explosionTexture.loadFromFile("../_external/sprites/explosionn.png");
	m_explosionTexture.setSmooth(true);
	m_explosionShape.setTexture(&m_explosionTexture);
	m_posFrequency.fill(0);

	m_direction.firstState = sf::IntRect(0, 144, 48, 48);
	m_direction.secondState = sf::IntRect(0, 96, 48, 48);
	m_direction.thirdState = sf::IntRect(0, 48, 48, 48);
	m_direction.finalState = sf::IntRect(0, 0, 48, 48);

	if (m_center.x / 48 != 0 && m_center.y / 48 != 0)
		PlaceExplosion();
}

void Explosion::Update(float deltaTime, sf::RenderWindow& window)
{
	switch (m_animationComponents.animation.GetCurrentExplosionFrame())
	{
	case 0:
		m_animationComponents.animation.SetFirstFrame(m_direction.firstState);
		m_animationComponents.animation.SetFrame(m_direction.firstState);
		m_explosionShape.setTextureRect(m_animationComponents.animation.GetFrame());
		break;
	case 1:
		m_animationComponents.animation.SetFirstFrame(m_direction.secondState);
		m_animationComponents.animation.SetFrame(m_direction.secondState);
		m_explosionShape.setTextureRect(m_animationComponents.animation.GetFrame());
		break;
	case 2:
		m_animationComponents.animation.SetFirstFrame(m_direction.thirdState);
		m_animationComponents.animation.SetFrame(m_direction.thirdState);
		m_explosionShape.setTextureRect(m_animationComponents.animation.GetFrame());
		break;
	case 3:
		m_animationComponents.animation.SetFirstFrame(m_direction.finalState);
		m_animationComponents.animation.SetFrame(m_direction.finalState);
		m_explosionShape.setTextureRect(m_animationComponents.animation.GetFrame());
		break;
	default:
		break;
	}

	if (m_currentState == m_animationComponents.animation.GetCurrentExplosionFrame())
	{
		m_explosionShape.setPosition(m_center);
		m_explosionShape.setTextureRect(m_animationComponents.animation.GetFrame());
		Draw(window);

		std::vector<sf::IntRect> exFr = m_animationComponents.animation.GetExplosionsFrames(m_posFrequency, m_radius);

		std::vector<sf::Vector2f> upCopy = m_blockOnDir.up;
		std::vector<sf::Vector2f> downCopy = m_blockOnDir.down;
		std::vector<sf::Vector2f> rightCopy = m_blockOnDir.right;
		std::vector<sf::Vector2f> leftCopy = m_blockOnDir.left;

		for (auto& it : exFr)
		{
			if (!upCopy.empty())
			{
				m_explosionShape.setPosition(upCopy[0]);
				m_explosionShape.setTextureRect(it);
				Draw(window);
				if (m_fireBlockMark == false)
				{
					m_map->ExplosionMarker(upCopy[0]);
				}
				upCopy.erase(upCopy.begin());
			}
			else if (!downCopy.empty())
			{
				m_explosionShape.setPosition(downCopy[0]);
				m_explosionShape.setTextureRect(it);
				Draw(window);
				if (m_fireBlockMark == false)
					m_map->ExplosionMarker(downCopy[0]);
				downCopy.erase(downCopy.begin());
			}
			else if (!rightCopy.empty())
			{
				m_explosionShape.setPosition(rightCopy[0]);
				m_explosionShape.setTextureRect(it);
				Draw(window);
				if (m_fireBlockMark == false)
					m_map->ExplosionMarker(rightCopy[0]);
				rightCopy.erase(rightCopy.begin());
			}
			else if (!leftCopy.empty())
			{
				m_explosionShape.setPosition(leftCopy[0]);
				m_explosionShape.setTextureRect(it);
				Draw(window);
				if (m_fireBlockMark == false)
					m_map->ExplosionMarker(leftCopy[0]);
				leftCopy.erase(leftCopy.begin());
			}
		}
		if (upCopy.empty() && downCopy.empty() && leftCopy.empty() && rightCopy.empty())
		{
			m_map->ExplosionMarker(m_center);
			m_fireBlockMark = true;
		}
	}

	m_animationComponents.animation.UpdateExplosion(deltaTime, m_animationComponents.frameDuration);
	m_currentState = m_animationComponents.animation.GetCurrentExplosionFrame();

	//if (m_currentState == 2)
	//{
	//}
	if (m_currentState >= 4)
	{
		m_explosionNotFinished = false;
		/*m_map->ClearBlock(m_center);
		for (auto& iterator : m_emptyBlocksLocation)
			m_map->ClearBlock(iterator);*/
	}

}

void Explosion::Draw(sf::RenderWindow& window)
{
	window.draw(m_explosionShape);
}

sf::RectangleShape Explosion::GetExplosionShape() const
{
	return m_explosionShape;

}

bool Explosion::GetExplosionState() const
{
	return m_explosionNotFinished;
}

void Explosion::PlaceExplosion()
{
	uint16_t IndexBomba = (m_center.y / 48) * 17 + m_center.x / 48;

	bool flagLeft = false, flagRight = false;
	bool stoneBlockLeft = false, stoneBlockRight = false, stoneBlockUp = false, stoneBlockDown = false;
	for (uint16_t index = 1; index <= m_radius; index++)
	{
		if (index >= 1 && flagLeft == false && stoneBlockLeft == false &&
			m_map->GetBlock(IndexBomba - index).GetBlockType() != EBlockType::BorderBlock &&
			m_map->GetBlock(IndexBomba - index).GetBlockType() != EBlockType::WallBlock)
		{
			if (m_map->GetBlock(IndexBomba - index).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockLeft = true;
			}
			else if (m_map->GetBlock(IndexBomba - index).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(IndexBomba - index).GetPosition());
			}
			m_posFrequency[0]++;
			m_blockOnDir.left.push_back(m_map->GetBlock(IndexBomba - index).GetPosition());
		}
		else flagLeft = true;

		if (index >= 1 && flagRight == false && stoneBlockRight == false &&
			m_map->GetBlock(IndexBomba + index).GetBlockType() != EBlockType::BorderBlock &&
			m_map->GetBlock(IndexBomba + index).GetBlockType() != EBlockType::WallBlock)
		{
			if (m_map->GetBlock(IndexBomba + index).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockRight = true;
			}
			else if (m_map->GetBlock(IndexBomba + index).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(IndexBomba + index).GetPosition());
			}
			m_posFrequency[1]++;
			m_blockOnDir.right.push_back(m_map->GetBlock(IndexBomba + index).GetPosition());
		}
		else flagRight = true;
	}

	bool flagUp = false, flagDown = false;
	for (uint16_t index = 17; index <= m_radius * 17; index += 17)
	{
		if (IndexBomba > index&& index >= 17 && flagUp == false && stoneBlockUp == false &&
			m_map->GetBlock(IndexBomba - index).GetBlockType() != EBlockType::WallBlock &&
			m_map->GetBlock(IndexBomba - index).GetBlockType() != EBlockType::BorderBlock)
		{
			if (m_map->GetBlock(IndexBomba - index).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockUp = true;
			}
			else if (m_map->GetBlock(IndexBomba - index).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(IndexBomba - index).GetPosition());
			}
			m_posFrequency[2]++;
			m_blockOnDir.up.push_back(m_map->GetBlock(IndexBomba - index).GetPosition());
		}
		else flagUp = true;

		if (index >= 17 && flagDown == false && stoneBlockDown == false &&
			m_map->GetBlock(IndexBomba + index).GetBlockType() != EBlockType::WallBlock &&
			m_map->GetBlock(IndexBomba + index).GetBlockType() != EBlockType::BorderBlock)
		{
			if (m_map->GetBlock(IndexBomba + index).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockDown = true;
			}
			else if (m_map->GetBlock(IndexBomba + index).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(IndexBomba + index).GetPosition());
			}
			m_posFrequency[3]++;
			m_blockOnDir.down.push_back(m_map->GetBlock(IndexBomba + index).GetPosition());
		}
		else flagDown = true;
	}
	//m_emptyBlocksLocation.insert(m_emptyBlocksLocation.begin(), m_center);

	m_animationComponents.animation = Animation(m_direction.firstState, m_numberOfFrames);
	m_animationComponents.frameDuration = 0.5f / m_numberOfFrames;

}