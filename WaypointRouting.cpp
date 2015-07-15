#include "WaypointRouting.h"

WaypointRouting::WaypointRouting()
{
}

WaypointRouting::~WaypointRouting()
{
}


double WaypointRouting::getCourseToSteer(const PositionModel boat, const double trueWindDirection) const
{
	double cts = 0.0;
	if (m_waypoint != nullptr)
		cts = m_waypoint->getCourseToSteer(boat, trueWindDirection);
	else
		throw "WaypointRouting::setSystemStateCommands(), no waypoint set";
	return cts;
}

bool WaypointRouting::nextWaypoint(const PositionModel boat) const
{
	if (m_waypoint != nullptr)
		return m_waypoint->nextWaypoint(boat);
	else
		throw "WaypointRouting::nextWaypoint(), no waypoint set";
}

void WaypointRouting::setWaypoint(const WaypointModel waypoint)
{
	if (waypoint.type == 1) {
		m_waypoint = std::make_unique<StandardWaypoint>(waypoint, m_tackAngle, m_sectorAngle);
	}
	if (waypoint.type == 2) {
		m_waypoint = std::make_unique<TimedWaypoint>(waypoint, m_tackAngle, m_sectorAngle);
	}
}

void WaypointRouting::setCourseCalcValues(const double tackAngle, const double sectorAngle)
{
	m_tackAngle = tackAngle;
	m_sectorAngle = sectorAngle;
}