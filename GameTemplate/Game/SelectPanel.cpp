#include "stdafx.h"
#include "SelectPanel.h"
#include "Title.h"
#include "Game.h"
#include <random>
#include <iostream>

SelectPanel::SelectPanel() {}
SelectPanel::~SelectPanel() {}

bool SelectPanel::Start()
{            
    LoadRandomImage();
    // ボタン（幅・高さは任意
	m_fiveCountSprite.Init(m_imagePaths[3].c_str(), 200.0f, 100.0f);  // 5回モード
	m_tenCountSprite.Init(m_imagePaths[4].c_str(), 200.0f, 100.0f); // 10回モード
	m_obstacleSprite.Init(m_imagePaths[5].c_str(), 300.0f, 260.0f); // 障害物ありボタン
	m_nothingSprite.Init(m_imagePaths[6].c_str(), 300.0f, 260.0f); // 障害物なしボタン
	m_backTitleButtonSprite.Init(m_imagePaths[7].c_str(), 400.0f, 200.0f); // タイトルへ戻るボタン
	m_customStartButtonSprite.Init(m_imagePaths[8].c_str(), 400.0f, 200.0f); // ゲームスタートボタン
    m_frameBaseSprite.Init(m_imagePaths[9].c_str(), 400.0f, 200.0f);//フレーム数選択
    m_obstacleBaseSprite.Init(m_imagePaths[10].c_str(), 400.0f, 200.0f);//障害物の有無

    m_fiveCountBasePos = Vector3(200.0f, 200.0f, 0.0f);
    m_tenCountBasePos = Vector3(500.0f, 200.0f, 0.0f);
	m_obstacleBasePos = Vector3(200.0f, 0.0f, 0.0f);
	m_nothingBasePos = Vector3(500.0f, 0.0f, 0.0f);
	m_backTitleButtonBasePos = Vector3(200.0f, -200.0f, 0.0f);
	m_customStartButtonBasePos = Vector3(500.0f, -200.0f, 0.0f);
    m_frameBasePos = Vector3(-200.0f,200.0f,0.0f);
    m_obstacleBaseBasePos = Vector3(-200.0f,0.0f,0.0f);

    // 初期配置（必ず毎フレーム SetPosition するので Start では基準のみ）
    m_gameCountIndex = 0;
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
    Vector3 m_fiveCountPos = m_fiveCountBasePos;
    Vector3 m_tenCountPos = m_tenCountBasePos;
    Vector3 m_obstaclePos = m_obstacleBasePos;
    Vector3 m_nothingPos = m_nothingBasePos;
    Vector3 m_backTitleButtonPos = m_backTitleButtonBasePos;
    Vector3 m_customStartButtonPos = m_customStartButtonBasePos;
    Vector3 m_frameBaseposition = m_frameBasePos;
    Vector3 m_obstacleBaseposition = m_obstacleBaseBasePos;

    Vector3 m_fiveCountScale = Vector3::One;
    Vector3 m_tenCountScale = Vector3::One;
    Vector3 m_obstacleScale = Vector3::One;
    Vector3 m_nothingScale = Vector3::One;
    Vector3 m_backTitleButtonScale = Vector3::One;
    Vector3 m_customStartButtonScale = Vector3::One;

    const float HIGHLIGHT_OFFSET = -12.0f; // 選択時に上に移動させるなら負
    const float HIGHLIGHT_SCALE = 1.08f;   // 選択時拡大率
    // 入力処理
    if (g_pad[0]->IsTrigger(enButtonDown))
    {
        if (m_nextIndex == 0) {
            m_nextIndex = 1;
        }
        else if (m_nextIndex == 1)
        {
            m_nextIndex = 2;
        }
    }
    if (g_pad[0]->IsTrigger(enButtonUp))
    {
        if (m_nextIndex == 2)
        {
            m_nextIndex = 1;
        }
        else if (m_nextIndex == 1)
        {
            m_nextIndex = 0;
        }
    }
    if (m_nextIndex == 0) {
        // 方向キーで選択切り替え
        if (g_pad[0]->IsTrigger(enButtonLeft)) {
            m_gameCountIndex = 0; // 通常モード
        }
        if (g_pad[0]->IsTrigger(enButtonRight)) {
            m_gameCountIndex = 1; // 10回モード
        }
        m_frameBaseSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }
    if (m_nextIndex == 1)
    {
        if (g_pad[0]->IsTrigger(enButtonLeft))
        {
            m_obstacleIndex = 0; // 障害物あり
        }
        if (g_pad[0]->IsTrigger(enButtonRight))
        {
            m_obstacleIndex = 1; // 障害物なし
        }
        m_obstacleBaseSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }
    if (m_nextIndex == 2)
    {
        if (g_pad[0]->IsTrigger(enButtonLeft))
        {
            m_decisionIndex = 0;
        }
        if (g_pad[0]->IsTrigger(enButtonRight))
        {
            m_decisionIndex = 1;
        }
        if (m_decisionIndex == 0)
        {
            // Aボタンで確定してGameへ
            if (g_pad[0]->IsTrigger(enButtonA)) {
                ApplySelection();
                DeleteGO(this);
            }
        }
        else {
            // Bボタンでタイトルに戻る
            if (g_pad[0]->IsTrigger(enButtonA)) {
                NewGO<Title>(0, "title");
                DeleteGO(this);
            }
        }
    }

    if (m_gameCountIndex == 0)
    {
        m_fiveCountPos.y += bob + HIGHLIGHT_OFFSET;
        m_fiveCountScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        // 非選択は少し暗くする（SetMulColorが使えるなら）
        m_tenCountSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_fiveCountSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    else if (m_gameCountIndex == 1)
    {
        m_tenCountPos.y += bob + HIGHLIGHT_OFFSET;
        m_tenCountScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_fiveCountSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_tenCountSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }

    if (m_obstacleIndex == 0)
    {
        m_obstaclePos.y += bob + HIGHLIGHT_OFFSET;
        m_obstacleScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_obstacleSprite.SetMulColor(Vector4(1, 1, 1, 1));
        m_nothingSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
    }
    else if (m_obstacleIndex == 1)
    {
        m_nothingPos.y += bob + HIGHLIGHT_OFFSET;
        m_nothingScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_obstacleSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_nothingSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    if (m_decisionIndex == 0)
    {
        m_backTitleButtonPos.y += bob + HIGHLIGHT_OFFSET;
        m_backTitleButtonScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_customStartButtonSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_backTitleButtonSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    if (m_decisionIndex == 1)
    {
        m_customStartButtonPos.y += bob + HIGHLIGHT_OFFSET;
        m_customStartButtonScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_customStartButtonSprite.SetMulColor(Vector4(1, 1, 1, 1));
        m_backTitleButtonSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
    }
    if (m_nextIndex == 0 || m_nextIndex == 1)
    {
        m_customStartButtonSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_backTitleButtonSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
    }
    if (m_nextIndex == 1 || m_nextIndex == 2)
    {
        //インデックスが1のときは動かないようにする
        m_fiveCountPos = m_fiveCountBasePos;
        m_tenCountPos = m_tenCountBasePos;
        m_frameBaseSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
    }
    if (m_nextIndex == 0 || m_nextIndex == 2)
    {
        m_obstaclePos = m_obstacleBasePos;
        m_nothingPos = m_nothingBasePos;
        m_obstacleBaseSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
    }
    if (m_nextIndex == 0 || m_nextIndex == 1)
    {
        m_backTitleButtonPos = m_backTitleButtonBasePos;
        m_customStartButtonPos = m_customStartButtonBasePos;
    }

    m_fiveCountSprite.SetPosition(m_fiveCountPos);
    m_fiveCountSprite.SetScale(m_fiveCountScale);
    m_fiveCountSprite.Update();

    m_tenCountSprite.SetPosition(m_tenCountPos);
    m_tenCountSprite.SetScale(m_tenCountScale);
    m_tenCountSprite.Update();

    m_obstacleSprite.SetPosition(m_obstaclePos);
    m_obstacleSprite.SetScale(m_obstacleScale);
    m_obstacleSprite.Update();

    m_nothingSprite.SetPosition(m_nothingPos);
    m_nothingSprite.SetScale(m_nothingScale);
    m_nothingSprite.Update();

    m_backTitleButtonSprite.SetPosition(m_backTitleButtonPos);
    m_backTitleButtonSprite.SetScale(m_backTitleButtonScale);
    m_backTitleButtonSprite.Update();

    m_customStartButtonSprite.SetPosition(m_customStartButtonPos);
    m_customStartButtonSprite.SetScale(m_customStartButtonScale);
    m_customStartButtonSprite.Update();

    m_frameBaseSprite.SetPosition(m_frameBaseposition);
    m_frameBaseSprite.Update();

    m_obstacleBaseSprite.SetPosition(m_obstacleBaseposition);
    m_obstacleBaseSprite.Update();
}

void SelectPanel::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);
    m_fiveCountSprite.Draw(rc);
    m_tenCountSprite.Draw(rc);
    m_obstacleSprite.Draw(rc);
    m_nothingSprite.Draw(rc);
    m_backTitleButtonSprite.Draw(rc);
    m_customStartButtonSprite.Draw(rc);
    m_frameBaseSprite.Draw(rc);
    m_obstacleBaseSprite.Draw(rc);
}

        void SelectPanel::LoadRandomImage()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);

            float r = dist(gen);
            std::string selectedPath;

            if (r < 0.01f) {
                selectedPath = m_imagePaths[2];
            }
            else if (r < 0.02f) {
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
    if (m_gameCountIndex == 1) {
        game->m_maxGameCount = 10;  // 拡張モード
    }
    else {
        game->m_maxGameCount = 5;   // 通常モード
    }
    if (m_obstacleIndex == 1) {
        //障害物もここで生成しておく
        std::cout<<"otu";
    }
    else {
        game->EnableObstacle();
    }
}
