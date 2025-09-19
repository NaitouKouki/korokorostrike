#pragma once

#include "gameObject/IGameObject.h"
#include "graphics/ModelRender.h"
#include "physics/PhysicsStaticObject.h"
#include "graphics/IRenderer.h"
#include "math/Math.h"

class Player;

class BaseStage : public IGameObject
{
public:
	BaseStage();
	virtual ~BaseStage();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

protected:
	ModelRender			m_modelRender;
	PhysicsStaticObject	m_object;

	Vector3				m_position = Vector3::Zero;
	Quaternion			m_rotation = Quaternion::Identity;
	Vector3				m_scale = Vector3::One;

	Player* m_ball = nullptr;

private:
	void ApplyInputRotation();
};