#include "HelloWorldScene.h"
#include "PathStep.h"

USING_NS_CC;

static const std::string file_bg = "01.tmx";
const float EPSINON = 0.000001;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("playermove.plist");
    m_SpriteSheet = SpriteBatchNode::create("playermove.pvr.ccz");
    addChild(m_SpriteSheet);

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("CatMaze.plist");
	m_PlayerSheet = SpriteBatchNode::create("CatMaze.png");
	addChild(m_PlayerSheet);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	//auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            //origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

	// load map
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file_bg.c_str()).c_str());
	m_TileMap = TMXTiledMap::createWithXML(str->getCString(), "");
	m_BackGround = m_TileMap->layerNamed("background");
	m_BlockAge = m_TileMap->layerNamed("blockage01");
	m_BlockAge->setVisible(false);
	addChild(m_TileMap, -1);
	scheduleUpdate();
	//init player
	TMXObjectGroup* object = m_TileMap->getObjectGroup("Object-Player");
	auto PlayerShowUpPoint = object->getObject("PlayerShowUpPoint");

	int x = PlayerShowUpPoint["x"].asInt();
	int y = PlayerShowUpPoint["y"].asInt();

	float px = x + m_TileMap->getTileSize().width / 2;
	float py = y + m_TileMap->getTileSize().height / 2;
	m_Player = Player::Create(Point(px, py), m_TileMap, m_BlockAge);
	m_TileMap->addChild(m_Player);
	InitMapPosByPlayerPos(m_Player->getPosition());

	//add listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool {return true;};
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::update(float dt)
{
		//m_TileMap->setPositionX(m_TileMap->getPositionX() - 1);
}
//设置player在地图中间
//不能超过地图边界
void HelloWorld::SetViewPointCenter(Vec2 Pos)
{
	auto winSize = Director::getInstance()->getWinSize();
	float posY = winSize.height / 2 - Pos.y;
	float posX = winSize.width / 2 - Pos.x;
	
	if(posY >= EPSINON)//下边界
		posY = 0;
	if(posX > EPSINON)//左边界
		posX = 0;

	//上边界
	if(m_TileMap->getContentSize().height - Pos.y < winSize.height / 2)
		posY = -(m_TileMap->getContentSize().height - winSize.height);
	//右边界
	if(m_TileMap->getContentSize().width - Pos.x < winSize.width / 2)
		posX = -(m_TileMap->getContentSize().width - winSize.width);

	MoveTo *moveAction = MoveTo::create(1, Vec2(posX, posY));
	m_TileMap->runAction(moveAction);
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event)
{
	/*auto action1 = RotateTo::create(0, 0, 180);
	auto action2 = RotateTo::create(0, 0, 0);*/

	auto touchLocation = touch->getLocation();
	touchLocation = convertToNodeSpace(touchLocation);
	TouchPoint2MapPoint(&touchLocation);

	Point TargettileCoord = TileCoordForPostion(touchLocation);

	Point PlayerCoord = TileCoordForPostion(Point(m_Player->getPosition().x, m_Player->getPosition().y));
	m_Player->Move(PlayerCoord.x, PlayerCoord.y, TargettileCoord.x, TargettileCoord.y);
	PopStepAndAnimate();
}

//屏幕触点转换为地图坐标点map_point
void HelloWorld::TouchPoint2MapPoint(Point* touchpoint)
{
	touchpoint->x += abs(m_TileMap->getPosition().x);
	touchpoint->y += abs(m_TileMap->getPosition().y);
}

//计算tile坐标
//map_pos 为地图坐标，非屏幕坐标
Point HelloWorld::TileCoordForPostion(Point map_pos)
{
	int x = map_pos.x / m_TileMap->getTileSize().width;
	int y = (m_TileMap->getMapSize().height * m_TileMap->getTileSize().height - map_pos.y) / m_TileMap->getTileSize().height;
	return Point(x, y);
}

