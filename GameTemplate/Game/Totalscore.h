#pragma once

#include "gameObject/IGameObject.h"

class Title;
class Game;
class Pin;

class Totalscore :public IGameObject
{
public:
	Totalscore();
	~Totalscore();
	bool Start() override;
	void Update() override;
	void AddScore(int p);
	void Render(nsK2EngineLow::RenderContext& rc) override;


	int m_score = 0;
private:
	int fallenPins = 0;
	Title* m_title = nullptr;
	Game* m_game = nullptr;	
	Pin* m_pin = nullptr;
	FontRender m_fontRender;	
	RenderContext* g_renderContext2D = nullptr;	
};

