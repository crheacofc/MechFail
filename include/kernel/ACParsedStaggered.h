/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef ACPARSEDSTAGGERED_H
#define ACPARSEDSTAGGERED_H

#include "KernelValue.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class ACParsedStaggered;

template<>
InputParameters validParams<ACParsedStaggered>();

class ACParsedStaggered : public DerivativeMaterialInterface<JvarMapKernelInterface<KernelValue> >
{
public:
  ACParsedStaggered(const InputParameters & parameters);

  virtual void initialSetup();

protected:

  virtual Real precomputeQpResidual();
  virtual Real precomputeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);


  std::string _mat_name;

  /// Mobility
  const MaterialProperty<Real> & _L;

  //derivatives of bulk function w.r.t. the variables
  const MaterialProperty<Real> & _dFdEta;
  const MaterialProperty<Real> & _d2FdEta2;

  std::vector<const MaterialProperty<Real> *> _d2FdEtadarg;
};

#endif //ACPARSEDSTAGGERED_H
