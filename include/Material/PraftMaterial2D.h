/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PRAFTMATERIAL2D_H
#define PRAFTMATERIAL2D_H

#include "Material.h"
#include "RankTwoTensor.h"


//Forward Declarations
class PraftMaterial2D;
class Function;

template<>
InputParameters validParams<PraftMaterial2D>();

/**
 * Praft material class that defines a few properties.
 */
class PraftMaterial2D : public DerivativeMaterialInterface<Material>
{
public:
  PraftMaterial2D(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();
  virtual void initQpStatefulProperties();

private:
  /**
   * parameters
  */

  bool _viscosity_set, _L_const_set,  _G_c_const_set, _over_const_set, _diameter_set, _tens_wg_set, _tens_s_set,  _jam_set, _jam_factor_set, _break_set, _irrev_set, _over_type_set, _mobpack_imp_set, _mobpack_fac_set, _stateful_set,  _pack_update_set;
  Real _viscosity, _L_const, _G_c_const, _over_const, _diameter, _tens_wg, _tens_s, _jam,_jam_factor, _break;
  int _irrev, _over_type, _mobpack_imp, _mobpack_fac, _stateful, _pack_update;


  Function & _loadingfunction;

  std::string _mat_name;
  std::string _base_name;


  /**
   * This is the member reference that will hold the computed values
   * for the values property and gradients in this class.
   */



  /**
   * This is the member reference that will hold the gradient
   * of the coupled variable
   */

  const VariableValue & _packing;
  const VariableGradient & _packing_gradient;

  const VariableValue & _concentration;
  const VariableGradient & _concentration_gradient;

  const MaterialProperty<Real> & _trace;
  const MaterialProperty<Real> & _trace_old;

  MaterialProperty<Real> & _packing_prop;
  MaterialProperty<RealGradient> & _packing_prop_gradient;

  MaterialProperty<Real> & _tens;
  MaterialProperty<Real> & _overisostress;
  MaterialProperty<Real> & _G_c;
  MaterialProperty<Real> & _G_c_old;
  MaterialProperty<Real> & _L;
  MaterialProperty<Real> & _L_old;
  VariableName _c_name;
  MaterialProperty<Real> & _dG_cdc;
  MaterialProperty<Real> & _d2G_cdc2;
  MaterialProperty<RealGradient> & _G_c_grad;
  MaterialProperty<RealGradient> & _G_c_grad_old;
  MaterialProperty<RealGradient> & _L_grad;
  MaterialProperty<RealGradient> & _L_grad_old;

  MaterialProperty<Real> &_concentration_history;
  MaterialProperty<Real> &_concentration_history_old;
  MaterialProperty<Real> &_trace_history;
  MaterialProperty<Real> &_trace_history_old;

  MaterialProperty<Real> & _pack_factor_compressive;
  MaterialProperty<Real> & _pack_factor_compressive_old;

  MaterialProperty<Real> & _energy_over;
  MaterialProperty<Real> & _d_energy_over_dc;
  MaterialProperty<Real> & _d2_energy_over_dc2;

  MaterialProperty<RealGradient> & _F_marangoni;
  MaterialProperty<RealGradient> & _F_marangoni_old;



};

#endif //PRAFTMATERIAL2D_H
