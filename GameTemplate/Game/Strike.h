#pragma once

class Strike : public IGameObject
{
public:
    Strike();
    ~Strike();

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    SpriteRender m_sprite;
    float m_timer = 0.0f;
    const float slideSpeed = 3.0f;
    Vector3 m_position = { 1000.0f,0.0f,0.0f };
};