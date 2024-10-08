
#include "CollisionHandling.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "gameObject/UserPlayer.h"
#include "gameObject/Ball.h"
#include "gameObject/Goal.h"
#include "gameObject/ComputerPlayer.h"
#include "gameObject/ScoreBoard.h"
#include "gameObject/GoalSide.h"
#include "gameObject/GoalBack.h"
#include "gameObject/GoalTop.h"
#include "Keyboard.h"
#include "Resources.h"
#include "SoundControl.h"
#include "Box2d.h"


namespace // anonymous namespace — the standard way to make function "static"
{

    //=======================================UPDATE========================================\\ 
    //update after collide
    void updateBall(Ball& ballObject, Player& PlayerObject)
    {
        if (PlayerObject.getAura()) 
        {
            PlayerObject.getPower()->startTimer();
            ballObject.setPower(PlayerObject.getPower());
            PlayerObject.getPower()->activatePowerOnBall(&ballObject);
            PlayerObject.setAura(false);
            // Reset the velocity of the Box2D body
            PlayerObject.getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  // Set linear velocity to zero
            PlayerObject.getBody()->SetAngularVelocity(0.0f);               // Set angular velocity to zero
        }
        else if (ballObject.getPower()->powerIsActive()){
            ballObject.getPower()->activatePowerOnPlayer(&PlayerObject);
        }
    }

    // primary collision-processing functions
    void PlayerCollidBall(GameObject& Player, GameObject& ball)
    {

        Ball & ballObject = static_cast<Ball&>(ball);
        UserPlayer & PlayerObject = static_cast<UserPlayer&>(Player);
        
        updateBall(ballObject, PlayerObject);

        if (sf::Keyboard::isKeyPressed(PlayerObject.getKey().SPACE))//if Player kicked the ball
            ballObject.kick(PlayerObject.getSideOfPlayer());
    }

    void computerPlayerCollidBall(GameObject& computerPlayer, GameObject& ball) {

        Ball& ballObject = static_cast<Ball&>(ball);
        ComputerPlayer& computerObject = static_cast<ComputerPlayer&>(computerPlayer);

        updateBall(ballObject,computerObject);

        if (!computerObject.getPower()->powerIsActive())
            ballObject.kick(false);

    }

    void ballCollidWithGoalBack(GameObject& ball , GameObject& goalBack) {

        Ball& ballObject = dynamic_cast<Ball&>(ball);
        GoalBack& goalObject = dynamic_cast<GoalBack&>(goalBack);

        (goalObject.getGoalSide()) ? ScoreBoard::getInstance().updateScore(1, 0) : ScoreBoard::getInstance().updateScore(0, 1);
        
        ScoreBoard::getInstance().setGoalSign();
        SoundControl::getInstance().getGoalSound().play();

        ballObject.getPower()->setPowerIsActive(false);
        ballObject.reset();
    }

    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function

    void ballColliedPlayer(GameObject& ball,
        GameObject& Player)
    {
        PlayerCollidBall(Player, ball);
    }
   
    void GoalBackCollidWithBall(GameObject& goalBack, GameObject& ball) {

        ballCollidWithGoalBack(ball, goalBack);
    }
    
    void BallCollidComputerPlayer(GameObject& ball, GameObject& computerPlayer) {

        computerPlayerCollidBall(computerPlayer,ball);

    }

    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(UserPlayer), typeid(Ball))] = &PlayerCollidBall;
        phm[Key(typeid(Ball), typeid(GoalBack))] = &ballCollidWithGoalBack;
        phm[Key(typeid(Ball), typeid(UserPlayer))] = &ballColliedPlayer;
        phm[Key(typeid(GoalBack), typeid(Ball))] = &GoalBackCollidWithBall;
        phm[Key(typeid(ComputerPlayer), typeid(Ball))] = &computerPlayerCollidBall;
        phm[Key(typeid(Ball), typeid(ComputerPlayer))] = &BallCollidComputerPlayer;
        //----------------------------------------------------------------------
        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (phf)
    {
        phf(object1, object2);
    }
    
}
