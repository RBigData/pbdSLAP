#include <R.h>
#include <R_ext/Rdynload.h>

#include "zzz.h"

static const R_FortranMethodDef fortranMethods[] = {
	{"slap_blacs_gridinit", (DL_FUNC) &F77_CALL(slap_blacs_gridinit), 5},
	{"slap_blacs_gridexit", (DL_FUNC) &F77_CALL(slap_blacs_gridexit), 1},
	{"slap_blacs_exit", (DL_FUNC) &F77_CALL(slap_blacs_exit), 1},

	/* Finish R_FortranMethodDef. */
	{NULL, NULL, 0}
};
/* End of the callMethods[]. */

void R_init_pbdSLAP(DllInfo *info){
	R_registerRoutines(info, NULL, NULL, fortranMethods, NULL);
	R_useDynamicSymbols(info, TRUE);
} /* End of R_init_pbdSLAP(). */
