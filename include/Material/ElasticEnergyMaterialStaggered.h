/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef ELASTICENERGYMATERIALSTAGGERED_H
#define ELASTICENERGYMATERIALSTAGGERED_H

#include "DerivativeFunctionMaterialBase.h"

// Forward Declaration
class ElasticEnergyMaterialStaggered;
class RankTwoTensor;
class RankFourTensor;

template<>
InputParameters validParams<DerivativeFunctionMaterialBase>();

/**
 * Material class to compute the elastic free energy and its derivatives
 */
class ElasticEnergyMaterialStaggered : public DerivativeFunctionMaterialBase
{
public:
  ElasticEnergyMaterialStaggered(const InputParameters & parameters);

protected:
  virtual Real computeF();
  virtual Real computeDF(unsigned int);
  virtual Real computeD2F(unsigned int, unsigned int);

  std::string _base_name;

  /// Stress tensor
  const MaterialProperty<RankTwoTensor> & _stress;
  std::vector<const MaterialProperty<RankTwoTensor> *> _dstress;
  std::vector<std::vector<const MaterialProperty<RankTwoTensor> *> > _d2stress;

  ///@{ Elasticity tensor derivatives
  const MaterialProperty<RankFourTensor> & _elasticity_tensor;
  std::vector<const MaterialProperty<RankFourTensor> *> _delasticity_tensor;
  std::vector<std::vector<const MaterialProperty<RankFourTensor> *> > _d2elasticity_tensor;
  ///@}

  ///@{ Strain and derivatives
  const MaterialProperty<RankTwoTensor> & _strain;
  const MaterialProperty<RankTwoTensor> & _strain_old;
  std::vector<const MaterialProperty<RankTwoTensor> *> _dstrain;
  std::vector<std::vector<const MaterialProperty<RankTwoTensor> *> > _d2strain;
  ///@}
};

#endif //ELASTICENERGYMATERIALSTAGGERED_H
