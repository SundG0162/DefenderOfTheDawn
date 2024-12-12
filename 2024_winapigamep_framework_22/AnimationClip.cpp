#include "pch.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "Sprite.h"
#include "Object.h"
#include "TimeManager.h"
#include "SpriteRenderer.h"

AnimationClip::AnimationClip()
	: _animator(nullptr)
	, _spriteRenderer(nullptr)
	, _currentFrame(0)
	, _duration(0.f)
	, _timer(0.f)
{
}

AnimationClip::~AnimationClip()
{
}

void AnimationClip::update()
{
	if (_currentFrame == _sprites.size())
		return;
	_timer += DELTATIME;
	if (_timer >= _duration)
	{
		_timer = 0.f;
		_currentFrame++;
		if (_currentFrame == _sprites.size())
		{
			if (_isRepeat)
			{
				_currentFrame = 0;
			}
			else
			{
				OnAnimationEndEvent.invoke();
				return;
			}
		}

	}
	_spriteRenderer->setSprite(_sprites[_currentFrame]);
}

void AnimationClip::render(HDC hdc)
{
}

void AnimationClip::release()
{
	for (Sprite* sprite : _sprites)
	{
		delete sprite;
	}
	_sprites.clear();
}

void AnimationClip::init(Animator* animator)
{
	_animator = animator;
	_spriteRenderer = _animator->getOwner()->getComponent<SpriteRenderer>();
}

void AnimationClip::create(vector<Sprite*>& sprites, float duration)
{
	_sprites = sprites;
	_duration = duration;
}

