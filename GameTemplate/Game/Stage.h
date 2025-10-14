#pragma once
#include "Transform.h" // Transform を独自に持つので、ここでインクルード
#include "gameObject/IGameObject.h"

class Game;

class Stage : public IGameObject
{
public:
    // コンストラクタで、基底クラスのコンストラクタにモデルパスを渡す
    Stage();
    // デストラクタ: 独自の m_transform を削除
    ~Stage();

    // 基底クラスのメソッドをオーバーライドし、独自の m_transform を渡す
    bool Start() override;
    void Update() override;
    void Rotation(Transform* transform);
    void Render(RenderContext& rc); // Render も Transform を渡す形にOverride

    Vector3         m_StagePosition = Vector3::Zero;

    // 独自の GetTransform() を実装
    const Transform* GetTransform()
    {
        return m_transform;
    }

    

private:
    Transform*          m_transform = nullptr;
    PhysicsStaticObject m_phyStaticObject;		//静的物体用
	ModelRender         m_modelRender;					//モデルレンダラー
};