#include "WaypointRouting.h"
#include <math.h>
#include "models/WaypointModel.h"
#include "coursecalculation/CourseCalculation.h"
#include "utility/Timer.h"
#include "utility/Utility.h"

WaypointRouting::WaypointRouting(WaypointModel waypoint, double innerRadiusRatio,
		double tackAngle, double sectorAngle) :
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
	double trueWindDirection, double heading, double relativeWindDirection)
{
	if (m_waypoint.time > 0)
	{
		if (reachedRadius(m_waypoint.radius * m_innerRadiusRatio, boat))
		{
			m_courseToSteer = trueWindDirection;
			rudder = rudderCommand(m_courseToSteer, heading);
			sail = 1.0;
		}
		else
		{
			m_courseToSteer = getCTSFromCourseCalc(boat, trueWindDirection);
			rudder = rudderCommand(m_courseToSteer, heading);
			sail = sailCommand(relativeWindDirection);
		}
	}
	else
	{
		m_courseToSteer = getCTSFromCourseCalc(boat, trueWindDirection);
		rudder = rudderCommand(m_courseToSteer, heading);
		sail = sailCommand(relativeWindDirection);
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

double WaypointRouting::getCTSFromCourseCalc(PositionModel boat, double trueWindDirection)
{
	m_courseCalc.setTrueWindDirection(trueWindDirection);
	m_courseCalc.calculateCourseToSteer(boat, m_waypoint);
	return m_courseCalc.getCTS();
}


double WaypointRouting::rudderCommand(double courseToSteer, double heading)
{
	double offCourse = courseToSteer - heading;
	double steeringValue = 0;

	if (cos(Utility::degreeToRadian(offCourse)) > 0) { //offCourse > -90 && offCourse < 90
		steeringValue = sin(Utility::degreeToRadian(offCourse));
	}
	else {
		if (sin(Utility::degreeToRadian(offCourse)) > 0) { //offCourse >= 90
			steeringValue = 1;
		}
		else {
			steeringValue = -1;
		}
	}
	return steeringValue;
}


double WaypointRouting::sailCommand(double relativeWindDirection)
{
	double mid = 0.5;
	double delta = 0.5;
	return mid - cos(Utility::degreeToRadian(relativeWindDirection)) * delta;
}