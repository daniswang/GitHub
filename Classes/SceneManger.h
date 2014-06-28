#ifndef _SCENEMANGER_H_
#define _SCENEMANGER_H_

#include "cocos2d.h"

USING_NS_CC;

class SceneManger:public Object
{
public:
	SceneManger();
	~SceneManger();
	static void GoMenu();
	static void GoCredit();
	static void GoPlayerLayer();
private:
	static void Go(Layer* layer);
	static Scene* Warp(Layer* layer);

	/*SpriteBatchNode *m_SpriteSheet;
	SpriteBatchNode* m_PlayerSheet;*/
};
#endif;