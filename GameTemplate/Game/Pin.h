#pragma once
#include "gameObject/IGameObject.h"
#include <math/Vector.h>

class Game;

class Pin : public IGameObject
{
public:
	Pin();
	~Pin();
	// スタート
	bool Start() override;
	// アップデート
	void Update() override;
	// レンダー
	void Render(nsK2EngineLow::RenderContext& rc) override;

	Vector3				m_pinPosition = Vector3::Zero;
	Vector3				m_scale = Vector3::One;		// スケール
	// 物理の位置と回転を取得するための一時変数
	Vector3				boPos = Vector3::Zero;
	Quaternion			boRot = Quaternion::Identity;
	RigidBodyInitData	boInitData;
	RigidBody			m_rigidBody;	// 剛体
	void SetID(int id) { m_pinID = id; }
	void SetInitPosition(const Vector3& pos) { m_pinPosition = pos; }
	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_pinPosition;
	}
private:
	ModelRender			m_boxRender;
	BoxCollider			m_boxcollider;	// ボックスの当たり判定
	CollisionObject*	m_collisionObj;	// コリジョンオブジェクト
	Game*				m_game = nullptr;
	int					m_pinID;
	bool				m_isFall = false;	// 倒れたかどうか
	bool				m_isCounted = false; // スコアにカウントされたかどうか
};