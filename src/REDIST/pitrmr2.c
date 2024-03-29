#include <R.h>	//WCC:add

#include "redist.h"
/* $Id: pitrmr2.c,v 1.1.1.1 2000/02/15 18:04:08 susan Exp $
 * 
 * some functions used by the pitrmr2d routine see file pitrmr.c for more
 * documentation.
 * 
 * Created March 1993 by B. Tourancheau (See sccs for modifications). */
#define static2 static
#if defined(Add_) || defined(f77IsF2C)
#define fortran_mr2d pitrmr2do_
#define fortran_mr2dnew pitrmr2d_
#elif defined(UpCase)
#define fortran_mr2dnew PITRMR2D
#define fortran_mr2d PITRMR2DO
#define icopy_ ICOPY
#define ilacpy_ ILACPY
#else
#define fortran_mr2d pitrmr2do
#define fortran_mr2dnew pitrmr2d
#define icopy_ icopy
#define ilacpy_ ilacpy
#endif
#define Clacpy Citrlacpy
void  Clacpy(int, int, int*, int, int*, int);
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
  int   gstart;
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
extern void Cdgesd2d(int, int, int, double*, int, int, int);
extern void Cdgerv2d(int, int, int, double*, int, int, int);
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
#define scanD0 itrscanD0
#define dispmat itrdispmat
#define setmemory itrsetmemory
#define freememory itrfreememory
#define scan_intervals itrscan_intervals
extern void scanD0(char*, char*, int, int*, int*, int, int, MDESC*, int, int, int, int, MDESC*, int, int, int, int, IDESC*, int, IDESC*, int, int*);
extern void dispmat(void);
extern void setmemory(int**, int);
extern void freememory(int*);
extern int scan_intervals(char, int, int, int, MDESC*, MDESC*, int, int, int, int, IDESC*);
extern void Cpitrmr2do(char*, char*, int, int, int*, int, int, MDESC*, int*, int, int, MDESC*);
extern void Cpitrmr2d(char*, char*, int, int, int*, int, int, MDESC*, int*, int, int, MDESC*, int);
/* some defines for Cpitrmr2do */
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
/**************************************************************/
/* return the number of elements int the column after i and the distance of
 * the first one from i, i,j can be negative out of borns, the number of
 * elements returned can be negative (means 0) */
static2 int
insidemat(char *uplo, char *diag, int i, int j, int m, int n, int *offset)
//WCC  int   m, n, i, j;	/* coordonnees de depart, taille de la sous-matrice */
//WCC  char *uplo, *diag;
//WCC  int  *offset;
{
  /* tests outside mxn */
  assert(j >= 0 && j < n);
  assert(i >= 0);
  if (toupper(*uplo) == 'U') {
    int   nbline;	/* number of lines in the j_th column */
    int   virtualnbline;	/* number of line if we were not limited by m */
    *offset = 0;
    virtualnbline = max(m - n, 0) + j + (toupper(*diag) == 'N');
    nbline = min(virtualnbline, m);
    return nbline - i;
  } else {
    int   firstline;	/* first line in the j_th column */
    int   diagcol;	/* column where the diag begin */
    int   virtualline;	/* virtual first line if the matrix was extended with
			 * negative indices */
    int   off;
    diagcol = max(n - m, 0);;
    virtualline = j - diagcol + (toupper(*diag) == 'U');
    firstline = max(0, virtualline);
    off = max(firstline - i, 0);
    *offset = off;
    i += off;
    return m - i;
  }
}/* insidemat() */
/********************************************************************/
/* Execute an action on the local memories when an intersection occurs (the
 * action can be the filling of the memory buffer, the count of the memory
 * buffer size or the setting of the memory with the element received) */
static2 void
intersect(char *uplo, char *diag,
	  int j, int start, int end,
	  int action,
	  int *ptrsizebuff, int **pptrbuff, int *ptrblock,
	  int m, int n,
	  MDESC *ma, int ia, int ja, int templateheight0, int templatewidth0,
	  MDESC *mb, int ib, int jb, int templateheight1, int templatewidth1)
//WCC  int   action, *ptrsizebuff;
//WCC  int   j, start, end;
//WCC  int **pptrbuff, *ptrblock;
//WCC  int   templateheight0, templatewidth0;
//WCC  int   templateheight1, templatewidth1;
//WCC  MDESC *ma, *mb;
//WCC  int   ia, ja, ib, jb, m, n;
//WCC  char *uplo, *diag;
/* Execute the action on the local memory for the current interval and
 * increment pptrbuff and ptrsizebuff of the intervalsize */
