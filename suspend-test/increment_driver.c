//Elsa Gonsiorowski
//September 3, 2015

#include <stdio.h>
#include "ross.h"
#include "suspend.h"

//Init function
// - called once for each LP
// ! LP can only send messages to itself during init !
void increment_init (increment_state *s, tw_lp *lp) {
  int self = lp->gid;
  printf("GID %d is an incrementer!\n", self);

  // init state data
  s->increment_value = 1;
  s->round_count = 0;

  // Init message to myself
  tw_event *e = tw_event_new(self, 1, lp);
  message *msg = tw_event_data(e);
  msg->type = WAKEUP;
  tw_event_send(e);
}

//Forward event handler
void increment_event (increment_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
  int self = lp->gid;

  if (in_msg->type != WAKEUP) {
    tw_error(TW_LOC, "Increment LP received wrong message type");
  }

  s->round_count++;
  
  // Long loop to slow down the increment LP
  int i;
  int dummy;
  for (i = 0; i < 10000; i++){
    dummy = dummy + 7;
    dummy = dummy - 100;
    dummy = 93 + (10 * dummy);
    dummy /= 10;
    dummy = 0;
  }

  for (i = 0; i < total_receivers; i++) {
    tw_event *e = tw_event_new(i+2, 1, lp);
    message *msg = tw_event_data(e);
    msg->type = INCREMENT;
    msg->value = s->increment_value;
    tw_event_send(e);
  }

  // Wakeup self
  tw_event *e = tw_event_new(self, 2, lp);
  message *msg = tw_event_data(e);
  msg->type = WAKEUP;
  tw_event_send(e);
}

//Reverse Event Handler
void increment_event_reverse (increment_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
  // there is nothing to do here
  return;
}

//report any final statistics for this LP
void increment_final (increment_state *s, tw_lp *lp){
  int self = lp->gid;
  printf("%d sent %d rounds of increment messages, each with value %d\n", self, s->round_count, s->increment_value);
}
