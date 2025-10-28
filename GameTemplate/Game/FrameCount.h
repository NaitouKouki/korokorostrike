#pragma once
#include "gameObject/IGameObject.h"

class Game;

class FrameCount : public IGameObject
{
public:
    FrameCount();
    ~FrameCount();

    bool Start() override;
    void Update() override;
    void Render(nsK2EngineLow::RenderContext& rc) override;

    void SetFrame(int current, int max);
    void AddFrame();
    void Reset();

    int GetCurrentFrame() const { return m_currentFrame; }
    int GetMaxFrame() const { return m_maxFrame; }

private:
    int m_currentFrame = 1;
    int m_maxFrame = 10;
    bool m_visible = true;

    FontRender m_fontRender;
    Game* m_game = nullptr;
};
