#pragma once

//ばねカメラを使用したい場合は、SpringCameraをインクルードする。
#include "camera/SpringCamera.h"

//クラス宣言
class Player;
class Game;

class GameCamera :public IGameObject
{
public:

	GameCamera();
	~GameCamera();
	//スタート
	bool Start();
	//アップデート
	void Update();

private:
	Vector3			m_toCameraPos = Vector3::One;
	Vector3			m_toCameraTargetPos = Vector3::One;
	SpringCamera	m_springCamera;							//ばねカメラ
	Game*			m_game = nullptr;
	Player*			m_player = nullptr;
	bool			m_isInit = false;
	float			t = 0.0f;
};