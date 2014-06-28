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
 
    Label *titleLeft = Label::createWithTTF(config_font96, "Game ");
    Label *titleRight = Label::createWithTTF(config_font96, " Menu");
 
    ///MenuItemFont *startNew = MenuItemFont::create("New Game", CC_CALLBACK_1(MenuLayer::OnNewGame, this));
	MenuItemImage* startNew = MenuItemImage::create("newGameBtn.png", "newGameBtn_over.png",  CC_CALLBACK_1(MenuLayer::OnNewGame, this));
    //MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(MenuLayer::OnCredits, this));
	MenuItemImage* credits = MenuItemImage::create("creditsBtn.png", "creditsBtn_over.png", CC_CALLBACK_1(MenuLayer::OnCredits, this));
 
    Menu *menu = Menu::create(startNew, credits, NULL);
 
    titleLeft->setPosition(
		Point( (visibleSize.width - titleLeft->getContentSize().width) / 2, 
		visibleSize.height - 250) );
    addChild(titleLeft);
 
    titleRight->setPosition(
		Point( (visibleSize.width + titleRight->getContentSize().width) / 2 ,
           visibleSize.height - 250) );
    addChild(titleRight);
 
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