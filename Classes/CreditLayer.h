#include "cocos2d.h"

USING_NS_CC;

class CreditLayer : public Layer
{
public:
	CreditLayer();
	~CreditLayer(); 

	bool init();
	void Back(Object* pSender);

	CREATE_FUNC(CreditLayer);

};