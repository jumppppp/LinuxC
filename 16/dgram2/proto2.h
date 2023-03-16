#ifndef __PO_
#define __PO_
#include <stdint.h>
#define PORT "2000"
#define NAMESIZE (512 - 8 - 8)

struct msg_st
{

    uint32_t math;
    uint32_t chinese;
    uint8_t name[1];

} __attribute__((packed));

#endif