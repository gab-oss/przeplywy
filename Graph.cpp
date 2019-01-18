
#include "Graph.h"

Graph::Graph() {

	CAP_MAX = 1000;
	EFF_MAX = 1000;
	P_MAX = 1000;
	PL_MAX = 1000; //maksymalna dlugosc sciezki
	VT_MAX = 1000;

	mainSource = 0;
	mainSink = 1;
	vertices = std::vector<std::list<Edge>>(VT_MAX * 4 + 2);
	vCount = 2;
	eCount = 0;


	valveCap = std::vector<float>(VT_MAX * 3 + 2);
	sourceEff = std::vector<float>(VT_MAX + 2);
}

Graph::Graph(int capMax, int effMax, int pMax, int plMax, int vtMax) {

  CAP_MAX = capMax;
	EFF_MAX = effMax;
	P_MAX = pMax;
	PL_MAX = plMax; //maksymalna dlugosc sciezki
	VT_MAX = vtMax;

	mainSource = 0;
	mainSink = 1;
	vertices = std::vector<std::list<Edge>>(VT_MAX * 6 + 2);
	vCount = 2;
	eCount = 0;


	valveCap = std::vector<float>(VT_MAX * 5 + 2);
	sourceEff = std::vector<float>(VT_MAX * 2 + 3);
}

Graph::~Graph() {

	//for (auto e = vertices[0].begin(); e != vertices[0].end(); ++e) {

//	}

	//for (int i = 2; i < vCount; ++i) {
//		delete &vertices;
	//}

}

void Graph::addSource(int v, float eff) {

	sources.push_back(v);
	addEdge(mainSource, v, eff);
	sourceEff[v] = eff;
	++vCount;
}

void Graph::addValve(int v, float capacity) {

	valves.push_back(v);
	valveCap[v] = capacity;
	++vCount;
}

void Graph::addSink(int v) {

	sinks.push_back(v);
	addEdge(v, mainSink, 0);
	++vCount;
}

void Graph::addEdge(int v1, int v2, float capacity) {

//	Edge * e = new Edge(v2, 0, capacity);
//	vertices[v1].push_back(*e);
	vertices[v1].push_back(Edge(v2, 0, capacity));
	++eCount;

	auto it = std::find(sinks.begin(), sinks.end(), v2);
	if (it != sinks.end())
		vertices[v2].begin()->setCapacity(vertices[v2].begin()->getCapacity() + capacity);
}


void Graph::printFlow() {

	float flow;

	for (int i = 0; i < vCount; i++) {
		for (auto e = vertices[i].begin(); e != vertices[i].end(); ++e) {
			flow = e->getFlow();
			if (flow > 0) {
				std::cout << i << " -> " << e->getV() << " " << std::setprecision(2) << std::fixed << flow << " : "
					<< std::setprecision(2) << std::fixed << e->getCapacity() << std::endl;
			}
		}
	}
}

void Graph::printGraph() {

	for (int i = 0; i < vCount; i++) {
		for (auto e = vertices[i].begin(); e != vertices[i].end(); ++e) {
				std::cout << i << " -> " << e->getV() << " cap: "
					<< std::setprecision(2) << std::fixed << e->getCapacity() << std::endl;
		}
	}
}

void Graph::splitValves() {

	for (auto valve = valves.begin(); valve != valves.end(); ++valve) {
		vertices[vCount].splice(vertices[vCount].end(), vertices[*valve]);
		addEdge(*valve, vCount, valveCap[*valve]);
		++vCount;
	}
}

void Graph::initFlow() {
	float efficiency;
	float c_sum = 0.0;
	float c_new;
	int source;

	for (auto it = sources.begin(); it != sources.end(); ++it) {
		source = *it;
		efficiency = sourceEff[*it];
		for (auto efs = vertices[source].begin(); efs != vertices[source].end(); ++efs) { //edge from source
			c_sum += efs->getCapacity();
		}
		for (auto efs = vertices[source].begin(); efs != vertices[source].end(); ++efs) { //edge from source
			c_new = (efficiency / c_sum) * efs->getCapacity();
			efs->setCapacity(c_new);
		}
		c_sum = 0;
	}
}

