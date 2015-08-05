#include "WaypointRouting.h"
#include <math.h>
#include "coursecalculation/CourseCalculation.h"
#include "utility/Timer.h"
#include "utility/Utility.h"
#include "models/WaypointModel.h"
#include "models/SystemStateModel.h"


WaypointRouting::WaypointRouting(WaypointModel waypoint, double innerRadiusRatio,
		double tackAngle, double maxTackAngle, double minTackSpeed, double sectorAngle) :
	m_tackAngleHandler(tackAngle, maxTackAngle, minTackSpeed),
	m_commandHandler(),
	m_waypoint(waypoint),
	m_innerRadiusRatio(innerRadiusRatio),
	m_courseToSteer(0)
{
	m_courseCalc.setTackAngle(tackAngle);
	m_courseCalc.setSectorAngle(sectorAngle);
}

WaypointRouting::~WaypointRouting()
{
}


void WaypointRouting::getCommands(double & rudder, double & sail, PositionModel boat,
	double trueWindDirection, double heading, SystemStateModel systemStateModel)
{
	if (m_waypoint.time > 0 && reachedRadius(m_waypoint.radius * m_innerRadiusRatio, boat))
	{
		m_courseToSteer = trueWindDirection;
		rudder = m_commandHandler.rudderCommand(m_courseToSteer, heading);
		sail = m_commandHandler.runningSailCommand();
	}
	else
	{
		m_courseCalc.setTackAngle(m_tackAngleHandler.adjustedTackAngle(systemStateModel));

		m_courseToSteer = m_courseCalc.calculateCourseToSteer(boat, m_waypoint, trueWindDirection);
		rudder = m_commandHandler.rudderCommand(m_courseToSteer, heading);
		sail = m_commandHandler.sailCommand(systemStateModel.windsensorModel.direction);
	}
}


bool WaypointRouting::nextWaypoint(PositionModel boat)
{
	bool nextWaypoint = false;
	if (m_waypoint.time > 0)
	{
		if (m_timer.timeReached(m_waypoint.time))
			nextWaypoint = true;
		if (reachedRadius(m_waypoint.radius, boat))
			m_timer.start();
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
	m_timer.stop();
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

double WaypointRouting::getCTS()
{
	return m_courseToSteer;
}

bool WaypointRouting::getTack()
{
	return m_courseCalc.getTack();
}

bool WaypointRouting::getGoingStarboard()
{
	return m_courseCalc.getGoingStarboard();
}


bool WaypointRouting::reachedRadius(double radius, PositionModel boat) const
{
	bool reachedRadius = false;
	double dtw = m_courseMath.calculateDTW(boat, m_waypoint.positionModel);
	if (dtw < radius)
		reachedRadius = true;
	return reachedRadius;
}
