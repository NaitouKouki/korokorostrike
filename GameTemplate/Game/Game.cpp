#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "Player.h"
#include "Pin.h"
#include "GameCamera.h"
#include "Stage.h"
#include "Totalscore.h"
#include "Result.h"
#include "FrameCount.h"
#include "BackGround.h"

Game::Game()
{
}

Game::~Game()
{
	DeleteAll();
	DeleteGO(m_stage);
}

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 140.0f, -600.0f });

	m_currentGame = 1;
	m_throwCount = 1;
	m_state = 0;

	NewGO<BackGround>(0, "background");
	m_frameCount = NewGO<FrameCount>(0, "framecount");
	m_frameCount->SetFrame(m_currentGame , m_maxGameCount);

	m_stage = NewGO<Stage>(0, "stage");

	mainStage();

	// Physics設定
	//当たり判定を可視化する
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//一応重力を設定しておく
	PhysicsWorld::GetInstance()->SetGravity(Vector3(0.0f, -9.8f, 0.0f));
	m_totalscore = NewGO<Totalscore>(0, "totalscore");

	return true;
}

void Game::Update()
{
	switch (m_state)
	{
	case 0:
		break;
	case 1:
		if(m_player != nullptr || m_camera != nullptr)
		{
			DeleteGO(m_player);
			DeleteGO(m_camera);
			m_player = NewGO<Player>(0, "player");
			m_camera = NewGO<GameCamera>(0, "camera");
		}
		m_throwCount = 2;
		m_state = 0; // 状態を戻す
		break;
	case 2:
		// 1ゲーム終了
		m_currentGame++;
		m_frameCount->AddFrame();
		m_throwCount = 1;

		if (m_currentGame <= m_maxGameCount) 
		{
			// 次のゲームをスタート
			DeleteAll();
			mainStage();
			m_state = 0;
		} 
		else 
		{
			// 全5ゲーム終了 → 結果画面
			NewGO<Result>(0, "result");
			DeleteGO(this);
		}
		break;
	default:
		break;
	}
}

void Game::mainStage()
{
		m_player = NewGO<Player>(0, "player");
		m_camera = NewGO<GameCamera>(0, "camera");

	Vector3 pinPositions[10] = {
		{  0.0f, 30.0f, 1200.0f },
		{ -20.0f, 30.0f, 1240.0f },
		{  20.0f, 30.0f, 1240.0f },
		{ -40.0f, 30.0f, 1280.0f },
		{   0.0f, 30.0f, 1280.0f },
		{  40.0f, 30.0f, 1280.0f },
		{ -60.0f, 30.0f, 1320.0f },
		{ -20.0f, 30.0f, 1320.0f },
		{  20.0f, 30.0f, 1320.0f },
		{  60.0f, 30.0f, 1320.0f },
	};

	for (int i = 0; i < 10; i++) {
		pins[i] = NewGO<Pin>(0, "pin");
		pins[i]->SetID(i);
		pins[i]->SetInitPosition(pinPositions[i]);
	}
}

void Game::DeleteAll ()
{

	DeleteGO(m_player);
	DeleteGO(m_camera);
	auto pins = FindGOs<Pin>("pin");
	for (auto pin : pins) {
		DeleteGO(pin);
	}
}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}