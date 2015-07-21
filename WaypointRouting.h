#ifndef __WAYPOINTROUTING_H__
#define __WAYPOINTROUTING_H__

#include <chrono>
#include "models/WaypointModel.h"
#include "coursecalculation/CourseCalculation.h"

class PositionModel;

class WaypointRouting
{
public:
	WaypointRouting(WaypointModel waypoint, double innerRadiusRatio,
		double tackAngle, double sectorAngle);
	WaypointRouting(const WaypointRouting &) = delete;
	WaypointRouting & operator=(const WaypointRouting &) = delete;	
	~WaypointRouting();

	double calculateCourseToSteer(PositionModel boat, double trueWindDirection);
	bool nextWaypoint(PositionModel boat);
	void setWaypoint(WaypointModel waypoint);
	void setCourseCalcValues(double tackAngle, double sectorAngle);
	void setInnerRadiusRatio(double ratio);

	double getDTW();
	double getCTS();
	double getBTW();
	double getTWD();
	bool getTack();
	bool getGoingStarboard();

private:
	double timedCTS(PositionModel boat, double trueWindDirection);
	bool reachedRadius(double radius, PositionModel boat) const;
	double getCTSFromCourseCalc(PositionModel boat, double trueWindDirection);
	WaypointModel m_waypoint;
	CourseCalculation m_courseCalc;
	CourseMath m_courseMath;
	double m_innerRadiusRatio;

	//timer
	bool timerDone() const;
	void startTimer();
	std::chrono::steady_clock::time_point m_timerStart;
	bool m_timerRunning;
};

#endif