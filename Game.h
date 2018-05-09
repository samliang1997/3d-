/*	FIT2096 - Example Code
*	Game.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class is the heart of our game and is also where our game logic will reside
*	It contains the overall Update and Render method for the whole game
*	You should eventually split some game logic into other objects which Game will manage
*	Watch the size of this class - it can grow out of control very fast!
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "Camera.h"
#include "InputController.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "GameBoard.h"
#include "Player.h"
#include "Monster.h"
#include "Health.h"
#include <vector>

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"

using namespace std;

class Game
{
private:
	Direct3D* m_renderer;
	InputController* m_input;
	Camera* m_currentCam;		
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;

	Shader* m_diffuseTexturedShader;

	//Sprites /Fonts/new add
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_arialFont12;
	SpriteFont* m_arialFont18;

	wstring m_scoreText;
	wstring m_healthText;

	Texture* m_currentItemSprite;

	// Our game data. The Game class only needs to manage three objects for this game.
	GameBoard* m_gameBoard;
	Player* m_player;
	vector<Monster*> m_monster;
	vector<Health*> m_healCube;
	GameObject* m_movesRemainingBar;
	
	int monsterCout = 5;
	// Splitting initialisation up into several steps
	bool InitShaders();
	bool LoadMeshes();
	bool LoadTextures();
	void InitGameWorld();

	
	void LoadFonts();
	void InitUI();
	void DrawUI();
	void RefershUI();

	void CheckGameOver();

public:
	Game();	
	~Game();

	bool Initialise(Direct3D* renderer, InputController* input); //The initialise method will load all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();					//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn

	void Shutdown(); //Cleanup everything we initialised

};

#endif