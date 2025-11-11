#include "stdafx.h"
#include "Totalscore.h"
#include "Game.h"
#include "gameObject/GameObjectManager.h"

Totalscore::Totalscore() {}
Totalscore::~Totalscore() {}

bool Totalscore::Start()
{
	m_fontRender.SetPosition(600.0f, 275.0f, 500.0f);
    m_fontRender.SetScale(1.5f);
	m_fontRender.SetColor(g_vec4Gray);
    m_mainScoreFont.SetPosition(650.0f, 275.0f, 500.0f);
    m_mainScoreFont.SetColor(g_vec4Gray);
    m_scoreFonts.resize(10);
    for (int i = 0; i < 10; ++i) {
        m_scoreFonts[i] = std::make_unique<FontRender>();
        m_scoreFonts[i]->SetPosition(650.0f, 100.0f - i * 40.0f, 500.0f);
        m_scoreFonts[i]->SetColor(g_vec4Gray);
    }
    m_game = FindGO<Game>("game");
    return true;
}

void Totalscore::Update()
{
	// スコア表示更新
    wchar_t scoreText[256];
    swprintf_s(scoreText, L"Score: %d", m_gamescore);
    m_fontRender.SetText(scoreText);
    GetTotalScore();

    // メインスコア更新
    wchar_t totalText[256];
    swprintf_s(totalText, L"Total: %d", GetTotalScore());
    m_mainScoreFont.SetText(totalText);

    // 個別スコア描画更新
    for (int i = 0; i < m_game->m_maxGameCount; i++) {
        wchar_t text[64];
        if (i < 9) {
            swprintf_s(text, L"Frame  %d: %d", i + 1, m_gameScores[i]);
        }
        else {
            swprintf_s(text, L"Frame %d: %d", i + 1, m_gameScores[i]);
        }
        if (m_scoreFonts[i]) {
            m_scoreFonts[i]->SetText(text); // ポインタ経由で呼び出す    
        }
    }
    // --- 表示切り替え ---
    if (g_pad[0]->IsTrigger(enButtonUp)) {
        m_isVisible = false;  //非表示
    }
    if (g_pad[0]->IsTrigger(enButtonDown)) {
        m_isVisible = true;   //再表示
    }
}

void Totalscore::AddScore(int points)
{
    m_gamescore += points;
}

void Totalscore::RegisterGameScore()
{
    // 現在のゲーム番号を取得して登録
    int index = m_game ? m_game->m_currentGame - 1 : 0;
    if (index >= 0 && index < 10) {
        m_gameScores[index] = m_gamescore;
    }
    m_totalScore += m_gamescore;
    m_gamescore = 0;
}

void Totalscore::Render(nsK2EngineLow::RenderContext& rc)
{
    if (!m_isVisible) return;  // ← 非表示ならスキップ
    for (auto& font : m_scoreFonts) {
        font->Draw(rc);
    }
    m_fontRender.Draw(rc);
}
