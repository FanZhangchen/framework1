#pragma once

#include "ADKernel.h"

class DislocationDensityFlux : public ADKernel
{
public:
  static InputParameters validParams();

  DislocationDensityFlux(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

  const Real & _backstress;

  const ADMaterialProperty<Real> & _rhos;
};
