#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
	Edge();

	Edge(int v, float flow, float capacity);

	~Edge();

	void setV(int v);

	int getV() const;

	void setFlow(float flow);

	float getFlow() const;

	void setCapacity(float capacity);

	float getCapacity() const;

	void setResCapacity(float resCapacity);

	float getResCapacity() const;

private:
	int v;
	float flow;
	float capacity;
	float resCapacity;
};

#endif
