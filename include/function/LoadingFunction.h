/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef LOADINGFUNCTION_H
#define LOADINGFUNCTION_H

#include "Function.h"

class LoadingFunction;

template<>
InputParameters validParams<LoadingFunction>();

class LoadingFunction : public Function
{
public:
  LoadingFunction(const InputParameters & parameters);

  virtual Real value(Real t, const Point & p);

protected:
  Real _alpha;

};

#endif //LOADINGFUNCTION_H
