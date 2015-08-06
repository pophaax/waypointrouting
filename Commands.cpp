#include "Commands.h"
#include <math.h>
#include "utility/Utility.h"

Commands::Commands() :
	m_starboardExtreme(1),
	m_portExtreme(-1),
	m_closeReach(0),
	m_running(1)
{
}

Commands::~Commands()
{
}


double Commands::rudderCommand(double courseToSteer, double heading)
{
	double offCourse = courseToSteer - heading;
	double steeringValue = 0;

	if (cos(Utility::degreeToRadian(offCourse)) > 0) { //offCourse > -90 && offCourse < 90
		steeringValue = sin(Utility::degreeToRadian(offCourse));
	}
	else {
		if (sin(Utility::degreeToRadian(offCourse)) > 0) { //offCourse >= 90
			steeringValue = m_starboardExtreme;
		}
		else {
			steeringValue = m_portExtreme;
		}
	}
	return steeringValue;
}


double Commands::sailCommand(double relativeWindDirection)
{
	double mid = (m_closeReach + m_running) / 2;
	double delta = m_running - mid;
	return mid - cos(Utility::degreeToRadian(relativeWindDirection)) * delta;
}


double Commands::runningSailCommand()
{
	return m_running;
}
