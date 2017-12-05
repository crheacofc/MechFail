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

#include "ElasticKernel2D.h"

template<>
InputParameters validParams<ElasticKernel2D>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<std::string>("base_name", "Praft material name");
  params.addRequiredParam<std::string>("component", "x, y");
  params.addCoupledVar("coupled", "");
  return params;
}

ElasticKernel2D::ElasticKernel2D(const InputParameters & parameters) :
  // You must call the constructor of the base class first
  Kernel(parameters),
  _base_name(getParam<std::string>("base_name")),
  _component(getParam<std::string>("component")),
  _stress(getMaterialPropertyByName<std::vector<Real> >(_base_name + "_stress")),
  _Jacobian_mult(getMaterialPropertyByName<std::vector<Real> >(_base_name + "_Jacobian_mult"))



{}

Real ElasticKernel2D::computeQpResidual()
{
  int _comp;
  int dim = 2;
  double sum=0.0;
  unsigned int i;

  if (_component == "x" ) _comp = 0;
  if (_component == "y" ) _comp = 1;

  for (i=0;i<dim;i++) sum += _stress[_qp][_comp*dim+i]*_grad_test[_i][_qp](i);



//  if ((_qp==0)&&(_current_elem->id()==5)) printf("This is residual comp=%d elem=%d qp=%d for test function=%d  SUM =%f \n",_comp, _current_elem->id(),_qp,_i,sum);




  return sum;
}

Real ElasticKernel2D::computeQpJacobian()
{
 unsigned int i, j, k, l;
 int dim = 2;
 int pos;
//generate final derivative with fouth order tensor
  int _comp;
 if (_component == "x" ) _comp = 0;
 if (_component == "y" ) _comp = 1;



    // d(stress_ij*d(test)/dx_j)/du_k = d(C_ijmn*du_m/dx_n dtest/dx_j)/du_k (which is nonzero for m=k)
       Real the_sum = 0.0;
       i=_comp;
       k=_comp;
       for (j = 0; j < dim; ++j){
       for (l = 0; l < dim; ++l){
            pos = i*(dim*dim*dim)+j*(dim*dim)+k*(dim)+l;
       the_sum += _Jacobian_mult[_qp][pos] * _grad_phi[_j][_qp](l) * _grad_test[_i][_qp](j);}}

       /*
       i=_comp;
       l=_comp;
       for (j = 0; j < dim; ++j){
       for (k = 0; k < dim; ++k){
            pos = i*(dim*dim*dim)+j*(dim*dim)+k*(dim)+l;
       the_sum += 0.5*_Jacobian_mult[_qp][pos] * _grad_phi[_j][_qp](k) * _grad_test[_i][_qp](j);}}
*/


//if ((_qp==0)&&(_current_elem->id()==5)) printf("This is diagonal jacobian for comp=%d elem=%d qp=%d for test function=%d respect phi_function=%d SUM =%f \n",_comp, _current_elem->id(),_qp,_i,_j, the_sum);

       return the_sum;
}

Real ElasticKernel2D::computeQpOffDiagJacobian(unsigned int jvar)
{

Real the_sum = 0.0;
    unsigned int i, j, k, l;
    int dim = 2;
    int pos;
   //generate final derivative with fouth order tensor
     int _comp, _comp_c;
    if (_component == "x" ) {_comp = 0;_comp_c=1;}
    if (_component == "y" ) {_comp = 1;_comp_c=0;}


    int _coupled = coupled("coupled");//check if this is the right component
    if (jvar==_coupled)
    {

       // d(stress_ij*d(test)/dx_j)/du_k = d(C_ijmn*du_m/dx_n dtest/dx_j)/du_k (which is nonzero for m=k)
          i=_comp;
          k=_comp_c;
          for (j = 0; j < dim; ++j){
          for (l = 0; l < dim; ++l){
               pos = i*(dim*dim*dim)+j*(dim*dim)+k*(dim)+l;
          the_sum += _Jacobian_mult[_qp][pos] * _grad_phi[_j][_qp](l) * _grad_test[_i][_qp](j);}}

    }


    //if ((_qp==0)&&(_current_elem->id()==5)) printf("This is var=%d jvar=%d offdiag jacobian for comp=%d elem=%d qp=%d for test function=%d respect phi_function=%d SUM =%f \n",_var.number(),jvar, _comp, _current_elem->id(),_qp,_i,_j, the_sum);



return the_sum;
}
