#include <stdio.h>

char MEM[1000];
int PC=0;

void ReadFromFile() {
	FILE *fp;
	fp=fopen("Input.txt","r");
	int ct=0;
	while(ct<4){
		fscanf(fp,"%s","%s",MEM);
		printf("%s",MEM);
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
	ReadFromFile();
	int ct=0;
	while(ct<4){
		Fetch();
		ct++;
	}
}