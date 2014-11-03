#include "KeyboardScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

Scene* KeyboardScene::createScene()
{
	auto scene = Scene::create();

	auto layer = KeyboardScene::create();
	scene->addChild(layer);
	return scene;
}

bool KeyboardScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 255, 255, 255)))
	{
		return false;
	}

	/**auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);

	this->addChild(sprite, 0);**/
	

	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/horse.ExportJson");

	Armature *armature = Armature::create("horse");
	//armature->getAnimation()->playWithIndex(1);
	armature->getAnimation()->play("run");
	armature->getAnimation()->setSpeedScale(1.0f);
	armature->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	armature->setScale(0.6f);
	this->addChild(armature);

	auto label = Label::createWithSystemFont("Action Perform: " + armature->getAnimation()->getCurrentMovementID(), "Arial", 25);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(this->getContentSize().width - label->getContentSize().width, 0);
	//getBoundingBox().size.width

	this->addChild(label);

	auto eventListener = EventListenerKeyboard::create();


	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){
		if (keys.find(keyCode) == keys.end()){
			keys[keyCode] = event->getCurrentTarget();
		}
		/*
		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			event->getCurrentTarget()->setPosition(--loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			event->getCurrentTarget()->setPosition(++loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			event->getCurrentTarget()->setPosition(loc.x, ++loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			event->getCurrentTarget()->setPosition(loc.x, --loc.y);
			break;
		}*/
		
	};

	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		keys.erase(keyCode);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, armature);
	this->scheduleUpdate();
	CCLOG("Decimals: %d",&armature);
	return true;
}

bool KeyboardScene::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

void KeyboardScene::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Node::update(delta);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
		auto obj = keys.at(EventKeyboard::KeyCode::KEY_LEFT_ARROW);

		Vec2 loc = obj->getPosition();
		obj->setPosition(--loc.x, loc.y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
		auto obj = keys.at(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);

		Vec2 loc = obj->getPosition();
		obj->setPosition(++loc.x, loc.y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_W)){
		auto obj = keys.at(EventKeyboard::KeyCode::KEY_UP_ARROW);

		Vec2 loc = obj->getPosition();
		obj->setPosition(loc.x, ++loc.y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || isKeyPressed(EventKeyboard::KeyCode::KEY_S)){
		auto obj = keys.at(EventKeyboard::KeyCode::KEY_DOWN_ARROW);

		Vec2 loc = obj->getPosition();
		obj->setPosition(loc.x, --loc.y);
	}
}
std::map<cocos2d::EventKeyboard::KeyCode,
	cocos2d::Node*> KeyboardScene::keys;