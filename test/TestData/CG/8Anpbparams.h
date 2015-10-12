c NPROCS = 8 CLASS = A
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  
        integer            na, nonzer, niter
        double precision   shift, rcond
        parameter(  na=14000,
     >              nonzer=11,
     >              niter=15,
     >              shift=20.,
     >              rcond=1.0d-1 )

c number of nodes for which this version is compiled
        integer    nnodes_compiled
        parameter( nnodes_compiled = 8)
        integer    num_proc_cols, num_proc_rows
        parameter( num_proc_cols=4, num_proc_rows=2 )
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='01 Feb 2009')
        character*3 npbversion
        parameter (npbversion='2.3')
        character*6 cs1
        parameter (cs1='mpif77')
        character*6 cs2
        parameter (cs2='mpif77')
        character*39 cs3
        parameter (cs3='-L~/mpich-1.2.6/lib -lfmpich # -lmyprof')
        character*23 cs4
        parameter (cs4='-I~/mpich-1.2.6/include')
        character*4 cs5
        parameter (cs5='-O3 ')
        character*6 cs6
        parameter (cs6='(none)')
        character*6 cs7
        parameter (cs7='(none)')
