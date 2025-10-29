#include "stdafx.h"
#include "BackGround.h"
#include "Game.h"

BackGround::BackGround(){}
BackGround::~BackGround(){}

bool BackGround::Start()
{
	m_game = FindGO<Game>("game");
	m_spriteRender.Init("Assets/Sprite/BackGround.DDS", 720.0f, 580.0f);
	m_spriteRender.SetPosition({ 760.0f, 130.0f, 0.0f });

	if (m_game->m_maxGameCount == 5) {
		m_spriteRender.SetScale({ 0.6f,1.0f,1.0f });
	}
	else {	
		m_spriteRender.SetPosition({ 760.0f, 50.0f, 0.0f });
		m_spriteRender.SetScale({ 0.6f,1.5f,1.0f });	
	}
	return true;
}
void BackGround::Update()
{
	// --- 表示切り替え ---
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_isVisible = false;  //非表示
	}
	if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_isVisible = true;   //再表示
	}
	m_spriteRender.Update();
}

void BackGround::Render(nsK2EngineLow::RenderContext& rc)
{
	if (!m_isVisible) return;  // ← 非表示ならスキップ
	m_spriteRender.Draw(rc);
}