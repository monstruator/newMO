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
#include "../include/cpci1p.h"

#define BAR0 0x10
#define BAR1 0x14
#define BAR2 0x18

#define D_RS422 0x035D
#define V_RS422 0x1498
#define D_BRD 0x9030
#define V_BRD 0x10b5
		  
#include "../include/shared_mem.h"

#define N_CHAN 4 //R999

struct command999 
{
	
	unsigned char addr; //0xf8
	unsigned char chan01 : 4; // edinici kanala
	unsigned char chan10 : 4; // des9tki kanala
	unsigned char speed  : 2; // skorost'
	unsigned char reserv : 2; // reserv
	unsigned char power  : 2; // power
	unsigned char reserv1: 2; // reserv1
	unsigned char com    : 7; // command
	unsigned char odd    : 1; // 4etn

};

union
{
		unsigned int command;
		struct command999 cm; 
		
} com999;

timer_t  tm10;
struct sigevent event_sig;
struct itimerspec timer_sig;

unsigned short D_Bridge=D_BRD;
long V_Bridge=V_BRD,Base_adr0,Base_adr2,value1=0xFFFFFFFF;
int ind=0;
struct conf_pci my_device;
char *ptr1=0,*addr1;
unsigned long ba;
unsigned short ba1;
char *ptr2,*addr2;
int i,ii,j,k,irq_A;
//struct com999 r999;
char str_st_arinc[20]={"arinc_pci"};
char str_zap[100];
int fd2,fd1;
nid_t St_node=0;
pid_t proxy,pidm;
unsigned int ri;
int id;
//---------- ?ö ÿöR¢òÿ ô ? «÷ÿ-ð¯ --------------------------------
#pragma aux pcli="cli";
#pragma aux psti="sti";
#pragma off (check_stack);
int far mpcint2 ()   // ¤£-ò¦ð¯ Rö ÿöR¢òð ? ? . INT2 R¢ INT ??
		{ 
	pcli(); 
    ri=inp(SA+6);// citaem
	outp(SA+6,0); // -?Rö¥Rýð¿R §¢Rö« ¡-¯¢¬ ð¡¢R§-ðò ? ? «÷.
	psti(); 
    return(proxy);
		};
#pragma on( check_stack );

