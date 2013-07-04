#include "Bdef.h"

void BI_BlacsAbort(int ErrNo)
{
   int ierr;
//WCC   fflush(stderr);
//WCC   fflush(stdout);
   ierr=MPI_Abort(MPI_COMM_WORLD, ErrNo);
}
