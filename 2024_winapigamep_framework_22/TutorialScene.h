#pragma once
#include "Scene.h"
class WindowUI;
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();
public:
	void init() override;
public:
	void nextTutorial();
private:
	int _currentIndex;
	Vector2 _panelPosition;
	Vector2 _panelSize;
	WindowUI* _panelUI;
	WindowUI* _textUI;
	vector<wstring> _tutorialTexts;
	vector<Sprite*> _panelSprites;
};

