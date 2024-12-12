#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
void CollisionManager::update()
{
	for (UINT Row = 0; Row < (UINT)LAYER::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)LAYER::END; ++Col)
		{
			if (_layers[Row] & (1 << Col))
			{
				//int a = 0;
				collisionLayerupdate((LAYER)Row, (LAYER)Col);
			}
		}
	}
}

void CollisionManager::checkLayer(LAYER _left, LAYER _right)
{
	// 작은쪽을 행으로 씁시다.
	// 작은 값을 LAYER의 행으로, 큰 값을 열
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);

	//// 비트 연산
	// 체크가 되어있다면
	if (_layers[Row] & (1 << Col))
	{
		// 체크 풀기
		_layers[Row] &= ~(1 << Col);
	}
	// 체크가 안되어있다면r
	else
	{
		_layers[Row] |= (1 << Col);
	}
}

void CollisionManager::checkReset()
{
	// 메모리 초기화
	memset(_layers, 0, sizeof(UINT) * (UINT)LAYER::END);
}

void CollisionManager::collisionLayerupdate(LAYER _left, LAYER _right)
{
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLETON(SceneManager)->getCurrentScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->getLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->getLayerObjects(_right);
	map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Collider* pLeftCollider = vecLeftLayer[i]->getComponent<Collider>();
		// 충돌체 없는 경우
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->getComponent<Collider>();
			// 충돌체가 없거나, 자기자신과의 충돌인 경우
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			COLLIDER_ID colliderID; // 두 충돌체로만 만들 수 있는 ID
			colliderID.left_ID = pLeftCollider->getID();
			colliderID.right_ID = pRightCollider->getID();

			iter = _coliisionInfoMap.find(colliderID.ID);
			// 이전 프레임 충돌한 적 없다.
			if (iter == _coliisionInfoMap.end())
			{
				// 충돌 정보가 미등록된 상태인 경우 등록(충돌하지 않았다로)
				_coliisionInfoMap.insert({ colliderID.ID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = _coliisionInfoMap.find(colliderID.ID);
			}
			if (isCollision(pLeftCollider, pRightCollider))
			{
				// 이전에도 충돌중
				if (iter->second)
				{
					if (vecLeftLayer[i]->isDead() || vecRightLayer[j]->isDead())
					{
						pLeftCollider->exitCollision(pRightCollider);
						pRightCollider->exitCollision(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->stayCollision(pRightCollider);
						pRightCollider->stayCollision(pLeftCollider);
					}
				}
				else // 이전에 충돌 x
				{
					if (!vecLeftLayer[i]->isDead() && !vecRightLayer[j]->isDead())
					{
						pLeftCollider->enterCollision(pRightCollider);
						pRightCollider->enterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // 충돌 안하네?
			{
				if (iter->second) // 근데 이전에 충돌중
				{
					pLeftCollider->exitCollision(pRightCollider);
					pRightCollider->exitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::isCollision(Collider* _left, Collider* _right)
{
	Vector2 vLeftPos = _left->getPosition();
	Vector2 vRightPos = _right->getPosition();
	Vector2 vLeftSize = _left->getSize();
	Vector2 vRightSize = _right->getSize();

	RECT leftRt = RECT_MAKE(vLeftPos.x, vLeftPos.y, vLeftSize.x, vLeftSize.y);
	RECT rightRt = RECT_MAKE(vRightPos.x, vRightPos.y, vRightSize.x, vRightSize.y);
	RECT rt;
	return ::IntersectRect(&rt, &leftRt, &rightRt);
	/*if (abs(vRightPos.x - vLeftPos.x) < (vLeftSize.x + vRightSize.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftSize.y + vRightSize.y) / 2.f)
	{
		return true;
	}

	return false;*/
}
