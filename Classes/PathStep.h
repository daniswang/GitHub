#ifndef _PATHSTEP_H_
#define _PATHSTEP_H_

#include "cocos2d.h"

USING_NS_CC;

class PathStep:public Object
{
public:
	PathStep();
	~PathStep();
public:
	static PathStep* CreatWithIndex(int row, int col);
	void InitWithIndex(int row, int col);
	int GetFValue();

private:
	CC_SYNTHESIZE(int, m_Row, Row);
	CC_SYNTHESIZE(int, m_Col, Col);
	CC_SYNTHESIZE(int, m_G, G);
	CC_SYNTHESIZE(int, m_H, H);

	CC_SYNTHESIZE(PathStep*, m_FatherStep, FatherStep);


};
#endif;