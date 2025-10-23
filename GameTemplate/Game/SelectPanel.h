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
};
