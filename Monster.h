/*	FIT2096 - Assignment 1 Sample Solution
*	Monster.h
*	Created by Mike Yeates - 2017 - Monash University
*	A simpe object which has a health, can attack, and can be hit.
*/

#ifndef MONSTER_H
#define MONSTER_H

#include "GameObject.h"
#include "GameBoard.h"
#include "Player.h"

class Monster:public GameObject
{
private:
	int m_health;
	int m_skill;
	bool m_isAlive;

	void TeleportToTileOfType(TileType type);

	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	GameBoard* m_gameBoard;

	Vector3 m_targetposition;


public:
	Monster();
	Monster(Mesh* mesh, Shader* shader, Texture* texture, GameBoard* board);
	~Monster();

	int Attack();
	void BeHit(int amount);

	bool IsAlive() { return m_isAlive; }
	int GetSkill() { return m_skill; }

	void Update(float timestep);

};

#endif