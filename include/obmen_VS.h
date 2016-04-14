#define BU1	1 //nomer interfeisa 
#define CPP	2 //nomer interfeisa
typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)
	short	SVCH_FORM_3[80];	//(20 байт) * 8 фомуляров (Формуляр НЦ)

	short	null_bytes[519];	//620 - 101 = 519

} Mem_Region23_NO_t;	//202 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];	//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_4[88];	//(22 байт) * 8 фомуляров (Формуляр РЭС)

	short	null_bytes[515];	//620 - 105 = 515

} Mem_Region23_REO_t;	//210 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_3[10];	//20 байт (Формуляр НЦ)

	short	null_bytes[594];	//620 - 26 = 594

} Mem_Region23_CpNC_t;	//52 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];	//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_4[11];	//22 байт (Формуляр РЭС)

	short	null_bytes[593];	//620 - 27 = 593

} Mem_Region23_CpRES_t;	//54 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)

	short	null_bytes[600];	//620 - 20 = 600

} Mem_Region23_VZ_t;	//40 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short cr_transm_takt;
	unsigned short num_words;

	short	SVCH_FORM_5[5];
	short	SVCH_FORM_6[606];


} Mem_Region23_RLI_t;	//1240 б.инф.

typedef	union {
	short buf[620];

	Mem_Region23_NO_t 		Mem_Region_NO;		//Освещение НО	(kvi = 5)
	Mem_Region23_REO_t 		Mem_Region_REO;		//Освещение РЭО	(kvi = 7)
	Mem_Region23_CpNC_t 	Mem_Region_CpNC;	//Целепоказ НЦ	(kvi = 6)
	Mem_Region23_CpRES_t 	Mem_Region_CpRES;	//Целепоказ РЭС	(kvi = 8)
	Mem_Region23_VZ_t 		Mem_Region_VZ;		//Взаимодействие	(kvi = 2)
	Mem_Region23_RLI_t 		Mem_Region_RLI;		//Режим РЛИ			(kvi = 9)

}Mem_Region23_t;

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)
	short	SVCH_FORM_3[40];	//(20 байт) * 4 фомуляров (Формуляр НЦ)

} Mem_Region4_NO_t;	//122 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_4[44];	//(22 байт) * 4 фомуляров (Формуляр РЭС)

} Mem_Region4_REO_t;	//122 б.инф.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 байт (Формуляр НОСИТЕЛЬ)
	short	SVCH_FORM_2[4];		//8 байт (Формуляр ТР)

	short	null_bytes[41];	//122 - 40 = 82

} Mem_Region4_VZ_t;	//40 б.инф.


 typedef union{
//	short buf[97];
//	Mem_Region4_NO_t 	Mem_Region_NO;		//Освещение НО		(kvi = 5)
//	Mem_Region4_REO_t 	Mem_Region_REO;		//Освещение РЭО		(kvi = 7)
//	Mem_Region4_VZ_t 	Mem_Region_VZ;		//Взаимодействие	(kvi = 4)
	short buf[61];	//Изменение протокола: дмв - как свч (pdn 08.04.2016)
	Mem_Region4_NO_t 	Mem_Region_NO;		//Освещение НО		(kvi = 5)
	Mem_Region4_REO_t 	Mem_Region_REO;		//Освещение РЭО		(kvi = 7)
	Mem_Region4_VZ_t 	Mem_Region_VZ;		//Взаимодействие	(kvi = 4)

} Mem_Region4_t;

 

typedef struct 
 {
      short num_out;
      short num_in;
      int time; //double
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
   } formrls;

//////////////////////////////////////

typedef struct {
	  unsigned char temp[4];
      unsigned short cr_com;
      short num_com;
      int a_params[5];
      //short pr_bearing; 
      //float p;
      //float k;
      //short nform;
      //formrls form[3];
   } packcmd;

/////////////////////////////////////
   
typedef   struct  {
	  unsigned char temp[4];
      unsigned short cr_com; //por9dkovii nomer
      short num_com; //nomer poslednei
      int lp2_param; //1 parametr komandi
      short kzv; //kod zaverweni9 (0 - norma)
      int k_o; //kod owibki
      short fk; //kod FK (0 - norma)
      short link; 

      unsigned int sost_kasrt[9];
      unsigned int sost_spiak;
	  unsigned int sost_r999;

      Mem_Region23_t Mem_Region2;
	  Mem_Region4_t Mem_Region4;
   } packusoi;

  
   
typedef struct 
{
	//unsigned short n_step; //nomer waga vipolneni9 comandi
	unsigned short n_chan; //nomer intergeisa
	unsigned short n_com;  //nomer komandi dl9 zadannogo interfeisa
    short          status; //status vipolneni9
	/*unsigned short w_answ[2]; //neobhodimost' zdat' otvet, otvet polu4en //1-gdat' 2-gotovo
	unsigned short n_answ;	//neobhodimii nomer otveta, polu4ennii otvet
	*/
	
} step_UPR;  //opisanie mini comandi dl9 kazdogo intergeisa na tekuwem wage
   
typedef struct 
{
	unsigned short num_mini_com; //kol-vo mini komand na kagdom wage
	unsigned short done_mini_com; //kol-vo mini vipolnennih komand na kagdom wage
    long 		   t_start; //vrem9 starta (v tikah taimera dispet4era)
	long 		   t_stop;  //vrem9 okon4ani9
	step_UPR s[10]; //nabor mini komand dl9 interfeisov na tekuwem wage 
} c_UPR;  //komanda upravleni9 
 
typedef struct 
{
	long sys_timer; //s4et4ik timera
	packcmd fromMN3;	//komanda iz MN3	(provereno i prin9to k ispolneniu)
	packcmd inbufMN3;	//komanda iz MN3	(bufer priema dl9 kanala MN3)	
	packusoi  toMN3;	//otvet v MN3
	short cvs; //10 ili 11
	c_UPR work_com[10]; //wagi vipolneni9 tekuwei komandi upravleni9
	short cur_step; //tekuwii wag vipolneni9 komandi
	short kol_step; //kol-vo wagov vipolneni9 komandi
	short verbose;	//detalizaci9 pe4ati
}SHMEM_MO3A;


