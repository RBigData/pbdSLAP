\name{pbdSLAP-package}
\alias{pbdSLAP-package}
\alias{pbdSLAP}
\docType{package}
\title{Programming with Big Data -- Scalable Linear Algebra Packages}
\description{
  pbdSLAP utilizes scalable linear algebra packages mainly
  including BLACS, PBLAS, and ScaLAPACK in double precision via
  pbdMPI based on ScaLAPACK version 2.0.2.
}
\details{
  This package requires \pkg{pbdMPI} and MPI system. The main purpose of
  \pkg{pbdSLAP} is to provide several scalable linear algebra packages
  containing double precision libraries for \pkg{pbdDMAC} or other useful
  packages.
}
\references{
  Programming with Big Data in R Website:
  \url{https://pbdr.org/}

  ScaLAPACK Website:
  \url{https://netlib.org/scalapack/}

  ScaLAPACK Block Cyclic Data Distribution Website:
  \url{https://icl.utk.edu/lapack-forum/viewtopic.php\%3ff=5&t=4922.html}
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
\keyword{package}