/* Notice that if the interval is contigous in the virtual matrice, it is
 * also contigous in the real one ! */
{
  /* int       un = 1; only when we use dcopy instead of memcpy */
  int  *ptrstart;
  int   offset, nbline;
  int   intervalsize;
  assert(start < end);
  assert(j >= 0 && j < n);
  nbline =
	insidemat(uplo, diag, start, j, m, n, &offset);
  if (nbline <= 0)
    return;
  start += offset;
  if (start >= end)
    return;
  intervalsize = min(end - start, nbline);
  (*ptrsizebuff) += intervalsize;
  switch (action) {
  case SENDBUFF:	/* fill buff with local elements to be sent */
    ptrstart = ptrblock + localindice(start + ia, j + ja,
				      templateheight0, templatewidth0, ma);
    memcpy((char *) (*pptrbuff), (char *) ptrstart,
	   intervalsize * sizeof(int));
    /* icopy_(&intervalsize, (char *) (ptrstart), &un, (char *) (*pptrbuff),
     * &un); */
    (*pptrbuff) += intervalsize;
    break;
  case RECVBUFF:	/* fill local memory with the values received */
    ptrstart = ptrblock + localindice(start + ib, j + jb,
				      templateheight1, templatewidth1, mb);
    memcpy((char *) ptrstart, (char *) (*pptrbuff),
	   intervalsize * sizeof(int));
    /* icopy_(&intervalsize, (char *) (*pptrbuff), &un, (char *) (ptrstart),
     * &un); */
    (*pptrbuff) += intervalsize;
    break;
  case SIZEBUFF:	/* computation of sizebuff */
    break;
  default:
//WCC    printf("action is  %d outside the scope of the case [0..2] !! \n ", action);
//WCC    exit(0);
    Rprintf("action is  %d outside the scope of the case [0..2] !! \n ", action);
    error("exit intersect");
    break;
  };	/* switch (action) */
}/* intersect() */
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
   * beginning of the Cpitrmr2d */
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
    result[offset].gstart = start;
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
/*********************************************************************/
/* Do the scanning of intervals and the requested action */
void
scanD0(char *uplo, char *diag, int action, int *ptrbuff, int *ptrsizebuff,
       int m, int n,
       MDESC *ma, int ia, int ja, int p0, int q0,
       MDESC *mb, int ib, int jb, int p1, int q1,
       IDESC *v_inter, int vinter_nb,
       IDESC *h_inter, int hinter_nb,
       int *ptrblock)
//WCC  int   action,	/* # of the action done on the intersected intervals  */
//WCC       *ptrsizebuff;	/* size of the communication ptrbuffer (chosen to be
//WCC			 * an output parameter in every cases) */
//WCC  int  *ptrbuff	/* address of the communication ptrbuffer (a suffisant memory
//WCC      space is supposed to be allocated before the call) */ , *ptrblock;
//WCC  int   p0, q0, p1, q1;
//WCC  IDESC *v_inter, *h_inter;
//WCC  int   vinter_nb, hinter_nb;
//WCC  int   m, n;
//WCC  int   ia, ja, ib, jb;
//WCC  MDESC *ma, *mb;
//WCC  char *uplo, *diag;
{/* Rmk: the a+au type addresses are strict bounds as a+au does not belong to
  * the [a..a+au-1] interval of length au */
  int   templateheight1, templatewidth1;
  int   templateheight0, templatewidth0;
  int   h, v;	/* for scanning the intervals */
  /* initializations */
  templateheight1 = p1 * mb->nbrow;
  templateheight0 = p0 * ma->nbrow;
  templatewidth1 = q1 * mb->nbcol;
  templatewidth0 = q0 * ma->nbcol;
  /* we now will deal will logical grids, that's to say we change our
   * numbering of processors so that (0,0) begin on logical processor (0,0) */
  /* in case we will not enter the while loop */
  (*ptrsizebuff) = 0;
  for (h = 0; h < hinter_nb; h++)
    for (v = 0; v < vinter_nb; v++) {
      int   j;
      for (j = 0; j < h_inter[h].len; j++)
	intersect(uplo, diag, j + h_inter[h].gstart,
		  v_inter[v].gstart, v_inter[v].gstart + v_inter[v].len,
		  action, ptrsizebuff, &ptrbuff, ptrblock, m, n,
		  ma, ia, ja, templateheight0, templatewidth0,
		  mb, ib, jb, templateheight1, templatewidth1);
    }
}/* scanD0() */
