#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	
}

Title::~Title()
{
	DeleteGO(m_soundSource);
}

bool Title::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/ModelData/Title.DDS", 1920.0f, 1080.0f);
	//BGM。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");
	m_soundSource = NewGO<SoundSource>(0);
	//ResistWaveFileBankで指定した番号。
	m_soundSource->Init(0);
	//BGMは曲をループさせる。
	m_soundSource->Play(true);
	return true;
}

void Title::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//m_describe = NewGO<Describe>(0, "describe");
		DeleteGO(this);
		//GameをNewGOで生成する。
		NewGO<Game>(0, "game");
	}
}

void Title::Render(RenderContext& rc)
{
	//画像を描画する。
	m_spriteRender.Draw(rc);
}
