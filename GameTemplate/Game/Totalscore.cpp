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
    m_score = 0;
    m_game = FindGO<Game>("game");
    return true;
}

void Totalscore::Update()
{
    wchar_t scoreText[256];
    swprintf_s(scoreText, L"Score: %d", m_score);
	m_fontRender.SetText(scoreText);
	// フォントの描画位置を決定
	m_fontRender.Draw(*g_renderContext2D);

    m_pin = FindGO<Pin>("pin");

    //// ピンが消えたらスコア加算
    if (m_pin == nullptr) {
        m_score += 1;
    }
	// ★スコアが100を超えたらリザルト画面へ
	//ただし、今回はまだリザルト画面は実装していないので、スコアのみリセットする
    if (m_score > 99) {
		m_score = 0; // スコアをリセット
        return;
    }
}

void Totalscore::Render(nsK2EngineLow::RenderContext& rc)
{
    wchar_t scoreText[256];
    swprintf_s(scoreText, L"Score: %d", m_score);
}
