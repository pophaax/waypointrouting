#include "TimedWaypoint.h"

TimedWaypoint::TimedWaypoint(WaypointModel waypoint) :
	StandardWaypoint(waypoint),
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