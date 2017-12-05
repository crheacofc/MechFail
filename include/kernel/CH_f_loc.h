/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef CH_F_LOC_H
#define CH_F_LOC_H

#include "CHBulk.h"

//Forward Declarations
class CH_f_loc;

template<>
InputParameters validParams<CH_f_loc>();

/**Cahn-Hilliard Kernel implementing the free energy f = 1/2c^2(1-c^2), such that grad df/dc = (3 c^2 -1) grad_c.
 * Most of the Cahn-Hilliard equation is implemented in CHBulk and CHInterface.  This kernel inherits from CHBulk
 * and implements a simple polynomial double well to model spinodal decomposition.
**/

class CH_f_loc : public CHBulk<Real>
{
public:
  CH_f_loc(const InputParameters & parameters);

protected:
  virtual RealGradient computeGradDFDCons(PFFunctionType type);
};

#endif //CH_F_LOC_H
