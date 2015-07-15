
#ifndef __TIMEDWAYPOINT_H__
#define __TIMEDWAYPOINT_H__

#include "StandardWaypoint.h"
#include <chrono>

class TimedWaypoint : public StandardWaypoint
{
public:
	TimedWaypoint(const WaypointModel waypoint, const double tackAngle, const double sectorAngle);
	TimedWaypoint(const TimedWaypoint &) = delete;
	TimedWaypoint & operator=(const TimedWaypoint &) = delete;
	~TimedWaypoint() override;

	bool nextWaypoint(const PositionModel boat) const override;
	double getCourseToSteer(const PositionModel boat, const double trueWindDirection) override;

private:
	bool timerDone() const;
	void startTimer();
	std::chrono::steady_clock::time_point m_timerStart;
	bool m_timerRunning;
};

#endif