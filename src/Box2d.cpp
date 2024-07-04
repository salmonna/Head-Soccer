
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
    //-------------------------------------------ceiling---------------------------//
    // Create the ceiling
    b2BodyDef ceilingBodyDef;
    ceilingBodyDef.position.Set(900.f / SCALE, 30.f / SCALE);
    b2Body* ceilingBody = m_world.CreateBody(&ceilingBodyDef);
    b2PolygonShape ceilingBox;
    ceilingBox.SetAsBox(900.f / SCALE, 10.f / SCALE);
    ceilingBody->CreateFixture(&ceilingBox, 0.f);
    //-------------------------------------------left Wall---------------------------//
    // Create the left wall
    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set(10.f / SCALE, 500.f / SCALE);
    b2Body* leftWallBody = m_world.CreateBody(&leftWallBodyDef);
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(10.f / SCALE, 500.f / SCALE);
    leftWallBody->CreateFixture(&leftWallBox, 0.f);
    //-------------------------------------------right Wall---------------------------//
    // Create the right wall
    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set(1790.f / SCALE, 500.f / SCALE);
    b2Body* rightWallBody = m_world.CreateBody(&rightWallBodyDef);
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(10.f / SCALE, 500.f / SCALE);
    rightWallBody->CreateFixture(&rightWallBox, 0.f);
    //-------------------------------------------top goal left---------------------------//
    // Create the top goal
    b2BodyDef topGoalBodyDef;
    topGoalBodyDef.position.Set(70.f / SCALE, 590.f / SCALE);
    b2Body* topGoalBody = m_world.CreateBody(&topGoalBodyDef);
    b2PolygonShape topGoalBox;
    topGoalBox.SetAsBox(75.f / SCALE, 10.f / SCALE); // Box2D uses half-widths and half-heights
    topGoalBody->CreateFixture(&topGoalBox, 0.f);
    //-------------------------------------------top goal right---------------------------//
    // Create the top goal on the right side
    b2BodyDef topGoalBodyDef2;
    topGoalBodyDef2.position.Set(1800.f / SCALE, 590.f / SCALE); // Position in Box2D world coordinates
    b2Body* topGoalBody2 = m_world.CreateBody(&topGoalBodyDef2);
    // Define the shape of the top goal (adjust dimensions as needed)
    b2PolygonShape topGoalBox2;
    topGoalBox2.SetAsBox(150.f / SCALE, 10.f / SCALE); // SetAsBox takes half-width and half-height
    // Create fixture for the top goal body
    topGoalBody2->CreateFixture(&topGoalBox2, 0.f); // Density set to 0 for static bodies
}

//create Player in box3d
b2Body* Box2d::createPlayer(sf::Vector2f basePosition) {

    // Create the Player
    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.position.Set(basePosition.x / SCALE, basePosition.y / SCALE);
    b2Body* body = m_world.CreateBody(&PlayerBodyDef);

    // Prevent the Player from rotating
    body->SetFixedRotation(true);
    b2PolygonShape PlayerBox;
    PlayerBox.SetAsBox(30.f / SCALE, 40.f / SCALE);
    b2FixtureDef PlayerFixtureDef;
    PlayerFixtureDef.shape = &PlayerBox;
    PlayerFixtureDef.density = 10.f;
    PlayerFixtureDef.friction = 0.3f;
    body->CreateFixture(&PlayerFixtureDef);
    // Set the gravity scale for the Player
    body->SetGravityScale(Player_GRAVITY_SCALE);

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
    fixtureDef.density = 0.4f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.7f;
    body->CreateFixture(&fixtureDef);

    return body;
}

//create goal back in box3d
b2Body* Box2d::createGoalBack(sf::Vector2f basePosition) {
    //-------------------------------------------goal Back---------------------------//

    // Create the goal back
    b2BodyDef goalBackBodyDef;
    goalBackBodyDef.position.Set(basePosition.x / SCALE, basePosition.y / SCALE);
    b2Body* goalBackBody = m_world.CreateBody(&goalBackBodyDef);
    b2PolygonShape goalBackBox;
    goalBackBox.SetAsBox(10.f / SCALE, 100.f / SCALE);
    goalBackBody->CreateFixture(&goalBackBox, 0.f);

    return goalBackBody;
}

//get world
b2World* Box2d::getBox2dWorld() {

    return &m_world;
}

void Box2d::step() {
    float timeStep = 1.f / 60.f;
    int32 velocityIterations = 6;
    int32 positionIterations = 3;
    m_world.Step(timeStep, velocityIterations, positionIterations);
}

Box2d::~Box2d()
{
}