
#ifndef PACKETS_H

   #define PACKETS_H

//-------------------- Status -------------------

   struct status {
      unsigned int out;
      unsigned int in;
      unsigned int link;
      unsigned int flag;
	  unsigned int rli;	  //режим запросов РЛИ
   };

   #define TIMEOUT_OFF 0
   #define TIMEOUT_ON 1

   struct timeout {
      unsigned int stat;
      unsigned int count;
   };

   struct counts {
      unsigned long in1;
      unsigned long in2;
      unsigned long in3;
      unsigned long in4;
      unsigned long in5;
      unsigned long in6;
      unsigned long out1;
      unsigned long out2;
      unsigned long out3;
      unsigned long out4;
      unsigned long out5;
      unsigned long out6;
   };

//-------------------- Mode -------------------

   struct workmode {
      unsigned int pr;

      unsigned int mo1a : 1;
      unsigned int mn1: 1;
      unsigned int scan1: 1;
      unsigned int scan2: 1;
	  unsigned int rli1: 1;
      unsigned int rli2: 1;
      unsigned int recv3: 1;
      unsigned int rez: 11;

      int kar;

      int addr1;
      int addr2;
      int addr3;
	  
	  unsigned short a0: 4;
      unsigned short a1: 4;
      unsigned short a2: 4;
      unsigned short a3: 4;
	  
	  unsigned short a4: 4;
      unsigned short a5: 4;
      unsigned short p0: 4;
      unsigned short p1: 4;
	  
      unsigned short p2: 4;
      unsigned short p3: 4;
      unsigned short p4: 4;
      unsigned short p5: 4;

      unsigned short cf1_svch1[10];  //слова 1-10 чф1
      unsigned short cf2_svch1[5];  //слова 1-5 чф2

      unsigned short cf1_svch2[10];  //слова 1-5 чф1
      unsigned short cf2_svch2[5];  //слова 1-5 чф2
	  unsigned short no_num;  //kol-vo form3 NO
	  
   };

//------------------- Constants ------------------

	#define KRK_OK 0
	#define KRK_ERR 1
	#define KRK_LINK_ERR 2
	#define KRK_SWITCH_RECV 3
	#define KRK_DATA_NOT 4
	#define KRK_MODE_REO 5
	#define KRK_DATA_OK 6
	#define KRK_CMD_OK 7
	#define KRK_LINK_OK 8
	#define KRK_SWITCH_TRANS 9
	#define KRK_DATA_AND_TRANS 10

//-------------------- Buffers -------------------

   struct buffer {
      char *start;
      char *end;
      char *load;
      char *save;
   };

   #define BUFFER1_SIZE 10000
   struct buffer1 {
      char data[ BUFFER1_SIZE ];
      unsigned int save;
      unsigned int load;
   };

   #define BUFFER2_SIZE 1500
   struct buffer2 {
      char data[ BUFFER2_SIZE ];
      unsigned int size;
   };

   #define BUFFER2_MAX 100
   struct buffer2kit {
      struct buffer2 buf[ BUFFER2_MAX ];
      unsigned int nsave;
      unsigned int nload;
   };

   #define BUFFER3_SIZE 1500
   struct buffer3 {
      char data[ BUFFER3_SIZE ];
      unsigned int size;
      unsigned int cmd;
      unsigned int param;
   };

   #define BUF3KIT_MAX 500
   #define BUF3KIT_BLK0 0x01
   #define BUF3KIT_BLK1 0x02
   #define BUF3KIT_BLK2 0x04
   #define BUF3KIT_BLK3 0x08
   #define BUF3KIT_BLK4 0x10
   #define BUF3KIT_BLK5 0x20
   #define BUF3KIT_BLK6 0x40
   #define BUF3KIT_BLKT 0x80
   #define BUF3KIT_CMD_NONE 0x000000
   #define BUF3KIT_CMD_BLK0 0x000001
   #define BUF3KIT_CMD_BLK1 0x000002
   #define BUF3KIT_CMD_BLK2 0x000004
   #define BUF3KIT_CMD_BLK3 0x000008
   #define BUF3KIT_CMD_BLK4 0x000010
   #define BUF3KIT_CMD_BLK5 0x000020
   #define BUF3KIT_CMD_BLK6 0x000040
   #define BUF3KIT_CMD_BLKT 0x000080
   #define BUF3KIT_CMD_OUT0 0x000100
   #define BUF3KIT_CMD_OUT1 0x000200
   #define BUF3KIT_CMD_OUT2 0x000400
   #define BUF3KIT_CMD_OUT3 0x000800
   #define BUF3KIT_CMD_OUT4 0x001000
   #define BUF3KIT_CMD_OUT5 0x002000
   #define BUF3KIT_CMD_OUT6 0x004000
   #define BUF3KIT_CMD_DEC 0x010000
   #define BUF3KIT_CMD_END 0x020000
   #define BUF3KIT_CMD_KRK 0x040000
   #define BUF3KIT_CMD_SVC 0x080000
   struct buffer3kit {
      struct buffer3 buf[ BUF3KIT_MAX ];
      unsigned int nsave;
      unsigned int nload;
      unsigned int blk;
   };

