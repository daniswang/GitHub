#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PathStep.h"
#include "Player.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void SetViewPointCenter(Vec2 Pos);
	void onTouchEnded(Touch* touch, Event* unused_event);
	void TouchPoint2MapPoint(Point* touchpoint);
	Point TileCoordForPostion(Point map_pos);
	Point PostionForTileCoord(Point mapCoord);
	void SetPlayerPostion(Point map_pos);
	bool IsMapPointPass(Point map_pos);
	//
	/*bool Move(int FromRow, int FromCol, int ToRow, int ToCol);
	bool AStarPathFind(int source_Row, int source_Col, PathStep* DesStep);
	bool Add2OpenList(PathStep* addStep);
	bool Add2CloseList(PathStep* addStep, PathStep* DesStep);
	PathStep* FindMinF_OpenList();
	bool AddNeighbour2OpenList(PathStep* sourceStep, PathStep* DesStep);
	void SetStepGHAndFather(PathStep* father, PathStep* step, PathStep* desStep);
	void DeleteFromOpenList();
	bool CheckNeighborStep(int row, int col, PathStep* fatherStep);*/
	void PopStepAndAnimate();
	private:
		TMXTiledMap* m_TileMap;
		TMXLayer* m_BackGround;
		Player* m_Player;
		TMXLayer* m_BlockAge;

		//
		SpriteBatchNode *m_SpriteSheet;
		SpriteBatchNode* m_PlayerSheet;
};

#endif // __HELLOWORLD_SCENE_H__
