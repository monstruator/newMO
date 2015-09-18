#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <stdlib.h>
#include "../include/shared_mem.h"

#include <math.h>
#define MS 1000000

void main( int argc, char *argv[] )
{
	unsigned short cr_com,data_count=0;
	unsigned int TCount=0,DTTM=0; //общий таймер, последний приход данных
	int TC10=0; //таймер по 100 мс
	int Mes;
    timer_t id;
	unsigned int i,i2=0;
    struct itimerspec timer;
    struct sigevent event;
	pid_t pid, proxy;

	while( (i=getopt(argc, argv, "mis:") )!=-1)	{
		switch(i){
			case 'p' :  break;
			case 's' :	break;//sscanf(optarg,"%f",&porog_sf); printf("Yaa Zdes!!\n"); break;
			case 'i' :	break;//sscanf(optarg,"%f",&porog_df); break;
		}//switch
	}//while
	
//	porog_sf = atof(argv[2]);
//	porog_df = atof(argv[3]);

	create_shmem();
	delay(300);
	open_shmem();
	delay(2300);


	//----------------------------------------------------
	/* Get a proxy for the timer to kick */
    proxy = qnx_proxy_attach( 0, 0, 0, -1 );
    if( proxy == -1 ) {
      printf( "Unable to attach proxy." );
      return;
    }

    /* Attach to the timer */
    event.sigev_signo = -proxy;
    id = timer_create( CLOCK_REALTIME, &event );
    if( id == -1 ) {
      printf( "Unable to attach timer." );
      return;
    }



    timer.it_value.tv_sec     = 2L; //start after X sec
    timer.it_value.tv_nsec    = 0L;
    timer.it_interval.tv_sec  = 0;
    timer.it_interval.tv_nsec = 30*MS;
    timer_settime( id, 0, &timer, NULL );

    while(1) 
	{
    	pid=Receive( 0 , 0, 0 );
		if (pid==proxy) //обработчик таймера
		{
			TCount++;
			TC10++;
			if (TC10==10) TC10=0;
			p->sys_timer++;
			//printf("%d\n",p->sys_timer);
		}
//----------------------------чтение К1-----------------------------
    }

    timer_delete( id );
  }