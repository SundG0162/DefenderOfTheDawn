#pragma once
#include "Action.h"
class Texture;
class Sprite;
class Animator;
class SpriteRenderer;
class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();
public:
	void update();
	void render(HDC hdc);
	void release();
public:
	void init(Animator* animator);
	void create(vector<Sprite*>& sprites, float duration);
public:
	void setFrame(int frame) { _currentFrame = frame; _timer = 0.f; }
	void setRepeat(bool repeat) { _isRepeat = repeat; }
public:
	Action<> OnAnimationEndEvent;
public:
	bool flag = false;
private:
	Animator* _animator;
	SpriteRenderer* _spriteRenderer;
	bool _isRepeat;
	int _currentFrame;
	float _duration;
	float _timer;
	vector<Sprite*> _sprites;
};