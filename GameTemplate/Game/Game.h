#pragma once

#include "Level3DRender/LevelRender.h"
#include "Title.h"

class Player;
//class Score;
class HoldCamera;
class Stage;

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

	enum EnGameState {
		enTitle,
		enStageSelect,
		enInGame,
		enResult,
	};
	EnGameState m_gameState = enTitle;

	int	 m_state = 0;
	Vector3     m_flagPos = Vector3::Zero;

private:
	LevelRender		m_levelRender;

	// タイトル画面
	Title*			m_title = nullptr;

	Player* m_player = nullptr;
	HoldCamera* m_camera = nullptr;
	SoundSource* m_soundSource = nullptr;
	Stage* m_stage = nullptr;
	Title* m_titleScreen = nullptr;
};

