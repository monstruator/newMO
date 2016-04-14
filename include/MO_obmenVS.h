///// Структуры обмена пр.5М и станции МО3А 						/////

//==========================================================================
//обмен данными между приборами  5м  и mo3  
//
//#define 	SUM_FORM_SVCH		100  //определено в MN3_TYPE.h

typedef struct 
{

	int		time_send;		// Время суток посылки формуляра с ВК, с, int;
	short	num_bort;		// Бортовой номер вертолета (1-999), short;
	short	num_VK;			// Номер вертолета в группе, short (1-4);
	short	rejim_fly;		// Режим полета ВК, short;
					 	    //	(0-маршрут (движение к очередному ППМ), 
						    //	1-пролет ТР (движение в зоне ответственности ППМ), 
      						//	2-выход из ТР (движение вне зоны ответственности ППМ), 
      						//	3-возврат на базу);
	short	KPC;			// Режим работы с КПЦ, short; (1-ТКИ, 2-РЛИ);
	short	tip_AK;			// Тип АК, short; (0-ВК, 1-СК);
	short	work_VK;		// Режим работы ВК, short; (0-"Освещение НО", 1-"Освещение РЭО");
	short	work_PNK;		// Режим работы ПНК, short; (0-СНС, 1-ДИСС, 2-курсовоздушный, 
							//   3-отказ ПНК);
	int		time_VK;		// Время суток определения координат и параметров движения ВК, с, int;
	float	Xvk;			// Координаты Хвк, м, float (отн центра ТР);
	float	Yvk;			// Координаты Yвк, м, float (отн центра ТР);
	float	Kvk;			// Курс ВК, рад, float;
	float	Vvk;			// Скорость ВК, м/с, float;
	float	Hvk;			// Высота полета Нвк, м, float;
	float	SKOvk;			// Круговая СКО места ВК, м, float;
	float	fi_TR;			// Широта центра ТР, рад, float;
	float	la_TR;			// Долгота центра ТР, рад, float;
						    //   ВК формирует информацию о координатах своего местоположения в 
							//   прямоугольной системе координат ТР, в которой начало координат 
							//   совмещено с точкой центра ТР, ось Х направлена на север, ось Y - на 
							//   восток.
}	FORM_VK_t; 
								//формуляр  "Паспорт НЦ" 
typedef struct 
{
	int		time_send;      // Время суток посылки формуляра с ВК, с, int;
	short	num_VK;			// Номер цели в нумерации ВК (в ИП средств РЛС ВК), short, (1-100);
	short	tip_NC;			// Тип цели, short; (0-не определен, 1-большая НЦ, 2-малая НЦ, 
							//   3-РЭС, 4-КПЦ);
							//   Тип цели РЭС означает, что на одном из 10-ти секундных циклов 
							//   наблюдения средствами РТР ВК для этой цели были определены 
							//   радиотехнические параметры;
	short	P_GO;			// Признак ГП, short; (0-не определен, 1-свой, 2-чужой);
	short	P_KV;			// Признак ПД (параметров движения), short; 
							//   (0-курс и скорость не определены, 
							//   1-курс и скорость определены);
	short	P_PS;			// Признак ПС (потери сопровождения), short;
					//   (1-на последнем 10-ти секундном цикле наблюдения контакта с целью не 
					//   было, в этом случае ее местоположение экстраполируется на момент 
					//   посылки паспорта с ВК, а параметры движения соответствуют моменту
					//   последнего контакта с целью;
					//   0-на последнем 10-ти секундном цикле наблюдения контакт с целью был,
					//  в этом случае ее местоположение и параметры движения соответствуют
					//   моменту последнего контакта с целью);
	int		time_NC;      	// Время суток последнего контакта с целью, с, int;
	float	Xnc;			// Координата Хнц, м, float (отн центра ТР);
	float	Ync;			// Координата Yнц, м, float (отн центра ТР);
	float	SKO_X;			// СКО цели по Х, м, float;
	float	SKO_Y;			// СКО цели по Y, м, float;
							//   Данные по СКО цели учитывают только ошибки по определению координат 
							//   цели в РЛС ВК, без учета ошибок ПНК.
	float	Knc;			// Курс цели, рад, float;
	float	Vnc;			// Скорость цели, м/с, float;
	float	Dnc_nakl;			// Наклонная дальность до цели, м, float (отн ВК);
	float	Pnc;			// Пеленг цели, рад, float (отн ВК);
					//   Для целей с признаком ПС=0 наклонная дальность и пеленг указываются 
					//   на момент последнего контакта с целью; для целей  с признаком ПС=1 
					//   в качестве наклонной дальности и пеленга цели указываются значения,
					//  экстраполированные на момент посылки формуляра с ВК.

}	FORM_PSP_NC_t; 
								//формуляр  "Паспорт РЭС" 
typedef struct 
{
	int	    time_send;		// Время суток посылки формуляра с ВК, с, int;
	short	num_VK;			// Номер цели в нумерации ВК (в ИП средств РТР ВК), short, (1-100);
	short	tip_RES;		// Номер типа РЭС по каталогу ВК, short;
	short	SIGN;			// Вид излучения РЭС, short; (1-имп, 2-непрерывный, 3-квазинепрерывный);
	short	P_IZL;	 		// Мощность излучения РЭС, дБ, short;
	float	T_i;			// Период повторения сигналов РЭС, мкс, float;
	float	tau_i;			// Длительность импульса РЭС, мс, float;
	float	T_OBL;			// Период облучения, с, float;
	float	tau_P;			// Длительность пачки импульсов РЭС, мс, float;
			      //   В качестве значений радиотехнических параметров указываются значения,
			      //   полученные во время последнего контакта с РЭС средствами РТР ВК.
	int	    time_RES;		// Время суток последнего контакта с РЭС, с, int;
	float	Dres_nakl;      // Наклонная дальность РЭС, м, float; (отн ВК);
	float	Pres;			// Пеленг РЭС, рад, float; (отн ВК);
			      //   Пеленг и наклонная дальность цели указываются на момент последнего 
			      //   контакта с РЭС (напомним, что контакт с РЭС возможен только при 
			      //   наличии радиолокационного контакта).

}	FORM_PSP_RES_t; 
								//формуляр  канала свч
