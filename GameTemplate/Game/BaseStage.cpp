#include "stdafx.h"
#include "BaseStage.h"
#include "Player.h"

BaseStage::BaseStage()
{
}

BaseStage::~BaseStage()
{
}

bool BaseStage::Start()
{
	// モデルと静的衝突の初期化。モデルファイルは固定化例（必要なら派生で差し替え）。
	m_modelRender.Init("Assets/modelData/bg.tkm");
	m_object.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetWorldMatrix(0));

	m_ball = FindGO<Player>("Player");

	// 初期トランスフォームをモデルに反映
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	return true;
}

void BaseStage::ApplyInputRotation()
{
	// カメラ基準での入力回転を反映
	Vector3 forwardXZ = g_camera3D->GetForward();
	forwardXZ.y = 0.0f;
	forwardXZ.Normalize();
	Quaternion addRot;
	addRot.SetRotation(forwardXZ, g_pad[0]->GetLStickXF() * -0.006f);

	Vector3 rightXZ = g_camera3D->GetRight();
	rightXZ.y = 0.0f;
	rightXZ.Normalize();
	Quaternion addLot;
	addLot.SetRotation(rightXZ, g_pad[0]->GetLStickYF() * 0.006f);

	Quaternion qAdd;
	qAdd.Multiply(addRot, addLot);

	Matrix mTrans, mRot, mWorld;
	mTrans.MakeTranslation(m_position);
	mRot.MakeRotationFromQuaternion(m_rotation);
	mWorld = mRot * mTrans;

	Vector3 playerPos = m_ball ? m_ball->m_ballPosition : Vector3::Zero;
	mWorld._41 -= playerPos.x;
	mWorld._42 -= playerPos.y;
	mWorld._43 -= playerPos.z;

	mRot.MakeRotationFromQuaternion(qAdd);
	mWorld.Multiply(mWorld, mRot);

	mWorld._41 += playerPos.x;
	mWorld._42 += playerPos.y;
	mWorld._43 += playerPos.z;

	m_rotation.SetRotation(mWorld);
	m_position.Set(mWorld._41, mWorld._42, mWorld._43);
}

void BaseStage::Update()
{
	if (m_ball == nullptr) {
		m_ball = FindGO<Player>("Player");
	}

	ApplyInputRotation();

	// 物理と描画へ反映
	m_object.GetBody()->SetPositionAndRotation(m_position, m_rotation);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void BaseStage::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}