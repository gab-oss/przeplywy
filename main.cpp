
#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
#include <climits>

#include "Graph.h"

int main(int argc, char** argv)
{

	Graph * graph;
	std::vector<Result> res;

	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
  std::chrono::duration<double> time_span;


	if (argc > 1 && isdigit(*(argv[1]))) {
			int vtMax = atoi(argv[1]); //maksymalna liczba wierzcholkow w sumie

			for (int i = vtMax; i > 0; --i) {
				graph = new Graph(vtMax, vtMax, vtMax, vtMax, vtMax);
				graph->generate();
				graph->printGraph();

				t1 = std::chrono::high_resolution_clock::now();
				graph->maxFlow();
				t2 = std::chrono::high_resolution_clock::now();
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
				res.push_back(Result(i, time_span));

				graph->printFlow();
				graph->printResult();
				std::cout << "--------------------------" << i << std::endl;
				delete graph;
		}

		std::cout << std::setw(10) << "liczba wierzcholkow" << std::setw(10) << "czas [s]" << std::endl;

		for (auto r = res.begin(); r != res.end(); ++r) {
				std::cout << std::setw(10) << r->getIteration() << std::setw(20)
				<< std::fixed << std::setprecision(7) << (r->getElapsed()).count() << std::endl;
		}
	}

	else if (argc > 1) {
		graph = new Graph();
		graph->load(argv[1]);
		graph->printGraph();
		graph->maxFlow();
		graph->printFlow();
		graph->printResult();
	}

	else {
		std::cout << "Podaj sciezke do pliku z grafem albo liczbe wierzcholkow" << std::endl;
	}
}
