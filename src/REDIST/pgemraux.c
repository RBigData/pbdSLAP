#include <R.h>	//WCC:add

#include "redist.h"
/* $Id: pgemraux.c,v 1.1.1.1 2000/02/15 18:04:10 susan Exp $
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
#include <assert.h>
void *
mr2d_malloc(long int n)
//WCC  long int   n;
{
  void *ptr;
  assert(n > 0);
  ptr = (void *) malloc(n);
  if (ptr == NULL) {
/*WCC    fprintf(stderr, "xxmr2d:out of memory\n"); */
/*WCC    exit(2); */
    REprintf("xxmr2d:out of memory\n");
    error("exit mr2d_malloc");
  }
  return ptr;
}
int 
pgcd(int a, int b)
//WCC  int   a, b;
{
  int   aux;
  if (a < b)
    return pgcd(b, a);
  else {
    aux = a % b;
    if (aux == 0)
      return b;
    else
      return pgcd(b, aux);
  }
}
int 
ppcm(int a, int b)
//WCC  int   a, b;
{
  int   pg;
  pg = pgcd(a, b);
  return a * (b / pg);
}
/* localsize:return the number of rows on the local processor given by its
 * row number myprow, of a distributed matrix with m rows distributed of on a
 * grid of processors with p rows with blocksize nbrow : this procedure can
 * also be used to compute the number of cols by replacing rows by cols */
int 
localsize(int myprow, int p, int nbrow, int m)
//WCC  int   myprow, p, nbrow, m;
{
  int   templateheight, blockheight;
  templateheight = p * nbrow;
  if (m % templateheight != 0) {	/* not an exact boundary */
    if ((m % templateheight) > (nbrow * myprow)) {	/* processor
							 * (myprow,mypcol) has
							 * some elements in that
							 * incomplete template */
      if ((m % templateheight) >= (nbrow * (myprow + 1))) {	/* processor
								 * (myprow,mypcol)'s
								 * part is complete */
	blockheight = (m / templateheight) * nbrow + nbrow;
      } else {	/* processor (myprow,mypcol)'s part is not complete */
	blockheight = (m / templateheight) * nbrow + (m % nbrow);
      };	/* if ((m%templateheight) > (nbrow*(myprow+1))) */
    } else {	/* processor (myprow,mypcol) has no element in that
		 * incomplete template */
      blockheight = (m / templateheight) * nbrow;
    };	/* if ((m%templateheight) > (nbrow*myprow)) */
  } else {	/* exact boundary */
    blockheight = m / p;	/* (m/templateheight) * nbrow */
  };	/* if (m%templateheight !=0) */
  return blockheight;
}
/****************************************************************/
/* Returns the exact memory block size corresponding to the parameters */
int
memoryblocksize(MDESC *a)
//WCC  MDESC *a;
{
  int   myprow, mypcol, p, q;
  /* Compute the (myprow,mypcol) indices of processor mypnum in P0xQ0 We
   * assume the row-major ordering of the BLACS */
  Cblacs_gridinfo(a->ctxt, &p, &q, &myprow, &mypcol);
  myprow = SHIFT(myprow, a->sprow, p);
  mypcol = SHIFT(mypcol, a->spcol, q);
  assert(myprow >= 0 && mypcol >= 0);
  return localsize(myprow, p, a->nbrow, a->m) *
	localsize(mypcol, q, a->nbcol, a->n);
}
void 
checkequal(int ctxt, int a)
//WCC  int   a, ctxt;
{
  int   np, dummy, nbrow, myp, b;
  Cblacs_gridinfo(ctxt, &nbrow, &np, &dummy, &myp);
  assert(nbrow == 1);
  if (np == 1)
    return;
  if (myp == 0) {
    Cigesd2d(ctxt, 1, 1, &a, 1, 0, 1);
    Cigerv2d(ctxt, 1, 1, &b, 1, 0, np - 1);
    assert(a == b);
  } else {
    Cigerv2d(ctxt, 1, 1, &b, 1, 0, myp - 1);
    assert(a == b);
    Cigesd2d(ctxt, 1, 1, &a, 1, 0, (myp + 1) % np);
  }
}
void 
paramcheck(MDESC *a, int i, int j, int m, int n, int p, int q, int gcontext)
//WCC  MDESC *a;
/*WCC  int   i, j, m, n, p, q; */
//WCC  int   i, j, m, n, p, q, gcontext; //WCC:add
{
  int   p2, q2, myprow, mypcol;
#ifndef NDEBUG
  checkequal(gcontext, p);
  checkequal(gcontext, q);
  checkequal(gcontext, a->sprow);
  checkequal(gcontext, a->spcol);
  checkequal(gcontext, a->m);
  checkequal(gcontext, a->n);
  checkequal(gcontext, i);
  checkequal(gcontext, j);
  checkequal(gcontext, a->nbrow);
  checkequal(gcontext, a->nbcol);
#endif
  Cblacs_gridinfo(a->ctxt, &p2, &q2, &myprow, &mypcol);
  /* compatibility T3D, must check myprow  and mypcol are within bounds */
  if (myprow >= p2 || mypcol >= q2)
    myprow = mypcol = -1;
  if ((myprow >= 0 || mypcol >= 0) && (p2 != p && q2 != q)) {
/*WCC    fprintf(stderr, "??MR2D:incoherent p,q parameters\n"); */
/*WCC    exit(1); */
    REprintf("??MR2D:incoherent p,q parameters\n");
    error("exit paramcheck 1");
  }
  assert(myprow < p && mypcol < q);
  if (a->sprow < 0 || a->sprow >= p || a->spcol < 0 || a->spcol >= q) {
/*WCC    fprintf(stderr, "??MR2D:Bad first processor coordinates\n"); */
/*WCC    exit(1); */
    REprintf("??MR2D:Bad first processor coordinates\n");
    error("exit paramcheck 2");
  }
  if (i < 0 || j < 0 || i + m > a->m || j + n > a->n) {
/*WCC    fprintf(stderr, "??MR2D:Bad submatrix:i=%d,j=%d,\ */
/*WCC m=%d,n=%d,M=%d,N=%d\n", */
/*WCC	    i, j, m, n, a->m, a->n); */
/*WCC    exit(1); */
    REprintf("??MR2D:Bad submatrix:i=%d,j=%d,\
m=%d,n=%d,M=%d,N=%d\n",
	    i, j, m, n, a->m, a->n);
    error("exit paramcheck 3");
  }
  if ((myprow >= 0 || mypcol >= 0) &&
      localsize(SHIFT(myprow, a->sprow, p), p, a->nbrow, a->m) > a->lda) {
/*WCC     fprintf(stderr, "??MR2D:bad lda arg:row=%d,m=%d,p=%d,\ */
/*WCC nbrow=%d,lda=%d,sprow=%d\n", */
/*WCC 	    myprow, a->m, p, a->nbrow, a->lda, a->sprow); */
/*WCC     exit(1); */
    REprintf("??MR2D:bad lda arg:row=%d,m=%d,p=%d,\
nbrow=%d,lda=%d,sprow=%d\n",
	    myprow, a->m, p, a->nbrow, a->lda, a->sprow);
    error("exit paramcheck 4");
  }
}
/* to change from the submatrix beginning at line i to one beginning at line
 * i' with i'< blocksize return the line number on the local process where
 * the new matrix begin, the new process number, and i' */
