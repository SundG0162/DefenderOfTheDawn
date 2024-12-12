#include "pch.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Texture.h"
#include "Sprite.h"
void ResourceManager::init()
{
	::GetCurrentDirectory(255, _resourcePath);
	wcscat_s(_resourcePath, 255, L"\\Resource\\");
	//::SetWindowText(GET_SINGLE(Core)->GetHwnd(), m_resourcePath);

	FMOD::System_Create(&_soundSystem); // �ý��� ���� �Լ�
	if (_soundSystem != nullptr)
		_soundSystem->init(512, FMOD_INIT_NORMAL, nullptr);

	loadTexture(L"Computer", L"Texture\\Computer.bmp");
	loadTexture(L"Camera", L"Texture\\CameraScreen.bmp");
	loadTexture(L"BarUI", L"Texture\\BarUI.bmp");
	loadTexture(L"Torch", L"Texture\\Torch.bmp");
	loadTexture(L"UpgradeCard", L"Texture\\UpgradeCard.bmp");
	loadTexture(L"PowerIcon", L"Texture\\PowerIcon.bmp");
	loadTexture(L"CameraIcon", L"Texture\\CameraIcon.bmp");
	loadTexture(L"CCTVIcon", L"Texture\\CCTVIcon.bmp");
	loadTexture(L"ExplodeEffect", L"Texture\\ExplodeEffect.bmp");
	loadTexture(L"Heart", L"Texture\\Heart.bmp");
	loadTexture(L"TutorialPanel1", L"Texture\\TutorialPanel1.bmp");
	loadTexture(L"TutorialPanel2", L"Texture\\TutorialPanel2.bmp");
	loadTexture(L"TutorialPanel3", L"Texture\\TutorialPanel3.bmp");
	loadTexture(L"TutorialPanel4", L"Texture\\TutorialPanel4.bmp");
	loadTexture(L"TutorialPanel5", L"Texture\\TutorialPanel5.bmp");
	loadTexture(L"TutorialPanel6", L"Texture\\TutorialPanel6.bmp");
	loadTexture(L"EnemySheet", L"Texture\\EnemySheet.bmp");
	loadTexture(L"Selected", L"Texture\\Selected.bmp");
	loadTexture(L"TorchIcon", L"Texture\\TorchIcon.bmp");
	loadTexture(L"Upgrade", L"Texture\\Upgrade.bmp");
	loadTexture(L"W", L"Texture\\W.bmp");
	loadTexture(L"A", L"Texture\\A.bmp");
	loadTexture(L"S", L"Texture\\S.bmp");
	loadTexture(L"D", L"Texture\\D.bmp");
	loadTexture(L"rW", L"Texture\\rW.bmp");
	loadTexture(L"rA", L"Texture\\rA.bmp");
	loadTexture(L"rS", L"Texture\\rS.bmp");
	loadTexture(L"rD", L"Texture\\rD.bmp");
	loadTexture(L"Rotate", L"Texture\\Rotate.bmp");
	loadTexture(L"GameLogo", L"Texture\\GameLogo.bmp");

	loadSound(L"CameraCapture", L"Sound\\CameraCapture.mp3", false);
	loadSound(L"Dash", L"Sound\\Dash.mp3", false);
	loadSound(L"EnemyHit", L"Sound\\Hit.mp3", false);
	loadSound(L"PlayerHit", L"Sound\\PlayerHit.mp3", false);
	loadSound(L"Card", L"Sound\\Card.mp3", false);
	loadSound(L"Error", L"Sound\\Error.mp3", false);
	loadSound(L"Snap", L"Sound\\Snap.mp3", false);
	loadSound(L"Beep", L"Sound\\Beep.mp3", false);
	loadSound(L"Spin", L"Sound\\Spin.mp3", false);
	loadSound(L"BGM", L"Sound\\november.mp3", true);
	loadSound(L"Die", L"Sound\\EnemyDie.mp3", false);
	loadSound(L"RoundOver", L"Sound\\RoundOver.mp3", false);
	loadSound(L"TorchStart", L"Sound\\TorchStart.mp3", false);

	for (auto pair : _textureMap)
	{
		Texture* texture = pair.second;
		loadSprite(pair.first, utils::SpriteParser::textureToSprite(texture));
	}
}

