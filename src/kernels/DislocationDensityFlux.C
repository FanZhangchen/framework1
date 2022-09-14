#include "DislocationDensityFlux.h"

registerMooseObject("framework1App", DislocationDensityFlux);

InputParameters
DislocationDensityFlux::validParams()
{
  auto params = ADKernel::validParams();
  params.addParam<Real>("backstress", 1.0, "Back stress' parameter");
  params.addClassDescription("The time derivative operator with the weak form of $(\\psi_i, "
                             "\\frac{\\partial rhog}{\\partial t})$.");
  return params;
}

DislocationDensityFlux::DislocationDensityFlux(const InputParameters & parameters)
  : ADKernel(parameters),
    _backstress(getParam<Real>("backstress")),
    _rhos(getADMaterialProperty<Real>("rhos"))
{
}

ADReal
DislocationDensityFlux::computeQpResidual()
{
  return -_grad_test[_i][_qp](0)*(_rhos[_qp] + std::abs(_u[_qp])) 
    + _backstress * _grad_u[_qp]*_grad_test[_i][_qp];
}
