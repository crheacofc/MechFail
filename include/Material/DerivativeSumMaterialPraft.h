/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef DERIVATIVESUMMATERIALPRAFT_H
#define DERIVATIVESUMMATERIALPRAFT_H

#include "DerivativeFunctionMaterialBase.h"

class DerivativeSumMaterialPraft;

template<>
InputParameters validParams<DerivativeSumMaterialPraft>();

class DerivativeSumMaterialPraft : public DerivativeFunctionMaterialBase
{
public:
  DerivativeSumMaterialPraft(const InputParameters & parameters);

  virtual void initialSetup();

protected:
  virtual void computeProperties();

  std::vector<std::string> _sum_materials;
  unsigned int _num_materials;

  /// arguments to construct a sum of the form \f$ c+\gamma\sum_iF_i \f$
  std::vector<Real> _prefactor;
  Real _constant;
  std::string _mat_name;
  bool _stateful_set;
  int _stateful;
  const MaterialProperty<Real> & _G_c;
  const MaterialProperty<Real> & _G_c_old;
  const MaterialProperty<Real> & _dG_cdc;
  const MaterialProperty<Real> & _d2G_cdc2;
  const MaterialProperty<Real> & _kappa;
  std::vector<const VariableGradient *> _gradarg;

  MaterialProperty<Real> & _energy_bulk;
  MaterialProperty<Real> & _energy_interface;

  /// Function values of the summands.
  std::vector<const MaterialProperty<Real> *> _summand_F;

  /// Derivatives of the summands with respect to arg[i]
  std::vector<std::vector<const MaterialProperty<Real> *> > _summand_dF;

  /// Second derivatives of the summands.
  std::vector<std::vector<std::vector<const MaterialProperty<Real> *> > > _summand_d2F;

  /// Third derivatives of the summands.
  std::vector<std::vector<std::vector<std::vector<const MaterialProperty<Real> *> > > > _summand_d3F;
};

#endif //DERIVATIVESUMMATERIALPRAFT_H
