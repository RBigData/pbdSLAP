/* ---------------------------------------------------------------------
*
*  -- PBLAS auxiliary routine (version 2.0) --
*     University of Tennessee, Knoxville, Oak Ridge National Laboratory,
*     and University of California, Berkeley.
*     April 1, 1998
*
*  ---------------------------------------------------------------------
*/
/*
*  Include files
*/
#include "../pblas.h"
#include "../PBpblas.h"
#include "../PBtools.h"
#include "../PBblacs.h"
#include "../PBblas.h"
/*WCC:add to disable warnings generated by gcc-9. */
#include "../wcc_PBtools.h"

PBTYP_T * PB_Cdtypeset(void)
{
/*
*  Purpose
*  =======
*
*  PB_Cdtypeset on the first call initializes a static structure contai-
*  ning typed information and returns a pointer to it.  The  other calls
*  to this routine just returns this pointer.
*
*  -- Written on April 1, 1998 by
*     R. Clint Whaley, University of Tennessee, Knoxville 37996, USA.
*
*  ---------------------------------------------------------------------
*/
/*
*  .. Local Scalars ..
*/
   static int     setup=0;
   static PBTYP_T TypeStruct;
   static double  zero, one, negone;
/* ..
*  .. Executable Statements ..
*
*/
   if( setup ) return( &TypeStruct );

   setup = 1;

   TypeStruct.type = DREAL;
   TypeStruct.usiz = sizeof( double );
   TypeStruct.size = sizeof( double );

   zero   = ZERO;
   one    =  ONE;
   negone = -ONE;

   TypeStruct.zero      = (char *) (&zero);
   TypeStruct.one       = (char *) (&one);
   TypeStruct.negone    = (char *) (&negone);

/*WCC
   TypeStruct.Cgesd2d   = Cdgesd2d;
   TypeStruct.Cgerv2d   = Cdgerv2d;
   TypeStruct.Cgebs2d   = Cdgebs2d;
   TypeStruct.Cgebr2d   = Cdgebr2d;
   TypeStruct.Cgsum2d   = Cdgsum2d;

   TypeStruct.Fmmadd    = dmmadd_;
   TypeStruct.Fmmcadd   = dmmcadd_;
   TypeStruct.Fmmtadd   = dmmtadd_;
   TypeStruct.Fmmtcadd  = dmmtcadd_;
   TypeStruct.Fmmdda    = dmmdda_;
   TypeStruct.Fmmddac   = dmmddac_;
   TypeStruct.Fmmddat   = dmmddat_;
   TypeStruct.Fmmddact  = dmmddact_;

   TypeStruct.Fcshft    = dcshft_;
   TypeStruct.Frshft    = drshft_;

   TypeStruct.Fvvdotu   = dvvdot_;
   TypeStruct.Fvvdotc   = dvvdot_;

   TypeStruct.Fset      = dset_;

   TypeStruct.Ftzpad    = dtzpad_;
   TypeStruct.Ftzpadcpy = dtzpadcpy_;
   TypeStruct.Ftzscal   = dtzscal_;
   TypeStruct.Fhescal   = dtzscal_;
   TypeStruct.Ftzcnjg   = dtzscal_;

   TypeStruct.Faxpy     = daxpy_;
   TypeStruct.Fcopy     = dcopy_;
   TypeStruct.Fswap     = dswap_;

   TypeStruct.Fgemv     = dgemv_;
   TypeStruct.Fsymv     = dsymv_;
   TypeStruct.Fhemv     = dsymv_;
   TypeStruct.Ftrmv     = dtrmv_;
   TypeStruct.Ftrsv     = dtrsv_;
   TypeStruct.Fagemv    = dagemv_;
   TypeStruct.Fasymv    = dasymv_;
   TypeStruct.Fahemv    = dasymv_;
   TypeStruct.Fatrmv    = datrmv_;

   TypeStruct.Fgerc     = dger_;
   TypeStruct.Fgeru     = dger_;
   TypeStruct.Fsyr      = dsyr_;
   TypeStruct.Fher      = dsyr_;
   TypeStruct.Fsyr2     = dsyr2_;
   TypeStruct.Fher2     = dsyr2_;

   TypeStruct.Fgemm     = dgemm_;
   TypeStruct.Fsymm     = dsymm_;
   TypeStruct.Fhemm     = dsymm_;
   TypeStruct.Fsyrk     = dsyrk_;
   TypeStruct.Fherk     = dsyrk_;
   TypeStruct.Fsyr2k    = dsyr2k_;
   TypeStruct.Fher2k    = dsyr2k_;
   TypeStruct.Ftrmm     = dtrmm_;
   TypeStruct.Ftrsm     = dtrsm_;
*/

   TypeStruct.Cgesd2d   = wcc_Cdgesd2d;
   TypeStruct.Cgerv2d   = wcc_Cdgerv2d;
   TypeStruct.Cgebs2d   = wcc_Cdgebs2d;
   TypeStruct.Cgebr2d   = wcc_Cdgebr2d;
   TypeStruct.Cgsum2d   = wcc_Cdgsum2d;

   TypeStruct.Fmmadd    = wcc_dmmadd_;
   TypeStruct.Fmmcadd   = wcc_dmmcadd_;
   TypeStruct.Fmmtadd   = wcc_dmmtadd_;
   TypeStruct.Fmmtcadd  = wcc_dmmtcadd_;
   TypeStruct.Fmmdda    = wcc_dmmdda_;
   TypeStruct.Fmmddac   = wcc_dmmddac_;
   TypeStruct.Fmmddat   = wcc_dmmddat_;
   TypeStruct.Fmmddact  = wcc_dmmddact_;

   TypeStruct.Fcshft    = wcc_dcshft_;
   TypeStruct.Frshft    = wcc_drshft_;

   TypeStruct.Fvvdotu   = wcc_dvvdot_;
   TypeStruct.Fvvdotc   = wcc_dvvdot_;

   TypeStruct.Fset      = wcc_dset_;

   TypeStruct.Ftzpad    = wcc_dtzpad_;
   TypeStruct.Ftzpadcpy = wcc_dtzpadcpy_;
   TypeStruct.Ftzscal   = wcc_dtzscal_;
   TypeStruct.Fhescal   = wcc_dtzscal_;
   TypeStruct.Ftzcnjg   = wcc_dtzscal_;

   TypeStruct.Faxpy     = wcc_daxpy_;
   TypeStruct.Fcopy     = wcc_dcopy_;
   TypeStruct.Fswap     = wcc_dswap_;

   TypeStruct.Fgemv     = wcc_dgemv_;
   TypeStruct.Fsymv     = wcc_dsymv_;
   TypeStruct.Fhemv     = wcc_dsymv_;
   TypeStruct.Ftrmv     = wcc_dtrmv_;
   TypeStruct.Ftrsv     = wcc_dtrsv_;
   TypeStruct.Fagemv    = wcc_dagemv_;
   TypeStruct.Fasymv    = wcc_dasymv_;
   TypeStruct.Fahemv    = wcc_dasymv_;
   TypeStruct.Fatrmv    = wcc_datrmv_;

   TypeStruct.Fgerc     = wcc_dger_;
   TypeStruct.Fgeru     = wcc_dger_;
   TypeStruct.Fsyr      = wcc_dsyr_;
   TypeStruct.Fher      = wcc_dsyr_;
   TypeStruct.Fsyr2     = wcc_dsyr2_;
   TypeStruct.Fher2     = wcc_dsyr2_;

   TypeStruct.Fgemm     = wcc_dgemm_;
   TypeStruct.Fsymm     = wcc_dsymm_;
   TypeStruct.Fhemm     = wcc_dsymm_;
   TypeStruct.Fsyrk     = wcc_dsyrk_;
   TypeStruct.Fherk     = wcc_dsyrk_;
   TypeStruct.Fsyr2k    = wcc_dsyr2k_;
   TypeStruct.Fher2k    = wcc_dsyr2k_;
   TypeStruct.Ftrmm     = wcc_dtrmm_;
   TypeStruct.Ftrsm     = wcc_dtrsm_;

   return( &TypeStruct );
/*
*  End of PB_Cdtypeset
*/
}
