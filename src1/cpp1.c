  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include "../include/USOIwrk.h"
  #include "../include/CrSocket.h"
  #include "../include/MesForm.h"
  
  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  
  #define TIMEOUT_SEC		   0L	//0 ������
#define TIMEOUT_NSEC	10000000L	//����. ����� �������� 10 ��
#define LENBUFWR	80	//����� ������ ��������
#define LnTitle		32		//����� ���������
#define LENBUFRD 	1400	//����� ������ ������
#define LnKdr	   512	//���� ����� ����(2 �����) � �����
#define MaxKdr	  10000	//���� ����� �������� ������
//  #include "../include/func_IP.h"
  #include "../include/shared_mem.h"
  
#define MS 1000000
#define N_CHAN 2
//===============================================================================
un short bufW [LENBUFWR], bufR [LENBUFRD];

un short *ptbufW,*ptbufR;

un short BKdr[MaxKdr][LnKdr];//����� �������� ������
un int pRdBKdr=0;pWrBKdr=0;	//��������� ������ � ������ � BKdr
int NmKdr=0;	//����� ������ � ������� �� ������ � ��3
int SocketSTOP=0;//������ ������������ ������ �������� ������
 
pid_t proxy_time;
volatile un counter;

timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;

int T_ALRM =0;
char Host[12];

int Seans=0,Step=0,Kdr=0; 
long NmbKDR=0;//����� �������� ������
long SumDate=0;//����� �������� ������
//int pt1=0;OTL1[150*100];

int NmbMes=1;//����� ���������
un short TimeL=0,TimeH=0;//
//--------- ���������� ���������� �� ������� 50�� -----------------------------
pid_t far handler_time()
{/*������ "proxy" ������ 2-� ���������� (��� � 100��) */
  if (( ++counter % 2)==0)
	return (proxy_time);	
  return (0);			
} 
//------------------ ������� ��������� ������� --------------------------------
void SigHandler ( int signal_number )	
	{ // ��������� ������� �� ������� �� ��������� ������� �������� ������
	printf("\n%s �����: %d-%d-K%d ��� ���������� ",Host,Seans,Step,Kdr);
	T_ALRM=1; 
	}
//===============================================================================

main(int argc, char *argv[])
{
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
	int sock1,LnbufW,LnbufR=LENBUFRD;
	pid_t pid1;
//-------------------------------------------------------------------------------
	if (argc<3) {printf("\n�� ������� ���� ��� ����\n");exit(0);}	
	memcpy(Host,argv[1],5);
//-------------------------------------------------------------------------------
	ptbufW=bufW;
	ptbufR=bufR;
	memset(bufR,0,sizeof(bufR));
	memset(bufW,0,sizeof(bufW));
//char msg1 [200];
	int n,m,k,j,r;
	int rez;
    //create_shmem();
	event_sig.sigev_signo = SIGALRM;
 tm10 = timer_create(CLOCK_REALTIME,&event_sig ); // �������� ������� 
 if (tm10==-1) printf("\n������ �������� �������: %s",strerror(errno));
	timer_sig.it_value.tv_sec        = 0L;
	timer_sig.it_value.tv_nsec       = 0L;
	timer_sig.it_interval.tv_sec     = 0L;
	timer_sig.it_interval.tv_nsec    = 0L;
	signal ( SIGALRM, SigHandler );
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//            ������������ ������ � ��������  
printf("START\n\n");
	T_ALRM =0;Seans++;Step=1;Kdr=0;//===== ����������� ������ =====
	timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*5; //5*10ms
	 rez=timer_settime( tm10, 0, &timer_sig,NULL); // ������ �������
	if (rez==-1)    printf("%s ����� %d ������ ������� ������� %s \n",argv[1],Seans,strerror(errno));     

	printf("Create Socket\n");
	sock1 = CrSocket(argv[1],argv[2]);

	if (T_ALRM !=0) 
	{
		printf("\n%s %s �� ���������� �����",argv[1],Seans);
		goto EndCeanc;//��� ����� � ����� 		====>>
	}
	timer_sig.it_value.tv_nsec = 0L;
	timer_settime( tm10, 0, &timer_sig,NULL); // ������� �������
	if (sock1==-1) 		{printf("\n����� %d �� ���������� ����� � %s  %s\n",Seans,argv[1],argv[2]);	  	goto EndCeanc;} //��� ����� � ����� 		====>>
	
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
