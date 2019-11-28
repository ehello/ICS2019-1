#include "nemu.h"
#include <stdlib.h>
#include <time.h>

const char *regsl[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
const char *regsw[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
const char *regsb[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};

void reg_test() {
  srand(time(0));
  uint32_t sample[8];
  uint32_t pc_sample = rand();
  cpu.pc = pc_sample;

  int i;
  for (i = R_EAX; i <= R_EDI; i ++) {
    sample[i] = rand();
    reg_l(i) = sample[i];
    assert(reg_w(i) == (sample[i] & 0xffff));
  }

  assert(reg_b(R_AL) == (sample[R_EAX] & 0xff));
  assert(reg_b(R_AH) == ((sample[R_EAX] >> 8) & 0xff));
  assert(reg_b(R_BL) == (sample[R_EBX] & 0xff));
  assert(reg_b(R_BH) == ((sample[R_EBX] >> 8) & 0xff));
  assert(reg_b(R_CL) == (sample[R_ECX] & 0xff));
  assert(reg_b(R_CH) == ((sample[R_ECX] >> 8) & 0xff));
  assert(reg_b(R_DL) == (sample[R_EDX] & 0xff));
  assert(reg_b(R_DH) == ((sample[R_EDX] >> 8) & 0xff));

  assert(sample[R_EAX] == cpu.eax);
  assert(sample[R_ECX] == cpu.ecx);
  assert(sample[R_EDX] == cpu.edx);
  assert(sample[R_EBX] == cpu.ebx);
  assert(sample[R_ESP] == cpu.esp);
  assert(sample[R_EBP] == cpu.ebp);
  assert(sample[R_ESI] == cpu.esi);
  assert(sample[R_EDI] == cpu.edi);

  assert(pc_sample == cpu.pc);
}

void isa_reg_display() {
	printf("%-8s0x%08x %d\n","%eax:",cpu.eax,cpu.eax);
	printf("%-8s0x%08x %d\n","%ecx:",cpu.ecx,cpu.ecx);
	printf("%-8s0x%08x %d\n","%edx:",cpu.edx,cpu.edx);
	printf("%-8s0x%08x %d\n","%ebx:",cpu.ebx,cpu.ebx);
	printf("%-8s0x%08x %d\n","%esp:",cpu.esp,cpu.esp);
	printf("%-8s0x%08x %d\n","%ebp:",cpu.ebp,cpu.ebp);
	printf("%-8s0x%08x %d\n","%esi:",cpu.esi,cpu.esi);
	printf("%-8s0x%08x %d\n","%edi:",cpu.edi,cpu.edi);
}

uint32_t isa_reg_str2val(const char *s, bool *success) {
	int i,l=strlen(s);
	*success = true;
	char tmp[10]="";strcpy(tmp,s);
	for(i=0;i<l;i++) tmp[i]=tolower(s[i]);
	if(strcmp(tmp,"pc")==0) return cpu.pc;
	else if(strcmp(tmp,"cf")==0) return cpu.eflags.CF; 
	else if(strcmp(tmp,"zf")==0) return cpu.eflags.ZF;
	else if(strcmp(tmp,"of")==0) return cpu.eflags.OF;
	else if(strcmp(tmp,"sf")==0) return cpu.eflags.SF;
	else if(strcmp(tmp,"if")==0) return cpu.eflags.IF;
	for(i=0;i<8;i++){
		if(strcmp(tmp,reg_name(i,1))==0) return reg_b(i);
		if(strcmp(tmp,reg_name(i,2))==0) return reg_w(i);
		if(strcmp(tmp,reg_name(i,4))==0) return reg_l(i);
	}	
	*success = false;
	return 0;
}