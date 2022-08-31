/********************************************************************************
* 决策点接口，由TESS NG实现，用户可以借此调用接口方法，获取决策点一些基本属性，进行一些操作
*********************************************************************************/

#ifndef __IDecisionPoint__
#define __IDecisionPoint__

#include "tessinterfaces_global.h"

class ILink;

class TESSINTERFACES_EXPORT IDecisionPoint
{
public:
	/*决策点ID	*/
	virtual long id();
	//决策点名称
	virtual QString name();
	//决策点所在路段
	virtual ILink *link();
	//设置是否被动态修改，默认情况下发车信息被动态修改后，整个文件不能保存，以免破坏原有发车设置
	virtual void setDynaModified(bool bModified);
};

#endif