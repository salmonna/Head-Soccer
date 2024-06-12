#include "Factory/StaticFactory.h"


std::shared_ptr<StaticObject> StaticFactory::createStatic(const std::string& name) {
	auto it = getStaticMap().find(name);
	if (it == getStaticMap().end())
		return nullptr;
	return it->second();
}

bool StaticFactory::registeritStatic(const std::string& name, std::shared_ptr<StaticObject>(*f)()) {
	getStaticMap().emplace(name, f);
	return true;
}