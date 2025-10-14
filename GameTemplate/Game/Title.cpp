#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	
}

Title::~Title()
{

}

bool Title::Start()
{
	//‰æ‘œ‚ğ“Ç‚İ‚ŞB
	m_spriteRender.Init("Assets/Sprite/Title.DDS", 1920.0f, 1080.0f);
	return true;
}

void Title::Update()
{

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	//‰æ‘œ‚ğ•`‰æ‚·‚éB
	m_spriteRender.Draw(rc);
}
