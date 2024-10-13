#include <arpa/inet.h>
#include <netinet/in.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "listener.h"

char *get_readable_ip(pcap_addr_t *device_addr) {
    char *ip = malloc(INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(((struct sockaddr_in *)device_addr->addr)->sin_addr),
              ip, INET_ADDRSTRLEN);
    return ip;
}

int run(pcap_if_t *network_device, pcap_addr_t *device_addr) {
    char error_buffer[PCAP_ERRBUF_SIZE];
    char *ip = get_readable_ip(device_addr);
    pcap_t *handle;
    int timeout_limit = 10000; /* In milliseconds */

    handle = pcap_open_live(network_device->name, BUFSIZ, 0, timeout_limit,
                            error_buffer);

    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", network_device->name,
                error_buffer);
        return 2;
    }

    printf("Listening on device %s on address %s\n", network_device->name, ip);
    free(ip);
    pcap_loop(handle, 0, packet_handler, NULL);
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

int get_first_usable_device(pcap_if_t *all_devices, pcap_if_t **network_device,
                            pcap_addr_t **device_addr) {
    pcap_if_t *chosen_device;
    for (chosen_device = all_devices; chosen_device != NULL;
         chosen_device = chosen_device->next) {
        pcap_addr_t
            *dev_addr; // interface address that used by pcap_findalldevs()

        /* check if the device captureble*/
        for (dev_addr = chosen_device->addresses; dev_addr != NULL;
             dev_addr = dev_addr->next) {
            if (dev_addr->addr->sa_family == AF_INET && dev_addr->addr &&
                dev_addr->netmask) {
                char *ip = get_readable_ip(dev_addr);
                printf("Found a device %s on address %s\n", chosen_device->name,
                       ip);
                free(ip);
                *network_device = chosen_device;
                *device_addr = dev_addr;
                return 0;
            }
        }
    }
    fprintf(stderr, "No suitable devices found. Exiting.\n");
    return 1;
}

int main(int argc, char *argv[]) {
    pcap_if_t *all_devices = NULL, *network_device = NULL;
    pcap_addr_t *device_addr = NULL;
    int load_devices_status, get_usable_device_status, status;

    load_devices_status = load_devices(&all_devices);
    if (load_devices_status > 0) {
        return load_devices_status;
    }

    get_usable_device_status =
        get_first_usable_device(all_devices, &network_device, &device_addr);
    if (get_usable_device_status > 0) {
        return get_usable_device_status;
    }
    status = run(network_device, device_addr);
    pcap_freealldevs(all_devices);
    return status;
}
