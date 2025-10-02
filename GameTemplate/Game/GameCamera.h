//#pragma once
//
//#include "camera/SpringCamera.h"
//#include "Player.h" // m_playerを使う場合は前方宣言またはインクルード
//
//class Game;
//class Player;
//
//class GameCamera : public IGameObject
//{
//public:
//    GameCamera();
//    ~GameCamera();
//    // スタート
//    bool Start() override;
//    // アップデート
//    void Update() override;
//    // レンダー
//    void Render(RenderContext& rc) override;
//
//    Vector3 m_toCameraPos = Vector3(0.0f, 100.0f, 300.0f);
//    Vector3 m_toCameraTargetPos = Vector3::One;
//
//    Game* m_game = nullptr;
//    Player* m_player = nullptr; // プレイヤー参照
//    SpringCamera m_springCamera; // 三人称カメラ
//
//    bool m_isCameraEvent = false;
//    bool m_isInit = false;
//};
//

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
	SpringCamera	m_springCamera;					//ばねカメラ

	Game* m_game = nullptr;
	Player* m_player = nullptr;

	bool	m_isInit = false;
	float	t = 0.0f;
};