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
\tabular{ll}{
  Package: \tab pbdSLAP\cr
  Type: \tab Package\cr
%  Version: \tab 0.1-2\cr
%  Date: \tab 2010-02-18\cr
  License: \tab GPL\cr
  LazyLoad: \tab yes\cr
}

  This package requires \pkg{pbdMPI} and MPI system. The main purpose of
  \pkg{pbdSLAP} is to provide several scalable linear algebra packages
  containing double precision libraries for \pkg{pbdDMAC} or other useful
  packages.
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
\keyword{package}

