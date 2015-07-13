#include "WaypointRouting.h"

WaypointRouting::WaypointRouting() :
	m_starboardExtreme(0),
	m_midships(0),
	m_closeReach(0),
	m_running(0)
{
}

WaypointRouting::~WaypointRouting()
{
}


void WaypointRouting::setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection)
{
	if (m_waypoint != nullptr)
		m_waypoint->setSystemStateCommands(systemState, boat, trueWindDirection);
	else
		throw "WaypointRouting::setSystemStateCommands(), no waypoint set";
}

bool WaypointRouting::nextWaypoint()
{
	if (m_waypoint != nullptr)
		return m_waypoint->nextWaypoint();
	else
		throw "WaypointRouting::nextWaypoint(), no waypoint set";
}

void WaypointRouting::setWaypoint(WaypointModel waypoint)
{
	if (waypoint.type == 1) {
		m_waypoint = std::make_unique<StandardWaypoint>(waypoint,
			m_starboardExtreme, m_midships, m_closeReach, m_running, m_tackAngle, m_sectorAngle);
	}
	if (waypoint.type == 2) {
		m_waypoint = std::make_unique<TimedWaypoint>(waypoint,
			m_starboardExtreme, m_midships, m_closeReach, m_running, m_tackAngle, m_sectorAngle);
	}
}

void WaypointRouting::setRudderCommandValues(int starboardExtreme, int midships)
{
	m_starboardExtreme = starboardExtreme;
	m_midships = midships;
}

void WaypointRouting::setSailCommandValues(int closeReach, int running)
{
	m_closeReach = closeReach;
	m_running = running;
}

void WaypointRouting::setCourseCalcValues(double tackAngle, double sectorAngle)
{
	m_tackAngle = tackAngle;
	m_sectorAngle = sectorAngle;
}
