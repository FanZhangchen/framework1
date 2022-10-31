#include "SSDSinkMaterial.h"

registerMooseObject("framework1App", SSDSinkMaterial);

InputParameters
SSDSinkMaterial::validParams()
{
  InputParameters params = Material::validParams();

  // Parameter for radius of the spheres used to interpolate permeability.
  params.addClassDescription("Compute the evolution equation of SSD density");
  params.addParam<Real>("initial_rhos", 1.0,"The initial condition of SSD density");
  params.addParam<Real>("sink", 6.7, "The number of sink term");
  params.addRequiredCoupledVar("rhog", "variable for SSD density");
  return params;
}

SSDSinkMaterial::SSDSinkMaterial(const InputParameters & parameters)
  : DerivativeMaterialInterface<Material>(parameters),

    // Get the parameters of the initial condition of SSD density from the input file
    _initial_rhos(getParam<Real>("initial_rhos")),

    // Get the parameters of the coupled value of GND density
    _rhog(coupledValue("rhog")),
    _grad_rhog(coupledGradient("rhog")),

    // Declare the current value and older value of SSD density
    _rhos(declareADProperty<Real>("rhos")),
    _rhos_old(getMaterialPropertyOld<Real>("rhos")),

    // Declare the value of sink term
    _sink(getParam<Real>("sink"))
{
}

void
SSDSinkMaterial::initQpStatefulProperties()
{
  _rhos[_qp] = _initial_rhos;
}

void
SSDSinkMaterial::computeQpProperties()
{
  _rhos[_qp] = _rhos_old[_qp] - _sink *
  (std::abs(_rhog[_qp])+_rhos_old[_qp]) * std::abs(std::abs(_rhog[_qp]) + _rhos_old[_qp] - _grad_rhog[_qp](0)) *_dt;
}
