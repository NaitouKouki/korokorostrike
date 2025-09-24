#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "Player.h"
#include "GameCamera.h"
#include "Stage.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_soundSource);
	DeleteGO(m_camera);
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
	PhysicsWorld::GetInstance()->SetGravity({ 0.0f,50.0f,0.0f });
	FindGO<Player>("player");

	m_stage = NewGO<Stage>(0, "stage");
	return true;
}

void Game::Update()
{
	//Aボタンを押したらゲームを再スタートする
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_player = NewGO<Player>(0, "player");
	}
	//Bボタンを押したら重力を加算しボールを転がす
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		PhysicsWorld::GetInstance()->SetGravity({ 0.0f,-300.0f,100.0f });
	}
}

void Game::Stage1()
{
	//ステージを参照し呼び出す
	m_camera = NewGO<GameCamera>(0, "camera");
	m_stage = NewGO<Stage>(0, "stage");
}

void Game::GameStateUpdate()
{
	m_player = NewGO<Player>(0, "player");
}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}
