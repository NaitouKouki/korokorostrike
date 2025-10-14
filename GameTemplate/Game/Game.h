#pragma once

#include "Level3DRender/LevelRender.h"
#include "Title.h"

class Title;
class Player;
class Pin;
class GameCamera;
class Stage;
class Totalscore;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Stage1();
	void GameStateUpdate();
	void Render(RenderContext& rc);
	
	int				m_state = 0;
private:
	LevelRender		m_levelRender;
	Title*			m_title = nullptr;
	Player*			m_player = nullptr;
	GameCamera*		m_camera = nullptr;
	Stage*			m_stage = nullptr;
	Title*			m_titleScreen = nullptr;
	Game*			m_game = nullptr;
	Totalscore*		m_totalscore = nullptr;
	Pin*			pins[10];

};

