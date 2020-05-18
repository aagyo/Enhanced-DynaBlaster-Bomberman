#include "Explosion.h"

Explosion::Explosion(const sf::Vector2f& bombPosition, const uint16_t radius, Map* map) :
	m_explosionShape(sf::Vector2f(m_tileSize, m_tileSize)), m_center(bombPosition), m_radius(radius), m_map(map)
{
	m_explosionTexture.loadFromFile("../_external/sprites/explosion.png");
	m_explosionTexture.setSmooth(true);
	m_explosionShape.setTexture(&m_explosionTexture);
	m_posFrequency.fill(0);

	m_direction.firstState = sf::IntRect(0, static_cast<int>(m_tileSize) * 3, static_cast<int>(m_tileSize), static_cast<int>(m_tileSize));
	m_direction.secondState = sf::IntRect(0, static_cast<int>(m_tileSize) * 2, static_cast<int>(m_tileSize), static_cast<int>(m_tileSize));
	m_direction.thirdState = sf::IntRect(0, static_cast<int>(m_tileSize), static_cast<int>(m_tileSize), static_cast<int>(m_tileSize));
	m_direction.finalState = sf::IntRect(0, 0, static_cast<int>(m_tileSize), static_cast<int>(m_tileSize));

	if (m_center.x / m_tileSize != 0 && m_center.y / m_tileSize != 0)
	{
		PlaceExplosion();
	}
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
				{
					m_map->ExplosionMarker(downCopy[0]);
				}

				downCopy.erase(downCopy.begin());
			}
			else if (!rightCopy.empty())
			{
				m_explosionShape.setPosition(rightCopy[0]);
				m_explosionShape.setTextureRect(it);
				Draw(window);

				if (m_fireBlockMark == false)
				{
					m_map->ExplosionMarker(rightCopy[0]);
				}

				rightCopy.erase(rightCopy.begin());
			}
			else if (!leftCopy.empty())
			{
				m_explosionShape.setPosition(leftCopy[0]);
				m_explosionShape.setTextureRect(it);
				Draw(window);

				if (m_fireBlockMark == false)
				{
					m_map->ExplosionMarker(leftCopy[0]);
				}
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

	const uint16_t stateFinish = 4;
	
	if (m_currentState >= stateFinish)
	{
		m_explosionNotFinished = false;
	}
}

void Explosion::Draw(sf::RenderWindow& window)
{
	window.draw(m_explosionShape);
}

sf::RectangleShape Explosion::GetExplosionShape()
{
	return m_explosionShape;
}

bool Explosion::GetExplosionState()
{
	return m_explosionNotFinished;
}

void Explosion::PlaceExplosion()
{
	const uint16_t tileDir = 17;
	const uint16_t indexBomb = static_cast<uint16_t>((m_center.y / m_tileSize) * static_cast<float>(tileDir) + m_center.x / m_tileSize);

	bool flagLeft = false, flagRight = false;
	bool stoneBlockLeft = false, stoneBlockRight = false, stoneBlockUp = false, stoneBlockDown = false;
	
	for (uint16_t indexBlock = 1; indexBlock <= m_radius; indexBlock++)
	{
		if (indexBlock >= 1 && flagLeft == false && stoneBlockLeft == false &&
			m_map->GetBlock(indexBomb - indexBlock).GetBlockType() != EBlockType::BorderBlock &&
			m_map->GetBlock(indexBomb - indexBlock).GetBlockType() != EBlockType::WallBlock)
		{
			if (m_map->GetBlock(indexBomb - indexBlock).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockLeft = true;
			}
			else if (m_map->GetBlock(indexBomb - indexBlock).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(indexBomb - indexBlock).GetPosition());
			}

			m_posFrequency[0]++;
			m_blockOnDir.left.push_back(m_map->GetBlock(indexBomb - indexBlock).GetPosition());
		}

		else
		{
			flagLeft = true;
		}

		if (indexBlock >= 1 && flagRight == false && stoneBlockRight == false &&
			m_map->GetBlock(indexBomb + indexBlock).GetBlockType() != EBlockType::BorderBlock &&
			m_map->GetBlock(indexBomb + indexBlock).GetBlockType() != EBlockType::WallBlock)
		{
			if (m_map->GetBlock(indexBomb + indexBlock).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockRight = true;
			}
			else if (m_map->GetBlock(indexBomb + indexBlock).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(indexBomb + indexBlock).GetPosition());
			}
			m_posFrequency[1]++;
			m_blockOnDir.right.push_back(m_map->GetBlock(indexBomb + indexBlock).GetPosition());
		}
		
		else
		{
			flagRight = true;
		}
	}

	bool flagUp = false, flagDown = false;
	
	for (uint16_t indexBlock = tileDir; indexBlock <= m_radius * tileDir; indexBlock += tileDir)
	{
		if (indexBomb > indexBlock&& indexBlock >= tileDir && flagUp == false && stoneBlockUp == false &&
			m_map->GetBlock(indexBomb - indexBlock).GetBlockType() != EBlockType::WallBlock &&
			m_map->GetBlock(indexBomb - indexBlock).GetBlockType() != EBlockType::BorderBlock)
		{
			if (m_map->GetBlock(indexBomb - indexBlock).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockUp = true;
			}
			else if (m_map->GetBlock(indexBomb - indexBlock).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(indexBomb - indexBlock).GetPosition());
			}
			m_posFrequency[2]++;
			m_blockOnDir.up.push_back(m_map->GetBlock(indexBomb - indexBlock).GetPosition());
		}
		else
		{
			flagUp = true;
		}

		if (indexBlock >= tileDir && flagDown == false && stoneBlockDown == false &&
			m_map->GetBlock(indexBomb + indexBlock).GetBlockType() != EBlockType::WallBlock &&
			m_map->GetBlock(indexBomb + indexBlock).GetBlockType() != EBlockType::BorderBlock)
		{
			if (m_map->GetBlock(indexBomb + indexBlock).GetBlockType() == EBlockType::StoneBlock)
			{
				stoneBlockDown = true;
			}
			else if (m_map->GetBlock(indexBomb + indexBlock).GetBlockType() != EBlockType::PortalBlock)
			{
				m_emptyBlocksLocation.push_back(m_map->GetBlock(indexBomb + indexBlock).GetPosition());
			}
			m_posFrequency[3]++;
			m_blockOnDir.down.push_back(m_map->GetBlock(indexBomb + indexBlock).GetPosition());
		}
		else
		{
			flagDown = true;
		}
	}
	
	m_animationComponents.animation = Animation(m_direction.firstState, m_numberOfFrames);
	m_animationComponents.frameDuration = 0.5f / static_cast<float>(m_numberOfFrames);
}