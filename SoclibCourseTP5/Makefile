
simulator.x : tp5_top.desc tp5_top.cpp
	soclib-cc -m debug -P -p tp5_top.desc -o simulator.x

simulator_cluster.x : tp5_cluster_top.cpp tp5_cluster_top.desc
	soclib-cc -m debug -P -p tp5_cluster_top.desc -o simulator_cluster.x

clean:
	rm -f *.o *.x core tmp *.deps stats trace simul*
	soclib-cc -x -X -P -p tp5_top.desc  -o simulator.x

