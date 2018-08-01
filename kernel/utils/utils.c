#include "utils.h"

void memset(char* ptr, char value, int size){
  int i = 0;
  for(; i < size; i++){
    ptr[i] = value;
  }
}

void memcpy(char* src, char* dest, int size){
  int i;
  for(i = 0; i < size; i++){
    dest[i] = src[i];
  }
}
