#ifndef MAC_H
#define MAC_H

void mac_key(vector K1, vector K2, vector R);
void C_mac(vector block, vector K_, vector C, int flag_mac);
void mac(FILE *input, FILE *output, size_t size);

#endif
