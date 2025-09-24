#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	// モデル
	m_ballRender.Init("Assets/modelData/ball.tkm");
	m_ballPosition.Set(0.0f, 100.0f, -300.0f);
	m_ballRender.SetPosition(m_ballPosition);
	m_ballRender.SetScale(1.3f, 1.3f, 1.3f);

	// 球の大きさ
	m_sphereCollider.Create(17.0f);
	rbInitData.collider = &m_sphereCollider;
	rbInitData.mass = 10.0f;
	rbInitData.pos = m_ballPosition;
	rbInitData.rot = Quaternion::Identity;
	rbInitData.restitution = 0.8f;  // 反発係数を正常な範囲に修正

	m_rigidBody.Init(rbInitData);
	m_rigidBody.SetFriction(1);

	m_charaCon.Init(0.1f, 0.1f, m_ballPosition);

	m_game = FindGO<Game>("game");
	return true;
}

void Player::Update()
{
	//今だけ座標を表示。(使わなくなったらけしてねー)
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"Pos: (%f, %f, %f)", m_ballPosition.x, m_ballPosition.y, m_ballPosition.z);
	m_rigidBody.GetPositionAndRotation(rbPos, rbRot);
	// 取得した位置と回転を反映する
	m_ballRender.SetPosition(rbPos);
	m_ballRender.SetRotation(rbRot);
	m_ballRender.Update();
	m_ballPosition = rbPos;
}


// 描画
void Player::Render(nsK2EngineLow::RenderContext& rc)
{
	m_ballRender.Draw(rc);
}