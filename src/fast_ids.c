#include <arpa/inet.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <string.h>

int run(pcap_if_t *network_device) {
    printf("Device Name: %s\n", network_device->name);
    return 0;
}

int load_devices(pcap_if_t **all_devices) {
    char error_buffer[PCAP_ERRBUF_SIZE];
    printf("Loading network devices...\n");
    int findalldevs_status = pcap_findalldevs(all_devices, error_buffer);
    if (findalldevs_status == PCAP_ERROR) {
        fprintf(stderr, "Error loading devices: %s\n", error_buffer);
        return 2;
    }

    if (all_devices == NULL) {
        fprintf(stderr, "No devices found. Exiting.\n");
        return 1;
    }

    printf("Load successful.\n");

    return 0;
}

int main(int argc, char *argv[]) {

    pcap_if_t *all_devices = NULL, *network_device = NULL;
    int load_devices_status, status;

    load_devices_status = load_devices(&all_devices);

    if (load_devices_status > 0) {
        return load_devices_status;
    }

    // Linked list, we're just interested in the first device.
    network_device = all_devices;

    status = run(network_device);
    pcap_freealldevs(all_devices);
    return status;
}
