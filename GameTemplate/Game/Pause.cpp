#include "stdafx.h"
#include "Pause.h"
#include "Player.h"
#include "GameCamera.h"
#include "Pin.h"
#include "Title.h"
#include "Totalscore.h"
#include "FrameCount.h"
#include "BackGround.h"
#include "Game.h"

Pause::Pause() {}
Pause::~Pause() {}

bool Pause::Start()
{
    m_sprite.Init("Assets/Sprite/suiteiPause.DDS", 1920.0f, 1080.0f);
    m_sprite.SetPosition({0.0f, 0.0f, 0.0f});
    return true;
}

void Pause::Update()
{
    // Bボタンでポーズ解除
    if (g_pad[0]->IsTrigger(enButtonStart)) {
        // playerを一度削除し再生成する
		Player* player = FindGO<Player>("player");
        if (player != nullptr) {
            player->SetPause(false);
        }
        DeleteGO(this); // 自身を削除
        return;
    }

    // 選択肢切り替えなど（必要なら）
    if (g_pad[0]->IsTrigger(enButtonY)) {        
        NewGO<Title>(0, "title"); 
        auto pins = FindGOs<Pin>("pin");
        for (auto pin : pins) {
            DeleteGO(pin);
        }
		DeleteGO(FindGO<Player>("player"));
		DeleteGO(FindGO<GameCamera>("gamecamera"));
		DeleteGO(FindGO<Totalscore>("totalscore"));
		DeleteGO(FindGO<FrameCount>("framecount"));
		DeleteGO(FindGO<BackGround>("background"));
        DeleteGO(FindGO<Game>("game"));
        DeleteGO(this);
    }
}

void Pause::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);
}
