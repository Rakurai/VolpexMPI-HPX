c NPROCS = 16 CLASS = A
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  
        integer nx, ny, nz, maxdim, niter_default, ntotal, np_min
        parameter (nx=256, ny=256, nz=128, maxdim=256)
        parameter (niter_default=6)
        parameter (ntotal=nx*ny*nz)
        parameter (np_min = 16)
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
