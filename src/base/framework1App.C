#include "framework1App.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
framework1App::validParams()
{
  InputParameters params = MooseApp::validParams();

  return params;
}

framework1App::framework1App(InputParameters parameters) : MooseApp(parameters)
{
  framework1App::registerAll(_factory, _action_factory, _syntax);
}

framework1App::~framework1App() {}

void
framework1App::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"framework1App"});
  Registry::registerActionsTo(af, {"framework1App"});

  /* register custom execute flags, action syntax, etc. here */
}

void
framework1App::registerApps()
{
  registerApp(framework1App);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
framework1App__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  framework1App::registerAll(f, af, s);
}
extern "C" void
framework1App__registerApps()
{
  framework1App::registerApps();
}
