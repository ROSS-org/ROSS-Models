# suspend-test
Model for testing the LP-Suspend feature in ROSS

## Model Description

This model is based on a simple ping-pong scheme.
One LP sends "ping" messages, where another LP sends "pong" messages, the remaining LPs listen to these messages.
The timing of the model ensures that the messages are scheduled to alternate: ping, pong, ping, pong.
There is one caveat, the LP running sending the "ping" messages is slow.

During sequential or conservative simulation, a single slow LP is not an issue.
All of the listening LPs are guarenteed to receive properly ordered "ping, pong, ping, pong" messages.
It is in optimistic simulation that the correct ordering of events is **not** guarenteed.
In this case, receiver LPs may hear "ping, pong, pong, pong."
Instead of continuing to listen, the receivers enter suspend mode and wait until proper event ordering occurs.
