#ifndef __STANDARDWAYPOINT_H__
#define __STANDARDWAYPOINT_H__

#include "../models/SystemStateModel.h"
#include "../models/PositionModel.h"
#include "../models/WaypointModel.h"
#include "../coursecalculation/CourseCalculation.h"
#include "../ruddercommand/RudderCommand.h"
#include "../sailcommand/SailCommand.h"

class StandardWaypoint
{
public:
	StandardWaypoint(WaypointModel waypoint, int starboardExtreme,
		int midships, int closeReach, int running, double tackAngle, double sectorAngle);
	StandardWaypoint(const StandardWaypoint &) = delete;
	StandardWaypoint & operator=(const StandardWaypoint &) = delete;
	virtual ~StandardWaypoint();
	
	virtual bool nextWaypoint();
	virtual void setSystemStateCommands(SystemStateModel & systemState,
		PositionModel boat, double trueWindDirection);

protected:
	bool reachedWaypoint();

private:
	WaypointModel m_waypoint;
	CourseCalculation m_courseCalc;
	SailCommand m_sailCommand;
	RudderCommand m_rudderCommand;
};

#endif


