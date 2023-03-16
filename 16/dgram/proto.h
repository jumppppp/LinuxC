#ifndef __PO_
#define __PO_

#define PORT  "2000"
#define NAMESIZE 111

struct msg_st{
    char name[NAMESIZE];
    int math;
    int chinese;

}__attribute__((packed));


#endif