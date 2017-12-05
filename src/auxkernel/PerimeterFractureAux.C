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

#include "PerimeterFractureAux.h"

template<>
InputParameters validParams<PerimeterFractureAux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredParam<Real>("factor", "factor relating the real area");
  params.addRequiredParam<Real>("lambda", "regularization parameter");
  params.addRequiredCoupledVar("phasefield", "the phase field variable");


  return params;
}

PerimeterFractureAux::PerimeterFractureAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _factor(getParam<Real>("factor")),
    _lambda(getParam<Real>("lambda")),
    _phi(coupledValue("phasefield")),
    _grad_phi(coupledGradient("phasefield"))


{
}

Real
PerimeterFractureAux::computeValue()
{

//coordinates of point p(0) and p(1)
   // Point p = _q_point[_qp];


     //Point p = (*_current_node);

     double perimeter = _factor*0.5*(0.5*_phi[_qp]*_phi[_qp]*(1.0-_phi[_qp])*(1.0-_phi[_qp])/_lambda + _lambda*_grad_phi[_qp]*_grad_phi[_qp]);


  return  perimeter;
}
