#include <stdio.h>
#include <sys/stat.h>
void binaryPrint(int mode);

int main(){
  struct stat sb;
  stat("makefile",&sb);
  printf("%d B\n",sb.st_size);

  int mode = sb.st_mode;
  int killer = 256+128+64+32+16+8+4+2+1;
  mode = killer & mode;
  binaryPrint(mode);
  printf("\n");

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
  printf("%s",permissions);
}