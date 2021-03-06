!/*
!#
!# Copyright (c) 2006-2012      University of Houston. All rights reserved.
!# $COPYRIGHT$
!#
!# Additional copyrights may follow
!#
!# $HEADER$
!#
!
!
!# The structure of this header file follows the mpif.h header file of the 
!# MPICH disitribution in the 1.1.x series. It has been adapted to VolpexMPI
!# Here is the copyright of the MPICH 1.1.x series.
!*/

C
C  
C  (C) 1993 by Argonne National Laboratory and Mississipi State University.
C      All rights reserved.  See COPYRIGHT in top-level directory.
C
C

! include file for MPI FORTRAN programs
!
! return codes 
      INTEGER MPI_SUCCESS,MPI_ERR_BUFFER,MPI_ERR_COUNT,MPI_ERR_TYPE
      INTEGER MPI_ERR_TAG,MPI_ERR_COMM,MPI_ERR_RANK,MPI_ERR_ROOT
      INTEGER MPI_ERR_GROUP
      INTEGER MPI_ERR_OP,MPI_ERR_TOPOLOGY,MPI_ERR_DIMS,MPI_ERR_ARG
      INTEGER MPI_ERR_UNKNOWN,MPI_ERR_TRUNCATE,MPI_ERR_OTHER
      INTEGER MPI_ERR_INTERN,MPI_ERR_IN_STATUS,MPI_ERR_PENDING
      INTEGER MPI_ERR_REQUEST,MPI_ERR_LASTCODE
      PARAMETER (MPI_SUCCESS=0,MPI_ERR_BUFFER=1,MPI_ERR_COUNT=2)
      PARAMETER (MPI_ERR_TYPE=3,MPI_ERR_TAG=4,MPI_ERR_COMM=5)
      PARAMETER (MPI_ERR_RANK=6,MPI_ERR_ROOT=8,MPI_ERR_GROUP=9)
      PARAMETER (MPI_ERR_OP=10,MPI_ERR_TOPOLOGY=11,MPI_ERR_DIMS=12)
      PARAMETER (MPI_ERR_ARG=13,MPI_ERR_UNKNOWN=14)
      PARAMETER (MPI_ERR_TRUNCATE=15,MPI_ERR_OTHER=16)
      PARAMETER (MPI_ERR_INTERN=17,MPI_ERR_IN_STATUS=18)
      PARAMETER (MPI_ERR_PENDING=19,MPI_ERR_REQUEST=7)
      PARAMETER (MPI_ERR_LASTCODE=31)
!
      INTEGER MPI_UNDEFINED
      parameter (MPI_UNDEFINED = (-3))
!
      INTEGER MPI_GRAPH, MPI_CART
      PARAMETER (MPI_GRAPH = 1, MPI_CART = 2)
      INTEGER  MPI_PROC_NULL
      PARAMETER ( MPI_PROC_NULL = (-1) )
!
      INTEGER MPI_BSEND_OVERHEAD
      PARAMETER ( MPI_BSEND_OVERHEAD = 32 )

      INTEGER MPI_SOURCE, MPI_TAG, MPI_ERROR
      PARAMETER(MPI_SOURCE=2, MPI_TAG=3, MPI_ERROR=4)
      INTEGER MPI_STATUS_SIZE
      PARAMETER (MPI_STATUS_SIZE=5)
      INTEGER MPI_MAX_PROCESSOR_NAME, MPI_MAX_ERROR_STRING
      PARAMETER (MPI_MAX_PROCESSOR_NAME=256)
      PARAMETER (MPI_MAX_ERROR_STRING=512)
      INTEGER MPI_MAX_NAME_STRING
      PARAMETER (MPI_MAX_NAME_STRING=63)
!
      INTEGER MPI_COMM_NULL
      PARAMETER (MPI_COMM_NULL=0)
!
      INTEGER MPI_DATATYPE_NULL
      PARAMETER (MPI_DATATYPE_NULL = 0)
      
      INTEGER MPI_ERRHANDLER_NULL
      PARAMETER (MPI_ERRHANDLER_NULL = 0)
      
      INTEGER MPI_GROUP_NULL
      PARAMETER (MPI_GROUP_NULL = 0)
      
      INTEGER MPI_KEYVAL_INVALID
      PARAMETER (MPI_KEYVAL_INVALID = 0)
      
      INTEGER MPI_REQUEST_NULL
      PARAMETER (MPI_REQUEST_NULL = -1)
