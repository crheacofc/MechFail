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

#ifndef ELASTIC2D_H
#define ELASTIC2D_H

#include "Material.h"
#include "RankTwoTensor.h"



//Forward Declarations
class Elastic2D;

template<>
InputParameters validParams<Elastic2D>();

/**
 * Praft material class that defines a few properties.
 */
class Elastic2D : public DerivativeMaterialInterface<Material>
{
public:
  Elastic2D(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();
  virtual void initQpStatefulProperties();

private:
  /**
   * parameters
  */

  bool _viscosity_set, _L_const_set,  _G_c_const_set, _over_const_set, _diameter_set, _tens_wg_set, _tens_s_set, _eta_set, _jam_set, _jam_factor_set, _break_set, _packing_mean_set;
  Real _viscosity, _L_const, _G_c_const, _over_const, _diameter, _tens_wg, _tens_s, _eta, _jam,_jam_factor, _break, _packing_mean;

  std::string _base_name;
  std::string _mat_name;


  MaterialProperty<std::vector<Real>> &_stress;
  MaterialProperty<std::vector<Real>> &_Jacobian_mult;




};

#endif //ELASTIC2D_H
