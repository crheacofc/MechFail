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

#include "AreaFractureAux.h"

template<>
InputParameters validParams<AreaFractureAux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("phasefield", "the phase field variable");

  return params;
}

AreaFractureAux::AreaFractureAux(const InputParameters & parameters) :
    AuxKernel(parameters),
    _phi(coupledValue("phasefield"))


{
}

Real
AreaFractureAux::computeValue()
{

//coordinates of point p(0) and p(1)
   // Point p = _q_point[_qp];


     //Point p = (*_current_node);

     double area = _phi[_qp];


  return  area;
}
