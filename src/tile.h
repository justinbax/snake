#ifndef NODE_H
#define NODE_H

#include <vector>

struct Coordinates {
	int x, y;
}; // struct Coordinates

class Node {
	friend void quickSortNodes(std::vector<Node *> &nodes, int lowIndex, int highIndex);
	public:
		Node();
		void visit(Node *end, std::vector<Node *> *toVisit);
		void addNeighbour(Node *neighbour);
		void setPosition(Coordinates nCoords);
		Coordinates getPosition();
		Node *getParent();
		void setStart(Node *end);
		void setPassThrough(bool nCanPassThrough);
		bool getPassThrough();
	private:
		bool updateWith(Node *other, Node *end);
		float distanceFrom(Node *other);
		Node *parent;
		std::vector<Node *> neighbours;
		float local, global;
		Coordinates coords;
		bool visited, canPassThrough;
}; // class Node

#endif // ifndef NODE_H