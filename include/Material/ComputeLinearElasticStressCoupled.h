/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTELINEARELASTICSTRESSCOUPLED_H
#define COMPUTELINEARELASTICSTRESSCOUPLED_H

#include "ComputeStressBase.h"

/**
 * ComputeLinearElasticStressCoupled computes the stress following linear elasticity theory (small strains)
 */
class ComputeLinearElasticStressCoupled : public ComputeStressBase
{
public:
  ComputeLinearElasticStressCoupled(const InputParameters & parameters);

protected:
  virtual void computeQpStress();

  const MaterialProperty<RankTwoTensor> & _total_strain;
  const MaterialProperty<RankTwoTensor> & _total_strain_global;
  const bool _is_finite_strain;

  bool _aux_const_set;
  Real _aux_const;
  bool _decomp_set;
  Real _decomp;

  //Coupled variable
  const VariableValue & _porosity;
  const VariableValue & _concentration;

private:

  //Coupled variable
  VariableName _c_name;//to get name of concentration

  //For derivatives of elasticity tensor w.r.t. concentration
  MaterialProperty<RankTwoTensor> & _dstress_dc;
  MaterialProperty<RankTwoTensor> & _d2stress_dc2;



};

#endif //COMPUTELINEARELASTICSTRESSCOUPLED_H
