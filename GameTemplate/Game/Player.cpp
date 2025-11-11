#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Pin.h"
#include "GameCamera.h"
#include "Totalscore.h"
#include "Result.h"

Player::Player() {}
Player::~Player() {}

bool Player::Start()
{
	// モデル初期化
	m_ballRender.Init("Assets/modelData/ball.tkm");
	m_ballRender.SetPosition(m_startPosition);
	m_ballRender.SetScale(1.3f, 1.3f, 1.3f);

	// 球の当たり判定と物理挙動
	m_sphereCollider.Create(17.0f);
	rbInitData.collider = &m_sphereCollider;
	rbInitData.mass = 1200.0f;
	rbInitData.pos = m_startPosition;
	rbInitData.rot = Quaternion::Identity;
	rbInitData.restitution = 0.5f;

	m_rigidBody.Init(rbInitData);
	m_rigidBody.SetFriction(1);

	// ゲーム管理オブジェクトの取得
	m_game = FindGO<Game>("game");

	return true;
}

void Player::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	// 現在位置を反映
	m_rigidBody.GetPositionAndRotation(rbPos, rbRot);
	m_ballRender.SetPosition(rbPos);
	m_ballRender.SetRotation(rbRot);
	m_ballRender.Update();
	m_ballPosition = rbPos;

	if (!m_isThrown)
	{
		if (g_pad[0]->IsPress(enButtonLeft)) {
			m_startPosition.x -= moveSpeed;
			if(m_startPosition.x < -200.0f) {
				m_startPosition.x = -200.0f;
			}
		}
		if (g_pad[0]->IsPress(enButtonRight)) {
			m_startPosition.x += moveSpeed;
			if (m_startPosition.x > 250.0f) {
				m_startPosition.x = 250.0f;
			}
		}
		if(!g_pad[0]->IsPressAnyKey()) {
			moveSpeed = 4.0f;
			m_timer = 0.0f;
		}

		if (m_timer > 0.7f) { // 3秒経過したら実行
			moveSpeed = 10.0f; // moveSpeedを最大にする
		}
		// モデルと物理位置を更新
		m_ballRender.SetPosition(m_startPosition);
		m_rigidBody.SetPositionAndRotation(m_startPosition, Quaternion::Identity);
	}

	if (g_pad[0]->IsTrigger(enButtonB)) {
		Vector3 dir = Vector3::Front;
		dir.Normalize();
		m_rigidBody.SetLinearVelocity(dir * 800.0f);
		m_isThrown = true;
	}

	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_curveAmount = 0.3f;
		m_throwDir = Vector3::Front + (Vector3::Left * fabs(m_curveAmount));
		m_throwDir.Normalize();

		m_rigidBody.SetLinearVelocity(m_throwDir * 800.0f);
		m_rigidBody.SetAngularVelocity(Vector3(0.0f,200.0f, -100.0f));
		m_isThrown = true;
	}

	if (g_pad[0]->IsTrigger(enButtonX)) {
		m_curveAmount = 0.3f;
		m_throwDir = Vector3::Front + (Vector3::Right * fabs(m_curveAmount));
		m_throwDir.Normalize();

		m_rigidBody.SetLinearVelocity(m_throwDir * 800.0f);
		m_rigidBody.SetAngularVelocity(Vector3(0.0f, 200.0f, 100.0f));
		m_isThrown = true;
	}

	if (g_pad[0]->IsTrigger(enButtonY)) {
		Vector3 dir = Vector3::Back;
		dir.Normalize();
		m_rigidBody.SetLinearVelocity(dir * 800.0f);
		m_isThrown = true;
	}

	if ((m_ballPosition.y < -50.0f || m_ballPosition.y > 700.0f) && m_game->m_state == 0)
	{
		m_rigidBody.SetPositionAndRotation(m_startPosition, Quaternion::Identity);
		m_rigidBody.SetLinearVelocity(Vector3::Zero);
		m_rigidBody.SetAngularVelocity(Vector3::Zero);
		m_isThrown = false; // 再び調整可能に

		m_totalscore = FindGO<Totalscore>("totalscore");
		if (m_game->m_throwCount == 1)
		{
			m_game->m_state = 1;
		}
		else
		{
			m_game->m_state = 2;
			m_totalscore->RegisterGameScore();
		}

		// ストライク時の即時スキップ処理
		if (m_totalscore->m_gamescore == 10) {
			m_game->m_state = 2;
			m_totalscore->RegisterGameScore();
		}
	}
}

void Player::Render(nsK2EngineLow::RenderContext& rc)
{
	m_ballRender.Draw(rc);
}
