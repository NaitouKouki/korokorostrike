#include "stdafx.h"
#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle() {}
Obstacle::~Obstacle() {}
bool Obstacle::Start()
{
	m_boxRender.Init("Assets/modelData/ball.tkm");
	m_boxRender.SetScale(20.0f,6.0f, 20.0f);
	m_boxRender.Update();
	m_phyObject.CreateFromModel(m_position, m_boxRender.GetModel(), m_boxRender.GetModel().GetWorldMatrix());
	return true;
}

void Obstacle::Update()
{
    // 時間更新（回転に必須）
    m_timer += g_gameTime->GetFrameDeltaTime();

    float rotSpeed = 1.5f;
    m_angleSpeed = m_timer * rotSpeed;
    qRot.SetRotationY(m_angleSpeed);

    Vector3 pos = m_position;

    pos.y += m_moveSpeed * moveDir * g_gameTime->GetFrameDeltaTime();

    if (pos.y > topLimit) {
        pos.y = topLimit;
        moveDir = -50.0f;
    }
    else if (pos.y < bottomLimit) {
        pos.y = bottomLimit;
        moveDir = 50.0f;
    }

    m_boxRender.SetRotation(qRot);
    m_boxRender.SetPosition(pos);
    m_boxRender.Update();

    m_phyObject.SetRotation(qRot);
    m_phyObject.SetPosition(pos);

    m_position = pos;
}

void Obstacle::Render(nsK2EngineLow::RenderContext& rc)
{
	m_boxRender.Draw(rc);
}

void Obstacle::SetPosition1(const Vector3& pos)
{
	m_boxRender.SetPosition(pos);
	m_boxRender.Update();
}