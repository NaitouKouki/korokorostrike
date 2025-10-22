#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Pin.h"
#include "GameCamera.h"
#include "Totalscore.h"
#include "Result.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
    // モデル初期化
    m_ballRender.Init("Assets/modelData/ball.tkm");
    m_ballPosition.Set(0.0f, 40.0f, -800.0f);
    m_ballRender.SetPosition(m_ballPosition);
    m_ballRender.SetScale(1.3f, 1.3f, 1.3f);

    // 球の当たり判定と物理挙動
    m_sphereCollider.Create(17.0f);
    rbInitData.collider = &m_sphereCollider;
    rbInitData.mass = 100.0f;
    rbInitData.pos = m_ballPosition;
    rbInitData.rot = Quaternion::Identity;
    rbInitData.restitution = 1.0f;   // 反発係数

    m_rigidBody.Init(rbInitData);
    m_rigidBody.SetFriction(1);

    // ゲーム管理オブジェクトの取得
    m_game = FindGO<Game>("game");

    return true;
}

void Player::Update()
{
    // 位置と回転の反映
    m_rigidBody.GetPositionAndRotation(rbPos, rbRot);
    m_ballRender.SetPosition(rbPos);
    m_ballRender.SetRotation(rbRot);
    m_ballRender.Update();
    m_ballPosition = rbPos;

    //----------------------------------------
    // 入力処理
    //----------------------------------------
    // Bボタン：やや右方向に前進
    if (g_pad[0]->IsTrigger(enButtonB)) {
        Vector3 dir = Vector3::Front + (Vector3::Right * 0.2f); // 少し右方向成分を加える
        dir.Normalize();
        m_rigidBody.SetLinearVelocity(dir * 800.0f);
    }

    // Aボタン：左移動
    if (g_pad[0]->IsTrigger(enButtonA)) {
        m_rigidBody.SetLinearVelocity(Vector3::Left * 200.0f);
    }

    // Xボタン：右移動
    if (g_pad[0]->IsTrigger(enButtonX)) {
        m_rigidBody.SetLinearVelocity(Vector3::Right * 200.0f);
    }

    // Yボタン：後退
    if (g_pad[0]->IsTrigger(enButtonY)) {
        m_rigidBody.SetLinearVelocity(Vector3::Back * 200.0f);
    }

    //----------------------------------------
    // 入力がないときの減速処理
    //----------------------------------------
    if (!g_pad[0]->IsPressAnyKey()) {
        Vector3 velocity = m_rigidBody.GetLinearVelocity();
        velocity *= 0.99f; // 減速率
        m_rigidBody.SetLinearVelocity(velocity);
    }

    //----------------------------------------
    // 落下時のリセット処理
    //----------------------------------------
    if (m_ballPosition.y < -50.0f && m_game->m_state == 0)
    {
        // 初期位置にリセット
        m_rigidBody.SetPositionAndRotation(Vector3(0.0f, 90.0f, -800.0f), Quaternion::Identity);
        m_rigidBody.SetLinearVelocity(Vector3::Zero);
        m_rigidBody.SetAngularVelocity(Vector3::Zero);

        m_totalscore = FindGO<Totalscore>("totalscore");

        // スコアが10ならリザルトへ
        if (m_totalscore->m_score == 10) {
            NewGO<Result>(0, "result");
            DeleteGO(this);
        }
        else {
            m_game->m_state = 1;
        }
    }

    if (m_ballPosition.y < -100.0f && m_game->m_state == 1)
    {
        // リザルト画面へ遷移
        m_rigidBody.SetPositionAndRotation(Vector3(0.0f, 90.0f, -300.0f), Quaternion::Identity);
        m_rigidBody.SetLinearVelocity(Vector3::Zero);
        m_rigidBody.SetAngularVelocity(Vector3::Zero);

        NewGO<Result>(0, "result");
        DeleteGO(this);
    }
}

void Player::Render(nsK2EngineLow::RenderContext& rc)
{
    m_ballRender.Draw(rc);
}
