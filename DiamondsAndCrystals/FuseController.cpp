#include "FuseController.h"
#include "ParticlesController.h"


FuseController::FuseController()
{
	m_burnTime = 60;

}


FuseController::~FuseController()
{
}

void FuseController::Init()
{
	
	auto fx = std::make_shared<ParticlesController>();
	fx->m_burstSize = 0;
	fx->m_spawnRate = 10;
	fx->m_velocity = 15;
	fx->m_assetName = "Fire.png";
	fx->m_controllerLife = -1;
	m_fire = Object()->CreateObject("Explosion", 0,0, NULL, fx).GetSharedPtr();
	
	Reset();
	
}

void FuseController::Update(Uint32 timeDelta)
{
	if (m_totalLength <= 0)
		return;

	float delta = timeDelta / 1000.0;

	m_timeElapsed += delta;
	if (m_timeElapsed > m_burnTime)
		return;

	float phase = m_timeElapsed / m_burnTime;
	float phaseLen = m_totalLength*phase;

	int index = 0;
	float indexLen = 0;
	for (auto& i : m_indexes)
	{
		if (i.first > phaseLen)
			break;
		
		index = i.second;
		indexLen = i.first;
	}

	if (index >= m_points.size()-1)
		return;

	float vectorPhase = (phaseLen - indexLen) / Vector2d::Distance(m_points[index], m_points[index + 1]);
	Vector2d pos = m_points[index] + (m_points[index + 1] - m_points[index])*vectorPhase;
	//printf("Fuse:\t%d\t%d\n", (int)pos.x, (int)pos.y);
	m_fire.lock()->m_localPosition = pos;
}

void FuseController::Reset()
{
	m_totalLength = 0;
	m_timeElapsed = 0;
	m_indexes.clear();
	if (m_points.size() < 2)
		return;


	for (int i = 1; i < m_points.size(); i++)
	{
		float len = Vector2d::Distance(m_points[i], m_points[i - 1]);
		m_totalLength += len;
		m_indexes[m_totalLength] = i;
	}
}
