#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "../qsys_headers/hps_0.h"


#define LW_AXI_BASE 0xFF200000 //ARM LW ADDR BASE
#define LW_AXI_SPAN 0x00200000 //2 MB SIZE

void* virtual_base;
void* led_addr;
void* sw_addr;

int fd;
int switches;

int main (){
  fd=open("/dev/mem",(O_RDWR|O_SYNC));
  virtual_base = mmap(NULL,LW_AXI_SPAN,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,LW_AXI_BASE);
  sw_addr = virtual_base + SW_BASE; //defined in hps_0.h
  led_addr = virtual_base + LED_BASE; //defined in hps_0.h

  while(1){
    switches=*(uint32_t *)sw_addr;
    *(uint32_t *)led_addr=switches;
    usleep(1000000);
    printf("%u\n",switches);


  }

return 0;
}
