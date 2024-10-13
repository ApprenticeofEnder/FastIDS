#ifndef LISTENER
#define LISTENER

#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <pcap.h>
#include <stdio.h>
#include <time.h>

void packet_handler(u_char *args, const struct pcap_pkthdr *header,
                    const u_char *packet);
void print_packet_info(const u_char *packet,
                       const struct pcap_pkthdr *packet_header);

#endif