Texture* ResourceManager::loadTexture(const wstring& _key, const wstring& _path)
{
	Texture* texture = getTexture(_key);
	if (nullptr != texture)
		return texture;

	// ����� �����Դϴ�. ������ּ���.
	// 1. ��� ����
	wstring texpath = _resourcePath;
	texpath += _path;

	// 2. Texture ��������?
	texture = new Texture;
	texture->loadBmp(texpath);
	_textureMap.insert({ _key,texture });
	return texture;
}

Texture* ResourceManager::getTexture(const wstring& _key)
{
	auto iter = _textureMap.find(_key);
	if (iter != _textureMap.end())
		return iter->second;
	return nullptr;
}

Sprite* ResourceManager::loadSprite(const wstring& key, Sprite* sprite)
{
	Sprite* spr = getSprite(key);
	if (spr)
		return spr;
	_spriteMap.insert({ key,sprite });
	return sprite;
}

Sprite* ResourceManager::getSprite(const wstring& key)
{
	auto iter = _spriteMap.find(key);
	if (iter != _spriteMap.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::release()
{
	{
		map<wstring, Texture*>::iterator iter;
		for (iter = _textureMap.begin(); iter != _textureMap.end(); ++iter)
			delete iter->second;
		_textureMap.clear();
	}
	{
		map<wstring, Sprite*>::iterator iter;
		for (iter = _spriteMap.begin(); iter != _spriteMap.end(); ++iter)
			delete iter->second;
		_spriteMap.clear();
	}
	{
		map<wstring, SoundInfo*>::iterator iter;
		for (iter = _soundMap.begin(); iter != _soundMap.end(); ++iter)
		{
			if (nullptr != iter->second)
				delete iter->second;
		}
		_soundMap.clear();
	}
	_soundSystem->close();
	_soundSystem->release();
}

void ResourceManager::loadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (findSound(_key))
		return;
	wstring strFilePath = _resourcePath;
	strFilePath += _path;
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());
	FMOD_MODE eMode = FMOD_LOOP_NORMAL;
	if (!_isLoop)
		eMode = FMOD_DEFAULT;

	SoundInfo* ptSound = new SoundInfo;
	ptSound->isLoop = _isLoop;
	_soundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->sound);
	_soundMap.insert({ _key, ptSound });
}

void ResourceManager::play(const wstring& _key, SOUND_CHANNEL channel)
{
	SoundInfo* ptSound = findSound(_key);
	if (!ptSound)
		return;
	_soundSystem->update();
	SOUND_CHANNEL eChannel = channel;
	if (ptSound->isLoop)
		eChannel = SOUND_CHANNEL::BGM;
	if (eChannel == SOUND_CHANNEL::BGM)
	{
		bool isPlaying = false;
		_channels[(UINT)eChannel]->isPlaying(&isPlaying);
		if (isPlaying)
			return;
	}
	if (eChannel == SOUND_CHANNEL::EFFECT)
		_soundSystem->playSound(ptSound->sound, nullptr, false, nullptr);
	else
	{
		_soundSystem->playSound(ptSound->sound, nullptr, false, &_channels[(UINT)eChannel]);
	}
}

void ResourceManager::stop(SOUND_CHANNEL _channel)
{
	_channels[(UINT)_channel]->stop();
}

void ResourceManager::volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 ���� ����
	_channels[(UINT)_channel]->setVolume(_vol);
}

void ResourceManager::pause(SOUND_CHANNEL _channel, bool _ispause)
{
	// bool���� true�� �Ͻ�����. ��, �� �Լ��� ������ Createsound�Ҷ� 
// FMOD_MODE�� FMOD_LOOP_NORMAL �̾�� ��.
	_channels[(UINT)_channel]->setPaused(_ispause);
}

SoundInfo* ResourceManager::findSound(const wstring& _key)
{
	map<wstring, SoundInfo*>::iterator iter = _soundMap.find(_key);

	if (iter == _soundMap.end())
		return nullptr;
	return iter->second;
}
