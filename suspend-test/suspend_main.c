//Elsa Gonsiorowski
//September 3, 2015

#include "ross.h"
#include "suspend.h"

// Define LP types
//   these are the functions called by ROSS for each LP
//   multiple sets can be defined (for multiple LP types)
tw_lptype suspend_lps[] = {
  {
    (init_f) increment_init,
    (pre_run_f) NULL,
    (event_f) increment_event,
    (revent_f) increment_event_reverse,
    (final_f) increment_final,
    (map_f) suspend_map,
    sizeof(increment_state)
  },
  {
    (init_f) decrement_init,
    (pre_run_f) NULL,
    (event_f) decrement_event,
    (revent_f) decrement_event_reverse,
    (final_f) decrement_final,
    (map_f) suspend_map,
    sizeof(decrement_state)
  },
  {
    (init_f) receiver_init,
    (pre_run_f) NULL,
    (event_f) receiver_event,
    (revent_f) receiver_event_reverse,
    (final_f) receiver_final,
    (map_f) suspend_map,
    sizeof(receiver_state)
  },
  { 0 },
};

//Define command line arguments default values
unsigned int total_receivers = 2;

//add your command line opts
const tw_optdef suspend_opts[] = {
	TWOPT_GROUP("Suspend Test"),
	TWOPT_UINT("total_receivers", total_receivers, "Number of receiver LPs to create"),
	TWOPT_END(),
};


//for doxygen
#define suspend_main main

int suspend_main (int argc, char* argv[]) {
	int i;
	int num_lps_per_pe;

	tw_opt_add(suspend_opts);
	tw_init(&argc, &argv);

	//Do some error checking?
	//Print out some settings?

	g_tw_mapping = LINEAR;

	//Custom Mapping
	/*
	g_tw_mapping = CUSTOM;
	g_tw_custom_initial_mapping = &suspend_custom_mapping;
	g_tw_custom_lp_global_to_local_map = &suspend_mapping_to_lp;
	*/

	//Useful ROSS variables and functions
	// tw_nnodes() : number of nodes/processors defined
	// g_tw_mynode : my node/processor id (mpi rank)

	//Useful ROSS variables (set from command line)
	// g_tw_events_per_pe
	// g_tw_lookahead
	// g_tw_nlp
	// g_tw_nkp
	// g_tw_synchronization_protocol

	// LP0: increment type
	// LP1: decrement type
	// LPn: receiver type
	int num_total_lps = 2 + total_receivers;
	num_lps_per_pe = num_total_lps / tw_nnodes();

	//set up LPs within ROSS
	tw_define_lps(num_lps_per_pe, sizeof(message));
	// note that g_tw_nlp gets set here by tw_define_lps

	// IF there are multiple LP types
	//    you should define the mapping of GID -> lptype index
	g_tw_lp_typemap = &suspend_typemap;

	// set the global variable and initialize each LP's type
	g_tw_lp_types = suspend_lps;
	tw_lp_setup_types();

	// Do some file I/O here? on a per-node (not per-LP) basis

	tw_run();

	tw_end();

	return 0;
}
