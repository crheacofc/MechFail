#ifndef YOUNGSMODULUSBASIC_H
#define YOUNGSMODULUSBASIC_H

// MOOSE Includes
#include "InitialCondition.h"
#include <vector>

// Forward Declarations
class YoungsModulusBasic;
template<>
InputParameters validParams<YoungsModulusBasic>();


class YoungsModulusBasic : public InitialCondition
{
public:
    YoungsModulusBasic(const InputParameters & parameters);

    virtual Real value(const Point & p);
private:
    Real _Youngs_Modulus;

};

#endif //YOUNGSMODULUSBASIC_H
