#include "StandardWaypoint.h"

StandardWaypoint::StandardWaypoint(WaypointModel waypoint) :
	m_waypoint(waypoint)//fix assignment constructor / copy construct???
{
}

bool StandardWaypoint::nextWaypoint()
{
	return reachedWaypoint();
}

void StandardWaypoint::setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection)
{
	m_courseCalc.setTrueWindDirection(trueWindDirection);
	m_courseCalc.calculateCourseToSteer(boat, m_waypoint);
	systemState.rudder = m_rudderCommand.getCommand(
		m_courseCalc.getCTS(), systemState.compassModel.heading);
	systemState.sail = m_sailCommand.getCommand(systemState.windsensorModel.direction);
}

bool StandardWaypoint::reachedWaypoint()
{
	bool reachedWaypoint = false;
	if (m_courseCalc.getDTW() < m_waypoint.radius)
		reachedWaypoint = true;
	return reachedWaypoint;
}
