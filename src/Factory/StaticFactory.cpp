#include "Factory/StaticFactory.h"

//--------------------------------------------------------------------------------
// Create a static object based on its name
std::shared_ptr<StaticObject> StaticFactory::createStatic(const std::string& name) {
	auto it = getStaticMap().find(name);
	if (it == getStaticMap().end())
		return nullptr;
	return it->second();
}
//--------------------------------------------------------------------------------
// Register a function pointer to create a static object with a given name
bool StaticFactory::registeritStatic(const std::string& name, std::shared_ptr<StaticObject>(*f)()) {
	getStaticMap().emplace(name, f);
	return true;
}