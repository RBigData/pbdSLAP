### SHELL> mpiexec -np 4 Rscript --vanilla [...].r

library(pbdMPI, quiet = TRUE)
library(pbdSLAP, quiet = TRUE)
init()

slap.init.grid(2, 2, ictxt = 0)
comm.print(.pbdSLAPEnv$.__grid_info_0, all.rank = TRUE)
slap.exit.grid(0)

slap.init.grid(2, 3, ictxt = 1)
comm.print(.pbdSLAPEnv$.__grid_info_1, all.rank = TRUE)
slap.exit.grid(1)

slap.finalize()
finalize()
