#include "Commands.h"
#include <math.h>
#include "utility/Utility.h"
#include <iostream>

Commands::Commands() :
	m_starboardExtreme(1),
	m_portExtreme(-1),
	m_closeReach(0),
	m_running(1)
{}

Commands::~Commands(){}


double Commands::rudderCommand(double courseToSteer, double heading) {
	double offCourse = Utility::limitAngleRange(courseToSteer - heading);
	if (cos(Utility::degreeToRadian(offCourse)) > 0) { //offCourse > -90 && offCourse < 90
		if (offCourse > 180) {
		
			offCourse -= 360;
		}
		return m_portExtreme + (offCourse + 90) * (m_starboardExtreme - m_portExtreme) / 180;			
	} else {
		if (sin(Utility::degreeToRadian(offCourse)) > 0) { //offCourse >= 90
			offCourse = m_starboardExtreme;
		}
		else {
			offCourse = m_portExtreme;
		}
	}
	return offCourse;
}


double Commands::sailCommand(double relativeWindDirection) {
	relativeWindDirection = Utility::limitAngleRange(relativeWindDirection);

	if (relativeWindDirection > 180) {
		relativeWindDirection = 360 - relativeWindDirection;
	} 
	if (relativeWindDirection < 45) {
		return m_closeReach;
	}
		
	return m_closeReach + (relativeWindDirection - 45) * (m_running - m_closeReach) / 135;
	
}


double Commands::runningSailCommand() {
	return m_running;
}
