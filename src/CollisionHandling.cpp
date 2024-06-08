#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "Player.h"
#include "Ball.h"
#include "Goal.h"

namespace // anonymous namespace — the standard way to make function "static"
{

    // primary collision-processing functions
    void playerCollidBall(GameObject& /*spaceShip*/,
        GameObject& /*asteroid*/)
    {
        // To get the actual types and use them:
        // SpaceShip& ship = dynamic_cast<SpaceShip&>(spaceShip);
        // Asteroid&  ast  = dynamic_cast<Asteroid&>(asteroid);
        // or:
        // SpaceShip& ship = static_cast<SpaceShip&>(spaceShip);
        // Asteroid&  ast  = static_cast<Asteroid&>(asteroid);

        std::cout << "player and ball collision!\n";
    }

    void playerCollidPlayer(GameObject& /*spaceShip*/,
        GameObject& /*spaceStation*/)
    {
        //std::cout << "Player and Player collision!\n";
        //system("cls");
    }

    void ballCollidGoal(GameObject& /*asteroid*/,
        GameObject& /*spaceStation*/)
    {
        std::cout << "Ball and Goal collision!\n";
    }


    //...

    // secondary collision-processing functions that just
    // implement symmetry: swap the parameters and call a
    // primary function
    void ballColliedPlayer(GameObject& asteroid,
        GameObject& spaceShip)
    {
        playerCollidBall(spaceShip, asteroid);
    }
    void playerColliedPlayer(GameObject& spaceStation,
        GameObject& spaceShip)
    {
        playerCollidPlayer(spaceShip, spaceStation);
    }
    void GoalColliedBall(GameObject& spaceStation,
        GameObject& asteroid)
    {
        ballCollidGoal(asteroid, spaceStation);
    }
    //...

    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    // typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    // std::unordered_map is better, but it requires defining good hash function for pair
    using HitMap = std::map<Key, HitFunctionPtr>;

    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(Player), typeid(Ball))] = &playerCollidBall;//shipAsteroid;
        phm[Key(typeid(Player), typeid(Player))] = &playerCollidPlayer;//shipStation;
        phm[Key(typeid(Ball), typeid(Goal))] = &ballCollidGoal;//asteroidStation;

        phm[Key(typeid(Ball), typeid(Player))] = &ballColliedPlayer;//shipAsteroid;
        phm[Key(typeid(Player), typeid(Player))] = &playerCollidPlayer;//shipStation;
        phm[Key(typeid(Goal), typeid(Ball))] = &GoalColliedBall;//asteroidStation;
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
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
