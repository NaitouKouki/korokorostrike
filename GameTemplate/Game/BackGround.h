#pragma once
#include "gameObject/IGameObject.h"

class Game;
class BackGround:public IGameObject
{
	public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Render(nsK2EngineLow::RenderContext& rc);
private:
	bool m_isVisible	= true;
	SpriteRender		m_spriteRender;
	Game*				m_game = nullptr;
};

