#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game.h"

GameCamera::GameCamera(){}
GameCamera::~GameCamera(){}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 100.0f, -300.0f);

	return true;
}

void GameCamera::Update()
{
	m_player = FindGO<Player>("player");
	if (m_player == nullptr) return;

	// 初期化（初回のみ）
	if (!m_isInit) {
		m_springCamera.Init(*g_camera3D, 1000.0f, true, 5.0f);
		m_isInit = true;
	}


	Vector3 target = m_player->rbPos;
	target.y += 80.0f;
	target += g_camera3D->GetForward() * 20.0f;

	static bool followEnabled = true;
	const float stopZ = 1500.0f;  // 停止ライン（Z軸位置）

	if (followEnabled)
	{
		if (target.z > stopZ) {
			followEnabled = false;  // 一度だけ追尾解除
		}
		else {
			// 通常の追尾処理
			Vector3 toCameraPosOld = m_toCameraPos;

			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();

			Quaternion qRot;
			qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
			qRot.Apply(m_toCameraPos);

			Vector3 axisX;
			axisX.Cross(Vector3::AxisY, m_toCameraPos);
			axisX.Normalize();
			qRot.SetRotationDeg(axisX, 1.5f * y);
			qRot.Apply(m_toCameraPos);

			Vector3 toPosDir = m_toCameraPos;
			toPosDir.Normalize();
			if (toPosDir.y < -0.5f || toPosDir.y > 0.8f) {
				m_toCameraPos = toCameraPosOld;
			}

			Vector3 pos = target + m_toCameraPos;
			m_springCamera.SetPosition(pos);
			m_springCamera.SetTarget(target);
			m_springCamera.Update();
		}
	}
	else
	{
		Vector3 currentPos = g_camera3D->GetPosition();
		Vector3 currentTarget = g_camera3D->GetTarget();

		m_springCamera.SetPosition(currentPos);
		m_springCamera.SetTarget(currentTarget);
		m_springCamera.Update();
	}
	if (!followEnabled && m_player->rbPos.z < 1450.0f) {
		followEnabled = true;  // 再追尾開始
	}

}


void GameCamera::Render(nsK2EngineLow::RenderContext& rc)
{
	(void)rc;
}