void Graph::load(char * filename) {
	std::ifstream myfile(filename);

	std::string line;
	int name;
	float num;

	int i = 0;
	int j = 0;

	while (getline(myfile, line)) {

		std::istringstream iss(line);

		if (line.length() == 0) {
			++i;
		}
		else {
			if (i == 0) {
				if (j == 0) { //czytaj zrodla
					while (iss >> name >> num)
						addSource(name, num);
					++j;
				}
				else if (j == 1) {
					while (iss >> name >> num)
						addValve(name, num);
					++j;
				}
				else {
					while (iss >> name) {
						addSink(name);
					}
				}
			}
			if (i == 1) {
				iss >> name;
				int v1 = name;

				while (iss >> name >> num) {
					addEdge(v1, name, num);
				}
			}
		}
	}

	CAP_MAX = vCount;
	EFF_MAX = vCount;
	P_MAX = vCount;
	PL_MAX = vCount; //maksymalna dlugosc sciezki
	VT_MAX = vCount;
}

void Graph::addRevEdges() {
	std::list<std::pair<int, int>> l;

	for (int v = 0; v < vCount; ++v) {
		for (auto e = vertices[v].begin(); e != vertices[v].end(); ++e) {
			int v2 = e->getV();

			for (auto e2 = vertices[v2].begin(); e2 != vertices[v2].end(); ++e2) {
				int vr = e2->getV();
				if (vr == v) {
					break;
				}

			}
			l.push_back(std::pair<int, int>(v2, v));
		}
	}

	for (auto p = l.begin(); p != l.end(); ++p) {
		addEdge(p->first, p->second, 0);
	}
}

float Graph::maxFlow() {

	splitValves();
	addRevEdges();
	initFlow();

	std::queue<int> q;
	std::vector<int> predec(vCount);
	std::vector<float> cfp(vCount);
	float cp;
	int u, v; //numery wierzcholkow
	bool pathFound = false;
	float fmax = 0;

	while (1) {

		for (int i = 0; i < vCount; ++i)
			predec[i] = -1;
		//predec[mainSource] = -2;

		cfp[mainSource] = (float)INT_MAX;

		while (!q.empty())
			q.pop();

		q.push(mainSource);

		while (!q.empty()) {
			pathFound = false;

			u = q.front();
			q.pop();

			std::list<Edge> edges = vertices[u];

			for (auto e = edges.begin(); e != edges.end(); ++e) {
				v = e->getV();
				cp = e->getCapacity() - e->getFlow();
				if (cp && predec[v] == -1) {
					predec[v] = u;
					if (cfp[u] < cp) {
						cfp[v] = cfp[u];
					}
					else {
						cfp[v] = cp;
					}

					if (v == mainSink) {
						pathFound = true;
						break;
					}
					else {
						q.push(v);
					}
				}
			}

			if (pathFound)
				break;
		}

		if (!pathFound)
			break;

		fmax += cfp[mainSink];

		for (v = mainSink; v != mainSource; v = u) {
			u = predec[v];

			for (auto e = vertices[u].begin(); e != vertices[u].end(); ++e) {
				int v2 = e->getV();

				if (v2 == v) {
					e->setFlow(e->getFlow() + cfp[mainSink]);
					break;
				}
			}

			for (auto e = vertices[u].begin(); e != vertices[u].end(); ++e) {
				int v2 = e->getV();

				if (v2 == u) {
					e->setFlow(e->getFlow() - cfp[mainSink]);
					break;
				}
			}

		}
	}

	float sum = 0;

	for (int i = 0; i < sinks.size(); ++i) {
		for (auto e = vertices[sinks[i]].begin(); e != vertices[sinks[i]].end(); ++e) {
			sum += e->getFlow();
		}
		result.push_back(std::pair<int, float>(sinks[i], sum));
		sum = 0;
	}
	return fmax;
}

