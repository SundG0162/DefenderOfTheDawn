#pragma once
#include "Object.h"
class Animator;
class AnimationClip;
class Effect : public Object
{
public:
	Effect();
	virtual ~Effect();
public:
	void update() override;
	void render(HDC hdc) override;
public:
	void setClip(AnimationClip* clip);
	void play(bool isRepeat = false);
	void stop();
private:
	Animator* _animator;
};