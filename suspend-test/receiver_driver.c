//Elsa Gonsiorowski
//September 3, 2015

#include <stdio.h>
#include "ross.h"
#include "suspend.h"

//Init function
// - called once for each LP
// ! LP can only send messages to itself during init !
void receiver_init (receiver_state *s, tw_lp *lp) {
  int self = lp->gid;
  printf("GID %d is a receiver!\n", self);

  // init state data
  s->count = 0;
  s->forward_event_count = 0;
  s->reverse_event_count = 0;
  s->net_event_count = 0;
}

//Forward event handler
void receiver_event (receiver_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
  int self = lp->gid;

  s->forward_event_count++;
  s->net_event_count++;

  switch (in_msg->type) {
    case INCREMENT :
    {
      s->count += in_msg->value;
      break;
    }
    case DECREMENT :
    {
      s->count -= in_msg->value;
      break;
    }
    default :
      tw_error(TW_LOC, "Unhandeled message type by receiver lp");
  }
}

//Reverse Event Handler
void receiver_event_reverse (receiver_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
  int self = lp->gid;

  s->reverse_event_count++;
  s->net_event_count--;

  switch (in_msg->type) {
    case INCREMENT :
    {
      s->count -= in_msg->value;
      break;
    }
    case DECREMENT :
    {
      s->count += in_msg->value;
      break;
    }
    default :
      tw_error(TW_LOC, "Unhandeled reverse message type by receiver LP");
  }
}

//report any final statistics for this LP
void receiver_final (receiver_state *s, tw_lp *lp){
  int self = lp->gid;
  printf("%d received %d forward and %d reverse messages: count is %d\n", self, s->forward_event_count, s->reverse_event_count, s->count);
}
