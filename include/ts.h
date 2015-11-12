/*
 *  ������⥪� �㭪権 ९��⠦� �१ �S-�ࢥ�.
 *  Copyright (c) 2002 Fomin D.A. V3.01
 */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <sys/vc.h>
#include <sys/kernel.h>
#include <sys/dev.h>
#include <time.h>
#include <fcntl.h>
//#include "arg.h"
#define mku 40
#define m_u   if(Muz==0) Muz=getnid();
int Muz=0;
pid_t pid_czr[mku]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//--------------------------------------------
/*
 *  ������⥪� �㭪権 ��� ������� �室��� ��㬥�⮢ �ணࠬ��.
 *  Copyright (c) 2002 Fomin D.A. V1.00
 */
//#include <stdio.h>
//#include <conio.h>
//#include <string.h>

/* ������쭠� ������� ��㬥�⮢. */
struct SARG {
  char *name; /* ��������� �ࠢ��. */
  int argc; char *argv[128]; /* �室�� ��㬥���. */
  int hlpc; char hlpv[128][32]; char *hlpv1[128]; char *hlpv2[128];
  int null; /* ��६����� ��� ����. */
} arg;

/*
 *  arginit - ��砫쭠� ���樠������.
 *
 *  1-> ������⢮ �室��� ��㬥�⮢ �ணࠬ��.
 *  2-> �����⥫� �� ��ப� �室��� ��㬥�⮢ �ணࠬ��.
 *  3-> �����⥫� �� ⥪�⮢�� ��������� c�ࠢ��.
 */
void arginit(int argc, const char *argv[], const char *msg) {
  int i;
/* ���࠭���� 㪠��⥫� �� ��������� �ࠢ��. */
  arg.name = msg;
/* ���࠭��� ��㬥�⮢ �ணࠬ��. */
  arg.argc = argc;
  for(i=0; i<argc; i++) arg.argv[i] = argv[i];
}//arg

/*
 *  argp - ���樠������ ��६�����.
 *
 *  1-> �����⥫� �� �����䨪��� ��६�����
 *  2-> �����⥫� �� ⨯ (%�ଠ�) �८�ࠧ������ ���祭�� ��६�����
 *  3-> �����⥫� �� ���樠�����㥬�� ��६�����
 *  4-> �����⥫� �� ��ப� �ࠢ�� �� ��६�����
 */
int argp(const char *msgid, const char *msgf, void *var, const char *msgh) {
  int i, status=0;;
/* ���࠭���� 㪠��⥫�� �� ��ப� �ࠢ�� �� ��६�����. */
  arg.hlpv1[arg.hlpc] = msgid; arg.hlpv2[arg.hlpc] = msgh;
/* ���� �����䨪��� ��६����� � �� ���樠������. */
  for (i=1; i<arg.argc; i++) {
    if (strncmp(arg.argv[i], msgid, strlen(msgid)) == 0)
        status = sscanf(arg.argv[i]+strlen(msgid), msgf, var) + 2;
  }//for i
/* ���࠭���� ���祭�� ��६����� � ���� ��ப�. */
  if (strcmp(msgf, "%s") == 0)
    sprintf(arg.hlpv[arg.hlpc], msgf, (char *)var);
  else
  if (strcmp(msgf, "%f") == 0)
    sprintf(arg.hlpv[arg.hlpc], msgf, *(float *)var);
  else
  if (strcmp(msgf, "%lf") == 0)
    sprintf(arg.hlpv[arg.hlpc], msgf, *(double *)var);
  else
    sprintf(arg.hlpv[arg.hlpc], msgf, *(long *)var);
/* ���ਬ��� ���稪� �ࠢ��. */
  arg.hlpc++;
/* �����襭�� �㭪樨 � ����ᮬ ���樠����樨. */
  return(status);
}//arg -> 0h - ���樠������ �� �஢�����, �� ������ �����䨪��� ��६�����
 //       1h - ���樠������ �� �஢�����, ��᫥ �����䨪��� ��� ���祭��
 //       2h - ���樠������ �� �஢�����, ����४�� �ଠ� ���祭��
 //       3h - ���樠������ �ᯥ譮 �஢�����

/*
 *  arg2p - ���樠������ ���� ��६�����.
 *
 *  1-> �����䨪��� ��६�����
 *  2-> �����⥫� �� 1-� ���樠�����㥬�� ��६�����
 *  3-> ��� (�ଠ�) �८�ࠧ������ ���祭�� 1-� ��६�����
 *  5-> �����⥫� �� 2-� ���樠�����㥬�� ��६�����
 *  6-> ��� (�ଠ�) �८�ࠧ������ ���祭�� 2-� ��६�����
 *  7-> �����⥫� �� ��ப� �ࠢ�� �� ��६����
 */
