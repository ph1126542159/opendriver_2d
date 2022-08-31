/********************************************************************************
* 面域接口，由TESS NG实现，用户可以借此调用接口方法，获取面域一些基本属性
*********************************************************************************/

#ifndef __IConnectorArea__
#define __IConnectorArea__

#include "tessinterfaces_global.h"

class IConnector;

class TESSINTERFACES_EXPORT IConnectorArea
{
public:
	virtual long id();

	virtual QList<IConnector*> allConnector();
};

#endif