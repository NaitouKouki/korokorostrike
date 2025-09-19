#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	//�摜��ǂݍ��ށB
	m_spriteRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
}

Title::~Title()
{
	DeleteGO(m_soundSource);
}

bool Title::Start()
{
	//BGM�B
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");
	m_soundSource = NewGO<SoundSource>(0);
	//ResistWaveFileBank�Ŏw�肵���ԍ��B
	m_soundSource->Init(0);
	//BGM�͋Ȃ����[�v������B
	m_soundSource->Play(true);
	return true;
}

void Title::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//m_describe = NewGO<Describe>(0, "describe");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	//�摜��`�悷��B
	m_spriteRender.Draw(rc);
}
