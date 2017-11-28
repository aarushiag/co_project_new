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
static unsigned int Offset;
static unsigned int Operand1;
static unsigned int Operand2;
static unsigned int Destination;
static unsigned int R[16];

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
	printf("%s %x %s %x \n","FETCH: Fetching instruction ",current_instruction," from address ",current_address);
	PC+=4;
}

void ReadInstruction() {
	//printf("%x",current_instruction);
	Condition = (current_instruction >> 28) & (0b1111);
	printf("%d \n",Condition);
	Flag = (current_instruction >> 26) & (0b0011);
	printf("%d \n",Flag);

    if(Flag==0)
    {
        Immediate=(current_instruction >> 25)& (0b0001);
        Opcode=(current_instruction >> 21)& (0b1111);
        Operand1=(current_instruction >> 16)& (0b1111);
        Destination=(current_instruction >> 12)& (0b1111);

        if(Immediate==0)
        {
            Operand2=(current_instruction)& (0b1111);
        }

        else if(Immediate==1)
        {
            Operand2=(current_instruction)& (0b11111111);
        }
    }

    else if(Flag==1)
    {
        Opcode=(current_instruction >> 20)& (0b00111111);
        Operand1 = ((current_instruction>>16)&(0b1111));
        Operand2 = ((current_instruction)&(0b111111111111));
        Destination = ((current_instruction>>12)&(0x1111));
    }

    else if (Flag==2)
    {
        Opcode = ((current_instruction>>24) & (0b0011));
        Offset = (current_instruction & (0b111111111111111111111111));
    }

}


void Decode() {
	//current_instruction= 0xE3A0200A;
	ReadInstruction();
	if(Flag==0)
	{
		if(Immediate==0){
        
			if(Opcode==0) {
			  printf("DECODE: Operation is AND, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==1) {
				printf("DECODE: Operation is XOR, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==2) {
				printf("DECODE: Operation is SUB, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==4) {
				printf("DECODE: Operation is ADD, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==5) {
				printf("DECODE: Operation is ADC, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==10) {
				printf("DECODE: Operation is CMP, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==12) {
				printf("DECODE: Operation is ORR, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==13) {
				printf("DECODE: Operation is MOV, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==15) {
				printf("DECODE: Operation is MNV, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}

      }

      else if(Immediate==1){
        
        if(Opcode==0) {
			  printf("DECODE: Operation is AND, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==1) {
				printf("DECODE: Operation is XOR, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==2) {
				printf("DECODE: Operation is SUB, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==4) {
				printf("DECODE: Operation is ADD, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==5) {
				printf("DECODE: Operation is ADC, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==10) {
				printf("DECODE: Operation is CMP, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==12) {
				printf("DECODE: Operation is ORR, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==13) {
				printf("DECODE: Operation is MOV, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==15) {
				printf("DECODE: Operation is MNV, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}

      }
	}
	
}
void Add(){
	if(Immediate==0) 
	{R[Destination]=R[Operand1]+R[Operand2];}
	else 
	{R[Destination]=R[Operand1]+Operand2;}
}	
void Sub(){
	if(Immediate==0)
	{R[Destination]=R[Operand1]-R[Operand2];}
	else 
	{R[Destination]=R[Operand1]-Operand2;}
}
void Mov(){
	R[Destination]=R[Operand1];
}
void Mnv(){
	R[Destination]= ~R[Operand1];
}

void And() {
	if(Immediate==0)
	{
		R[Destination] = R[Operand1] & R[Operand2];
	}
	else
	{
		R[Destination] = R[Operand1] & Operand2;
	}
}

void Or() {
	if(Immediate==0)
	{
		int or = R[Operand1] | R[Operand2];
		R[Destination] = or;
	}
	else
	{
		int or = R[Operand1] | Operand2;
		R[Destination] = or;
	}
}
	
void main() {
	
	ReadFromFile();
	
	while(current_instruction != 0xEF000011) {
		Fetch();
		Decode();
	}
}