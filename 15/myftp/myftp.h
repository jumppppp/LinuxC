#ifndef MY_FTP_
#define MY_FTP_

#define KEYPATH "./tmp1"
#define KEYPROJ 'p'
#define KEYPATH2 "./tmp2"
#define KEYPROJ2 'm'
#define PATHMAX 1024
#define DATAMAX 1024
enum{
    MSG_PATH =1,
    MSG_DATA,
    MSG_EOT,
};
struct msg_path_st{
    long mtype;
    char path[PATHMAX];
};
struct msg_data_st{
    long mtype;
    char data[DATAMAX];
    int datalen;
};


#endif

