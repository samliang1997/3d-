#include "Monster.h"
#include "MathsHelper.h"

Monster::Monster()
{
	m_health = 100;
	m_skill = MathsHelper::RandomRange(3, 10);
	m_isAlive = true;
	m_gameBoard = NULL;
}

Monster::~Monster() {}

int Monster::Attack()
{
	// A monster's attack power is limited to its skill
	return MathsHelper::RandomRange(0, m_skill);
}

void Monster::BeHit(int amount)
{
	// "abs" keeps a value positive
	m_health -= abs(amount);

	if (m_health <= 0)
	{
		m_isAlive = false;
	}
}

Monster::Monster(Mesh* mesh, Shader* shader, Texture* texture, GameBoard* board):GameObject(mesh,shader,texture,Vector3::Zero)
{
	m_gameBoard = board;
	TeleportToTileOfType(TileType::MONSTER_VAR1);
	
}

void Monster::TeleportToTileOfType(TileType type)
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

void Monster::Update(float timestep)
{
	// m_objectToLookAt must be set as the player object when the game is initialised
	// directionToPlayer = the vector from the Enemy to the player
	// calculated using vector subtraction (see lecture notes for week 2)
	//Vector3 directionToPlayer = m_objectToLookAt->GetPosition() - m_position;
	// Normalize the vector to get a vector of unit length 
	//directionToPlayer.Normalize();
	// Calculate the angle the enemy should be facing
	// There are a couple of ways to do this, atan2 is fairly straightforward
	//m_rotX = atan2(directionToPlayer.x, directionToPlayer.z);

}