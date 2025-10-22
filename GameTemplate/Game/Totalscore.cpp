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
        m_fontRender.SetColor(g_vec4Black);
        m_fontRender.Draw(*g_renderContext2D);
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
