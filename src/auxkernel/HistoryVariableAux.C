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

#include "HistoryVariableAux.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<HistoryVariableAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("damage", "coupled variable to store as history");

  return params;
}

HistoryVariableAux::HistoryVariableAux(const InputParameters & parameters) :
  // You must call the constructor of the base class first
  AuxKernel(parameters),
  _damage(coupledValue("damage"))

{}

Real HistoryVariableAux::computeValue()
{

//compare
Real value;

if (_damage[_qp] > _u_old[_qp]) value = _damage[_qp];
else value = _u_old[_qp];

return value;
}


