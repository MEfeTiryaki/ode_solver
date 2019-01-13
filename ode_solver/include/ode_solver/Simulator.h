/*
File name: Simulator.h
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 13.1.2019
Date last modified: 13.1.2019
*/

#ifndef Simulator_H_
#define Simulator_H_

#include <Eigen/Core>

#include <iostream>
#include <boost/thread/thread.hpp>

#include "ode_solver/OdeSolver.h"

namespace ODE {

class Simulator
{
 public:
  /** \~turkish

      \~english
  */
  Simulator();
  /** \~turkish

      \~english
  */
  virtual ~Simulator();

  /** \~turkish
      @param[solver]
      \~english
      @param[solver]
  */
  void initilize(ODE::OdeSolver* solver);

  /** \~turkish

      @param[initialValue]
      @param[maxTime]
      @param[stepNumber]
      \~english

      @param[initialValue]
      @param[maxTime]
      @param[stepNumber]
  */
  void start(Eigen::VectorXd initialValue, double maxTime, int stepNumber);

  /** \~turkish

      @param[initialValue]
      @param[stepSize]
      \~english
      @param[initialValue]
      @param[stepSize]
  */
  void start(Eigen::VectorXd initialValue, double stepSize);

  /** TODO : check if this should be protected
      \~turkish

      \~english
  */
  void solve();

  /** \~turkish
      @param[id]

      \return
      \~english
      @param[initialValue]

      \return
  */
  std::vector<double> getBuffer(int id);

  /** \~turkish
      @param[stop]

      \~english
      @param[stop]
  */
  void setStop(bool stop);

  /** \~turkish
      @param[factor]

      \~english
      @param[factor]
  */
  void setRealTimeFactor(double factor){
    realTimeFactor_ = factor;
  }

  /** \~turkish

      \~english
  */
  void clearBuffer();

 protected:

  ODE::OdeSolver* solver_;

  bool stop_;
  // simulation time step
  double stepSize_;
  // current time in simulation
  double currentTime_;
  //  time step of the simulation
  int timeStep_;
  int maxTimeStep_;
  // simulation time step
  double realTimeFactor_;

  int n_;
  // solution matrix to be filled during calculation
  std::vector<Eigen::VectorXd> buffer_;

  // dynamic function
  std::function<Eigen::VectorXd(double,Eigen::VectorXd)> F_;

  boost::thread* workerThread_;
  boost::mutex workerMutex_;
  boost::chrono::system_clock::time_point start_;
};

} /* namespace ODE */

#endif /* OdeSolverNew_H_ */
