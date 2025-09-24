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

    Matrix GetWorldMatrix() const
    {
        // 独自の Transform からワールド行列を取得
        if (m_transform) {
            return m_modelRender.GetWorldMatrix(0);
        }
        return Matrix::Identity; // エラー時のデフォルト
    }

    Transform* m_transform = nullptr;
    //RigidBodyInitData	rbInitData;
    //RigidBody			m_rigidBody;	// 剛体

private: // 各ステージが独自の Transform を持つ

    PhysicsStaticObject m_phyStaticObject;		//静的物体用
	ModelRender m_modelRender;					//モデルレンダラー
    //SphereCollider		m_stageCollider;	// 床の当たり判定
};