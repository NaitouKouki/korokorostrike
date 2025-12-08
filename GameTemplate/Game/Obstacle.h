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
	PhysicsDynamicObject	m_phyObject;//“®“I—¬‘Ì—p
	Quaternion				qRot;
	float					m_angleSpeed = 0.0f;
	float					m_moveSpeed = 0.0f;
	float					rotSpeed = 1.0f;
	float					m_timer = 0.0f;
	float					moveDir = 800.0f;
	float					bottomLimit = -300.0f;
	float					topLimit = 300.0f;
	Vector3					m_position = Vector3::Zero;
};