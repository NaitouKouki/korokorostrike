#pragma once

class Game;

#include "gameObject/IGameObject.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	// �X�^�[�g
	bool Start() override;
	// �A�b�v�f�[�g
	void Update() override;
	// �����_�[
	void Render(nsK2EngineLow::RenderContext& rc) override;

	Vector3         m_ballPosition = Vector3::Zero;
	Vector3         m_scale = Vector3::One;		// �X�P�[��

	// �����̈ʒu�Ɖ�]���擾���邽�߂̈ꎞ�ϐ�
	Vector3			rbPos = Vector3::Zero;
	Quaternion		rbRot = Quaternion::Identity;
	RigidBodyInitData	rbInitData;
	RigidBody			m_rigidBody;	// ����

private:
	CharacterController	 m_charaCon;		// �L�����R��
	ModelRender			m_ballRender;
	SphereCollider		m_sphereCollider;	// �{�[���̓����蔻��

	Game* m_game = nullptr;
};