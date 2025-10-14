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

public:
	int m_score = 0;
	int m_totalscore = 0;
	int GetTotalScore()
	{
		m_totalscore = m_score;
		return m_totalscore;
	};

private:
	Title*			m_title = nullptr;
	Game*			m_game = nullptr;	
	Pin*			m_pin = nullptr;
	FontRender		m_fontRender;	
	RenderContext*	g_renderContext2D = nullptr;	
};

