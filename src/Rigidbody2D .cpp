#include "Rigidbody2D .h"

Rigidbody2D::Rigidbody2D(SDL_Rect rect,float mass)
{
	m_rect = rect;
	m_mass = mass;
}
void Rigidbody2D::SetGravity(float newGravity)
{
	m_gravity = newGravity;
}
void Rigidbody2D::applyForce(Vec2 f) {
	m_ax += f.x / m_mass;
	m_ay += f.y / m_mass;
}
void Rigidbody2D::update(float dt) {
	// atualiza a velocidade com a aceleração da gravidade
	m_vy += m_gravity * dt;

	m_vx += m_ax * dt;
	m_vy += m_ay * dt;
	m_rect.x += (int) m_vx * dt;
	m_rect.y += (int) m_vy * dt;

	m_ax = 0.0f;
	m_ay = 0.0f;
}
bool Rigidbody2D::checkCollision(Rigidbody2D& other) {
	return SDL_HasIntersection(&m_rect, &other.m_rect);
}
SDL_Rect Rigidbody2D::GetBox(){
	return m_rect;
}
void Rigidbody2D::resetParams(SDL_Rect rect,float mass){
	m_rect = rect;
	m_mass = mass;
	m_vx = 0;
	m_vy = 0;
	m_ax = 0;
	m_ay = 0;
}
