///// �������� ������ ��.5� � �⠭樨 ��3� 						/////

//==========================================================================
//����� ����묨 ����� �ਡ�ࠬ�  5�  � mo3  
//
//#define 	SUM_FORM_SVCH		100  //��।����� � MN3_TYPE.h

typedef struct 
{

	int		time_send;		// �६� ��⮪ ���뫪� ����� � ��, �, int;
	short	num_bort;		// ���⮢�� ����� ���⮫�� (1-999), short;
	short	num_VK;			// ����� ���⮫�� � ��㯯�, short (1-4);
	short	rejim_fly;		// ����� ����� ��, short;
					 	    //	(0-������� (�������� � ��।���� ���), 
						    //	1-�஫�� �� (�������� � ���� �⢥��⢥����� ���), 
      						//	2-��室 �� �� (�������� ��� ���� �⢥��⢥����� ���), 
      						//	3-������ �� ����);
	short	KPC;			// ����� ࠡ��� � ���, short; (1-���, 2-���);
	short	tip_AK;			// ��� ��, short; (0-��, 1-��);
	short	work_VK;		// ����� ࠡ��� ��, short; (0-"�ᢥ饭�� ��", 1-"�ᢥ饭�� ���");
	short	work_PNK;		// ����� ࠡ��� ���, short; (0-���, 1-����, 2-���ᮢ������, 
							//   3-�⪠� ���);
	int		time_VK;		// �६� ��⮪ ��।������ ���न��� � ��ࠬ��஢ �������� ��, �, int;
	float	Xvk;			// ���न���� ���, �, float (�� 業�� ��);
	float	Yvk;			// ���न���� Y��, �, float (�� 業�� ��);
	float	Kvk;			// ���� ��, ࠤ, float;
	float	Vvk;			// ������� ��, �/�, float;
	float	Hvk;			// ���� ����� ���, �, float;
	float	SKOvk;			// ��㣮��� ��� ���� ��, �, float;
	float	fi_TR;			// ���� 業�� ��, ࠤ, float;
	float	la_TR;			// ������ 業�� ��, ࠤ, float;
						    //   �� �ନ��� ���ଠ�� � ���न���� ᢮��� ���⮯�������� � 
							//   ��אַ㣮�쭮� ��⥬� ���न��� ��, � ���ன ��砫� ���न��� 
							//   ᮢ��饭� � �窮� 業�� ��, ��� � ���ࠢ���� �� ᥢ��, ��� Y - �� 
							//   ���⮪.
}	FORM_VK_t; 
								//�����  "��ᯮ�� ��" 
typedef struct 
{
	int		time_send;      // �६� ��⮪ ���뫪� ����� � ��, �, int;
	short	num_VK;			// ����� 楫� � �㬥�樨 �� (� �� �।�� ��� ��), short, (1-100);
	short	tip_NC;			// ��� 楫�, short; (0-�� ��।����, 1-������ ��, 2-����� ��, 
							//   3-���, 4-���);
							//   ��� 楫� ��� ����砥�, �� �� ����� �� 10-� ᥪ㭤��� 横��� 
							//   ������� �।�⢠�� ��� �� ��� �⮩ 楫� �뫨 ��।����� 
							//   ࠤ���孨�᪨� ��ࠬ����;
	short	P_GO;			// �ਧ��� ��, short; (0-�� ��।����, 1-᢮�, 2-�㦮�);
	short	P_KV;			// �ਧ��� �� (��ࠬ��஢ ��������), short; 
							//   (0-���� � ᪮���� �� ��।�����, 
							//   1-���� � ᪮���� ��।�����);
	short	P_PS;			// �ਧ��� �� (���� ᮯ஢�������), short;
					//   (1-�� ��᫥���� 10-� ᥪ㭤��� 横�� ������� ���⠪� � 楫�� �� 
					//   �뫮, � �⮬ ��砥 �� ���⮯�������� ���࠯�������� �� ������ 
					//   ���뫪� ��ᯮ�� � ��, � ��ࠬ���� �������� ᮮ⢥������ �������
					//   ��᫥����� ���⠪� � 楫��;
					//   0-�� ��᫥���� 10-� ᥪ㭤��� 横�� ������� ���⠪� � 楫�� ��,
					//  � �⮬ ��砥 �� ���⮯�������� � ��ࠬ���� �������� ᮮ⢥������
					//   ������� ��᫥����� ���⠪� � 楫��);
	int		time_NC;      	// �६� ��⮪ ��᫥����� ���⠪� � 楫��, �, int;
	float	Xnc;			// ���न��� ���, �, float (�� 業�� ��);
	float	Ync;			// ���न��� Y��, �, float (�� 業�� ��);
	float	SKO_X;			// ��� 楫� �� �, �, float;
	float	SKO_Y;			// ��� 楫� �� Y, �, float;
							//   ����� �� ��� 楫� ���뢠�� ⮫쪮 �訡�� �� ��।������ ���न��� 
							//   楫� � ��� ��, ��� ��� �訡�� ���.
	float	Knc;			// ���� 楫�, ࠤ, float;
	float	Vnc;			// ������� 楫�, �/�, float;
	float	Dnc_nakl;			// ��������� ���쭮��� �� 楫�, �, float (�� ��);
	float	Pnc;			// ������ 楫�, ࠤ, float (�� ��);
					//   ��� 楫�� � �ਧ����� ��=0 ��������� ���쭮��� � ������ 㪠�뢠���� 
					//   �� ������ ��᫥����� ���⠪� � 楫��; ��� 楫��  � �ਧ����� ��=1 
					//   � ����⢥ ��������� ���쭮�� � ������� 楫� 㪠�뢠���� ���祭��,
					//  ���࠯���஢���� �� ������ ���뫪� ����� � ��.

}	FORM_PSP_NC_t; 
								//�����  "��ᯮ�� ���" 
