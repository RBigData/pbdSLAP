#include <R.h>
#include <Rinternals.h>

extern void F77_NAME(slap_blacs_gridinit)(int *nprow, int *npcol, int *ictxt,
	int *myrow, int *mycol);
extern void F77_NAME(slap_blacs_gridexit)(int *ictxt);
extern void F77_NAME(slap_blacs_exit)(int *notdone);

