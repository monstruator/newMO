struct zag_CPP
{
 int marker1=0xff;
 int marker1=0xff;
 int KSS; //kol-vo slov
 char II; // CPP1=2 CPP2=3
 char TS;
 int PS;

}

struct form11 
{
	char nf=11; //nomer formul9ra
	char rezerv;
	char KU0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
	char ustKU0; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU1; // pereda4a : 1 - vkl, 0 - otkl 
	char ustKU1; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU2; // priem : 1 - vkl, 0 - otkl 
	char ustKU2; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU3; //  1 - TKI, 0 - RLI 
	char ustKU3; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU4; //  1 - FM1, 0 - FM2 
	char ustKU4; // 1 - ustanovit' , 0 - ne ustanavlivat'
	unsigned char KU5; // RT PRD 1 - 255
	char ustKU5; // 1 - ustanovit' , 0 - ne ustanavlivat'
	unsigned char KU6; // RT PRM 1 - 255
	char ustKU6; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU7; // oslablenie 0 - 25
	char ustKU7; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU8; // FK 1 - 12
	char ustKU8; // 1 - ustanovit' , 0 - ne ustanavlivat'
	unsigned char KU9; // Preambula 1 - 255
	char ustKU9; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU10; // porog MI 1 - 15
	char ustKU10; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU11; // porog SS 1 - 15
	char ustKU11; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU12; // Usilenie PRM 0 - 63
	char ustKU12; // 1 - ustanovit' , 0 - ne ustanavlivat'
	int CHK_SUM;
}

struct form13 
{
	char nf=13; //nomer formul9ra
	char rezerv;
	char KU0; //rezim raboti 0 - rabota, 1 - FK, 2 - SR
	char ustKU0; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU1; // pereda4a : 1 - vkl, 0 - otkl 
	char ustKU1; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU2; // priem : 1 - vkl, 0 - otkl 
	char ustKU2; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU3; //  1 - TKI, 0 - RLI 
	char ustKU3; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU4; //  1 - FM1, 0 - FM2 
	char ustKU4; // 1 - ustanovit' , 0 - ne ustanavlivat'
	unsigned char KU5; // RT PRD 1 - 255
	char ustKU5; // 1 - ustanovit' , 0 - ne ustanavlivat'
	unsigned char KU6; // RT PRM 1 - 255
	char ustKU6; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU7; // oslablenie 0 - 25
	char ustKU7; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU8; // FK 1 - 12
	char ustKU8; // 1 - ustanovit' , 0 - ne ustanavlivat'
	unsigned char KU9; // Preambula 1 - 255
	char ustKU9; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU10; // porog MI 1 - 15
	char ustKU10; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU11; // porog SS 1 - 15
	char ustKU11; // 1 - ustanovit' , 0 - ne ustanavlivat'
	char KU12; // Usilenie PRM 0 - 63
	char ustKU12; // 1 - ustanovit' , 0 - ne ustanavlivat'
	int CHK_SUM;
}

struct form12 
{
	char nCPP;
	char nf=12; //nomer formul9ra
	char SS1; // 0 - rabota, 1 - FK, 2 - SR	
	unsigned char SS0_r : 4; //reserv
	unsigned char SS0_prd : 1; // 0 - neispr , 1 - ispr
	unsigned char SS0_prm : 1; // 0 - neispr , 1 - ispr
	unsigned char SS0_cpp : 1; // 0 - neispr , 1 - ispr
	unsigned char SS0_all : 1; // 0 - neispr , 1 - ispr
	char SS2_0; // vid raboti : 0 - prm, 1 - prd
	char SS2_1; // tip raboti : 0 - tki, 1 - rli
	char rezerv; // rezerv
	char SS3; // 0 - FM1, 1 - FM2
	char SS5; // nomer RT PRM 7-12
	char SS4; // nomer RT PRD 7-12
	char SS7; // oslablenie PRD 0-25
	char SS6; // nomer FK 1-10
	char SS9; // PZ IB v PRD : 0 - net zarguzki, 1 - IB zagruzen, 2 - IS peredano 
	char SS8; // priznak priema IS (TKI) 0 - net priema, 1 - priem IS
	int SS10; // dlina preambuli : 1 - 255
	int SS11; // porog ss : 1 - 15
	int SS12; // porog mi : 1 - 15
	int SS13; // s4et4ik pss : 1 - 20	
	int SS14; // s4et4ik pmi : 1 - 20
	int SS15; // s4et4ik svch : 1 - 20
	int SS16; // s4et4ik sboinih: 1 - 20
	int SS17; // s4et4ik propuwennih : 1 - 20
	int SS18; // s4et4ik chksum  : 1 - 20
	int SS19; // srednii pik AFK  : 0 - 360
	int SS20; // max pik AFK  : 0 - 360
	int SS21; // oslablenie prm  : 0 - 63
	int KSS; //kontrol'na9 summa
}

struct form12 
{
	char nCPP;
	char nf=14; //nomer formul9ra
	char SS1; // 0 - rabota, 1 - FK, 2 - SR	
	unsigned char SS0_r : 4; //reserv
	unsigned char SS0_prd : 1; // 0 - neispr , 1 - ispr
	unsigned char SS0_prm : 1; // 0 - neispr , 1 - ispr
	unsigned char SS0_cpp : 1; // 0 - neispr , 1 - ispr
	unsigned char SS0_all : 1; // 0 - neispr , 1 - ispr
	char SS2_0; // vid raboti : 0 - prm, 1 - prd
	char SS2_1; // tip raboti : 0 - tki, 1 - rli
	char rezerv; // rezerv
	char SS3; // 0 - FM1, 1 - FM2
	char SS5; // nomer RT PRM 7-12
	char SS4; // nomer RT PRD 7-12
	char SS7; // oslablenie PRD 0-25
	char SS6; // nomer FK 1-10
	char SS9; // PZ IB v PRD : 0 - net zarguzki, 1 - IB zagruzen, 2 - IS peredano 
	char SS8; // priznak priema IS (TKI) 0 - net priema, 1 - priem IS
	int SS10; // dlina preambuli : 1 - 255
	int SS11; // porog ss : 1 - 15
	int SS12; // porog mi : 1 - 15
	int SS13; // s4et4ik pss : 1 - 20	
	int SS14; // s4et4ik pmi : 1 - 20
	int SS15; // s4et4ik svch : 1 - 20
	int SS16; // s4et4ik sboinih: 1 - 20
	int SS17; // s4et4ik propuwennih : 1 - 20
	int SS18; // s4et4ik chksum  : 1 - 20
	int SS19; // srednii pik AFK  : 0 - 360
	int SS20; // max pik AFK  : 0 - 360
	int SS21; // oslablenie prm  : 0 - 63
	int KSS; //kontrol'na9 summa
}















