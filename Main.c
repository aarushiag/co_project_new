#include <stdio.h>
//program_sequence stores all the instructions read from file
static unsigned long int program_sequence[1000];
//address is for storing address temporarily while reading from file
static unsigned int address;
//instruction is for storing instruction temporarily while reading from file
static unsigned int instruction;
//current_address stores the address of the current address being executed
static unsigned int current_address;
//PC is for program counter
static unsigned int PC=0;
//current_instruction stores the current instruction being executed
static unsigned int current_instruction;
//Condiiton, Flag, Immediate and Opcode are for identifying the type of instruction and the operation
//to be performed on the operands Operand1 and Operand2
static unsigned int Condition;
static unsigned int Flag;
static unsigned int Immediate;
static unsigned int Opcode;
//Offset is for storing offset obtained from the instruction
static int Offset;
//Offset_ext is for storing offset obtained after sign extension
static int Offset_ext;
//Operand1 and Operand2 are operands of the instruction
static unsigned int Operand1;
static unsigned int Operand2;
//Destination is the index of the register in which the result of execution is stored
static unsigned int Destination;
//R acts as registers for ARMSIM
static unsigned int reg[16];
//result stores the intermediate result obtained after EXECUTE stage
static unsigned int final_val;
static unsigned int stored_value;
static unsigned int Z;
static unsigned int N;
//array_of_registers is for simulating memory
static long int array_of_registers[16][512];

void ReadFromFile() {
	//FETCH stage
	//Reads the .MEM file to obtain the instructions required for executing the program
	FILE *fp;
	fp=fopen("Input.mem","r");

	if(fp == NULL) {
		printf("Error opening file for writing\n");
		return;
  }
	int ct=0;
	while(fscanf(fp,"%x %x",&address,&instruction)!=EOF){
		program_sequence[address]=instruction;
	}

	fclose(fp);
}

void Fetch() {
	//FETCH stage: gets the next instruction to be executed using program counter as the index
	//increments the program counter to point to the next instruction
	current_address=PC;
	current_instruction=program_sequence[PC];
	printf("%s%x %s%x \n","FETCH: Fetching instruction 0x",current_instruction," from address 0x",current_address);
	PC+=4;
}

void ReadInstruction() {
	//DECODE stage
	//parses the instruction to find the Condition, Flag, Immediate, Opcode and operands
	//for the instruction currently being decoded
	Condition = (current_instruction >> 28) & (0b1111);
	Flag = (current_instruction >> 26) & (0b0011);

    if(Flag==0)
    {
        Immediate=(current_instruction >> 25)& (0x1);
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
        Destination = ((current_instruction>>12)&(0b1111));

    }

    else if (Flag==2)
    {
        Opcode = ((current_instruction>>24) & (0b0011));
        Offset = (current_instruction & (0b111111111111111111111111));
    }

}


