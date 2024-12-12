#include "pch.h"
#include "UpgradeComponent.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "UpgradeUI.h"
#include "WindowUI.h"
#include "Window.h"
#include "DamageUpgrade.h"
#include "SizeUpgrade.h"
#include "CCTVStunUpgrade.h"
#include "AttackSpeedUpgrade.h"
#include "CameraStunUpgrade.h"
#include "CameraDamageUpgrade.h"
#include "CameraCountUpgrade.h"
#include "CameraSizeUpgrade.h"
#include "TorchAttackSpeedUpgrade.h"
#include "TorchDamageUpgrade.h"
#include "TorchSizeUpgrade.h"
#include "EventManager.h"
#include "ResourceManager.h"

UpgradeComponent::UpgradeComponent()
{
	_upgradeFlag = false;
}

UpgradeComponent::~UpgradeComponent()
{
	for (Upgrade* upgrade : _upgrades)
	{
		delete upgrade;
		upgrade = nullptr;
	}
	_upgrades.clear();
	for (Upgrade* upgrade : _finishedUpgrade)
	{
		delete upgrade;
		upgrade = nullptr;
	}
	_finishedUpgrade.clear();
}

void UpgradeComponent::initialize()
{
	{
		Upgrade* upgrade = new DamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe 데미지 증가", L"CCTV.exe가 더욱 강해집니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new SizeUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe 확장", L"CCTV.exe가 더욱 넓어집니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CCTVStunUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe 강화", L"CCTV.exe의 공격을 맞으면\n적이 잠시 멈춥니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new AttackSpeedUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CCTVIcon"), L"CCTV.exe 공격속도 증가", L"CCTV.exe의 공격 딜레이가\n감소합니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraStunUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe 강화", L"Camera.exe가 적을 멈추는 시간이\n길어집니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraDamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe 데미지 증가", L"Camera.exe가 더욱 강해집니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraCountUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe 강화", L"Camera.exe의 캡처 속도가\n증가합니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new CameraSizeUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"CameraIcon"), L"Camera.exe 확장", L"Camera.exe가 더욱 넓어집니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new TorchAttackSpeedUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"TorchIcon"), L"Torch.exe 공격속도 증가", L"Torch.exe의 공격 딜레이가\n감소합니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new TorchDamageUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"TorchIcon"), L"Torch.exe 데미지 증가", L"Torch.exe가 더욱 강해집니다.");
		_upgrades.push_back(upgrade);
	}
	{
		Upgrade* upgrade = new TorchSizeUpgrade(GET_SINGLETON(ResourceManager)->getSprite(L"TorchIcon"), L"Torch.exe 확장", L"Torch.exe가 더욱 넓어집니다.");
		_upgrades.push_back(upgrade);
	}
	Player* player = dynamic_cast<Player*>(getOwner());
	for (Upgrade* u : _upgrades)
	{
		u->initialize(player);
	}
}

void UpgradeComponent::lateUpdate()
{
}

void UpgradeComponent::render(HDC hDC)
{
}

void UpgradeComponent::setRandomUpgrade()
{
	if (_upgradeFlag || _upgrades.empty()) return;
	GET_SINGLETON(ResourceManager)->play(L"Card");
	int index = utils::ExMath::getRandomValue(0, _upgrades.size() - 1);
	Upgrade* upgrade = _upgrades[index];
	upgrade->applyUpgrade();
	GET_SINGLETON(Core)->OnMessageProcessEvent += [this, upgrade]()
		{
			if (_upgradeFlag)
			{
				GET_SINGLETON(Core)->OnMessageProcessEvent -= [this, upgrade]() {};
				return;
			}
			_upgradeFlag = true;
			UpgradeUI* upgradeUI = new UpgradeUI();
			upgradeUI->setUpgrade(upgrade);
			WindowUI* windowUI = new WindowUI({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { 240,360 }, WINDOW_TYPE::NEW, L"Upgrade.exe");
			windowUI->setUI(upgradeUI);
			windowUI->openTween(0.f);
			Window* window = windowUI->getWindow();
			window->setCloseable(true);
			window->setMoveable(true);
			window->OnTweenEndEvent += [this, window, windowUI]()
				{
					window->closeTween(2.f);
					window->OnTweenEndEvent -= [this]() {};
					window->OnTweenEndEvent += [this, windowUI]()
						{
							GET_SINGLETON(EventManager)->deleteObject(windowUI);
							_upgradeFlag = false;
						};
				};
			window->OnWindowCloseEvent += [this]()
				{
					_upgradeFlag = false;
				};
			GET_SINGLETON(EventManager)->createObject(windowUI, LAYER::UI);
		};
	if (!upgrade->isValid())
	{
		auto iter = std::find(_upgrades.begin(), _upgrades.end(), upgrade);
		_finishedUpgrade.push_back(*iter);
		_upgrades.erase(iter);
	}
}