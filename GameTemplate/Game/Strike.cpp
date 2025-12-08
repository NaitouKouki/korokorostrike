#include "stdafx.h"
#include "Strike.h"
#include "Player.h"

Strike::Strike() {}
Strike::~Strike() {}

bool Strike::Start()
{
    // ストライク画像の読み込み
    m_sprite.Init("Assets/Sprite/strike.DDS", 1200.0f,600.0f);

    m_sprite.SetPosition(m_position);

    return true;
}

void Strike::Update()
{
    // 左へ移動
    m_position.x -= slideSpeed * 3;

    // タイマー進行
    m_timer += g_gameTime->GetFrameDeltaTime();
    m_sprite.SetPosition(m_position);
    // 画面中央到達後、一定時間表示して消える
    if (m_position.x <= 0.0f)
    {
        if (m_timer < 3.0f)
        {
            m_position.x = 0.0f;   // 止める
            if (m_timer >= 3.0f) {
                return;
            }
        }
    }
    if (m_position.x <= -2000.0f) {
        DeleteGO(this);
    }
    m_sprite.Update();
}

void Strike::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);
}
