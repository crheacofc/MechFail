[Mesh]
file = mesh/MechFrac.e
boundary_id = '1 2'
boundary_name = 'outside inside'
[]

[Variables]
[./disp_x]
    order = FIRST
    family = LAGRANGE
  [../]
  [./disp_y]
    order = FIRST
    family = LAGRANGE
  [../]
[./d]
    order = FIRST
    family = LAGRANGE
initial_condition = 0.0
scaling = 1e5
  [../]
[./phi]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
[]

[AuxVariables]
[./YoungsModulus]
	order = FIRST
	family = LAGRANGE
[../]
 [./d_history]
 order = FIRST
 family = LAGRANGE
 [../]
[./phi_ini]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0.0
  [../]
[./frac_ini]
    order = FIRST
    family = LAGRANGE
  [../]
[./elastic_tensile]
order = CONSTANT
family = MONOMIAL
[../]
[./elastic_energyd]
order = CONSTANT
family = MONOMIAL
[../]
[./elastic_energyd2]
order = CONSTANT
family = MONOMIAL
[../]
[./elastic_tensile_raw]
order = CONSTANT
family = MONOMIAL
[../]
[./elastic_tensile_raw_history]
order = CONSTANT
family = MONOMIAL
[../]
[./elastic_compressive_raw]
order = CONSTANT
family = MONOMIAL
[../]
[./elastic_compressive]
order = CONSTANT
family = MONOMIAL
[../]
[./trace]
order = CONSTANT
family = MONOMIAL
[../]
[]


[AuxKernels]
 [./d_history_kernel]
 type = HistoryVariableAux
 variable = d_history
 damage = d
 [../]
[./phiinikernel]
type = InitialFieldAux
variable = phi_ini
[../]
[./elastic_tensile]
type = MaterialRealAux
variable = elastic_tensile
property = praft_energy_tensile
[../]
[./elastic_tensiled]
type = MaterialRealAux
variable = elastic_energyd
property = praft_d_energy_tensile_dc
[../]
[./elastic_tensiled2]
type = MaterialRealAux
variable = elastic_energyd2
property = praft_d2_energy_tensile_dc2
[../]
[./elastic_tensile_raw]
type = MaterialRealAux
variable = elastic_tensile_raw
property = praft_energy_tensile_raw
[../]
[./elastic_tensile_raw_history]
type = MaterialRealAux
variable = elastic_tensile_raw_history
property = praft_energy_tensile_raw_history
[../]
[./elastic_compressive_raw]
type = MaterialRealAux
variable = elastic_compressive_raw
property = praft_energy_compressive_raw
[../]
[./elastic_compressive]
type = MaterialRealAux
variable = elastic_compressive
property = praft_energy_compressive
[../]
[./trace]
type = MaterialRealAux
variable = trace
property = praft_trace_st
[../]
[]



[Kernels]
      [./x]
    type = ElasticKernel2D
    variable = 'disp_x'
    component = x
    coupled = disp_y
    base_name = praft
  [../]
    [./y]
     type = ElasticKernel2D
     variable = 'disp_y'
     component = y
     coupled = disp_x
     base_name = praft
 [../]
[./interface]
    type = ACInterfaceFrac
    variable = d
    mob_name = L
    toughness_name = Gc
    args = 'phi'
    kappa_name = lambda
    variable_L = false
    variable_Gc = true
    #use_displaced_mesh = false
  [../]
  [./bulk]
    type = AllenCahn
    variable = d
    mob_name = L
    args = 'phi'
    f_name = f_couple
    #use_displaced_mesh = false
 [../]

[./phi_rate]
    type = TimeDerivative
    variable = phi
    #use_displaced_mesh = true
[../]

[]


[ICs]
[./frac_ini]
variable = frac_ini
type=PhasefieldShapes
epsilon=0.0
shapes='circle'
centers_tips ='0.0 0.0 0.0 0.0'
[../]
[./youngsmodulusinit]
variable = YoungsModulus
type = readinic
dataFile = '/home/crhea/Dropbox/Research/Kidney-Stone/sheep/mesh/MechFrac_E.txt'
[../]
[]


[Materials]
[./constant]
  type = GenericConstantMaterial
    prop_names  = 'lambda'
    prop_values ='0.01'
    block = 1
  [../]
  
[./mobility]
    type = DerivativeParsedMaterial
    block = 1
    f_name = L
    args = 'phi'
    constant_names = 'constant viscosity diameter'
    constant_expressions ='0.01 1 1'
    #function = 'constant*(1-phi)/(viscosity*diameter)'
    function = '1'
    enable_jit = true
    derivative_order = 2
[../]

