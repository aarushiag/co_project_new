#include <stdio.h>

char MEM[1000];
char address[1000];
char instruction[1000];
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
	while(fscanf(fp,"%s %s",&address,&instruction)!=EOF){
		
		printf("%s",address);
		printf("%s",instruction);
		ct++;
	}
	
	fclose(fp);
}

void Fetch() {
	char temp[10];
	char temp2[4];
	int i=PC+5;
	for (i=PC+5;i<PC+14;i++)temp[i-PC]=MEM[i];
	for (i=PC;i<PC+4;i++)temp2[i-PC]=MEM[i];
	printf("FETCH Instruction : %s from address: %s",&temp,&temp2); 
	PC=PC+14;
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