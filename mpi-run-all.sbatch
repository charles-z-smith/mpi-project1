#!/bin/sh

set -e
#SBATCH --ntasks=1
#SBATCH --output=mpi-run-all

sbatch mpi-run-kcore.sbatch 1
sbatch mpi-run-kcore.sbatch 4
sbatch mpi-run-kcore.sbatch 16
sbatch mpi-run-kcore.sbatch 64

