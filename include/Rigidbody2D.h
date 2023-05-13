#ifndef RIGIDBODY2D_H
#define RIGIDBODY2D_H


#include <SDL.h>
#include <Vec2.h>
#include <Engine.h>
class Rigidbody2D {
public:
    Rigidbody2D(SDL_Rect rect, float mass);

    void applyForce(Vec2 f);

    Vec2 GetVelocity();

    void update(float dt);

    bool checkCollision(Rigidbody2D& other);
    bool checkCollision(Rigidbody2D others[],int length);

    SDL_Rect& GetBox();

    void SetGravity(float newGravity);

    void SetVelocity(Vec2 v);
    void SetRect(SDL_Rect rect);

    void resetParams(SDL_Rect rect,float mass);

    void collide(Rigidbody2D other);
private:
	float m_gravity = 10;
    SDL_Rect m_rect; // position and size
    float m_vx = 0.0f, m_vy = 0.0f; // velocity
    float m_ax = 0.0f, m_ay = 0.0f; // acceleration
    float m_mass;
};

#endif // RIGIDBODY2D_H