//-------------------- Test -------------------

   struct teststart {
      unsigned long itog;
      unsigned long bu;
   };

//-------------------- Socket 0 ---------------------

   struct formrls {
      short num_out;
      short num_in;
      int time; //int double
      float car_freq;
      float imp_freq;
      float inp_len;
      short mod_type;
      float scan_time;
      float targ_bear;
      float bear_sko;
      float targ_vip;
      float latitude;
      float longitude;
      float course;
      float speed;
      float div_course;
   };

   struct packcmd {
      unsigned short cr_com;
      short num_com;
      int a_params[5];
      short pr_bearing; 
      float p;
      float k;
      short nform;
      struct formrls form[3];
   };

   struct packusoi {
      unsigned short cr_com;
      short num_com;
      int lp2_param;
      short kzv;
      int k_o;
      short ended_loop;
      short krk;
      short link;

      unsigned int word_sost_kasrt1_1;
      unsigned int word_sost_kasrt1_2;
      unsigned int word_sost_kasrt2_1;
      unsigned int word_sost_kasrt2_2;
      unsigned int word_sost_0;
      unsigned int word_sost_1;
      unsigned int word_sost_2;
      unsigned int word_sost_3;
      unsigned int word_sost_sec;
      unsigned int word_sost_time;
      unsigned int word_sost_date;
      unsigned int word_sost_rts_1;
      unsigned int word_sost_rts_2;

      union {
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short word[4082];           
         } svch1;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form2[5];
            short form3[1100];
         } svch1_no;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form4[1100];
         } svch1_reo;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form2[5];
            short form5[6];
            short form6[4060];
            unsigned short num;
         } svch1_rli;
      };      

      union {
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short word[4082];           
         } svch2;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form2[5];
            short form3[1100];
         } svch2_no;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form4[1100];
         } svch2_reo;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form2[5];
            short form5[6];
            short form6[4060];
            unsigned short num;
         } svch2_rli;
      };      

      union {
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short word[103];           
         } r999;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form2[5];
            short form3[88];
         } r999_no;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short nword;
            short form1[10];
            short form4[88];
         } r999_reo;
         struct {
            unsigned short cr;
            unsigned short sach18;
            short nform;
            struct formrls form[3];
         } r999_cu2;
      };
   };

   struct errusoi {
      unsigned char a9 : 1;
      unsigned char a10 : 1;
      unsigned char a11 : 1;
      unsigned char a12 : 1;
      unsigned char a13 : 1;
      unsigned char a14 : 1;
      unsigned char a15 : 1;
      unsigned char r90_1 : 1;

      unsigned char a1 : 1;
      unsigned char a3 : 1;
      unsigned char a4 : 1;
      unsigned char a5 : 1;
      unsigned char a7 : 1;
      unsigned char a8 : 1;
      unsigned char a2 : 1;
      unsigned char r90_2 : 1;

      unsigned char bu1 : 1;
      unsigned char bu2 : 1;
      unsigned char cpp1 : 1;
      unsigned char cpp2 : 1;
      unsigned char svc1 : 1;
      unsigned char svc2 : 1;
      unsigned char r999 : 1;
      unsigned char usoi : 1;

      unsigned char cpp1dz : 1;
      unsigned char cpp1dp : 1;
      unsigned char cpp2dz : 1;
      unsigned char cpp2dp : 1;
      unsigned char rez1 : 1;
      unsigned char rez2 : 1;
      unsigned char rez3 : 1;
      unsigned char to : 1;
   };

   struct statkasrt {
      unsigned int s0got : 1;
      unsigned int s0prm : 1;
      unsigned int s0prd : 1;
      unsigned int s0cpp : 1;
      unsigned int s1fk : 1;
      unsigned int s1fm : 1;
      unsigned int s1prm : 1;
      unsigned int s1rab : 1;
      unsigned int s2prd : 3;
      unsigned int s2prm : 4;
      unsigned int rez1 : 1;
      unsigned int s3prd : 4;
      unsigned int s4fk : 4;
      unsigned int s5ss : 1;
      unsigned int s5mi : 1;
      unsigned int s5ib : 1;
      unsigned int s5erib : 1;
      unsigned int s6upr : 1;
      unsigned int s6inf : 1;
      unsigned int s6prd : 1;
      unsigned int s7inf : 1;
 
      unsigned int s8erib : 8;
      unsigned int s9pream : 16;
      unsigned int rez2 : 8;

      unsigned int s9ss : 16;
      unsigned int s9mi : 16;
   };

   struct sostrts {
      unsigned int rts : 1;
      unsigned int svc1 : 1;
      unsigned int svc2 : 1;
      unsigned int dmv : 1;
      unsigned int usoi : 1;
      unsigned int rej : 1;
      unsigned int fk : 4;
      unsigned int svc1_rej : 1;
      unsigned int svc1_m : 1;
      unsigned int svc1_rejprm : 1;
      unsigned int svc1_rab : 1;
      unsigned int svc1_prd : 4;
      unsigned int svc1_prm : 4;
      unsigned int svc1_oslprd : 4;
      unsigned int svc1_fk : 4;
      unsigned int svc1_rez1 : 2;

      unsigned int svc2_rej : 1;
      unsigned int svc2_m : 1;
      unsigned int svc2_rejprm : 1;
      unsigned int svc2_rab : 1;
      unsigned int svc2_prd : 4;
      unsigned int svc2_prm : 4;
      unsigned int svc2_oslprd : 4;
      unsigned int svc2_fk : 4;
      unsigned int dmv_rej : 1;
      unsigned int dmv_kan : 6;
      unsigned int dmv_vidrab : 1;
      unsigned int dmv_fk : 2;
      unsigned int dmv_rez2 : 2;
};

   struct header0 {
      unsigned char type;
      unsigned char npack;
      unsigned char npart;
      unsigned char allpart;
//      unsigned int nbyte;
   };

   struct packet0 {
      struct header0 head;
      unsigned char data[];
   };

