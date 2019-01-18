#include "Edge.h"

Edge::Edge()
{
}


Edge::~Edge()
{
}

Edge::Edge(int v, float flow, float capacity)
	: v(v), flow(flow), capacity(capacity) {
	resCapacity = capacity - flow;
}

void Edge::setV(int v) {
	this->v = v;
}

int Edge::getV() const {
	return v;
}

void Edge::setFlow(float flow) {
	this->flow = flow;
}

float Edge::getFlow() const {
	return flow;
}

void Edge::setCapacity(float capacity) {
	this->capacity = capacity;
}

float Edge::getCapacity() const {
	return capacity;
}

void Edge::setResCapacity(float resCapacity) {
	this->resCapacity = resCapacity;
}

float Edge::getResCapacity() const {
	return resCapacity;
}
