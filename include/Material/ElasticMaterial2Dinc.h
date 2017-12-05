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

#ifndef ELASTICMATERIAL2DINC_H
#define ELASTICMATERIAL2DINC_H
#include "DerivativeMaterialInterface.h"

#include "Material.h"
#include "RankTwoTensor.h"



//Forward Declarations
class ElasticMaterial2Dinc;

template<>
InputParameters validParams<ElasticMaterial2Dinc>();

/**
 * Praft material class that defines a few properties.
 */
class ElasticMaterial2Dinc : public DerivativeMaterialInterface<Material>
{
public:
  ElasticMaterial2Dinc(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();
  virtual void initQpStatefulProperties();


private:


  /// Elastic constants
  bool _bulk_modulus_set;
  bool _lambda_set;
  bool _poissons_ratio_set;
  bool _shear_modulus_set;
  bool _youngs_modulus_set;
  bool _decomp_set;
  bool _stateful_set;
  bool _eta_set;
  bool _irrev_set;



  Real _bulk_modulus;
  Real _lambda;
  Real _poissons_ratio;
  Real _shear_modulus;
  Real _youngs_modulus;
  int _decomp;
  int _stateful;
  Real _eta;
  int _irrev;


  std::string _base_name;
  std::string _mat_name;

  //Coupled variable
  const VariableValue & _concentration;

  const MaterialProperty<RankTwoTensor> & _total_strain;
  MaterialProperty<RankTwoTensor>  & _stress;
  MaterialProperty<RankTwoTensor>  & _stress_old;
  MaterialProperty<std::vector<Real> > & _Jacobian_mult;



  MaterialProperty<Real> & trace_st;
  MaterialProperty<Real> & trace_st_old;
  MaterialProperty<std::vector<Real> > & strain_plus_st;
  MaterialProperty<std::vector<Real> > & strain_plus_st_old;
  MaterialProperty<std::vector<Real> > & strain_minus_st;
  MaterialProperty<std::vector<Real> > & strain_minus_st_old;
  MaterialProperty<Real> & _concentration_st;
  MaterialProperty<Real> & _concentration_st_old;


  MaterialProperty<Real> & _energy_tensile_raw;
  MaterialProperty<Real> & _energy_compressive_raw;
  MaterialProperty<Real> & _energy_tensile_raw_history;
  MaterialProperty<Real> & _energy_tensile_raw_history_old;
  MaterialProperty<Real> & _energy_tensile;
  MaterialProperty<Real> & _d_energy_tensile_dc;
  MaterialProperty<Real> & _d2_energy_tensile_dc2;



  std::vector<Real> iso_const;


};

#endif //ELASTICMATERIAL2D_H
