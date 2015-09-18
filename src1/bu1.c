  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
//  #include "../include/func_IP.h"
  #include "../include/shared_mem.h"
  
#define MS 1000000
#define N_CHAN 1


main()
{//--- KOHCTAHTbl npu6opa 1.0 ---//
    int sock, length, i , count_mes=0, i1 , i_p=0 , i2=0;
    char bufi[1024];
    char bufo[1024];
    char out_buf[1024];
    int r,bytes,COM=0;
    packusoi p1;
    packcmd p2;
    timer_t id;
    short c_step=0;	
    struct itimerspec timer;
    struct sigevent event;
    pid_t pid, proxy_BU;
    short T0=0;
    long bu1_timer=0;
    int data_read; //4tenie dannih 
	
    //create_shmem();
	delay(500);
	open_shmem();
	delay(500);
	
	
	while(1)
	{
		if (bu1_timer!=p->sys_timer) //timer
		{
			bu1_timer=p->sys_timer;
			if (p->cur_step!=0) //est' wag dl9 vipolnenni9
			{
				c_step=p->cur_step;
				for (i=0;i<p->work_com[c_step].num_mini_com;i++) //prosmotrim vse minicomandi na wage 
					if(p->work_com[c_step].s[i].n_chan==N_CHAN) //na tekuwem wage (i - minikomanda) est' komanda dl9 nas
					{
						printf("STEP=%d    minicom for 1 chan : %d status=%d time %d T0=%d\n", p->cur_step,  p->work_com[c_step].s[i].n_com, p->work_com[c_step].s[i].status, p->sys_timer, T0);

						switch(p->work_com[c_step].s[i].n_com)
						{
							case 1: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {   
                                        printf("Send to 1 chan\n");
                                        p->work_com[c_step].s[i].status=2;
                                    }
                                    break;
							
                            case 2: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {   
                                        printf("Send to 1 chan\n");
                                        //p->work_com[c_step].s[i].t_start=p->sys_timer; // vrem9 starta
                                        //p->work_com[c_step].s[i].t_stop =p->sys_timer+300; //stop ne pozdnee
                                        T0=0; //ots4et vremeni (vremenno)
                                        p->work_com[c_step].s[i].status=1;
                                    }
                                    if (p->work_com[c_step].s[i].status==1) //zdem otveta
                                    {   
                                        if (data_read==1) //bilo 4tenie 
                                        {
                                            p->work_com[c_step].s[i].status=2;
                                            data_read=0;
                                        }
                                    }
                                    break;

							default: printf("Bad minicom for 1 chan : %d",p->work_com[c_step].s[i].n_com);					
						}//switch (n_com)
						//-------------------------------------------------------
                        //esli previweno vrem9 ozhidani9
						//if ((p->work_com[c_step].s[i].status==1)&&(p->work_com[c_step].s[i].t_stop>p->sys_timer)) p->work_com[c_step].s[i].status=3;
                        
						//-------------------------------------------------------						
					}//ewe ne vipoln9li
		
					//if (p->work_com[c_step].s[i].w_answ[0]==2) //esli nado gdat' otveta
					//if (p->work_com[c_step].s[i].w_answ[1]=1)
					//-------VREMENNO PRIEM DANNIH-------------------------------
					T0++;
					if (T0==30)
					{
						T0=0;	
						data_read=1;
					}		
					//-----------------------------------------------------------				
			} //step>0
		}//timer
	}//while

}
