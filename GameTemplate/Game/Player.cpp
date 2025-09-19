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
	// ƒ‚ƒfƒ‹
	m_ballRender.Init("Assets/modelData/ball.tkm");
	m_ballPosition.Set(0.0f, 300.0f, 0.0f);
	m_ballRender.SetPosition(m_ballPosition);
	m_ballRender.SetScale(0.2f, 0.2f, 0.2f);

	// ‹…‚Ì‘å‚«‚³
	m_sphereCollider.Create(17.0f);
	rbInitData.collider = &m_sphereCollider;
	rbInitData.mass = 10.0f;
	rbInitData.pos = m_ballPosition;
	rbInitData.rot = Quaternion::Identity;
	rbInitData.restitution = 0.8f;  // ”½”­ŒW”‚ğ³í‚È”ÍˆÍ‚ÉC³

	m_rigidBody.Init(rbInitData);
	m_rigidBody.SetFriction(1);

	m_charaCon.Init(0.1f, 0.1f, m_ballPosition);

	m_game = FindGO<Game>("game");
	return true;
}

void Player::Update()
{
	m_rigidBody.GetPositionAndRotation(rbPos, rbRot);
	// æ“¾‚µ‚½ˆÊ’u‚Æ‰ñ“]‚ğ”½‰f‚·‚é
	m_ballRender.SetPosition(rbPos);
	m_ballRender.SetRotation(rbRot);
	m_ballRender.Update();
	m_ballPosition = rbPos;
}


// •`‰æ
void Player::Render(nsK2EngineLow::RenderContext& rc)
{
	m_ballRender.Draw(rc);
}