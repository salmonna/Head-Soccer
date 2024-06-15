
#pragma once
#include "gameObject/MovingObject.h"


typedef std::map<std::string, std::shared_ptr<MovingObject>(*)()> MovingMap;
// ================   class MovingFactory   ============================
class MovingFactory {
public:
	static std::shared_ptr<MovingObject> createMoving(const std::string& name);
	static bool registeritMoving(const std::string& name, std::shared_ptr<MovingObject>(*)());
private:
	static MovingMap & getMovingMap()
	{
		static MovingMap m_movingMap;
		return m_movingMap;
	}
};
