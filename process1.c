 #include "header.h"
 int main()
 {
        int msgid;
        struct my_msg_st some_data;
        msgid = msgget((key_t)2234, 0666 | IPC_CREAT);
        if (msgid == -1)
        {
                printf("msgget failed with error: %d\n");
                goto OUT;
        }
        if (msgrcv(msgid,&some_data, BUFSIZ,2, 0) == -1)
        {
                printf("msgrcv failed with error\n");
                goto OUT;
        }
        printf("process_data=%s", some_data.some_text);
        sleep(1);	
	return 0;
OUT:
	return -1;
}