//===============================================================================
//			MAIN	MAIN	MAIN	MAIN 	MAIN
main(int argc, char *argv[])
{
	
	int n,i,j,col,i1,read_w=0;
	unsigned int command=0;
	unsigned char rele=0;// sosto9nie rele
    short c_step=0,T0=0;	
    long rele_timer=0;
	unsigned short save;
	int ind=0,Con1=1;
	char rezim=0;
	
	char txt[100],buf[10];
char *run[]={"/dev/io1","/dev/io2","/dev/io3",NULL};
int fd[3];
unsigned int word=0;
int chk_num,Time_out=2000,Con=0;
unsigned short etalon_r_pr[]={0x1,0x2,0x20,0x40,0x80,0x100};
unsigned short etalon_wr_pr[]={0x4,0};
IntFlag=0;
arginit(argc,argv,"¢?¡¢ ¿Rý£<¯ CPCI429-3\n");
argp("IO=", "%d", &ind, "?-ý?ò¡ ¿Rý£<¯ -ÿ ¨ð-? CPCI");
argp("V_Br=","%x",&V_Bridge,"ID ô Rð÷Rýð¢?<¯");
argp("D_Br=", "%x", &D_Bridge, "ID £¡¢ Rc¡¢÷ÿ");
argp("delay=", "%d", &Time_out, "'ÿc¿ÿ£¢ ÿô£¡òÿ ¢?¡¢ÿ");
argp("Node=", "%d", &St_node, "?R¿?  £<ÿ ÿô£¡òÿ ÷¡ôR¿R?ÿ¢?<¬-R?R ô R¦?¡¡ÿ");
if (p->verbose) printf("START MO3A<->R999\n\n");
	//===============================================================================
	//			 timer 10ms
	event_sig.sigev_signo = SIGALRM;
	tm10 = timer_create(CLOCK_REALTIME,&event_sig ); // ñîçäàíèå òàéìåðà 
	if (tm10==-1) printf("\ntimer opening error: %s",strerror(errno));
	timer_sig.it_value.tv_sec        = 0L;
	timer_sig.it_value.tv_nsec       = 0L;
	timer_sig.it_interval.tv_sec     = 0L;
	timer_sig.it_interval.tv_nsec    = 0L;
	
	
	if(ba_arinc()<0) 	defecte();
 	SA=ba1; PLX=ba1-0x80; INT=0; //INT=irq_A; //?ÿöR¢ÿ?¿ ö? ô ? «÷ÿ-ðc
	printf("SA=%x,PLX=%x,INT=%x \n",SA,PLX,INT);		
	err_pc=0;
	//?ô ?ý?<?-ð? ðý?-¢ð¤ðòÿ¢R ÿ ¿Rý£<¯ ôR -ÿcý?--R¿£ öÿR÷R¿£ ÿý ?¡£			
	pc_rj();
	if (err_pc==2){
		printf("Error err_pc=%d rj_pc=%x\n",err_pc,rj_pc);
		defecte();	    
	}
	else printf("rj_pc=%x\n",rj_pc);
	
	if(t_osu()){
				printf("Error write/read MEM ARINC%s\n"); defecte();
				}
				//?³ðýÿ-ð? R¡÷RöR³ý?-ð¯  ??ð¡¢ ÿ ô ? «÷ÿ-ðc
				if(frei_rrv()){ printf("Error read INT ARINC\n"); defecte();
				}

				if(usd()){ printf("Error run regim \n");  defecte();
				}
	    		
		printf("Number VER PO %x\n",pc_rm(3002));
	//for(j=0,i=0;j<512;j++,i=i+2)	si_tb (1,j,0xc000+i); //?ÿ¡ô. ??1 ý<¯ ??=0¥0 ÷ ?=¡000h
		pc_fsi (0xa,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0); //a 
		pc_fso (0xa,0,0,0,0,0,0,0); //a
		//pc_si_gp (1);	//??1 na priem //!
		pc_si_ap (1,0,3,1);	//??1 na priem		
	//--------------------------------------------nastroika rele----------------------------
	//create_shmem();
	delay(500);
	open_shmem();
	delay(500);
	com999.cm.addr=0xf8;
	com999.cm.reserv=0; // reserv
	com999.cm.reserv1=0; // reserv1
	com999.cm.com=0;
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
						if((p->verbose>1)&&(p->work_com[c_step].s[i].status==0)) printf("\nSTEP=%d    minicom for R999 : %d      status=%d time %d \n", p->cur_step,  p->work_com[c_step].s[i].n_com, p->work_com[c_step].s[i].status, p->sys_timer);

						switch(p->work_com[c_step].s[i].n_com)
						{
							case 1: p->work_com[c_step].s[i].status=1;
									read_w=pc_rml(0x41f0);
									if(p->verbose) printf("		R999 READ=%x %x\n",0x41f0,read_w);
									p->work_com[c_step].s[i].status=2;
									break;
							case 2: p->work_com[c_step].s[i].status=1;
									com999.cm.power=p->inbufMN3.a_params[0];
									send_com();
									p->work_com[c_step].s[i].status=2;
									break;
							case 4:	p->work_com[c_step].s[i].status=1; 
									if(p->verbose) printf("		R999 BASE SETUP \n");
									com999.cm.com=0; 
									com999.cm.chan01=1;
									com999.cm.chan10=com999.cm.power=com999.cm.speed=0;
									send_com();
									p->work_com[c_step].s[i].status=2;
									break;
							case 10: if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										if(p->verbose) printf("		R999 ZU \n");
										com999.cm.com=0; 
										com999.cm.chan01=p->inbufMN3.a_params[0]%10;
										com999.cm.chan10=p->inbufMN3.a_params[0]/10;
										com999.cm.power=p->inbufMN3.a_params[2];
										com999.cm.speed=p->inbufMN3.a_params[1];
										send_com();
										p->work_com[c_step].t_start = p->sys_timer;
										p->work_com[c_step].s[i].status=2;
									}
									
									break;
							case 11: if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										if(p->verbose) printf("		R999 PPR4 \n");
										com999.cm.com=0x22; //0x22
										com999.cm.chan01=p->inbufMN3.a_params[0]%10;
										com999.cm.chan10=p->inbufMN3.a_params[0]/10;
										com999.cm.power=p->inbufMN3.a_params[2];
										com999.cm.speed=p->inbufMN3.a_params[1];
										send_com();
										p->work_com[c_step].t_start = p->sys_timer;
										p->work_com[c_step].s[i].status=2;
									}
									
									break;
							case 80:if (p->work_com[c_step].s[i].status==0) 
									{
										p->work_com[c_step].s[i].status=1; 
										if(p->verbose) printf("		R999 REQUEST \n");
										pc_so_uf (1,0,1,0); //1 raz 1 slovo
										pc_wml(0x8000,0x3a0201f8);		
										pc_wm (0x2004,0x00); //KCP 
										pc_wm (0x2001,0x0888); //ô£¡ò ???-?ÿöR¢« (<®öR? c<R÷R,
										p->work_com[c_step].t_start = p->sys_timer;
									}
									if ((p->work_com[c_step].s[i].status==1)&&(p->sys_timer - p->work_com[c_step].t_start > 100))
									{
										read_w=pc_rml(0x41f0);
										if(p->verbose>1) printf("		R999 READ=%x %x\n",0x41f0,read_w);
										p->toMN3.sost_r999=read_w;
										p->work_com[c_step].s[i].status=2;
									}  
									//if(p->verbose) printf("		%d %d\n",p->work_com[c_step].s[i].status,p->sys_timer - p->work_com[c_step].t_start);
									break;
							default: 
									printf("Bad minicom %d for %d chan : %d",p->work_com[c_step].s[i].n_com,N_CHAN);					
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


