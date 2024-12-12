#include "pch.h"
#include "Animator.h"
#include "AnimationClip.h"

Animator::Animator()
	: _currentClip(nullptr)
	, _isRepeat(false)
	, _repeatCount(0)
{
}

Animator::~Animator()
{
	map<wstring, AnimationClip*>::iterator iter;
	for (iter = _animationMap.begin(); iter != _animationMap.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			iter->second->release();
			delete iter->second;
		}
	}
	_animationMap.clear();
}

void Animator::lateUpdate()
{
	if (_currentClip != nullptr)
		_currentClip->update();
}

void Animator::render(HDC hdc)
{
	if (_currentClip != nullptr)
		_currentClip->render(hdc);
}

void Animator::createAnimation(const wstring& name, vector<Sprite*>& sprites, float duration)
{
	AnimationClip* clip = new AnimationClip;
	clip->create(sprites, duration);
	clip->init(this);
	_animationMap.insert({ name, clip });
}

AnimationClip* Animator::findAnimation(const wstring& name)
{
	AnimationClip* clip = _animationMap[name];
	return clip;
}

void Animator::playAnimation(const wstring& name, bool isRepeat, int repeatCount)
{
	AnimationClip* clip = findAnimation(name);
	clip->setFrame(0);
	clip->setRepeat(isRepeat);
	_currentClip = clip;
	_isRepeat = isRepeat;
	_repeatCount = repeatCount;
}

void Animator::stopAnimation()
{
	_currentClip = nullptr;
}

void Animator::addAnimation(const wstring& name, AnimationClip* clip)
{
	clip->init(this);
	_animationMap.insert({ name, clip });
}
