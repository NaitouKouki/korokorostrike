#pragma once

class Result;
class Game;
class GameCamera;
class Pin;
class Totalscore;

#include "gameObject/IGameObject.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	// スタート
	bool Start() override;
	// アップデート
	void Update() override;
	// レンダー
	void Render(nsK2EngineLow::RenderContext& rc) override;

	Vector3				m_ballPosition = Vector3::Zero;
	Vector3				m_scale = Vector3::One;		// スケール

	// 物理の位置と回転を取得するための一時変数
	Vector3				rbPos = Vector3::Zero;
	Quaternion			rbRot = Quaternion::Identity;
	RigidBodyInitData	rbInitData;
	RigidBody			m_rigidBody;	// 剛体

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_ballPosition;
	}

private:
	ModelRender			m_ballRender;
	SphereCollider		m_sphereCollider;	// ボールの当たり判定
	Pin*				m_pin = nullptr;
	GameCamera*			m_camera = nullptr;
	Result*				m_Result = nullptr;
	Game*				m_game = nullptr;
	Totalscore*			m_totalscore = nullptr;
};