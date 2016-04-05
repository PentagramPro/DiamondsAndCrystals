#include "ParticlesController.h"



ParticlesController::ParticlesController()
{
	m_life = 500;
	m_controllerLife = 500;
	m_acceleration = 20;
	m_burstSize = 15;
	m_velocity = 40;
	m_velocityNoise = 0.8f;
	m_spawnRate = 0;
	m_assetName = "Particle.png";
}


ParticlesController::~ParticlesController()
{
}

void ParticlesController::Init()
{
	
	m_spawnCapacitor = 0;
	for (int i = 0; i < m_burstSize; i++)
	{
		
		SpawnParticle();
	}
}

void ParticlesController::Burst(int size)
{
	for (int i = 0; i < size; i++)
		SpawnParticle();
}

void ParticlesController::SpawnParticle()
{
	GameObject& obj = Object()->CreateObject("Particle", 0, 0, m_assetName.c_str(), NULL);
	obj.m_localPosition.x = -obj.Width() / 2.0f;
	obj.m_localPosition.y = -obj.Height() / 2.0f;
	obj.SetBlendingMode(SDL_BLENDMODE_ADD);
	Particle p;
	p.object = obj.GetSharedPtr();
	p.life = m_life;

	float velNoiseRate = (rand() / (float)RAND_MAX - 0.5f)*m_velocityNoise;

	p.velocity.x = rand() / (float)RAND_MAX - 0.5f;
	p.velocity.y = rand() / (float)RAND_MAX - 0.5f;
	p.velocity.Normalize();
	p.velocity *= m_velocity*(1 + velNoiseRate);
	m_particles.push_back(p);
}

void ParticlesController::Update(Uint32 timeDelta)
{
	if (m_controllerLife >= 0)
	{
		if (m_controllerLife < (int)timeDelta)
		{
			Object()->Destroy();
			return;
		}
		m_controllerLife -= timeDelta;
	}
	
	float fraction = timeDelta / 1000.0f;
	
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

	if (m_spawnRate > 0)
	{
		m_spawnCapacitor += m_spawnRate*fraction;
		int tospawn = (int)m_spawnCapacitor;
		for (int i = 0; i < tospawn; i++)
		{
			SpawnParticle();
		}
		m_spawnCapacitor -= tospawn;
	}
}


