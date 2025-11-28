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
    int m_decisionIndex = 0;
	int m_nextIndex = 0;
    float m_animTime = 0.0f;
    void LoadRandomImage();
    void ApplySelection();   // ← 選択を確定してGameへ渡す
	SpriteRender m_fiveCountSprite;
	SpriteRender m_tenCountSprite;
	SpriteRender m_obstacleSprite;
	SpriteRender m_nothingSprite;
	SpriteRender m_backTitleButtonSprite;
	SpriteRender m_customStartButtonSprite;
	SpriteRender m_frameBaseSprite;
	SpriteRender m_obstacleBaseSprite;

    FontRender font;

    std::vector<std::string> m_imagePaths = {
        "Assets/Sprite/SelectBackGround.DDS",
        "Assets/Sprite/SelectZ.DDS",
        "Assets/Sprite/Select_ANYS.DDS",
        "Assets/Sprite/5Games.DDS",
        "Assets/Sprite/10Games.DDS",
		"Assets/Sprite/Obstacle.DDS",
		"Assets/Sprite/Nothing.DDS",
        "Assets/Sprite/customStartButton.DDS",
		"Assets/Sprite/BackToTheTitle.DDS",
        "Assets/Sprite/frameBase.DDS",
        "Assets/Sprite/obstacleBase.DDS"
    };

    // ボタンの基準位置（中央基準）
    Vector3 m_fiveCountBasePos =            Vector3::Zero;
    Vector3 m_tenCountBasePos =             Vector3::Zero;
	Vector3 m_obstacleBasePos =             Vector3::Zero;
	Vector3 m_nothingBasePos =              Vector3::Zero;
	Vector3 m_backTitleButtonBasePos =      Vector3::Zero;
	Vector3 m_customStartButtonBasePos =    Vector3::Zero;
    Vector3 m_obstacleBaseBasePos =         Vector3::Zero;
    Vector3 m_frameBasePos =                Vector3::Zero;
};
