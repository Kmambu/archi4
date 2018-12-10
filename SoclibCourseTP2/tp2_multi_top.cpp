#include <systemc>
#include <limits>

#include "vci_gcd_master.h"
#include "vci_gcd_coprocessor.h"
#include "vci_vgsb.h"
#include "vci_signals.h"
#include "vci_param.h"
#include "mapping_table.h"

#define MAPPING_BASE_ADDR 0x00000000

#define GCD_SIZE	16

int sc_main(int argc, char *argv[])
{
	using namespace sc_core;
	using namespace soclib::caba;
	using namespace soclib::common;

	// VCI fields width definition
	//	cell_size	= 4;
	// 	plen_size	= 8;
	// 	addr_size	= 32;
	// 	rerror_size	= 1;
	// 	clen_size	= 1;
	// 	rflag_size	= 1;
	// 	srcid_size	= 12;
	// 	trdid_size	= 1;
	// 	pktid_size	= 1;
	// 	wrplen_size	= 1;

	typedef VciParams< 4,8,32,1,1,1,12,1,1,1 > vci_param;

	///////////////////////////////////////////////////////////////////////////
	// simulation arguments : number of cycles & seed for the random generation
	///////////////////////////////////////////////////////////////////////////
	int ncycles = std::numeric_limits<int>::max();
	int seed    = 123456789;
	if (argc > 1) ncycles = atoi(argv[1]) ;
	if (argc > 2) seed = atoi(argv[2]) ;

	//////////////////////////////////////////////////////////////////////////
	// Mapping Table
	//////////////////////////////////////////////////////////////////////////
	int i;
	std::string s;
	MappingTable maptab(32, IntTab(8), IntTab(8), 0x3000000);

	maptab.add(soclib::common::Segment("GCD0", 0x0, 		GCD_SIZE, IntTab(0), true));
	maptab.add(soclib::common::Segment("GCD1", 0x1000000, 	GCD_SIZE, IntTab(1), true));
	maptab.add(soclib::common::Segment("GCD2", 0x2000000, 	GCD_SIZE, IntTab(2), true));
	std::cout << std::endl << maptab << std::endl;
	//////////////////////////////////////////////////////////////////////////
	// Signals
	//////////////////////////////////////////////////////////////////////////
	sc_clock               		signal_clk("signal_clk", sc_time( 1, SC_NS ), 0.5 );
	sc_signal<bool> 			signal_resetn("signal_resetn");
	VciSignals<vci_param> 		signal_vci_m0("signal_vci_m0");
	VciSignals<vci_param> 		signal_vci_m1("signal_vci_m1");
	VciSignals<vci_param> 		signal_vci_m2("signal_vci_m2");
	VciSignals<vci_param> 		signal_vci_c0("signal_vci_c0");
	VciSignals<vci_param> 		signal_vci_c1("signal_vci_c1");
	VciSignals<vci_param> 		signal_vci_c2("signal_vci_c2");

	//////////////////////////////////////////////////////////////////////////
	// Components
	//////////////////////////////////////////////////////////////////////////
	VciGcdMaster<vci_param > master0("master0", IntTab(0), maptab, seed+0, 0x0);
	VciGcdMaster<vci_param > master1("master1", IntTab(1), maptab, seed+1, 0x1000000);
	VciGcdMaster<vci_param > master2("master2", IntTab(2), maptab, seed+2, 0x2000000);
	
	VciGcdCoprocessor<vci_param > coproc0("coproc0", IntTab(0), maptab);
	VciGcdCoprocessor<vci_param > coproc1("coproc1", IntTab(1), maptab);
	VciGcdCoprocessor<vci_param > coproc2("coproc2", IntTab(2), maptab);

	VciVgsb<vci_param> vgsb("vgsb", maptab, 3, 3);
	
	//////////////////////////////////////////////////////////////////////////
	// Net-List
	//////////////////////////////////////////////////////////////////////////
	vgsb.p_clk(signal_clk);
	vgsb.p_resetn(signal_resetn);

	master0.p_clk(signal_clk);
	master0.p_resetn(signal_resetn);
	master1.p_clk(signal_clk);
	master1.p_resetn(signal_resetn);
	master2.p_clk(signal_clk);
	master2.p_resetn(signal_resetn);

	coproc0.p_clk(signal_clk);
	coproc0.p_resetn(signal_resetn);
	coproc1.p_clk(signal_clk);
	coproc1.p_resetn(signal_resetn);
	coproc2.p_clk(signal_clk);
	coproc2.p_resetn(signal_resetn);
	
	vgsb.p_to_initiator[0](signal_vci_m0);
	master0.p_vci(signal_vci_m0);
	vgsb.p_to_initiator[1](signal_vci_m1);
	master1.p_vci(signal_vci_m1);
	vgsb.p_to_initiator[2](signal_vci_m2);
	master2.p_vci(signal_vci_m2);

	vgsb.p_to_target[0](signal_vci_c0);
	coproc0.p_vci(signal_vci_c0);
	vgsb.p_to_target[1](signal_vci_c1);
	coproc1.p_vci(signal_vci_c1);
	vgsb.p_to_target[2](signal_vci_c2);
	coproc2.p_vci(signal_vci_c2);
	//////////////////////////////////////////////////////////////////////////
	// simulation
	//////////////////////////////////////////////////////////////////////////
	sc_start(0);
	signal_resetn = false;
	sc_start( sc_time( 1, SC_NS ) ) ;

	signal_resetn = true;
	for ( size_t n=1 ; n<ncycles ; n++) sc_start( sc_time( 1, SC_NS ) ) ;

	return(0);

} // end sc_main

