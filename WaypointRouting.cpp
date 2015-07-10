#include "WaypointRouting.h"

explicit WaypointRouting(WaypointModel waypoint)
{
}

void WaypointRouting::setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection)
{
	m_waypoint.setSystemStateCommands(systemState, boat, trueWindDirection);
}

bool WaypointRouting::nextWaypoint()
{
	return m_waypoint.nextWaypoint();
}

void WaypointRouting::setWaypoint(WaypointModel waypoint)
{
	m_waypoint = StandardWaypoint(waypoint);
/*	if (waypointModel.type == standard)
		m_waypoint = StandardWaypoint(waypoint);
	if (waypointModel.type == timed)
		m_waypoint = TimedWaypoint(waypoint);*/
}