typedef struct 
{
	int	    time_send;		// �६� ��⮪ ���뫪� ����� � ��, �, int;
	short	num_VK;			// ����� 楫� � �㬥�樨 �� (� �� �।�� ��� ��), short, (1-100);
	short	tip_RES;		// ����� ⨯� ��� �� ��⠫��� ��, short;
	short	SIGN;			// ��� ����祭�� ���, short; (1-���, 2-�����뢭�, 3-����������뢭�);
	short	P_IZL;	 		// ��魮��� ����祭�� ���, ��, short;
	float	T_i;			// ��ਮ� ����७�� ᨣ����� ���, ���, float;
	float	tau_i;			// ���⥫쭮��� ������ ���, ��, float;
	float	T_OBL;			// ��ਮ� ����祭��, �, float;
	float	tau_P;			// ���⥫쭮��� ��窨 �����ᮢ ���, ��, float;
			      //   � ����⢥ ���祭�� ࠤ���孨�᪨� ��ࠬ��஢ 㪠�뢠���� ���祭��,
			      //   ����祭�� �� �६� ��᫥����� ���⠪� � ��� �।�⢠�� ��� ��.
	int	    time_RES;		// �६� ��⮪ ��᫥����� ���⠪� � ���, �, int;
	float	Dres_nakl;      // ��������� ���쭮��� ���, �, float; (�� ��);
	float	Pres;			// ������ ���, ࠤ, float; (�� ��);
			      //   ������ � ��������� ���쭮��� 楫� 㪠�뢠���� �� ������ ��᫥����� 
			      //   ���⠪� � ��� (��������, �� ���⠪� � ��� �������� ⮫쪮 �� 
			      //   ����稨 ࠤ������樮����� ���⠪�).

}	FORM_PSP_RES_t; 
								//�����  ������ ��
typedef struct 
{
	FORM_VK_t		FORM_VK; 
	unsigned short	cr_PSP_NC;	//����� ����� PSP_NC
	unsigned short	cr_PSP_RES;	//����� ����� PSP_RES
	FORM_PSP_NC_t	FORM_PSP_NC[SUM_FORM_SVCH]; 
	FORM_PSP_RES_t	FORM_PSP_RES[SUM_FORM_SVCH]; 

}	FORM_SVCH_t; 
								//�����  ��3 -> ��3  (������ 楫��)
typedef struct 
{
	FORM_SVCH_t	FORM_SVCH1; 
	FORM_SVCH_t	FORM_DMV; 

}	FORM_MO_MN_t;  

								//����� "���� ���"
typedef struct 
{
	int	    time_send;		// �६� ��⮪ ���뫪� ����� � ��, �, int;
	int	    time_cadr;		// �६� ��⮪ �ନ஢���� ����, �, int;
	float	X;				// ���न��� X 業�� ����, �, float (�� 業�� ��);
	float	Y;				// ���न��� Y 業�� ����, �, float (�� 業�� ��);
	short	pr_IRLI;		// �ਧ��� ���� ���, short (0-���1, 1-���2);
	short	scale;      	// �ਧ��� 誠��, short (1-260 ��, 2-130 ��, 3-65 ��, 4-32 ��);
							// (�ᯮ������ ⮫쪮 � ०��� ���-1)
	int		num_NC;			// ����� ��, int (0 - ��� 䨪�஢����� �窨);              
							// (�ᯮ������ ⮫쪮 � ०��� ���-2)
}	CADR_RLI_t;

							//����� "��ப� ����"
