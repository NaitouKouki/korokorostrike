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
	m_firstSprite.Init(m_imagePaths[3].c_str(), 300.0f, 100.0f);  // 5回モード
	m_secondSprite.Init(m_imagePaths[4].c_str(), 300.0f, 100.0f); // 10回モード
	m_thirdSprite.Init(m_imagePaths[5].c_str(), 300.0f, 200.0f); // スタートボタン
	m_fourthSprite.Init(m_imagePaths[6].c_str(), 300.0f, 200.0f); // 選択ボタン

    m_firstBasePos = Vector3(200.0f, 200.0f, 0.0f);
    m_secondBasePos = Vector3(500.0f, 200.0f, 0.0f);
	m_thirdBasePos = Vector3(200.0f, 0.0f, 0.0f);
	m_fourthBasePos = Vector3(500.0f, 0.0f, 0.0f);

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
    Vector3 firstPos = m_firstBasePos;
    Vector3 secondPos = m_secondBasePos;
	Vector3 thirdPos = m_thirdBasePos;
	Vector3 fourthPos = m_fourthBasePos;

    Vector3 firstScale = Vector3::One;
    Vector3 secondScale = Vector3::One;
	Vector3 thirdScale = Vector3::One;
	Vector3 fourthScale = Vector3::One;

    const float HIGHLIGHT_OFFSET = -12.0f; // 選択時に上に移動させるなら負
    const float HIGHLIGHT_SCALE = 1.08f;   // 選択時拡大率
	// 入力処理
    if (g_pad[0]->IsTrigger(enButtonDown))
    {
        if (m_nextIndex == 0) {
            m_nextIndex = 1;
        }
        else if(m_nextIndex == 1)
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
    }
    if (m_nextIndex == 1)
    {
        if(g_pad[0]->IsTrigger(enButtonLeft))
        {
			m_obstacleIndex = 0; // 障害物あり
		}
        if (g_pad[0]->IsTrigger(enButtonRight))
        {
			m_obstacleIndex = 1; // 障害物なし
        }
    }
    if(m_nextIndex == 2)
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

        
    if (m_gameCountIndex == 0)
    {
        firstPos.y += bob + HIGHLIGHT_OFFSET;
        firstScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        // 非選択は少し暗くする（SetMulColorが使えるなら）
        m_secondSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_firstSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
	else if (m_gameCountIndex == 1)
    {
        secondPos.y += bob + HIGHLIGHT_OFFSET;
        secondScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_firstSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_secondSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }

    if (m_obstacleIndex == 0)
    {
        thirdPos.y += bob + HIGHLIGHT_OFFSET;
        thirdScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_thirdSprite.SetMulColor(Vector4(1, 1, 1, 1));
        m_fourthSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
    }
    else if (m_obstacleIndex == 1)
    {
        fourthPos.y += bob + HIGHLIGHT_OFFSET;
        fourthScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_thirdSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_fourthSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    if(m_nextIndex == 1 || m_nextIndex == 2)
    {
		//インデックスが1のときは動かないようにする
		firstPos = m_firstBasePos;
		secondPos = m_secondBasePos;
	}
    if (m_nextIndex == 0 || m_nextIndex == 2) 
    {
		thirdPos = m_thirdBasePos;
		fourthPos = m_fourthBasePos;
    }

    m_firstSprite.SetPosition(firstPos);
    m_firstSprite.SetScale(firstScale);
    m_firstSprite.Update();

    m_secondSprite.SetPosition(secondPos);
    m_secondSprite.SetScale(secondScale);
    m_secondSprite.Update();

	m_thirdSprite.SetPosition(thirdPos);
	m_thirdSprite.SetScale(thirdScale);
	m_thirdSprite.Update();

	m_fourthSprite.SetPosition(fourthPos);
	m_fourthSprite.SetScale(fourthScale);
	m_fourthSprite.Update();
}

void SelectPanel::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);
    m_firstSprite.Draw(rc);
    m_secondSprite.Draw(rc);
	m_thirdSprite.Draw(rc);
	m_fourthSprite.Draw(rc);
}

void SelectPanel::LoadRandomImage()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    float r = dist(gen);
    std::string selectedPath;

    if (r < 0.03f) {
        selectedPath = m_imagePaths[2];
    }
    else if (r < 0.05f) {
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
}
