#include "stdafx.h"
#include "Stage.h" 

Stage::Stage()
{
    // ここで Stage01 独自の m_transform を生成
    //モデルの読み込み
	m_modelRender.Init("Assets/modelData/stage-bowling.tkm");
    m_modelRender.SetScale(2.0f,2.0f,2.0f);
    m_transform = new Transform();    
    m_modelRender.Update();
    m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

Stage::~Stage()
{
    // ここで Stage01 独自の m_transform を削除
    delete m_transform;
	m_transform = nullptr;
}

bool Stage::Start()
{
	return true;
}

void Stage::Update()
{

}

void Stage::Rotation(Transform* transform) // ここに Transform* transform を追加
{
    // ここで transform を使って回転処理を行う
    if (transform && m_transform) {
        // 例えば、Y軸周りに回転させる場合
        m_transform->m_localRotation.SetRotationY(0.01f); // 少しずつ回転
        m_transform->UpdateTransform();
	}
}

void Stage::Render(RenderContext& rc)
{
    // ここで rc と m_transform を使って描画処理を行う
    if (m_transform) {
        m_modelRender.Draw(rc);
	}
}