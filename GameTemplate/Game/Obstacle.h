#pragma once
#include "PhysicsDynamicObject.h"
class Game;
class Result;
class Obstacle:public IGameObject
{
	public:
	Obstacle();
	~Obstacle();
	bool Start() override;
	void Update() override;
	void Render(nsK2EngineLow::RenderContext& rc) override;	
	void SetPosition1(const Vector3& pos);
private:
	ModelRender				m_boxRender;
	PhysicsDynamicObject	m_phyObject;//ìÆìIó¨ëÃóp
	Quaternion				qRot;
	float					m_angleSpeed = 0.0f;
	float					m_moveSpeed = 1.0f;
	float					m_timer = 5.0f;
	float					moveDir = 50.0f;         // 1.0f = è„, -1.0f = â∫
	float					bottomLimit = -150.0f;
	float					topLimit = 30.0f;
	Vector3					m_position = Vector3::Zero;
};