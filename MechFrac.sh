#!/bin/sh

#SBATCH --job-name=MechanicalFailure
#SBATCH --output=MechanicalFailure_output.txt
#SBATCH --error=MechanicalFailure_error.txt
#SBATCH --ntasks=1
#SBATCH -N 1
#SBATCH --time=24:00:00



mpiexec ./sheep-opt -i input/Draft2/crackpressure/fixedBoundary/nonref.i
