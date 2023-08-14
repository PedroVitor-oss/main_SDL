#include "Rigidbody2D.h"

void Rigidbody2D::SetVelocity(Vec2 v)
{
	m_vx = v.x;
	m_vy = v.y;
}
Vec2 Rigidbody2D::GetVelocity(){
	return {m_vx,m_vy};
}
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
	bool isColider = SDL_HasIntersection(&m_rect, &other.m_rect);
	if (isColider){
		collide(other);
	}
	return isColider;
}
bool Rigidbody2D::checkCollision(Rigidbody2D others[],int length)
{
	bool collider = false;
	for(int i =0;i<length;i++){
		Rigidbody2D other = others[i];
		bool isColider = SDL_HasIntersection(&m_rect, &other.m_rect);
		if (isColider){
				collider = true;
			collide(other);

		}
	}
	return collider;
}
SDL_Rect& Rigidbody2D::GetBox(){
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

void Rigidbody2D::collide(Rigidbody2D other){
	SDL_Rect rectOther = other.GetBox();
	int deltaX = m_rect.x + m_rect.w / 2 - (rectOther.x + rectOther.w / 2);
    int deltaY = m_rect.y + m_rect.h / 2 - (rectOther.y + rectOther.h / 2);
    int intersectX = (abs(deltaX) - (m_rect.w + rectOther.w) / 2) / 2;
    int intersectY = (abs(deltaY) - (m_rect.h + rectOther.h) / 2) / 2;

    if (intersectX > intersectY) {
			m_vx = 0;
        if (deltaX > 0) {
            m_rect.x = rectOther.x + rectOther.w;
        } else {
            m_rect.x = rectOther.x - m_rect.w;
        }
    } else {
		m_vy = 0;
		float dax = m_mass * m_gravity;
		if(m_vx<-2 || m_vx>2)
		{
			if(m_vx>0)
			{
				m_vx-= dax;
				m_vx = m_vx<0? 0:m_vx;

			}else{
				m_vx+= dax;
				m_vx = m_vx>0? 0:m_vx;
			}
		}else{
			m_vx = 0;
		}
        if (deltaY > 0) {
            m_rect.y = rectOther.y + rectOther.h;
        } else {
            m_rect.y = rectOther.y - m_rect.h;
        }
    }
}
void Rigidbody2D::SetRect(SDL_Rect rect){
	m_rect = rect;
}
