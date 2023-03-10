#ifndef _A__
#define _A__

#define KEYPATH     "./tmp10"
#define KEYPROJ     'K'
#define NAMESIZE 32
struct msg_st{
    long mtype;
    char name[NAMESIZE];
    int math;
    int chinese;
};


#endif