
#ifndef __TIMEDWAYPOINT_H__
#define __TIMEDWAYPOINT_H__

#include "StandardWaypoint.h"

class TimedWaypoint : public StandardWaypoint
{
public:
	explicit TimedWaypoint(WaypointModel waypoint, int starboardExtreme,
		int midships, int closeReach, int running, double tackAngle, double sectorAngle);
	TimedWaypoint(const TimedWaypoint &) = delete;
	TimedWaypoint & operator=(const TimedWaypoint &) = delete;
	~TimedWaypoint() override;

	bool nextWaypoint() override;
	void setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection) override;

};

#endif