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
    void playerCollidBall(GameObject& player,
        GameObject& ball)
    {

        Ball & ballObject = dynamic_cast<Ball&>(ball);
        Player & playerObject = dynamic_cast<Player&>(player);

        if (playerObject.getAura()){

            playerObject.setAura(false);            
        }

        float kickStrength = 500.0f; // עוצמת הבעיטה
        float kickVerticalBoost = -400.0f; // עוצמת הבעיטה האנכית

        sf::Vector2f direction = ballObject.getPosition() - playerObject.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // נרמול הכיוון
       
        sf::Vector2f currVelocity = ballObject.getVelocity();

        const float gravity = 980.0f;  // כוח המשיכה בפיקסלים לשנייה בריבוע
        const float restitution = 0.8f;  // מקדם ההתנגשות
        float dotProduct = currVelocity.x * direction.x + currVelocity.y * direction.y;

        if (sf::Keyboard::isKeyPressed(playerObject.getKey().SPACE))//if player kicked the ball
        {
            // עדכון מהירות הכדור בעקבות הבעיטה
            currVelocity += direction * kickStrength;
            currVelocity.y += kickVerticalBoost; // הוספת כוח בעיטה אנכי כדי לגרום לכדור לקפוץ

        }
        else
        {

            if (dotProduct < 0) { // Ensure the ball is moving towards the player
                sf::Vector2f reflection = 2.0f * dotProduct * direction;
                currVelocity -= reflection * restitution;
            }
        }        
     
        ballObject.setBallVelocity(currVelocity);

        //std::cout << "player and ball collision!\n";
    }

    void playerCollidPlayer(GameObject& player1,
        GameObject& player2)
    {                                                              
        //std::cout << "Player1 and Player2 collision!\n";
        //system("cls");
    }

    void ballCollidGoalTop(GameObject& ball,
        GameObject& goal)
    {

        Ball& ballObject = dynamic_cast<Ball&>(ball);
        GoalTop& goalObject = dynamic_cast<GoalTop&>(goal);

        auto scoreBar = goalObject.getSprite().getGlobalBounds();
        auto ballVelocity = ballObject.getVelocity();;

        const float restitution = 0.8f;

        float ballLeft = ballObject.getPosition().x - ballObject.getRadius();
        float ballRight = ballObject.getPosition().x + ballObject.getRadius();
        float ballTop = ballObject.getPosition().y - ballObject.getRadius();
        float ballBottom = ballObject.getPosition().y + ballObject.getRadius();

        if (ballRight >= scoreBar.left && ballLeft <= scoreBar.left + scoreBar.width &&
            ballBottom >= scoreBar.top && ballTop <= scoreBar.top + scoreBar.height) {

            if (ballTop < scoreBar.top) {
                // Ball hit the top
                ballObject.setPosition(sf::Vector2f(ballObject.getPosition().x, scoreBar.top - ballObject.getRadius()));
                ballVelocity.y = -ballObject.getVelocity().y * restitution;
            }
            else if (ballBottom > scoreBar.top + scoreBar.height) {
                // Ball hit the bottom
                ballObject.setPosition(sf::Vector2f(ballObject.getPosition().x, scoreBar.top + scoreBar.height + ballObject.getRadius()));
                ballVelocity.y = -ballVelocity.y * restitution;
            }
            else if (ballLeft < scoreBar.left) {
                // Ball hit the left side
                ballObject.setPosition(sf::Vector2f(scoreBar.left - ballObject.getRadius(), ballObject.getPosition().y));
                ballVelocity.x = -ballVelocity.x * restitution;
            }
            else if (ballRight > scoreBar.left + scoreBar.width) {
                // Ball hit the right side
                ballObject.setPosition(sf::Vector2f(scoreBar.left + scoreBar.width + ballObject.getRadius(), ballObject.getPosition().y));
                ballVelocity.x = -ballVelocity.x * restitution;
            }
        }

        ballObject.setBallVelocity(ballVelocity);

    }

    void ballCollidWithGoalBack(GameObject& ball , GameObject& goalBack) {

        Ball& ballObject = dynamic_cast<Ball&>(ball);
        GoalBack& goalObject = dynamic_cast<GoalBack&>(goalBack);

        goalObject.setIfGoal(true);

        ballObject.setBallVelocity(sf::Vector2f(5.f, -10.f));
        ballObject.setPosition(sf::Vector2f(900.0f, 494.0f));

    }

    void computerPlayerCollidBall(GameObject& computerPlayer, GameObject& ball) {

        
        Ball& ballObject = dynamic_cast<Ball&>(ball);
        ComputerPlayer& computerObject = dynamic_cast<ComputerPlayer&>(computerPlayer);

        sf::Vector2 velocity = ballObject.getVelocity();

        computerObject.movePlayer(sf::Vector2f(160, 126), 7,10);

        const float kickStrength = 200.0f; // עוצמת הבעיטה
        const float kickVerticalBoost = -100.0f; // עוצמת הבעיטה האנכית

        
        // כיוון הבעיטה (ממרכז השחקן למרכז הכדור)
        sf::Vector2f direction = computerObject.getRivalGoal() - ballObject.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // נרמול הכיוון

        // עדכון מהירות הכדור בעקבות הבעיטה
        velocity += direction * kickStrength;
        velocity.y += kickVerticalBoost; // הוספת כוח בעיטה אנכי כדי לגרום לכדור לקפוץ

        ballObject.setBallVelocity(velocity);

    }

    /*void handleUnnecessaryCollision(GameObject& side, GameObject& back) {}*/

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

        //----------------------------------------------------------------------
        phm[Key(typeid(ComputerPlayer), typeid(Player))] = &playerCollidPlayer;
        phm[Key(typeid(ComputerPlayer), typeid(Ball))] = &computerPlayerCollidBall;
        //----------------------------------------------------------------------

        phm[Key(typeid(Ball), typeid(Player))] = &ballColliedPlayer;
        phm[Key(typeid(GoalTop), typeid(Ball))] = &GoalTopColliedBall;
        phm[Key(typeid(GoalBack), typeid(Ball))] = &GoalBackCollidWithBall;
        phm[Key(typeid(Player), typeid(Player))] = &playerCollidPlayer;
       

        //----------------------------------------------------------------------
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
