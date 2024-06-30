
#include "Box2d.h"

Box2d::Box2d():m_world(b2Vec2(0.f, GRAVITY))
{

    //-------------------------ground-----------------------//

    // Create the ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(900.f / SCALE, 825.f / SCALE);
    b2Body* groundBody = m_world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(900.f / SCALE, 10.f / SCALE);
    groundBody->CreateFixture(&groundBox, 0.f);

    // Create the ground rectangle shape for rendering
    sf::RectangleShape ground(sf::Vector2f(1800.f, 20.f));
    ground.setFillColor(sf::Color::Green);
    ground.setOrigin(900.f, 10.f);
    ground.setPosition(900.f, 825.f);
    m_ground = ground;

    //-------------------------------------------ceiling---------------------------//

    // Create the ceiling
    b2BodyDef ceilingBodyDef;
    ceilingBodyDef.position.Set(900.f / SCALE, 30.f / SCALE);
    b2Body* ceilingBody = m_world.CreateBody(&ceilingBodyDef);
    b2PolygonShape ceilingBox;
    ceilingBox.SetAsBox(900.f / SCALE, 10.f / SCALE);
    ceilingBody->CreateFixture(&ceilingBox, 0.f);

    // Create the ceiling rectangle shape for rendering
    sf::RectangleShape ceiling(sf::Vector2f(1800.f, 20.f));
    ceiling.setFillColor(sf::Color::Red);
    ceiling.setOrigin(900.f, 10.f);
    ceiling.setPosition(900.f, 30.f);
    m_ceiling = ceiling;

    //-------------------------------------------left Wall---------------------------//

    // Create the left wall
    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set(10.f / SCALE, 500.f / SCALE);
    b2Body* leftWallBody = m_world.CreateBody(&leftWallBodyDef);
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(10.f / SCALE, 500.f / SCALE);
    leftWallBody->CreateFixture(&leftWallBox, 0.f);

    // Create the left wall rectangle shape for rendering
    sf::RectangleShape leftWall(sf::Vector2f(20.f, 1013.f));
    leftWall.setFillColor(sf::Color::Blue);
    leftWall.setOrigin(10.f, 500.f);
    leftWall.setPosition(10.f, 500.f);
    m_leftWall = leftWall;

    //-------------------------------------------right Wall---------------------------//

    // Create the right wall
    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set(1790.f / SCALE, 500.f / SCALE);
    b2Body* rightWallBody = m_world.CreateBody(&rightWallBodyDef);
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(10.f / SCALE, 500.f / SCALE);
    rightWallBody->CreateFixture(&rightWallBox, 0.f);

    // Create the right wall rectangle shape for rendering
    sf::RectangleShape rightWall(sf::Vector2f(20.f, 1013.f));
    rightWall.setFillColor(sf::Color::Yellow);
    rightWall.setOrigin(10.f, 500.f);
    rightWall.setPosition(1790.f, 500.f);
    m_rightWall = rightWall;

    //-------------------------------------------top goal left---------------------------//

    // Create the top goal
    b2BodyDef topGoalBodyDef;
    topGoalBodyDef.position.Set(70.f / SCALE, 580.f / SCALE);
    b2Body* topGoalBody = m_world.CreateBody(&topGoalBodyDef);
    b2PolygonShape topGoalBox;
    topGoalBox.SetAsBox(75.f / SCALE, 5.f / SCALE); // Box2D uses half-widths and half-heights
    topGoalBody->CreateFixture(&topGoalBox, 0.f);

    // Create the ceiling rectangle shape for rendering
    sf::RectangleShape topGoal(sf::Vector2f(150.f, 10.f)); // Full width = 2 * half-width
    topGoal.setFillColor(sf::Color::Red);
    topGoal.setOrigin(75.f, 5.f); // Origin at the center
    topGoal.setPosition(70.f, 580.f); // Position using Box2D coordinates scaled to SFML
    m_topGoalLeft = topGoal;


    //-------------------------------------------top goal right---------------------------//

    // Create the top goal on the right side
    b2BodyDef topGoalBodyDef2;
    topGoalBodyDef2.position.Set(1800.f / SCALE, 580.f / SCALE); // Position in Box2D world coordinates
    b2Body* topGoalBody2 = m_world.CreateBody(&topGoalBodyDef2);

    // Define the shape of the top goal (adjust dimensions as needed)
    b2PolygonShape topGoalBox2;
    topGoalBox2.SetAsBox(150.f / SCALE, 5.f / SCALE); // SetAsBox takes half-width and half-height

    // Create fixture for the top goal body
    topGoalBody2->CreateFixture(&topGoalBox2, 0.f); // Density set to 0 for static bodies

    // Create the rectangle shape for rendering
    sf::RectangleShape topGoal2(sf::Vector2f(150.f, 10.f)); // Adjust size as needed for rendering
    topGoal2.setFillColor(sf::Color::Black);
    topGoal2.setOrigin(150.f, 5.f); // Origin should match half-width and half-height for correct positioning
    topGoal2.setPosition(1800.f, 580.f); // Position in screen coordinates
    m_topGoalRight = topGoal2;

}


//get world
b2World* Box2d::getBox2dWorld() {

    return &m_world;
}

void Box2d::draw(sf::RenderWindow& window)const {

    window.draw(m_ground);
    window.draw(m_ceiling);
    window.draw(m_leftWall);
    window.draw(m_rightWall);
    window.draw(m_topGoalLeft); 
    window.draw(m_topGoalRight);
}

//create player in box3d
b2Body* Box2d::createPlayer(sf::Vector2f basePosition) {

    // Create the player
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(basePosition.x / SCALE, basePosition.y / SCALE);
    b2Body* body = m_world.CreateBody(&playerBodyDef);

    // Prevent the player from rotating
    body->SetFixedRotation(true);

    b2PolygonShape playerBox;
    playerBox.SetAsBox(30.f / SCALE, 40.f / SCALE);
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerBox;
    playerFixtureDef.density = 10.f;
    playerFixtureDef.friction = 0.3f;
    playerFixtureDef.restitution = 0.4f; // Ensure there's no bounce
    body->CreateFixture(&playerFixtureDef);

    // Set the gravity scale for the player
    body->SetGravityScale(PLAYER_GRAVITY_SCALE);

    return body;
}

//create ball in box3d
b2Body* Box2d::createBall(sf::Vector2f basePosition) {

    // Create the ball
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(basePosition.x / SCALE, basePosition.y / SCALE);
    b2Body* body = m_world.CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = 25.0f / SCALE;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.7f;
    body->CreateFixture(&fixtureDef);

    return body;
}

Box2d::~Box2d()
{


}