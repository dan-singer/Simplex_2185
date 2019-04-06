#ifndef _OCTREE_H
#define _OCTREE_H

#include "Definitions.h"

namespace Simplex
{
	// Small struct representing a bounding box that can detect if another boundingbox is completely contained in this box
	struct BoundingBox {
		vector3 min;
		vector3 max;

		// Default constructor
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


	/*
		Octree Class used for spacial optimization.
		Based upon this tutorial: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/introduction-to-octrees-r3529/
	*/
	class Octree
	{
	private:
		BoundingBox m_region;
		std::vector<uint> m_entities;
		Octree** m_childNodes = new Octree*[8]{};
		const int MIN_SIZE = 1;
		byte m_activeNodes = 0; // bitmask indicated which child nodes are actively used
		Octree* m_parent;
		// Attaches and creates an Octree node to this Octree
		Octree* CreateNode(BoundingBox region, std::vector<uint> entities);
	public:


		Octree();
		Octree(BoundingBox region);
		Octree(BoundingBox region, std::vector<uint> entities);
		// The actual building of the tree happens here
		void BuildTree(int depth, int maxDepth);
		// Display the entire octree
		void Display();
		// Display one octant of this tree by index
		void Display(uint targetIndex);
		// Displays this octant but not its children
		void DisplayOctantOnly();
		// Returns the number of octants in this tree (Recursively)
		uint GetOctantCount();
		// Checks for collisions between all entities in this tree
		void CheckCollisions(std::vector<uint> parentObjs = std::vector<uint>());
		byte GetActiveNodes() { return m_activeNodes; }


		~Octree();

	};
}

#endif
