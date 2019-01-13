/*
File name: pendulum_test.cpp
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 21.12.2018
Date last modified: 13.1.2019
*/
//! @example


#include <iostream>
#include <vector>
#include <Eigen/Core>
#include "ode_solver/OdeSolver.h"
#include "ode_solver/RungeKutta.h"
#include "plotgui/PlotGui.h"
#include <boost/bind.hpp>

using namespace ODE;
using namespace std;
//using namespace std::placeholders;

Eigen::VectorXd pendulumEquation(double time, Eigen::VectorXd x){
  Eigen::MatrixXd A = Eigen::MatrixXd(2,2);
  A << 0, 1, -9.81*1 , -1.0 ;
  return A*x ;

}

int main() {

  RungeKutta solver = RungeKutta();
  solver.setDynamics(boost::bind(&pendulumEquation, _1, _2));

  double maxTime = 10.0;
  int stepNumber = 1000;
  Eigen::Vector2d initValue;
  initValue << 0.6, -0.2;

  solver.solve(initValue, maxTime, stepNumber);
  std::vector<Eigen::VectorXd> solution = solver.getSolution();
  Eigen::VectorXd t = solution.back();
  //cout<< solver.getSolution() <<endl;

  // Scope
  int argc;
  char **argv;
  QApplication app(argc, argv);
  PlotGui gui;

  gui.subplot(2,1,0);
  gui.plot(t,solution[0]);
  gui.fillBelow(QColor(0,0,255,75));
  gui.yLabel("Angle(rad)");
  std::vector<std::string> lName(1);
  lName[0] ="pendulum angle";
  gui.legend(lName);
  gui.subplot(2,1,1);
  gui.plot(t,solution[1],Qt::red);
  gui.fillBelow(QColor(255,0,0,75));
  gui.xLabel("Time(s)");
  gui.yLabel("Angular Velocity(rad/s)");
  lName[0] ="pendulum angular velocity" ;
  gui.legend(lName);
  gui.show();
  return app.exec();
}
