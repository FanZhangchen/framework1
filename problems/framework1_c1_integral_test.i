[Mesh]
  [gen]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 100
    ny = 100
  []
  [block1]
    type = SubdomainBoundingBoxGenerator
    block_id = 1
    bottom_left = '0 0 0'
    top_right = '0.5 1 0'
    input = gen
  []
  [block2]
    type = SubdomainBoundingBoxGenerator
    block_id = 2
    bottom_left = '0.5 0 0'
    top_right = '1 1 0'
    input = block1
  []
[]

[Variables]
  [rhog]
    initial_condition = 0.
  []
[]

[Kernels]
  [gnd_time_derivative]
    type = GNDTimeDerivative
    variable = rhog
  []
  [dislocation_density_flow]
    type = DislocationDensityFlux
    variable = rhog
    backstress = 1.0
  []
[]

[Materials]
  [ssd]
    type = SSDMaterial
    rhog = rhog
  []
[]

[BCs]
[]

[Executioner]
  type = Transient
  end_time = 1.0
  dt = 0.005
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Postprocessors]
  [block1]
    type = ElementIntegralVariablePostprocessor
    variable = rhog
    block = '1'
  []
  [block2]
    type = ElementIntegralVariablePostprocessor
    variable = rhog
    block = '2'
  []
[]

[VectorPostprocessors]
  [t_sampler]
    type = LineValueSampler
    variable = rhog
    start_point = '0 0.5 0'
    end_point = '1 0.5 0'
    num_points = 21
    sort_by = x
    
  []
[]

[Outputs]
  exodus = true
  [final_rhog]
    type = CSV
    file_base = rhog_distr_c1_out
    execute_on = final
  []
  [num_rhog]
    type = CSV
    file_base = rhog_num_c1_out
    show = 'block1 block2'
  []
[]