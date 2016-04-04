#pragma once
#include "Engine\Controller.h"

#include <vector>
#include <memory>
#include <map>
using std::vector;
using std::weak_ptr;
using std::map;

class FuseController :
	public Controller
{
public:
	FuseController();
	virtual ~FuseController();

	virtual void Init();
	virtual void Update(Uint32 timeDelta);

	vector<Vector2d> m_points;
	weak_ptr<GameObject> m_fire;

	void Reset();

	// in seconds
	float m_burnTime;
private:
	float m_totalLength;
	float m_timeElapsed;
	map<float, int> m_indexes;
	
};

