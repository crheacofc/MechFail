/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTELINEARELASTICSTRESSDECOMPCOUPLED_H
#define COMPUTELINEARELASTICSTRESSDECOMPCOUPLED_H

#include "ComputeStressBase.h"

/**
 * ComputeLinearElasticStressDecomp computes the stress following linear elasticity theory (small strains)
 */
class ComputeLinearElasticStressDecompCoupled : public ComputeStressBase
{
public:
  ComputeLinearElasticStressDecompCoupled(const InputParameters & parameters);

protected:
  virtual void computeQpStress();

  const MaterialProperty<RankTwoTensor> & _total_strain;
  const MaterialProperty<RankTwoTensor> & _total_strain_global;
  const bool _is_finite_strain;

  const MaterialProperty<RankFourTensor> & _elasticity_tensor_old;
  MaterialProperty<RankFourTensor> & _elasticity_tensor_final;

  bool _aux_const_set;
  Real _aux_const;
  bool _decomp_set;
  Real _decomp;


  //Coupled variable
  //VariableValue & _porosity;
  //VariableValue & _concentration;

private:

  //Coupled variable
  VariableName _c_name;//to get name of concentration



  //For derivatives of elasticity tensor w.r.t. concentration
  //MaterialProperty<RankTwoTensor> & _dstress_dc;
  //MaterialProperty<RankTwoTensor> & _d2stress_dc2;



};

#endif //COMPUTELINEARELASTICSTRESSDECOMPCOUPLED_H
