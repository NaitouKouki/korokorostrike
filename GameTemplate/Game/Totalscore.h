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
	int m_gamescore = 0;
	//合計スコア計算用
	int GameScore() 
	{
		m_totalscore += m_gamescore;
		return m_totalscore;
	}
	//合計スコア取得用
	int GetTotalScore()
	{
		m_gamescore = m_score;
		return m_gamescore;
	};

private:
	Title*			m_title = nullptr;
	Game*			m_game = nullptr;	
	Pin*			m_pin = nullptr;
	FontRender		m_fontRender;	
	RenderContext*	g_renderContext2D = nullptr;	
};

