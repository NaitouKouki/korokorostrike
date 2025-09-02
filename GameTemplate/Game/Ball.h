#pragma once

class Game;

class Ball : public IGameObject
{
public:
	Ball();
	~Ball();
	//スタート
	bool Start();
	//アップデート
	void Update();
	//レンダー
	void Render(RenderContext& rc);

	Vector3         m_position = Vector3::Zero;	//座標。
	Vector3         m_ballPosition = Vector3::Zero;
	Vector3         m_scale = Vector3::One;		//スケール

	// 剛体の位置と回転を取得する
	Vector3			rbPos = Vector3::Zero;
	Quaternion		rbRot = Quaternion::Identity;
	RigidBodyInitData	rbInitData;
	RigidBody			m_rigidBody;	// 剛体

private:
	CharacterController     m_charaCon;		//キャラコン
	ModelRender			m_ballRender;
	SphereCollider		m_sphereCollider;	// ボールの形状

	Game* m_game = nullptr;
};