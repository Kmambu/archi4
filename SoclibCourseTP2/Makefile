CC=g++
SIMPLE_OBJS = mapping_table.o \
	   segment.o \
	   address_decoding_table.o \
	   address_masking_table.o \
	   vci_gcd_master.o \
	   vci_gcd_coprocessor.o \
	   tp2_simple_top.o
MULTI_OBJS = mapping_table.o \
	   segment.o \
	   address_decoding_table.o \
	   address_masking_table.o \
	   vci_gcd_master.o \
	   vci_gcd_coprocessor.o \
	   vci_vgsb.o \
	   tp2_multi_top.o

%.o : %.cpp
	$(CC) -Wno-deprecated -std=gnu++0x -I. -I/users/outil/dsx/cctools/include -m32 -c $< -o $@
simple_simulator.x : $(SIMPLE_OBJS)
	g++ -Wno-deprecated -m32 -L. -L/users/outil/dsx/cctools/lib-linux -o $@ $^ -lsystemc 2>&1 
multi_simulator.x : $(MULTI_OBJS)
	g++ -Wno-deprecated -m32 -L. -L/users/outil/dsx/cctools/lib-linux -o $@ $^ -lsystemc 2>&1 
all : simple_simulator.x multi_simulator.x
.PHONY : clean
clean :
	rm -rf simple_simulator.x multi_simulator.x *.o
