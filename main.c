#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include "header.h"

int main(){
  struct stat sb;
  if(stat("makefile",&sb)==-1){
    printf("%s",strerror(errno));
    return 0;
  }
  int mode = sb.st_mode;
  int killer = 256+128+64+32+16+8+4+2+1;
  mode = killer & mode;

  printf("Investigating the metadata of makefile\n");
  printf("The file size in bytes is %ld B\n",sb.st_size);
  printf("The file size in kilobytes is %f KB\n",sb.st_size/1024.0);
  printf("The file size in megabytes is %f MB\n",sb.st_size/1024.0/1024.0);
  printf("The file size in gigabytes is %f GB\n",sb.st_size/1024.0/1024.0/1024.0);
  binaryPrint(mode);
  printf("The last time the file was accessed was at: %s\n", ctime(& (sb.st_atime)));


}
void binaryPrint(int mode){
  int i;
  char permissions [10];
  for(i=8;i>=0;i--){
    switch(mode%2){
      case 0:
        permissions[i] = '-';
        break;
      case 1:
        switch(i%3){
          case 0:
            permissions[i] = 'r';
            break;
          case 1:
            permissions[i] = 'w';
            break;
          case 2:
            permissions[i] = 'x';
            break;
        }
    }
    mode = mode>>1;
  }
  permissions[9] = 0;
  printf("The file permissions are: %s\n", permissions);
}