typedef struct 
{
	FORM_VK_t		FORM_VK; 
	unsigned short	cr_PSP_NC;	//номер пакета PSP_NC
	unsigned short	cr_PSP_RES;	//номер пакета PSP_RES
	FORM_PSP_NC_t	FORM_PSP_NC[SUM_FORM_SVCH]; 
	FORM_PSP_RES_t	FORM_PSP_RES[SUM_FORM_SVCH]; 

}	FORM_SVCH_t; 
								//обмен  мо3 -> мн3  (формуляры целей)
typedef struct 
{
	FORM_SVCH_t	FORM_SVCH1; 
	FORM_SVCH_t	FORM_DMV; 

}	FORM_MO_MN_t;  

								//формуляр "кадр РЛИ"
typedef struct 
{
	int	    time_send;		// Время суток посылки формуляра с ВК, с, int;
	int	    time_cadr;		// Время суток формирования кадра, с, int;
	float	X;				// Координата X центра кадра, м, float (отн центра ТР);
	float	Y;				// Координата Y центра кадра, м, float (отн центра ТР);
	short	pr_IRLI;		// Признак вида РЛИ, short (0-РЛИ1, 1-РЛИ2);
	short	scale;      	// Признак шкалы, short (1-260 км, 2-130 км, 3-65 км, 4-32 км);
							// (используется только в режиме РЛИ-1)
	int		num_NC;			// Номер НЦ, int (0 - для фиксированной точки);              
							// (используется только в режиме РЛИ-2)
}	CADR_RLI_t;

							//формуляр "Строка кадра"
typedef struct 
{
	int		num_string;			// Номер строки в кадре, int; 1-400
	unsigned short	pix[200];	// Массив яркостей пикселей, unsigned short [200]:
								// Яркость первой пары пикселей, unsigned short;
								// Разряды 0-7:  пиксель с большим номером
								//		   8-15: пиксель с меньшим номером
								//         ................................
								// Яркость 200-ой пары пикселей, unsigned short;
} string_CADR_t;

								//режимы "целепоказ РЛИ НО" и "целепоказ РЛИ НЦ"

typedef struct 
{
	unsigned short	cr_RLI;		//номер пакета RLI
	FORM_VK_t		FORM_VK;	//формуляр "носитель"
	CADR_RLI_t		CADR_RLI;	//формуляр "кадр РЛИ"
	string_CADR_t	string_CADR[400];	//400 строк кадра

}	FORM_RLI_t;  

//////////////////////////////////////////////////////////////////////////
///// РЕГИОН 2 или 3 /////
//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///// РЕГИОН 4 /////
//////////////////////////////////////////////////////////////////////////
//Изменение протокола: дмв - как свч (pdn 08.04.2016)
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

//////////////////////////////////
/*
typedef struct {
	unsigned short cr_p999;
	short	P999_FORM_SACH[6];
	unsigned short num_words;

	short	P999_FORM_1[9];			//коорд и полетные данные самолета
	short	P999_FORM_2_DMV[3];		//формуляр2, ТР
	short	P999_FORM_3_DMV[48];	//24байт * 4 форм (формуляр 6, параметры НЦ)

	short	null_bytes[31];	//97 - 68 = 31

} Mem_Region4_NO_t;		//136 б.инф.

typedef struct {
	unsigned short cr_p999;
	short	P999_FORM_SACH[6];
	unsigned short num_words;

	short	P999_FORM_1[9];			//коорд и полетные данные самолета
	short	P999_FORM_4_DMV[80];	//40байт * 4 форм (формуляр 6, параметры РЭС)

} Mem_Region4_REO_t;	//194 б.инф.

typedef struct {
	unsigned short cr_p999;
	short	P999_FORM_SACH[6];

	short	P999_FORM_1_DMV[8];			//коорд и полетные данные АКРЦ

	short	null_bytes[82];	//97 - 15 = 82

} Mem_Region4_VZ_t;		//30 б.инф.
*/
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

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///// Структуры обмена /////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct	{
	unsigned short	cr_com;	//порядковый номер последней выполненной команды  
							//0-USHRT_MAX
	short	num_com;		//номер последеней команды по перечню
	int		lp2_param;		//значение параметра последней команды от лп2

	short			kzv;	//код завершения последней команды (0 - норма, 1 - не норма(ошибка), 2 - команда отменена)
	unsigned int	k_o;	//код ошибки последней команды
	short			krk;	//код результата функционального контроля (крк) (0 - норма, 1 - не норма)
	short			kvk;	//код выполнения команд взаимодействия с АК (квк) (0 - норма, 1 - не норма, 2 - связь установлена, 3 - переключить тракт на прием, 5 - режим установлен, 7 - команда выполнена, 8 - связь установлена)

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
	unsigned short	cr_com;	//порядковый номер последней команды, выданной из пр.мн3 в пр.мо3а 
							//0-USHRT_MAX

	short num_com;		//номер последеней команды по перечню
	int	 a_params[5];	//массив параметров команды управления

} obmen_MN3_MO3A_t;



//>>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>


//>>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>  >>>
//==========================================================================
//обмен данными между приборами му3, ме и мн3 вынесен в TYPE.h 
//==========================================================================
