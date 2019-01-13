/*
File name: EulerModified.h
Author: Mehmet Efe Tiryaki
E-mail: m.efetiryaki@gmail.com
Date created: 21.12.2018
Date last modified: 13.1.2019
*/

#ifndef EULERMODIFIED_H_
#define EULERMODIFIED_H_

#include "OdeSolver.h"

namespace ODE {

class EulerModified : public OdeSolver
{
public:
  EulerModified();
  virtual ~EulerModified();
protected:
  virtual Eigen::VectorXd updateFunction() override;

};

} /* namespace ODE */


#endif /* EULERMODIFIED_H_ */
