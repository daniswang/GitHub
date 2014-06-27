#include "Player.h"

USING_NS_CC;

const float EPSINON = 0.000001;

Player::Player():m_FoundPath(false),_curAnimation(NULL),_curAnimate(NULL)
{
}

Player::~Player()
{}

Player* Player::Create(Point playerPos, TMXTiledMap* TileMap, TMXLayer* BlockAge)
{
	Player* pPlayer = new Player();
	if(!pPlayer)
		return NULL;

	//pPlayer->setScale(0.5);
	//pPlayer->initWithSpriteFrameName("029.png");
	pPlayer->setPosition(playerPos.x, playerPos.y);
	pPlayer->InitWithLayer(TileMap, BlockAge);
	return pPlayer;
}

bool Player::InitWithLayer(TMXTiledMap* TileMap, TMXLayer* BlockAge)
{
	 bool bRet = false;
    do{
        CC_BREAK_IF(!this->initWithSpriteFrameName("cat_forward_1.png"));
        
        
        _facingForwardAnimation = CreatePlayerAnimation("forward");
        _facingForwardAnimation->retain();
        _facingBackAnimation = CreatePlayerAnimation("back");
        _facingBackAnimation->retain();
        _facingLeftAnimation = CreatePlayerAnimation("left");
        _facingLeftAnimation->retain();
        _facingRightAnimation = CreatePlayerAnimation("right");
        _facingRightAnimation->retain();
		_TileMap = TileMap;
		_BlockAge = BlockAge;
        bRet = true;
    } while (0);

    return bRet;
}

//创建player移动动画
Animation* Player::CreatePlayerAnimation(const char *animType)
{
    Animation *animation = Animation::create();
    for (int i = 1; i <= 2; ++i){
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("cat_%s_%d.png", animType, i)));
    }
    animation->setDelayPerUnit(0.2f);
    return animation;
}

//播放player移动动画
void Player::RunAnimation(Animation *animation)
{
	if (_curAnimation == animation){
        return;
    } 
  
	 _curAnimation = animation;
    if (_curAnimate != nullptr)
	{
        stopAction(_curAnimate);
    }
	
    _curAnimate = RepeatForever::create(Animate::create(animation));
    runAction(_curAnimate);
}

//移动
bool Player::Move(int FromRow, int FromCol, int ToRow, int ToCol)
{
	PathStep* desStep = PathStep::CreatWithIndex(0, 0);
	desStep->InitWithIndex(ToRow, ToCol);

	if(AStarPathFind(FromRow, FromCol, desStep))
	{
		m_FoundPathList.clear();
		PathStep* step = desStep;
		CCLog("source %d, %d\n", FromRow, FromCol);
		do
		{
			if(step->getFatherStep())
			{
				m_FoundPathList.insert(0, step);
				CCLog("index %d, %d\n", step->getRow(), step->getCol());
			}
			step = step->getFatherStep();
		}while(step);

		CCLog("des %d,%d\n",desStep->getRow(), desStep->getCol());
	}

	return false;
}

//AStar
bool Player::AStarPathFind(int source_Row, int source_Col, PathStep* DesStep)
{

	PathStep* sourceStep = PathStep::CreatWithIndex(0, 0);
	sourceStep->InitWithIndex(source_Row, source_Col);

	CCLog("delte begintime %lld\n", GetCurrentTime());
	m_OpenList.clear();
	m_CloseList.clear();
	CCLog("delte endtime %lld\n", GetCurrentTime());
	m_OpenList.pushBack(sourceStep);

	CCLog("begin time %lld\n", GetCurrentTime());
	do
	{
		PathStep* minStep = FindMinF_OpenList();
		if(!minStep)
			break;

		if(Add2CloseList(minStep, DesStep))
			break;

		DeleteFromOpenList();

		if(AddNeighbour2OpenList(minStep, DesStep))
		{
			setFoundPath(true);
			break;
		}

	}while(m_OpenList.size() > 0);

	CCLog("end time %lld\n", GetCurrentTime());
	if(getFoundPath())
		return true;

	return false;
}

// true  目标点在openlist
//false 正常
bool Player::Add2OpenList(PathStep* addStep)
{
	int stepFScore = addStep->GetFValue();
	ssize_t count = m_OpenList.size();
    ssize_t i = 0;
    for (; i < count; ++i)
    {
		if (stepFScore <= m_OpenList.at(i)->GetFValue())
        {
            break;
        }
    }
    m_OpenList.insert(i, addStep);

	return true;
}

