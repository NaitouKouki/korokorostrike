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
    // フォントの初期設定（画面右上あたり）
    m_fontRender.SetPosition(650.0f, 300.0f, 500.0f);
    m_fontRender.SetColor(g_vec4Black);
    m_game = FindGO<Game>("game");
    return true;
}

void Totalscore::Update()
{
    // スコアテキスト生成
    wchar_t scoreText[256];
    swprintf_s(scoreText, L"Score: %d", m_gamescore);

    // フォント描画設定
    m_fontRender.SetText(scoreText);
    m_fontRender.Draw(*g_renderContext2D);
	// 合計スコア取得
    GetTotalScore();
}

void Totalscore::AddScore(int points)
{
    m_score += points;
}

void Totalscore::Render(nsK2EngineLow::RenderContext& rc)
{
    // 必要ならここに3D描画処理を追加
}
