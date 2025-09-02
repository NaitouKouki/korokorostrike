#pragma once

class Game;

class Ball : public IGameObject
{
public:
	Ball();
	~Ball();
	//�X�^�[�g
	bool Start();
	//�A�b�v�f�[�g
	void Update();
	//�����_�[
	void Render(RenderContext& rc);

	Vector3         m_position = Vector3::Zero;	//���W�B
	Vector3         m_ballPosition = Vector3::Zero;
	Vector3         m_scale = Vector3::One;		//�X�P�[��

	// ���̂̈ʒu�Ɖ�]���擾����
	Vector3			rbPos = Vector3::Zero;
	Quaternion		rbRot = Quaternion::Identity;
	RigidBodyInitData	rbInitData;
	RigidBody			m_rigidBody;	// ����

private:
	CharacterController     m_charaCon;		//�L�����R��
	ModelRender			m_ballRender;
	SphereCollider		m_sphereCollider;	// �{�[���̌`��

	Game* m_game = nullptr;
};