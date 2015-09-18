  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

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
		  
#include "../include/shared_mem.h"
#include "../include/USOIwrk.h"
#include "../include/CrSocket.h"
#include "../include/MesForm.h"


  
#define MS 1000000
#define N_CHAN 2 //CPP SPC

#ifdef __USAGE
		  %C - эта программа выполняет функции клиента при обмене по протоколу 
		  TCP/IP.
		  программа требует параметры: 
		  адрес сервера(например CPP1)	
		  порт сервера(например 4000). 
		  при запуске программа каждые 100 мс устанавливает связь с сервером,
		  посылает ему команды (сообщения) и получает ответные данные, которые
		  помещает в массив разделяемой (общей) памяти.
		  %C [опции]

		  опции:
		  1-й параметр 	имя хоста сервера
		  2-й параметр 	номер порта сервера

	#endif

un short bufW [LENBUFWR], bufR [LENBUFRD];
pid_t proxy_time;
volatile un counter;
struct zag_CPP mes_cpp, *mes_fcpp;
struct from_cpp12 *f12;
struct to_cpp11 f11;
timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;
unsigned short *aaa,*bbb;

int T_ALRM =0; //prizn srabativani9 taimera
char Host[12]="CPP",port[4]="4004";
int Seans=0; 
//--------- timer 50ms -----------------------------
pid_t far handler_time()
{
  if (( ++counter % 2)==0)
	return (proxy_time);	
  return (0);			
} 
//------------------ SIGNAL --------------------------------
void SigHandler ( int signal_number )	
{
	if (p->verbose>2) printf("\n%s.    seanse: %d error",Host,Seans);
	T_ALRM=1; 
}

