c NPROCS = 4 CLASS = S
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  

c number of nodes for which this version is compiled
        integer nnodes_compiled
        parameter (nnodes_compiled = 4)

c full problem size
        integer isiz01, isiz02, isiz03
        parameter (isiz01=12, isiz02=12, isiz03=12)

c sub-domain array size
        integer isiz1, isiz2, isiz3
        parameter (isiz1=6, isiz2=6, isiz3=isiz03)

c number of iterations and how often to print the norm
        integer itmax_default, inorm_default
        parameter (itmax_default=50, inorm_default=50)
        double precision dt_default
        parameter (dt_default = 0.5d0)
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='17 Jul 2007')
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
