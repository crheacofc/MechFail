/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTEISOELASTICITYTENSORCOUPLED_H
#define COMPUTEISOELASTICITYTENSORCOUPLED_H

#include "ComputeElasticityTensorBase.h"

/**
 * ComputeElasticityTensor defines an elasticity tensor material for isi.
 */
class ComputeIsoElasticityTensorCoupled : public ComputeElasticityTensorBase
{
public:
  ComputeIsoElasticityTensorCoupled(const InputParameters & parameters);

protected:
  virtual void computeQpElasticityTensor();

  /// Elastic constants
  bool _bulk_modulus_set;
  bool _lambda_set;
  bool _poissons_ratio_set;
  bool _shear_modulus_set;
  bool _youngs_modulus_set;
  bool _eta_set;


  Real _bulk_modulus;
  Real _lambda;
  Real _poissons_ratio;
  Real _shear_modulus;
  Real _youngs_modulus;
  Real _eta;


  //Coupled variable
  const VariableValue & _porosity;
  VariableName _phi_name;//to get name of porosity (usually phi)

  //For derivatives of elasticity tensor w.r.t. porosity
  MaterialProperty<RankFourTensor> & _delasticity_tensor_dphi;
  MaterialProperty<RankFourTensor> & _d2elasticity_tensor_dphi2;



  /// Individual elasticity tensor
  RankFourTensor _Cijkl;
};

#endif //COMPUTEISOELASTICITYTENSORCOUPLED_H
