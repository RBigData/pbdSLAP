\name{SLAP Grid Information}
\alias{slap.init.grid}
\alias{slap.exit.grid}
\alias{slap.finalize}
\title{SLAP Grid}
\description{
  These functions initializes a grid of \code{pbdSLAP}, assigns the
  information to a global object, and free the grid.
}
\usage{
  slap.init.grid(nprow, npcol = 1, ictxt = 0)
  slap.exit.grid(ictxt)
  slap.finalize(quit.mpi = FALSE)
}
\arguments{
  \item{nprow}{number of row processors.}
  \item{npcol}{number of column processors.}
  \item{ictxt}{the grid id}
  \item{quit.mpi}{if finalize MPI.}
}
\details{
  This function arranges all processors in a (nprow * npcol) grid and
  the grid will map the big data matrix.
}
\value{
  \code{slap.init.grid} assigns a global object \code{.__grid_info_0} for
  \code{ictxt = 0} containing the grid information. \code{slap.exit.grid}
  free the grid. \code{slap.finalize} free all memory.
}
\references{
  Programming with Big Data in R Website:
  \url{http://r-pbd.org/}

  ScaLAPACK Website:
  \url{http://www.netlib.org/scalapack/}

  ScaLAPACK Block Cyclic Data Distribution Website:
  \url{http://acts.nersc.gov/scalapack/hands-on/datadist.html}
}
\author{
  Wei-Chen Chen \email{wccsnow@gmail.com}, Drew Schmidt,
  George Ostrouchov, and Pragneshkumar Patel.
}
\examples{
\dontrun{
### Under command mode, run the demo with 2 processors by
### (Use Rscript.exe for windows system)

mpiexec -np 2 Rscript -e "demo(gridinfo,'pbdSLAP',ask=F,echo=F)"
}
}
\keyword{programming}
