//obmen s mn3 i vibor comandi
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  #include "../include/func_IP.h"
  #include "../include/shared_mem.h"
  
  #define SRC_PORT 4003
  #define DST_PORT 4000


  #define MS 1000000
  char          pack_buf[1500];  

  
main()
{//--- KOHCTAHTbl npu6opa 1.0 ---//
		int sock, length, i , count_mes=0, i1 , i_p=0 , i2=0 , j;
		static Udp_Client_t Uc42;
		short c_step=0,TC10=0;	
		char bufi[1024];
		char bufo[1024];
		char out_buf[1024];
#ifdef CVM10
		char name[30] ="SPIAK_N8_Eth2";// "192.168.3.1";
	
#else
		char name[30] ="SPIAK_N9_Eth4";// "192.168.3.1";

#endif

		int r,bytes,COM=0;
		short n_s=0; //nomer waga zapolneni9 komabdi
		short n_mc=0; //nomer mini comandi na tekuwem wage
		packusoi p1;
		packcmd p2;
    	timer_t id;
 		struct itimerspec timer;
    	struct sigevent event;
		pid_t pid, proxym;
		long timer_mn3=0;
	  	


	i = Udp_Client_Ini(&Uc42,name,DST_PORT,SRC_PORT);
	printf(" Udp_Init=%d	\n", i);

//	create_shmem();
	delay(1500);
	open_shmem();
	delay(300);
	p->verbose=3;
	
  	printf("Start MN3 %d\n\n",sizeof(packusoi));	

	while(1)
	{
	   	if (timer_mn3!=p->sys_timer) //timer
		{
			timer_mn3=p->sys_timer;
			//TCount++;
			TC10++;
			//printf("%d\n", TC10);
			if (TC10==2) 
			{
				TC10=0;
				bytes = Udp_Client_Read(&Uc42,bufi,4096);
				if (bytes>0)
				{
					//printf(" Udp_READ=%d	\n", bytes);
					//printf("\n<===== ");for(i=0;i<28;i++) printf(" %d ", bufi[i]);

					memcpy(&p->inbufMN3,&bufi,sizeof(packcmd));

					memcpy(pack_buf,&p->toMN3,sizeof(packusoi)); ///!!!!!!
					//printf("cr_com->MO3 = %d \n",	p->toMN3.cr_com);
					//for(j=0;j<9;j++) printf("%08x ",p->toMN3.sost_kasrt[j]);  printf("\n");
					//if(p->verbose>1) printf("SS0=%x SS1=%x SS2=%x SS3=%x \n",p->toMN3.sost_kasrt[0],p->toMN3.sost_kasrt[1],p->toMN3.sost_kasrt[2],p->toMN3.sost_kasrt[3]);
	     			i = Udp_Client_Send(&Uc42,pack_buf,sizeof(packusoi));
	
					//printf("Send i = %d\n ",i);
					//printf("\n=====> ");for(i1=0;i1<i;i1++) printf(" %d ", pack_buf[i1]);printf("\n");
				}
			}
            
			if (p->fromMN3.cr_com!=p->inbufMN3.cr_com) // new command from MN3
//			if ((p->fromMN3.cr_com==0)||(p->fromMN3.cr_com!=p->inbufMN3.cr_com)) // new command from MN3
			{
                p->toMN3.num_com = p->inbufMN3.num_com;
                p->toMN3.lp2_param = p->inbufMN3.a_params[0];
                p->toMN3.kzv = 0;
                p->toMN3.k_o = 0;
               // p->toMN3.ended_loop = 0;
               // p->toMN3.krk = 0;
                p->toMN3.link = 0;
					

				printf("\nNew command : %d , param: %d %d %d    time=%d\n",p->inbufMN3.num_com,p->inbufMN3.a_params[0],p->inbufMN3.a_params[1],p->inbufMN3.a_params[2],p->sys_timer);
				switch (p->inbufMN3.num_com)
				{
				case 1 : case 60 : case 70 :    
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=1;
						p->work_com[n_s].s[n_mc].status=0;		
                        n_mc++; //kol-vo mini komand + 1
					//---------------------------------------------
					
					//---------------------------------------------
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
						p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
                        p->work_com[n_s].t_start=p->sys_timer;                        
                        p->work_com[n_s].t_stop =p->sys_timer+100;                        
 						break;
				case 4 : case 25 :
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=3;
						p->work_com[n_s].s[n_mc].n_com=p->inbufMN3.num_com;
						p->work_com[n_s].s[n_mc].status=0;		
						n_mc++; //kol-vo mini komand + 1
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
						p->work_com[n_s].t_start=p->sys_timer;                        
						p->work_com[n_s].t_stop =p->sys_timer+100; 
						//---------------------------------------------
						n_s=2;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=3;
						p->work_com[n_s].s[n_mc].n_com=30;  //waiting
						p->work_com[n_s].s[n_mc].status=0;						
						n_mc++; //kol-vo mini komand + 1						
						p->work_com[n_s].t_start=p->sys_timer;                        
						p->work_com[n_s].t_stop =p->sys_timer+70;        //2 sec                
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
						//-----------------------------------------------------------
						n_s=3;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=3;
						p->work_com[n_s].s[n_mc].n_com=29;  //waiting
						p->work_com[n_s].s[n_mc].status=0;						
						n_mc++; //kol-vo mini komand + 1						
						p->work_com[n_s].t_start=p->sys_timer;                        
						p->work_com[n_s].t_stop =p->sys_timer+160;        //2 sec                
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
						//----------------------------------------------------------
						p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
						break;
					
					case 5 : 
						if ((p->inbufMN3.a_params[0]>0)&&(p->inbufMN3.a_params[0]<7))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=5;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 8 : case 12 :case 14 :case 15 : 
						if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<2))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=p->inbufMN3.num_com;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 10 : case 11 :
							if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<40)&&
							    (p->inbufMN3.a_params[1]>=0)&&(p->inbufMN3.a_params[1]<4)&&
								(p->inbufMN3.a_params[2]>=0)&&(p->inbufMN3.a_params[2]<4))
							{	
								n_s=1;  //nomer waga
								n_mc=0; //s4et4ik mini komamdi
								p->work_com[n_s].s[n_mc].n_chan=4;
								p->work_com[n_s].s[n_mc].n_com=p->inbufMN3.num_com;
								p->work_com[n_s].s[n_mc].status=0;		
								n_mc++; //kol-vo mini komand + 1
								//---------------------------------------------
								p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
								p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
								p->work_com[n_s].t_start=p->sys_timer;                        
								p->work_com[n_s].t_stop =p->sys_timer+100; 
							}
							else 
							{
								printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
								p->toMN3.kzv=1;
								p->toMN3.cr_com++;
							}
							break;							
					
					case 30 : case 32 : case 33: case 42 : case 43:
						if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<26))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=2;
							p->work_com[n_s].s[n_mc].n_com=p->inbufMN3.num_com;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 61 : case 71 :    
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=61;
						p->work_com[n_s].s[n_mc].status=0;		
                        n_mc++; //kol-vo mini komand + 1
					//---------------------------------------------
					
					//---------------------------------------------
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
						p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
                        p->work_com[n_s].t_start=p->sys_timer;                        
                        p->work_com[n_s].t_stop =p->sys_timer+100;                        
 						break;
				case 65 :    
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=2;
						p->work_com[n_s].s[n_mc].n_com=65;
						p->work_com[n_s].s[n_mc].status=0;		
                        n_mc++; //kol-vo mini komand + 1
					//---------------------------------------------
					
					//---------------------------------------------
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
						p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
                        p->work_com[n_s].t_start=p->sys_timer;                        
                        p->work_com[n_s].t_stop =p->sys_timer+100;                        
 						break;
					case 78 :    
						n_s=1;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=1;
						p->work_com[n_s].s[n_mc].n_com=2;
						p->work_com[n_s].s[n_mc].status=0;						
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_start=p->sys_timer;                        
                        p->work_com[n_s].t_stop =p->sys_timer+100;                        
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  

					//---------------------------------------------
						n_s=2;  //nomer waga
						n_mc=0; //s4et4ik mini komamdi
						p->work_com[n_s].s[n_mc].n_chan=1;
						p->work_com[n_s].s[n_mc].n_com=2;
						p->work_com[n_s].s[n_mc].status=0;						
						n_mc++; //kol-vo mini komand + 1						
                        p->work_com[n_s].t_start=p->sys_timer;                        
                        p->work_com[n_s].t_stop =p->sys_timer+200;                        
						p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
					
					//---------------------------------------------
						p->kol_step=n_s; //obwee kol-vo wagov na dannom wage 

						//printf("номер канала на нулевом шаге = %d\n",p->work_com[0].s[0].n_chan);
 						break;
					case 100 : //rele_off
						if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<9))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=2;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 101 : //rele_onn
						if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<9))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=3;
							p->work_com[n_s].s[n_mc].n_com=1;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 102 : //n_chan r999
						if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<40))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=4;
							p->work_com[n_s].s[n_mc].n_com=1;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					case 103 : //power r999
						if ((p->inbufMN3.a_params[0]>=0)&&(p->inbufMN3.a_params[0]<4))
						{
							n_s=1;  //nomer waga
							n_mc=0; //s4et4ik mini komamdi
							p->work_com[n_s].s[n_mc].n_chan=4;
							p->work_com[n_s].s[n_mc].n_com=2;
							p->work_com[n_s].s[n_mc].status=0;		
							n_mc++; //kol-vo mini komand + 1
							//---------------------------------------------
							p->work_com[n_s].num_mini_com=n_mc; //zapomnim kol-vo mini komand na wage n_s  
							p->kol_step=n_s; //obwee kol-vo wagov na dannom wage
							p->work_com[n_s].t_start=p->sys_timer;                        
							p->work_com[n_s].t_stop =p->sys_timer+100;   
						}
						else 
						{
							printf("Bad param0 : %d\n",p->inbufMN3.a_params[0]);
							p->toMN3.kzv=1;
							p->toMN3.cr_com++;
						}
 						break;
					default:    
                        printf("Bad command : %d\n",p->inbufMN3.num_com);
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;
				} //switch komandi
				
				if (p->toMN3.kzv!=1) p->cur_step=1;
				p->fromMN3=p->inbufMN3; //utvergdaem komandu

	
			} //nova9 komanda
			
			//Proverka wagov vipolneni9 komandi--------------------------
			if (p->cur_step!=0)
			{
				//printf("done_com=%d", p->work_com[c_step].done_mini_com);
				c_step=p->cur_step;
				p->work_com[c_step].done_mini_com=0; //zanovo s4itaem kol-vo vopolnennih
				for (i=0;i<p->work_com[c_step].num_mini_com;i++) //prosmotrim vse statusi
				{
					if(p->work_com[c_step].s[i].status==2) //esli wag vipolnen
						p->work_com[c_step].done_mini_com++; //zanovo s4itaem kol-vo vopolnennih
					if(p->work_com[c_step].s[i].status==3) //esli owibka
					{
						printf("Command %d error , time=%d . ",p->fromMN3.num_com,p->sys_timer);
						printf("Step=%d Interf=%d . \n",c_step,p->work_com[c_step].s[i].n_chan);
						// NADO GOTOVIT' AVARIINOE ZAVERW KOMANDI---------------
						//------------------------------------------------------
						//------------------------------------------------------	
						//------------------------------------------------------
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;
						ResetCom();
												
					}
				}
				//if(p->verbose>2) printf("wipolneno na %d wage %d comand, time %d\n",c_step, p->work_com[c_step].done_mini_com, timer_mn3);
				if (p->toMN3.kzv!=1)
				{
					if(p->work_com[c_step].t_stop<p->sys_timer) //esli timer istek
					{
						printf("Command %d timeout , time=%d . ",p->fromMN3.num_com,p->sys_timer);
						printf("Step=%d Interf=%d . \n",c_step,p->work_com[c_step].s[i].n_chan);
						// NADO GOTOVIT' AVARIINOE ZAVERW KOMANDI---------------
						//------------------------------------------------------
						//------------------------------------------------------	
						//------------------------------------------------------
						p->toMN3.kzv=1;
						p->toMN3.cr_com++;
						ResetCom();		
					}
					else 
					if (p->work_com[c_step].done_mini_com==p->work_com[c_step].num_mini_com) //vipolneni vse
					{	 printf("step=%d time=%d\n",p->cur_step,p->sys_timer);p->cur_step++;}
				}
			}
			if ((p->cur_step > p->kol_step) && (p->kol_step!=0)) //vse wagi proideni, komanda vopolnena
			{
				printf("Command %d complete , time=%d\n",p->fromMN3.num_com,p->sys_timer);
				// NADO GOTOVIT' DANNIE DL9 MN3 ------------------------
				//------------------------------------------------------
				//------------------------------------------------------	
				//------------------------------------------------------
				p->toMN3.kzv=0;
				p->toMN3.cr_com++;
			
				ResetCom();		

			}

		}//proxy timer
	}//while   
}


