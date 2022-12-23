#include "PKEApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
PKEApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  return params;
}

PKEApp::PKEApp(InputParameters parameters) : MooseApp(parameters)
{
  PKEApp::registerAll(_factory, _action_factory, _syntax);
}

PKEApp::~PKEApp() {}

void
PKEApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"PKEApp"});
  Registry::registerActionsTo(af, {"PKEApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
PKEApp::registerApps()
{
  registerApp(PKEApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
PKEApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  PKEApp::registerAll(f, af, s);
}
extern "C" void
PKEApp__registerApps()
{
  PKEApp::registerApps();
}
