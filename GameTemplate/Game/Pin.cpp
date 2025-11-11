#include "stdafx.h"
#include "Pin.h"
#include "Game.h"
#include "Totalscore.h"
#include "collision/CollisionObject.h"

Pin::Pin(){}
Pin::~Pin(){}

bool Pin::Start()
{
	m_boxRender.Init("Assets/modelData/pin.tkm");
	m_boxRender.SetPosition(m_pinPosition);
	m_boxRender.SetScale(0.2f, 0.2f, 0.2f);

	m_boxcollider.Create(Vector3(17.0f, 60.0f, 17.0f));
	boInitData.collider = &m_boxcollider;
	boInitData.mass = 50.0f;
	boInitData.pos = m_pinPosition;
	boInitData.rot = Quaternion::Identity;
	boInitData.restitution = 1.2f;

	m_rigidBody.Init(boInitData);
	m_rigidBody.SetFriction(1);

	m_game = FindGO<Game>("game");
	return true;
}

void Pin::Update()
{
    m_rigidBody.GetPositionAndRotation(boPos, boRot);
    m_boxRender.SetPosition(boPos);
    m_boxRender.SetRotation(boRot);
    m_boxRender.Update();
    m_pinPosition = boPos;

    // âÒì]ÇéÊìæÇµÇƒè„ï˚å¸ÉxÉNÉgÉãÇãÅÇﬂÇÈ
    btTransform transform;
    m_rigidBody.GetBody()->getMotionState()->getWorldTransform(transform);
    btQuaternion rot = transform.getRotation();
    btVector3 upDir = quatRotate(rot, btVector3(0, 1, 0));
    upDir.normalize();

    // åXÇ´ìxÅAèÍäOÇîªíË
    float dot = upDir.dot(btVector3(0, 1, 0));  // 1 = ê^è„, 0 = â°ì|Çµ
    if (dot < 0.6f) {
        if (!m_isFall) {
            m_isFall = true;
        }

        // Ç‹ÇæÉXÉRÉAÇ…îΩâfÇµÇƒÇ¢Ç»Ç¢èÍçáÇÃÇ›â¡éZ
        if (m_isFall && !m_isCounted) {
            m_isCounted = true;
            Totalscore* totalScore = FindGO<Totalscore>("totalscore");
            if (totalScore) {
                totalScore->AddScore(1);
            }
        }
    }
}

// ï`âÊ
void Pin::Render(nsK2EngineLow::RenderContext& rc)
{
	m_boxRender.Draw(rc);
}