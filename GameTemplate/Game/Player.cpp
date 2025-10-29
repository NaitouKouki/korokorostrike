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
    rbInitData.mass = 1200.0f;
    rbInitData.pos = m_ballPosition;
    rbInitData.rot = Quaternion::Identity;
    rbInitData.restitution = 0.5f;   // 反発係数

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

    // メンバ変数として追加（Player.h）
    float m_curveAmount = 0.0f;
    Vector3 m_throwDir;
    bool m_isThrown = false;


    // Aボタン：やや右に投げる
    if (g_pad[0]->IsTrigger(enButtonA)) {
        m_curveAmount = 0.3f; // 左方向（マイナスで左、プラスで右）
        m_throwDir = Vector3::Front + (Vector3::Left * fabs(m_curveAmount));
        m_throwDir.Normalize();

        m_rigidBody.SetLinearVelocity(m_throwDir * 800.0f);
        
        // 横方向のスピンを加える（左に曲がるスピン）
        Vector3 spin = Vector3(0.0f, 200.0f, 50.0f); // Y軸回転速度（値が大きいほど曲がる）
        m_rigidBody.SetAngularVelocity(spin);
        m_isThrown = true;
    }

    // Xボタン：やや左に投げる
    if (g_pad[0]->IsTrigger(enButtonX)) {
        m_curveAmount = -0.3f; // 右方向（Aの逆向きになっている）
        m_throwDir = Vector3::Front + (Vector3::Right *fabs(m_curveAmount));
        m_throwDir.Normalize();
        m_rigidBody.SetLinearVelocity(m_throwDir * 800.0f);
        
        // 横方向のスピンを加える（右に曲がるスピン）
        Vector3 spin = Vector3(0.0f, 200.0f, -50.0f); // Y軸回転速度（値が大きいほど曲がる）
        m_rigidBody.SetAngularVelocity(spin);
        m_isThrown = true;
    }

    // Bボタン：前進
    if (g_pad[0]->IsTrigger(enButtonB)) {
        Vector3 dir = Vector3::Front;     // 前方向へ進む
        dir.Normalize();

        // 進行方向の速度設定
        m_rigidBody.SetLinearVelocity(dir * 800.0f);
        m_isThrown = true;
    }

    // Yボタン：後退
    if (g_pad[0]->IsTrigger(enButtonY)) {
        m_rigidBody.SetLinearVelocity(Vector3::Back * 1000.0f);
    }

    if (g_pad[0]->IsPressAnyKey()) {
        Vector3 velocity = m_rigidBody.GetLinearVelocity();
        velocity *= 0.991f; // 減速率
        m_rigidBody.SetLinearVelocity(velocity);
    }

	// 曲がりを徐々に減衰させる処理
    if (m_isThrown) {
        // 毎フレーム、傾きを少しずつ0に近づける
        m_curveAmount *= 0.91f;  // 減衰率（小さいほど早く真っ直ぐになる）

        // 新しい方向ベクトルを再計算
        Vector3 dir = Vector3::Front + (Vector3::Right * m_curveAmount);
        dir.Normalize();

        // 現在の速度を保持しつつ方向だけ補正
        Vector3 velocity = m_rigidBody.GetLinearVelocity();
        float speed = velocity.Length();

        m_rigidBody.SetLinearVelocity(dir * speed);
    }


    //落下後の処理
    if (m_ballPosition.y < -50.0f && m_game->m_state == 0 || m_ballPosition.y >700.0f && m_game->m_state == 0)
    {
        // 初期位置にリセット
        m_rigidBody.SetPositionAndRotation(Vector3(0.0f, 90.0f, -800.0f), Quaternion::Identity);
        m_rigidBody.SetLinearVelocity(Vector3::Zero);
        m_rigidBody.SetAngularVelocity(Vector3::Zero);

        m_totalscore = FindGO<Totalscore>("totalscore");
        if (m_game->m_throwCount == 1) 
        {
			// 1投目終了 → 2投目へ    
            m_game->m_state = 1;
        }
        else 
        {
            // 2投目終了 → 次のゲームへ
            m_game->m_state = 2;
            m_totalscore->RegisterGameScore();
        }
        //スコアを10点取った場合次のゲームへ
        if (m_totalscore->m_gamescore == 10) {
			m_game->m_state = 2;
			m_totalscore->RegisterGameScore();
			m_totalscore->m_gamescore = 0;// スコアリセット

        }
        //一定より高かった場合も同様に処理する

    }
}

void Player::Render(nsK2EngineLow::RenderContext& rc)
{
    m_ballRender.Draw(rc);
}