#include <stdio.h>

static unsigned long int MEM[1000];
static unsigned int address[1000];
static unsigned int instruction[1000];
//stores the address and instruction of the current line being read from file
//used in Fetch function and ReadFromFile function
static unsigned int current_address,current_instruction;
int PC=0;
int flag=0;


void ReadFromFile() {
	FILE *fp;
	fp=fopen("Input.txt","r");
	
	if(fp == NULL) {
		printf("Error opening file for writing\n");
		flag=-1;
		return;
  }
	int ct=0;
	while(fscanf(fp,"%x %x",&address,&instruction)!=EOF){
		printf("%x",address);
		printf("%x",instruction);
		MEM[address]=instruction;
	}
	
	fclose(fp);
}

void Fetch() {
	current_address=PC;
	current_instruction=MEM[PC];
	PC+=4;
}
	
void main() {
	printf("Hello");
	ReadFromFile();
	int ct=0;
	if (flag==0){
	while(ct<4){
		//Fetch();
		ct++;
	}
	}
}