void Decode() {
	//DECODE stage: calls the ReadInstruction() to parse the instruction and identify the operation to be performed
	ReadInstruction();
	if(Flag==0)
	{
		if(Immediate==0){

			if(Opcode==0) {
			  printf("DECODE: Operation is AND, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==1) {
				printf("DECODE: Operation is XOR, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==2) {
				printf("DECODE: Operation is SUB, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==4) {
				printf("DECODE: Operation is ADD, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==5) {
				printf("DECODE: Operation is ADC, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==10) {
				printf("DECODE: Operation is CMP, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==12) {
				printf("DECODE: Operation is ORR, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==13) {
				printf("DECODE: Operation is MOV, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}
			else if(Opcode==15) {
				printf("DECODE: Operation is MVN, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1],Operand2,reg[Operand2]);
			}

      }

      else if(Immediate==1){

        if(Opcode==0) {
			  printf("DECODE: Operation is AND, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==1) {
				printf("DECODE: Operation is XOR, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==2) {
				printf("DECODE: Operation is SUB, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==4) {
				printf("DECODE: Operation is ADD, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==5) {
				printf("DECODE: Operation is ADC, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==10) {
				printf("DECODE: Operation is CMP, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==12) {
				printf("DECODE: Operation is ORR,First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==13) {
				printf("DECODE: Operation is MOV,First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}
			else if(Opcode==15) {
				printf("DECODE: Operation is MVN, First Operand is R%d, Immediate Second Operand is %d, Destination register is R%d.\nRead Rs: R%d = %d\n",Operand1,Operand2,Destination,Operand1,reg[Operand1]);
			}

      }
	}
	else if(Flag==1)
	{

      if(Opcode==25)
      {
        printf("DECODE: Operation is LDR, Base Register is R%d, Offset is %d, Destination Register is R%d.\n",Operand1,Operand2,Destination);
      }
      else if(Opcode==24)
      {
        printf("DECODE: Operation is STR, Base Register is R%d, Offset is %d, Register to be stored in memory is R%d.\nRead Register: R%d = %d\n",Operand1,Operand2,Destination,Destination,reg[Destination]);
      }
  }
  else if(Flag==2)
  {
    if(Opcode==2){
      if(Condition==0){
        printf("DECODE: Operation is BEQ\n");
      }
      else if(Condition==1) {
		  printf("DECODE: Operation is BNE\n");
	  }
      else if(Condition==11) {
		  printf("DECODE: Operation is BLT\n");
	  }
      else if(Condition==13) {
		  printf("DECODE: Operation is BLE\n");
	  }
      else if(Condition==12) {
		  printf("DECODE: Operation is BGT\n");
	  }
      else if(Condition==10) {
		  printf("DECODE; Operation is BGE\n");
	  }
      else if(Condition==14) {
		  printf("DECODE: Operation is BAL\n");
	  }
    }
  }

}

void Add(){
	//EXECUTE stage
	//ADD operation: adds the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: ADD %d and %d\n",reg[Operand1],reg[Operand2]);
		final_val=reg[Operand1]+reg[Operand2];
	}
	else
	{
		printf("EXECUTE: ADD %d and %d\n",reg[Operand1],Operand2);
		final_val=reg[Operand1]+Operand2;}
}
void Adc(){
	//EXECUTE stage
	//ADC operation: adds (with carry) the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: ADD WITH CARRY %d and %d\n",reg[Operand1],reg[Operand2]);
		final_val=reg[Operand1]+reg[Operand2];
	}
	else
	{
		printf("EXECUTE: ADD WITH CARRY %d and %d\n",reg[Operand1],Operand2);
		final_val=reg[Operand1]+Operand2;}
}
void Sub(){
	//EXECUTE stage
	//SUB operation: subtracts the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: SUB %d and %d\n",reg[Operand1],reg[Operand2]);
		final_val=reg[Operand1]-reg[Operand2];}
	else
	{
		printf("EXECUTE: SUB %d and %d\n",reg[Operand1],Operand2);
		final_val=reg[Operand1]-Operand2;
		}
}
void Mov(){
	//EXECUTE stage
	//MOV operation: moves the value stored in one of operand registers to the other one
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0) {
		printf("EXECUTE: MOV value of R%d in R%d\n,",Operand2,Destination);
		final_val=reg[Operand2];
	}
	else {
		printf("EXECUTE: MOV %d in R%d\n",Operand2,Destination);
		final_val=Operand2;
	}
}
void Mvn(){
	//EXECUTE stage
	//MNV operation: moves the bitwise NOT of the value stored in one of operand registers to the other one
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0) {
		printf("EXECUTE: MVN NOT of this R%d in R%d\n",Operand2,Destination);
		final_val=~reg[Operand2];
	}
	else {
		printf("EXECUTE: MVN NOT of %d in R%d\n",Operand2,Destination);
		final_val=~Operand2;
	}
}

void And() {
	//EXECUTE stage
	//AND operation: performs bitwise AND on the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: AND %d and %d\n",reg[Operand1],reg[Operand2]);
		final_val = reg[Operand1] & reg[Operand2];
	}
	else
	{
		printf("EXECUTE: AND %d and %d\n",reg[Operand1],Operand2);
		final_val = reg[Operand1] & Operand2;
	}
}

void Or() {
	//EXECUTE stage
	//OR operation: performs bitwise OR on the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: ORR %d and %d\n",reg[Operand1],reg[Operand2]);
		int or = reg[Operand1] | reg[Operand2];
		final_val = or;
	}
	else
	{
		printf("EXECUTE: ORR %d and %d\n",reg[Operand1],Operand2);
		int or = reg[Operand1] | Operand2;
		final_val = or;
	}
}

void Xor() {
	//EXECUTE stage
	//XOR operation: performs bitwise XOR on the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: XOR %d and %d\n",reg[Operand1],reg[Operand2]);
		int xor = reg[Operand1] ^ reg[Operand2];
		final_val = xor;
	}
	else
	{
		printf("EXECUTE: XOR %d and %d\n",reg[Operand1],Operand2);
		int xor = reg[Operand1] ^ Operand2;
		final_val = xor;
	}
}

void Cmp() {
	//EXECUTE stage
	//CMP operation: performs comparison on the operands stored in registers given in instruction
	//if Immediate bit is high, then one of the operands is directly taken from the instruction
	if(Immediate==0)
	{
		printf("EXECUTE: CMP %d and %d\n",reg[Operand1],reg[Operand2]);
          if(reg[Operand1] == reg[Operand2])
		  {
            final_val = 0;
            Z=1;
          }
          else if(reg[Operand1] < reg[Operand2])
		  {
            final_val = -1;
            N=1;
          }
          else{
            final_val = 1;
          }
	}
	else
	{
		printf("EXECUTE: CMP %d and %d\n",reg[Operand1],Operand2);
		if(reg[Operand1] == Operand2)
		{
            final_val = 0;
            Z=1;
        }
         else if(reg[Operand1] < Operand2)
		{
            final_val = -1;
            N=1;
        }
          else{
            final_val = 1;
        }
	}
}

void Sign_extend()
{
        //EXECUTE stage
	//sign extension is used in branch instructions when the first bit of offset is 1
	int addr=(Offset*4);

        if ((Offset >> 23) && 1)
        {
            Offset_ext =  ((0xFF000000)|addr);
        }

        else
        {
            Offset_ext =addr;
        }

}

void Ldr(){
	//EXECUTE stage
	//LDR operation: loads the value stored in a memory location to a register
	int index=Operand2/4;
	final_val=array_of_registers[Operand1][index];
	//load value from memory location to register
	printf("%s%d %s %d\n","EXECUTE: LOAD instruction from array R",Operand1," index ",index);
}
void Store(){
	//EXECUTE stage
	//STR operation: stores the value in a register to a memory location
	int index=Operand2/4;
	stored_value=reg[Destination];
	//store value from register to memory location
	printf("%s%d %s %d\n","EXECUTE: STORE instruction from array R",Operand1," index ",index);
}



void Execute() {
  //EXECUTE stage: calls the appropriate method to perform the required operation on the operation based on opcode
  if(Flag == 0)
  {
        if(Opcode == 0)
        {

          And();
        }
        else if(Opcode == 1)
        {
          Xor();
        }
        else if(Opcode == 2)
        {
          Sub();
        }
        else if(Opcode == 4)
        {
          Add();
        }
        else if(Opcode == 5)
        {
          Adc();
        }
        else if(Opcode == 10)
        {
          Cmp();
        }
        else if(Opcode == 12)
        {
          Or();
        }
        else if(Opcode == 13)
        {
          Mov();
        }
        else if(Opcode == 15)
        {
          Mvn();
        }

    }
	else if(Flag==1)
	{
		if(Opcode == 25)
		{
			Ldr();
		}
		else if(Opcode==24)
		{
			Store();
		}
	}
	 else if (Flag==2)
    {
    if(Opcode==2)
    {
        Sign_extend();
        if (Condition==0)
        {
             printf("EXECUTE: BEQ offset is: %d\n",Offset);
             if(Z==1)
             {
                 PC=PC-4;
                 PC=PC+8 + Offset_ext;
             }
        }

        else if (Condition==1)
        {
             printf("EXECUTE: BNE offset is: %d\n",Offset);
             if(Z!=1)
             {
                PC=PC-4;
                PC=PC+8 + Offset_ext;
             }
        }

        else if(Condition ==11)
        {
            printf("EXECUTE: BLT offset is: %d\n",Offset);
            if((N==1)&&(Z==0))
            {
                PC=PC-4;
                PC=PC+8 + Offset_ext;
            }
        }

        else if (Condition == 12)
        {

          printf("EXECUTE: BGT offset is: %d\n",Offset);
          if((N==0)&&(Z==0))
          {
                PC=PC-4;
                PC=PC+8 + Offset_ext;
          }

        }

        else if (Condition == 13)
        {
             printf("EXECUTE: BLE offset is: %d\n",Offset);
             if((N==1)||(Z==1))
             {
                PC=PC-4;
                PC=PC+8 + Offset_ext;
             }
        }

        else if (Condition == 14)
        {
              printf("EXECUTE: BAL offset is: %d\n",Offset);
              PC=PC-4;
              PC=PC+8 + Offset_ext;
        }

        else if (Condition == 10)
        {
             printf("EXECUTE: BGE offset is: %d\n",Offset);
             if((N==0)||(Z==1))
             {
              PC=PC-4;
              PC=PC+8 + Offset_ext;
             }
        }

    }

    }

}

void Memory() {
	//MEMORY stage: to either load a value or store a value from the memory
	if(Flag==1)
	{
		if(Opcode==25)
		{
			printf("%s \n","MEMORY: Load value from memory");
		}
		else if(Opcode==24)
		{
			printf("%s \n","MEMORY: Store value to memory");
		}
	}
	else
	{
		printf("%s \n","MEMORY: No Memory Operation");
	}
}

void WriteBackForStore(){
	//WRITEBACK stage
	//performs the writeback function for STORE instruction
	//stores the value in register to desired location in memory
	int index=Operand2/4;
	array_of_registers[Operand1][index]=stored_value;
	printf("%s%d %s %d\n","WRITEBACK: Store value in array R",Operand1," at index ",index);
}

void WriteBack(){
	//WRITEBACK stage: stores the results of the operations performed to registers or to the memory according to the instruction
	if(current_instruction != 0xEF000011) {
		if(Flag==1 && Opcode == 24)
		{
			WriteBackForStore();
		}
		else {
			reg[Destination]=final_val;
			printf("%s %d %s%d\n","WRITEBACK: Store value",final_val,"in R",Destination);
		}
	}
}

void main() {
	//MAIN function to run the program
	ReadFromFile();

	do {
		Fetch();
		if (current_instruction == 0xEF00006B)
        {
           printf("%s %d","Printing the value in R1 :-",reg[1]);
           printf("\n");
        }

        else if (current_instruction == 0xEF000000)
        {
           printf("%s %s","Printing the value in R0 :-",reg[1]);
           printf("\n");
        }
        else if (current_instruction == 0xEF00006A)
        {
            printf("%s","Please enter the input string");
            char *a;
            gets(a);
	   printf("\n");
	    
        }
        else if(current_instruction == 0xEF00006C)
        {
            printf("%s","Please enter the input integer ");
            int a;
            scanf("%d",&a);
            reg[0]=a;

        }
        else
        {
       	        Decode();
		Execute();
		Memory();
		WriteBack();
        }
		printf("\n");
	}while(current_instruction != 0xEF000011);
	printf("%s\n","EXIT:");
}
