#
# Copyright (c) 2008-2012      University of Houston. All rights reserved.
# Additional copyrights may follow
#
include ../../Makefile.defs

#W_INC_DIR = ..\include
#W_LIB_DIR = ..\lib

#WCLIB		= libvcdll.a
#WFLIB		= libvfdll.a
#CDLL		= vc.dll
#FDLL		= vf.dll

#WCFLAGS = -c -DBUILD_DLL -DMINGW 
#WFFLAGS	= -c -DBUILD_DLL -DMINGW -DVOLPEXFORTRAN -w
#WCDLLFLAGS  = -shared -o ..\lib\vc.dll -Wl,--out-implib,..\lib\libvcdll.a
#WFDLLFLAGS  = -shared -o ..\lib\vf.dll -Wl,--out-implib,..\lib\libvfdll.a

OBJ = 	volpex_API.o		\
	volpex_collective.o	\
	volpex_comm.o		\
	volpex_global.o		\
	volpex_p2p.o		\
	volpex_header.o		\
	volpex_proc.o		\
	volpex_communicator.o	\
	volpex_target_selection.o\
	volpex_returnheader.o    \
	volpex_progress.o	\
	volpex_debug.o		\
	volpex_target_info.o    \
	volpex_hybrid.o		\
	volpex_add_new_proc.o	\
	volpex_fAPI.o		

.SUFFIXES: .o.c

all: 
	make $(VOLPEX_LIB)

$(VOLPEX_LIB): $(HEADER) $(OBJ)
	$(AR) $(AR_FLAGS) $(VOLPEX_LIB_DIR)/$(VOLPEX_LIB) $(OBJ)

$(OBJ): $(HEADER)
.c.o:   $(HEADER)
	$(CC) $(CFLAGS) -DVOLPEXFORTRAN -c $<


clean:
	$(RM) $(RMFLAGS) *.o *~
