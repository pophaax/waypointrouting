#include "WaypointRouting.h"
#include "models/WaypointModel.h"
#include "coursecalculation/CourseCalculation.h"
#include "utility/Timer.h"

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


double WaypointRouting::calculateCourseToSteer(PositionModel boat, double trueWindDirection)
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
		if (m_timer.timeUntil(m_waypoint.time) <= 0 && m_timerRunning)
			nextWaypoint = true;
		if (reachedRadius(m_waypoint.radius, boat) && !m_timerRunning)
		{
			m_timer.start();
			m_timerRunning = true;
		}
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

double WaypointRouting::getDTW()
{
	return m_courseCalc.getDTW();
}

double WaypointRouting::getBTW()
{
	return m_courseCalc.getBTW();
}

double WaypointRouting::getTWD()
{
	return m_courseCalc.getTWD();
}

bool WaypointRouting::getTack()
{
	return m_courseCalc.getTack();
}

bool WaypointRouting::getGoingStarboard()
{
	return m_courseCalc.getGoingStarboard();
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