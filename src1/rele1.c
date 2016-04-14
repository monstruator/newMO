  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  
#include <stdlib.h>
#include <sys/pci.h>
#include <i86.h>
#include <conio.h>
#include <stdio.h>
#include <sys/seginfo.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/my_pci_ts_new.h"
#include "../include/ts.h"
#define BAR0 0x10
#define BAR1 0x14
#define BAR2 0x18

#define D_cp384 0x5555
#define V_cp384 0x1556

//#define SET_BIT  (value, bit_n) ((value) |=  (1 << (bit_n)))
//#define UNSET_BIT(value, bit_n) ((value) &= ~(1 << (bit_n)))
 
#define TIMEOUT_SEC		   0L	//0 секунд
#define TIMEOUT_NSEC	10000000L	//макс. время ожидания 10 мс
#define LENBUFWR	80	//длина буфера передачи
#define LnTitle		32		//длина заголовка
#define LENBUFRD 	1400	//длина буфера приема
#define LnKdr	   512	//макс число слов(2 байта) в кадре
#define MaxKdr	  10000	//макс число хранимых кадров
		  
#include "../include/shared_mem.h"
#include "../include/USOIwrk.h"

#define MS 1000000
#define N_CHAN 3 //RELE


timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;

unsigned short D_Bridge=D_cp384;
long V_Bridge=V_cp384,Base_adr0,Base_adr2,value1=0xFFFFFFFF;
struct conf_pci my_device;
char *ptr1=0,*addr1;
unsigned long ba;
unsigned short ba1;
char *ptr2,*addr2;
int i,ii,ii1;
int fd1;

