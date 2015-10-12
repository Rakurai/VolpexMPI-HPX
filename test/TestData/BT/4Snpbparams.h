c NPROCS = 4 CLASS = S
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  
        integer maxcells, problem_size, niter_default
        parameter (maxcells=2, problem_size=12, niter_default=60)
        double precision dt_default
        parameter (dt_default = 0.010d0)
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='10 Sep 2007')
        character*3 npbversion
        parameter (npbversion='2.3')
        character*4 cs1
        parameter (cs1='g95')
        character*4 cs2
        parameter (cs2='g95')
        character*23 cs3
        parameter (cs3='-L/usr/local/lib -lmpi')
        character*21 cs4
        parameter (cs4='-I/usr/local/include')
        character*5 cs5
        parameter (cs5='-O3 ')
        character*6 cs6
        parameter (cs6='(none)')
        character*7 cs7
        parameter (cs7='randi8')