//true 目标在closelist 
bool Player::Add2CloseList(PathStep* addStep, PathStep* DesStep)
{
	m_CloseList.pushBack(addStep);
	if(addStep == DesStep)
	{
		setFoundPath(true);
		return true;
	}

	return false;
}

//find minest F
PathStep* Player::FindMinF_OpenList()
{
	if(m_OpenList.size() < 1)
		return NULL;
	m_OpenList.at(0);
}

// right   left   down   up
bool Player::AddNeighbour2OpenList(PathStep* sourceStep, PathStep* DesStep)
{
	//right
	if(CheckNeighborStep(sourceStep->getRow() + 1, sourceStep->getCol(), sourceStep))
	{
		if(DesStep->getRow() == sourceStep->getRow() + 1 && DesStep->getCol() == sourceStep->getCol())
		{
			DesStep->setFatherStep(sourceStep);
			Add2CloseList(DesStep, DesStep);
			return true;
		}
		PathStep* Step = PathStep::CreatWithIndex(sourceStep->getRow() + 1, sourceStep->getCol());
		SetStepGHAndFather(sourceStep, Step, DesStep);
		Add2OpenList(Step);
	}
	//left
	if(CheckNeighborStep(sourceStep->getRow() - 1, sourceStep->getCol(), sourceStep))
	{
		if(DesStep->getRow() == sourceStep->getRow() - 1 && DesStep->getCol() == sourceStep->getCol())
		{
			DesStep->setFatherStep(sourceStep);
			Add2CloseList(DesStep, DesStep);
			return true;
		}
		PathStep* Step = PathStep::CreatWithIndex(sourceStep->getRow() - 1, sourceStep->getCol());
		SetStepGHAndFather(sourceStep, Step, DesStep);
		Add2OpenList(Step);
	}

	//up
	if(CheckNeighborStep(sourceStep->getRow(), sourceStep->getCol() + 1, sourceStep))
	{
		if(DesStep->getRow() == sourceStep->getRow() && DesStep->getCol() == sourceStep->getCol() + 1)
		{
			DesStep->setFatherStep(sourceStep);
			Add2CloseList(DesStep, DesStep);
			return true;
		}
		PathStep* Step = PathStep::CreatWithIndex(sourceStep->getRow(), sourceStep->getCol() + 1);
		SetStepGHAndFather(sourceStep, Step, DesStep);
		Add2OpenList(Step);
	}

	//down
	if(CheckNeighborStep(sourceStep->getRow(), sourceStep->getCol() - 1, sourceStep))
	{
		if(DesStep->getRow() == sourceStep->getRow() && DesStep->getCol() == sourceStep->getCol() - 1)
		{
			DesStep->setFatherStep(sourceStep);
			Add2CloseList(DesStep, DesStep);
			return true;
		}
		PathStep* Step = PathStep::CreatWithIndex(sourceStep->getRow(), sourceStep->getCol() - 1);
		SetStepGHAndFather(sourceStep, Step, DesStep);
		Add2OpenList(Step);
	}

	return false;
}

void Player::DeleteFromOpenList()
{
	m_OpenList.erase(0);
}

void Player::SetStepGHAndFather(PathStep* father, PathStep* step, PathStep* desStep)
{
	step->setFatherStep(father);
	step->setG(father->getG() + 10);
	
	int row = abs(desStep->getRow() - step->getRow());
	int col = abs(desStep->getCol() - step->getCol());

	step->setH(row + col);
}

//check step
bool Player::CheckNeighborStep(int row, int col, PathStep* fatherStep)
{
	if(row < 0 || row >= _TileMap->getMapSize().width)
		return false;
	if(col < 0 || col >= _TileMap->getMapSize().height)
		return false;

	// wall
	int tileGid = _BlockAge->getTileGIDAt(Point(row, col));
	if(tileGid)
	{
		auto propertes = _TileMap->getPropertiesForGID(tileGid).asValueMap();
		if(!propertes.empty())
		{
			auto  wall = propertes["Blockage"].asString();
			if(wall == "true")
			{
				return false;
			}
		}
	}

	//close
	Vector<PathStep*>::iterator it = m_CloseList.begin();
	for(;it != m_CloseList.end();it ++)
	{
		if((*it)->getRow() == row && (*it)->getCol() == col)
			return false;
	}
	//open
	Vector<PathStep*>::iterator its = m_OpenList.begin();
	for(;its != m_OpenList.end();its ++)
	{
		if((*its)->getRow() == row && (*its)->getCol() == col)
		{
			if((*its)->getG() > fatherStep->getG() + 10)
			{
				(*its)->setG(fatherStep->getG() + 10);
				(*its)->setFatherStep(fatherStep);
			}
			return false;
		}
	}

	return true;
}