int arg2p(const char *msgid, const char *msgf, void *var1, void *var2, 
      const char *msgh) {
  int i, status;
/* ���࠭���� 㪠��⥫�� �� ��ப� �ࠢ�� �� ��६�����. */
  arg.hlpv1[arg.hlpc] = msgid; arg.hlpv2[arg.hlpc] = msgh;
/* ���� �����䨪��� ��६����� � �� ���樠������. */
  for (i=1; i<arg.argc; i++) {
    if (strncmp(arg.argv[i], msgid, strlen(msgid)) == 0)
      status = sscanf(arg.argv[i]+strlen(msgid), msgf, var1, var2) + 2;
  }//for i
/* ���࠭���� ���祭�� ��६����� � ���� ��ப�. */
  if (strcmp(msgf+3, "%s") == 0)
    sprintf(arg.hlpv[arg.hlpc], msgf, *(long *)var1, (char *)var2);
  else
    sprintf(arg.hlpv[arg.hlpc], msgf, *(long *)var1, *(long *)var2);
/* ���ਬ��� ���稪� �ࠢ��. */
  arg.hlpc++;
/* �����襭�� �㭪樨 � ����ᮬ ���樠����樨. */
  return(status);
}//arg2p -> 0h - ���樠������ �� �஢�����, �� ������ �����䨪��� ��६�����
 //         1h - ���樠������ �� �஢�����, ��᫥ �����䨪��� ��� ���祭��
 //         2h - ���樠������ �� �஢�����, ����४�� �ଠ� ���祭��
 //         3h - ���樠������ �ᯥ譮 �஢�����

/*
 * arghlp - �뢮� �ࠢ�� �� ��ࠬ��ࠬ.
 */
void arghlp(void) {
  int i;
/* ��ନ஢���� � �뢮� ��ப �ࠢ��. */
  if (argp("H", "", &arg.null, "�맮� �ࠢ�� �� ��㬥�⠬ �ணࠬ��")) {
    fprintf(stdout, "%s - %s\n", arg.argv[0], arg.name);
    for (i=0; i<arg.hlpc; i++) fprintf(stdout, "  %s   %s (%s%s)\n",
      arg.hlpv1[i], arg.hlpv2[i], arg.hlpv1[i], arg.hlpv[i]);
    exit(-1);
  }//if
}//arghlp
//--------------------------------------------
#define __TS__
/* ������� ���஢����. */
#define OK  1
#define ERR 2
/* ����� ���஢����. */
#define MODEPUSK  0x1
#define MODEAUTO  0x4
#define MODEINTER 0x2
#define MODESYPER 0x8
/* ��� ���஢����. */
#define JAZRUS 0x0
#define JAZANG 0x1
#define JAZFR  0x2
/* ��� ९��⠦�. */
#define REPNO  0x1
#define REPERR 0x2
#define REPALL 0x3

/* �������� ��६���� ts. */
char *nam={"??.NONAME"},podID[100];
int mode=MODEPUSK, jaz=JAZRUS, rep=REPALL, nuz=0, npid=0, err=0, rez=0;

/*
 *  sighandler - ��ࠡ��稪 ᨣ���� SIGTERM
 */
void sighandler(int n) {
  oo(2, "�����襭�� �� ᨣ���� SIGTERM"); exit(-1);
}//sighandler

/*
 *  argts -���樠������ ��ࠬ��஢ ts. 
 */
void argts(void) {
/* ������ ��㬥�⮢ ts. */
  if (arg.argc > 1)
    if (sscanf(arg.argv[1], "%x", &arg.null) == 1) {
      mode = arg.null & 0xF; jaz = arg.null >> 5;
    }//if
  if (arg.argc > 2)
    if (sscanf(arg.argv[2], "%d", &arg.null) == 1) {
      rep = arg.null % 10; nuz = arg.null / 10;
      if (strlen(arg.argv[2]) > 4) nam = arg.argv[2] + 4;
    }//if
/* ������ �⠭������ ��㬥�⮢. */
  if (argp("P", "", &arg.null, "०�� ��᪮���� ���")) mode = MODEPUSK;
  if (argp("A", "", &arg.null, "०�� ��⮬���᪮�� ���")) mode = MODEAUTO;
  if (argp("I", "", &arg.null, "०�� ���ࠪ⨢���� ���")) mode = MODEINTER;
  if (argp("X", "", &arg.null, "०�� ᯥ樠�쭮�� ���")) mode = MODESYPER;
  argp("M", "%x", &mode, "०�� ���஢����, 1-���, 2-����, 4-���, 8-ᯥ�");
  argp("J", "%x", &jaz, "�� ���஢����, 0-���, 1-����, 3-�࠭");
  argp("R", "%x", &rep, "९��⠦ ���஢����, 1-���, 2-�訡, 3-��");
}//arginit