void Graph::printResult(){
	for (auto it = result.begin(); it != result.end(); ++it) {
			std::cout << "wynik " << it->first << ": " << std::setprecision(2) << std::fixed << it->second << std::endl;
	}

	std::cout << std::setprecision(2) << std::fixed << "fmax = " << fmax << std::endl;
}

void Graph::generate() {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_real_distribution<float> lastSrcDist(2, 2 + VT_MAX - 0.01);
	int lastSource = (int)lastSrcDist(generator);

	std::uniform_real_distribution<float> lastValveDist(lastSource + 1, lastSource + VT_MAX + 0.99);
	int lastValve = (int)lastValveDist(generator);

	std::uniform_real_distribution<float> lastSinkDist(lastValve + 1, lastValve + VT_MAX + 0.99);
	int lastSink = (int)lastSinkDist(generator);

	std::uniform_real_distribution<float> srcEffDist(1, EFF_MAX);
	std::uniform_real_distribution<float> cpDist(1, CAP_MAX);

	for (int i = 2; i <= lastSource; ++i) {
		addSource(i, srcEffDist(generator));
	}

	for (int i = lastSource + 1; i <= lastValve; ++i) {
		addValve(i, cpDist(generator));
	}

	for (int i = lastValve + 1; i <= lastSink; ++i) {
		addSink(i);
	}


	std::uniform_real_distribution<float> pthsCountDist(1, P_MAX);
	int pathsCount = (int)pthsCountDist(generator);

	std::uniform_real_distribution<float> plDist(1, PL_MAX + 0.95);
	std::uniform_real_distribution<float> srcDist(2, lastSource + 0.95);
	std::uniform_real_distribution<float> vrtDist(lastSource + 1, lastSink + 0.95);
	std::uniform_real_distribution<float> snksDist(lastValve + 1, lastSink + 0.95);

	int v1, v2;
	int pathLength;
	bool edge_exists = false, toSink = false;

	for (int i = 0; i < pathsCount; ++i) { //generuj sciezki
		pathLength = (int)plDist(generator);
		v1 = (int)srcDist(generator);

		while (pathLength) {

			do {
				v2 = (int)vrtDist(generator);
			} while (v2 == v1);

			auto it = std::find(sinks.begin(), sinks.end(), v2);
			if (it != sinks.end())
				toSink = true;

			for (auto e = vertices[v1].begin(); e != vertices[v1].end(); ++e) {
				if (e->getV() == v2)
					edge_exists = true;
			}

			if (!edge_exists)
				addEdge(v1, v2, cpDist(generator));

			if (toSink) {
				toSink = false;
				edge_exists = false;
				break;
			}
			else {
				if (pathLength == 1) {
					int nextSink = snksDist(generator);
					for (auto e = vertices[v2].begin(); e != vertices[v2].end(); ++e) {
						if (e->getV() == nextSink)
							edge_exists = true;
					}
					if (!edge_exists)
						addEdge(v2, nextSink, cpDist(generator));
					toSink = false;
					edge_exists = false;
					break;
				}
			}

			v1 = v2;

			--pathLength;
			edge_exists = false;
			toSink = false;
		}
	}

	int src, sink;

	for (int i = 2; i < vCount; i++) {
		if (vertices[i].empty()) {

			sink = (int)snksDist(generator);
			addEdge(i, sink, cpDist(generator));

			if (i > lastSource) {
				src = (int)srcDist(generator);
				addEdge(src, i, cpDist(generator));
			}
		}
	}

	edge_exists = false;

	for (auto it = sinks.begin(); it != sinks.end(); ++it) {
		for (int i = 2; i < vCount; ++i) {
			for (auto e = vertices[i].begin(); e != vertices[i].end(); ++e) {

				if (e->getV() == *it)
					edge_exists = true;
			}
		}

		if (!edge_exists) {

			src = (int)srcDist(generator);
			addEdge(src, *it, cpDist(generator));
		}

		edge_exists = false;
	}
}
