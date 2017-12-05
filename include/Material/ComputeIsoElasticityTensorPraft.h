/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTEISOELASTICITYTENSORPRAFT_H
#define COMPUTEISOELASTICITYTENSORPRAFT_H

#include "ComputeElasticityTensorBase.h"

/**
 * ComputeElasticityTensor defines an elasticity tensor material for isi.
 */
class ComputeIsoElasticityTensorPraft : public ComputeElasticityTensorBase
{
public:
  ComputeIsoElasticityTensorPraft(const InputParameters & parameters);

protected:
  virtual void computeQpElasticityTensor();
  virtual void initQpStatefulProperties();

  /// Elastic constants
  bool _bulk_modulus_set;
  bool _lambda_set;
  bool _poissons_ratio_set;
  bool _shear_modulus_set;
  bool _youngs_modulus_set;
  bool _decomp_set;
  bool _eta_set;
  bool _jam_set;
  bool _break_set;

  Real _bulk_modulus;
  Real _lambda;
  Real _poissons_ratio;
  Real _shear_modulus;
  Real _youngs_modulus;
  Real _decomp;
  Real _eta;
  Real _jam;
  Real _break;

   std::string _mat_name;

  //Coupled variable
  const VariableValue & _concentration;
  VariableName _c_name;//to get name of concentration

  //For derivatives of elasticity tensor w.r.t. porosity
  MaterialProperty<RankFourTensor> & _delasticity_tensor_dc;
  MaterialProperty<RankFourTensor> & _d2elasticity_tensor_dc2;
  MaterialProperty<RankFourTensor> & _elasticity_tensor_old;

   //const MaterialProperty<Real> & _conc_factor;
   //const MaterialProperty<Real> & _pack_factor_tensile;
   const MaterialProperty<Real> & _pack_factor_compressive;

  /// Individual elasticity tensor
  RankFourTensor _Cijkl;



};

#endif //COMPUTEISOELASTICITYTENSORPRAFT_H
