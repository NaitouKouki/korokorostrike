#include "stdafx.h"
#include "Pin.h"
#include "Game.h"
#include "collision/CollisionObject.h"

Pin::Pin()
{

}

Pin::~Pin()
{

}

bool Pin::Start()
{
	// モデル
	m_boxRender.Init("Assets/modelData/pin.tkm");
	m_boxPosition.Set(0.0f, 90.0f, -100.0f);
	m_boxRender.SetPosition(m_boxPosition);
	m_boxRender.SetScale(0.2f, 0.2f, 0.2f);

	/*CleateCollision();
	*/
	// ボックスの大きさ
	m_boxcollider.Create(Vector3(17.0f, 60.0f, 17.0f));
	boInitData.collider = &m_boxcollider;
	boInitData.mass = 10.0f;
	boInitData.pos = m_boxPosition;
	boInitData.rot = Quaternion::Identity;
	boInitData.restitution = 0.8f;  // 反発係数を正常な範囲に修正

	m_rigidBody.Init(boInitData);
	m_rigidBody.SetFriction(1);

	m_charaCon.Init(0.1f, 0.1f, m_boxPosition);

	m_game = FindGO<Game>("game");
	return true;
}

void Pin::Update()
{
	m_rigidBody.GetPositionAndRotation(boPos, boRot);
	// 取得した位置と回転を反映する
	m_boxRender.SetPosition(boPos);
	m_boxRender.SetRotation(boRot);
	m_boxRender.Update();
	m_boxPosition = boPos;
	//m_collisionObj->Update();
	m_charaCon.SetPosition(m_boxPosition);
    
	btTransform transform;
	m_rigidBody.GetBody()->getMotionState()->getWorldTransform(transform);

	// 現在の回転を取得
	btQuaternion rot = transform.getRotation();

	// Upベクトルを算出（Y軸基準の場合）
	btVector3 upDir = quatRotate(rot, btVector3(0, 1, 0));

	upDir.normalize();

	// どれだけ傾いているか確認（例：Y成分が小さくなると倒れてる）
	float dot = upDir.dot(btVector3(0, 1, 0));  // 1 = 真上, 0 = 横向き
	if (dot < 0.1f) { // 0.8fは調整可能な閾値
		// 一定以上傾いていたら立て直す
		//transform.setRotation(btQuaternion(0, 0, 0, 1)); // 単位クォータニオンでリセット
		//m_rigidBody.GetBody()->setWorldTransform(transform);
		//m_rigidBody.GetBody()->getMotionState()->setWorldTransform(transform);
		//m_rigidBody.SetLinearVelocity(Vector3::Zero); // 速度をリセット
		//m_rigidBody.SetAngularVelocity(Vector3::Zero); // 回転速度もリセット
		DeleteGO(this);
		return;
	}
}


// 描画
void Pin::Render(nsK2EngineLow::RenderContext& rc)
{
	m_boxRender.Draw(rc);
}