/*
File name: pendulumScope_test.cpp
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 21.12.2018
Date last modified: 13.1.2019
*/
//! @example

#include <iostream>
#include <vector>
#include <Eigen/Core>
#include "ode_solver/RungeKutta.h"
#include "ode_solver/Simulator.h"
#include "plotgui/ScopeGui.h"
#include <boost/bind.hpp>

using namespace ODE;
using namespace std;
//using namespace std::placeholders;

Eigen::VectorXd pendulumEquation(double time, Eigen::VectorXd x){
  Eigen::MatrixXd A = Eigen::MatrixXd::Zero(2,2);
  A << 0, 1, -9.81*1 , -1.0 ;
  return A*x ;

}

int main() {
  // Scope
  int argc;
  char **argv;
  QApplication app(argc, argv);
  ScopeGui gui;

  // Solver
  RungeKutta* solver = new RungeKutta();
  solver->setDynamics(boost::bind(&pendulumEquation, _1, _2));

  double maxTime = 10.0;
  int stepNumber = 1000;
  double stepSize = 0.01;
  Eigen::Vector2d initValue;
  initValue << 0.5, 0;
  // Simulator
  Simulator sim;
  sim.initilize(solver);
  sim.setRealTimeFactor(1);

  sim.start(initValue, maxTime, stepNumber);
  //sim.start(initValue, stepSize);
  gui.setScopeNumber(2);
  std::vector<std::string> legendNames(0);
  legendNames.push_back("position");
  gui.setXAxisRange(5);
  gui.setYAxis(-0.5,0.5);
  gui.addTimeSignal(boost::bind(&Simulator::getBuffer,&sim,-1));
  gui.addStopFunction(boost::bind(&Simulator::setStop,&sim, _1));
  gui.addClearFunction(boost::bind(&Simulator::clearBuffer,&sim));
  gui.addGraph(0, boost::bind(&Simulator::getBuffer,&sim, 0));
  gui.legend(0,legendNames);
  gui.addGraph(1, boost::bind(&Simulator::getBuffer,&sim, 1));
  legendNames[0] = "velocity" ;
  gui.legend(1,legendNames);

  gui.show();

  return app.exec();
}
