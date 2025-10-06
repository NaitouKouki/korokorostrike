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

// Start メソッドをオーバーライド: BaseStage の Start に自身の m_transform を渡す
bool Stage::Start()
{
    //m_modelRender.SetPosition(m_StagePosition);
    //m_stageCollider.Create(17.0f);
    //rbInitData.collider = &m_stageCollider;
    //rbInitData.mass = 10.0f;
    //rbInitData.pos = m_StagePosition;
    //rbInitData.rot = Quaternion::Identity;
    //rbInitData.restitution = 0.8f;  // 反発係数を正常な範囲に修正

    //m_rigidBody.Init(rbInitData);
    //m_rigidBody.SetFriction(1);
	return true;
}

// Update メソッドをオーバーライド: BaseStage の Update に自身の m_transform を渡す
void Stage::Update()
{

}

// Rotation メソッドをオーバーライド: BaseStage の Rotation に自身の m_transform を渡す
void Stage::Rotation(Transform* transform) // ここに Transform* transform を追加
{
    // ここで transform を使って回転処理を行う
    if (transform && m_transform) {
        // 例えば、Y軸周りに回転させる場合
        m_transform->m_localRotation.SetRotationY(0.01f); // 少しずつ回転
        m_transform->UpdateTransform();
	}
}

// Render メソッドをオーバーライド: BaseStage の Render に自身の m_transform を渡す
void Stage::Render(RenderContext& rc)
{
    // ここで rc と m_transform を使って描画処理を行う
    if (m_transform) {
        m_modelRender.Draw(rc);
	}
}