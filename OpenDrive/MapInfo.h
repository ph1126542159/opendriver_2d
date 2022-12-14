#ifndef MAPINFO_H
#define MAPINFO_H
#include "xodr.h"
#include <QVector>
#include <QPointF>
#include <vector>
#include <map>
#include "eulerspiral.h"

typedef QVector<std::pair<QPointF, int> > LanePoint; // int对应roadMark索引
typedef std::vector<LanePoint> GeometryPoint;
typedef std::vector<std::pair<GeometryPoint, int> > LaneSectionPoint;
typedef std::vector<LaneSectionPoint> RoadPoint;
typedef std::vector<RoadPoint> RoadMapPoint;

class MapInfo
{
public:
    static MapInfo* getInstance(){
        static MapInfo mapInfo;
        return &mapInfo;
    }
    void transferRoadMapInfo(std::vector< std::shared_ptr<t_road> > &vecAllRoad,RoadMapPoint& roadMapPoint);

    void getRoadGeometryPoint(const RoadMapPoint &roadMapAllPoint,
                              QVector<QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > > &qvecQvecQvecQvecQvecQpointf) const;

    void getRoadLaneSectionPoint(const RoadMapPoint &roadMapAllPoint, QVector<QVector<QVector<QVector<QPointF> > > > &qvecQvecMapPoint) const;

    QPointF getCenterPoint()const;
	
	QSizeF getGraphicsSize()const;
private:
    void setLaneOffsetOpposite(std::vector<std::shared_ptr<t_road>> &vecRoad);
    void setSGeometryOpposite(std::vector<std::shared_ptr<t_road>> &vecRoad);

    void getRoadSurfaceContourPoint(const std::vector< std::shared_ptr<t_road> > &vecAllRoad, RoadMapPoint &roadMapAllPoint);

    double getLaneSectionEnd(const double& roadLength,
                             const double& dLaneStart,
                             int startSectionIndex,
                             const std::vector<std::shared_ptr<t_road_lanes_laneSection>>& laneSections);

    std::shared_ptr<t_road_lanes_laneOffset> getLaneOffset(const double& laneSectionStart,
                                                           const std::vector<std::shared_ptr<t_road_lanes_laneOffset>>& laneOffsets);

    LaneSectionPoint getLaneSectionPoint(const std::string& roadId,
                                         const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset,
                                         const std::shared_ptr<t_road_lanes_laneSection> &laneSection,
                                         const std::vector<std::shared_ptr<t_road_planView_geometry>> &vecGeometry,
                                         double dLaneSectionStart, double dLaneSectionEnd, double dRoadLength,
                                         std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > > &lanesectionRoadmarkPoint);

    void getGeometryIndex(const std::string& roadId, const std::vector<std::shared_ptr<t_road_planView_geometry>> &vecGeometry,
                          int &iStartIndex, int &iEndIndex, double dLaneStart, double dLaneEnd);

    std::vector<QVector<std::pair<QPointF, int> > > getGeometryData(const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset,
                                                                    const std::shared_ptr<t_road_lanes_laneSection> &laneSection,
                                                                    const std::shared_ptr<t_road_planView_geometry> &geometry, double dRelatGeometrySStart,
                                                                    double dRelatGeometrySEnd, double dLaneSectionEnd, double dRoadLength,
                                                                    std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint);

    void getAllPointOfLaneFromGeometryS(const std::shared_ptr<t_road_planView_geometry> &geometry,
                                        const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset,
                                        const std::shared_ptr<t_road_lanes_laneSection> &laneSection,
                                        const double &dGeometryS, const double &dRelatGeometrySStart,
                                        const double &dLaneSectionEnd, const double &dRelatLaneSectionSOffset,
                                        const double &dRoadLength,
                                        const std::vector<double> &vecRoadMarkS,
                                        QVector<std::pair<QPointF, int> > &vecQpointf,
                                        std::map<int, QVector<std::pair<QPointF, int> > > &qvecQvecLeftLanesPoint,
                                        std::map<int, QVector<std::pair<QPointF, int> > > &qvecQvecRightLanesPoint,
                                        std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint);

