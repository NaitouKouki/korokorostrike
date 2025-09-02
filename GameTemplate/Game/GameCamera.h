#pragma once

//ばねカメラを使用したい場合は、SpringCameraをインクルードする。
#include "camera/SpringCamera.h"

//クラス宣言
class Player;//こちらも同様に保留
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
	//カメライベント
	void CameraEvent();

private:
	Vector3			m_toCameraPos = Vector3::One;
	Vector3			m_toCameraTargetPos = Vector3::One;
	SpringCamera	m_springCamera;					//ばねカメラ

	Game* m_game = nullptr;
	Player* m_player = nullptr;//保留

	bool	m_isCameraEvent = false;
	bool	m_isInit = false;
	float	t = 0.0f;
};

