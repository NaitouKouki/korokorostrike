#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "Player.h"
#include "Pin.h"
#include "GameCamera.h"
#include "Stage.h"
#include "Totalscore.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_pin);
	DeleteGO(m_soundSource);
	DeleteGO(m_camera);
	DeleteGO(m_totalscore);
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
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//重力の設定
	PhysicsWorld::GetInstance()->SetGravity({ 0.0f,0.0f,0.0f });
	FindGO<Player>("player");
	FindGO<Pin>("pin");

	Stage1();
	return true;
}

void Game::Update()
{
	//Aボタンを押したらゲームを再度発射する
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//m_player = NewGO<Player>(0, "player");
		for (int i = 0; i < 10; i++) {
			m_pin = NewGO<Pin>(0, "pin");
		}
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
	//m_camera = NewGO<GameCamera>(0, "camera");
	m_stage = NewGO<Stage>(0, "stage");
	m_pin = NewGO<Pin>(0, "pin");
	m_player = NewGO<Player>(0, "player");
	m_totalscore = NewGO<Totalscore>(0, "totalscore");
}

void Game::GameStateUpdate()
{

}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}