int ba_arinc(){
int er=0;
//?ô ?ý?<?-ð? ?ÿR÷R?R ÿý ?¡ÿ ÷-£¢ ?--ð¥  ??ð¡¢ R÷ ¿R¡¢ÿ
if (new_func_read(D_Bridge,V_Bridge,&my_device,0x3c,ind)!=-1)
{
irq_A=mass[0x3c];
irq_A&=0xF;
}
i=new_func_read(D_Bridge,V_Bridge,&my_device,BAR0,ind);
if (i==-1) {error("?R¡¢ R¢¡£¢¡¢÷£?¢");er=-1;}
else {
if (PCI_IS_MEM(mass[BAR0])) {
//?¢Rö ÿ³?-ð? ôR ¢R÷ ¿Rý£<¯ ÷ PCI Memory Space
//printf ("Memory %08x\n",ba=PCI_MEM_ADDR(mass[BAR0]));

//----?Rô«¢òÿ  ÿöR¢ÿ¢¬ ¡ ôÿ¿¯¢¬®
fd1=shm_open("Physical",O_RDWR,0777);
ptr1=(char *)mmap(0,4*256,PROT_READ|PROT_WRITE|PROT_NOCACHE,MAP_SHARED,fd1,
PCI_MEM_ADDR(mass[BAR0])&~4095);
printf ("ptr1 = %x %8x\n",ptr1,ba); 
if (ptr1==(char *)-1) {printf ("FAULT\n"); exit (-1);}
addr1=ptr1 + (ba&4095);
printf ("Memory configuration addr = %x\n",addr1);
*(unsigned int*)(addr1)=0xFFFFFFFF;
printf("READ %x\n",*(unsigned int*)(addr1));
munmap(ptr1,4096);
close(fd1);
							}
//?ô ?ý?<?-ð? ?ÿR÷R?R ÿý ?¡ÿ ôR ¢R÷ ÷÷Rýÿ - ÷«÷Rýÿ
//?¢Rö ÿ³?-ð? ôR ¢R÷ ¿Rý£<¯ ÷ PCI I/O Space
i=new_func_read(D_Bridge,V_Bridge,&my_device,BAR1,ind);
   if (i==-1) {error("?R¡¢ R¢¡£¢¡¢÷£?¢");er=-1;}
		else{
if (PCI_IS_IO(mass[BAR1])){  
//printf ("Base_addr_IO %08x\n",ba=PCI_IO_ADDR(mass[BAR1]));
//?ô ?ý?<?-ð? ?ÿR÷R?R ÿý ?¡ÿ ôR ¢R÷ ÷÷Rýÿ - ÷«÷Rýÿ
new_func_read(D_Bridge,V_Bridge,&my_device,BAR2,ind);
if (PCI_IS_IO(mass[BAR2])) { 
ba1=PCI_IO_ADDR(mass[BAR2]);
printf ("IO Space adr for access to IO ports  %x irq= %d\n",ba1,irq_A);

	} //:¡<ð PCI £¡¢ Rc¡¢÷R Rö-ÿ £³?-R
            }
			}
	} 
return(er);
}




