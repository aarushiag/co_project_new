#include <stdio.h>

#include <stdio.h>

static unsigned long int MEM[1000];
static unsigned int address;
static unsigned int instruction;
//stores the address and instruction of the current line being read from file
//used in Fetch function and ReadFromFile function
static unsigned int current_address;
static unsigned int PC=0;
static unsigned int current_instruction;
static unsigned int Condition;
static unsigned int Flag;
static unsigned int Immediate;
static unsigned int Opcode;
static unsigned int Operand1;
static unsigned int Operand2;
static unsigned int Destination;
static int register[15];

void ReadFromFile() {
	FILE *fp;
	fp=fopen("Input.txt","r");
	
	if(fp == NULL) {
		printf("Error opening file for writing\n");
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
	printf("%s %x %s %x \n","Fetching instruction ",current_instruction," from address ",current_address);
	PC+=4;
}


void ReadInstruction() {
	//printf("%x",current_instruction);
	Condition = (current_instruction >> 28) & (0b1111);
	printf("%d \n",Condition);
	Flag = (current_instruction >> 26) & (0b0011);
	printf("%d \n",Flag);
}

void Decode() {
	//current_instruction= 0xE3A0200A;
	ReadInstruction();
	
}
void Add(){
	if (Immediate==0)register[Destination]=register[Operand1]+register[Operand2];
	else register[Destination]=register[Operand1]+Operand2;
}	
void Sub(){
	if (Immediate==0)register[Destination]=register[Operand1]-register[Operand2];
	else register[Destination]=register[Operand1]-Operand2;
}

void main() {
	ReadFromFile();
	Fetch();
	decode();
	
}
