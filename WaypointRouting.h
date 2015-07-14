#ifndef __WAYPOINTROUTING_H__
#define __WAYPOINTROUTING_H__

#include <memory>
#include "StandardWaypoint.h"
#include "TimedWaypoint.h"

class WaypointRouting
{
public:
	WaypointRouting();
	WaypointRouting(const WaypointRouting &) = delete;
	WaypointRouting & operator=(const WaypointRouting &) = delete;	
	~WaypointRouting();

	double getCourseToSteer(const PositionModel boat, const double trueWindDirection) const;
	bool nextWaypoint(const PositionModel boat) const;
	void setWaypoint(const WaypointModel waypoint);
	void setCourseCalcValues(const double tackAngle, const double sectorAngle);

private:
	std::unique_ptr<StandardWaypoint> m_waypoint;
	double m_tackAngle, m_sectorAngle;
};

#endif