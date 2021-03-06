/*	FIT2096 - Assignment 1 Sample Solution
*	GameBoard.h
*	Created by Mike Yeates - 2017 - Monash University
*	Generates the board and manages a collection of Tiles.
*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include "MeshManager.h"
#include "TextureManager.h"

class GameBoard
{
private:
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	Shader* m_tileShader;

	int MonsterCout = 5;

	// How many tiles does this board manage
	const static int BOARD_WIDTH = 20;
	const static int BOARD_HEIGHT = 20;

	// Storing tiles in a 2D array to make neighbour checking easier
	Tile* m_tiles[BOARD_HEIGHT][BOARD_WIDTH];

	void Generate();
	void AddWalls();
	//void GetRandomMonsterTilePosition();

public:
	GameBoard();
	GameBoard(MeshManager* meshManager, TextureManager* textureManager, Shader* tileShader);
	~GameBoard();

	void Update(float timestep);
	void Render(Direct3D* renderer, Camera* camera);

	void DeactivateTile(int x, int z);
	TileType GetTileTypeForPosition(int x, int z);
	Tile* GetRandomTileOfType(TileType type);

	void GetRandomMonsterTilePosition();

};

#endif

