
#ifndef __TIMEDWAYPOINT_H__
#define __TIMEDWAYPOINT_H__

#include "StandardWaypoint.h"

class TimedWaypoint : public StandardWaypoint
{
public:
	TimedWaypoint(WaypointModel waypoint);
	TimedWaypoint(const TimedWaypoint &) = delete;
	TimedWaypoint & operator=(const TimedWaypoint &) = delete;
	~TimedWaypoint() override;

	bool nextWaypoint() override;
	void setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection) override;

};

#endif