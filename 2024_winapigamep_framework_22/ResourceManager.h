#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL //사운드마다 채널
{
	BGM, EFFECT, HIT, DEAD, END
};
struct SoundInfo
{
	FMOD::Sound* sound; // 실제 사운드 메모리
	bool isLoop;		// 사운드마다 루프할지말지
};
class Texture;
class Sprite;
class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager);
public:
	void init();
	const wchar_t* getResourcePath() const { return _resourcePath; }
public:
	Texture* loadTexture(const wstring& _key, const wstring& _path);
	Texture* getTexture(const wstring& _key);
	Sprite* loadSprite(const wstring& key, Sprite* sprite);
	Sprite* getSprite(const wstring& key);
	void release();
public:
	void loadSound(const wstring& _key, const wstring& _path, bool _isLoop);
	void play(const wstring& _key, SOUND_CHANNEL channel = SOUND_CHANNEL::EFFECT);
	void stop(SOUND_CHANNEL _channel);
	void volume(SOUND_CHANNEL _channel, float _vol);
	void pause(SOUND_CHANNEL _channel, bool _ispause);
private:
	SoundInfo* findSound(const wstring& _key);
private:
	wchar_t _resourcePath[255] = {};
	map<wstring, Texture*> _textureMap;
	map<wstring, Sprite*> _spriteMap;
	map<wstring, SoundInfo*> _soundMap;
	FMOD::System* _soundSystem; // 사운드 시스템
	FMOD::Channel* _channels[(UINT)SOUND_CHANNEL::END]; // 오디오 채널
};

