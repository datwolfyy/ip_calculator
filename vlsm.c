#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t IPADDR;

int getoct(IPADDR addr, int n_oct) {
    return (addr >> (4-n_oct)*8) & 0xFF;
}

int main(int argc, char* argv[]) {
    IPADDR network = 0;
    uint* ip_tmp = (uint*)malloc(4*sizeof(uint));
    uint nclient;
    while (printf("Mi legyen az alhálózat hálózati címe? "), scanf("%d.%d.%d.%d", &ip_tmp[0], &ip_tmp[1], &ip_tmp[2], &ip_tmp[3]) == 4) {
        for (int i = 0; i < 4; i++) {
            if (ip_tmp[i] >= 255 || (i == 3 && ip_tmp[3] % 2 != 0)) {
                printf("A(z) %d. octet hibás! Újra (csak az octetet): ", i+1);
                if (scanf("%d", &ip_tmp[i]) != 1) return -2;
            }
        }
        network |= ip_tmp[0] << 24;
        network |= ip_tmp[1] << 16;
        network |= ip_tmp[2] <<  8;
        network |= ip_tmp[3];

        free(ip_tmp);

        if (printf("Hány gépes legyen az alhálózat? "), scanf("%d", &nclient) != 1) {
            printf("Érvénytelen!\n");
            return -2;
        }

        printf("\nA hálózat IP-címe: \t%d.%d.%d.%d\n", getoct(network, 1), getoct(network, 2), getoct(network, 3), getoct(network, 4));

        IPADDR mask = 0xFFFFFFFF;
        for (int i = 1; i < (nclient % 2 == 0 ? nclient+2 : nclient+3); i*=2) {
            mask <<= 1;    
        }
        printf("Alhálózati maszk: \t%d.%d.%d.%d\n", getoct(mask, 1), getoct(mask, 2), getoct(mask, 3), getoct(mask, 4));

        IPADDR addr_min = network+1;
        IPADDR addr_max = (network | ~mask)-1;
        printf("Tartomány: \t\t%d.%d.%d.%d - %d.%d.%d.%d\n", getoct(addr_min, 1), getoct(addr_min, 2), getoct(addr_min, 3), getoct(addr_min, 4), \
                getoct(addr_max, 1), getoct(addr_max, 2), getoct(addr_max, 3), getoct(addr_max, 4));
        
        IPADDR broadcast = (network | ~mask);
        printf("Szórási cím: \t\t%d.%d.%d.%d\n", getoct(broadcast, 1), getoct(broadcast, 2), getoct(broadcast, 3), getoct(broadcast, 4));
        return 0;
    }
    return -1;
}