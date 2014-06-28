#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:
	MenuLayer();
	~MenuLayer();

	bool init();

	void OnNewGame(Object* pSender);
	void OnCredits(Object* pSender);

	CREATE_FUNC(MenuLayer);
};
#endif;