/*
 *  oopen - ��⨢����� ࠡ��� � ९��⠦���.
 */
void oopen(void) {
  int i; char msg[256];
/* ��ࠡ�⪠ ��ࠬ��஢ ts. */
  argts(); arghlp();
/* ������祭�� ��ࠡ��稪� ᨣ���� SIGTERM. */
  signal(SIGTERM, sighandler);
/* �뢮� ��������� ���. */
  if (nuz == 0) nuz = getnid();
  sprintf(msg, "//%d -> //%d", nuz, getnid());
  for (i=0; i<arg.argc; i++) { strcat(msg, " "); strcat(msg, arg.argv[i]); }
  oo(1, msg); oo(0, arg.name);
/* �뢮� ��������� ०��� ���. */
  strcpy(msg, "��砫� ");
  if (mode & MODEPUSK) strcat(msg, "��᪮���� ");
  if (mode & MODEAUTO) strcat(msg, "��⮬���᪮�� ");
  if (mode & MODEINTER) strcat(msg, "���ࠪ⨢���� ");
  if (mode & MODESYPER) strcat(msg, "ᯥ樠�쭮�� ");
  strcat(msg, "���..."); oo(0, msg);
}//oopen

/*
 *  oclose - �����襭�� ࠡ��� � ९��⠦���.
 */
void oclose(void) {
  int i; char msg[256]={0,0};
  for(i=1;i<mku;i++) if(pid_czr[i]>0) Send(pid_czr[i],msg,0,4,0);
/* �뢮� १���� ���. */
  strcpy(msg, "����� ");
  if (mode & MODEPUSK) strcat(msg, "��᪮���� ");
  if (mode & MODEAUTO) strcat(msg, "��⮬���᪮�� ");
  if (mode & MODEINTER) strcat(msg, "���ࠪ⨢���� ");
  if (mode & MODESYPER) strcat(msg, "ᯥ樠�쭮�� ");
  strcat(msg,"���...");
  if(rez==1) strcat(msg,"OK\n"); else  strcat(msg,"ERROR\n");
  oo(0, msg);
/* �����⨥ ����㠫쭮�� ������ � �����⨢訬 ts. */
  if (npid > 0) qnx_vc_detach(npid);
  for(i=1;i<mku;i++) if(pid_czr[i]>0) qnx_vc_detach(pid_czr[i]);
}//oopen

/*
 *  otest - ����� �㭪樨 ���.
 */
int otest(int x, int (*funk)()) {
  int i;
/* ����� �㭪樨 ���. */
  if (x & mode) {
    i = funk(); err += i;
  }//if
/* �����襭�� � ������⢮� �訡��. */
  return(i);
}//argtest -> ������⢮ �訡��

/*
 *  oexit - �����襭�� �ணࠬ��.
 */
void oexit(void) {
  oclose();
  if(err == 0) rez = OK; else rez = ERR;
  exit(rez);
}//oexit

/*
 *  tsz - �⥭�� 梥� ����� �� ���� ts-�ࢥ�
 *
 *  ident-> ����ᨬ����� �����䨪��� �����
 *  tipT -> ��� ��� (��᪮���, ��⮬��., ���ࠪ�.)
 */
int tsz( char ident[], int tipT) {
  char str[8],c=0;
/* �������� ����㠫쭮�� ������� � �����⨢訬 ts. */
  if (npid == 0) npid = qnx_vc_name_attach(nuz, 100, "/ts");
/* ��ନ஢���� � ���뫪� ��������� ��ப� */
  if(npid > 0) { str[0]=3; str[1]=tipT;
       str[2]=ident[0]; str[3]=ident[1];
       Send(npid, str, str, 5, 3); c=str[0];
               }//if
return(c); }//tsz

