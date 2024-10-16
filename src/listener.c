#include "listener.h"
#include "detection/detection.h"

void packet_handler(u_char *args, const struct pcap_pkthdr *header,
                    const u_char *packet) {
    print_packet_info(packet, header);
    // Listener for various rules, probably add an extra parameter
    return;
}
void print_packet_info(const u_char *packet,
                       const struct pcap_pkthdr *packet_header) {
    printf("Packet capture length: %d\n", packet_header->caplen);
    printf("Packet total length: %d\n", packet_header->len);
}
