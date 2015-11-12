//***************************************************************************
#include <unistd.h>
#include <sys/osinfo.h>
#include <time.h>
#include <process.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/dev.h>
#include "../include/shared_mem.h"


//*********************************** MAIN **********************************
void main(int argc, char *argv[])
{
 int i;

   if( argc < 2 ) {
      perror( "argc" );
      exit( 1 );
   }


    i = atoi( argv[1] );

	printf("i=%d\n",i);

	delay(1500);
	open_shmem();
	p->inbufMN3.num_com=i;
	p->inbufMN3.cr_com++;

} //*************************************************************************
