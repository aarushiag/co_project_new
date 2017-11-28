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
static int Offset;
static int Offset_ext;
static unsigned int Operand1;
static unsigned int Operand2;
static unsigned int Destination;
static unsigned int R[16];
static unsigned int result;
static unsigned int stored_value;
static unsigned int Z;
static unsigned int N;
static long int array_of_registers[16][512];

void ReadFromFile() {
	FILE *fp;
	fp=fopen("Input.txt","r");
	
	if(fp == NULL) {
		printf("Error opening file for writing\n");
		return;
  }
	int ct=0;
	while(fscanf(fp,"%x %x",&address,&instruction)!=EOF){
		//printf("%x",address);
		//printf("%x",instruction);
		MEM[address]=instruction;
	}
	
	fclose(fp);
}

void Fetch() {
	current_address=PC;
	current_instruction=MEM[PC];
	printf("%s%x %s%x \n","FETCH: Fetching instruction 0x",current_instruction," from address 0x",current_address);
	PC+=4;
}

void ReadInstruction() {
	//printf("%x",current_instruction);
	Condition = (current_instruction >> 28) & (0b1111);
	//printf("%d \n",Condition);
	Flag = (current_instruction >> 26) & (0b0011);
	//printf("%d \n",Flag);

    if(Flag==0)
    {
        Immediate=(current_instruction >> 25)& (0x1);
		//printf("%d \n",Immediate);
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
				printf("DECODE: Operation is MOV, First Operand is R%d, Immediate Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
			}
			else if(Opcode==15) {
				printf("DECODE: Operation is MNV, First Operand is R%d, Second Operand is R%d, Destination register is R%d.\nRead Rs: R%d = %d, R%d = %d\n",Operand1,Operand2,Destination,Operand1,R[Operand1],Operand2,R[Operand2]);
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
        printf("DECODE: Operation is STR, Base Register is R%d, Offset is %d, Register to be stored in memory is R%d.\n,Read Register: R%d = %d\n",Operand1,Operand2,Destination,Destination,R[Destination]);
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
	if(Immediate==0) 
	{
		printf("EXECUTE: ADD %d and %d\n",R[Operand1],R[Operand2]);
		result=R[Operand1]+R[Operand2];
	}
	else 
	{
		printf("EXECUTE: ADD %d and %d\n",R[Operand1],Operand2);
		result=R[Operand1]+Operand2;}
}	
void Sub(){
	if(Immediate==0)
	{
		printf("EXECUTE: SUB %d and %d\n",R[Operand1],R[Operand2]);
		result=R[Operand1]-R[Operand2];}
	else 
	{
		printf("EXECUTE: SUB %d and %d\n",R[Operand1],Operand2);
		result=R[Operand1]-Operand2;
		}
}
void Mov(){
	if(Immediate==0) {
		printf("EXECUTE: MOV value of R%d in R%d\n,",Operand2,Destination);
		result=R[Operand2];
	}
	else {
		printf("EXECUTE: MOV %d in R%d\n",Operand2,Destination);
		result=Operand2;
	}
}
void Mnv(){
	if(Immediate==0) {
		printf("EXECUTE: MNV NOT of this R%d in R%d\n",Operand2,Destination);
		result=~R[Operand2];
	}
	else {
		printf("EXECUTE: MNV NOT of %d in R%d\n",Operand2,Destination);
		result=~Operand2;
	}
}

void And() {
	if(Immediate==0)
	{
		printf("EXECUTE: AND %d and %d\n",R[Operand1],R[Operand2]);
		result = R[Operand1] & R[Operand2];
	}
	else
	{
		printf("EXECUTE: AND %d and %d\n",R[Operand1],Operand2);
		result = R[Operand1] & Operand2;
	}
}

void Or() {
	if(Immediate==0)
	{
		printf("EXECUTE: ORR %d and %d\n",R[Operand1],R[Operand2]);
		int or = R[Operand1] | R[Operand2];
		result = or;
	}
	else
	{
		printf("EXECUTE: ORR %d and %d\n",R[Operand1],Operand2);
		int or = R[Operand1] | Operand2;
		result = or;
	}
}

void Xor() {
	if(Immediate==0)
	{
		printf("EXECUTE: XOR %d and %d\n",R[Operand1],R[Operand2]);
		int xor = R[Operand1] ^ R[Operand2];
		result = xor;
	}
	else
	{
		printf("EXECUTE: XOR %d and %d\n",R[Operand1],Operand2);
		int xor = R[Operand1] ^ R[Operand2];
		result = xor;
	}
}

void Cmp() {
	if(Immediate==0)
	{
		printf("EXECUTE: CMP %d and %d\n",R[Operand1],R[Operand2]);
          if(R[Operand1] == R[Operand2])
		  {
            result = 0;
            Z=1;
          }
          else if(R[Operand1] < R[Operand2])
		  {
            result = -1;
            N=1;
          }
          else{
            result = 1;
          }
	}
	else
	{
		printf("EXECUTE: CMP %d and %d\n",R[Operand1],Operand2);
		if(R[Operand1] == Operand2)
		{
            result = 0;
            Z=1;
        }
         else if(R[Operand1] < Operand2)
		{
            result = -1;
            N=1;
        }
          else{
            result = 1;
        }
	}
}

void Sign_extend()
{
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
	int index=Operand2/4;
	result=array_of_registers[Operand1][index];
	//load value from memory location to register
	printf("%s%d %s %d\n","EXECUTE: LOAD instruction from array R",Operand1," index ",index);
}
void Store(){
	int index=Operand2/4;
	stored_value=R[Destination];
	//store value from register to memory location
	printf("%s%d %s %d\n","EXECUTE: STORE instruction from array R",Operand1," index ",index);
}



void Execute() {
  
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
          printf("EXECUTE: ADC %d and %d\n",R[Operand1],R[Operand2]);
          //WRITE CODE
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
          Mnv();
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
	int index=Operand2/4;
	array_of_registers[Operand1][index]=stored_value;
	printf("%s%d %s %d\n","WRITEBACK: Store value in array R",Operand1," at index ",index);
}	

void WriteBack(){
	if(current_instruction != 0xEF000011) {
		if(Flag==1 && Opcode == 24)
		{
			WriteBackForStore();
		}
		else {
			R[Destination]=result;
			printf("%d\n",result);
			printf("%s%d\n","WRITEBACK: Store value in R",Destination);
		}
	}
}

	
	
void main() {
	
	ReadFromFile();
	
	do {
		Fetch();
		Decode();
		Execute();
		Memory();
		WriteBack();
		printf("\n");
	}while(current_instruction != 0xEF000011);
	printf("%s\n","EXIT:");
}