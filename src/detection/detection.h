#ifndef DETECTION
#define DETECTION

#include <glib.h>

/* actions
- alert
- pass
- drop
- reject
- rejectsrc
- rejectdest
- rejectboth
*/
#define PASS 0
#define ALERT 1
#define DROP 2
#define REJECT_SRC 4
#define REJECT_DEST 8
#define REJECT REJECT_SRC
#define REJECT_BOTH 12

struct protocol_match;
struct direction_match;
struct ip_match;
struct port_match;
struct rule;

typedef struct rules_matcher {
    // protocol_match **protocol_matchers;
    GHashTable *protocol_matchers;
} rules_matcher_t;

typedef struct protocol_match {
    char *protocol;
    GHashTable *ip_matchers;
} protocol_match_t;

typedef struct ip_match {
    char *ip;
    GHashTable *port_matchers;
} ip_match_t;

typedef struct port_match {
    int port;
    struct rule **rules;
} port_match_t;

typedef struct rule {
    char action;
} rule_t;

typedef struct ip_rule {
    rule_t super;
} ip_rule_t;

typedef struct tcp_rule {
    rule_t super;
} tcp_rule_t;

typedef struct udp_rule {
    rule_t super;
} udp_rule_t;

typedef struct icmp_rule {
    rule_t super;
} icmp_rule_t;

typedef struct http_rule {
    rule_t super;
} http_rule_t;

typedef char action_t;

int load_rules();
void cleanup_rules();
action_t analyze_packet();
void alert_worker();

// AsyncQueue for alerting
// Probably anywhere from 1-4 workers each for alerting
#endif
