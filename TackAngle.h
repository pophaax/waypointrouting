#ifndef __TACKANGLE_H__
#define __TACKANGLE_H__

class SystemStateModel;

class TackAngle
{
public:
	TackAngle(double tackAngle, double maxTackAngle, double minTackSpeed);
	~TackAngle();

	double adjustedTackAngle(SystemStateModel systemStateModel);

private:
	double getSpeed(SystemStateModel systemStateModel);

	double m_tackAngle, m_maxTackAngle, m_minTackSpeed;
};

#endif