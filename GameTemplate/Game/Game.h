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
	void mainStage();
	void DeleteAll();
	void Render(RenderContext& rc);

	int				m_state = 0;
	int				m_currentGame = 0;   // 現在のゲーム数（1~5）
	int				m_throwCount = 0;    // 現在の投球回数（1 or 2）
	const int		MAX_GAMES = 5; // 全5ゲーム制

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