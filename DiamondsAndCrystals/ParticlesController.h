#pragma once
#include "Engine\Controller.h"
#include "Engine\GameObject.h"
#include <memory>
#include <list>
#include <string>

using std::weak_ptr;
using std::list;
using std::string;

struct Particle {
	Vector2d velocity;
	weak_ptr<GameObject> object;
	Uint32 life;
};

class ParticlesController :
	public Controller
{
public:
	ParticlesController();
	virtual ~ParticlesController();

	virtual void Init();
	virtual void Update(Uint32 timeDelta);

	float m_velocity;
	float m_acceleration;
	float m_velocityNoise;


	// in ms
	int m_life;
	int m_controllerLife;

	int m_burstSize;
	float m_spawnRate;
	string m_assetName;
	void Burst(int size);
protected:
	list<Particle> m_particles;
	float m_spawnCapacitor;

	void SpawnParticle();
};

