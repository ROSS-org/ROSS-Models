#include "ross.h"

FILE *rng_event_log;

typedef struct {
} message;

typedef struct {
} state;

void rngt_init(state *s, tw_lp *lp)
{
    tw_event *e;
    
    e = tw_event_new(lp->gid, 1.0, lp);
    
    tw_event_send(e);
}

void rngt_event(state *s, tw_bf *bf, message *m, tw_lp *lp)
{
    int i;
    double temp;
    
    for (i = 0; i < 100; i++) {
        temp = tw_rand_unif(lp->rng);
        fprintf(rng_event_log, "%lf \n", temp);
    }
}

void rngt_final(state *s, tw_lp *lp)
{
}

tw_peid rngt_map(tw_lpid gid)
{
    return (tw_peid) gid / g_tw_nlp;
}

tw_lptype rng_lps[] = {
    {
        (init_f) rngt_init,
        (pre_run_f) NULL,
        (event_f) rngt_event,
        (revent_f) 0, // model_event_reverse,
        (final_f) rngt_final,
        (map_f) rngt_map,
        sizeof(state)
    },
    { 0 },
};

#define rng_main main

int rng_main(int argc, char *argv[])
{
    int i;
    
    int32_t local_seed[] = { 5555, 6666, 7777, 8888 };
    // Do this *BEFORE* tw_init() is called
    g_tw_rng_seed = local_seed;

    rng_event_log = fopen("rng_log.txt", "w");
    if (rng_event_log == NULL) {
        tw_error(TW_LOC, "Failed to open rng_log.txt\n");
    }

    tw_init(&argc, &argv);
    
    // Note: you must pass the same value as the last arg. to tw_define_lps()
    tw_define_lps(1, sizeof(message), local_seed);
    
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &rng_lps[0]);
    }
    
    tw_run();
    
    tw_end();
    
    fclose(rng_event_log);
    
    return 0;
}
