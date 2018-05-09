#include "Health.h"
#include "MathsHelper.h"


Health::Health()
{
	m_gameBoard = NULL;
}


Health::~Health()
{
}

Health::Health(Mesh* mesh, Shader* shader, Texture* texture, GameBoard* board):GameObject(mesh, shader, texture, Vector3::Zero)
{
	m_gameBoard = board;
	TeleportToTileOfType(TileType::HEALTH);
}

void Health::TeleportToTileOfType(TileType type)
{
	Tile* destinationTile = m_gameBoard->GetRandomTileOfType(type);

	if (destinationTile)
	{
		// We need to set both the current position and the target
		// The only time the player remains still is when these two positions match
		m_targetposition = destinationTile->GetPosition();
		m_position = destinationTile->GetPosition();

		// Tiles start up in the sky and fall down. Ensure player starts on the ground.
		m_targetposition.y = 0.0f;
		m_position.y = 0.0f;
	}

}

void Health::Update(float timestep)
{
	//TeleportToTileOfType(TileType::HEALTH);
}