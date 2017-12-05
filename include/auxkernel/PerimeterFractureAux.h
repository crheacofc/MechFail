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

#ifndef PerimeterFractureAux_H
#define PerimeterFractureAux_H

#include "AuxKernel.h"

//Forward Declarations
class PerimeterFractureAux;

template<>
InputParameters validParams<PerimeterFractureAux>();

/**
 * Constant auxiliary value
 */
class PerimeterFractureAux : public AuxKernel
{
public:
  PerimeterFractureAux(const InputParameters & parameters);

  virtual ~PerimeterFractureAux() {}

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue();

  Real _factor, _lambda;
  const VariableValue & _phi;
  const VariableGradient & _grad_phi;

};

#endif //PerimeterFractureAux_H
