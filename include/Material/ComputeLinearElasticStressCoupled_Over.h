/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTELINEARELASTICSTRESSCOUPLED_OVER_H
#define COMPUTELINEARELASTICSTRESSCOUPLED_OVER_H

#include "ComputeStressBase.h"

/**
 * ComputeLinearElasticStressCoupled_Over computes the stress following linear elasticity theory (small strains)
 */
class ComputeLinearElasticStressCoupled_Over : public ComputeStressBase
{
public:
  ComputeLinearElasticStressCoupled_Over(const InputParameters & parameters);

protected:
  virtual void computeQpStress();

  const MaterialProperty<RankTwoTensor> & _total_strain;
  const bool _is_finite_strain;

  bool _aux_const_set;
  Real _aux_const;

  //Coupled variable
  const VariableValue & _porosity;
  const VariableValue & _concentration;

private:





};

#endif //COMPUTELINEARELASTICSTRESSCOUPLED_OVER_H
