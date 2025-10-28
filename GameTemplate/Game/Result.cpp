#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"
#include "TotalScore.h"
#include "FrameCount.h"

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{	
	m_totalscore = FindGO<Totalscore>("totalscore");
	m_game = FindGO<Game>("game");
	//画像を読み込む。
	m_spriteRender.Init("Assets/Sprite/Result.dds", 1920.0f, 1080.0f);
	TotalScore();
	return true;
}

//更新処理
void Result::Update()
{
	m_spriteRender.Update();

	//Aボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(m_totalscore);
		DeleteGO(FindGO<FrameCount>("framecount"));
		DeleteGO(m_game);	
		NewGO<Title>(0, "title");
		
		DeleteGO(this);	

	}
}

void Result::TotalScore()
{
	wchar_t scorew[256];
	swprintf_s(scorew, 256, L"%d点",m_totalscore->GameScore());
	m_fontRender.SetText(scorew);
	m_fontRender.SetPosition({ 200.0f, 100.0f, 0.0f });
	m_fontRender.SetScale(5.0);
	m_fontRender.SetColor(g_vec4Black);
}

//描画処理
void Result::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}
