#pragma once

#include "cocos2d.h"
#include <map>

class KeyboardScene : public cocos2d::LayerColor{
public:
	static cocos2d::Scene* createScene();

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode code);

	virtual bool init();
	virtual void update(float delta) override;

	CREATE_FUNC(KeyboardScene);

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		cocos2d::Node*> keys;
};