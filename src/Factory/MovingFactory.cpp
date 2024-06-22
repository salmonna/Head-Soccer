#include "Factory/MovingFactory.h"

std::shared_ptr<MovingObject> MovingFactory::createMoving(const std::string& name) {
	auto it = getMovingMap().find(name);
	if (it == getMovingMap().end())
		return nullptr;
	return it->second();
}

bool MovingFactory::registeritMoving(const std::string& name, std::shared_ptr<MovingObject>(*f)()) {
	getMovingMap().emplace(name, f);
	return true;
}