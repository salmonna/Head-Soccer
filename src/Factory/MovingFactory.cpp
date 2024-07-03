#include "Factory/MovingFactory.h"

std::shared_ptr<MovingObject> MovingFactory::createMoving(const std::string& name, std::shared_ptr<Ball> ball) {
	auto it = getMovingMap().find(name);
	if (it == getMovingMap().end())
		return nullptr;
	return it->second(ball);
}

bool MovingFactory::registeritMoving(const std::string& name, FunctionTypeWithBall f) {
	getMovingMap().emplace(name, f);
	return true;
}

bool MovingFactory::registeritMoving(const std::string& name, FunctionType f) {
	getMovingMap().emplace(name, [f](std::shared_ptr<Ball>) { return f(); });
	return true;
}