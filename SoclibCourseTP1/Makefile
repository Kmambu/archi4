CC=g++
%.o : %.cpp
	$(CC) -Wno-deprecated -std=gnu++0x -I. -I/users/outil/dsx/cctools/include -m32 -c $< -o $@
%.oo : %.cpp
	$(CC) -O0 -g -Wno-deprecated -std=gnu++0x -I. -I/users/outil/dsx/systemcass/include -m32 -c $< -o $@
simulator.x : fifo_gcd_master.o fifo_gcd_coprocessor.o tp1_top.o
	g++ -Wno-deprecated -m32 -L. -L/users/outil/dsx/cctools/lib-linux -o $@ $^ -lsystemc 2>&1 
fast_simulator.x : fifo_gcd_master.oo fifo_gcd_coprocessor.oo tp1_top.oo
	$(CC) -O0 -g -std=gnu++0x -Wno-deprecated -m32 -L. -L/users/outil/dsx/systemcass/lib -o $@ $^ -lsystemc -ldl 2>&1
all : simulator.x fast_simulator.x
.PHONY : clean
clean :
	rm -rf simulator.x fast_simulator.x *.o *.oo