//根据tile
Point HelloWorld::PostionForTileCoord(Point mapCoord)
{
	float x = mapCoord.x * m_TileMap->getTileSize().width + m_TileMap->getTileSize().width / 2;
	float y = (m_TileMap->getMapSize().height - mapCoord.y) * m_TileMap->getTileSize().height - m_TileMap->getTileSize().height / 2;

	return Point(x, y);
}
//设置player map_pos
void HelloWorld::SetPlayerPostion(Point map_pos)
{
	if(!IsMapPointPass(map_pos))
		return;
	
	m_Player->setPosition(map_pos);
}

bool HelloWorld::IsMapPointPass(Point map_pos)
{
	Point tileCoord = TileCoordForPostion(map_pos);
	int tileGid = m_BlockAge->getTileGIDAt(tileCoord);
	if(tileGid)
	{
		auto propertes = m_TileMap->getPropertiesForGID(tileGid).asValueMap();
		if(!propertes.empty())
		{
			auto  wall = propertes["Blockage"].asString();
			if(wall == "true")
			{
				return false;
			}
			return true;
		}
		return false;
	}

	return true;
}

void HelloWorld::PopStepAndAnimate()
{
	 // 检查是否仍有路径步骤需要前进
	if (m_Player->m_FoundPathList.size() == 0)
    {
		m_Player->Stop();
		CCLOG("foundlist is NULL!!!\n");
        return;
    }
    // 得到下一步移动的步骤
    PathStep *s = m_Player->m_FoundPathList.at(0);

	auto playerPos = m_Player->getPosition();
	Point touchLocation =PostionForTileCoord(Point(s->getRow(), s->getCol()));
	auto diff = touchLocation - playerPos;

	if(abs(diff.x) > abs(diff.y))
	{
		if(diff.x >= EPSINON)
		{
			playerPos.x += m_TileMap->getTileSize().width / 2;
			//m_Player->runAction(action2);
			m_Player->RunAnimation(m_Player->getRight());
		}
		else
		{
			playerPos.x -= m_TileMap->getTileSize().width / 2;
			m_Player->RunAnimation(m_Player->getLeft());
			//m_Player->runAction(action1);
		}
	}
	else
	{
		if(diff.y >= EPSINON)
		{
			playerPos.y += m_TileMap->getTileSize().height / 2;
			m_Player->RunAnimation(m_Player->getBack());
		}
		else
		{
			playerPos.y -= m_TileMap->getTileSize().height / 2;
			m_Player->RunAnimation(m_Player->getForWard());
		}
	}

	CCLog("player now pos row %f, col %f\n", m_Player->getPositionX(), m_Player->getPositionY());
	SetViewPointCenter(m_Player->getPosition());
    // 移除步骤
    m_Player->m_FoundPathList.erase(0);

	   // 准备动作和回调
	MoveTo *moveAction = MoveTo::create(1, PostionForTileCoord(Point(s->getRow(), s->getCol())));
	m_Player->setMoveTo(moveAction);
    CallFunc *moveCallback = CallFunc::create(CC_CALLBACK_0(HelloWorld::PopStepAndAnimate, this));
    // 运行动作
    m_Player->runAction(Sequence::create(moveAction, moveCallback, nullptr));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::InitMapPosByPlayerPos(Vec2 Pos)
{
	auto winSize = Director::getInstance()->getWinSize();
	float posY = winSize.height / 2 - Pos.y;
	float posX = winSize.width / 2 - Pos.x;
	
	if(posY >= EPSINON)//下边界
		posY = 0;
	if(posX > EPSINON)//左边界
		posX = 0;

	//上边界
	if(m_TileMap->getContentSize().height - Pos.y < winSize.height / 2)
		posY = -(m_TileMap->getContentSize().height - winSize.height);
	//右边界
	if(m_TileMap->getContentSize().width - Pos.x < winSize.width / 2)
		posX = -(m_TileMap->getContentSize().width - winSize.width);

	m_TileMap->setPosition(Point(posX, posY));
}
