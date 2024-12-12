#include "pch.h"
#include "ExplodeEffect.h"
#include "AnimationClip.h"
#include "ResourceManager.h"
#include "EventManager.h"

ExplodeEffect::ExplodeEffect() : Effect()
{
	AnimationClip* clip = new AnimationClip();
	Texture* tex = GET_SINGLETON(ResourceManager)->getTexture(L"ExplodeEffect");
	vector<Sprite*> sprites = utils::SpriteParser::textureToSprites(tex, { 32,0 }, { 32,32 }, 7);
	clip->create(sprites, 0.1f);
	setClip(clip);
	clip->flag = true;
	GET_SINGLETON(EventManager)->createObject(this, LAYER::EFFECT);
}

ExplodeEffect::~ExplodeEffect()
{
}
