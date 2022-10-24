//WCC:add
// For C/Fortran char* string lengths using size_t
#ifdef USE_FC_LEN_T
  #include <stddef.h>
  #include <Rconfig.h>    // this defines FC_LEN_T
  #include <string.h>
#endif

#ifdef HERM
#undef HERM
#endif

//WCC:add
// To disable warnings generated by gcc-9.
void wcc_Cigesd2d(int ConTxt, int m, int n, char *A, int lda,
                  int rdest, int cdest);
void wcc_Cigerv2d(int ConTxt, int m, int n, char *A, int lda, int rsrc,
                  int csrc);
void wcc_Cigebs2d(int ConTxt, char *scope, char *top, int m, int n, char *A,
                  int lda);
void wcc_Cigebr2d(int ConTxt, char *scope, char *top, int m, int n, char *A,
                  int lda, int rsrc, int csrc);
void wcc_Cigsum2d(int ConTxt, char *scope, char *top, int m, int n, char *A,
                  int lda, int rdest, int cdest);

//WCC:add
// To disable warnings generated by gcc-9.
void wcc_Cdgesd2d(int ConTxt, int m, int n, char *A, int lda,
                  int rdest, int cdest);
void wcc_Cdgerv2d(int ConTxt, int m, int n, char *A, int lda, int rsrc,
                  int csrc);
void wcc_Cdgebs2d(int ConTxt, char *scope, char *top, int m, int n, char *A,
                  int lda);
void wcc_Cdgebr2d(int ConTxt, char *scope, char *top, int m, int n, char *A,
                  int lda, int rsrc, int csrc);
void wcc_Cdgsum2d(int ConTxt, char *scope, char *top, int m, int n, char *A,
                  int lda, int rdest, int cdest);
void wcc_dmmadd_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                 char *B, int *LDB);
void wcc_dmmcadd_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                  char *B, int *LDB);
void wcc_dmmtadd_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                  char *B, int *LDB);
void wcc_dmmtcadd_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                   char *B, int *LDB);
void wcc_dmmdda_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                 char *B, int *LDB);
void wcc_dmmddac_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                 char *B, int *LDB);
void wcc_dmmddat_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                 char *B, int *LDB);
void wcc_dmmddact_(int *M, int *N, char *ALPHA, char *A, int *LDA, char *BETA,
                 char *B, int *LDB);
void wcc_dcshft_(int *M, int *N, int *OFFSET, char *A, int *LDA);
void wcc_drshft_(int *M, int *N, int *OFFSET, char *A, int *LDA);
void wcc_dvvdot_(int *N, char *DOT, char *X, int *INCX, char *Y, int *INCY);
void wcc_dset_(int *N, char *ALPHA, char *X, int *INCX);
void wcc_dtzpad_(char *UPLO, char *HERM, int *M, int *N, int *IOFFD,
                 char *ALPHA, char *BETA, char *A, int *LDA);
void wcc_dtzpadcpy_(char *UPLO, char *DIAG, int *M, int *N, int *IOFFD,
                    char *A, int *LDA, char *B, int *LDB);
void wcc_dtzscal_(char *UPLO, int *M, int *N, int *IOFFD,
                  char *ALPHA, char *A, int *LDA);
void wcc_daxpy_(int *n, char *da, char *dx, int *incx, char *dy, int *incy);
void wcc_dcopy_(int *n, char *dx, int *incx, char *dy, int *incy);
void wcc_dswap_(int *n, char *dx, int *incx, char *dy, int *incy);
void wcc_dgemv_(char *TRANS, int *M, int *N, char *ALPHA, char *A, int *LDA,
                char *X, int *INCX, char *BETA, char *Y, int *INCY);
void wcc_dsymv_(char *UPLO, int *N, char *ALPHA, char *A, int *LDA,
                char *X, int *INCX, char *BETA, char *Y, int *INCY);
void wcc_dtrmv_(char *UPLO, char *TRANS, char *DIAG, int *N, char *A, int *LDA,
                char *X, int *INCX);
void wcc_dtrsv_(char *UPLO, char *TRANS, char *DIAG, int *N, char *A, int *LDA,
                char *X, int *INCX);
void wcc_dagemv_(char *TRANS, int *M, int *N, char *ALPHA, char *A, int *LDA,
                 char *X, int *INCX, char *BETA, char *Y, int *INCY);
void wcc_dasymv_(char *UPLO, int *N, char *ALPHA, char *A, int *LDA,
                 char *X, int *INCX, char *BETA, char *Y, int *INCY);
void wcc_datrmv_(char *UPLO, char *TRANS, char *DIAG, int *N,
                 char *ALPHA, char *A, int *LDA, char *X, int *INCX,
                 char *BETA, char *Y, int *INCY);
void wcc_dger_(int *M, int *N, char *ALPHA, char *X, int *INCX,
               char *Y, int *INCY, char *A, int *LDA);
void wcc_dsyr_(char *UPLO, int *N, char *ALPHA, char *X, int *INCX,
               char *A, int *LDA);
void wcc_dsyr2_(char *UPLO, int *N, char *ALPHA, char *X, int *INCX,
                char *Y, int *INCY, char *A, int *LDA);
void wcc_dgemm_(char *TRANSA, char *TRANSB, int *M, int *N, int *K,
                char *ALPHA, char *A, int *LDA, char *B, int *LDB,
                char *BETA, char *C, int *LDC);
void wcc_dsymm_(char *SIDE, char *UPLO, int *M, int *N,
                char *ALPHA, char *A, int *LDA, char *B, int *LDB,
                char *BETA, char *C, int *LDC);
void wcc_dsyrk_(char *UPLO, char *TRANS, int *N, int *K,
                char *ALPHA, char *A, int *LDA,
                char *BETA, char *C, int *LDC);
void wcc_dsyr2k_(char *UPLO, char *TRANS, int *N, int *K,
                 char *ALPHA, char *A, int *LDA, char *B, int *LDB,
                 char *BETA, char *C, int *LDC);
void wcc_dtrmm_(char *SIDE, char *UPLO, char *TRANSA, char *DIAG,
                int *M, int *N,
                char *ALPHA, char *A, int *LDA, char *B, int *LDB);
void wcc_dtrsm_(char *SIDE, char *UPLO, char *TRANSA, char *DIAG,
                int *M, int *N,
                char *ALPHA, char *A, int *LDA, char *B, int *LDB);
