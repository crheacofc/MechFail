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

#ifndef INJECTIONDIRAC_H
#define INJECTIONDIRAC_H

// Moose Includes
#include "DiracKernel.h"

// Forward Declarations
class InjectionDirac;

template<>
InputParameters validParams<InjectionDirac>();

class InjectionDirac : public DiracKernel
{
public:
  InjectionDirac(const InputParameters & parameters);

  virtual void addPoints();
  virtual Real computeQpResidual();

protected:
  Real _value;
  Point _point;
};

#endif //INJECTIONDIRAC_H
