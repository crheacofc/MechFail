#include "YoungsModulusBasic.h"

#include <algorithm>
template<>
InputParameters validParams<YoungsModulusBasic>()
{
    InputParameters params = validParams<InitialCondition>();
    params.addRequiredParam<Real>("Youngs_Modulus", "Average youngs modulus to be used");
    params.addParam<Real>("val","Values of Youngs Modulus");
    return params;
}

YoungsModulusBasic::YoungsModulusBasic(const InputParameters & parameters) :
InitialCondition(parameters),
_Youngs_Modulus(getParam<Real>("Youngs_Modulus"))
{}


Real
YoungsModulusBasic::value(const Point & p)
{

  // Apply random value to youngs modulus in inner ring
  double M = _Youngs_Modulus-.001;
  double N = _Youngs_Modulus+.001;
  double _val;
  _val = M + rand() / (RAND_MAX / (N - M ));
  std::cout<<_val<<std::endl;
  return  _val;


}
