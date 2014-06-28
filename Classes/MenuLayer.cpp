#include "MenuLayer.h"
#include "SceneManger.h"

MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}

bool MenuLayer::init()
{
	if(!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
 
    TTFConfig config_font96("Marker Felt.ttf", 96);
    //TTFConfig config_font52("Marker Felt.ttf", 52);
 
    Label *titleLeft = Label::createWithTTF(config_font96, "Game ");
    Label *titleRight = Label::createWithTTF(config_font96, " Menu");
    //Label *titleQuotes = Label::createWithTTF(config_font96, "");
    //Label *titleCenterTop = Label::createWithTTF(config_font52, "How to build a...");
    //Label *titleCenterBottom = Label::createWithTTF(config_font96, "Part 1");
 
    MenuItemFont *startNew = MenuItemFont::create("New Game", CC_CALLBACK_1(MenuLayer::OnNewGame, this));
    MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MenuLayer::OnCredits, this));
 
    Menu *menu = Menu::create(startNew, credits, NULL);
 
    /*titleCenterTop->setPosition(
                   Point( (visibleSize.width - titleCenterTop->getContentSize().width)/2,
                           visibleSize.height - 100) );*/
	/*titleCenterTop->setPosition(
                   Point( visibleSize.width / 2,
                           visibleSize.height - 100) );
    addChild(titleCenterTop);*/
 
    /*titleQuotes->setPosition(
          Point(visibleSize.width / 2,
          40) );
    addChild(titleQuotes);*/
 
    //int tileWidth = titleLeft->getContentSize().width + titleRight->getContentSize().width + 50;
    titleLeft->setPosition(
		Point( (visibleSize.width - titleLeft->getContentSize().width) / 2, 
		visibleSize.height - 250) );
    addChild(titleLeft);
 
    titleRight->setPosition(
		Point( (visibleSize.width + titleRight->getContentSize().width) / 2 ,
           visibleSize.height - 250) );
    addChild(titleRight);
 
   /* titleCenterBottom->setPosition(
        Point( visibleSize.width / 2,
        titleRight->getPosition().y - titleCenterBottom->getContentSize().height - 40) );
    addChild(titleCenterBottom);*/
 
    menu->setPosition(
            Point( visibleSize.width / 2,
                 150 ) );
    menu->alignItemsVerticallyWithPadding(80.0f);
    addChild(menu, 2);
 
    return true;
}

void MenuLayer::OnNewGame(Object* pSender)
{
	SceneManger::GoPlayerLayer();
}

void MenuLayer::OnCredits(Object* pSender)
{
	SceneManger::GoCredit();
}