short tcp_send_read(int );
//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main(int argc, char *argv[])
{
	
	int n,i,j,col,command,i1;
	
	packusoi p1;
    packcmd p2;
    short c_step=0,T0=0;	
    long cpp_timer=0;
    int data_read; //4tenie dannih 
	if (p->verbose) printf("START MO3A<->CPP\n\n");
	if (argc<3) printf("\nhost and port number dont entering\n");
	else 
	{	
		memcpy(Host,argv[1],5);
		memcpy(port,argv[2],5);
	}	
	//===============================================================================
//			 timer 10ms
	event_sig.sigev_signo = SIGALRM;
	tm10 = timer_create(CLOCK_REALTIME,&event_sig ); // ёючфрэшх ЄрщьхЁр 
	if (tm10==-1) printf("\ntimer opening error: %s",strerror(errno));
	timer_sig.it_value.tv_sec        = 0L;
	timer_sig.it_value.tv_nsec       = 0L;
	timer_sig.it_interval.tv_sec     = 0L;
	timer_sig.it_interval.tv_nsec    = 0L;
	signal ( SIGALRM, SigHandler );
	//create_shmem();
	delay(500);
	open_shmem();
	delay(500);
	
//---------------------------------------------------------------------	
	while(1)
	{
		if (cpp_timer!=p->sys_timer) //timer
		{
			cpp_timer=p->sys_timer;
			if (p->cur_step!=0) //est' wag dl9 vipolnenni9
			{
				c_step=p->cur_step;
				for (i=0;i<p->work_com[c_step].num_mini_com;i++) //prosmotrim vse minicomandi na wage 
					if((p->work_com[c_step].s[i].n_chan==N_CHAN)&&(p->work_com[c_step].s[i].status==0)) //na tekuwem wage (i - minikomanda) est' komanda dl9 nas
					{
						printf("STEP=%d    minicom for 2 chan : %d status=%d time %d T0=%d\n", p->cur_step,  p->work_com[c_step].s[i].n_com, p->work_com[c_step].s[i].status, p->sys_timer, T0);

						switch(p->work_com[c_step].s[i].n_com)
						{
							case 1: 	p->work_com[c_step].s[i].status=1;
                                        if(p->verbose) printf("SVCH work (TC=3)\n");
										memset((char *)&f11, 0, sizeof(struct to_cpp11));
										f11.zag.reserv=sizeof(struct form11);
										f11.zag.II=1;
										f11.zag.TS=3;
										f11.zag.PS=1;
										//---------------------------------
										f11.data.nf=11;
										f11.data.KU0=0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
										f11.data.ustKU0=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										bbb = (unsigned short *)&f11;	
										col = sizeof(f11);
										if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col;i1++) printf("%x ",bbb[i1]);printf("\n");}
										col=tcp_send_read(col);
										if (col==0x14) //esli otet=sosto9nie 
										{
											//if (f12->data.SS0_all) 
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else p->work_com[c_step].s[i].status=3;
                                        printf("col=%d status=%d\n",col/2,p->work_com[c_step].s[i].status);
									    break;
							case 2: 	p->work_com[c_step].s[i].status=1;
                                        if(p->verbose) printf("SVCH PRD-PRM CHAN (TC=3)\n");
										memset((char *)&f11, 0, sizeof(struct to_cpp11));
										f11.zag.reserv=sizeof(struct form11);
										f11.zag.II=1;
										f11.zag.TS=3;
										f11.zag.PS=1;
										//---------------------------------
										f11.data.nf=11;
										f11.data.KU5=p->inbufMN3.a_params[0]; //// RT PRD 1 - 6
										f11.data.ustKU5=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										f11.data.KU4=p->inbufMN3.a_params[0]+6; //// RT PRD 1 - 6
										f11.data.ustKU4=1; // 1 - ustanovit' , 0 - ne ustanavlivat'
										bbb = (unsigned short *)&f11;	
										col = sizeof(f11);
										if(p->verbose>2) {printf("<-Send ");for(i1=0;i1<col;i1++) printf("%x ",bbb[i1]);printf("\n");}
										col=tcp_send_read(col);
										if (col==0x14) //esli otet=sosto9nie 
										{
											if(p->verbose>1) printf("SS4=%d SS5=%d \n",f12->data.SS4,f12->data.SS5);
											p->work_com[c_step].s[i].status=2; // ispravnost'
										}
										else p->work_com[c_step].s[i].status=3;
                                        break;
							
                            case 3: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
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
									case 101: if (p->work_com[c_step].s[i].status==0) //na4alo vipolneni9
                                    {   
                                        if(p->verbose) printf("Check CPP link (TC=0)\n");
										//tcp_send_read();
                                        p->work_com[c_step].s[i].status=2;
                                    }
                                    break;
							default: 
									printf("Bad minicom for 1 chan : %d",p->work_com[c_step].s[i].n_com);					
									p->work_com[c_step].s[i].status=3;
									
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
	timer_delete(tm10);
}


short tcp_send_read(int col)
{
	int sock1;
	short rez;
	int i,i1,n,j;
	short status;
	

//message
	/*mes_cpp.marker1=0xFFFF;
	mes_cpp.marker2=0xFFFF;
	mes_cpp.KSS=0;
	mes_cpp.II=0;
	mes_cpp.TS=0;
	mes_cpp.PS=1;
	*/
	f11.zag.marker1=0xFFFF;
	f11.zag.marker2=0xFFFF;
	
	
	//            starting connection
	for(i1=0;i1<3;i1++)
	{
		T_ALRM =0;
		timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*5; //5*10ms
		rez=timer_settime( tm10, 0, &timer_sig,NULL); //start timer
		if (rez==-1)    printf("%s. seanse %d. start timer error\n",Host,Seans);     

		if (p->verbose>1) printf("Create Socket : ");
		sock1 = CrSocket(Host,port);
		
		rez=1;
		if ((T_ALRM !=0)||(sock1==-1)) 
		{
			if (p->verbose>1) printf("error\n",Host,Seans);
			rez=0;
			//goto EndCeanc;
		}
		else 
		{
			if (p->verbose>1) printf("ok\n",Host,Seans);
			i1=3; //exit from "for"
		}
		timer_sig.it_value.tv_nsec = 0L;	timer_settime( tm10, 0, &timer_sig,NULL); // stop timer
		delay(100);
	}
	if (rez) //send message
	{
			i1=3; //exit from "for"
			T_ALRM =0;
			timer_sig.it_value.tv_nsec = TIMEOUT_NSEC*10;  
			timer_settime( tm10, 0, &timer_sig,NULL); ////start timer 
//-----------------------------------------------------------------
			write(sock1, bbb, col);	Seans++;
			n=read(sock1,bbb,1400);
			timer_sig.it_value.tv_nsec = 0L;	timer_settime( tm10, 0, &timer_sig,NULL); // останов таймера
			close(sock1);
//-----------------------------------------------------------------			
			if ((n>0)&&(T_ALRM==0))
			{			
				if(p->verbose>1) {printf("->Read %d word : ",n/2); for (j=0;j<n/2;j++ ) printf(" %x",bbb[j]); printf("\n");}
				//mes_fcpp = (struct zag_CPP *)bbb;
				f12 = (struct from_cpp12 *)bbb;
				if(p->verbose>1) printf("KSS=%d II=%d TS=%d      ", f12->zag.KSS,f12->zag.II,f12->zag.TS);
				switch(f12->zag.TS)
				{
					case 0x10 : if(p->verbose) printf("Check CPP link OK(TC=0x10)\n");
								break;
					case 0x11 : if(p->verbose) printf("Message loaded OK(TC=0x11)\n");
								break;
					case 0x12 : if(p->verbose) printf("Data recieved OK(TC=0x12)\n");
								break;
					case 0x13 : if(p->verbose) printf("No data from AK(TC=0x13)\n");
								break;
					case 0x14 : if(p->verbose) printf("CPP parameters (TC=0x14)\n");
								if (f12->data.nf==12)
								{
									//if(p->verbose>1) printf("SS0_prd=%d SS0_prm=%d SS0_cpp=%d SS0_all=%d \n",f12->data.SS0_prd,f12->data.SS0_prm,f12->data.SS0_cpp,f12->data.SS0_all);
									
									for(j=0;j<9;j++) p->toMN3.sost_kasrt[j]=f12->i.data_int[j];
									return 0x14;
								}
								//printf("nf=%d\n",f12->data.nf);
								
								break;
					default :   if(p->verbose) printf("Error TS (TC=%d)\n",f12->zag.TS);
								break;
			
				}
				
				
				printf("\n");
				//printf("nf=%d\n",f12->data.nf);
				return f12->zag.TS;
			}
			else 
			{
				return 0; //owibka soedineni9
			}//owibka priema
			T_ALRM=0;
	} //send-recieve
	else 
	{
		return 0; //owibka soedineni9
	
	}
	//delay(100);
	
	return 0;
}