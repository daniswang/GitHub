#include "CreditLayer.h"
#include "SceneManger.h"

USING_NS_CC;

CreditLayer::CreditLayer()
{}

CreditLayer::~CreditLayer()
{
}

bool CreditLayer::init()
{
	if(!Layer::init())
		return false;

	Size visibelSize = Director::getInstance()->getVisibleSize();

	MenuItemFont* back = MenuItemFont::create("back", CC_CALLBACK_1(CreditLayer::Back, this));
	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Point((visibelSize.width - back->getContentSize().width + back->getContentSize().width / 2 - 10), 
		back->getContentSize().height / 2 + 10));
	addChild(menu);

	return true;

}

void CreditLayer::Back(Object* pSender)
{
	SceneManger::GoMenu();
}

