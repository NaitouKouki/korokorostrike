#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Pin.h"
#include "GameCamera.h"
#include "Result.h"



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
	m_ballPosition.Set(0.0f, 90.0f, -300.0f);
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

	m_game = FindGO<Game>("game");
	return true;
}

void Player::Update()
{
	m_rigidBody.GetPositionAndRotation(rbPos, rbRot);
	//取得した位置と回転を反映する
	m_ballRender.SetPosition(rbPos);
	m_ballRender.SetRotation(rbRot);
	m_ballRender.Update();
	m_ballPosition = rbPos;

	//Aボタンで左に移動
	if (g_pad[0]->IsTrigger(enButtonA)) {
		Vector3 left = Vector3::Left;
		left.Normalize();
		left *= 50.0f; // 力の大きさを調整
		m_rigidBody.SetLinearVelocity(left);
	}
	//Bボタンで前進
	if (g_pad[0]->IsTrigger(enButtonB)) {
		Vector3 forward = Vector3::Front;
		forward.Normalize();
		forward *= 300.0f; // 力の大きさを調整
		m_rigidBody.SetLinearVelocity(forward);
	}
	//Xボタンで右に移動
	if (g_pad[0]->IsTrigger(enButtonX)) {
		Vector3 right = Vector3::Right;
		right.Normalize();
		right *= 50.0f; // 力の大きさを調整
		m_rigidBody.SetLinearVelocity(right);
	}
	//一定より下に落ちたらリセット
	if (m_ballPosition.y < -50.0f) {
		m_rigidBody.SetPositionAndRotation(Vector3(0.0f, 90.0f, -300.0f), Quaternion::Identity);
		m_rigidBody.SetLinearVelocity(Vector3::Zero);
		m_rigidBody.SetAngularVelocity(Vector3::Zero);
		NewGO<Result>(0, "result");
		DeleteGO(this);
	}
}


// 描画
void Player::Render(nsK2EngineLow::RenderContext& rc)
{
	m_ballRender.Draw(rc);
}