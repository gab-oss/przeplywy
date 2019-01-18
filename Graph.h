#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Result.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <climits>
#include <queue>
#include <list>
#include <algorithm>
#include <random>
#include <iomanip>

class Graph {
public:
	Graph();
	Graph(int capMax, int effMax, int pMax, int plMax, int vtMax);
	~Graph();
	void load(char * filename);
	void addSource(int v, float eff);
	void addValve(int v, float capacity);
	void addSink(int v);
	void addEdge(int v1, int v2, float capacity);

	void initFlow();
	float maxFlow();
	void splitValves();
	void addRevEdges();
	void printFlow();
	void generate();
	void printGraph();
	void printResult();

private:
	int mainSource;
	int mainSink;
	int vCount;
	int eCount;
	std::vector<std::list<Edge>> vertices;
	std::vector<int> sources;
	std::vector<int> valves;
	std::vector<int> sinks;
	std::vector<float> valveCap;
	std::vector<float> sourceEff;
	std::vector<std::pair<int, float>> result;

	int CAP_MAX;
	int EFF_MAX;
	int P_MAX;
	int PL_MAX; //maksymalna dlugosc sciezki
	int VT_MAX; //liczba wierzcholkow danego typu
};

#endif
