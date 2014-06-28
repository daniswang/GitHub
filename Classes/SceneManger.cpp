#include "SceneManger.h"
#include "MenuLayer.h"
#include "CreditLayer.h"
#include "HelloWorldScene.h"


SceneManger::SceneManger()
{
}

SceneManger::~SceneManger()
{
}

void SceneManger::GoMenu()
{
	Layer* layer = MenuLayer::create();
	SceneManger::Go(layer);
}

void SceneManger::Go(Layer* layer)
{
	Director* pDir = Director::getInstance();
	Scene* newScene = SceneManger::Warp(layer);

	if(pDir->getRunningScene())
	{
		pDir->replaceScene(newScene);
	}
	else
	{
		pDir->runWithScene(newScene);
	}
}

Scene* SceneManger::Warp(Layer* layer)
{
	Scene* newScene = Scene::create();
	newScene->addChild(layer);
	return newScene;
	return NULL;
}

void SceneManger::GoCredit()
{
	Layer* CreditLayer = CreditLayer::create();
	SceneManger::Go(CreditLayer);
}

void SceneManger::GoPlayerLayer()
{
	Layer* PlayerLayer = HelloWorld::create();
	SceneManger::Go(PlayerLayer);
}