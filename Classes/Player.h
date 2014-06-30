#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "PathStep.h"

USING_NS_CC;

class Player:public Sprite
{
public:
	Player();
	~Player();
	static Player* Create(Point playerPos, TMXTiledMap* TileMap, TMXLayer* BlockAge);
	bool InitWithLayer(TMXTiledMap* TileMap, TMXLayer* BlockAge);
	Animation* CreatePlayerAnimation(const char *animType);
	void RunAnimation(Animation *animation);

public:
	Vector<PathStep*> m_OpenList;
	Vector<PathStep*> m_CloseList;
	Vector<PathStep*> m_FoundPathList;

	
	bool Move(int FromRow, int FromCol, int ToRow, int ToCol);
	void Stop();
	bool AStarPathFind(int source_Row, int source_Col, PathStep* DesStep);
	bool Add2OpenList(PathStep* addStep);
	bool Add2CloseList(PathStep* addStep, PathStep* DesStep);
	PathStep* FindMinF_OpenList();
	bool AddNeighbour2OpenList(PathStep* sourceStep, PathStep* DesStep);
	void SetStepGHAndFather(PathStep* father, PathStep* step, PathStep* desStep);
	void DeleteFromOpenList();
	bool CheckNeighborStep(int row, int col, PathStep* fatherStep);

private:
	CC_SYNTHESIZE(Point, m_Pos, Pos);
	CC_SYNTHESIZE(bool, m_FoundPath, FoundPath);

	CC_SYNTHESIZE(Animation*, _facingForwardAnimation, ForWard);
    CC_SYNTHESIZE(Animation*, _facingBackAnimation, Back);
    CC_SYNTHESIZE(Animation*, _facingLeftAnimation, Left);
    CC_SYNTHESIZE(Animation*, _facingRightAnimation, Right);
    CC_SYNTHESIZE(Animation*, _curAnimation, CurrentA);
   CC_SYNTHESIZE( Action*, _curAnimate, Animate);
   TMXTiledMap* _TileMap;
   TMXLayer* _BlockAge;


};
#endif;