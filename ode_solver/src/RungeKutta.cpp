 /*
  File name: RungeKutta.cpp
  Author: Mehmet Efe Tiryaki
  E-mail: m.efetiryaki@gmail.com
  Date created: 21.12.2018
  Date last modified: 13.1.2019
  */

#include "ode_solver/RungeKutta.h"

namespace ODE {

RungeKutta::RungeKutta():
    OdeSolver()
{
  // TODO Auto-generated constructor stub

  //std::cout << "Runge kutta works!!" << std::endl;
}

RungeKutta::~RungeKutta()
{
  // TODO Auto-generated destructor stub
}

Eigen::VectorXd RungeKutta::updateFunction()
{
  //std::cout << "Runge kutta works!!" << std::endl;
  k1_.resize(this->n_);
  k2_.resize(this->n_);
  k3_.resize(this->n_);
  k4_.resize(this->n_);
  Eigen::VectorXd x = this->solution_.back().segment(0,n_);
  k1_ = this->stepSize_ *  this->F_(this->currentTime_,x);
  k2_ = this->stepSize_ *  this->F_(this->currentTime_+ this->stepSize_/2 , x + 0.5 *k1_);
  k3_ = this->stepSize_ *  this->F_(this->currentTime_+ this->stepSize_/2 , x + 0.5 *k2_);
  k4_ = this->stepSize_ *  this->F_(this->currentTime_+ this->stepSize_ , x + k3_);
  return (k1_ + 2 *k2_ + 2 *k3_ + k4_)/6;
}


} /* namespace ODE */
