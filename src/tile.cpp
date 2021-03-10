#include "tile.h"
#include <cmath>

Node::Node() {
	this->global = INFINITY;
	this->local = INFINITY;
	this->parent = nullptr;
	this->coords.x = 0;
	this->coords.y = 0;
	this->visited = false;
	this->canPassThrough = true;
}

void Node::visit(Node *end, std::vector<Node *> *toVisit) {
	for (int i = 0; i < this->neighbours.size(); i++) {
		if (this->updateWith(this->neighbours[i], end)) {
			(*toVisit).push_back(this->neighbours[i]);
		}
	}
	this->visited = true;
	(*toVisit).erase((*toVisit).begin());
}

void Node::addNeighbour(Node *neighbour) {
	this->neighbours.push_back(neighbour);
}

void Node::setPosition(Coordinates nCoords) {
	this->coords = nCoords;
}

Coordinates Node::getPosition() {
	return this->coords;
}

Node *Node::getParent() {
	return this->parent;
}

void Node::setStart(Node *end) {
	this->local = 0;
	this->global = this->distanceFrom(end);
}

void Node::setPassThrough(bool nCanPassThrough) {
	this->canPassThrough = nCanPassThrough;
}

bool Node::getPassThrough() {
	return this->canPassThrough;
}

bool Node::updateWith(Node *other, Node *end) {
	float newLocal = this->local + this->distanceFrom(other);
	if (newLocal < other->local && other->canPassThrough) {
		other->parent = this;
		other->local = newLocal;
		other->global = other->distanceFrom(end) + other->local;
		if (!this->visited) {
			return true;
		}
	}
	return false;
}

float Node::distanceFrom(Node *other) {
	// uses pythagorean theorem to calculate distance between two nodes
	return std::sqrt((other->coords.x - this->coords.x) * (other->coords.x - this->coords.x) + (other->coords.y - this->coords.y) * (other->coords.y - this->coords.y));
}
void quickSortNodes(std::vector<Node *> &nodes, int lowIndex, int highIndex) {
	if (lowIndex < highIndex) {
		Node *pivot = nodes[highIndex - 1];
		int nextSwap = lowIndex;
		for (int i = lowIndex; i < highIndex; i++) {
			if (nodes[i]->global <= pivot->global) {
				Node *nodeToSwap = nodes[i];
				nodes[i] = nodes[nextSwap];
				nodes[nextSwap] = nodeToSwap;
				nextSwap++;
			}
		}
		quickSortNodes(nodes, lowIndex, nextSwap - 1);
		quickSortNodes(nodes, nextSwap + 1, highIndex);
	}
}