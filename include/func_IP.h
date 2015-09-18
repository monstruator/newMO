//=====================================================================================
//=============      �㭪樨    �ਥ��-��।��   IP / UDP     ========================
//=====================================================================================
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#if (LONG_MAX !=0x7fffffffUL)
#error "Unsupported platform, using long type isn't 32 bits"
#endif

//=====================================================================================
//=============   ���䨣���� ᮪�� � ���⮢ �ਥ��-��।�� ========================
//=====================================================================================
#define UDP_KADR_MAX 1200  // ???? - ��筨��

typedef struct
         {
          int soc;        //�����䨪��� socket-�
          int port_out;   //����� ���� �� ��।��� ����ᮢ
          int port_inp;   //����� ���� �� �ਥ� �⢥⮢
          int y;          //���ﭨ� ������
          char *serv_name;//㪠��⥫� �� ��� �ࢥ�
          struct hostent *host;    //㪠��⥫� ��� ���᪠
                                  //IP-���� �� ����� �ࢥ� 
          struct sockaddr_in serv;      //���� �ࢥ�
          struct sockaddr_in serv_from; //����, �� ���஬� ��蠥� 
          struct sockaddr_in from;      //����, ��㤠 䠪��᪨ ����稫� 
         }Udp_Client_t;
//=====================================================================================
//=============   �㭪樨  �ਥ��-��।�� �ࢥ� � ������   ========================
//=====================================================================================

//---------------------------------------------------
int Udp_Client_Ini(Udp_Client_t *Uc,char *serv_name,int port_out,int port_inp)
 {
  int broadcast;
  int dl;
  int x; 
  Uc->port_out=port_out;
  Uc->port_inp=port_inp;
  Uc->y=1;
  Uc->serv_name=serv_name;
  Uc->soc=socket(AF_INET,SOCK_DGRAM,0);
  if(Uc->soc<0)Uc->y=-1; //��㤠� �� ᮧ����� socket-�
  else
    {//socket ᮧ���  
     Uc->host=(struct hostent*)gethostbyname(Uc->serv_name);
     if(Uc->host==NULL)
      {//��㤠� �� ��।������ IP ����
       Uc->y=-2;
      }//��㤠� �� ��।������ IP ����
      else
       {//IP-���� ������
        memcpy(&Uc->serv.sin_addr,Uc->host->h_addr,
                                  Uc->host->h_length);
        Uc->serv.sin_family=AF_INET;
        Uc->serv.sin_port=htons(Uc->port_out);
        broadcast=1; //-ࠧ�蠥� �ப����⥫��� ��।���
        if(setsockopt(Uc->soc,SOL_SOCKET,SO_BROADCAST,
                     &broadcast,sizeof(broadcast))<0)
              {//��㤠� �� ��⠭���� BROADCAST
               Uc->y=-3;
              }//��㤠� �� ��⠭���� BROADCAST
      }//IP-���� ������
     }//socket ᮧ���

  if(Uc->y==1)
     {//����ன�� �ਥ�����
      Uc->serv_from.sin_family=AF_INET;
      Uc->serv_from.sin_addr.s_addr=INADDR_ANY;
//      Uc->serv_from.sin_port=0;//htons(Uc->port_inp);
      Uc->serv_from.sin_port=htons(Uc->port_inp);
      x=bind(Uc->soc,(struct sockaddr*)&Uc->serv_from,
                             sizeof(Uc->serv_from));
    if(x<0)
     {//��㤠� �� �����祭�� ����
      printf("Udp_Client_Ini : bind(...)=%d\n",x);
      fflush(stdout); 
      Uc->y=-4;
     }//��㤠� �� �����祭�� ����
     else
     {//���� �����祭 ��ଠ�쭮
      dl=sizeof(struct sockaddr_in);
      x=getsockname(Uc->soc,(struct sockaddr*)&Uc->serv_from,&dl);
//      printf("gethostname=%d\n",x);
//      printf("Udp_Client_Ini fr_port=%d\n",ntohs(Uc->serv_from.sin_port));
//      fflush(stdout);
     }//���� �����祭 ��ଠ�쭮     
     }//����ன�� �ਥ�����
  return(Uc->y);
 }
//---------------------------------------------------
int Udp_Client_Send(Udp_Client_t *Uc,void *otkuda,int skolko)
 {
  int x; 
//  if((otkuda!=NULL)&&(skolko<=UDP_KADR_MAX)&&(skolko>0))
  if((otkuda!=NULL)&&(skolko>0))
   {//����� ���४��, ����� ��।�����
    x=sendto(Uc->soc,otkuda,skolko,0,
                (struct sockaddr*)&Uc->serv,sizeof(Uc->serv));
   }//����� ���४��, ����� ��।�����
  return(x);
 }
//---------------------------------------------------
int Udp_Client_Read(Udp_Client_t *Uc,void *kuda,int limit)
 {//��������饥 �⥭�� �⢥�
  int x,dfr;
  if(Uc->y==1)
     {//�������� ����� �� UDP
       dfr=sizeof(Uc->serv_from);
       memcpy(&Uc->from,&Uc->serv_from,sizeof(Uc->serv_from));
       x=recvfrom(Uc->soc,kuda,limit,0,(struct sockaddr*)&Uc->from,&dfr);
     //  printf("sin_port=%d\n",ntohs(Uc->from.sin_port)); 
//      printf("Udp_Client_Read from_addr=%d\n",ntohs(Uc->from.sin_addr.s_addr));
     //  fflush(stdout);
     }//�������� ����� �� UDP
  else
  {//�ਥ���� �� ����஥�
    printf("Udp_Client_Read: �������� ������ �� ������஥����� �ਥ�����\n");
    fflush(stdout);
    delay(1000);
    x=0;   
  }//�ਥ���� �� ����஥� 
  return(x);
 }//��������饥 �⥭�� �⢥�
//-----------------------------------------------------
