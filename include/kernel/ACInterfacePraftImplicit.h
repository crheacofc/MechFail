/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef ACInterfacePraftImplicit_H
#define ACInterfacePraftImplicit_H

#include "Kernel.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class ACInterfacePraftImplicit;

template<>
InputParameters validParams<ACInterfacePraftImplicit>();

class ACInterfacePraftImplicit : public DerivativeMaterialInterface<JvarMapKernelInterface<Kernel> >
{
public:
  ACInterfacePraftImplicit(const InputParameters & parameters);
  virtual void initialSetup();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();


  std::string _mat_name;

  RealGradient gradL();
  RealGradient gradKappa();
  RealGradient gradG_c();

  /// the \f$ \nabla(L\kappa\psi) \f$ term
  RealGradient nablaLKappaPsi();

  /// Mobility
  const MaterialProperty<Real> & _L_nouse;
  const MaterialProperty<Real> & _L;
  const MaterialProperty<RealGradient> & _L_grad;

  /// Interfacial parameter
  const MaterialProperty<Real> & _kappa;

  /// Interfacial parameter
  const MaterialProperty<Real> & _G_c_nouse;
  const MaterialProperty<Real> & _G_c;
  const MaterialProperty<RealGradient> & _G_c_grad;



  /// flag set if L is a function of non-linear variables in args
  bool _variable_L;

  /// flag set if kappa is a function of non-linear variables in args
  bool _variable_kappa;

  /// flag set if kappa is a function of non-linear variables in args
  bool _variable_G_c;

  /// @{ Mobility derivatives w.r.t. order parameter
  const MaterialProperty<Real> & _dLdop;
  const MaterialProperty<Real> & _d2Ldop2;
  /// @}

  /// @{ kappa derivatives w.r.t. order parameter
  const MaterialProperty<Real> & _dkappadop;
  const MaterialProperty<Real> & _d2kappadop2;
  /// @}
  ///

  /// @{ kappa derivatives w.r.t. order parameter
  const MaterialProperty<Real> & _dG_cdop;
  const MaterialProperty<Real> & _d2G_cdop2;
  /// @}

  /// number of coupled variables
  unsigned int _nvar;

  /// @{ Mobility derivative w.r.t. other coupled variables
  std::vector<const MaterialProperty<Real> *> _dLdarg;
  std::vector<const MaterialProperty<Real> *> _d2Ldargdop;
  std::vector<std::vector<const MaterialProperty<Real> *> > _d2Ldarg2;
  /// @}

  /// @{ kappa derivative w.r.t. other coupled variables
  std::vector<const MaterialProperty<Real> *> _dkappadarg;
  std::vector<const MaterialProperty<Real> *> _d2kappadargdop;
  std::vector<std::vector<const MaterialProperty<Real> *> > _d2kappadarg2;
  /// @}
  ///
  /// /// @{ G_c derivative w.r.t. other coupled variables
  std::vector<const MaterialProperty<Real> *> _dG_cdarg;
  std::vector<const MaterialProperty<Real> *> _d2G_cdargdop;
  std::vector<std::vector<const MaterialProperty<Real> *> > _d2G_cdarg2;
  /// @}

  /// Gradients for all coupled variables
   std::vector<const VariableGradient *> _gradarg;
};

#endif //ACInterfacePraftImplicit_H
