#!/bin/sh

#SBATCH --job-name=MechanicalFailure
#SBATCH --output=MechanicalFailure_output.txt
#SBATCH --error=MehcanicalFailure_error.txt
#SBATCH --ntasks=8
#SBATCH -N 1
#SBATCH --time=24:00:00



mpiexec ./sheep-opt -i input/4branch.i
