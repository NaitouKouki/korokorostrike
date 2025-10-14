#pragma once

class Game;
class Totalscore;
class Timer;
class Flag;

class Result : public IGameObject
{
public:
	Result();
	~Result();
	bool Start()override;
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render(RenderContext& rc);
	void TotalScore();

private:
	SpriteRender	m_spriteRender;
	FontRender		m_fontRender;
	Game*			m_game = nullptr;
	Totalscore*		m_totalscore = nullptr;
	int				m_score = 100;
};