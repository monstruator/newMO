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
  
  #define TIMEOUT_SEC		   0L	//0 секунд
#define TIMEOUT_NSEC	10000000L	//макс. время ожидания 10 мс
#define LENBUFWR	80	//длина буфера передачи
#define LnTitle		32		//длина заголовка
#define LENBUFRD 	1400	//длина буфера приема
#define LnKdr	   512	//макс число слов(2 байта) в кадре
#define MaxKdr	  10000	//макс число хранимых кадров
//  #include "../include/func_IP.h"
  #include "../include/shared_mem.h"
  
#define MS 1000000
#define N_CHAN 2
//===============================================================================
un short bufW [LENBUFWR], bufR [LENBUFRD];

un short *ptbufW,*ptbufR;

un short BKdr[MaxKdr][LnKdr];//буфер принятых кадров
un int pRdBKdr=0;pWrBKdr=0;	//указатели чтения и записи в BKdr
int NmKdr=0;	//число кадров в очереди на чтение в МН3
int SocketSTOP=0;//сигнал переполнения буфера принятых кадров
 
pid_t proxy_time;
volatile un counter;

timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;

int T_ALRM =0;
char Host[12];

int Seans=0,Step=0,Kdr=0; 
long NmbKDR=0;//число принятых кадров
long SumDate=0;//число принятых данных
//int pt1=0;OTL1[150*100];

int NmbMes=1;//номер сообщения
un short TimeL=0,TimeH=0;//
//--------- обработчик прерывания от таймера 50мс -----------------------------
pid_t far handler_time()
{/*выдача "proxy" каждое 2-е прерывание (раз в 100мс) */
  if (( ++counter % 2)==0)
	return (proxy_time);	
  return (0);			
} 
//------------------ Функция обработки СИГНАЛА --------------------------------
void SigHandler ( int signal_number )	
	{ // Обработка сигнала от таймера об истечении времени ожидания ответа
	printf("\n%s Сеанс: %d-%d-K%d Нет готовности ",Host,Seans,Step,Kdr);
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
	if (argc<3) {printf("\nНе указаны хост или порт\n");exit(0);}	
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
 tm10 = timer_create(CLOCK_REALTIME,&event_sig ); // создание таймера 
 if (tm10==-1) printf("\nОшиБка открытия таймера: %s",strerror(errno));
	timer_sig.it_value.tv_sec        = 0L;
	timer_sig.it_value.tv_nsec       = 0L;
	timer_sig.it_interval.tv_sec     = 0L;
	timer_sig.it_interval.tv_nsec    = 0L;
	signal ( SIGALRM, SigHandler );
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//            установление обмена с сервером  
printf("START\n\n");
	T_ALRM =0;Seans++;Step=1;Kdr=0;//===== Подключение СОКЕТА =====
	timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*5; //5*10ms
	 rez=timer_settime( tm10, 0, &timer_sig,NULL); // запуск таймера
	if (rez==-1)    printf("%s сеанс %d ошибка ЗАпуска таймера %s \n",argv[1],Seans,strerror(errno));     

	printf("Create Socket\n");
	sock1 = CrSocket(argv[1],argv[2]);

	if (T_ALRM !=0) 
	{
		printf("\n%s %s не подключить СОКЕТ",argv[1],Seans);
		goto EndCeanc;//нет связи с КАСРТ 		====>>
	}
	timer_sig.it_value.tv_nsec = 0L;
	timer_settime( tm10, 0, &timer_sig,NULL); // останов таймера
	if (sock1==-1) 		{printf("\nСеанс %d не подключить СОКЕТ к %s  %s\n",Seans,argv[1],argv[2]);	  	goto EndCeanc;} //нет связи с КАСРТ 		====>>
	
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
