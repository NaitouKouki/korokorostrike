#pragma once
#include "gameObject/IGameObject.h"

class Game;
class Player;
class Pause : public IGameObject
{
public:
    Pause();
    ~Pause();
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    int m_selectedIndex = 0;
    float m_animTime = 0.0f;
    void LoadRandomImage();
    SpriteRender        m_sprite;
    SpriteRender        m_firstSprite;
    SpriteRender        m_secondSprite;
    Game*               m_game = nullptr;
	Player*             m_player = nullptr;

    // ボタンの基準位置（中央基準）
    Vector3 m_firstBasePos = Vector3::Zero;
    Vector3 m_secondBasePos = Vector3::Zero;
};
