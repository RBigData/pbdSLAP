# pbdSLAP

* **License:** [![License](http://img.shields.io/badge/license-MPL%202-orange.svg?style=flat)](https://www.mozilla.org/MPL/2.0/)
* **Download:** [![Download](http://cranlogs.r-pkg.org/badges/pbdSLAP)](https://cran.r-project.org/package=pbdSLAP)
* **Status:** [![Build Status](https://travis-ci.org/snoweye/pbdSLAP.png)](https://travis-ci.org/snoweye/pbdSLAP)
* **Author:** See section below.


pbdSLAP provides scalable linear algebra packages including BLACS, PBLAS, and
ScaLAPACK via pbdMPI based on ScaLAPACK version 2.0.2.



## Installation

pbdSLAP requires

- R version 2.14.0 or higher with pbdMPI installed.
- SUN HPC 8.2.1 (OpenMPI) for Solaris.
- OpenMPI for Linux.
- OpenMPI for Mac OS X.
- MS-MPI for Windows.

For installing pbdSLAP, 

- see "INSTALL" for Solaris, Linux and Mac OS.
- see "INSTALL.win.*" for Windows.

More information about pbdSLAP can be found in

1. pbdSLAP vignette at `pbdSLAP/inst/doc/pbdSLAP-guide.pdf`.
2. http://r-pbd.org/



## Authors

pbdSLAP is authored and maintained by the pbdR core team:
* Wei-Chen Chen
* Drew Schmidt
* George Ostrouchov
* Pragneshkumar Patel

With additional contributions from:
* Brian Ripley (Solaris & Mac)

For copyrights on the shipped ScaLAPACK code, see
`pbdSLAP/inst/ScaLAPACK_LICENSE.txt`.

