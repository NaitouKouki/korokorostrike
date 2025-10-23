#include "stdafx.h"
#include "SelectPanel.h"
#include "Title.h"
#include "Game.h"

SelectPanel::SelectPanel() {}
SelectPanel::~SelectPanel() {}

bool SelectPanel::Start()
{
    m_sprite.Init("Assets/Sprite/Select.DDS", 1920.0f, 1080.0f);
    return true;
}

void SelectPanel::Update()
{
    if (g_pad[0]->IsTrigger(enButtonB)) {
        // ƒ^ƒCƒgƒ‹‚É–ß‚é
        NewGO<Title>(0, "title");
        DeleteGO(this);
    }
}

void SelectPanel::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);
}