//--------------- Socket 1,2 ---------------

   struct header12 {
      unsigned short mark1[2];

      unsigned short key[4];

      unsigned short mark2[2];

      unsigned short rez9 : 6;
      unsigned short npol : 10;

      unsigned short rez10 : 6;
      unsigned short notp : 10;

      unsigned short rez11 : 12;
      unsigned short nspol : 4;

      unsigned short nsotp : 4;
      unsigned short nsoob : 10;
      unsigned short rez12 : 2;

      unsigned short rez13 : 8;
      unsigned short kss : 8;
   //   unsigned short kss2 : 4;

      unsigned short kvi : 4;
      unsigned short sk : 1;
      unsigned short kg : 1;
      unsigned short kpts : 1;
      unsigned short ps : 1;
      unsigned short kzo : 4;
      unsigned short rez14 : 4;

      unsigned short totpm;

      unsigned short totps;
   };

   struct packet12 {
      struct header12 head;
      unsigned short wf[];
   };

//--------------- Device 3,4 ---------------

   struct header34 {
      unsigned short pream;
      unsigned char code;
   };

   struct packet34 {
      struct header34 head;
      unsigned char data[];
   };

//--------------- Device 5,6 ---------------

   struct header56 {
      unsigned char code;
   };

   struct packet56 {
      struct header56 head;
      unsigned char data[];
   };

   struct config999 {
      unsigned char rrc : 1;
      unsigned char ap : 1;
      unsigned char pwr : 2;
      unsigned char s1i : 1;
      unsigned char sa : 1;
      unsigned char sp : 2;

      unsigned char can;
   };

