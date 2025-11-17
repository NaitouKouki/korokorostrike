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
    // ボタン（幅・高さは任意
    m_firstSprite.Init("Assets/Sprite/first.DDS", 400.0f, 140.0f);
    m_secondSprite.Init("Assets/Sprite/second.DDS", 400.0f, 140.0f);

    m_firstBasePos = Vector3(0.0f, 200.0f, 0.0f);
    m_secondBasePos = Vector3(500.0f, 200.0f, 0.0f);

    // 初期配置（必ず毎フレーム SetPosition するので Start では基準のみ）
    m_selectedIndex = 0;
    m_animTime = 0.0f;
    return true;
}

void SelectPanel::Update()
{

    // アニメーション時間（フレーム毎の加算）
    float dt = GameTime().GetFrameDeltaTime(); // あれば使う。なければ小さめの固定値 (1/60) を使う
    m_animTime += dt;

    // 選択中は少し上下に動く（bob アニメ）＋若干拡大
    float bob = sinf(m_animTime * 6.0f) * 6.0f; // 振幅6px, 周期は調整可
    Vector3 startPos = m_firstBasePos;
    Vector3 selectPos = m_secondBasePos;
    Vector3 startScale = Vector3::One;
    Vector3 selectScale = Vector3::One;

    const float HIGHLIGHT_OFFSET = -12.0f; // 選択時に上に移動させるなら負
    const float HIGHLIGHT_SCALE = 1.08f;   // 選択時拡大率
	// 入力処理
    if (g_pad[0]->IsTrigger(enButtonDown))
    {
        m_nextIndex = 1;
    }
    if (g_pad[0]->IsTrigger(enButtonUp))
    {
        m_nextIndex = 0;
    }
    if (m_nextIndex == 0) {
        // 方向キーで選択切り替え
        if (g_pad[0]->IsTrigger(enButtonA)) {
            m_selectedIndex = 0; // 通常モード
        }
        if (g_pad[0]->IsTrigger(enButtonX)) {
            m_selectedIndex = 1; // 10回モード
        }
    }
    if(m_nextIndex == 1)
    {
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

        
    if (m_selectedIndex == 0)
    {
        startPos.y += bob + HIGHLIGHT_OFFSET;
        startScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        // 非選択は少し暗くする（SetMulColorが使えるなら）
        m_secondSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_firstSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    else
    {
        selectPos.y += bob + HIGHLIGHT_OFFSET;
        selectScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_firstSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_secondSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    if(m_nextIndex == 1)
    {
		//インデックスが1のときは動かないようにする
		startPos = m_firstBasePos;
		selectPos = m_secondBasePos;
	}

    m_firstSprite.SetPosition(startPos);
    m_firstSprite.SetScale(startScale);
    m_firstSprite.Update();

    m_secondSprite.SetPosition(selectPos);
    m_secondSprite.SetScale(selectScale);
    m_secondSprite.Update();
}

void SelectPanel::Render(RenderContext& rc)
{
    // 選択状態を画面に文字で出す(デバッグ用)
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

    m_sprite.Draw(rc);
    m_firstSprite.Draw(rc);
    m_secondSprite.Draw(rc);
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
