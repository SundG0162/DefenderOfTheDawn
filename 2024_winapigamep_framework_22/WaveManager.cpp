#include "pch.h"
#include "WaveManager.h"
#include "SpawnManager.h"
#include "BasicEnemy.h"
#include "SpinEnemy.h"
#include "DashEnemy.h"
#include "InvincibleEnemy.h"
#include <iostream>
#include "EventManager.h"
#include "ResourceManager.h"

void WaveManager::init()
{
	setWave(0);

#pragma region spawnData

	//웨이브 0
	waves.push_back({ 3.f, SIvectorforEmpty, EvectorforEmpty });


	//웨이브 1
	waves.push_back({ 6.f, SIvectorforEmpty, getEnemies<BasicEnemy>(1) });

	//웨이브 2
	waves.push_back({ 8.f, SIvectorforEmpty, getEnemies<BasicEnemy>(2) });

	//웨이브 3
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<BasicEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(3, 0.5f)
		),
			EvectorforEmpty });
	//웨이브 4
	waves.push_back({ 10.f,
		SIvectorforEmpty,
		getEnemies<DashEnemy>(3) });
	//웨이브 5
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(2, 2.f)
		),
			EvectorforEmpty });
	//웨이브 6
	waves.push_back({ 10.f,
		SIvectorforEmpty,getEnemies<InvincibleEnemy>(1) });
	//웨이브 7
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<InvincibleEnemy>(2, 1.f)
		),
			EvectorforEmpty });
	//웨이브 8
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<InvincibleEnemy>(3, 0.8f)
		),
			EvectorforEmpty });
	//웨이브 9
	waves.push_back({ 10.f,
		mergeSIVectors(
			getEnemiesInTime<DashEnemy>(1, 1.0f),
			getEnemiesTimeInterval<SpinEnemy>(5, 0.5f)
		),
			EvectorforEmpty });

	//웨이브 10
	waves.push_back({ 10.f,
		SIvectorforEmpty,getEnemies<InvincibleEnemy>(5) });


#pragma endregion
}



void WaveManager::update()
{

	leftTime -= DELTATIME;
	if (leftTime <= 0)
	{
		//가능하면 시간이 지난다던지 종이 처서 소리가 난다던지 
		//윈도우를 띄어서 메시지를 보내던지 시간이 지났다는걸 표시하고 싶음
		if (wave >= 10)
			//무한 웨이브
		{
			waves.push_back({ 12.f,
				mergeSIVectors(
					getEnemiesInTime<BasicEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesInTime<SpinEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesInTime<DashEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesInTime<InvincibleEnemy>(randSpawnNum(), randSpawnTime()),
					
					getEnemiesTimeInterval<BasicEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesTimeInterval<SpinEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesTimeInterval<DashEnemy>(randSpawnNum(), randSpawnTime()),
					getEnemiesTimeInterval<InvincibleEnemy>(randSpawnNum(), randSpawnTime())
				),
				mergeEVectors(
					getEnemies<BasicEnemy>(randSpawnNum()),
					getEnemies<SpinEnemy>(randSpawnNum()),
					getEnemies<DashEnemy>(randSpawnNum()),
					getEnemies<DashEnemy>(randSpawnNum())
				)
				});
		}
		if (waves.size() > 0)
		{
			++wave;
			leftTime = waves[0].waveContinueTime;
			for (auto enemy : waves[0].spawnEnemyList)
			{
				GET_SINGLETON(SpawnManager)->addSpawnObject({ enemy, 0.f });
			}
			for (auto info : waves[0].spawnList)
			{
				GET_SINGLETON(SpawnManager)->addSpawnObject(info);
			}
			std::cout << "Before erase, waves size: " << waves.size() << std::endl;
			waves.erase(waves.begin());//소환 끝났으면 애들없에기
			std::cout << "After erase, waves size: " << waves.size() << std::endl;

		}
	}
}

void WaveManager::release()
{
	for (auto info : waves)
	{
		for (Enemy* enemy : info.spawnEnemyList)
		{
			GET_SINGLETON(EventManager)->deleteObject(enemy);
		}
	}
	waves.clear();
}
