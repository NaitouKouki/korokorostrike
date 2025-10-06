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
	DeleteGO(m_camera);
	DeleteGO(m_totalscore);
}

bool Game::Start()
{

	Vector3 pinPositions[10] = {
		{  0.0f, 10.0f, 200.0f },
		{ -20.0f, 10.0f, 240.0f },
		{  20.0f, 10.0f, 240.0f },
		{ -40.0f, 10.0f, 280.0f },
		{   0.0f, 10.0f, 280.0f },
		{  40.0f, 10.0f, 280.0f },
		{ -60.0f, 10.0f, 320.0f },
		{ -20.0f, 10.0f, 320.0f },
		{  20.0f, 10.0f, 320.0f },
		{  60.0f, 10.0f, 320.0f }
	};

	//10本生成＆番号付け
	for (int i = 0; i < 10; i++) {
		pins[i] = NewGO<Pin>(0, ("pin" + std::to_string(i)).c_str());
		pins[i]->SetID(i);
		pins[i]->SetInitPosition(pinPositions[i]);
	}



	g_camera3D->SetPosition({ 0.0f, 140.0f, -600.0f });
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
	PhysicsWorld::GetInstance()->SetGravity({ 0.0f,-300.0f,-1.0f });
	FindGO<Player>("player");

	Stage1();
	return true;
}

void Game::Update()
{
	////Bボタンを押したら重力を加算しボールを転がす
	//if (g_pad[0]->IsTrigger(enButtonB))
	//{
	//	PhysicsWorld::GetInstance()->SetGravity({ 0.0f,-300.0f,100.0f });
	//}
}

void Game::Stage1()
{
	//m_camera = NewGO<GameCamera>(0, "camera");
	m_stage = NewGO<Stage>(0, "stage");
	m_player = NewGO<Player>(0, "player");
	m_camera = NewGO<GameCamera>(0, "camera");
	m_totalscore = NewGO<Totalscore>(0, "totalscore");
}

void Game::GameStateUpdate()
{

}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}