/*
 *  cweF - ��������� 梥� ����� � ���� ts-�ࢥ�
 *
 *  ident-> ����ᨬ����� �����䨪��� �����
 *  tipT -> ��� ��� (��᪮���, ��⮬��., ���ࠪ�.)
 *  cwet -> ��⠭��������� 梥� �����
 */
void cweF( char ident[], int tipT, int cwet) {
  char str[8];
/* �������� ����㠫쭮�� ������� � �����⨢訬 ts. */
  if (npid == 0) npid = qnx_vc_name_attach(nuz, 100, "/ts");
/* ��ନ஢���� � ���뫪� ��������� ��ப� */
  if(npid > 0) { str[0]=2;
       str[2]=ident[0]; str[3]=ident[1];
       str[4]=tipT; str[5]=cwet;
      if(str[2]|str[3]) Send(npid, str, 0, 6, 0);
               }//if
}//cweF

/*
 *  pskF - ����� ��� ����� � ���� ts-�ࢥ�
 *
 *  ident-> ����ᨬ����� �����䨪��� �����
 *  tipT -> ��� ��� (��᪮���, ��⮬��., ���ࠪ�.)
 */
void pskF( char ident[], int tipT ) {
  char str[8];
/* �������� ����㠫쭮�� ������� � �����⨢訬 ts. */
  if (npid == 0) npid = qnx_vc_name_attach(nuz, 100, "/ts");
/* ��ନ஢���� � ���뫪� ��������� ��ப� */
  if(npid > 0) { str[0]='t'; str[1]=tipT;
       str[2]=ident[0]; str[3]=ident[1];
       Send(npid, str, 0, 4, 0);
               }//if
}//pskF

/*
 *  oo - �뢮� ९��⠦�.
 *
 *  1-> �ਮ��� ९��⠦� (0-norm, 1-war, 2-err).
 *  2-> �����⥫� �� ��ப� ९��⠦�.
 */
void oo(int x, char msg[]) {
  char buf[80]={"   "};
/* �������� ����㠫쭮�� ������� � �����⨢訬 ts. */
  if (npid == 0) npid = qnx_vc_name_attach(nuz, 100, "/ts");
/* ��ନ஢���� ��ப� ९��⠦�. */
  if(npid > 0) strncat(buf, nam, 3);
  strncat(buf, msg, 72);
  if(x & 2) buf[1] = '!'; //else if(x & 1) buf[1] = '*'; 
/* �뢮� ��ப� ९��⠦�. */
  if(((x&2)&&(rep>1)) || (rep>2)) {
    if (npid > 0) Send(npid, buf, 0, strlen(buf)+1, 0); else puts(buf+1);
  }//if
}//oo

/*
 * ��ଠ�஢���� �뢮� �� ���ன�⢮ ९��⠦�
 */
int oprintf(int type, char *format, ...) {
	char    msgbuf[80];
	int     msglen;
	va_list arglist;

	va_start(arglist, format);
	msglen = vsprintf(msgbuf, format, arglist);
	va_end(arglist);
	oo(type, msgbuf);
	return (msglen);
} /* oprintf() */

/*
 *  report  - �뢮� ������� ९��⠦�.
 */
int report(char *format, ...) {
	char    msgbuf[80];
	int     msglen;
	va_list arglist;

	va_start(arglist, format);
	msglen = vsprintf(msgbuf, format, arglist);
	va_end(arglist);
	oo(0, msgbuf);
	return (msglen);
} /* oprintf() */

/*
 *  warning - �뢮� ������� ९��⠦�.
 */
int warning(char *format, ...) {
	char    msgbuf[80];
	int     msglen;
	va_list arglist;

	va_start(arglist, format);
	msglen = vsprintf(msgbuf, format, arglist);
	va_end(arglist);
	oo(1, msgbuf);
	return (msglen);
} /* oprintf() */

/*
 *  error   - �뢮� ९��⠦� � �訡���.
 */
int error(char *format, ...) {
	char    msgbuf[80];
	int     msglen;
	va_list arglist;

	va_start(arglist, format);
	msglen = vsprintf(msgbuf, format, arglist);
	va_end(arglist);
#ifdef TSINTh
	oo(2, msgbuf);
	oj(msgbuf);
#else
	oo(2, msgbuf);
#endif
	rez=2; return (msglen);
} /* oprintf() */

//--��㧠 ��� ॣ���஢�� ������ �� ��㣨� 㧫�� (czr)----------------
void og(int dt){
#ifdef TSINTh
        ogi(dt);
#else
		delay(dt);
#endif
 }