    void pointfOfLanesOrderAdjust(std::vector<QVector<std::pair<QPointF, int> > > &vecQvecAllLanesPoint,
                                  const std::vector<QVector<std::pair<QPointF, int> > > &vecQvecCenterLanePoint,
                                  const std::map<int, QVector<std::pair<QPointF, int> > > &vecQvecLeftLanesPoint,
                                  const std::map<int, QVector<std::pair<QPointF, int> > > &vecQvecRightLanesPoint) const;

    void getLengthOfRoadMarkFromLane(std::vector<double> &vecRoadMarkLength, const t_road_lanes_laneSection_lr_lane &eachLane, const double &dLaneSectionEnd) const;

    PointFHdg getReferencePointf(const std::shared_ptr<t_road_planView_geometry> &geometry,
                                 const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset,
                                 const double &dGeometryS, const double &dRelatLaneSectionS) const;

    PointFHdg calcPosition(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const;
    PointFHdg getLineData(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const;
    PointFHdg getSpiralData(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const;
    PointFHdg getArcData(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const;
    PointFHdg getPoly3Data(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const;
    PointFHdg getParamPoly3Data(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const;

    void getReferenceOffset(PointFHdg &pointfHdg, const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset, const double dLaneSectionDs) const;

    int getIndexOfVec(const std::vector<double> &vec, const double &dRelatSectionDS) const;

    void genRoadMarkPointf(QPointF qpointf, double hdg, int iIndexRoadMark, double dRelatLaneSectionS, double dLengthToReferenc,
                           const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane> > &qvecLane, int iLaneIndex,
                           std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint);

    QVector<std::pair<QPointF, int> > getCurrentLanePoint(const std::shared_ptr<t_road_planView_geometry> &geometry, const PointFHdg &pointfHdg,
                                                          const int iLaneIndex, const double dLaneSectionEnd, const double dRelatLaneSectionS,
                                                          const double dRelatRoadS, const double dRoadLength,
                                                          const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane> > &qvecLane,
                                                          const std::vector<std::pair<double, PointFHdg> > &qvecRelatLaneSectionSAndPointFHdg,
                                                          std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint,
                                                          bool isLeft);

    double getDistanceFromCurrentLaneAndS(const int iLaneIndex, const double &dLaneSectionEnd, const double &dLaneSectionDs,
                                          const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane> > &vecLane, bool isLeft) const;

    std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane_width>> getAllWidthToReference(const int iLaneIndex,
                                                                                                const double &dLaneSectionEnd,
                                                                                                const double &dLaneSectionDs,
                                                                                                const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane> > &vecLane, bool isLeft) const;

    std::shared_ptr<t_road_lanes_laneSection_lr_lane_width> getWidthFromLane(const std::shared_ptr<t_road_lanes_laneSection_lr_lane> lane,
                                                                             const double &dLaneSectionEnd, const double &dRelatSectionDS) const;


    void getLengthOfWidthFromLane(std::vector<double> &vecWidthLength, std::map<double, int> &mapWidthLengthAndIndex,
                                  const std::shared_ptr<t_road_lanes_laneSection_lr_lane> eachLane, const double &dLaneSectionEnd) const;

    void mergeAllRelativelyLaneSection(QVector<QVector<QPointF> > &qvecQvecEachLaneSection,
                                         const QVector<QVector<QVector<QPointF> > > &qvecQvecQvecAllRelativelyLaneSection) const;

    MapInfo();
    ~MapInfo();
    MapInfo(const MapInfo &)=delete;
    MapInfo &operator =(const MapInfo &)=delete;

    std::map<std::string,
    std::map<int,
    std::map<int,
    std::map<std::string,
    std::map<std::string,
    QVector<std::pair<QPointF, int>>>>>>> m_qmapAllRoadMarkPoint;

    QPointF m_maxPoint;

    QPointF m_minPoint;
};

#endif // MAPINFO_H
