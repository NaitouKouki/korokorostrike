#pragma once

class Game;

class Title :public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	bool Start();
	void Render(RenderContext& rc);

private:
	SpriteRender	m_spriteRender;
	Game* m_game = nullptr;
	SoundSource* m_soundSource = nullptr;
};

