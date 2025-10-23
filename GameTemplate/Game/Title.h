#pragma once
#include "gameObject/IGameObject.h"

// 前方宣言
class Game;
class SelectPanel;

/// <summary>
/// タイトル画面クラス
/// ・背景表示
/// ・「START」「SELECT」ボタンの描画と選択
/// ・Aボタンで遷移
/// </summary>
class Title : public IGameObject
{
public:
    Title();
    ~Title();

    bool Start() override;                      // 初期化
    void Update() override;                     // 入力とアニメ処理
    void Render(RenderContext& rc) override;    // 描画処理

private:

    SpriteRender m_titleSprite;    // タイトル背景
    SpriteRender m_startSprite;    // 「START」ボタン
    SpriteRender m_selectSprite;   // 「SELECT」ボタン

    int   m_selectedIndex = 0;     // 現在の選択（0 = Start / 1 = Select）
    float m_animTime = 0.0f;       // アニメーション時間

    // ボタンの基準位置（中央基準）
    Vector3 m_startBasePos = Vector3::Zero;
    Vector3 m_selectBasePos = Vector3::Zero;
};
