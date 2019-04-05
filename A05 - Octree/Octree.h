#ifndef _OCTREE_H
#define _OCTREE_H

#include "Definitions.h"
#include "MyEntityManager.h"

/*
Octree Class used for spacial optimization
*/
namespace Simplex
{
	struct BoundingBox {
		vector3 min;
		vector3 max;
		BoundingBox()
		{

		}
		BoundingBox(vector3 a_min, vector3 a_max)
		{
			min = a_min;
			max = a_max;
		}

		bool CompletelyContains(BoundingBox other)
		{
			return (
				other.min.x >= min.x && other.max.x <= max.x &&
				other.min.y >= min.y && other.max.y <= max.y &&
				other.min.z >= min.z && other.max.z <= max.z
				);
		}
	};

	class Octree
	{
	public:
		BoundingBox m_region;
		std::vector<uint> m_entities;
		Octree** m_childNodes = new Octree*[8]{};
		byte m_activeNodes = 0; // bitmask indicated which child nodes are actively used
		const int MIN_SIZE = 1;
		Octree* m_parent;



		Octree* CreateNode(BoundingBox region, std::vector<uint> entities);
	public:
		Octree();
		Octree(BoundingBox region);
		Octree(BoundingBox region, std::vector<uint> entities);

		~Octree();
		void BuildTree();


		std::vector<std::pair<uint, uint>> GetIntersection(std::vector<uint> parentObjs);
	};
}

#endif