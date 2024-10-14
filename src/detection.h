#ifndef DETECTION
#define DETECTION

typedef struct ids_rule {
    char *message;
    int signature_id;
    int group_id;
    char *classtype;
    int priority;
    // Convert these to hash tables?
    char *ip_source;
    char *ip_dest;
    int port_source;
    int port_dest;
} ids_rule_t;

int load_rules();
void cleanup_rules();
void match_rule();
void alert_worker();

// Need to implement the rete algorithm for detection

// AsyncQueue for alerting
// Probably anywhere from 1-4 workers each for alerting
#endif
