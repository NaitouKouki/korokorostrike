#include "stdafx.h"
#include "SelectPanel.h"
#include "Title.h"
#include "Game.h"
#include <random>

SelectPanel::SelectPanel() {}
SelectPanel::~SelectPanel() {}

bool SelectPanel::Start()
{
    LoadRandomImage();
    return true;
}

void SelectPanel::Update()
{
	// 方向キーで選択切り替え
    if (g_pad[0]->IsTrigger(enButtonA)) {
        m_selectedIndex = 0; // 通常モード
    }
    if (g_pad[0]->IsTrigger(enButtonX)) {
        m_selectedIndex = 1; // 10回モード
    }

    // Aボタンで確定してGameへ
    if (g_pad[0]->IsTrigger(enButtonY)) {
        ApplySelection();
        DeleteGO(this);
    }

    // Bボタンでタイトルに戻る
    if (g_pad[0]->IsTrigger(enButtonB)) {
        NewGO<Title>(0, "title");
        DeleteGO(this);
    }
}

void SelectPanel::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);

    // 選択状態を画面に文字で出す（デバッグ用）
    wchar_t text[128];
    if (m_selectedIndex == 0) {
        swprintf_s(text, L"Mode: 5 Game");
    }
    else {
        swprintf_s(text, L"Mode: 10 Game");
    }

    font.SetPosition(0.0f, -400.0f, 0.0f);
    font.SetText(text);
    font.SetColor(g_vec4Black);
    font.Draw(rc);
}

void SelectPanel::LoadRandomImage()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float r = dist(gen);
    std::string selectedPath;

    if (r < 0.05f) {
        selectedPath = m_imagePaths[2];
    }
    else if (r < 0.25f) {
        selectedPath = m_imagePaths[1];
    }
    else {
        selectedPath = m_imagePaths[0];
    }

    m_sprite.Init(selectedPath.c_str(), 1920.0f, 1080.0f);
}

void SelectPanel::ApplySelection()
{
    // ゲームオブジェクトを生成
    Game* game = NewGO<Game>(0, "game");

    // 選択内容に応じて設定変更
    if (m_selectedIndex == 1) {
        game->m_maxGameCount = 10;  // 拡張モード
    }
    else {
        game->m_maxGameCount = 5;   // 通常モード
    }
}
