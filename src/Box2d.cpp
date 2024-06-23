
#include "Box2d.h"

Box2d::Box2d():m_world(b2Vec2(0.f, GRAVITY))
{

    //-------------------------ground-----------------------//

    // Create the ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(900.f / SCALE, 720.f / SCALE);
    b2Body* groundBody = m_world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(900.f / SCALE, 10.f / SCALE);
    groundBody->CreateFixture(&groundBox, 0.f);

    // Create the ground rectangle shape for rendering
    sf::RectangleShape ground(sf::Vector2f(1800.f, 20.f));
    ground.setFillColor(sf::Color::Green);
    ground.setOrigin(900.f, 10.f);
    ground.setPosition(900.f, 720.f);
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
    leftWallBodyDef.position.Set(30.f / SCALE, 500.f / SCALE);
    b2Body* leftWallBody = m_world.CreateBody(&leftWallBodyDef);
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(10.f / SCALE, 500.f / SCALE);
    leftWallBody->CreateFixture(&leftWallBox, 0.f);

    // Create the left wall rectangle shape for rendering
    sf::RectangleShape leftWall(sf::Vector2f(20.f, 1013.f));
    leftWall.setFillColor(sf::Color::Blue);
    leftWall.setOrigin(10.f, 500.f);
    leftWall.setPosition(30.f, 500.f);
    m_leftWall = leftWall;

    //-------------------------------------------right Wall---------------------------//

    // Create the right wall
    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set(1800.f / SCALE, 500.f / SCALE);
    b2Body* rightWallBody = m_world.CreateBody(&rightWallBodyDef);
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(10.f / SCALE, 500.f / SCALE);
    rightWallBody->CreateFixture(&rightWallBox, 0.f);

    // Create the right wall rectangle shape for rendering
    sf::RectangleShape rightWall(sf::Vector2f(20.f, 1013.f));
    rightWall.setFillColor(sf::Color::Yellow);
    rightWall.setOrigin(10.f, 500.f);
    rightWall.setPosition(1800.f, 500.f);
    m_rightWall = rightWall;
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
}

Box2d::~Box2d()
{


}