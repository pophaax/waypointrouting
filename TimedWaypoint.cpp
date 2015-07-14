#include "TimedWaypoint.h"
#include <iostream>

TimedWaypoint::TimedWaypoint(const WaypointModel waypoint, const double tackAngle, const double sectorAngle) :
	StandardWaypoint(waypoint, tackAngle, sectorAngle),
	m_clockGoing(false)
{
}

TimedWaypoint::~TimedWaypoint()
{
}

bool TimedWaypoint::nextWaypoint(const PositionModel boat) const
{
	bool nextWaypoint = false;
	if (timeDone())
		nextWaypoint = true;
	return nextWaypoint;
}

double TimedWaypoint::getCourseToSteer(const PositionModel boat, const double trueWindDirection)
{
	double cts = 0.0;
	if (!StandardWaypoint::reachedRadius(m_waypoint.innerRadius, boat))
	{
		// WANT THIS???? m_clockGoing = false;
		cts = StandardWaypoint::getCourseToSteer(boat, trueWindDirection);
	}
	else
	{
		if (!m_clockGoing)
		{
			m_clockStart = std::chrono::steady_clock::now();
			m_clockGoing = true;
		}
		cts = trueWindDirection;
	}
	return cts;
}

bool TimedWaypoint::timeDone() const
{
	bool done = false;
	if (m_clockGoing)
	{
		std::chrono::steady_clock::time_point clockEnd = std::chrono::steady_clock::now();
		std::chrono::duration<double> timeSpan =
			std::chrono::duration_cast<std::chrono::duration<double>>(clockEnd - m_clockStart);
		if (timeSpan.count() > static_cast<double>(m_waypoint.time))
			done = true;
	}
	return done;
}
