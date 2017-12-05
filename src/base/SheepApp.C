#include "SheepApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"
#include "LoadingFunction.h"
#include "ElasticKernel2D.h"
#include "HistoryVariableAux.h"
#include "CHInterface.h"
#include "ACInterfaceFrac.h"
#include "ElasticEnergyMaterial2DFrac.h"
#include "SurfactantPressure2DFrac.h"
#include "ElasticMaterial2DFracHistory.h"
#include "ElasticMaterial2DFracHistoryYM.h"
#include "AreaFractureAux.h"
#include "PerimeterFractureAux.h"
#include "OverIsoStress.h"
#include "PhasefieldShapes.h"
#include "ElasticMaterial2DFrac.h"
#include "ElasticMaterial2DFracYM.h"

#include "InitialFieldAux.h"
#include "PhiUpdateAux.h"
#include "YoungsModulusBasic.h"
#include "TensorMechanicsAction.h"
#include "readinic.h"

template<>
InputParameters validParams<SheepApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

SheepApp::SheepApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SheepApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SheepApp::associateSyntax(_syntax, _action_factory);
}

SheepApp::~SheepApp()
{
}

// External entry point for dynamic application loading
extern "C" void SheepApp__registerApps() { SheepApp::registerApps(); }
void
SheepApp::registerApps()
{
  registerApp(SheepApp);
}

// External entry point for dynamic object registration
extern "C" void SheepApp__registerObjects(Factory & factory) { SheepApp::registerObjects(factory); }
void
SheepApp::registerObjects(Factory & factory)
{

  registerKernel(ElasticKernel2D);

//kernels

registerKernel(ACInterfaceFrac);
registerKernel(OverIsoStress);
registerAuxKernel(HistoryVariableAux);
registerAuxKernel(InitialFieldAux);
registerKernel(PhiUpdateAux);
registerMaterial(AreaFractureAux);
registerMaterial(PerimeterFractureAux);
registerFunction(LoadingFunction);
registerMaterial(ElasticMaterial2DFrac);
registerMaterial(ElasticMaterial2DFracYM);
registerMaterial(ElasticMaterial2DFracHistory);
registerMaterial(ElasticMaterial2DFracHistoryYM);
registerMaterial(ElasticEnergyMaterial2DFrac);
registerMaterial(SurfactantPressure2DFrac);
registerInitialCondition(PhasefieldShapes);
registerBoundaryCondition(YoungsModulusBasic);
registerInitialCondition(readinic);
}

// External entry point for dynamic syntax association
extern "C" void SheepApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SheepApp::associateSyntax(syntax, action_factory); }
void
SheepApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