! 
      INTEGER MPI_IDENT, MPI_CONGRUENT, MPI_SIMILAR, MPI_UNEQUAL
      PARAMETER (MPI_IDENT=0, MPI_CONGRUENT=1, MPI_SIMILAR=2)
      PARAMETER (MPI_UNEQUAL=3)
!
!     MPI_BOTTOM needs to be a known address; here we put it at the
!     beginning of the common block.  The point-to-point and collective
!     routines know about MPI_BOTTOM, but MPI_TYPE_STRUCT as yet does not.
!
!     MPI_STATUS_IGNORE and MPI_STATUSES_IGNORE are similar objects
!     Until the underlying MPI library implements the C version of these
!     (a null pointer), these are declared as arrays of MPI_STATUS_SIZE
!
!     The types MPI_INTEGER1,2,4 and MPI_REAL4,8 are OPTIONAL.
!     Their values are zero if they are not available.  Note that
!     using these reduces the portability of code (though may enhance
!     portability between Crays and other systems)
!
      INTEGER MPI_TAG_UB, MPI_HOST, MPI_IO
      INTEGER MPI_BOTTOM
      INTEGER MPI_STATUS_IGNORE(MPI_STATUS_SIZE)
      INTEGER MPI_STATUSES_IGNORE(MPI_STATUS_SIZE)
      INTEGER MPI_INTEGER, MPI_REAL, MPI_DOUBLE_PRECISION 
      INTEGER MPI_COMPLEX, MPI_DOUBLE_COMPLEX,MPI_LOGICAL
      INTEGER MPI_CHARACTER, MPI_BYTE, MPI_2INTEGER, MPI_2REAL
      INTEGER MPI_2DOUBLE_PRECISION, MPI_2COMPLEX, MPI_2DOUBLE_COMPLEX
      INTEGER MPI_UB, MPI_LB
      INTEGER MPI_PACKED, MPI_WTIME_IS_GLOBAL
      INTEGER MPI_COMM_WORLD, MPI_COMM_SELF, MPI_GROUP_EMPTY
      INTEGER MPI_SUM, MPI_MAX, MPI_MIN, MPI_PROD, MPI_LAND, MPI_BAND
      INTEGER MPI_LOR, MPI_BOR, MPI_LXOR, MPI_BXOR, MPI_MINLOC
      INTEGER MPI_MAXLOC
      INTEGER MPI_OP_NULL
      INTEGER MPI_ERRORS_ARE_FATAL, MPI_ERRORS_RETURN
!
      PARAMETER (MPI_ERRORS_ARE_FATAL=1)
      PARAMETER (MPI_ERRORS_RETURN=2)
!
      PARAMETER (MPI_COMPLEX=16,MPI_DOUBLE_COMPLEX=17,MPI_LOGICAL=18)
      PARAMETER (MPI_REAL=14,MPI_DOUBLE_PRECISION=15,MPI_INTEGER=13)
      PARAMETER (MPI_2INTEGER=39,MPI_2COMPLEX=30,MPI_2DOUBLE_COMPLEX=31)
      PARAMETER (MPI_2REAL=37,MPI_2DOUBLE_PRECISION=38,MPI_CHARACTER=19)
      PARAMETER (MPI_BYTE=27,MPI_UB=29,MPI_LB=30,MPI_PACKED=28)

      INTEGER MPI_ORDER_C, MPI_ORDER_FORTRAN 
      PARAMETER (MPI_ORDER_C=56, MPI_ORDER_FORTRAN=57)
      INTEGER MPI_DISTRIBUTE_BLOCK, MPI_DISTRIBUTE_CYCLIC
      INTEGER MPI_DISTRIBUTE_NONE, MPI_DISTRIBUTE_DFLT_DARG
      PARAMETER (MPI_DISTRIBUTE_BLOCK=121, MPI_DISTRIBUTE_CYCLIC=122)
      PARAMETER (MPI_DISTRIBUTE_NONE=123)
      PARAMETER (MPI_DISTRIBUTE_DFLT_DARG=-49767)
      INTEGER MPI_MAX_INFO_KEY, MPI_MAX_INFO_VAL
      PARAMETER (MPI_MAX_INFO_KEY=255, MPI_MAX_INFO_VAL=1024)
      INTEGER MPI_INFO_NULL
      PARAMETER (MPI_INFO_NULL=0)

