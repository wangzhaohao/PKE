//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "PKETestApp.h"
#include "PKEApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
PKETestApp::validParams()
{
  InputParameters params = PKEApp::validParams();
  return params;
}

PKETestApp::PKETestApp(InputParameters parameters) : MooseApp(parameters)
{
  PKETestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

PKETestApp::~PKETestApp() {}

void
PKETestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  PKEApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"PKETestApp"});
    Registry::registerActionsTo(af, {"PKETestApp"});
  }
}

void
PKETestApp::registerApps()
{
  registerApp(PKEApp);
  registerApp(PKETestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
PKETestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  PKETestApp::registerAll(f, af, s);
}
extern "C" void
PKETestApp__registerApps()
{
  PKETestApp::registerApps();
}
