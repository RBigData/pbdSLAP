#include "redist.h"
/* $Id: pigemr2.c,v 1.1.1.1 2000/02/15 18:04:08 susan Exp $
 * 
 * some functions used by the pigemr2d routine see file pigemr.c for more
 * documentation.
 * 
 * Created March 1993 by B. Tourancheau (See sccs for modifications). */
#define static2 static
#if defined(Add_) || defined(f77IsF2C)
#define fortran_mr2d pigemr2do_
#define fortran_mr2dnew pigemr2d_
#elif defined(UpCase)
#define fortran_mr2dnew PIGEMR2D
#define fortran_mr2d PIGEMR2DO
#define icopy_ ICOPY
#define ilacpy_ ILACPY
#else
#define fortran_mr2d pigemr2do
#define fortran_mr2dnew pigemr2d
#define icopy_ icopy
#define ilacpy_ ilacpy
#endif
#define Clacpy Cigelacpy
void  Clacpy(int, int, int, int, int, int);
typedef struct {
  int   desctype;
  int   ctxt;
  int   m;
  int   n;
  int   nbrow;
  int   nbcol;
  int   sprow;
  int   spcol;
  int   lda;
}     MDESC;
#define BLOCK_CYCLIC_2D 1
typedef struct {
  int   lstart;
  int   len;
}     IDESC;
#define SHIFT(row,sprow,nbrow) ((row)-(sprow)+ ((row) >= (sprow) ? 0 : (nbrow)))
#define max(A,B) ((A)>(B)?(A):(B))
#define min(A,B) ((A)>(B)?(B):(A))
#define DIVUP(a,b) ( ((a)-1) /(b)+1)
#define ROUNDUP(a,b) (DIVUP(a,b)*(b))
#ifdef MALLOCDEBUG
#define malloc mymalloc
#define free myfree
#define realloc myrealloc
#endif
/* Cblacs */
extern void Cblacs_pcoord(int, int, int*, int*);
extern int Cblacs_pnum(int, int, int);
extern void Csetpvmtids(void);
extern void Cblacs_get(int, int, int*);
extern void Cblacs_pinfo(int*, int*);
extern void Cblacs_gridinfo(int, int*, int*, int*, int*);
extern void Cblacs_gridinit(int*, char*, int, int);
extern void Cblacs_exit(int);
extern void Cblacs_gridexit(int);
extern void Cblacs_setup(int*, int*);
extern void Cigebs2d(int, char*, char*, int, int, int*, int);
extern void Cigebr2d(int, char*, char*, int, int, int*, int, int, int);
extern void Cigesd2d(int, int, int, int*, int, int, int);
extern void Cigerv2d(int, int, int, int*, int, int, int);
extern void Cigsum2d(int, char*, char*, int, int, int*, int, int, int);
extern void Cigamn2d(int, char*, char*, int, int, int*, int, int*, int*, int, int, int);
extern void Cigamx2d(int, char*, char*, int, int, int*, int, int*, int*, int, int, int);
//WCC extern void Cigesd2d();
//WCC extern void Cigerv2d();
/* lapack */
void  ilacpy_(const char*, const int*, const int*, const int*, const int*, int*, const int*);
/* aux fonctions */
extern int localindice(int, int, int, int, MDESC*);
extern void *mr2d_malloc(long int);
extern int ppcm(int, int);
extern int localsize(int, int, int, int);
extern int memoryblocksize(MDESC*);
extern int changeorigin(int, int, int, int, int, int*, int*);
extern void paramcheck(MDESC*, int, int, int, int, int, int, int);
/* tools and others function */
#define scanD0 igescanD0
#define dispmat igedispmat
#define setmemory igesetmemory
#define freememory igefreememory
#define scan_intervals igescan_intervals
extern void scanD0(char*, char*, int, int*, int*, int, int, MDESC*, int, int, int, int, MDESC*, int, int, int, int, IDESC*, int, IDESC*, int, int*);
extern void dispmat(void);
extern void setmemory(int**, int);
extern void freememory(int*);
extern int scan_intervals(char, int, int, int, MDESC*, MDESC*, int, int, int, int, IDESC*);
extern void Cpigemr2do(int, int, int*, int, int, MDESC*, int*, int, int, MDESC*);
extern void Cpigemr2d(int, int, int*, int, int, MDESC*, int*, int, int, MDESC*, int);
/* some defines for Cpigemr2do */
#define SENDBUFF 0
#define RECVBUFF 1
#define SIZEBUFF 2
#if 0
#define DEBUG
#endif
#ifndef DEBUG
#define NDEBUG
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
/* Created March 1993 by B. Tourancheau (See sccs for modifications). */
/************************************************************************/
/* Set the memory space with the malloc function */
void
setmemory(int **adpointer, int blocksize)
//WCC  int **adpointer;
//WCC  int   blocksize;
{
  assert(blocksize >= 0);
  if (blocksize == 0) {
    *adpointer = NULL;
    return;
  }
  *adpointer = (int *) mr2d_malloc(
				   blocksize * sizeof(int));
}
/******************************************************************/
/* Free the memory space after the malloc */
void
freememory(int *ptrtobefreed)
//WCC  int  *ptrtobefreed;
{
  if (ptrtobefreed == NULL)
    return;
  free((char *) ptrtobefreed);
}
/* extern functions for intersect() extern icopy_(); */
/* scan_intervals: scans two distributions in one dimension, and compute the
 * intersections on the local processor. result must be long enough to
 * contains the result that are stocked in IDESC structure, the function
 * returns the number of intersections found */