//--------------- Forms ---------------

   struct form11 {
      unsigned short rez1: 12;
      unsigned short kdv: 4;

      unsigned short ku7: 5;
      unsigned short x0: 1;
      unsigned short x1: 1;
      unsigned short rez2: 5;
      unsigned short ku3: 1;
      unsigned short ku2: 1;
      unsigned short ku1: 1;
      unsigned short ku0: 1;

      unsigned short ku4: 3;
      unsigned short rez3: 13;

      unsigned short ku5: 4;
      unsigned short rez4: 12;

      unsigned short ku6: 4;
      unsigned short rez5: 12;

      unsigned short rez6: 2;
      unsigned short ku9z10: 1;
      unsigned short ku9z9: 1;
      unsigned short ku9z8: 1;
      unsigned short ku9z7: 1;
      unsigned short ku9z6: 1;
      unsigned short ku9z5: 4;
      unsigned short ku9z4: 1;
      unsigned short ku9z3: 1;
      unsigned short ku9z2: 1;
      unsigned short ku9z1: 1;
      unsigned short ku9z0: 1;

      unsigned short rez7: 7;
      unsigned short ku13: 1;
      unsigned short ku12: 1;
      unsigned short ku11: 1;
      unsigned short ku10: 1;
      unsigned short ku8: 5;

      unsigned short rez8;
   };

   struct form12 {
      unsigned short ncpp: 2;
      unsigned short rez1: 10;
      unsigned short kdv: 4;

      unsigned short rez2: 9;
      unsigned short s1vr: 1;
      unsigned short s1rp: 1;
      unsigned short s1tr: 1;
      unsigned short s0got: 1;
      unsigned short s0cpp: 1;
      unsigned short s0prd: 1;
      unsigned short s0prm: 1;

      unsigned short s1m;

      unsigned short s2prd;

      unsigned short s2prm;

      unsigned short s7: 1;
      unsigned short s6inf: 1;
      unsigned short s6upr: 1;
      unsigned short s5erib: 1;
      unsigned short s5ib: 1;
      unsigned short s5mi: 1;
      unsigned short s5ss: 1;
      unsigned short s4: 5;
      unsigned short s3: 4;

      unsigned short rez7: 4;
      unsigned short kprd: 1;
      unsigned short s9mi: 1;
      unsigned short s9ss: 1;
      unsigned short s9pr: 1;
      unsigned short s8: 8;
   };

   struct sac {
      unsigned short ps: 1;
      unsigned short vr: 1;
      unsigned short rez1: 1;
      unsigned short kvi: 4;
      unsigned short rez2: 1;
      unsigned short nf: 8;

      unsigned short a0: 4;
      unsigned short a1: 4;
      unsigned short a2: 4;
      unsigned short a3: 4;

      unsigned short a4: 4;
      unsigned short a5: 4;
      unsigned short p0: 4;
      unsigned short p1: 4;

      unsigned short p2: 4;
      unsigned short p3: 4;
      unsigned short p4: 4;
      unsigned short p5: 4;

      unsigned short r0: 4;
      unsigned short r1: 4;
      unsigned short r2: 4;
      unsigned short r3: 4;


      unsigned short v0: 4;
      unsigned short v1: 4;
      unsigned short v2: 4;
      unsigned short v3: 4;
   };
 
 struct sac_dmv {
      unsigned short ps: 1;
      unsigned short vr: 1;
      unsigned short rez1: 1;
      unsigned short kvi: 4;
      unsigned short rez2: 1;
      unsigned short nf: 8;

      unsigned short a0: 4;
      unsigned short v1: 4;
      unsigned short a2: 4;
      unsigned short v3: 4;

      unsigned short p4: 4;
      unsigned short a5: 4;
      unsigned short p0: 4;
      unsigned short r1: 4;

      unsigned short v2: 4;
      unsigned short r3: 4;
      unsigned short a4: 4;
      unsigned short p5: 4;

      unsigned short r0: 4;
      unsigned short p1: 4;
      unsigned short r2: 4;
      unsigned short p3: 4;

      unsigned short v0: 4;
      unsigned short a1: 4;
      unsigned short p2: 4;
      unsigned short a3: 4;
   };

   struct form193 {
      struct sac s;
      unsigned short t1: 8;
      unsigned short t2: 8;
      unsigned short pn: 8;
      unsigned short kfs: 8;
      unsigned short v1_0: 4;
      unsigned short v1_1: 4;
      unsigned short v1_2: 4;
      unsigned short v1_3: 4;
      unsigned int v2_0: 6;
      unsigned int v2_1: 6;
      unsigned int v2_2: 7;
      unsigned int r11: 1;
      unsigned int v3_0: 6;
      unsigned int v3_1: 6;
      unsigned short v3_2: 8;
      unsigned short r12: 8;
      unsigned short r13: 16;
      unsigned short r14: 16;
      unsigned short r15: 16;
      unsigned short r16: 16;
      unsigned short r17: 16;
      unsigned short r18: 16;
      unsigned short r19: 16;
      unsigned short r20: 16;
   };

