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
    int m_gameCountIndex = 0; // 0: 通常, 1: 10回モード
	int m_obstacleIndex = 0; // 0: 障害物あり, 1: 障害物なし
	int m_selectIndex = 0;
	int m_nextIndex = 0;// 次に選択されるインデックス
    float m_animTime = 0.0f;
    void LoadRandomImage();
    void ApplySelection();   // ← 選択を確定してGameへ渡す
	SpriteRender m_firstSprite;
	SpriteRender m_secondSprite;
	SpriteRender m_thirdSprite;
	SpriteRender m_fourthSprite;

    FontRender font;

    std::vector<std::string> m_imagePaths = {
        "Assets/Sprite/Select.DDS",
        "Assets/Sprite/SelectZ.DDS",
        "Assets/Sprite/Select_ANYS.DDS",
        "Assets/Sprite/5Games.DDS",
        "Assets/Sprite/10Games.DDS",
		"Assets/Sprite/Obstacle.DDS",
		"Assets/Sprite/Nothing.DDS"
    };

    // ボタンの基準位置（中央基準）
    Vector3 m_firstBasePos = Vector3::Zero;
    Vector3 m_secondBasePos = Vector3::Zero;
	Vector3 m_thirdBasePos = Vector3::Zero;
	Vector3 m_fourthBasePos = Vector3::Zero;
};
