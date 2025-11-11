#pragma once

class Game;
class Totalscore;
class Title;
class FrameCount;
class BackGround;

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
	FrameCount*		m_frameCount = nullptr;
	BackGround*		m_background = nullptr;
};