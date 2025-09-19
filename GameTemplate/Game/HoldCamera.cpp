#include "stdafx.h"
#include "HoldCamera.h"
#include "Game.h"
#include "Player.h"

HoldCamera::HoldCamera() {}
HoldCamera::~HoldCamera() {}

bool HoldCamera::Start()
{
    // ターゲットからカメラ位置までのベクトルを設定
    m_toCameraPos.Set(0.0f, 100.0f, 300.0f);

    // プレイヤー（ボール）のインスタンスを探す
    m_player = FindGO<Player>("player");
    m_game = FindGO<Game>("game");

    // カメライベント（追従）を有効化
    m_isCameraEvent = true;

    return true;
}

void HoldCamera::Update()
{
    if (m_isCameraEvent) {
        if (!m_isInit) {
            // 三人称カメラの初期化
            m_springCamera.Init(
                *g_camera3D,		// 三人称カメラの挙動を行うカメラを指定
                1000.0f,			// カメラの移動速度の最大値
                true,				// カメラの慣性(スムージング)を有効にするか
                5.0f				// カメラに設定するバネの剛性
            );
            m_isInit = true;
        }

        Vector3 toCameraPosOld = m_toCameraPos;
        // パッド入力でカメラを回転
        float x = g_pad[0]->GetRStickXF();
        float y = g_pad[0]->GetRStickYF();
        // Y軸回転
        Quaternion qRot;
        qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
        qRot.Apply(m_toCameraPos);
        // X軸回転
        Vector3 axisX;
        axisX.Cross(Vector3::AxisY, m_toCameraPos);
        axisX.Normalize();
        qRot.SetRotationDeg(axisX, 1.5f * y);
        qRot.Apply(m_toCameraPos);
        // カメラの回転の制限をチェック
        // ターゲットからカメラまでのベクトルを正規化
        // 俯角/仰角の制限
        Vector3 toPosDir = m_toCameraPos;
        toPosDir.Normalize();
        if (toPosDir.y < -0.5f) {
            // カメラが下を向きすぎ
            m_toCameraPos = toCameraPosOld;
        }
        else if (toPosDir.y > 0.8f) {
            // カメラが上を向きすぎ
            m_toCameraPos = toCameraPosOld;
        }

        // ボールの現在位置に追従するためターゲット/位置を設定
        if (m_player != nullptr) {
            const Vector3 target = m_player->m_ballPosition;
            const Vector3 pos = target + m_toCameraPos;
            m_springCamera.SetTarget(target);
            m_springCamera.SetPosition(pos);
        }
        else {
            // ボールが見つからない場合はデフォルト位置に設定
            const Vector3 target = Vector3::Zero;
            const Vector3 pos = target + m_toCameraPos;
            m_springCamera.SetTarget(target);
            m_springCamera.SetPosition(pos);
        }

        // カメラ更新
        m_springCamera.Update();
    }
}

void HoldCamera::Render(RenderContext& rc)
{
    // 必要に応じて描画処理を記述

}
