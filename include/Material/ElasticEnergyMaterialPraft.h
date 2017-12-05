/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef ELASTICENERGYMATERIALPRAFT_H
#define ELASTICENERGYMATERIALPRAFT_H

#include "DerivativeFunctionMaterialBase.h"
#include "DerivativeMaterialInterface.h"

// Forward Declaration
class ElasticEnergyMaterialPraft;
class RankTwoTensor;
class RankFourTensor;

template<>
InputParameters validParams<DerivativeFunctionMaterialBase>();

/**
 * Material class to compute the elastic free energy and its derivatives
 */
class ElasticEnergyMaterialPraft : public DerivativeFunctionMaterialBase
{
public:
  ElasticEnergyMaterialPraft(const InputParameters & parameters);

protected:
  virtual Real computeF();
  virtual Real computeDF(unsigned int);
  virtual Real computeD2F(unsigned int, unsigned int);

  std::string _base_name;

  const MaterialProperty<RankTwoTensor> & _stress;
  const MaterialProperty<RankFourTensor> & _elasticity_tensor_raw;
  const MaterialProperty<RankTwoTensor> & _strain;


  VariableValue _concentration;

  bool _eta_set;
  Real _eta;

  MaterialProperty<Real> & _energy_history;

};

#endif //ELASTICENERGYMATERIALPRAFT_H
