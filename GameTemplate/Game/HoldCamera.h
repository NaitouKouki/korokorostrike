#pragma once

#include "camera/SpringCamera.h"
#include "Player.h" // m_player���g���ꍇ�͑O���錾�܂��̓C���N���[�h

class Game;
class Player;

class HoldCamera : public IGameObject
{
public:
    HoldCamera();
    ~HoldCamera();
    // �X�^�[�g
    bool Start() override;
    // �A�b�v�f�[�g
    void Update() override;
    // �����_�[
    void Render(RenderContext& rc) override;

    Vector3 m_toCameraPos = Vector3(0.0f, 100.0f, 300.0f);
    Vector3 m_toCameraTargetPos = Vector3::One;

    Game* m_game = nullptr;
    Player* m_player = nullptr; // �v���C���[�Q��
    SpringCamera m_springCamera; // �O�l�̃J����

    bool m_isCameraEvent = false;
    bool m_isInit = false;
};

