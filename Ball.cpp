#include "Ball.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Window/Keyboard.hpp>
using namespace std;

Ball::Ball(){
	m_ball.setRadius(8.0f);
	m_ball.setFillColor({255,255,255});
	m_ball.setOutlineThickness(1.0f);
	m_ball.setOutlineColor(Color::White);
	m_ball.setPosition(400,300);
	
	velocity = 6.f;
	m_speed.y = velocity; paso_limites = false;
	m_speed.x = 0;
	
	bordes_pelota.loadFromFile("rebote.wav");
	sonido_b.setBuffer(bordes_pelota);
}

void Ball::Update(){
	Play();
	auto p = m_ball.getPosition();
	paso_limites = false;
	
	if(p.x<0 or p.x + 16> 800){
		m_speed.x = -m_speed.x;
		sonido_b.play();
		
	}
	if(p.y - 8 < 0){
		m_speed.y = -m_speed.y;
		sonido_b.play();
	}
	if(p.y> 600){
		m_ball.setPosition(800 / 2.f,600 / 2.f);
		ball_moving = false; paso_limites = true;
		m_speed.x = 0;
	}
	

	
}

void Ball::Rebotar(const FloatRect& playerBounds){ /// Este rebotar se utiliza para paleta-pelota
	/// Invierte la direcci�n vertical de la pelota
	m_speed.y = -m_speed.y;
	
	/// Calcula la posici�n relativa de la pelota en relaci�n con la paleta
	float relativeIntersect = (m_ball.getPosition().x + m_ball.getRadius()) - (playerBounds.left + playerBounds.width / 2);
	
	/// Ajusta el cambio en la direcci�n horizontal en funci�n de la posici�n relativa
	m_speed.x = relativeIntersect / (playerBounds.width / 2) * MAX_SPEED_X;
}
void Ball::Rebotar(){ /// Este rebotar se utiliza para pelota - ladrillo 
	m_speed.y = -m_speed.y;
	m_speed.x -= rand()%100 / 50.f;
}

void Ball::IncrementarVelocidad(int speed){
	velocity+=speed;
	m_speed.y = velocity;
	
}

void Ball::Play(){

	if(ball_moving){
		m_ball.move(m_speed);
	}
}

void Ball::setBallMoving(bool moving){
	ball_moving = moving;
}

int Ball::ball_speed(){
	return velocity;
}

bool Ball::PasoLimites(){
	return paso_limites;
}
