#include "TimedWaypoint.h"

TimedWaypoint::TimedWaypoint(const WaypointModel waypoint,
	const double tackAngle, const double sectorAngle) :
	StandardWaypoint(waypoint, tackAngle, sectorAngle),
	m_timerRunning(false)
{
}

TimedWaypoint::~TimedWaypoint()
{
}

bool TimedWaypoint::nextWaypoint(const PositionModel boat) const
{
	bool nextWaypoint = false;
	if (timerDone())
		nextWaypoint = true;
	return nextWaypoint;
}

double TimedWaypoint::getCourseToSteer(const PositionModel boat, const double trueWindDirection)
{
	double cts = 0.0;
	if (StandardWaypoint::reachedRadius(m_waypoint.innerRadius, boat))
	{
		startTimer();
		cts = trueWindDirection;
	}
	else if (StandardWaypoint::reachedRadius(m_waypoint.radius, boat))
	{
		startTimer();
		cts = StandardWaypoint::getCourseToSteer(boat, trueWindDirection);		
	}
	else
	{
		m_timerRunning = false;
		cts = StandardWaypoint::getCourseToSteer(boat, trueWindDirection);
	}
	return cts;
}

bool TimedWaypoint::timerDone() const
{
	bool done = false;
	if (m_timerRunning)
	{
		using namespace std::chrono;
		steady_clock::time_point clockEnd = steady_clock::now();
		auto timeSpan = duration_cast<seconds>(clockEnd - m_timerStart);
		if (timeSpan.count() >= m_waypoint.time)
			done = true;
	}
	return done;
}

void TimedWaypoint::startTimer()
{
	if (!m_timerRunning)
	{
		m_timerStart = std::chrono::steady_clock::now();
		m_timerRunning = true;
	}	
}