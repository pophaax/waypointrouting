#include "TimedWaypoint.h"

TimedWaypoint::TimedWaypoint(WaypointModel waypoint, int starboardExtreme,
	int midships, int closeReach, int running, double tackAngle, double sectorAngle) :
	StandardWaypoint(waypoint, starboardExtreme, midships, closeReach, running, tackAngle, sectorAngle)
{
}

TimedWaypoint::~TimedWaypoint()
{
}


bool TimedWaypoint::nextWaypoint()
{
	bool nextWaypoint = false;
/*	if (timeOK && reachedWaypoint())
		nextWaypoint = true;
*/
	return nextWaypoint;
}

void TimedWaypoint::setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection)
{
	if (!reachedWaypoint())
	{
		//set clock to 0?
		StandardWaypoint::setSystemStateCommands(systemState, boat, trueWindDirection);
	}
	else
	{
		//startclockblablabla
	}
}