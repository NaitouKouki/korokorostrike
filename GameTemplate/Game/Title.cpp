#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "SelectPanel.h"

Title::Title(){}
Title::~Title(){}

namespace 
{
    // 画面サイズ（必要なら実際のゲームの値に合わせて変更）
    static const float SCREEN_W = 1920.0f;
    static const float SCREEN_H = 1080.0f;
    const float HIGHLIGHT_OFFSET = -12.0f; // 選択時に上に移動させるなら負
    const float HIGHLIGHT_SCALE = 1.08f;   // 選択時拡大率
}

bool Title::Start()
{
    // 背景（フルスクリーン）
    m_titleSprite.Init("Assets/Sprite/Title.DDS", SCREEN_W, SCREEN_H);
    m_titleSprite.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); // ここはエンジンの原点に合わせる

    // ボタン（幅・高さは任意）
    m_startSprite.Init("Assets/Sprite/ingame.DDS", 500.0f, 480.0f);
    m_selectSprite.Init("Assets/Sprite/custom.DDS", 600.0f, 410.0f);

    m_startBasePos = Vector3(-400.0f, -200.0f, 0.0f); 
    m_selectBasePos = Vector3(400.0f, -200.0f, 0.0f);  

    // 初期配置（必ず毎フレーム SetPosition するので Start では基準のみ）
    m_selectedIndex = 0;
    m_animTime = 0.0f;

    return true;
}

void Title::Update()
{
    // アニメーション時間（フレーム毎の加算）
    float dt = GameTime().GetFrameDeltaTime(); // あれば使う。なければ小さめの固定値 (1/60) を使う
    m_animTime += dt;

    if (g_pad[0]->IsTrigger(enButtonRight)) {
        m_selectedIndex = 1;
    }
    else if (g_pad[0]->IsTrigger(enButtonLeft)) {
        m_selectedIndex = 0;
    }

    // 決定（Aボタン）
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        if (m_selectedIndex == 0) {
            NewGO<Game>(0, "game");
            DeleteGO(this);
            return;
        }
        else {
            NewGO<SelectPanel>(0, "select");
            DeleteGO(this);
            return;
        }
    }

    // ----- 毎フレームでボタン位置・スケールを更新する -----
    // 選択中は少し上下に動く（bob アニメ）＋若干拡大
    float bob = sinf(m_animTime * 6.0f) * 6.0f; // 振幅6px, 周期は調整可
    Vector3 startPos = m_startBasePos;
    Vector3 selectPos = m_selectBasePos;
    Vector3 startScale = Vector3::One;
    Vector3 selectScale = Vector3::One;

    if (m_selectedIndex == 0) {
        startPos.y += bob + HIGHLIGHT_OFFSET;
        startScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        // 非選択は少し暗くする（SetMulColorが使えるなら）
        m_selectSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_startSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }
    else {
        selectPos.y += bob + HIGHLIGHT_OFFSET;
        selectScale = Vector3(HIGHLIGHT_SCALE, HIGHLIGHT_SCALE, 1.0f);
        m_startSprite.SetMulColor(Vector4(0.6f, 0.6f, 0.6f, 1.0f));
        m_selectSprite.SetMulColor(Vector4(1, 1, 1, 1));
    }

    m_startSprite.SetPosition(startPos);
    m_startSprite.SetScale(startScale);
    m_startSprite.Update(); 

    m_selectSprite.SetPosition(selectPos);
    m_selectSprite.SetScale(selectScale);
    m_selectSprite.Update();
}

void Title::Render(RenderContext& rc)
{
    // 背景
    m_titleSprite.Draw(rc);

    // ボタン（描画順も重要）
    m_startSprite.Draw(rc);
    m_selectSprite.Draw(rc);
}
