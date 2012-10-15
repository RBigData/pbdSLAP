### Lastest load into a package.

.First.lib <- function(lib, pkg){
  if(! is.loaded("spmd_initialize", PACKAGE = "pbdMPI")){
    library.dynam("pbdMPI", "pbdMPI", lib)
    if(pbdMPI:::comm.is.null(0L) == -1){
      pbdMPI:::init()
    }
  }

  library.dynam("pbdSLAP", pkg, lib)
} # End of .First.lib().

.Last.lib <- function(libpath){
  pbdSLAP:::slap.finalize()
  library.dynam.unload("pbdSLAP", libpath)
} # End of .Last.lib().
