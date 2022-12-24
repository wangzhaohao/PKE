#include "PKEODE.h"
registerMooseObject("PKEApp", PKEODE);

InputParameters
PKEODE::validParams()
{
  InputParameters params = ODEKernel::validParams();
  params.addRequiredParam<std::vector<std::string>>("DNP_variables_names", "the names of the DNP variable this PKEODE will have");
  params.addParam<Real>("rho", "the reacivity");
  params.addParam<Real>("beta", "the DNP frations");
  params.addParam<Real>("lambda", "the DNP decay constants");
  params.addParam<Real>("n_delayed_groups", "the num of delayed groups");
  return params;
}

PKEODE::PKEODE(const InputParameters & parameters):
  ODEKernel(parameters),
  _rho(getParam<Real>("rho")),
  _beta(getParam<Real>("beta")),
  _lambda(getParam<Real>("lambda")),
  _Lambda(_lambda),
  _n_delayed_groups(getParam<Real>("n_delayed_groups")),
  _DNP_variables_names(getParam<std::vector<std::string>>("DNP_variables_names"))
{
  unsigned int num_names = _DNP_variables_names.size();
  if (_n_delayed_groups != num_names)
    mooseError("Numeber of DNP variable must match of number of delayed groups");
  _n_delayed_groups = num_names;

  _DNP_variables.resize(num_names);
  
  for(unsigned int i = 0; i < _n_delayed_groups; i++)
    _DNP_variables[i] = &coupledValue(_DNP_variables_names[i]);
}

Real
PKEODE::computeQpResidual()
{
  return (_rho-_beta)/_Lambda*_u[_i]+_lambda*_c[_i];
}

Real
PKEODE::computeqpJacobian()
{
  return (_rho-_beta)/_Lambda;
}
  
