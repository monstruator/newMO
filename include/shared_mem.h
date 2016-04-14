 #include "headers.h"
 #include "obmen_VS.h"
 #define MAX_SHMEM_COUNT 20

#define  SHMEM_NAME  "MO3Av1.1"   
#define  SHMEM_t  SHMEM_MO3A

//#define CVM10
//#define CVM11

SHMEM_MO3A *p;      

int	create_shmem ( void )
	{
	int 	i1;
	int		result;
	
	shm_unlink ( SHMEM_NAME );			// Закрытие ранее созданного ОПП

	i1 = shm_open ( SHMEM_NAME, O_RDWR | O_CREAT, 0777 );
	if ( i1 == -1 )
		{
		printf ("error shm_open ( %s, O_RDWR | O_CREAT, 0777 ) = %s \n", SHMEM_NAME, strerror(errno));
		return ( -1 );				// Аварийный выход
		}

	result = ltrunc ( i1, sizeof(SHMEM_t), SEEK_SET );			// усечение ОПП
	if ( result == -1 )
		{
		printf ("error ltrunc ( i1, %d, SEEK_SET ) = %s \n", sizeof(SHMEM_t), strerror(errno));
		return ( -2 );				// Аварийный выход
		}
		
	p = (SHMEM_t*) mmap ( 0, sizeof(SHMEM_t), PROT_READ|PROT_WRITE, MAP_SHARED, i1, 0);
	if ( p == NULL )
		{
		printf ("error mmap ( 0, %d, PROT_READ|PROT_WRITE, MAP_SHARED, i1, 0 ) = %s\n", sizeof(SHMEM_t), strerror(errno));
		return ( -3 );				// Аварийный выход
		}
	return ( 0 );					// Корректный выход
	}

int	open_shmem ( void )
	{
	int				i1 = -1;
	unsigned long	countS = 0;

	while (( i1 == -1 ) && ( countS < MAX_SHMEM_COUNT ))
		{
		i1 = shm_open ( SHMEM_NAME, O_RDWR, 0777 );
		if ( i1 == -1 )
			{ 
			printf ("errno shm_open( %s, O_RDWR, 0777 ) = %s, count = %d \n", SHMEM_NAME, strerror(errno), countS );
			delay ( 200 );
			countS++;
			}
		}
		
	if ( countS >= MAX_SHMEM_COUNT )
		{
		printf ("errno shm_open( %s, O_RDWR, 0777 ) = %s\n", SHMEM_NAME, strerror(errno));
		return ( - 1 );				// Аварийный выход
		}

	p = (SHMEM_t*) mmap ( 0, sizeof(SHMEM_t), PROT_READ|PROT_WRITE, MAP_SHARED, i1, 0);
	if ( p == NULL )
		{
		printf ("errno mmap ( 0, %d, PROT_READ|PROT_WRITE, MAP_SHARED, i1, 0 ) = %s\n", sizeof(SHMEM_t), strerror(errno));
		return ( -2 );				// Аварийный выход
		}
	return ( 0 );					// Корректный выход
	}
	

void ResetCom ()
{
	int i;
	for(i=0;i<10;i++)    memset( (char *)&p->work_com[i], 0, sizeof(c_UPR) );
	//for(i=0;i<10;i++)    p->k_step[i]=p->g_step[i]=0;
	p->kol_step=p->cur_step=0;
}