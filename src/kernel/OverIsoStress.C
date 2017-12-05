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

#include "OverIsoStress.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<OverIsoStress>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("mat_name", "Praft material name");
  params.addRequiredParam<std::string>("component", "x, y");
  return params;
}

OverIsoStress::OverIsoStress(const InputParameters & parameters) :
  // You must call the constructor of the base class first
  Kernel(parameters),
  _mat_name(getParam<std::string>("mat_name")),
  _component(getParam<std::string>("component")),
  //_overisostress(getMaterialPropertyOldByName<Real>(_mat_name + "_" + "overisostress"))
  _overisostress(getMaterialPropertyByName<Real>(_mat_name + "_" + "overisostress"))
{}

Real OverIsoStress::computeQpResidual()
{
  int _comp;

  if (_component == "x" ) _comp = 0;
  if (_component == "y" ) _comp = 1;

  return _grad_test[_i][_qp](_comp)*_overisostress[_qp];
}

Real OverIsoStress::computeQpJacobian()
{
  return 0.0;
}