int 
scan_intervals(char type, int ja, int jb, int n, MDESC *ma, MDESC *mb, int q0, int q1, int col0, int col1,
	       IDESC *result)
//WCC  char  type;
//WCC  int   ja, jb, n, q0, q1, col0, col1;
//WCC  MDESC *ma, *mb;
//WCC  IDESC *result;
{
  int   offset, j0, j1, templatewidth0, templatewidth1, nbcol0, nbcol1;
  int   l;	/* local indice on the beginning of the interval */
  assert(type == 'c' || type == 'r');
  nbcol0 = (type == 'c' ? ma->nbcol : ma->nbrow);
  nbcol1 = (type == 'c' ? mb->nbcol : mb->nbrow);
  templatewidth0 = q0 * nbcol0;
  templatewidth1 = q1 * nbcol1;
  {
    int   sp0 = (type == 'c' ? ma->spcol : ma->sprow);
    int   sp1 = (type == 'c' ? mb->spcol : mb->sprow);
    j0 = SHIFT(col0, sp0, q0) * nbcol0 - ja;
    j1 = SHIFT(col1, sp1, q1) * nbcol1 - jb;
  }
  offset = 0;
  l = 0;
  /* a small check to verify that the submatrix begin inside the first block
   * of the original matrix, this done by a sort of coordinate change at the
   * beginning of the Cpigemr2d */
  assert(j0 + nbcol0 > 0);
  assert(j1 + nbcol1 > 0);
  while ((j0 < n) && (j1 < n)) {
    int   end0, end1;
    int   start, end;
    end0 = j0 + nbcol0;
    end1 = j1 + nbcol1;
    if (end0 <= j1) {
      j0 += templatewidth0;
      l += nbcol0;
      continue;
    }
    if (end1 <= j0) {
      j1 += templatewidth1;
      continue;
    }
    /* compute the raw intersection */
    start = max(j0, j1);
    start = max(start, 0);
    /* the start is correct now, update the corresponding fields */
    result[offset].lstart = l + start - j0;
    end = min(end0, end1);
    if (end0 == end) {
      j0 += templatewidth0;
      l += nbcol0;
    }
    if (end1 == end)
      j1 += templatewidth1;
    /* throw the limit if they go out of the matrix */
    end = min(end, n);
    assert(end > start);
    /* it is a bit tricky to see why the length is always positive after all
     * this min and max, first we have the property that every interval
     * considered is at least partly into the submatrix, second we arrive
     * here only if the raw intersection is non-void, if we remove a limit
     * that means the corresponding frontier is in both intervals which
     * proove the final interval is non-void, clear ?? */
    result[offset].len = end - start;
    offset += 1;
  }	/* while */
  return offset;
}
