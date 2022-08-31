/********************************************************************************
* 发车点接口，由TESS NG实现，用户可以借此调用接口方法，获取发车点一些基本属性，增加发车间隔
*********************************************************************************/

#ifndef __IDispatchPoint__
#define __IDispatchPoint__

#include "tessinterfaces_global.h"

class ILink;

class TESSINTERFACES_EXPORT IDispatchPoint {
public:
	/*发车点ID	*/
	virtual long id();
	//发车点名称
	virtual QString name();
	//发车点所在路段
	virtual ILink *link();
	//设置是否被动态修改，默认情况下发车信息被动态修改后，整个文件不能保存，以免破坏原有发车设置
	virtual void setDynaModified(bool bModified);

	//增加发车间隔
	virtual long addDispatchInterval(long vehiCompId, int interval, int vehiCount);
};

#endif