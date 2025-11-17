#pragma once
#include "gameObject/IGameObject.h"

class SelectPanel : public IGameObject
{
public:
    SelectPanel();
    ~SelectPanel();

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    SpriteRender m_sprite;
    int m_selectedIndex = 0; // 0: 通常, 1: 10回モード
	int m_nextIndex = 0;// 次に選択されるインデックス
    float m_animTime = 0.0f;
    void LoadRandomImage();
    void ApplySelection();   // ← 選択を確定してGameへ渡す
	SpriteRender m_firstSprite;
	SpriteRender m_secondSprite;

    FontRender font;

    std::vector<std::string> m_imagePaths = {
        "Assets/Sprite/Select.DDS",
        "Assets/Sprite/SelectZ.DDS",
        "Assets/Sprite/Select_ANYS.DDS"
    };

    // ボタンの基準位置（中央基準）
    Vector3 m_firstBasePos = Vector3::Zero;
    Vector3 m_secondBasePos = Vector3::Zero;
};