int 
changeorigin(int myp, int sp, int p, int bs, int i, int *decal, int *newsp)
//WCC  int   myp, sp, p, bs, i;
//WCC  int  *decal, *newsp;
{
  int   tempheight, firstblock, firsttemp;
  /* we begin by changing the parameters so that ia < templatewidth,... */
  tempheight = bs * p;
  firsttemp = i / tempheight;
  firstblock = (i / bs) % p;
  *newsp = (sp + firstblock) % p;
  if (myp >= 0)
    *decal = firsttemp * bs + (SHIFT(myp, sp, p) < firstblock ? bs : 0);
  else
    *decal = 0;
  return i % bs;
}
/******************************************************************/
/* Return the indice in local memory of element of indice a in the matrix */
int
localindice(int ig, int jg, int templateheight, int templatewidth, MDESC *a)
//WCC  int   templateheight, templatewidth, ig, jg;
//WCC  MDESC *a;
/* Return the indice in local memory (scattered distribution) of the element
 * of indice a in global matrix */
{
  int   vtemp, htemp, vsubtemp, hsubtemp, il, jl;
  assert(ig >= 0 && ig < a->m && jg >= 0 && jg < a->n);
  /* coordinates in global matrix with the tests in intersect, ig MUST BE in
   * [0..m] and jg in [0..n] */
  /* coordinates of the template that "owns" the element */
  vtemp = ig / templateheight;
  htemp = jg / templatewidth;
  /* coordinates of the element in the subblock of the (vtemp, htemp)
   * template */
  vsubtemp = ig % a->nbrow;
  hsubtemp = jg % a->nbcol;
  /* coordinates of the element in the local block of the processor */
  il = a->nbrow * vtemp + vsubtemp;
  jl = a->nbcol * htemp + hsubtemp;
  assert(il < a->lda);
#ifndef NDEBUG
  {
    int   pr, pc, p, q, lp, lq;
    Cblacs_gridinfo(a->ctxt, &p, &q, &pr, &pc);
    p = templateheight / a->nbrow;
    q = templatewidth / a->nbcol;
    lp = ig % templateheight / a->nbrow;
    lq = jg % templatewidth / a->nbcol;
    assert(lp == SHIFT(pr, a->sprow, p));
    assert(lq == SHIFT(pc, a->spcol, q));
  }
#endif
  return (jl * a->lda + il);
}
