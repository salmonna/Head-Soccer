#pragma once
#include "gameObject/StaticObject.h"

typedef std::map<std::string, std::shared_ptr<StaticObject>(*)()> StaticMap;
// ================   class MovingFactory   ============================
class StaticFactory {
public:
	static std::shared_ptr<StaticObject> createStatic(const std::string& name);
	static bool registeritStatic(const std::string& name, std::shared_ptr<StaticObject>(*)());
private:
	static StaticMap & getStaticMap()
	{
		static StaticMap m_staticMap;
		return m_staticMap;
	}
};
