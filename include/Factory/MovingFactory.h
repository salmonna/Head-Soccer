
#pragma once
#include "gameObject/MovingObject.h"
#include "MovePlayerState/StandPlayerState.h"

#include <functional>

class Ball;

using FunctionTypeWithBall = std::function<std::shared_ptr<MovingObject>(std::shared_ptr<Ball>&)>;
using FunctionType = std::function<std::shared_ptr<MovingObject>()>;
typedef std::map<std::string, FunctionTypeWithBall> MovingMap;

// ================   class MovingFactory   ============================
class MovingFactory {
public:
	static std::shared_ptr<MovingObject> createMoving(const std::string& name, std::shared_ptr<Ball>& ball);

	static bool registeritMoving(const std::string& name, FunctionType);
	static bool registeritMoving(const std::string& name, FunctionTypeWithBall);

private:
	static MovingMap & getMovingMap()
	{
		static MovingMap m_movingMap;
		return m_movingMap;
	}
};
