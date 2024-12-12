#pragma once
#include "Component.h"
class Texture;
class Sprite;
class AnimationClip;
class Animator : public Component
{
public:
	Animator();
	~Animator();
public:
	void lateUpdate() override;
	void render(HDC hdc) override;
public:
	void createAnimation(const wstring& name, vector<Sprite*>& sprites, float duration);
	AnimationClip* findAnimation(const wstring& name);
	void playAnimation(const wstring& name, bool isRepeat, int repeatCount = 0);
	void stopAnimation();
	void addAnimation(const wstring& name, AnimationClip* clip);
public:
	const bool& IsRepeat() { return _isRepeat; }
	const int& getRepeatCount() { return _repeatCount; }
private:
	map<wstring, AnimationClip*> _animationMap;
	AnimationClip* _currentClip;
	bool _isRepeat;
	int _repeatCount;
};