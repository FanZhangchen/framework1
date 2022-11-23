#include "AbsGNDDensity.h"

#include "metaphysicl/raw_type.h"

registerMooseObject("framework1App", AbsGNDDensity);

InputParameters
AbsGNDDensity::validParams()
{
  InputParameters params = AuxKernel::validParams();

  // Add a "coupling paramater" to get a variable from the input file.
  params.addCoupledVar("rhog", "The gnd density.");

  return params;
}

AbsGNDDensity::AbsGNDDensity(const InputParameters & parameters)
  : AuxKernel(parameters),

    // Get the gradient of the variable
    _rhog(coupledValue("rhog"))
{
}

Real
AbsGNDDensity::computeValue()
{
  // Access the gradient of the pressure at this quadrature point, then pull out the "component" of
  // it requested (x, y or z). Note, that getting a particular component of a gradient is done using
  // the parenthesis operator.
  return std::abs(_rhog[_qp]);
}
