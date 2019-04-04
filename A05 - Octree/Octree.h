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
				other.min.x >= min.x && other.max.x <= min.x &&
				other.min.y >= min.x && other.max.y <= min.y &&
				other.min.z >= min.x && other.max.z <= min.y
				);
		}
	};

	class Octree
	{
	private:
		BoundingBox m_region;
		std::vector<uint> m_entities;
		Octree* m_childNodes = new Octree[8];
		byte m_activeNodes = 0; // bitmask indicated which child nodes are actively used
		const int MIN_SIZE = 1;
		Octree* m_parent;

		// Private constructor
		Octree(BoundingBox region, std::vector<uint> entities);

		void BuildTree();
	public:
		Octree();
		Octree(BoundingBox region);
		~Octree();
	};
}

#endif
