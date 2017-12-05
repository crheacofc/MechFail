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

#ifndef AreaFractureAux_H
#define AreaFractureAux_H

#include "AuxKernel.h"

//Forward Declarations
class AreaFractureAux;

template<>
InputParameters validParams<AreaFractureAux>();

/**
 * Constant auxiliary value
 */
class AreaFractureAux : public AuxKernel
{
public:
  AreaFractureAux(const InputParameters & parameters);

  virtual ~AreaFractureAux() {}

protected:
  /**
   * AuxKernels MUST override computeValue.  computeValue() is called on
   * every quadrature point.  For Nodal Auxiliary variables those quadrature
   * points coincide with the nodes.
   */
  virtual Real computeValue();

  const VariableValue & _phi;

};

#endif //AreaFractureAux_H
