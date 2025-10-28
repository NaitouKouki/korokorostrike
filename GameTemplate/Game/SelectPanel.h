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
    void LoadRandomImage();
    void ApplySelection();   // ← 選択を確定してGameへ渡す

    FontRender font;

    std::vector<std::string> m_imagePaths = {
        "Assets/Sprite/Select.DDS",
        "Assets/Sprite/SelectZ.DDS",
        "Assets/Sprite/Select_ANYS.DDS"
    };
};
