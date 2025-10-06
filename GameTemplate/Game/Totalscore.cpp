#include "stdafx.h"
#include "Totalscore.h"
#include "Title.h"
#include "Game.h"
#include "Pin.h"
#include "gameObject/GameObjectManager.h"


Totalscore::Totalscore()
{
}

Totalscore::~Totalscore()
{
}

bool Totalscore::Start()
{
	m_fontRender.SetPosition(650.0f,300.0f, 500.0f); // 左上に表示
    m_game = FindGO<Game>("game");
    return true;
}

void Totalscore::Update()
{
    // スコア表示
        wchar_t scoreText[256];
        swprintf_s(scoreText, L"Score: %d", m_score);
        m_fontRender.SetText(scoreText);
        m_fontRender.Draw(*g_renderContext2D);

        //倒れたピン数をカウント
        for (int i = 0; i < 10; i++) {
            if (m_game->pins[i] == nullptr) {
                fallenPins++;
            }
        }

        //その数をスコアに反映（倒れた分だけ）
        //m_score = fallenPins * 1;   // 1本=1点ならこのまま
        // 2倍,10点制などにするならここで調整可

		if (m_score > 9) {// 10点超えたらゲーム終了
            m_score = 1000000000;
            m_game->m_gameState = Game::enResult;
            return;
        }

}

void Totalscore::AddScore(int p)
{
    m_score += p;
}

void Totalscore::Render(nsK2EngineLow::RenderContext& rc)
{
    wchar_t scoreText[256];
    swprintf_s(scoreText, L"Score: %d", m_score);
}
