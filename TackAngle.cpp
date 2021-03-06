#include "TackAngle.h"
#include "models/SystemStateModel.h"
#include "utility/Utility.h"

TackAngle::TackAngle(double tackAngle, double maxTackAngle, double minTackSpeed) :
	m_tackAngle(tackAngle),
	m_maxTackAngle(maxTackAngle),
	m_minTackSpeed(minTackSpeed)
{
}

TackAngle::~TackAngle()
{

}

double TackAngle::adjustedTackAngle(SystemStateModel systemStateModel)
{
	double adjustedTackAngle = m_tackAngle;
	double speed = Utility::directionAdjustedSpeed(systemStateModel.gpsModel.heading,
												  										systemStateModel.compassModel.heading,
												  										systemStateModel.gpsModel.speed);
	
	if (speed <  m_minTackSpeed)
	{
		double extraAngle = m_maxTackAngle - m_tackAngle;
		double factor = 1 - (speed / m_minTackSpeed);
		adjustedTackAngle = factor * extraAngle + m_tackAngle;
	}
	return adjustedTackAngle;
}
