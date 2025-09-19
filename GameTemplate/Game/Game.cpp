#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "Player.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_soundSource);
}

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 100.0f, -600.0f });
	GameStateUpdate();
	switch (m_state)
	{
	case 1:
		Stage1();
		break;
	}

	//当たり判定
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//重力の設定
	PhysicsWorld::GetInstance()->SetGravity({ 0.0f,-1800.0f,0.0f });
	//BGM.
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/BGM.wav");
	m_soundSource = NewGO<SoundSource>(0);
	//ResistWaveFileBankで指定した番号。
	m_soundSource->Init(1);
	//BGMは曲をループさせる。
	m_soundSource->Play(true);
	FindGO<Player>("player");

	return true;
}

void Game::Update()
{

}

void Game::Stage1()
{

}

void Game::GameStateUpdate()
{
	m_player = NewGO<Player>(0, "player");
}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}