//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main(int argc, char *argv[])
{
	
	int n,i,j,col,command,i1;
	unsigned char rele=0;// sosto9nie rele
    short c_step=0,T0=0;	
    long rele_timer=0;
	unsigned short save;
	int ind=0,chk_num,Time_out=5,Con1=1;
	if (p->verbose) printf("START MO3A<->RELE\n\n");
	//===============================================================================
	//			 timer 10ms
	event_sig.sigev_signo = SIGALRM;
	tm10 = timer_create(CLOCK_REALTIME,&event_sig ); // ёючфрэшх ЄрщьхЁр 
	if (tm10==-1) printf("\ntimer opening error: %s",strerror(errno));
	timer_sig.it_value.tv_sec        = 0L;
	timer_sig.it_value.tv_nsec       = 0L;
	timer_sig.it_interval.tv_sec     = 0L;
	timer_sig.it_interval.tv_nsec    = 0L;
	
	//--------------------------------------------nastroika rele----------------------------
	arginit(argc,argv,"тест модуля cp384\n");
	argp("IO=", "%d", &ind, "Индекс модуля на шине CPCI");
	argp("V_Br=","%x",&V_Bridge,"ID производителя");
	argp("D_Br=", "%x", &D_Bridge, "ID устройства");
	argp("delay=", "%d", &Time_out, "Таймаут запуска теста");
	argp("Con1=", "%x", &Con1, "Режим надетой заглушки - 0 - нет");

	delay(Time_out);
	//Определение Базового адреса внутренних регистров моста
	i=new_func_read(D_Bridge,V_Bridge,&my_device,BAR0,ind);
	if (i==-1) {printf("Мост отсутствует");exit(1);}
	else if (!PCI_IS_MEM(mass[BAR0])) {printf("PCI устройство не обнаружено");exit(1);}
	//Отображение портов модуля в PCI Memory Space
	printf ("Memory %08x\n",ba=PCI_MEM_ADDR(mass[BAR0]));

	//----Попытка работать с памятью
	fd1=shm_open("Physical",O_RDWR,0777);
	ptr1=(char *)mmap(0,64*1024,PROT_READ|PROT_WRITE|PROT_NOCACHE,MAP_SHARED,fd1,
	PCI_MEM_ADDR(mass[BAR0])&~4095);
	printf ("ptr1 = %x %8x\n",ptr1,ba); 
	if (ptr1==(char *)-1) {printf ("FAULT\n"); exit (-1);}
	addr1=ptr1 + (ba&4095);
	printf ("Memory configuration addr = %x\n",addr1);
	*(unsigned int*)(addr1)=0xFFFFFFFF;

	i=1; printf("WRITE O_CTL %x %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i)=0);
	i++; printf("READ O_STA_A %x, %x\n",0x2000 + 0x400*i,*(unsigned int*)(addr1 +0x2000 + 0x400*i));
	i++; printf("WRITE I_CTL %x\n",*(unsigned int*)(addr1 +0x4400)=0x80);
	//--------------------------------------------nastroika rele----------------------------
	//create_shmem();
	delay(500);
	open_shmem();
	delay(500);
	
//---------------------------------------------------------------------	
	while(1)
	{
		if (rele_timer!=p->sys_timer) //timer
		{
			rele_timer=p->sys_timer;
			if (p->cur_step!=0) //est' wag dl9 vipolnenni9
			{
				c_step=p->cur_step;
				for (i=0;i<p->work_com[c_step].num_mini_com;i++) //prosmotrim vse minicomandi na wage 
					if((p->work_com[c_step].s[i].n_chan==N_CHAN)&&(p->work_com[c_step].s[i].status!=2)) //na tekuwem wage (i - minikomanda) est' komanda dl9 nas
					{
						if((p->verbose>1)&&(p->work_com[c_step].s[i].status==0)) printf("\nSTEP=%d    minicom for RELE : %d      status=%d time %d \n", p->cur_step,  p->work_com[c_step].s[i].n_com, p->work_com[c_step].s[i].status, p->sys_timer);

						switch(p->work_com[c_step].s[i].n_com)
						{
							/*case 1: p->work_com[c_step].s[i].status=1;
									rele|=(1<<p->inbufMN3.a_params[0]);
									*(unsigned int*)(addr1 +0x2C00)=rele;
                                    if(p->verbose>1) printf("WRITE OUT DATA 0x2C00 %x\n",rele);
									if(p->verbose>1) printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									p->work_com[c_step].s[i].status=2;
									break;
							case 2: p->work_com[c_step].s[i].status=1;
									rele &= ~(1 << p->inbufMN3.a_params[0]);
									*(unsigned int*)(addr1 +0x2C00)=rele;
                                    if(p->verbose>1) printf("WRITE OUT DATA 0x2C00 %x\n",rele);
									if(p->verbose>1) printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									p->work_com[c_step].s[i].status=2;
									break;
									*/
							case 10: //off 1 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele &= ~1; 	*(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										if ((*(unsigned int*)(addr1 + 0x4C00)&0x08)==0) p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x %x\n",*(unsigned int*)(addr1 + 0x4C00),*(unsigned int*)(addr1 + 0x4C00)&0x01);
									}
									break;
							case 11: //on 1 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele|=1; *(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										if (*(unsigned int*)(addr1 + 0x4C00)&0x08) p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x \n",*(unsigned int*)(addr1 + 0x4C00));
									}
									break;
							case 20: //off 2 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele &= ~2; 	*(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										if ((*(unsigned int*)(addr1 + 0x4C00)&0x02)==0) p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x %x\n",*(unsigned int*)(addr1 + 0x4C00),*(unsigned int*)(addr1 + 0x4C00)&0x01);
									}
									break;
							case 21: //on 2 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele|=2; *(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										if (*(unsigned int*)(addr1 + 0x4C00)&0x02) p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x \n",*(unsigned int*)(addr1 + 0x4C00));
									}
									break;
							
							case 30: //off 3 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele &= ~4; 	*(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										if ((p->inbufMN3.a_params[0]==0)&&((*(unsigned int*)(addr1 + 0x4C00)&0x04)==0)) p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									}
									break;
							case 31: //on 3 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele|=4; *(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA  %x\n",rele);
										//p->work_com[c_step].t_start = p->sys_timer;
										//if(p->verbose>1) printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									}
									//if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start > 20))
									if (p->work_com[c_step].s[i].status==1)
									{
										if (*(unsigned int*)(addr1 + 0x4C00)&0x04) p->work_com[c_step].s[i].status=2;
										//if ((p->inbufMN3.a_params[0]==0)&&((*(unsigned int*)(addr1 + 0x4C00)&0x04)==0)) p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									}
									break;
							case 40: //off 4 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=2; 
										rele &= ~8; 	*(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									break;
							case 41: //on 4 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=2; 
										rele|=8; *(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA  %x\n",rele);
									}
									break;
							case 50: //off 5 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=2; 
										rele &= ~0x10; 	*(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA %x\n",rele);
									}
									break;
							case 51: //on 5 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=2; 
										rele|=0x10; *(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA  %x\n",rele);
									}
									break;
							case 60: //off 6 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele &= ~0x20; 	*(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA 0x2C00 %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										//if ((*(unsigned int*)(addr1 + 0x4C00)&0x20)==0) 
										p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x %x\n",*(unsigned int*)(addr1 + 0x4C00),*(unsigned int*)(addr1 + 0x4C00)&0x01);
									}
									break;
							case 61: //on 6 rele
									if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										rele|=0x20; *(unsigned int*)(addr1 +0x2C00)=rele;
										if(p->verbose>1) printf("WRITE OUT DATA 0x2C00 %x\n",rele);
									}
									if (p->work_com[c_step].s[i].status==1)
									{
										//if (*(unsigned int*)(addr1 + 0x4C00)&0x20) 
										p->work_com[c_step].s[i].status=2;
										if(p->verbose>1) printf("READ DATA %x \n",*(unsigned int*)(addr1 + 0x4C00));
									}
									break;		
							case 25: p->work_com[c_step].s[i].status=1;
									if (p->inbufMN3.a_params[0]) rele|=2;
									else rele &= ~2;
									*(unsigned int*)(addr1 +0x2C00)=rele;
                                    if(p->verbose>1) printf("WRITE OUT DATA  %x\n",rele);
									if(p->verbose>1) printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									p->work_com[c_step].s[i].status=2;
									break;
							case 29: p->work_com[c_step].s[i].status=1;
									//if(p->verbose>1) 
									printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									p->work_com[c_step].s[i].status=2;
									break;
							case 90: // pause
									//if(p->verbose>1) printf(" %d\n",p->work_com[c_step].t_stop-p->sys_timer);
									if (p->work_com[c_step].t_stop-p->sys_timer<20) p->work_com[c_step].s[i].status=2;
									break;
							case 104: //Ogidanie Ispravnosti R999
									//p->work_com[c_step].s[i].status=1;
									//if(p->verbose>1) 
									if (p->inbufMN3.a_params[0]&&(*(unsigned int*)(addr1 + 0x4C00)&0x04)) p->work_com[c_step].s[i].status=2;
									if ((p->inbufMN3.a_params[0]==0)&&((*(unsigned int*)(addr1 + 0x4C00)&0x04)==0)) p->work_com[c_step].s[i].status=2;
									
									//if ((*(unsigned int*)(addr1 + 0x4C00)&0x04)&&(p->inbufMN3.a_params[0])) p->work_com[c_step].s[i].status=2;
									printf("READ DATA %x\n",*(unsigned int*)(addr1 + 0x4C00));
									//p->work_com[c_step].s[i].status=2;
									break;		
							default: 
									printf("Bad minicom %d for %d chan : %d",p->work_com[c_step].s[i].n_com, N_CHAN);					
									p->work_com[c_step].s[i].status=3;
									
						}//switch (n_com)
						//-------------------------------------------------------
                        //esli previweno vrem9 ozhidani9
						//if ((p->work_com[c_step].s[i].status==1)&&(p->work_com[c_step].s[i].t_stop>p->sys_timer)) p->work_com[c_step].s[i].status=3;
                        
						//-------------------------------------------------------						
					}//ewe ne vipoln9li
		
					//if (p->work_com[c_step].s[i].w_answ[0]==2) //esli nado gdat' otveta
					//if (p->work_com[c_step].s[i].w_answ[1]=1)
						
			} //step>0
		}//timer
	}//while
	timer_delete(tm10);
}