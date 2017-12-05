/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTESMALLSTRAINDECOMP_H
#define COMPUTESMALLSTRAINDECOMP_H

#include "ComputeStrainBase.h"

/**
 * ComputeSmallStrainDecomp defines a strain tensor, assuming small strains.
 */
class ComputeSmallStrainDecomp : public ComputeStrainBase
{
public:
  ComputeSmallStrainDecomp(const InputParameters & parameters);

protected:
  virtual void computeProperties();
  virtual void initQpStatefulProperties();

  const MaterialProperty<RankTwoTensor> & _stress_free_strain;


  bool _decomp_set;
  Real _angle;
  Real _decomp;
  MaterialProperty<Real> & _angle_ppal; //to perform rotations on strain tensor
  MaterialProperty<RankTwoTensor> & _total_strain_ppal;
  MaterialProperty<RankTwoTensor> & _total_strain_global;//strain not decomposed
  MaterialProperty<RankTwoTensor> & _total_strain_old;//strain history
  MaterialProperty<Real> & _trace_strain;
  MaterialProperty<Real> & _trace_strain_old;
  MaterialProperty<Real> & _trace_strain_older;
  MaterialProperty<Real> & _eig0;
  MaterialProperty<Real> & _eig1;
  MaterialProperty<Real> & _eig2;
};

#endif //COMPUTESMALLSTRAINDECOMP_H
