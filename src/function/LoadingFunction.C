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

#include "LoadingFunction.h"

template<>
InputParameters validParams<LoadingFunction>()
{
  InputParameters params = validParams<Function>();
  params.addParam<Real>("alpha", 1.0, "The value of alpha");
  return params;
}

LoadingFunction::LoadingFunction(const InputParameters & parameters) :
    Function(parameters),
  _alpha(getParam<Real>("alpha"))
{}

Real
LoadingFunction::value(Real t, const Point & p)
{
    if (t<_alpha)
    {return t/_alpha;}
    else {return 1.0;}
}
