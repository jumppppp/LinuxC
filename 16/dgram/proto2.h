#ifndef __PO_
#define __PO_

#define PORT  "2000"
#define NAMESIZE (512-8-8)

struct msg_st{
    uint8_t name[1];
    uint32_t  math;
    uint32_t chinese;

}__attribute__((packed));


#endif