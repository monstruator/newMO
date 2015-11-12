#include <fcntl.h>
#include <stdlib.h>
#include <conio.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/pci.h>
#include <sys/osinfo.h>
#include <i86.h>
#include "ca91c042.h"

#define MAX_DEV 30
#define MAX_BUS 4
#define SAME_DEV 4
#define NUM_ADR_REG 6
#define VENDOR_ID 0x13FE

char Class[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xa,0xb,0xc,
			  0xd,0xe,0xf,0x10,0x11,0xFF};
char Sub_class[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
				0x10,0x20,0x30,0x40,0x80};
char Interface[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x10,0x20,0x40,0x80,
				0xFE}; 
struct conf_pci {long Class_Code;
unsigned short  Vendor_ID;
unsigned short  Device_ID;
unsigned devfuncnum, busnum;
long address[6];
char interrupt_line;
};
long mass[256];
unsigned short mass1[256];
int find_pci() {
unsigned version=0,bus=MAX_BUS;
unsigned hardware;
//Нахождение устройств PCI и определение номера шины и версии PCI
	if (_CA_PCI_BIOS_Present(&bus, &version, &hardware) == PCI_SUCCESS){
	printf ("PCI_BUS %x Version %x\n",bus,version);
	return (PCI_BIOS_PRESENT);
	}
	return (0);
	} 

//Определение базового адреса модуля по коду устройства и коду производителя

long get_base_adrDV(unsigned short  Device_ID, long Vendor_ID, int m,long *addr) {
struct conf_pci my_device;
int look,prizn=0;
	printf("%x %x\n",Device_ID, Vendor_ID);
	if (_CA_PCI_Find_Device(Device_ID,VENDOR_ID,m,&my_device.busnum,&my_device.devfuncnum) != PCI_SUCCESS)
	{printf("NO\n");return(0);} 
	else printf ("Найдено уст-во от поставщика %X PCI index %d\n",Vendor_ID,m);

	look=_CA_PCI_Read_Config_DWord(my_device.busnum,my_device.devfuncnum,
					offsetof(struct _pci_config_regs,Base_Address_Regs[0]),
						NUM_ADR_REG,(char *)&my_device.address);
	if (look != PCI_SUCCESS)
	{printf ("Не считывается базовый адрес\n"); 
	return (0); 	
	}
	for (m=0;m<NUM_ADR_REG; m++){  
if (my_device.address[m] && PCI_IS_IO(my_device.address[m]))
	{
	printf ("Базовый адрес %x\n",PCI_IO_ADDR(my_device.address[m]));
	*(addr+prizn)=PCI_IO_ADDR(my_device.address[m]); 
//Определение длины адресного пространства порта
/*
printf ("Длина адресного пространства %d\n",PCI_IS_MMAP20(my_device.address[m]));	
printf ("Длина адресного пространства %d\n",PCI_IS_MMAP32(my_device.address[m]));	
printf ("Длина адресного пространства %d\n",PCI_IS_MMAP64(my_device.address[m]));	
*/
	prizn++;
	} else				
	if (PCI_IS_MEM(my_device.address[m]))
	printf ("Область памяти %x\n",PCI_MEM_ADDR(my_device.address[m]));
								}
	return (prizn);
	}


//Определение линии прерывания модуля по коду устройства и коду производителя
	
int get_irqDV(unsigned short  Device_ID, long Vendor_ID , int m) {
struct conf_pci my_device;
int look=0,prizn=0;
	if (_CA_PCI_Find_Device(Device_ID,VENDOR_ID,m,&my_device.busnum,&my_device.devfuncnum) != PCI_SUCCESS)
	return(0); 
	else printf ("Найдено уст-во от поставщика %X PCI index %d \n",Vendor_ID,m);
	if ((_CA_PCI_Read_Config_Word(my_device.busnum,my_device.devfuncnum,
	offsetof(struct _pci_config_regs,Device_ID),1,(char *)&my_device.Device_ID) 
	== PCI_SUCCESS) && (my_device.Device_ID == Device_ID))
	printf ("Найдено уст-во типа % X\n",my_device.Device_ID);else 
	{printf("Нет устройств типа %X\n",Device_ID);
	return(0);} 
	look=_CA_PCI_Read_Config_Byte(my_device.busnum,my_device.devfuncnum,
					offsetof(struct _pci_config_regs,Interrupt_Line),
					  1,(char *)&my_device.interrupt_line);
	if (look == PCI_SUCCESS) return (my_device.interrupt_line); 
	else return (0);
	}


new_func_read(unsigned short dev_id, long ven_id, struct conf_pci *my_device,int offset,int ind){
int i;
if (_CA_PCI_Find_Device(dev_id,ven_id,ind,
	&my_device->busnum,&my_device->devfuncnum)!=PCI_SUCCESS) return (-1);

i=_CA_PCI_Read_Config_DWord(my_device->busnum,my_device->devfuncnum,offset,1,(char *)&mass[offset]);
printf("offset %8x value %08x\n",offset,mass[offset]);
return i;
					  }
new_func_read_W(unsigned short dev_id, long ven_id, struct conf_pci *my_device,int offset,int ind){
int i;
if (_CA_PCI_Find_Device(dev_id,ven_id,ind,
	&my_device->busnum,&my_device->devfuncnum)!=PCI_SUCCESS) return (-1);

i=_CA_PCI_Read_Config_Word(my_device->busnum,my_device->devfuncnum,offset,1,(char *)&mass1[offset]);
printf("offset %8x value %04x\n",offset,mass1[offset]);
return i;
					  }

new_func_write(unsigned short dev_id, long ven_id, 
		struct conf_pci *my_device,int offset,long *inf){
int i;

if (_CA_PCI_Find_Device(dev_id,ven_id,0,
	&my_device->busnum,&my_device->devfuncnum)!=PCI_SUCCESS) return (0);

i=_CA_PCI_Write_Config_DWord(my_device->busnum,my_device->devfuncnum,offset,1,(char *)inf);
return i;
}