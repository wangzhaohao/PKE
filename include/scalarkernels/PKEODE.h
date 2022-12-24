#pragma once
#include "ODEKernel.h"

/**
 * PKE: \frac{\rho-\beta}{\Lambda}n+\sum_{i=1}^{I}\lambda_ic_i
 */
class PKEODE : public ODEKernel
{
  public:
    PKEODE(const InputParameters & parameters);
    static InputParameters validParams();
  protected:
    virtual Real computeQpResidual() override;
    virtual Real computeQpJacobian() override;

    const Real _rho;
    const Real _beta;
    Real _Lambda;

    const Real _lambda;
    const Real _n_delayed_groups;
    const std::vector<std::string> & _DNP_variables_names;

    std::vector<VariableValue> _DNP_variables;
};
