/*
 File name: OdeSolver.h
 Author: Mehmet Efe Tiryaki
 E-mail: m.efetiryaki@gmail.com
 Date created: 21.12.2018
 Date last modified: 13.1.2019
 */

#ifndef ODESOLVER_H_
#define ODESOLVER_H_

#include <Eigen/Core>
#include <iostream>
#include <boost/thread/thread.hpp>

namespace ODE {

class OdeSolver
{
 public:
  /** \~turkish
      ATD çözücü yapıcısı
      \~english
      Ode solver constructor
  */
  OdeSolver();

  /** \~turkish
      ATD çözücü yıkıcısı
      \~english
      Ode solver destructor
  */
  virtual ~OdeSolver();

  /** \~turkish
      Türevsel denklemin başlangıç değerlerini, çözüm süresini ve adım sayısı
      düzenler. Solve yordamı çalıştırıldığında bu yordam çalıştırılmış olur.
      @param[initialValue]
      @param[maxTime]
      @param[stepNumber]
      \~english
      Sets the initial values, solution duration and step number. This method
      is run as the solve method is run.
      @param[initialValue]
      @param[maxTime]
      @param[stepNumber]
  */
  void initilize(Eigen::VectorXd initialValue, double maxTime, int stepNumber);

  /** \~turkish
      Türevsel denklemin başlangıç değerlerini ve adım boyunu düzenler. Çalışma
      süresi belli olmadığı zaman kullanılır. Solve yordamı çalıştırıldığında
      bu yordam çalıştırılmış olur.
      @param[initialValue]
      @param[stepSize]
      \~english
      Sets the initial values and step size. It is used when the solution duration
      is not known. This method is run as the solve method is run.
      @param[initialValue]
      @param[stepSize]
  */
  void initilize(Eigen::VectorXd initialValue, double stepSize);

  /** \~turkish
      Türevsel denklemi ATD çözücü içine yerleştirir.
      @param[F] Türevsel denklem
      \~english
      It registers the differential function.
      @param[F] Differential equation
  */
  void setDynamics(std::function<Eigen::VectorXd(double,Eigen::VectorXd)> F);

  /** \~turkish
      Türevsel denklemi tek kezde çözer.
      @param[initialValue]
      @param[maxTime]
      @param[stepNumber]
       \~english
      Solves the differential equation.
      @param[initialValue]
      @param[maxTime]
      @param[stepNumber]
  */
  void solve(Eigen::VectorXd initialValue, double maxTime, int stepNumber);


  /**  \~turkish
      ATD çözücüyü bir öd adımı boyu ilerletir. İşbu yordam solve yordamı içinde
      kullanılmaktadır. Çözücünün adım adım çalıştırılmak istenmesini olasılığı
      için açık bir yordamdır.
       \~english
      Advance the ode solver one time step size. This method is used by the
      solve method. It is a public method, in case you would like to use solver
      step by step.

  */
  void advance();

  /** \~turkish
      Çözüm yöneyini yalnızca son öğesi kalacak biçimde siler
      \~english
      While keeping the last element, deletes the rest of the solution vector
  */
  void clear();

  /** \~turkish
      En Son durumu yöneyini geri döner
      \return { Durum yöneyi = [Durum + öd] }
      \~english
      Returns the lastest state vector
      \return { State vector = [State + time] }
  */
  Eigen::VectorXd getState();

  /** \~turkish
      Bütün çözüm yöneylerini geri döner
      \return { Çözüm yöneyleri = [ Durum_yöneyi[0], Durum_yöneyi[1] ,..,Öd_yöneyi ] }
      \~english
      Returns all solution vectors
      \return { Solution vector = [ State_vector[0], State_vector[1] ,..,Time_vector ] }
  */
  std::vector<Eigen::VectorXd> getSolution();

 protected:
  /** \~turkish
      O anki durum yöneyi değişimini hesaplar
      \return{}
      \~english
      Calculates the change of the state vector at current time.
      \return{}
  */
  virtual Eigen::VectorXd updateFunction();


 protected:
  //! \~turkish Durum yöneyi boyu \~english State vector size
  int n_;
  //! \~turkish Öd adımı boyu \~english Time step size
  double stepSize_;
  //! \~turkish Çözümün o anki öd \~english Current time in the solution
  double currentTime_;
  //! \~turkish Çözümün o anki öd adımı \~english Time step of the solution
  int timeStep_;
  //! \~turkish En üst öd adım sayısı  \~english Maximum time step
  int maxTimeStep_;
  //! \~turkish Çözüm yöneyi, hesaplanan durum yöneyleri eklenir \~english Solution vector, calculated state vectors are added in
  std::vector<Eigen::VectorXd> solution_;
  //! \~turkish Değişim denklemi \~english Change function
  std::function<Eigen::VectorXd(double,Eigen::VectorXd)> F_;

};

} /* namespace ODE */

#endif /* ODESOLVER_H_ */
