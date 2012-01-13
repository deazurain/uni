#include <stdio.h>

FILE* fout;

FILE * DBG_init(){
  if(!fout)
  	fout = fopen("dbg.txt", "w");
  return fout;
}

void DBG_cleanup(){
  fclose(fout);
}



