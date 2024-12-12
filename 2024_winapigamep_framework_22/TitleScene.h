#pragma once
#include "Scene.h"
class WindowUI;
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();
public:
	void init() override;
};

