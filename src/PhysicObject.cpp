#include "PhysicObject.hpp"

#include "CONSTANT.hpp"
#include "Log.hpp"
#include "Utils.hpp"

PhysicObject::PhysicObject()
    : can_move_right_(true)
    , can_move_left_(true)
    , can_jump_(true)
    , is_ground_(false)
    , is_running_(false)
    , is_disabled_jump_(false)
    , move_speed_(0)
    , jump_height_(0)
    , num_foot_touch_(0)
{}

void PhysicObject::update()
{
    is_ground_ = getFootContact() > 0;
    can_jump_ = getBody()->GetLinearVelocity().y >= 0;
    is_running_ = false;
}

void PhysicObject::createBody(const int x, const int y, const int width, const int height)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = Utils::pixelToMeter(b2Vec2(x + width * 0.5f, y + height * 0.5f));
    bodyDef.fixedRotation = true;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body_ = PhysicWorld::Instance().getWorld()->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(Utils::pixelToMeter(width) * 0.5f, Utils::pixelToMeter(height) * 0.5f);

    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 1;
    fixture_ = body_->CreateFixture(&fixtureDef);

    createPolygonSensor(
        b2Vec2(0, height * 0.5),
        width - 0.5,
        1,
        ContactCategory::CAT_FOOT_SENSOR,
        ContactMask::MASK_FOOT_SENSOR);
}

void PhysicObject::changeFootContact(int n)
{
    num_foot_touch_ += n;
}

void PhysicObject::moveRight()
{
    if (!canMoveRight()) {
        return;
    }

    if (isOnGround()) {
        is_running_ = true;
    }

    float speedDifference = Utils::pixelToMeter(move_speed_) - body_->GetLinearVelocity().x;
    b2Vec2 impulse{body_->GetMass() * speedDifference, 0};
    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
}

void PhysicObject::moveLeft()
{
    if (!canMoveLeft()) {
        return;
    }

    if (isOnGround()) {
        is_running_ = true;
    }

    float speedDifference = Utils::pixelToMeter(-move_speed_) - body_->GetLinearVelocity().x;
    b2Vec2 impulse{body_->GetMass() * speedDifference, 0};
    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
}

void PhysicObject::jump() const
{
    if (is_disabled_jump_) {
        return;
    }

    if (!canJump()) {
        return;
    }

    if (!isOnGround()) {
        return;
    }

    float timeToJumpPeak = sqrt(2 * Utils::pixelToMeter(jump_height_) / GRAVITY);

    float velocity = Utils::pixelToMeter(jump_height_) / timeToJumpPeak;
    b2Vec2 impulse = body_->GetMass() * std::pow(velocity, 2) * b2Vec2(0, -1);

    body_->ApplyLinearImpulse(impulse, body_->GetWorldCenter(), true);
}

b2Body* PhysicObject::getBody() const
{
    return body_;
}

b2Vec2 PhysicObject::getPosition() const
{
    return Utils::meterToPixel(body_->GetPosition());
}

float PhysicObject::getAngle() const
{
    return Utils::degToRad(body_->GetAngle());
}

int PhysicObject::getFootContact() const
{
    return num_foot_touch_;
}

bool PhysicObject::isOnGround() const
{
    return is_ground_;
}

void PhysicObject::setMoveRight(bool can_move_right)
{
    can_move_right_ = can_move_right;
}

void PhysicObject::setMoveLeft(bool can_move_left)
{
    can_move_left_ = can_move_left;
}

bool PhysicObject::isRunning() const
{
    return is_running_;
}

bool PhysicObject::canMoveRight() const
{
    return can_move_right_;
}

bool PhysicObject::canMoveLeft() const
{
    return can_move_left_;
}

bool PhysicObject::canJump() const
{
    return can_jump_;
}

bool PhysicObject::isDisableJump() const
{
    return is_disabled_jump_;
}

void PhysicObject::setFilterData(ContactCategory category, ContactMask mask) const
{
    if (fixture_ == nullptr) {
        return;
    }

    b2Filter filter;
    filter.categoryBits = category;
    filter.maskBits = mask;
    fixture_->SetFilterData(filter);
}

b2Fixture* PhysicObject::createPolygonSensor(
    const b2Vec2& position,
    int width,
    int height,
    ContactCategory category,
    ContactMask mask) const
{
    b2PolygonShape polygon;
    polygon.SetAsBox(
        Utils::pixelToMeter(width * 0.5),
        Utils::pixelToMeter(height * 0.5),
        Utils::pixelToMeter(position),
        0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = category;
    fixtureDef.filter.maskBits = mask;
    return getBody()->CreateFixture(&fixtureDef);
}

b2Fixture* PhysicObject::createCircleSensor(
    const b2Vec2& position,
    const int radius,
    const ContactCategory category,
    const ContactMask mask) const
{
    b2CircleShape circle;
    circle.m_p = Utils::pixelToMeter(position);
    circle.m_radius = Utils::pixelToMeter(radius);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = category;
    fixtureDef.filter.maskBits = mask;

    return getBody()->CreateFixture(&fixtureDef);
}
