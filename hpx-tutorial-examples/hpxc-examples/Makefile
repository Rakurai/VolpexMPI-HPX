SHELL = /bin/sh

.SUFFIXES: .c .o

export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/opt/xpress/default-hpx/lib/pkgconfig

OBJECTS = self.o 
OUTPUTS = self
INPUTS = self.c

$(OUTPUTS):	$(OBJECTS)
	g++ $< -o $@ -g -O0 `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=$@ -I. -I/opt/xpress/hpx/include/ -I/opt/xpress/hpxc/include/ -L/opt/xpress/hpxc/lib -L/opt/xpress/hpx/lib/hpx -lhpxcd -lhpx  -L/home/hadi/VolpexMPI/trunk/lib/ -lvolpex

$(OBJECTS):	$(INPUTS)
	gcc $< -c -o $@ -I/opt/xpress/hpxc/include/ -I/opt/xpress/hpx/include/hpx/include/ -I/home/hadi/VolpexMPI/trunk/include/

#	g++ -o hello_world -g -O0 hello_world.cpp `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=hello_world -I/home/hadi/VolpexMPI/trunk/include -L/home/hadi/VolpexMPI/trunk/lib -lvolpex

clean:
	rm -rf $(OUTPUTS) $(OBJECTS) *~
