#ifndef RESULT_HPP
#define RESULT_HPP

#include <ratio>
#include <chrono>

class Result {
  private:
    int iteration;
    std::chrono::duration<double> elapsed;
  public:
    Result(int i, std::chrono::duration<double> e) : iteration(i), elapsed(e) {}
    void setIteration(int i){iteration = i;}
    void setElapsed(std::chrono::duration<double> e){elapsed = e;}
    int getIteration(){return iteration;}
    std::chrono::duration<double> getElapsed(){return elapsed;}
};

#endif
