/*
File name: Euler.h
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 21.12.2018
Date last modified: 13.1.2019
*/

#ifndef EULER_H_
#define EULER_H_

#include "OdeSolver.h"

namespace ODE {

class Euler : public OdeSolver
{
public:
  Euler();
  virtual ~Euler();

protected:
  /** \~turkish
      \f[
        \Delta x = \Delta t f(t,x)
      \f]
      \return{}
      \~english
      \f[
          \Delta x = \Delta t f(t,x)
      \f]
      \return{}
  */
  virtual Eigen::VectorXd updateFunction() override;

};

} /* namespace ODE */


#endif /* EULER_H_ */
