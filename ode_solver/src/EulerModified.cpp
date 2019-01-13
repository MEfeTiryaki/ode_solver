/*
File name: EulerModified.cpp
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 21.12.2018
Date last modified: 13.1.2019
*/

#include "ode_solver/EulerModified.h"

namespace ODE {

EulerModified::EulerModified():
    OdeSolver()
{

}

EulerModified::~EulerModified()
{
}

Eigen::VectorXd EulerModified::updateFunction()
{
  Eigen::VectorXd x = this->solution_.back().segment(0,n_);
  return  this->stepSize_ *  this->F_(this->currentTime_,x);;
}

} /* namespace ODE */
