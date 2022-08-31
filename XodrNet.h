#ifndef XODRNET_H
#define XODRNET_H
#include "Plugin/customernet.h"
#include "xodr.h"
#include <QVector>
#include "CreateLink.h"


inline std::map<e_contactPoint,std::string> enum_map_con()
{
    return {{ e_contactPoint::START,"start" } ,{ e_contactPoint::END,"end" }};
}

class XodrNet : public CustomerNet
{
public:
    XodrNet();

    //==========以下是接口方法重新实现==========
    //加载路网前的准备
    void beforeLoadNet() override;
    //加载完路网后的行为
    void afterLoadNet() override;
    //
    bool isPermitForCustDraw() override { return true; }
    //写标签，按照给定的属性名和字体大小（米）
    void labelNameAndFont(int itemType, long itemId, int &outPropName, qreal &outFontSize) override;
    //------------------------------------------

    void loadXodrNet(const QString& path);

    void setShowAll(bool flag);
private:
    void transferLanesList(const std::vector<std::shared_ptr<t_road>> &vecAllRoad, RoadMapLane &roadMapLane);

    int getLaneIdFromSection(int sectionIndex,SectionLane& sectionLane);

    void setNetAttrs(t_header* header,const QString& sourcePath);

    bool m_showAll;
};

#endif // XODRNET_H
