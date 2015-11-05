//Elsa Gonsiorowski
//September 3, 2015

#ifndef _suspend_h
#define _suspend_h

#include "ross.h"

//Example enumeration of message type... could also use #defines
typedef enum {
  WAKEUP,
  INCREMENT,
  DECREMENT,
} message_type;

//Message struct
//   this contains all data sent in an event
typedef struct {
  message_type type;
  int value;
} message;


//State struct
//   this defines the state of each LP
typedef struct {
	int increment_value;
	int round_count;
} increment_state;

typedef struct {
	int decrement_value;
	int round_count;
} decrement_state;

typedef struct {
	int count;
	int forward_event_count; // DON'T ROLL THIS BACK! (value is nondeterministic)
	int reverse_event_count; // DON'T ROLL THIS BACK! (value is nondeterministic)
	int net_event_count;
} receiver_state;

//Command Line Argument declarations
extern unsigned int total_receivers;

//Global variables used by both main and driver
// - this defines the LP types
extern tw_lptype suspend_lps[];

// Each LP type gets its own set of functions

// defined in increment_driver.c:
extern void increment_init(increment_state *s, tw_lp *lp);
extern void increment_event(increment_state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void increment_event_reverse(increment_state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void increment_final(increment_state *s, tw_lp *lp);

// defined in decrement_driver.c:
extern void decrement_init(decrement_state *s, tw_lp *lp);
extern void decrement_event(decrement_state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void decrement_event_reverse(decrement_state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void decrement_final(decrement_state *s, tw_lp *lp);

// defined in receiver_driver.c:
extern void receiver_init(receiver_state *s, tw_lp *lp);
extern void receiver_event(receiver_state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void receiver_event_reverse(receiver_state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void receiver_final(receiver_state *s, tw_lp *lp);

// All lp types can have same mapping
// found in suspend_map.c
extern tw_peid suspend_map(tw_lpid gid);
extern tw_lpid suspend_typemap(tw_lpid gid);

/*
//Custom mapping prototypes
void suspend_cutom_mapping(void);
tw_lp * suspend_mapping_to_lp(tw_lpid lpid);
tw_peid suspend_map(tw_lpid gid);
*/

#endif
