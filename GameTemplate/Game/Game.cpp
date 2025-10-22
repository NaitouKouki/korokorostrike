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
	DeleteGO(m_camera);
	DeleteGO(m_player);
	DeleteGO(m_totalscore);
	DeleteGO(m_stage);

	auto pins = FindGOs<Pin>("pin");
	for (auto pin : pins) {
		DeleteGO(pin);
	}
}

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 140.0f, -600.0f });
	GameStateUpdate();

	switch (m_state)
	{
	case 0:
		Stage1();
		break;

	case 1:
		DeleteGO(m_player);
		DeleteGO(m_camera);
		NewGO<Player>(0, "player");
		NewGO<GameCamera>(0, "camera");
		break;

	default:
		break;
	}

	// Physics 設定
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	PhysicsWorld::GetInstance()->SetGravity({ 0.0f, -400.0f, -5.0f });

	FindGO<Player>("player");
	FindGO<GameCamera>("camera");
	return true;
}

void Game::Update()
{
	GameStateUpdate();
}

void Game::Stage1()
{
	m_stage = NewGO<Stage>(0, "stage");
	m_player = NewGO<Player>(0, "player");
	m_camera = NewGO<GameCamera>(0, "camera");
	m_totalscore = NewGO<Totalscore>(0, "totalscore");

	Vector3 pinPositions[10] = {
		{  0.0f, 30.0f, 700.0f },
		{ -20.0f, 30.0f, 740.0f },
		{  20.0f, 30.0f, 740.0f },
		{ -40.0f, 30.0f, 780.0f },
		{   0.0f, 30.0f, 780.0f },
		{  40.0f, 30.0f, 780.0f },
		{ -60.0f, 30.0f, 820.0f },
		{ -20.0f, 30.0f, 820.0f },
		{  20.0f, 30.0f, 820.0f },
		{  60.0f, 30.0f, 820.0f }
	};

	// ピン10本生成＆番号設定
	for (int i = 0; i < 10; i++) {
		pins[i] = NewGO<Pin>(0, "pin");
		pins[i]->SetID(i);
		pins[i]->SetInitPosition(pinPositions[i]);
	}
}

void Game::GameStateUpdate()
{
}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}