typedef struct 
{
	int		num_string;			// ����� ��ப� � ����, int; 1-400
	unsigned short	pix[200];	// ���ᨢ �મ�⥩ ���ᥫ��, unsigned short [200]:
								// �મ��� ��ࢮ� ���� ���ᥫ��, unsigned short;
								// ������ 0-7:  ���ᥫ� � ����訬 ����஬
								//		   8-15: ���ᥫ� � ����訬 ����஬
								//         ................................
								// �મ��� 200-�� ���� ���ᥫ��, unsigned short;
} string_CADR_t;

								//०��� "楫������ ��� ��" � "楫������ ��� ��"

typedef struct 
{
	unsigned short	cr_RLI;		//����� ����� RLI
	FORM_VK_t		FORM_VK;	//����� "���⥫�"
	CADR_RLI_t		CADR_RLI;	//����� "���� ���"
	string_CADR_t	string_CADR[400];	//400 ��ப ����

}	FORM_RLI_t;  

//////////////////////////////////////////////////////////////////////////
///// ������ 2 ��� 3 /////
//////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 ���� (������ ��������)
	short	SVCH_FORM_2[4];		//8 ���� (������ ��)
	short	SVCH_FORM_3[80];	//(20 ����) * 8 䮬��஢ (������ ��)

	short	null_bytes[519];	//620 - 101 = 519

} Mem_Region23_NO_t;	//202 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];	//18 ���� (������ ��������)
	short	SVCH_FORM_4[88];	//(22 ����) * 8 䮬��஢ (������ ���)

	short	null_bytes[515];	//620 - 105 = 515

} Mem_Region23_REO_t;	//210 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 ���� (������ ��������)
	short	SVCH_FORM_3[10];	//20 ���� (������ ��)

	short	null_bytes[594];	//620 - 26 = 594

} Mem_Region23_CpNC_t;	//52 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];	//18 ���� (������ ��������)
	short	SVCH_FORM_4[11];	//22 ���� (������ ���)

	short	null_bytes[593];	//620 - 27 = 593

} Mem_Region23_CpRES_t;	//54 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 ���� (������ ��������)
	short	SVCH_FORM_2[4];		//8 ���� (������ ��)

	short	null_bytes[600];	//620 - 20 = 600

} Mem_Region23_VZ_t;	//40 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short cr_transm_takt;
	unsigned short num_words;

	short	SVCH_FORM_5[5];
	short	SVCH_FORM_6[606];


} Mem_Region23_RLI_t;	//1240 �.���.

typedef	union {
	short buf[620];

	Mem_Region23_NO_t 		Mem_Region_NO;		//�ᢥ饭�� ��	(kvi = 5)
	Mem_Region23_REO_t 		Mem_Region_REO;		//�ᢥ饭�� ���	(kvi = 7)
	Mem_Region23_CpNC_t 	Mem_Region_CpNC;	//��������� ��	(kvi = 6)
	Mem_Region23_CpRES_t 	Mem_Region_CpRES;	//��������� ���	(kvi = 8)
	Mem_Region23_VZ_t 		Mem_Region_VZ;		//����������⢨�	(kvi = 2)
	Mem_Region23_RLI_t 		Mem_Region_RLI;		//����� ���			(kvi = 9)

}Mem_Region23_t;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///// ������ 4 /////
//////////////////////////////////////////////////////////////////////////
//��������� ��⮪���: ��� - ��� �� (pdn 08.04.2016)
typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 ���� (������ ��������)
	short	SVCH_FORM_2[4];		//8 ���� (������ ��)
	short	SVCH_FORM_3[40];	//(20 ����) * 4 䮬��஢ (������ ��)

} Mem_Region4_NO_t;	//122 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];
	unsigned short num_words;

	short	SVCH_FORM_1[9];		//18 ���� (������ ��������)
	short	SVCH_FORM_4[44];	//(22 ����) * 4 䮬��஢ (������ ���)

} Mem_Region4_REO_t;	//122 �.���.

typedef struct {
	unsigned short cr_data_pac;
	short	SVCH_FORM_SACH[6];

	short	SVCH_FORM_1[9];		//18 ���� (������ ��������)
	short	SVCH_FORM_2[4];		//8 ���� (������ ��)

	short	null_bytes[41];	//122 - 40 = 82

} Mem_Region4_VZ_t;	//40 �.���.

