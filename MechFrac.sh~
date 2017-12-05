#!/bin/sh

#SBATCH --job-name=lithotripsy
#SBATCH --output=lithotripsy_output.txt
#SBATCH --error=lithotripsy_error.txt
#SBATCH --ntasks=8
#SBATCH -N 1
#SBATCH --time=24:00:00



mpiexec sheep-opt -i input/4branch.i
