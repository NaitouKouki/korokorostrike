#pragma once

class Stage : public IGameObject
{
public:
    Stage();
    ~Stage();
    bool Start();
    void Update();
    void Render(RenderContext& rc);
};