//--����� czr �� 㧫� u--------------------------------------
void cz(int u){ int t,r; char T[80]; pid_t p;
     p=qnx_vc_name_attach(u,100,"/czr"); if(p>0){ pid_czr[u]=p; return; }

     if(pid_czr[u]<=0){ t=getpid(); p=pid_czr[u]-1;
     if(p==-130) p=-101;
//????? -101 -21 ???
m101:if(p==-101) error("� ��⠫��� ��� �ணࠬ�� CZR");
     if(p< -100){ og(100); pid_czr[u]=p; return; }
     if(p==-1) p=-61; if(p==-90) p=-61; if(p==-50) p=-41; if(p==-25) p=-21;
     if(p< -60){ qnx_net_alive(T,mku);
               if(T[u]){ p=qnx_vc_name_attach(u,100,"/czr");
               if(p>0){ pid_czr[u]=p; return; }; p=-41; } else og(100); };
     if(p==-61) error("���� %d � �� �� �����",u);
     if(p< -60){ pid_czr[u]=p; return; }
     if(p< -40){ sprintf(T,"//%d %s/czr %d &",u,getcwd(NULL,0),t);
//                 if(system(T)){ pid_czr[u]=-100; return; } else p=-21; };
                 if(system(T)){ p=-101; goto m101; } else p=-21; };
     if(p==-41) error("� ��⠫��� ��� �ணࠬ�� CZR");
     if(p< -40){ og(100); pid_czr[u]=p; return; }
   pid_czr[u]=p; sprintf(T,"/czr%d",t); t=clock();
   while((p<0)&&((clock()-t)<1000)){ og(0); p=qnx_vc_name_attach(u,100,T); }
     if(p>0){ pid_czr[u]=p; return; }
   if(pid_czr[u]==-21) error("CZR �� 㧫� %d �� �⢥砥�",u); }}
//-- �⥭�� ���� 㧫� u ---------------------------------------------
int c_r(int u, int r){ unsigned short T[8],z; m_u;
        z=0; if((u==0)||(u==Muz)){ z=inp(r); return(z); }
        if(pid_czr[u]<=0) cz(u); if(pid_czr[u]<=0) return(-1);
        T[0]=1; T[1]=r; Send(pid_czr[u],T,T,8,8); z=T[2]; return(z); }
//-- ������ � ���� 㧫� u --------------------------------------------
void z_r(int u, int r, int d){ unsigned short T[8]; m_u;
        if((u==0)||(u==Muz)) outp(r,d); else{ if(pid_czr[u]<=0) cz(u);
        if(pid_czr[u]>0){ T[0]=2; T[1]=r; T[2]=d;
        Send(pid_czr[u],T,0,8,0); }}}
//-- �⥭�� ����-w 㧫� u ---------------------------------------------
int c_rw(int u, int r){ unsigned short T[8],z; m_u;
        z=0; if((u==0)||(u==Muz)){ z=inpw(r); return(z); }
        if(pid_czr[u]<=0) cz(u); if(pid_czr[u]<=0) return(-1);
        T[0]=3; T[1]=r; Send(pid_czr[u],T,T,8,8); z=T[2]; return(z); }
//-- ������ � ����-w 㧫� u --------------------------------------------
void z_rw(int u, int r, int d){ unsigned short T[8]; m_u;
        if((u==0)||(u==Muz)) outpw(r,d); else{ if(pid_czr[u]<=0) cz(u);
        if(pid_czr[u]>0){ T[0]=4; T[1]=r; T[2]=d;
        Send(pid_czr[u],T,0,8,0); }}}
//================ ����� � �ࠩ��ࠬ� ================================
char *dev_ac[10]; int *dev_ai[10],fdd[10],dev_max[10];
pid_t pid,dev_proxy[10],dev_proxr[10];
//------------------------------------------------------------
int dev_nac(int d, char N[], void *ac, int *ai, int max){ int i;
  dev_ac[d]=ac; dev_ai[d]=ai; dev_max[d]=max;
  fdd[d]=open(N,O_RDWR);
  if(fdd[d]<0){ printf("no  driver  \"%s\"\n",N); return(0); }
  dev_mode(fdd[d],0,_DEV_MODES);		//��⠭���� ०���
  dev_state(fdd[d],0,_DEV_EVENT_INPUT);		// ��⠭���� ���ﭨ�
  if(ai==0) return(1);
  while(dev_read(fdd[d],ac,max,max,0,2,0,0));
  for(i=0;i<max;i++) *(dev_ac[d]+i)=0;
  dev_proxy[d]=qnx_proxy_attach(0,0,0,-1);
  if(N[1]!='/') dev_proxr[d]=dev_proxy[d]; else{ sscanf(&N[2],"%d",&i);
                dev_proxr[d]=qnx_proxy_rem_attach(i,dev_proxy[d]); }
	dev_arm(fdd[d],dev_proxr[d],_DEV_EVENT_INPUT);	// ����� �roxy
   return(2); }
