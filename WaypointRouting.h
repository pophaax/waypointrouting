#ifndef __WAYPOINTROUTING_H__
#define __WAYPOINTROUTING_H__

#include "StandardWaypoint.h"
#include "TimedWaypoint.h"
#include "../models/SystemStateModel.h"
#include "../models/PositionModel.h"
#include "../models/WaypointModel.h"

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
private:
	StandardWaypoint m_waypoint;
};

#endif