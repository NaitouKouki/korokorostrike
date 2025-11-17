#pragma once

class Result;
class Game;
class GameCamera;
class Pause;
class Pin;
class Totalscore;

#include "gameObject/IGameObject.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();

	bool Start() override;
	void Update() override;
	void SetPause(bool isPause);
	void Render(nsK2EngineLow::RenderContext& rc) override;
	const Vector3& GetPosition() const { return m_ballPosition; }

	Vector3				rbPos = Vector3::Zero;
	Quaternion			rbRot = Quaternion::Identity;
	bool				m_isControl = true;
	bool				m_isPause = false;

private:
	ModelRender			m_ballRender;
	SphereCollider		m_sphereCollider;
	RigidBodyInitData	rbInitData;
	RigidBody			m_rigidBody;

	Pin*				m_pin = nullptr;	
	Game*				m_game = nullptr;
	GameCamera*			m_camera = nullptr;
	Pause*				m_pause = nullptr;
	Result*				m_Result = nullptr;
	Totalscore*			m_totalscore = nullptr;
	Vector3				m_ballPosition = Vector3::Zero;
	Vector3				m_startPosition = Vector3(0.0f, 40.0f, -800.0f);	// ボールの初期位置
	Vector3				m_scale = Vector3::One;
	Vector3				m_throwDir;             // 投球方向
	bool				m_isThrown = false;	// 投球済みフラグ
	float				m_curveAmount = 0.0f;
	float				moveSpeed = 0.0f;
	float				m_timer = 0.0f;
};
