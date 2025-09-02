#pragma once

//�΂˃J�������g�p�������ꍇ�́ASpringCamera���C���N���[�h����B
#include "camera/SpringCamera.h"

//�N���X�錾
class Player;//����������l�ɕۗ�
class Game;

class GameCamera :public IGameObject
{
public:

	GameCamera();
	~GameCamera();
	//�X�^�[�g
	bool Start();
	//�A�b�v�f�[�g
	void Update();
	//�J�����C�x���g
	void CameraEvent();

private:
	Vector3			m_toCameraPos = Vector3::One;
	Vector3			m_toCameraTargetPos = Vector3::One;
	SpringCamera	m_springCamera;					//�΂˃J����

	Game* m_game = nullptr;
	Player* m_player = nullptr;//�ۗ�

	bool	m_isCameraEvent = false;
	bool	m_isInit = false;
	float	t = 0.0f;
};

