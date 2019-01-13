/*
 File name: RungeKutta.h
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 21.12.2018
 Date last modified: 13.1.2019
 */


#ifndef RUNGEKUTTA_H_
#define RUNGEKUTTA_H_

#include "OdeSolver.h"

namespace ODE {

class RungeKutta : public OdeSolver
{
 public:
   /** \~turkish
       Runge-Kutta ATD çözücü yapıcısı
       \~english
       Runge-Kutta Ode solver constructor
   */
  RungeKutta();

   /** \~turkish
       Runge-Kutta ATD çözücü yıkıcısı
       \~english
       Runge-Kutta Ode solver destructor
   */
  virtual ~RungeKutta();

 protected:
   /** \~turkish
       \f[
          k_1 = \Delta t f(t,x)
       \f]
       \f[
          k_2 = \Delta t f(t+\Delta t/2,x+k_1/2)
       \f]
       \f[
          k_3 = \Delta t f(t+\Delta t/2,x+k_2/2)
       \f]
       \f[
          k_4 = \Delta t f(t+\Delta t,x+k_3)
       \f]
       \f[
          \Delta x = k_1 + 2 k_2 + 2 k_3 + k_4
       \f]
       \return{}
       \~english
       \f[
          k_1 = \Delta t f(t,x)
       \f]
       \f[
          k_2 = \Delta t f(t+\Delta t/2,x+k_1/2)
       \f]
       \f[
          k_3 = \Delta t f(t+\Delta t/2,x+k_2/2)
       \f]
       \f[
          k_4 = \Delta t f(t+\Delta t,x+k_3)
       \f]
       \f[
          \Delta x = k_1 + 2 k_2 + 2 k_3 + k_4
       \f]
       \return{}
   */
   virtual Eigen::VectorXd updateFunction() override;


 protected:
  Eigen::VectorXd k1_;
  Eigen::VectorXd k2_;
  Eigen::VectorXd k3_;
  Eigen::VectorXd k4_;

};

} /* namespace ODE */



#endif /* RUNGEKUTTA_H_ */
