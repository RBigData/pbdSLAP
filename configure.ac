dnl Process this file with autoconf to produce a configure script
AC_INIT(DESCRIPTION)

dnl Check chmod
chmod +x ./inst/test_intface/00_make.*

dnl Determine R_HOME.
: ${R_HOME=‘R RHOME‘}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
R_SCMD="${R_HOME}/bin/Rscript -e"


dnl Check other CC.
if test "X${CC}" = "X"; then
  CC=`"${R_HOME}/bin/R" CMD config CC`
  if test "X$CC" = "X" ; then
    # Our best guess...
    CC="gcc -std=gnu99"
  fi
fi
AC_PROG_CC


dnl Set EXT_LDFLAGS, otherwise default LDFLAGS, OBJS, and LIBS will be set.
AC_ARG_VAR(EXT_LDFLAGS, [ external linking flags of external libraries ])
AS_VAR_SET_IF(EXT_LDFLAGS, [], [ AS_VAR_SET(EXT_LDFLAGS, "") ])
if test "X$EXT_LDFLAGS" = "X" ; then
  EXT_LDFLAGS="\$(LAPACK_LIBS) \$(BLAS_LIBS)"
  EXT_OBJS="\$(R_SLAP)"
  EXT_LIBS="userLibrary"
else
  EXT_OBJS=""
  EXT_LIBS=""
fi

dnl C and Fortran interface
dnl CDEFS should be one of "-DAdd_", "-DNoChange", "-Df77IsF2C", or "-DUpCase"
dnl which is determined by "../inst/test_intface/00_make.sh".
dnl For GNU make, gcc, and gfortran, the default is "-DAdd_".
AC_ARG_VAR(CDEFS, [ intface of C and Fortran ])
AS_VAR_SET_IF(CDEFS, [], [ AS_VAR_SET(CDEFS, "") ])
if test "X$CDEFS" = "X" ; then
  CDEFS=-D`${R_SCMD} "invisible(system('cd ./inst/test_intface/;./00_make.sh'))"`
  CDEFS_CHECK=TRUE
fi
if test "X$CDEFS" = "X" ; then
  CDEFS=-DAdd_
  CDEFS_CHECK=FALSE
fi

dnl pbdMPI
SPMD_CPPFLAGS=`${R_SCMD} "source('./R/get_conf.r');get.conf('PKG_CPPFLAGS','"${R_ARCH}"')"`
SPMD_LDFLAGS=`${R_SCMD} "source('./R/get_conf.r');get.conf('PKG_LIBS','"${R_ARCH}"')"`


dnl Report
echo " "
echo "****************** Results of pbdSLAP package configure *****************"
echo " "
echo ">> CC = ${CC}"
echo ">> FC = ${FC}"
echo ">> EXT_LDFLAGS = ${EXT_LDFLAGS}"
echo ">> EXT_OBJS = ${EXT_OBJS}"
echo ">> EXT_LIBS = ${EXT_LIBS}"
echo ">> CDEFS = ${CDEFS}"
echo ">> CDEFS_CHECK = ${CDEFS_CHECK}"
echo ">> SPMD_CPPFLAGS = ${SPMD_CPPFLAGS}"
echo ">> SPMD_LDFLAGS = ${SPMD_LDFLAGS}"
echo " "
echo "*************************************************************************"
echo " "


dnl Start to substitute templates
AC_SUBST(CC)
AC_SUBST(EXT_LDFLAGS)
AC_SUBST(EXT_OBJS)
AC_SUBST(EXT_LIBS)
AC_SUBST(CDEFS)
AC_SUBST(CDEFS_CHECK)
AC_SUBST(SPMD_CPPFLAGS)
AC_SUBST(SPMD_LDFLAGS)
AC_OUTPUT(src/Makevars)
