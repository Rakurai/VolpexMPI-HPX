default: hpx_mpi_hello_world_scenario1 hpx_mpi_hello_world_scenario2 fibonacci
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/opt/xpress/default-hpx/lib/pkgconfig

hpx_mpi_hello_world_scenario1: hpx_mpi_hello_world_scenario1.cpp
	g++ -o ../bin/hpx_mpi_hello_world_scenario1 -g -O0 -Wall hpx_mpi_hello_world_scenario1.cpp -I../include `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=hpx_mpi_hello_world_scenario1 -L../lib -lvolpex


hpx_mpi_hello_world_scenario2: hpx_mpi_hello_world_scenario2.cpp
	g++ -o ../bin/hpx_mpi_hello_world_scenario2 -g -O0 -Wall hpx_mpi_hello_world_scenario2.cpp -I../include `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=hpx_mpi_hello_world_scenario2 -L../lib -lvolpex


hpx_hello_world: hpx_hello_world.cpp
	g++ -o ../bin/hpx_hello_world -g -O0 -Wall hpx_hello_world.cpp -I../include `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=hpx_hello_world

#	g++ -c hpx_mpi_hello_world.cpp -o ../bin/hpx_mpi_hello_world.o -g -O0 -I/home/hadi/VolpexMPI/trunk/include -I/opt/xpress/default-hpx/include/hpx/include -I/opt/xpress/default-boost/include/boost
#	g++ -f -O0 ../bin/hpx_mpi_hello_world.o -L/home/hadi/VolpexMPI/trunk/lib -lvolpex `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=hpx_mpi_hello_world 


fibonacci: fibonacci.cpp
	c++ -o ../bin/fibonacci fibonacci.cpp `pkg-config --cflags --libs hpx_application` -liostreams -DHPX_APPLICATION_NAME=fibonacci

clean:
	rm -rf *~ ../bin/hpx_mpi_hello_world_scenario1 ../bin/hpx_mpi_hello_world_scanrio2
