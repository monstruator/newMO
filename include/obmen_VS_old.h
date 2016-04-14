#define BU1	1 //nomer interfeisa 
#define CPP	2 //nomer interfeisa
  

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

      union {
         struct {
            unsigned short cr; //nomer paketa
            short sach18[6];
            unsigned short nword;
            short word[97];           
         } svch1;
         struct {
            unsigned short cr;//nomer paketa
            short sach18[6];
            unsigned short nform; //kol-vo form3 po 10 slov
            short form1[9]; //10 //nositel
            short form2[4]; //5
            short form3[80];//1100
         } svch1_no;
		 
		  struct {
            unsigned short cr;
            short sach18[6];
            short form1[9]; //10
            short form3[10]; //5
         } svch1_nz;
		 
         struct {
            unsigned short cr;//nomer paketa
            short sach18[6];
            unsigned short nform; //kol-vo form4 po 11 slov
            short form1[9]; //10 //nositel
            short form4[88]; //pasport res
         } svch1_reo;
       
	     struct {
            unsigned short cr;//nomer paketa
            short sach18[6];
            short form1[9]; //10 //nositel
            short form4[11]; //pasport res
         } svch1_res;
		 
		 struct {
            unsigned short cr;//nomer paketa
            short sach18[6];
            short form1[9]; //10 //nositel
            short form2[4]; //pasport res
         } svch1_vz;
		 
      };      

     

      union {
         struct {
            unsigned short cr;//nomer paketa
            short sach18[6];
            unsigned short nword;
            short word[89];           
         } r999;
         struct {
            unsigned short cr;//nomer paketa
            short sach18[6];
            unsigned short nform; //kol-vo form6 po 12 slov
            short form3[9];
            short form2[3];
            short form6[48];
         } r999_no;
         struct {
            unsigned short cr;
            short sach18[6];
            unsigned short  nform; //kol-vo form8 po 20 slov
            short form3[9];
            short form4[80];
         } r999_reo;
         struct {
            unsigned short cr; //nomer paketa
            short sach18[6];
            short form3[8];
         } r999_vz;
      };
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


