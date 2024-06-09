#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "gameObject/Player.h"
#include "gameObject/Ball.h"
#include "gameObject/Goal.h"


namespace // anonymous namespace — the standard way to make function "static"
{



    // primary collision-processing functions
    void playerCollidBall(GameObject& player,
        GameObject& ball)
    {

        Ball & ballObject = dynamic_cast<Ball&>(ball);
        Player & playerObject = dynamic_cast<Player&>(player);

        float kickStrength = 500.0f; // עוצמת הבעיטה
        float kickVerticalBoost = -400.0f; // עוצמת הבעיטה האנכית

        sf::Vector2f direction = ballObject.getPosition() - playerObject.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // נרמול הכיוון
       
        sf::Vector2f currVelocity = ballObject.getVelocity();



        if (sf::Keyboard::isKeyPressed(playerObject.getKey().SPACE))//if player kicked the ball
        {
            // עדכון מהירות הכדור בעקבות הבעיטה
            currVelocity += direction * kickStrength;
            currVelocity.y += kickVerticalBoost; // הוספת כוח בעיטה אנכי כדי לגרום לכדור לקפוץ

        }
        else
        {

            const float gravity = 980.0f;  // כוח המשיכה בפיקסלים לשנייה בריבוע
            const float restitution = 0.8f;  // מקדם ההתנגשות
            float dotProduct = currVelocity.x * direction.x + currVelocity.y * direction.y;

            if (dotProduct < 0) { // Ensure the ball is moving towards the player
                sf::Vector2f reflection = 2.0f * dotProduct * direction;
                currVelocity -= reflection * restitution;
            }
        }        
     
        ballObject.setBallVelocity(currVelocity);

        std::cout << "player and ball collision!\n";
    }

    void playerCollidPlayer(GameObject& player1,
        GameObject& player2)
    {                                                              
        std::cout << "Player1 and Player2 collision!\n";
        //system("cls");
    }

    void ballCollidGoal(GameObject& ball,
        GameObject& goal)
    {

        std::cout << "Ball and Goal collision!\n";
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
    void playerColliedPlayer(GameObject& player2,
        GameObject& player1)
    {
        playerCollidPlayer(player1, player2);
    }
    void GoalColliedBall(GameObject& goal,
        GameObject& ball)
    {
        ballCollidGoal(ball, goal);
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