//////////////////////////////////
/*
typedef struct {
	unsigned short cr_p999;
	short	P999_FORM_SACH[6];
	unsigned short num_words;

	short	P999_FORM_1[9];			//���� � ������ ����� ᠬ����
	short	P999_FORM_2_DMV[3];		//�����2, ��
	short	P999_FORM_3_DMV[48];	//24���� * 4 �� (����� 6, ��ࠬ���� ��)

	short	null_bytes[31];	//97 - 68 = 31

} Mem_Region4_NO_t;		//136 �.���.

typedef struct {
	unsigned short cr_p999;
	short	P999_FORM_SACH[6];
	unsigned short num_words;

	short	P999_FORM_1[9];			//���� � ������ ����� ᠬ����
	short	P999_FORM_4_DMV[80];	//40���� * 4 �� (����� 6, ��ࠬ���� ���)

} Mem_Region4_REO_t;	//194 �.���.

typedef struct {
	unsigned short cr_p999;
	short	P999_FORM_SACH[6];

	short	P999_FORM_1_DMV[8];			//���� � ������ ����� ����

	short	null_bytes[82];	//97 - 15 = 82

} Mem_Region4_VZ_t;		//30 �.���.
*/
typedef union{
//	short buf[97];
//	Mem_Region4_NO_t 	Mem_Region_NO;		//�ᢥ饭�� ��		(kvi = 5)
//	Mem_Region4_REO_t 	Mem_Region_REO;		//�ᢥ饭�� ���		(kvi = 7)
//	Mem_Region4_VZ_t 	Mem_Region_VZ;		//����������⢨�	(kvi = 4)
	short buf[61];	//��������� ��⮪���: ��� - ��� �� (pdn 08.04.2016)
	Mem_Region4_NO_t 	Mem_Region_NO;		//�ᢥ饭�� ��		(kvi = 5)
	Mem_Region4_REO_t 	Mem_Region_REO;		//�ᢥ饭�� ���		(kvi = 7)
	Mem_Region4_VZ_t 	Mem_Region_VZ;		//����������⢨�	(kvi = 4)

} Mem_Region4_t;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///// �������� ������ /////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct	{
	unsigned short	cr_com;	//���浪��� ����� ��᫥���� �믮������� �������  
							//0-USHRT_MAX
	short	num_com;		//����� ��᫥����� ������� �� �����
	int		lp2_param;		//���祭�� ��ࠬ��� ��᫥���� ������� �� ��2

	short			kzv;	//��� �����襭�� ��᫥���� ������� (0 - ��ଠ, 1 - �� ��ଠ(�訡��), 2 - ������� �⬥����)
	unsigned int	k_o;	//��� �訡�� ��᫥���� �������
	short			krk;	//��� १���� �㭪樮���쭮�� ����஫� (��) (0 - ��ଠ, 1 - �� ��ଠ)
	short			kvk;	//��� �믮������ ������ ����������⢨� � �� (���) (0 - ��ଠ, 1 - �� ��ଠ, 2 - ��� ��⠭������, 3 - ��४����� �ࠪ� �� �ਥ�, 5 - ०�� ��⠭�����, 7 - ������� �믮�����, 8 - ��� ��⠭������)

	unsigned int word_sost_1;
	unsigned int word_sost_2;
	unsigned int word_sost_3;
	unsigned int word_sost_4;
	unsigned int word_sost_5;
	unsigned int word_sost_6;
	unsigned int word_sost_7;
	unsigned int word_sost_8;
	unsigned int word_sost_9;
	unsigned int word_sost_SPIAK;
	unsigned int word_sost_P999;

	Mem_Region23_t Mem_Region2;
	Mem_Region4_t Mem_Region4;

} obmen_MO3A_MN3_t;


typedef struct	{
	unsigned short	cr_com;	//���浪��� ����� ��᫥���� �������, �뤠���� �� ��.��3 � ��.��3� 
							//0-USHRT_MAX

	short num_com;		//����� ��᫥����� ������� �� �����
	int	 a_params[5];	//���ᨢ ��ࠬ��஢ ������� �ࠢ�����

} obmen_MN3_MO3A_t;



//>>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>


//>>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>
//==========================================================================
//����� ����묨 ����� �ਡ�ࠬ� ��3, �� � ��3 �뭥ᥭ � TYPE.h 
//==========================================================================
