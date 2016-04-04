#include "ParticlesController.h"



ParticlesController::ParticlesController()
{
	m_life = 500;
	m_controllerLife = 500;
	m_acceleration = 20;
	m_burstSize = 15;
	m_velocity = 40;
	m_velocityNoise = 0.8;
}


ParticlesController::~ParticlesController()
{
}

void ParticlesController::Init()
{
	

	for (int i = 0; i < m_burstSize; i++)
	{
		GameObject& obj = Object()->CreateObject("Particle", 0, 0, "Particle.png", NULL);
		obj.m_localPosition.x = -obj.Width() / 2;
		obj.m_localPosition.y = -obj.Height() / 2;
		obj.SetBlendingMode(SDL_BLENDMODE_ADD);
		Particle p;
		p.object = obj.GetSharedPtr();
		p.life = m_life;
		
		float velNoiseRate = (rand() / (float)RAND_MAX-0.5)*m_velocityNoise;

		p.velocity.x = rand() / (float)RAND_MAX-0.5;
		p.velocity.y = rand() / (float)RAND_MAX-0.5;
		p.velocity.Normalize();
		p.velocity *= m_velocity*(1+velNoiseRate);
		m_particles.push_back(p); 

	}
}

void ParticlesController::Update(Uint32 timeDelta)
{
	if (m_controllerLife < timeDelta)
	{
		Object()->Destroy();
		return;
	}
	m_controllerLife -= timeDelta;
	float fraction = timeDelta / 1000.0;
	list<Particle>::iterator it = m_particles.begin();
	while(it!=m_particles.end())
	{
		if (it->life < timeDelta)
		{
			it->object.lock()->Destroy();
			it = m_particles.erase(it);
			continue;
		}

		it->life -= timeDelta;
		
		it->object.lock()->m_localPosition += it->velocity*fraction;
		it->object.lock()->m_alpha = it->life / (float)m_life;
		Vector2d norm = it->velocity;
		norm.Normalize();
		it->velocity += norm*fraction*m_acceleration;
		it++;
	}
}
