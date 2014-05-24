include ../SLmake.inc


# dlvl = ../..
# include $(dlvl)/Bmake.inc

#  --------------------------
#  The communication routines
#  --------------------------
comm = igesd2d_.o dgesd2d_.o \
       itrsd2d_.o dtrsd2d_.o \
       igerv2d_.o dgerv2d_.o \
       itrrv2d_.o dtrrv2d_.o \
       igebs2d_.o dgebs2d_.o \
       igebr2d_.o dgebr2d_.o \
       itrbs2d_.o dtrbs2d_.o \
       itrbr2d_.o dtrbr2d_.o \
       igsum2d_.o dgsum2d_.o \
       igamx2d_.o dgamx2d_.o \
       igamn2d_.o dgamn2d_.o

#  --------------------
#  The support routines
#  --------------------
supp = blacs_setup_.o blacs_set_.o blacs_get_.o \
       blacs_abort_.o blacs_exit_.o blacs_pnum_.o blacs_pcoord_.o \
       ksendid_.o krecvid_.o kbsid_.o kbrid_.o \
       dcputime00_.o dwalltime00_.o blacs_pinfo_.o \
       blacs_init_.o blacs_map_.o blacs_free_.o blacs_grid_.o blacs_info_.o \
       blacs_barr_.o sys2blacs_.o blacs2sys_.o free_handle_.o


#  ----------------------------
#  The fortran and C interfaces
#  ----------------------------
Fintobj   = $(comm) $(supp)
Cintobj   = $(comm:.o=.oo) $(supp:.o=.oo)

#  ---------------------
#  The internal routines
#  ---------------------
internal = BI_HypBS.o BI_HypBR.o BI_IdringBS.o BI_IdringBR.o \
           BI_MpathBS.o BI_MpathBR.o BI_SringBS.o BI_SringBR.o \
           BI_TreeBS.o BI_TreeBR.o \
           BI_Ssend.o BI_Rsend.o BI_Srecv.o BI_Asend.o BI_Arecv.o \
           BI_TreeComb.o BI_BeComb.o BI_MringComb.o \
           BI_ArgCheck.o BI_TransDist.o BI_GetBuff.o BI_UpdateBuffs.o \
           BI_EmergencyBuff.o BI_BlacsErr.o BI_BlacsWarn.o BI_BlacsAbort.o \
           BI_BuffIsFree.o BI_imvcopy.o BI_dmvcopy.o \
           BI_ivmcopy.o BI_dvmcopy.o \
           BI_Pack.o BI_Unpack.o BI_GetMpiGeType.o BI_GetMpiTrType.o \
           BI_ivvsum.o BI_dvvsum.o  \
           BI_ivvamx.o BI_dvvamx.o  \
           BI_ivvamx2.o BI_dvvamx2.o \
           BI_ivvamn.o BI_dvvamn.o  \
           BI_ivvamn2.o BI_dvvamn2.o \
           BI_iMPI_amx.o BI_dMPI_amx.o \
           BI_iMPI_amx2.o BI_dMPI_amx2.o \
           BI_iMPI_amn.o BI_dMPI_amn.o \
           BI_iMPI_amn2.o BI_dMPI_amn2.o \
           BI_ContxtNum.o BI_GlobalVars.o \
           BI_TransUserComm.o

PKG_Fintobj  = $(comm:.o=.fo) $(supp:.o=.fo)
PKG_Cintobj  = $(comm:.o=.oo) $(supp:.o=.oo)
PKG_internal = $(internal:.o=.fo)


lib : all

$(PKG_internal): Bdef.h Bconfig.h

$(PKG_Fintobj): Bdef.h Bconfig.h

#  ---------------------------------------
#  Make both C and fortran interface BLACS
#  ---------------------------------------
all : $(PKG_internal) $(PKG_Fintobj) $(PKG_Cintobj)
	$(ARCH) $(ARCHFLAGS) ../$(SCALAPACKLIB) \
                $(PKG_internal) $(PKG_Fintobj) $(PKG_Cintobj)
	$(RANLIB) ../$(SCALAPACKLIB)

#  -----------------------
#  Delete the object files
#  -----------------------
clean :
	rm -f $(PKG_Cintobj) $(PKG_Fintobj) $(PKG_internal)

#  ------------------------------------------------------------------------
#  We move C .o files to .oo so that we can use the portable suffix rule for
#  compilation, and still have them coexist with the fortran interface
#  .o files.
#  ------------------------------------------------------------------------
.SUFFIXES: .fo .oo
.c.oo:
	$(CC) -o $*.oo -c $(CDEFS) $(CCFLAGS) -DCallFromC $<
.c.fo:
	$(CC) -o $*.fo -c $(CDEFS) $(CCFLAGS) $<
