/*	FIT2096 - Assignment 1 Sample Solution
*	Game.h
*	Created by Mike Yeates - 2017 - Monash University
*/

#include "Game.h"
#include "TexturedShader.h"
#include "StaticObject.h"
#include <sstream>

#include"FirstPerson.h"
#include "DirectXTK/CommonStates.h"

Game::Game()
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_meshManager = NULL;
	m_textureManager = NULL;
	m_diffuseTexturedShader = NULL;
	m_gameBoard = NULL;
	m_movesRemainingBar = NULL;
	
	m_spriteBatch = NULL;
	m_arialFont18 = NULL;

}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;	
	m_input = input;
	m_meshManager = new MeshManager();
	m_textureManager = new TextureManager();
	
	m_currentCam = new FirstPerson(m_input,Vector3());
	

	if (!InitShaders())
		return false;

	if (!LoadMeshes())

		return false;

	if (!LoadTextures())
		return false;
	
	LoadFonts();
	InitUI();
	InitGameWorld();
	
	RefershUI();

	return true;
}

bool Game::InitShaders()
{
	m_diffuseTexturedShader = new TexturedShader();
	if (!m_diffuseTexturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
		return false;

	return true;
}

bool Game::LoadMeshes()
{
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/floor_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/wall_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/player_capsule.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/progress_cube.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/ground.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/bullet.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/ammoBlock.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/ruby.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/enemy.obj"))
		return false;

	return true;
}

bool Game::LoadTextures()
{
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_blue.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_disabled.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_green.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_orange.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_purple.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_white.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/ground.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_red.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redDarker.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redLighter.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redOrange.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redPink.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/bullet.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/sprite_healthBar.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/sprite_hurtOverlay.png"))
		return false;

	return true;
}

void Game::LoadFonts()
{
	m_arialFont12 = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-12pt.spritefont");
	m_arialFont18 = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-18pt.spritefont");
}

void Game::InitUI()
{
	m_spriteBatch = new SpriteBatch(m_renderer->GetDeviceContext());

}

void Game::RefershUI()
{
	// Ensure text in UI matches latest scores etc (call this after data changes)
	// Concatenate data into our label string using a wide string stream
	if (m_player)
	{
		std::wstringstream ss1;

		// Round to two decimal places for neater output
		ss1 << "Score is : " << floorf(m_player->GetScore() * 100) / 100;
		m_scoreText = ss1.str();

		std::wstringstream ss2;
		ss2 << " Player health is : " << floorf(m_player->GetHealth() * 100) / 100;
		m_healthText = ss2.str();
	}
}

void Game::InitGameWorld()
{	
	// A GameBoard creates the world layout and manages the Tiles.
	// We pass it the Mesh and Texture managers as it will be creating tiles and walls
	m_gameBoard = new GameBoard(m_meshManager, m_textureManager, m_diffuseTexturedShader);

	// The bar hovering above the player's head showing moves remaining.
	// This doesn't do anything on its own, so a StaticObject will be adequate.
	// Even though it does in fact move, it's told what to do by the Player and makes
	// no decisions on its own.
	m_movesRemainingBar = new StaticObject(m_meshManager->GetMesh("Assets/Meshes/progress_cube.obj"),
										   m_diffuseTexturedShader,
										   m_textureManager->GetTexture("Assets/Textures/tile_green.png"));


	// A player will select a random starting position.
	// We need to tell the player about the board it is standing on so it can validate movement
	// and ask the board what type of tile it is standing on.
	m_player = new Player(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
						  m_diffuseTexturedShader,
						  m_textureManager->GetTexture("Assets/Textures/tile_white.png"),
						  m_input,
						  m_gameBoard,
						  m_movesRemainingBar);

	for (int i = 0; i < 80; i++)
	{
		m_healCube.push_back(new Health(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/tile_green.png"),
			m_gameBoard));
	}
	m_monster.push_back(new Monster(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_red.png"),
			m_gameBoard));

	m_monster.push_back(new Monster(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
			m_gameBoard));

	m_monster.push_back(new Monster(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_redLighter.png"),
			m_gameBoard));

	m_monster.push_back(new Monster(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_redOrange.png"),
			m_gameBoard));

	m_monster.push_back(new Monster(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
			m_diffuseTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"),
			m_gameBoard));


}

void Game::Update(float timestep)
{
	// Look how short this function can be when we make objects responsible for their own logic.
	// Our only job out here is to Update the board and player, and check if the game is over.

	m_input->BeginUpdate();
	
	m_gameBoard->Update(timestep);

	m_player->Update(timestep);

	for (int i = 0; i < m_monster.size(); i++) 
	{
		m_monster[i]->Update(timestep);
	}

	for (int i = 0; i < m_healCube.size(); i++) 
	{ 
		m_healCube[i]->Update(timestep); 
	}
	
	RefershUI();

	// The moves remaining bar doesn't need updating as it does nothing

	CheckGameOver();

	// Sometimes creating a whole new child of Camera is a bit overkill. Here
	// we're just telling our existing camera what to do (it has been modified to include
	// the catch-up mode using LERP and also sets its look-at internally each frame).
	m_currentCam->SetTargetPosition(m_player->GetPosition()+ Vector3(0.0f, 0.4f, 0.1f));
	m_currentCam->Update(timestep);
	
	m_input->EndUpdate();
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	// The board renders all of its tiles
	m_gameBoard->Render(m_renderer, m_currentCam);
	//m_player->Render(m_renderer, m_currentCam);
	m_movesRemainingBar->Render(m_renderer, m_currentCam);

	for (int i = 0; i < m_monster.size(); i++)
		{
			m_monster[i]->Render(m_renderer, m_currentCam);
		}


	for (int i = 0; i < m_healCube.size(); i++)
	{
		m_healCube[i]->Render(m_renderer, m_currentCam);
	}

	 
	DrawUI();

	m_renderer->EndScene();		
}


void Game::DrawUI()
{
	// Sprites don't use a shader 
	m_renderer->SetCurrentShader(NULL);

	CommonStates states(m_renderer->GetDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	// Do UI drawing between the Begin and End calls
	// Let's draw some text over our game
	m_arialFont18->DrawString(m_spriteBatch, m_scoreText.c_str(), Vector2(500, 680), Color(1.0f, 1.0f, 1.0f), 0, Vector2(0, 0));

	m_arialFont18->DrawString(m_spriteBatch, m_healthText.c_str(), Vector2(20,30), Color(1.0f, 1.0f, 1.0f), 0, Vector2(0, 0));

	m_spriteBatch->End();
}

void Game::CheckGameOver()
{
	// Checks the three conditions that can end the game and informs the user

	const char* msg = "";

	if (m_player->GetHealth() <= 0.0f)
	{
		msg = "You've run out of health.";
	}
	else if (m_player->GetMovesRemaining() <= 0)
	{
		msg = "You've used up all your moves.";
	}
	else if (m_player->GetIsTrapped())
	{
		msg = "You're trapped.";
	}

	if (msg != "")
	{
		std::stringstream ss;
		ss << msg << " You scored " << m_player->GetScore() << " and defeated " << m_player->GetNumberOfMonstersDefeated() << " monsters.";

		// Message Boxes are a blocking call which makes life a little easier here
		MessageBox(NULL, ss.str().c_str(), "Game Over", MB_OK);
		PostQuitMessage(0);

		// From now on, an in-game UI should be used instead of a message box
	}
}

void Game::Shutdown()
{
	if (m_player)
	{
		delete m_player;
		m_player = NULL;
	}

	for (int i = 0; i < m_monster.size(); i++)
	{
		if (m_monster[i])
		{
			delete m_monster[i];
			m_monster [i] = NULL;
		}
	}

	for (int i = 0; i < m_healCube.size(); i++)
	{
		if (m_healCube[i])
		{
			delete m_healCube[i];
			m_healCube[i] = NULL;
		}
	}

	if (m_gameBoard)
	{
		delete m_gameBoard;
		m_gameBoard = NULL;
	}

	if (m_movesRemainingBar)
	{
		delete m_movesRemainingBar;
		m_movesRemainingBar = NULL;
	}

	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_meshManager)
	{
		m_meshManager->Release();
		delete m_meshManager;
		m_meshManager = NULL;
	}

	if (m_textureManager)
	{
		m_textureManager->Release();
		delete m_textureManager;
		m_textureManager = NULL;
	}

	if (m_diffuseTexturedShader)
	{
		m_diffuseTexturedShader->Release();
		delete m_diffuseTexturedShader;
		m_diffuseTexturedShader = NULL;
	}


	if (m_spriteBatch)
	{
		delete m_spriteBatch;
		m_spriteBatch = NULL;
	}

	if (m_arialFont12)
	{
		delete m_arialFont12;
		m_arialFont12 = NULL;
	}

	if (m_arialFont18)
	{
		delete m_arialFont18;
		m_arialFont18 = NULL;
	}


}