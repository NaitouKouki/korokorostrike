#include "stdafx.h"
#include "Ball.h"
#include "Game.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

bool Ball::Start()
{
	//�w�i
	m_ballRender.Init("Assets/modelData/ball.tkm");
	m_ballPosition.Set(0.0f, 300.0f, 0.0f);
	m_ballRender.SetPosition(m_ballPosition);
	m_ballRender.SetScale(0.2f, 0.2f, 0.2f);

	//���̂̑傫��
	m_sphereCollider.Create(17.0f);
	rbInitData.collider = &m_sphereCollider;
	rbInitData.mass = 10.0f;
	rbInitData.pos = m_ballPosition;
	rbInitData.rot = Quaternion::Identity;
	rbInitData.restitution = -100;

	m_rigidBody.Init(rbInitData);
	m_rigidBody.SetFriction(1);

	m_charaCon.Init(0.1f, 0.1f, m_ballPosition);

	m_game = FindGO<Game>("game");
	return true;
}

void Ball::Update()
{
	m_rigidBody.GetPositionAndRotation(rbPos, rbRot);
	// �擾�����ʒu�Ɖ�]�𔽉f������B
	m_ballRender.SetPosition(rbPos);
	m_ballRender.SetRotation(rbRot);
	m_ballRender.Update();
	m_ballPosition = rbPos;
}


//�`�揈���B
void Ball::Render(RenderContext& rc)
{
	m_ballRender.Draw(rc);
}