[./toughness]
    type = DerivativeParsedMaterial
    block = 1
    f_name = Gc
    args = 'd_history'
    constant_names = 'constant viscosity diameter'
    constant_expressions ='1e-05 1 1'
    function = 'constant*(1-30/70*d_history)'
    enable_jit = true
    derivative_order = 2
[../]
[./free_energy_chemical]
    type = DerivativeParsedMaterial
    block = 1
    f_name = f_bulk
    args = 'd d_history'
    material_property_names = 'Gc(d_history)'
    constant_names = 'lambda constant1'
    constant_expressions ='0.01 0.5'
    function = 'Gc*d^2/lambda*constant1'
    enable_jit = true
    derivative_order = 2
[../]

[./compfactor]
    type = DerivativeParsedMaterial
    block = 1
    f_name = fcomp
    args = 'phi'
    constant_names = 'a b epsilon threshold'
    constant_expressions ='1 10 0.01 0.87'
    #function = 'a+b*(1+tanh((phi-threshold)/epsilon))'   
    function = 'a'
    enable_jit = true
    derivative_order = 2
[../]
[./tensfactor]
    type = DerivativeParsedMaterial
    block = 1
    f_name = ftens
    #args = 'phi'
    constant_names = 'constant'
    constant_expressions ='1'
    function = 'constant'
    enable_jit = true
    derivative_order = 2
[../]
[./small_strain_total]
    type = ComputeSmallStrain
    block = 1
    base_name = praft
    displacements = 'disp_x disp_y'
  [../]
[./elasticity2D]
    type = ElasticMaterial2DFracHistoryYM
    block = 1
    base_name = praft
    youngs_modulus = YoungsModulus
    poissons_ratio = 0.22
    eta = 1.0e-6  #numerical parameter to prevent zero in stiffness matrix
    damage = d
    d_history = d_history
    compfactor_name = fcomp
    tensfactor_name = ftens
split = true
irrev = false
  [../]
[./elasticity2Denergy]
    type = ElasticEnergyMaterial2DFrac
    block = 1
    base_name = praft
    f_name = f_tensile
    args= 'd'
    derivative_order = 2
  [../]
 [./sum_energy]
    type = DerivativeSumMaterial
    block = 1
    f_name = f_couple
    sum_materials = 'f_bulk f_tensile'
  args = 'd phi'
    derivative_order = 2
[../]

[./pressure]
    type = SurfactantPressure2DFrac
    block = 1
    base_name = praft
    concentration = 'd_history'
    concentration_ini = 'frac_ini'
    irrev = true
    staggered = true
    const = 1
    pres_type = 1
    loadingfunction = bc_func
  [../]
[]

[Functions]
[./bc_func]
    type = ParsedFunction
    value = 0.1
 [../]
[]


[BCs]
  [./out_x]
    type = DirichletBC
  boundary = outside
    variable = 'disp_x'
    value = 0.0
  [../]
  [./out_y]
    type = DirichletBC
    boundary = outside
    variable = 'disp_y'
    value = 0.0
  [../]
  [./Pressure]
    [./central]
      boundary = inside
      factor = 1
      function = bc_func
      disp_x = disp_x
      disp_y = disp_y
    [../]
  [../]

[]



[Preconditioning]

   [./SMP]
	type = SMP
	full = true
   [../]
[]

[Executioner]
  type = Transient
  scheme = 'bdf2'
  #solve_type = 'FD'
  solve_type = 'Newton'
  #solve_type = 'PJFNK'







petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
petsc_options_value = 'asm      100                  preonly       lu           10'


#petsc_options='-ksp_monitor_singular_value'
petsc_options='-ksp_monitor_singular_value -ksp_converged_reason -ksp_monitor_true_residual'

  #petsc_options= '-ksp_monitor_singular_value -snes_ksp_ew -snes_atol 1.0e-2 --ksp_type #gmres -snes_linesearch_monitor true -#snes_linesearch_maxstep 1e+12  -#snes_linesearch_minlambda 1e-15  -snes_linesearch_rtol 1e-08 -snes_linesearch_atol 1e-15 #-#snes_linesearch_ltol 1e-08 -snes_linesearch_max_it 40 -snes_stol 1e-50 -snes_stol 1e-06  -snes_rtol 1e-06 '



  #l_max_its = 40
  #l_tol = 1.0e-6
  #nl_max_its = 1000
  #nl_rel_tol = 1e-5

  #l_tol = 1.0e-4
  nl_rel_tol = 1.0e-6
  nl_abs_tol = 1.0e-8


     start_time = 0.0
     end_time = 0.1
     dt = 0.001






  [Debug]
    show_var_residual_norms = true
  []



[Outputs]
  exodus = true
  interval = 2
  csv = true
  file_base = outputtest
[]
