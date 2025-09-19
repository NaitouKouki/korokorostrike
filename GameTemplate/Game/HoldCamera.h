#pragma once

#include "camera/SpringCamera.h"
#include "Player.h" // m_playerを使う場合は前方宣言またはインクルード

class Game;
class Player;

class HoldCamera : public IGameObject
{
public:
    HoldCamera();
    ~HoldCamera();
    // スタート
    bool Start() override;
    // アップデート
    void Update() override;
    // レンダー
    void Render(RenderContext& rc) override;

    Vector3 m_toCameraPos = Vector3(0.0f, 100.0f, 300.0f);
    Vector3 m_toCameraTargetPos = Vector3::One;

    Game* m_game = nullptr;
    Player* m_player = nullptr; // プレイヤー参照
    SpringCamera m_springCamera; // 三人称カメラ

    bool m_isCameraEvent = false;
    bool m_isInit = false;
};

