#ifndef RIGIDBODY2D _H
#define RIGIDBODY2D _H

#include <SDL.h>
#include <Vec2.h>
class Rigidbody2D {
public:
    Rigidbody2D(SDL_Rect rect, float mass);

    void applyForce(Vec2 f);

    void update(float dt);

    bool checkCollision(Rigidbody2D& other);

    SDL_Rect GetBox();

    void SetGravity(float newGravity);
    void resetParams(SDL_Rect rect,float mass);
private:
	float m_gravity = 10;
    SDL_Rect m_rect; // position and size
    float m_vx = 0.0f, m_vy = 0.0f; // velocity
    float m_ax = 0.0f, m_ay = 0.0f; // acceleration
    float m_mass;
};

#endif // RIGIDBODY2D _H
