/*
File name: Euler.cpp
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 21.12.2018
Date last modified: 13.1.2019
*/

#include "ode_solver/Euler.h"

namespace ODE {

Euler::Euler():
    OdeSolver()
{
}

Euler::~Euler()
{
}

Eigen::VectorXd Euler::updateFunction()
{
  Eigen::VectorXd x = this->solution_.back().segment(0,n_);
  return  this->stepSize_ *  this->F_(this->currentTime_,x);;
}


} /* namespace ODE */
