#include "PathStep.h"
#include "cocos2d.h"

USING_NS_CC;

PathStep::PathStep():m_Row(0),m_Col(0),m_G(0),m_H(0),m_FatherStep(NULL)
{
}

PathStep::~PathStep()
{
	CCLog("PathStep Destroy!!!");
}

PathStep* PathStep::CreatWithIndex(int row, int col)
{
	PathStep* pRet = new PathStep();
	if(pRet)
	{
		pRet->InitWithIndex(row, col);
		pRet->autorelease();
		return pRet;
	}

	return NULL;
}

void PathStep::InitWithIndex(int row, int col)
{
	setRow(row);
	setCol(col);
}

int PathStep::GetFValue()
{
	return getG() + getH();
}