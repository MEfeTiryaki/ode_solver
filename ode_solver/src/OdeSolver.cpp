/*
 File name: OdeSolver.cpp
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 21.12.2018
 Date last modified: 13.1.2019
 */

#include "ode_solver/OdeSolver.h"
#include <unistd.h>

namespace ODE {

OdeSolver::OdeSolver()
    : currentTime_(0.0),
      stepSize_(0.0),
      maxTimeStep_(0),
      timeStep_(0.0),
      n_(0)
{

}

OdeSolver::~OdeSolver()
{
}



void OdeSolver::setDynamics(std::function<Eigen::VectorXd(double,Eigen::VectorXd)> f){
  F_ = f ;
}

void OdeSolver::initilize(Eigen::VectorXd initialValue, double maxTime, int stepNumber){
  maxTimeStep_ = stepNumber;
  stepSize_ = maxTime / stepNumber;
  currentTime_ = 0.0;
  n_ = initialValue.size();
  // initilize the solution vector
  solution_.push_back(Eigen::VectorXd::Zero(n_+1));
  solution_.back().segment(0,n_) = initialValue;

}

void OdeSolver::initilize(Eigen::VectorXd initialValue, double stepSize){
  maxTimeStep_ = std::numeric_limits<int>::max();
  stepSize_ = stepSize;
  currentTime_ = 0.0;
  n_ = initialValue.size();
  solution_.push_back(Eigen::VectorXd::Zero(n_+1));
  solution_.back().segment(0,n_) = initialValue;
}

void OdeSolver::solve(Eigen::VectorXd initialValue, double maxTime, int stepNumber)
{
  initilize( initialValue, maxTime, stepNumber);

  for (timeStep_ = 0; timeStep_ < maxTimeStep_-1; timeStep_++) {
    advance();
  }
}

void OdeSolver::advance(){
  Eigen::VectorXd newState = solution_.back();
  // set the new new current time
  currentTime_ = newState[n_] + stepSize_;
  newState[n_] = currentTime_ ;
  // update the state
  newState.segment(0,n_) = solution_.back().segment(0,n_) + updateFunction();
  solution_.push_back(newState);
}

void OdeSolver::clear(){
  Eigen::VectorXd temp = solution_.back();
  solution_.clear();
  solution_.push_back(temp);
}

Eigen::VectorXd OdeSolver::getState(){
  // TODO : later get rid of if to make it faster
  if(solution_.size()>0){
    return solution_.back();
  }else{
    std::cout << "\033[0;32m"
              << "Erro : solution is empty"
              << "\033[0m" << std::endl;
    return Eigen::VectorXd::Zero(0);
  }
}


std::vector<Eigen::VectorXd>  OdeSolver::getSolution()
{
  std::vector<Eigen::VectorXd> result;
  for(int i = 0; i<n_+1 ; i++){
    result.push_back(Eigen::VectorXd::Zero(solution_.size()));
    for(int j = 0; j<solution_.size();j++){
      result[i][j] = solution_[j][i];
    }
  }
  return result;
}

Eigen::VectorXd OdeSolver::updateFunction()
{
  return Eigen::VectorXd::Zero(1);
}
;

} /* namespace ODE */
