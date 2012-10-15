! Initialize BLACS communicator, process grid
      SUBROUTINE slap_blacs_gridinit(NPROW, NPCOL, ICTXT, MYROW, MYCOL)
      EXTERNAL   SL_INIT, BLACS_GRIDINFO
      
      ! Inputs
      INTEGER NPROW, NPCOL
      ! Outputs
      INTEGER ICTXT, MYROW, MYCOL

      CALL BLACS_PINFO( IAM, NPROCS )
      IF( NPROCS.LT.1 ) THEN
         IF( IAM.EQ.0 )
     $      NPROCS = NPROW * NPCOL
         CALL BLACS_SETUP( IAM, NPROCS )
      END IF

      CALL BLACS_GET( -1, 0, ICTXT )
      CALL BLACS_GRIDINIT( ICTXT, 'Row-major', NPROW, NPCOL )
      CALL BLACS_GRIDINFO( ICTXT, NPROW, NPCOL, MYROW, MYCOL )

      RETURN
      END

! Release blacs grid
      SUBROUTINE slap_blacs_gridexit(ICTXT)
      EXTERNAL   BLACS_GRIDEXIT
      
      ! Inputs
      INTEGER ICTXT
      
      CALL BLACS_GRIDEXIT( ICTXT )

      RETURN
      END

! Finalize blacs
      SUBROUTINE slap_blacs_exit(NOTDONE)
      EXTERNAL   BLACS_EXIT
      
      CALL BLACS_EXIT( NOTDONE )

      RETURN
      END
