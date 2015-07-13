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

	void setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection);
	bool nextWaypoint();
	void setWaypoint(WaypointModel waypoint);
	void setRudderCommandValues(int starboardExtreme, int midships);
	void setSailCommandValues(int closeReach, int running);
	void setCourseCalcValues(double tackAngle, double sectorAngle);

private:
	std::unique_ptr<StandardWaypoint> m_waypoint;
	int m_starboardExtreme, m_midships, m_closeReach, m_running;
	double m_tackAngle, m_sectorAngle;
};

#endif