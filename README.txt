You’ll need SLURM installed to manage building and running of programs. This is a simple MPI program, which can multiply two square 512x512 matrices on 1,4,16 and 64 cores.
To build the project, simply run
sbatch mpi-build.sbatch  
To run the project, you should have the compiled file a.out in your directory.
To run the compiled file on 1,4,16 and 64 cores type
sbatch mpi-run-all.sbatch
and you should see the outputs for 1,4,16 and 64 cores.  Notice the speed up times for 4 and 16 cores, but a bit of a slowdown for communication on the 64 cores. You may see a bigger speed up on 64 cores depending on how many cores you have on one node. On UWM’s HPC peregrine cluster, it’s 16 core so the communication time is more expensive between all of the nodes. If the matrix was much much larger, the communication time would be much smaller than the computation time, and you would still see a speed up for the 64 cores.  Here is the output for the 512 x 512 square matrix.
--------------------------------------------------------------------------
WARNING: An invalid value was given for btl_tcp_if_exclude.  This
value will be ignored.

  Local host: compute-002.local
  Value:      127.0.0.1/8
  Message:    Did not find interface matching this subnet
--------------------------------------------------------------------------
Num procs 1 1.804688 with 1 processors
c[47][416]=142
c[444][196]=127
c[272][208]=115
c[180][510]=136
c[332][478]=139
c[308][83]=129
c[274][89]=129
c[112][295]=119
c[123][220]=119
c[412][203]=133
...skipping...
--------------------------------------------------------------------------
WARNING: An invalid value was given for btl_tcp_if_exclude.  This
value will be ignored.

  Local host: compute-002.local
  Value:      127.0.0.1/8
  Message:    Did not find interface matching this subnet
--------------------------------------------------------------------------
Num procs 4 0.476562 with 4 processors
c[47][416]=142
c[444][196]=127
c[272][208]=115
c[180][510]=136
c[332][478]=139
c[308][83]=129
c[274][89]=129
c[112][295]=119
c[123][220]=119
c[412][203]=133
[compute-002.local:51964] 3 more processes have sent help message help-mpi-btl-tcp.txt / invalid if_inexclude
[compute-002.local:51964] Set MCA parameter "orte_base_help_aggregate" to 0 to see all help / error messages
...skipping...
--------------------------------------------------------------------------
WARNING: An invalid value was given for btl_tcp_if_exclude.  This
value will be ignored.

  Local host: compute-002.local
  Value:      127.0.0.1/8
  Message:    Did not find interface matching this subnet
--------------------------------------------------------------------------
Num procs 16 0.210938 with 16 processors
c[47][416]=142
c[444][196]=127
c[272][208]=115
c[180][510]=136
c[332][478]=139
c[308][83]=129
c[274][89]=129
c[112][295]=119
c[123][220]=119
c[412][203]=133
[compute-002.local:51971] 15 more processes have sent help message help-mpi-btl-tcp.txt / invalid if_inexclude
[compute-002.local:51971] Set MCA parameter "orte_base_help_aggregate" to 0 to see all help / error messages
...skipping...
--------------------------------------------------------------------------
WARNING: An invalid value was given for btl_tcp_if_exclude.  This
value will be ignored.

  Local host: compute-002.local
  Value:      127.0.0.1/8
  Message:    Did not find interface matching this subnet
--------------------------------------------------------------------------
Num procs 64 0.492188 with 64 processors
c[47][416]=142
c[444][196]=127
c[272][208]=115
c[180][510]=136
c[332][478]=139
c[308][83]=129
c[274][89]=129
c[112][295]=119
c[123][220]=119
c[412][203]=133
[compute-002.local:51984] 63 more processes have sent help message help-mpi-btl-tcp.txt / invalid if_inexclude
[compute-002.local:51984] Set MCA parameter "orte_base_help_aggregate" to 0 to see all help / error messages












