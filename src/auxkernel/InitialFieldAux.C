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

#include "InitialFieldAux.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<InitialFieldAux>()
{
  InputParameters params = validParams<AuxKernel>();

  return params;
}

InitialFieldAux::InitialFieldAux(const InputParameters & parameters) :
  // You must call the constructor of the base class first
  AuxKernel(parameters)

{}

Real InitialFieldAux::computeValue()
{
  return _u[_qp];
}


