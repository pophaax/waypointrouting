#ifndef __WAYPOINTROUTING_H__
#define __WAYPOINTROUTING_H__

#include "models/WaypointModel.h"
#include "coursecalculation/CourseCalculation.h"
#include "utility/Timer.h"

class PositionModel;

class WaypointRouting
{
public:
	WaypointRouting(WaypointModel waypoint, double innerRadiusRatio,
		double tackAngle, double sectorAngle);
	WaypointRouting(const WaypointRouting &) = delete;
	WaypointRouting & operator=(const WaypointRouting &) = delete;	
	~WaypointRouting();

	void getCommands(double & rudder, double & sail, PositionModel boat,
		double trueWindDirection, double heading, double relativeWindDirection);
	bool nextWaypoint(PositionModel boat);
	void setWaypoint(WaypointModel waypoint);
	void setCourseCalcValues(double tackAngle, double sectorAngle);
	void setInnerRadiusRatio(double ratio);
	double rudderCommand(double courseToSteer, double heading);
	double sailCommand(double relativeWindDirection);

	double getDTW();
	double getBTW();
	double getTWD();
	double getCTS();
	bool getTack();
	bool getGoingStarboard();

private:
	bool reachedRadius(double radius, PositionModel boat) const;

	WaypointModel m_waypoint;
	CourseCalculation m_courseCalc;
	CourseMath m_courseMath;
	double m_innerRadiusRatio;
	Timer m_timer;
	double m_courseToSteer;

	const double m_starboardExtreme;
	const double m_portExtreme;
	const double m_closeReach;
	const double m_running;
};

#endif