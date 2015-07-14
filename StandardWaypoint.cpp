#include "StandardWaypoint.h"

StandardWaypoint::StandardWaypoint(const WaypointModel waypoint, const double tackAngle, const double sectorAngle) :
	m_waypoint(waypoint)//fix assignment constructor / copy construct???
{
	m_courseCalc.setTackAngle(tackAngle);
	m_courseCalc.setSectorAngle(sectorAngle);
}

StandardWaypoint::~StandardWaypoint()
{
}


bool StandardWaypoint::nextWaypoint(const PositionModel boat) const
{
	bool nextWaypoint = false;
	if (reachedRadius(m_waypoint.radius, boat))
		nextWaypoint = true;
	return nextWaypoint;
}

double StandardWaypoint::getCourseToSteer(const PositionModel boat, const double trueWindDirection)
{
	m_courseCalc.setTrueWindDirection(trueWindDirection);
	m_courseCalc.calculateCourseToSteer(boat, m_waypoint);
	return m_courseCalc.getCTS();
}

bool StandardWaypoint::reachedRadius(const double radius, const PositionModel boat) const
{
	bool reachedRadius = false;
	double dtw = m_courseMath.calculateDTW(boat, m_waypoint.positionModel);
	if (dtw < radius)
		reachedRadius = true;
	return reachedRadius;
}

