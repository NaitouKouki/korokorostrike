#include "stdafx.h"
#include "HoldCamera.h"
#include "Game.h"
#include "Player.h"

HoldCamera::HoldCamera() {}
HoldCamera::~HoldCamera() {}

bool HoldCamera::Start()
{
    // �^�[�Q�b�g����J�����ʒu�܂ł̃x�N�g����ݒ�
    m_toCameraPos.Set(0.0f, 100.0f, 300.0f);

    // �v���C���[�i�{�[���j�̃C���X�^���X��T��
    m_player = FindGO<Player>("player");
    m_game = FindGO<Game>("game");

    // �J�����C�x���g�i�Ǐ]�j��L����
    m_isCameraEvent = true;

    return true;
}

void HoldCamera::Update()
{
    if (m_isCameraEvent) {
        if (!m_isInit) {
            // �O�l�̃J�����̏�����
            m_springCamera.Init(
                *g_camera3D,		// �O�l�̃J�����̋������s���J�������w��
                1000.0f,			// �J�����̈ړ����x�̍ő�l
                true,				// �J�����̊���(�X���[�W���O)��L���ɂ��邩
                5.0f				// �J�����ɐݒ肷��o�l�̍���
            );
            m_isInit = true;
        }

        Vector3 toCameraPosOld = m_toCameraPos;
        // �p�b�h���͂ŃJ��������]
        float x = g_pad[0]->GetRStickXF();
        float y = g_pad[0]->GetRStickYF();
        // Y����]
        Quaternion qRot;
        qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
        qRot.Apply(m_toCameraPos);
        // X����]
        Vector3 axisX;
        axisX.Cross(Vector3::AxisY, m_toCameraPos);
        axisX.Normalize();
        qRot.SetRotationDeg(axisX, 1.5f * y);
        qRot.Apply(m_toCameraPos);
        // �J�����̉�]�̐������`�F�b�N
        // �^�[�Q�b�g����J�����܂ł̃x�N�g���𐳋K��
        // ��p/�p�̐���
        Vector3 toPosDir = m_toCameraPos;
        toPosDir.Normalize();
        if (toPosDir.y < -0.5f) {
            // �J������������������
            m_toCameraPos = toCameraPosOld;
        }
        else if (toPosDir.y > 0.8f) {
            // �J�����������������
            m_toCameraPos = toCameraPosOld;
        }

        // �{�[���̌��݈ʒu�ɒǏ]���邽�߃^�[�Q�b�g/�ʒu��ݒ�
        if (m_player != nullptr) {
            const Vector3 target = m_player->m_ballPosition;
            const Vector3 pos = target + m_toCameraPos;
            m_springCamera.SetTarget(target);
            m_springCamera.SetPosition(pos);
        }
        else {
            // �{�[����������Ȃ��ꍇ�̓f�t�H���g�ʒu�ɐݒ�
            const Vector3 target = Vector3::Zero;
            const Vector3 pos = target + m_toCameraPos;
            m_springCamera.SetTarget(target);
            m_springCamera.SetPosition(pos);
        }

        // �J�����X�V
        m_springCamera.Update();
    }
}

void HoldCamera::Render(RenderContext& rc)
{
    // �K�v�ɉ����ĕ`�揈�����L�q

}
