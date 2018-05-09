#ifndef HEALTH_H
#define HEALTH_H

#include "GameObject.h"
#include "GameBoard.h"


class Health:public GameObject
{
public:
	Health();
	Health(Mesh* mesh, Shader* shader, Texture* texture, GameBoard* board);
	~Health();

	void Update(float timestep);


private:

	GameBoard* m_gameBoard;
	Vector3 m_targetposition;
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;

	void TeleportToTileOfType(TileType type);
};

#endif 