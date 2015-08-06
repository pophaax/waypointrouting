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
	double speed = getSpeed(systemStateModel);
	if (speed < m_minTackSpeed)
	{
		double extraAngle = m_maxTackAngle - m_tackAngle;
		double factor = 1 - (speed / m_minTackSpeed);
		adjustedTackAngle = factor * extraAngle + m_tackAngle;
	}
	return adjustedTackAngle;
}



double TackAngle::getSpeed(SystemStateModel systemStateModel)
{
	double speed = 0;
	if (Utility::angleDifference(systemStateModel.gpsModel.heading,
		systemStateModel.compassModel.heading) < 90)
	{
		speed = systemStateModel.gpsModel.speed;
	}
	return speed;
}