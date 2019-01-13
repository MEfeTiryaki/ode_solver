/*
File name: Simulator.cpp
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 13.1.2019
Date last modified: 13.1.2019
*/

#include "ode_solver/Simulator.h"
#include <unistd.h>
#include <boost/chrono.hpp>
#include <ctime>
namespace ODE {

Simulator::Simulator()
    : currentTime_(0.0),
      stepSize_(0.0),
      maxTimeStep_(0),
      timeStep_(0.0),
      realTimeFactor_(1.0),
      stop_(false)
{
}

Simulator::~Simulator()
{
}


void Simulator::initilize(ODE::OdeSolver* solver){
  solver_ = solver;
}

void Simulator::start(Eigen::VectorXd initialValue, double maxTime, int stepNumber){
  maxTimeStep_ = stepNumber;
  stepSize_ = maxTime / stepNumber;
  currentTime_ = 0.0;

  n_ = initialValue.size();
  solver_->initilize(initialValue, maxTime, stepNumber);

buffer_.push_back(Eigen::VectorXd::Zero(n_+1));
  buffer_.back().segment(0,n_) = initialValue;

  workerThread_ = new boost::thread(boost::bind(&Simulator::solve,this));
  start_ = boost::chrono::system_clock::now();
  stop_ = false;
}

void Simulator::start(Eigen::VectorXd initialValue, double stepSize){
  maxTimeStep_ = std::numeric_limits<int>::max();
  stepSize_ = stepSize;
  currentTime_ = 0.0;

  n_ = initialValue.size();

  solver_->initilize(initialValue,stepSize);

  buffer_.push_back(Eigen::VectorXd::Zero(n_+1));
  buffer_.back().segment(0,n_) = initialValue;

  workerThread_ = new boost::thread(boost::bind(&Simulator::solve,this));
  start_ = boost::chrono::system_clock::now();
  stop_ = false;
}


void Simulator::setStop(bool stop){
  stop_ = stop;
}

std::vector<double> Simulator::getBuffer(int id){
  boost::lock_guard<boost::mutex> lock(workerMutex_);

  std::vector<double> b = std::vector<double>(0);

  if(buffer_.size()>1){
    if(id == -1){

      for(int i = 0 ; i< buffer_.size()-1 ; i++ ){
        b.push_back(buffer_[i][n_]);
      }
    }
    else{
      for(int i = 0 ; i< buffer_.size()-1 ; i++ ){
        b.push_back(buffer_[i][id]);
      }
    }
  }
  return b;
}

void Simulator::clearBuffer(){
  Eigen::VectorXd last = buffer_.back();
  buffer_.clear();
  buffer_.push_back(last);
}

void Simulator::solve(){

  for (timeStep_ = 0; timeStep_ < maxTimeStep_-1; ) {
    if(!stop_){
      boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
      {
        boost::lock_guard<boost::mutex> lock(workerMutex_);
        solver_->advance();
        buffer_.push_back(solver_->getState());
        solver_->clear();
      }
      boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - start;
      boost::chrono::duration<double> sinceStart = boost::chrono::system_clock::now() - start_;

      int microSecond = (stepSize_*realTimeFactor_-sec.count())*1000000;
      if(microSecond>0){
        //std::cout << sinceStart.count() <<" , "<<microSecond << " seconds\n";
        usleep(microSecond);
      }else{
        std::cout << "\033[0;33m"
                  << "Warning : Real time factor is " <<sec.count()/stepSize_
                  << "\033[0m" << std::endl;
      }
      timeStep_++;
    }else{
      usleep(100);
    }
  }
}


} /* namespace ODE */
