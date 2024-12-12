#include "pch.h"
#include "SpawnManager.h"
#include "Scene.h"
#include "EventManager.h"
#include "TimeManager.h"
#include "PlayerManager.h"
#include "Enemy.h"

void SpawnManager::init()
{
	currentTime = 0;
}

void SpawnManager::update()
{
	if (_isStopped) return;
	if (_target == nullptr) return;
	if (spawnQueue.empty())return;
	SpawnInfo topInfo = spawnQueue.front();
	currentTime += DELTATIME;
	if (topInfo.spawnTime < currentTime)
	{
		GET_SINGLETON(EventManager)->createObject(topInfo.spawnTarget, LAYER::ENEMY);
		Enemy* spawningObject;
		if(spawningObject = dynamic_cast<Enemy*>(topInfo.spawnTarget))
			spawningObject->SetTarget(_target);
		spawnQueue.pop();
	}
}

void SpawnManager::setStop(bool isStopped)
{
	_isStopped = isStopped;
	_target = isStopped ? nullptr : (Object*)GET_SINGLETON(PlayerManager)->getPlayer();
}
