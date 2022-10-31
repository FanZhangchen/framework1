#include "SSDSourceMaterial.h"

registerMooseObject("framework1App", SSDSourceMaterial);

InputParameters
SSDSourceMaterial::validParams()
{
  InputParameters params = Material::validParams();

  // Parameter for radius of the spheres used to interpolate permeability.
  params.addClassDescription("Compute the evolution equation of SSD density");
  params.addParam<Real>("initial_rhos", 1.0,"The initial condition of SSD density");
  params.addParam<Real>("source", 6.7, "The number of source term");
  params.addRequiredCoupledVar("rhog", "variable for SSD density");
  return params;
}

SSDSourceMaterial::SSDSourceMaterial(const InputParameters & parameters)
  : DerivativeMaterialInterface<Material>(parameters),

    // Get the parameters of the initial condition of SSD density from the input file
    _initial_rhos(getParam<Real>("initial_rhos")),

    // Get the parameters of the coupled value of GND density
    _rhog(coupledValue("rhog")),
    _grad_rhog(coupledGradient("rhog")),

    // Declare the current value and older value of SSD density
    _rhos(declareADProperty<Real>("rhos")),
    _rhos_old(getMaterialPropertyOld<Real>("rhos")),

    // Declare the value of source term
    _source(getParam<Real>("source"))
{
}

void
SSDSourceMaterial::initQpStatefulProperties()
{
  _rhos[_qp] = _initial_rhos;
}

void
SSDSourceMaterial::computeQpProperties()
{
  _rhos[_qp] = _rhos_old[_qp] + 
  _source * std::sqrt(std::abs(_rhog[_qp]) + _rhos_old[_qp]) * std::abs(std::abs(_rhog[_qp]) + _rhos_old[_qp] - _grad_rhog[_qp](0)) *_dt;
}
