#ifndef REMOTE_STUFF_H_
#define REMOTE_STUFF_H_

int f_sig = 31; //red forward
int b_sig = 33; //black back
int r_sig = 35; //white right
int l_sig = 39; //yellow  left

const int NUMSIGS = 4;

int sigs[NUMSIGS] = {f_sig,b_sig,r_sig,l_sig};

void start_remote(){
  for (int i = 0; i < NUMSIGS; i++){
    pinMode(sigs[i],INPUT);
  }
}



#endif
