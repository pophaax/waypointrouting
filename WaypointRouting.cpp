#include "WaypointRouting.h"

WaypointRouting::WaypointRouting(WaypointModel waypoint, double innerRadiusRatio,
		double tackAngle, double sectorAngle) :
	m_waypoint(waypoint),
	m_innerRadiusRatio(innerRadiusRatio),
	m_timerRunning(false)
{
	m_courseCalc.setTackAngle(tackAngle);
	m_courseCalc.setSectorAngle(sectorAngle);
}

WaypointRouting::~WaypointRouting()
{
}


double WaypointRouting::getCourseToSteer(PositionModel boat, double trueWindDirection)
{
	double cts = 0.0;
	if (m_waypoint.time > 0)
		cts = timedCTS(boat, trueWindDirection);
	else
		cts = getCTSFromCourseCalc(boat, trueWindDirection);
	return cts;
}

bool WaypointRouting::nextWaypoint(PositionModel boat)
{
	bool nextWaypoint = false;
	if (m_waypoint.time > 0)
	{
		if (timerDone())
			nextWaypoint = true;
		if (reachedRadius(m_waypoint.radius, boat))
			startTimer();
	}
	else
	{
		if (reachedRadius(m_waypoint.radius, boat))
			nextWaypoint = true;
	}
	return nextWaypoint;
}

void WaypointRouting::setWaypoint(WaypointModel waypoint)
{
	m_waypoint = waypoint;
	m_timerRunning = false;
}

void WaypointRouting::setCourseCalcValues(double tackAngle, double sectorAngle)
{
	m_courseCalc.setTackAngle(tackAngle);
	m_courseCalc.setSectorAngle(sectorAngle);
}

void WaypointRouting::setInnerRadiusRatio(double ratio)
{
	m_innerRadiusRatio = ratio;
}

double WaypointRouting::timedCTS(PositionModel boat, double trueWindDirection)
{
	m_courseCalc.setTrueWindDirection(trueWindDirection);
	m_courseCalc.calculateCourseToSteer(boat, m_waypoint);
	double cts = 0.0;
	if (reachedRadius(m_waypoint.radius * m_innerRadiusRatio, boat))
	{
		cts = trueWindDirection;
	}
	else if (reachedRadius(m_waypoint.radius, boat))
	{
		cts = getCTSFromCourseCalc(boat, trueWindDirection);
	}
	else
	{
		cts = getCTSFromCourseCalc(boat, trueWindDirection);
	}
	return cts;
}

bool WaypointRouting::reachedRadius(double radius, PositionModel boat) const
{
	bool reachedRadius = false;
	double dtw = m_courseMath.calculateDTW(boat, m_waypoint.positionModel);
	if (dtw < radius)
		reachedRadius = true;
	return reachedRadius;
}

double WaypointRouting::getCTSFromCourseCalc(PositionModel boat, double trueWindDirection)
{
	m_courseCalc.setTrueWindDirection(trueWindDirection);
	m_courseCalc.calculateCourseToSteer(boat, m_waypoint);
	return m_courseCalc.getCTS();
}

bool WaypointRouting::timerDone() const
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

void WaypointRouting::startTimer()
{
	if (!m_timerRunning)
	{
		m_timerStart = std::chrono::steady_clock::now();
		m_timerRunning = true;
	}	
}