!
! Optional Fortran Types.  Configure attempts to determine these.  
!
      INTEGER MPI_INTEGER1, MPI_INTEGER2, MPI_INTEGER4, MPI_INTEGER8
      INTEGER MPI_INTEGER16
      INTEGER MPI_REAL4, MPI_REAL8, MPI_REAL16
      INTEGER MPI_COMPLEX8, MPI_COMPLEX16, MPI_COMPLEX32
      PARAMETER (MPI_INTEGER1=20,MPI_INTEGER2=21)
      PARAMETER (MPI_INTEGER4=22)
      PARAMETER (MPI_INTEGER8=23)
      PARAMETER (MPI_INTEGER16=0)
      PARAMETER (MPI_REAL4=24)
      PARAMETER (MPI_REAL8=25)
      PARAMETER (MPI_REAL16=26)
      PARAMETER (MPI_COMPLEX8=0)
      PARAMETER (MPI_COMPLEX16=0)
      PARAMETER (MPI_COMPLEX32=0)
!
!    This is now handled with either the "pointer" extension or this same
!    code, appended at the end.
!      COMMON /MPIPRIV/ MPI_BOTTOM,MPI_STATUS_IGNORE,MPI_STATUSES_IGNORE
!
!     Without this save, some Fortran implementations may make the common
!     dynamic!
!    
!     For a Fortran90 module, we might replace /MPIPRIV/ with a simple
!     SAVE MPI_BOTTOM
!
!      SAVE /MPIPRIV/
!
! Intel compiler import specification
!MS$ATTRIBUTES DLLIMPORT :: /MPIPRIV/
! Visual Fortran import specification
!DEC$ ATTRIBUTES DLLIMPORT :: /MPIPRIV/
      COMMON /MPIPRIV/ MPI_BOTTOM,MPI_STATUS_IGNORE,MPI_STATUSES_IGNORE
      PARAMETER (MPI_MAX=1,MPI_MIN=2,MPI_SUM=3,MPI_PROD=4)
      PARAMETER (MPI_LAND=5,MPI_BAND=6,MPI_LOR=7,MPI_BOR=8)
      PARAMETER (MPI_LXOR=9,MPI_BXOR=10,MPI_MINLOC=12)
      PARAMETER (MPI_MAXLOC=11, MPI_OP_NULL=0)
!
      PARAMETER (MPI_GROUP_EMPTY=1,MPI_COMM_WORLD=1,MPI_COMM_SELF=2)
      PARAMETER (MPI_TAG_UB=1,MPI_HOST=2,MPI_IO=3)
      PARAMETER (MPI_WTIME_IS_GLOBAL=4)
!
      INTEGER MPI_ANY_SOURCE
      PARAMETER (MPI_ANY_SOURCE = (-2))
      INTEGER MPI_ANY_TAG
      PARAMETER (MPI_ANY_TAG = (-1))
!
      INTEGER MPI_VERSION, MPI_SUBVERSION
      PARAMETER (MPI_VERSION    = 1, MPI_SUBVERSION = 2)
!
!     There are additional MPI-2 constants 
      INTEGER MPI_ADDRESS_KIND, MPI_OFFSET_KIND
      PARAMETER (MPI_ADDRESS_KIND= 4)
      PARAMETER (MPI_OFFSET_KIND= 4)
!
!     All other MPI routines are subroutines
!     This may cause some Fortran compilers to complain about defined and
!     not used.  Such compilers should be improved.
!
!     Some Fortran compilers will not link programs that contain
!     external statements to routines that are not provided, even if
!     the routine is never called.  Remove PMPI_WTIME and PMPI_WTICK
!     if you have trouble with them.
!
      DOUBLE PRECISION MPI_WTIME, MPI_WTICK
!     EXTERNAL MPI_WTIME, MPI_WTICK
!
!     The attribute copy/delete subroutines are symbols that can be passed
!     to MPI routines
!     EXTERNAL MPI_NULL_COPY_FN, MPI_NULL_DELETE_FN, MPI_DUP_FN
