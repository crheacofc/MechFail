/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "ElasticEnergyMaterial2DFrac.h"
#include "RankTwoTensor.h"
#include "RankFourTensor.h"
#include "ElasticityTensorTools.h"

template<>
InputParameters validParams<ElasticEnergyMaterial2DFrac>()
{
  InputParameters params = validParams<DerivativeFunctionMaterialBase>();
  params.addClassDescription("This class just redirects the proper tensile energy and derivatives w.r.t. damageto be used along with a phase field kernel");
  params.addParam<std::string>("base_name", "Material property base name");
  params.addRequiredCoupledVar("args", "Arguments of F() - use vector coupling : tipically the damage");
  return params;
}

ElasticEnergyMaterial2DFrac::ElasticEnergyMaterial2DFrac(const InputParameters & parameters) :
    DerivativeFunctionMaterialBase(parameters),

    //parameters
    _base_name(getParam<std::string>("base_name")),

    //get current
    _energy_tensile(getMaterialPropertyByName<Real>(_base_name + "_" + "energy_tensile")),
    _d_energy_tensile_dc(getMaterialPropertyByName<Real>(_base_name + "_" + "d_energy_tensile_dc")),
    _d2_energy_tensile_dc2(getMaterialPropertyByName<Real>(_base_name + "_" + "d2_energy_tensile_dc2"))



{}


//get value and derivatives (only elasticity tensor has derivatives)


Real
ElasticEnergyMaterial2DFrac::computeF()
{

  return _energy_tensile[_qp];

}

Real
ElasticEnergyMaterial2DFrac::computeDF(unsigned int i_var)
{
  unsigned int i = argIndex(i_var);

  return _d_energy_tensile_dc[_qp];

}

Real
ElasticEnergyMaterial2DFrac::computeD2F(unsigned int i_var, unsigned int j_var)
{
  unsigned int i = argIndex(i_var);
  unsigned int j = argIndex(j_var);

  return _d2_energy_tensile_dc2[_qp];

}

