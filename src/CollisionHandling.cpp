#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "gameObject/Player.h"
#include "gameObject/Ball.h"
#include "gameObject/Goal.h"
#include "gameObject/ComputerPlayer.h"

#include "gameObject/GoalSide.h"
#include "gameObject/GoalBack.h"
#include "gameObject/GoalTop.h"
#include "Keyboard.h"


namespace // anonymous namespace — the standard way to make function "static"
{

    // primary collision-processing functions
    void playerCollidBall(GameObject& player, GameObject& ball)
    {

        Ball & ballObject = dynamic_cast<Ball&>(ball);
        Player & playerObject = dynamic_cast<Player&>(player);

        if (playerObject.getAura()){

            playerObject.setAura(false);            
        }

        if (sf::Keyboard::isKeyPressed(playerObject.getKey().SPACE))//if player kicked the ball
        {

            ballObject.kick(playerObject.getSideOfPlayer());
            
        }
       
    }

    void ballCollidGoalTop(GameObject& ball, GameObject& goal)
    {

    }

    void ballCollidWithGoalBack(GameObject& ball , GameObject& goalBack) {

        Ball& ballObject = dynamic_cast<Ball&>(ball);
        GoalBack& goalObject = dynamic_cast<GoalBack&>(goalBack);

        goalObject.setIfGoal(true);

        //ballObject.setBallVelocity(sf::Vector2f(5.f, -10.f));
        ballObject.setPosition(sf::Vector2f(900.0f, 100.0f));

    }

    void computerPlayerCollidBall(GameObject& computerPlayer, GameObject& ball) {

        Ball& ballObject = dynamic_cast<Ball&>(ball);
        ComputerPlayer& computerObject = dynamic_cast<ComputerPlayer&>(computerPlayer);

        ballObject.kick(false);

    }

    void playerCollidPlayer(GameObject& player1, GameObject& player2)
    {       
        
    }

    //...

    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function

    void ballColliedPlayer(GameObject& ball,
        GameObject& player)
    {
        playerCollidBall(player, ball);
    }
   
    void GoalTopColliedBall(GameObject& goal,
        GameObject& ball)
    {
        ballCollidGoalTop(ball, goal);
    }
    void GoalBackCollidWithBall(GameObject& goalBack, GameObject& ball) {

        ballCollidWithGoalBack(ball, goalBack);
    }
    
    void BallCollidComputerPlayer(GameObject& ball, GameObject& computerPlayer) {

        computerPlayerCollidBall(computerPlayer,ball);

    }
    /*
     void playerColliedPlayer(GameObject& player2,
        GameObject& player1)
    {
        playerCollidPlayer(player1, player2);
    }*/

    //...

    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Player), typeid(Ball))] = &playerCollidBall;
        phm[Key(typeid(Player), typeid(Player))] = &playerCollidPlayer;
        phm[Key(typeid(Ball), typeid(GoalTop))] = &ballCollidGoalTop;
        phm[Key(typeid(Ball), typeid(GoalBack))] = &ballCollidWithGoalBack;

        phm[Key(typeid(Ball), typeid(Player))] = &ballColliedPlayer;
        phm[Key(typeid(GoalTop), typeid(Ball))] = &GoalTopColliedBall;
        phm[Key(typeid(GoalBack), typeid(Ball))] = &GoalBackCollidWithBall;
       
        //--------------------ComputerPlayer Collision--------------------------
        phm[Key(typeid(ComputerPlayer), typeid(Player))] = &playerCollidPlayer;
        phm[Key(typeid(ComputerPlayer), typeid(Ball))] = &computerPlayerCollidBall;
        phm[Key(typeid(Player), typeid(ComputerPlayer))] = &playerCollidPlayer;
        phm[Key(typeid(Ball), typeid(ComputerPlayer))] = &BallCollidComputerPlayer;
        //----------------------------------------------------------------------

        //...
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
