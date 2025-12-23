#include "stdafx.h"
#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle() {}
Obstacle::~Obstacle() {}
bool Obstacle::Start()
{
	m_boxRender.Init("Assets/modelData/obstacle.tkm");
	m_boxRender.SetScale(4.0f,4.0f, 4.0f);
	m_boxRender.Update();
	m_phyObject.CreateFromModel(m_position, m_boxRender.GetModel(), m_boxRender.GetModel().GetWorldMatrix());
	return true;
}

void Obstacle::Update()
{
    // 時間更新（回転に必須）
    m_timer += g_gameTime->GetFrameDeltaTime();

    m_angleSpeed = m_timer * rotSpeed;
    qRot.SetRotationY(m_angleSpeed);

    Vector3 pos = m_position;

    pos.x += moveDir + m_moveSpeed * g_gameTime->GetFrameDeltaTime();

    if (pos.x > 250.0f) {
        pos.x = 250.0f;
        moveDir = -6.0f;
    }
    else if (pos.x < -250.0f) {
        pos.x = -250.0f;
        moveDir = 6.0f;
    }

    m_phyObject.SetRotation(qRot);
    m_phyObject.SetPosition(pos);

    m_boxRender.SetRotation(qRot);
    m_boxRender.SetPosition(pos);
    m_boxRender.Update();

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