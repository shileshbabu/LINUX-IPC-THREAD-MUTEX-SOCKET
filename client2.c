 #include "header.h"
 int main()
 {
        struct my_msg_st some_data;
        some_data.my_msg_type = 3;
        int msgid;
        char buff[20];
        msgid = msgget((key_t)2234, 0666 | IPC_CREAT);
        if (msgid == -1)
        {
                printf("msgget failed with error\n");
                goto OUT;
        }
                printf("please enter your message\n");
                fgets(buff,20, stdin);
                strcpy(some_data.some_text, buff);
                if(msgsnd(msgid,&some_data,BUFSIZ,0) == -1)
                {
                        printf("msgsnd failed\n");
                        goto OUT;
                }










        return 0;
 OUT:
        return -1;
 }