void defecte(){
	                err++; 
					rez=2; 
					error("?Rý£<¬ -?ð¡ô ÿ÷?-"); podswID();
					oclose();
sprintf(str_zap,"//%d slay %s &",St_node,str_st_arinc);
system(str_zap);
				
exit (rez);

}

int frei_rrv(){
int i,k;
	for (k=0,i=0;(((i&0x800)==0)&&(k<20000));k++) i=pc_rrv(); 
    if ((i&0xfff)!=0x805)	return(err_pc=14);
	else 
	return(0);
}	

int usd(){
	pc_wm (0x3000,0xffff);
    if ((pc_rm(0x3000)!=0x0bcc)||(pc_rm(0x3001)!=0xdc9d)) return(err_pc=16);
	else
	return(0);
}
t_osu(){
	err_pc=0;
	pc_wrv ();
	pc_wml (2,0x87654321); //long WE adr=2,3
	pc_wd (0x2345); pc_wd (0x3456); pc_wd (0x4567);	//WE adr=4,5,6
    if ((pc_rm(2)!=0x4321)||(pc_rd()!=0x8765)) err_pc=10;//adr=2,3?
//printf("READ OSU:err_pc=%d\n",err_pc);
    if ((pc_rml(4)!=0x34562345)||(pc_rd()!=0x4567))	err_pc=11;//adr=4,5,6?
//printf("READ OSU&RD:err_pc=%d\n",err_pc);
	pc_wra(0xaaaa);                                 //WE RA
    if (pc_rra()!=0xaaaa)				err_pc=12; //RA=?
//printf("READ OSU:err_pc=%d\n",err_pc);
	return(err_pc);
}

slay_arinc(){
sprintf(str_zap,"//%d slay %s &",St_node,str_st_arinc);
system(str_zap);
}


void send_com()
{
	int col=0,i1;
	for(i1=0;i1<31;i1++) if ((com999.command>>i1)&1==1) col++; 
	if (col%2==0) com999.cm.odd=1; else com999.cm.odd=0;
	//if(p->verbose) printf(" SEND		%x col=%d odd=%d\n",com999.command,col,com999.cm.odd);
	if(p->verbose) printf(" SEND		%x \n",com999.command);
	pc_so_uf (1,0,1,0); //1 raz 1 slovo
	pc_wml(0x8000,com999.command);		
	pc_wm (0x2004,0x00); //KCP 
	pc_wm (0x2001,0x0888); //ô£¡ò ???-?ÿöR¢« (<®öR? c<R÷R,

}