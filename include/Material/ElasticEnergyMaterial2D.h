/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef ELASTICENERGYMATERIAL2D_H
#define ELASTICENERGYMATERIAL2D_H

#include "DerivativeFunctionMaterialBase.h"

// Forward Declaration
class ElasticEnergyMaterial2D;
class RankTwoTensor;
class RankFourTensor;

template<>
InputParameters validParams<DerivativeFunctionMaterialBase>();

/**
 * Material class to compute the elastic free energy and its derivatives
 */
class ElasticEnergyMaterial2D : public DerivativeFunctionMaterialBase
{
public:
  ElasticEnergyMaterial2D(const InputParameters & parameters);

protected:
  virtual Real computeF();
  virtual Real computeDF(unsigned int);
  virtual Real computeD2F(unsigned int, unsigned int);

  std::string _base_name;
  bool _over_set;
  int _over;

  /*
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
  */

  const MaterialProperty<Real> & _energy_tensile;
  const MaterialProperty<Real> & _d_energy_tensile_dc;
  const MaterialProperty<Real> & _d2_energy_tensile_dc2;

  const MaterialProperty<Real> & _energy_over;
  const MaterialProperty<Real> & _d_energy_over_dc;
  const MaterialProperty<Real> & _d2_energy_over_dc2;




};

#endif //ELASTICENERGYMATERIAL2D_H