/*   struct form199 {
      struct sac s;  			//6 short
      unsigned short t1: 8;
      unsigned short t2: 8;

      unsigned short pn: 8;
      unsigned short kfs: 8;

      unsigned short v1_0: 4;
      unsigned short v1_1: 4;
      unsigned short v1_2: 4;
      unsigned short v1_3: 4;

      unsigned int v2_0: 6;
      unsigned int v2_1: 6;
      unsigned int v2_2: 7;
      unsigned int r11: 1;
      unsigned int v3_0: 6;
      unsigned int v3_1: 6;

      unsigned short v3_2: 8;
      unsigned short r12: 8;
      unsigned short r13: 16;
      unsigned short r14: 16;
      unsigned short r15: 16;
      unsigned short r16: 16;
      unsigned short r17: 16;
      unsigned short r18: 16;
      unsigned short r19: 16;
      unsigned short r20: 16;
      unsigned short f1[8];
   };
*/
   struct form199 {
      struct sac s;  			//6 short
      unsigned short f193[6];  //слова 7-12 ф193
      unsigned short cf1[10];  //слова 1-10 чф1
      unsigned short cf2[5];  //слова 1-5 чф2
   };


   struct fomr1n {
      unsigned short r1: 4;
      unsigned short tps: 1;
      unsigned short r2: 2;
      unsigned short tak: 1;
      unsigned short rilv: 2;
      unsigned short rp: 2;
      unsigned short nf: 4;

      unsigned short kx: 15;
      unsigned short kxz: 1;

      unsigned short ky: 15;
      unsigned short kyz: 1;

      unsigned short kvk: 16;

      unsigned short vp: 7;
      unsigned short svk: 9;

      unsigned short v0: 6;
      unsigned short v1: 6;
      unsigned short v2: 4;

      unsigned short sko: 13;
      unsigned short rrpnk: 3;

      unsigned short r3: 1;
      unsigned short nvkg: 3;
      unsigned short bnvk0: 4;
      unsigned short bnvk1: 4;
      unsigned short bnvk2: 4;

      unsigned short tv0: 6;
      unsigned short tv1: 6;
      unsigned short tv2: 4;

      unsigned short ks: 16;
   };      

#endif

