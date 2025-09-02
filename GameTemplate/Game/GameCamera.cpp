#include "stdafx.h"
#include "GameCamera.h"
#include "Game.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 100.0f, 300.0f);

	//�v���C���[�̃C���X�^���X��T���B
	//m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	return true;
}

void GameCamera::Update()
{
	if (m_isCameraEvent) {
		if (!m_isInit) {
			//�΂˃J�����̏������B
			m_springCamera.Init(
				*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
				1000.0f,			//�J�����̈ړ����x�̍ő�l�B
				true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
				5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
			);
			m_isInit = true;
		}
		//�J�������X�V�B
		//�����_���v�Z����B
		// �����_�ł͎g��Ȃ��̂ň�x�R�����g�A�E�g����
		/*Vector3 target = m_player->rbPos;
		//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
		target.y += 80.0f;
		target += g_camera3D->GetForward() * 20.0f;*/

		Vector3 toCameraPosOld = m_toCameraPos;
		//�p�b�h�̓��͂��g���ăJ�������񂷁B
		float x = g_pad[0]->GetRStickXF();
		float y = g_pad[0]->GetRStickYF();
		//Y������̉�]
		Quaternion qRot;
		qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
		qRot.Apply(m_toCameraPos);
		//X������̉�]�B
		Vector3 axisX;
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 1.5f * y);
		qRot.Apply(m_toCameraPos);
		//�J�����̉�]�̏�����`�F�b�N����B
		//�����_���王�_�܂ł̃x�N�g���𐳋K������B
		//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
		//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
		Vector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//�J����������������B
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
			m_toCameraPos = toCameraPosOld;
		}

		//���_���v�Z����B
		//Vector3 pos = target + m_toCameraPos;

		//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
		//m_springCamera.SetPosition(pos);
		//m_springCamera.SetTarget(target);

		//�J�����̍X�V�B
		m_springCamera.Update();
	}
	else {
		CameraEvent();
	}
}

void GameCamera::CameraEvent()
{
	/*m_toCameraTargetPos.Lerp(t, m_game->m_flagPos, m_player->m_position);
	t += 0.005;
	g_camera3D->SetTarget(m_toCameraTargetPos);
	Vector3 playerPos = m_player->m_position;
	playerPos.y += 600.0f;

	Vector3 flagDirection = m_player->m_position - m_game->m_flagPos;
	flagDirection.Normalize();
	flagDirection *= 500.0f;
	playerPos += flagDirection;

	g_camera3D->SetPosition(playerPos);

	if (t > 1.0f) {
		m_isCameraEvent = true;
	}*/
}
