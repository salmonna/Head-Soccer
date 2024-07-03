#include "Factory/MovingFactory.h"
//--------------------------------------------------------------------------------------
// Create a moving object based on the given name and ball
std::shared_ptr<MovingObject> MovingFactory::createMoving(const std::string& name, std::shared_ptr<Ball>& ball) {
	auto it = getMovingMap().find(name);
	if (it == getMovingMap().end())
		return nullptr;
	return it->second(ball);
}
//--------------------------------------------------------------------------------------
// Register a function for creating a moving object with a ball parameter
bool MovingFactory::registeritMoving(const std::string& name, FunctionTypeWithBall f) {
	getMovingMap().emplace(name, f);
	return true;
}
//--------------------------------------------------------------------------------------
// Register a function for creating a moving object without a ball parameter
bool MovingFactory::registeritMoving(const std::string& name, FunctionType f) {
	getMovingMap().emplace(name, [f](std::shared_ptr<Ball>) { return f(); });
	return true;
}