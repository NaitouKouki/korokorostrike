#include "stdafx.h"
#include "FrameCount.h"
#include "Game.h"

FrameCount::FrameCount() {}
FrameCount::~FrameCount() {}

bool FrameCount::Start()
{
    m_game = FindGO<Game>("game");
    m_fontRender.SetPosition(650.0f, 180.0f, 500.0f); // スコアより上に表示
    m_fontRender.SetColor(g_vec4Gray);
    return true;
}

void FrameCount::Update()
{
    // Gameから値を同期（自動更新タイプ）
    if (m_game) {
        m_currentFrame = m_game->m_currentGame;   // 今のフレーム数
        m_maxFrame = m_game->m_maxGameCount;        // 最大回数
    }    

    wchar_t frameText[256];
    
    if (m_maxFrame == 5) {
        swprintf_s(frameText, L"Frame: %d / %d", m_currentFrame, m_maxFrame);
    }
    else {
        swprintf_s(frameText, L"Frame: %d /%d", m_currentFrame, m_maxFrame);
    }    
    
    m_fontRender.SetText(frameText);
    
    // --- 表示切り替え ---
    if (g_pad[0]->IsTrigger(enButtonUp)) {
        m_isVisible = false;  //非表示
    }
    if (g_pad[0]->IsTrigger(enButtonDown)) {
        m_isVisible = true;   //再表示
    }
}

void FrameCount::Render(nsK2EngineLow::RenderContext& rc)
{
    if (!m_isVisible) return;
    m_fontRender.Draw(rc);
}

void FrameCount::SetFrame(int current, int max)
{
    m_currentFrame = current;
    m_maxFrame = max;
}

void FrameCount::AddFrame()
{
    m_currentFrame++;
}

void FrameCount::Reset()
{
    m_currentFrame = 1;
}