//-----------------------------------------------------------------
pid_t Crcv(int uz, void *B, int len){ int i,j;
         pid=Creceive(uz,B,len);
    if(pid>0){ for(i=0;i<10;i++) if(pid==dev_proxy[i]){ pid=0;
             if((j=*(dev_ai[i]))<dev_max[i]){
             read(fdd[i],dev_ac[i]+j,1); j++; *(dev_ai[i])=j; }
             dev_arm(fdd[i],dev_proxr[i],_DEV_EVENT_INPUT); break; }}
    return(pid); }
//-----------------------------------------------------------------
void dev_sdw(int d, int len){ int i,r; char *u; 
     r=dev_max[d]; u=dev_ac[d];
     for(i=len;i<r;i++) *(u+i-len)=*(u+i);
     for(i=r-len;i<r;i++) *(u+i)=0; *(dev_ai[d])=*(dev_ai[d])-len;
     if(*(dev_ai[d])<0) *(dev_ai[d])=0; }
//-- ����⨥ ����㯠 � �ࠩ���� D ---------------------------------------------
int  o_dr(char D[], char R[]){ int u,fd; char U[100];
       if(D[1]=='/'){ sscanf(&D[2],"%d",&u);
           if(u){ m_u; if(u!=Muz){ qnx_net_alive(U,mku);
           if(U[u]==0){ error("���� %d � �� �� �����",u); return(-2); }}}}
           fd=open(D,O_RDWR);
        if(fd<=0){ error("��� �ࠩ��� %s",D); return(-1); }
        dev_mode(fd,0,_DEV_MODES);
        dev_state(fd,0,_DEV_EVENT_INPUT);
//if'r':
        while(dev_read(fd,U,100,100,0,2,0,0));  return(fd); }
//-- �⥭�� �� �ࠩ��� D ----------------------------------------------
int  c_d(int fd, char *B, int lB){ int l,L=0; *B=0;
       while((l=dev_read(fd,&B[L],lB-L-1,lB-L-1,0,2,0,0))>0) L=L+l;
       *(B+L)=0; return(L); }
//-- ������ � �ࠩ��� D ------------------------------------------------
int  z_d(int fd, char *B, int l){
       write(fd,B,l); return(1); }
//========================================================================
/*
 *  ����஢�� 梥⮢
 */
#define _OBLACK        0
#define _OBLUE         1
#define _OGREEN        2
#define _OCYAN         0
#define _ORED          4
#define _OMAGENTA      0
#define _OBROWN        0
#define _OWHITE        15
#define _OGRAY         7
#define _OLIGHTBLUE    0
#define _OLIGHTGREEN   0
#define _OLIGHTCYAN    0
#define _OLIGHTRED     0
#define _OLIGHTMAGENTA 0
#define _OYELLOW       0
#define _OBRIGHTWHITE  0
#define _OLIGHTYELLOW  _YELLOW

/*
 * ��㧠
 */
void osleep(int time) {
	if (time != 0) {
		oprintf(1, "��㧠 %d ᥪ", time);
		sleep(time);
	} /* if */
} /* osleep() */

/*
 * ���ᢥ⪠ ��㯯� ����⮢ ts
 */
void ocolor(char string[], int color) {
	int i;

	if (*string != 0) {
		oprintf(1, "���᪠ ����⮢ %s 梥⮬ %d", string, color);
		cweF(string, 0 , color);
		for(i=0; i<strlen(string); i++) {
			if (string[i] != ',')
				continue;
			if (*(string + i + 1) != 0)
				cweF(string + i + 1, 0 , color);
		} /* for i */
	} /* if */
} /* ocolor() */
//--------------------------------------------------------------------
void podswID(){ int t=0,c;
     if(rez==-1) c=1; else if(rez==1) c=2; else if(rez==2) c=4; else c=0x64;
     m: if((podID[t]!=0)&&(podID[t+1]!=0)){ cweF(&podID[t],0,c); 
                 if(podID[t+2]==','){ t=t+3; goto m; }}}
//--------------------------------------------------------------------

