 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <unistd.h>
 #include <sys/msg.h>
 struct my_msg_st
 {
        long int my_msg_type;
        char some_text[BUFSIZ];
 };

