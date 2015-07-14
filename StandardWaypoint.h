#ifndef __STANDARDWAYPOINT_H__
#define __STANDARDWAYPOINT_H__

#include "../models/PositionModel.h"
#include "../models/WaypointModel.h"
#include "../coursecalculation/CourseCalculation.h"

class StandardWaypoint
{
public:
	StandardWaypoint(const WaypointModel waypoint, const double tackAngle, const double sectorAngle);
	StandardWaypoint(const StandardWaypoint &) = delete;
	StandardWaypoint & operator=(const StandardWaypoint &) = delete;
	virtual ~StandardWaypoint();
	
	virtual bool nextWaypoint(const PositionModel boat) const;
	virtual double getCourseToSteer(const PositionModel boat, const double trueWindDirection);

protected:
	bool reachedRadius(const double radius, const PositionModel boat) const;
	WaypointModel m_waypoint;

private:
	CourseCalculation m_courseCalc;
	CourseMath m_courseMath;
};

#endif


