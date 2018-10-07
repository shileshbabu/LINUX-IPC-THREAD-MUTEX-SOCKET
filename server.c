 #include "header.h"
 int main()
 {
        int msgid;
	int i;
        struct my_msg_st some_data;
        msgid = msgget((key_t)2234, 0666 | IPC_CREAT);
        if (msgid == -1)
        {
                printf("msgget failed with error: %d\n");
                goto OUT;
        }
	for(i=0;i<2;i++)
	{
        if (msgrcv(msgid,&some_data, BUFSIZ,3, 0) == -1)
        {
                printf("msgrcv failed with error\n");
                goto OUT;
        }
        printf("%s", some_data.some_text);
	sleep(2);
	}
	some_data.my_msg_type = 2;
	if(msgsnd(msgid,&some_data,BUFSIZ,0)==-1)
	{
		printf("msg send fail\n");
		goto OUT;
	}
	
	 if (msgctl(msgid, IPC_RMID, 0) == -1)
        {
                printf("msgctl(IPC_RMID) failed\n");
                goto OUT;
        }









        return 0;
 OUT:
        return -1;
 }
                
