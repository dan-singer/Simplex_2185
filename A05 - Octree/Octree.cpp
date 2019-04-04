#include "Octree.h"

using namespace Simplex;

Octree::Octree(BoundingBox region, std::vector<uint> entities)
{
	m_region = region;
	m_entities = entities;
}

void Octree::BuildTree()
{
	// Terminate if we're a leaf node
	if (m_entities.size() <= 1)
	{
		return;
	}

	vector3 dimensions = m_region.max - m_region.min;
	if (dimensions == vector3(0, 0, 0)) 
	{
		// TODO call FindEnclosingCube
		vector3 dimensions = m_region.max - m_region.min;
	}

	if (dimensions.x <= MIN_SIZE && dimensions.y <= MIN_SIZE && dimensions.z <= MIN_SIZE)
	{
		return;
	}

	vector3 half = dimensions / 2.0f;
	vector3 center = m_region.min + half;

	// Create the subdivided regions 
	BoundingBox octants[8];
	octants[0] = BoundingBox(m_region.min, center);
	octants[1] = BoundingBox(vector3(center.x, m_region.min.y, m_region.min.z),  vector3(m_region.max.x, center.y, center.z));
	octants[2] = BoundingBox(vector3(center.x, m_region.min.y, center.z),  vector3(m_region.max.x, center.y, m_region.max.z));
	octants[3] = BoundingBox(vector3(m_region.min.x, m_region.min.y, center.z),  vector3(center.x, center.y, m_region.max.z));
	octants[4] = BoundingBox(vector3(m_region.min.x, center.y, m_region.min.z),  vector3(center.x, m_region.max.y, center.z));
	octants[5] = BoundingBox(vector3(center.x, center.y, m_region.min.z),  vector3(m_region.max.x, m_region.max.y, center.z));
	octants[6] = BoundingBox(center, m_region.max);
	octants[7] = BoundingBox(vector3(m_region.min.x, center.y, center.z),  vector3(center.x, m_region.max.y, m_region.max.z));

	// This will contain each of the objects which fit within each octant
	std::vector<std::vector<uint>> octList;
	for (int i = 0; i < 8; ++i)
	{
		octList.push_back(std::vector<uint>());
	}

	// This will contain all of the objects which got moved down the tree and can be deslisted from this node
	std::vector<uint> delist;

	MyEntityManager* manager = MyEntityManager::GetInstance();
	for (int i = 0; i < m_entities.size(); ++i)
	{
		MyEntity* entity = manager->GetEntity(m_entities[i]);
		for (int a = 0; a < 8; ++a)
		{
			if (octants[a].CompletelyContains(BoundingBox(entity->GetRigidBody()->GetMinGlobal(), entity->GetRigidBody()->GetMaxGlobal())))
			{
				octList[a].push_back(m_entities[i]);
				delist.push_back(m_entities[i]);
				break;
			}
		}
	}

	// Remove objects that fit cleanly in one of the octants. Everything else remains part of this node because it must be intersecting
	for (uint id : delist)
	{
		octList.erase(std::remove(octList.begin(), octList.end(), id));
	}

	// TODO Make child nodes where there are items in the bounding region
}

Octree::Octree()
{
	
}

Octree::Octree(BoundingBox region)
{
	m_region = region;
}


Octree::~Octree()
{
}
