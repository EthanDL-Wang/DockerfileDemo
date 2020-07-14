#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <mosquitto.h>

#define KEEP_ALIVE 60
#define BUF_SIZE    1024
char *ip = NULL;
char *topic = NULL;
int port = 0;

int main(int argc, char *argv[])
{
	struct mosquitto *mosq = NULL;
	bool session = true ;
	int mid;
	int i = 0;
	char buff[BUF_SIZE];
	ip = argv[1];
	port = atoi(argv[2]);
	topic = argv[3];
	mosquitto_lib_init();
	mosq = mosquitto_new(NULL, session, NULL) ;
	if(!mosq){
		printf("Mosquitto_new() failed: %s\n", strerror(errno));
		mosquitto_destroy(mosq) ;
		mosquitto_lib_cleanup() ;
	}                       
	if(mosquitto_connect(mosq, ip, port, KEEP_ALIVE) != MOSQ_ERR_SUCCESS ){
		printf("Mosq_Connect() failed: %s\n", strerror(errno));
		mosquitto_destroy(mosq) ;
		mosquitto_lib_cleanup() ;
	}
	printf("Connect %s:%d Sucessfully!\n", ip, port);
	while(1){
		memset(buff, 0, sizeof(buff));
		snprintf(buff, sizeof(buff), "I am UC8112A, I told you %d times", ++i);
		if( mosquitto_publish(mosq, &mid, topic, strlen(buff)+1, buff, 0, 0) != MOSQ_ERR_SUCCESS){   
            printf("Mosq_Publish() error: %s\n", strerror(errno));
            mosquitto_destroy(mosq) ;
            mosquitto_lib_cleanup() ;
        }
        else    
             printf("Publish information Ok %d times!\n", i) ;

		fflush(stdout);
		sleep(30);
	}

	mosquitto_destroy(mosq) ;
	mosquitto_lib_cleanup() ;
	return 0;
}
