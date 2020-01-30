#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#define BUF 128
#define TOT 10
#define TRUE 1
#define FALSE 0


//************Declaring Structs***********************
//declare a struct for r type instructions
struct rtype {
	char r_instruction[TOT];
	char r_binary[TOT];
};

//declar a struct for i type instructions
struct itype{
	char i_instruction[TOT];
	char i_binary[TOT];
};

//declar a struct for registers
struct reg_num{
	char reg_name[TOT];
	char reg_binary[TOT];
};

//declare a struct for hex
struct hexadecimal{
    char binary[TOT];
    char hex[TOT];
};

//*******************Struct search Functions***********
char *divideString(char *str, int n);
char *hex_search(char *instruction, struct hexadecimal *array);
char *binaryconvert(char *dec);
void reverseString(char* str);
char *rtype_search(char *instruction, struct rtype *array);
char *itype_search(char *instruction, struct itype *array);
char *reg_search(char *instruction, struct reg_num *array); 
int rtype_bool(char *instruction, struct rtype *array);
int itype_bool(char *instruction, struct itype *array);

//*************MAIN PROGRAM***************************
int main(void) {

//************Struct initilization*******************
//declare hex struct
struct hexadecimal hex_array[16] = {
    {"0000", "0"},
    {"0001", "1"},
    {"0010", "2"},
    {"0011", "3"},
    {"0100", "4"},
    {"0101", "5"},
    {"0110", "6"},
    {"0111", "7"},
    {"1000", "8"},
    {"1001", "9"},
    {"1010", "a"},
    {"1011", "b"},
    {"1100", "c"},
    {"1101", "d"},
    {"1110", "e"},
    {"1111", "f"}
};
//declaring an array of rtype
struct rtype r_array[12] = {
    {"add", "100000"},
    {"addu", "100001"},
    {"and", "100100"},
    {"jr", "001000"},
    {"nor", "100111"},
    {"or", "100101"},
    {"slt", "101010"},
    {"sltu", "101011"},
    {"sll", "000000"},
    {"srl", "000010"},
    {"sub", "100010"},
    {"subu", "100011"},
    
};

//declare an array of itype
struct itype i_array[17] = {
    {"addi", "001000"},
    {"addiu", "001001"},
    {"andi", "001100"},
    {"beq", "000100"},
    {"bne", "000101"},
    {"lbu", "100100"},
    {"lhu", "100101"},
    {"ll", "110000"},
    {"lui", "001111"},
    {"lw", "100011"},
    {"ori", "001101"},
    {"slti", "001010"},
    {"sltiu", "001011"},
    {"sb", "101000"},
    {"sc", "111000"},
    {"sh", "101011"},
    {"sw", "101011"}
};

//declare an array of reg numbers
struct reg_num reg_array[32] = {
	{"$ze", "00000"},
	{"$at", "00001"},
	{"$v0", "00010"},
	{"$v1", "00011"},
	{"$a0", "00100"},
	{"$a1", "00101"},
	{"$a2", "00110"},
	{"$a3", "00111"},
	{"$t0", "01000"},
	{"$t1", "01001"},
	{"$t2", "01010"},
	{"$t3", "01011"},
	{"$t4", "01100"},
	{"$t5", "01101"},
	{"$t6", "01110"},
	{"$t7", "01111"},
	{"$s0", "10000"},
	{"$s1", "10001"},
	{"$s2", "10010"},
	{"$s3", "10011"},
	{"$s4", "10100"},		
	{"$s5", "10101"},		
	{"$s6", "10110"},		
	{"$s7", "10111"},
	{"$t8", "11000"},
	{"$t9", "11001"},
	{"$k0", "11010"},
	{"$k1", "11011"},
	{"$gp", "11100"},
	{"$sp", "11101"},
	{"$fp", "11110"},
	{"$ra", "11111"}					
};
//**************Variable initilization***************
char line[TOT][BUF]; 
char *token;
int i = 0;
//read file in
FILE *fp = fopen("textfile", "r");

//**************Reading text into array*************
//store file line by line
while(fgets(line[i], BUF, fp)) {
	line[i][strlen(line[i]) - 1] = '\0';
    i++;
}
//cleaning and making array of elements delimiter = " "
char *text_arry[i][4];
i--;
int len = i;
for (;i>-1;i--){
	token = strtok(line[i], " ");
	int j = 0;	
		while( token != NULL ) {
			text_arry[i][j]= token;    
			token = strtok(NULL, " ");
			j++;
		}
}
//clean comma off end of position 1 and 2
int len2 = len;
int len3 = len;
int len4 = len;
char *hexarry[len4][8];
for(;len>=0;len--){
	char *temp = text_arry[len][1];
	temp[strlen(temp)-1] = 0;
	text_arry[len][1] = temp;
}
for(;len2>=0;len2--){
	char *temp1 = text_arry[len2][2];
	temp1[strlen(temp1)-1] = 0;
	text_arry[len2][2] = temp1;
}

char *binaryarry[len3+1][4];
char *full_binary[len3];

//************PRINTS RESULTS*****************
//prints out restuls and fills binaryarray
for (int x=0;x<len3+1;x++){
	if (rtype_bool(text_arry[x][0],r_array)){
		printf("R-Format: ");
		printf("%s ",rtype_search(text_arry[x][0], r_array));
		printf("%s ",reg_search(text_arry[x][1],reg_array));
		printf("%s ",reg_search(text_arry[x][2],reg_array));
		printf("%s ",reg_search(text_arry[x][3],reg_array));
		binaryarry[x][0]= rtype_search(text_arry[x][0],r_array);
		binaryarry[x][1]= reg_search(text_arry[x][1],reg_array);
		binaryarry[x][2]= reg_search(text_arry[x][2],reg_array);
		binaryarry[x][3]= reg_search(text_arry[x][3],reg_array);
		full_binary[x] = binaryarry[x][0];
		strcat(full_binary[x], reg_search(text_arry[x][1],reg_array));
		strcat(full_binary[x], reg_search(text_arry[x][2],reg_array));
		strcat(full_binary[x], reg_search(text_arry[x][3],reg_array));
		strcat(full_binary[x], "00000000000");
	}else if (itype_bool(text_arry[x][0],i_array)){
		printf("I-Format: ");
		printf("%s ",itype_search(text_arry[x][0], i_array));
		printf("%s ",reg_search(text_arry[x][1],reg_array));
		printf("%s ",reg_search(text_arry[x][2],reg_array));
		printf("%s ", binaryconvert(text_arry[x][3]));
		binaryarry[x][0]= itype_search(text_arry[x][0],i_array);
		binaryarry[x][1]= reg_search(text_arry[x][1],reg_array);
		binaryarry[x][2]= reg_search(text_arry[x][2],reg_array);
		binaryarry[x][3]= binaryconvert(text_arry[x][3]);
		full_binary[x] = binaryarry[x][0];
		strcat(full_binary[x], reg_search(text_arry[x][1],reg_array));
		strcat(full_binary[x], reg_search(text_arry[x][2],reg_array));
		strcat(full_binary[x], binaryconvert(text_arry[x][3]));
	}
printf("\n");
}

//hexarry[0] = divideString(full_binary[0], 8);

/*
//tests structs
printf("Inst = %s, instbinary = %s", i_array[0].i_instruction, i_array[0].i_binary);
*/
return 0;
}
//******************Binary Converter****************
//converts decimal to binary
char *binaryconvert(char *dec){
int a = atoi(dec);
int binary[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char *return_binary = malloc(sizeof(char) * 16);
int i = 0;
while (a>0){
  binary[i] = a % 2;
  a = a / 2;
  i++;
}
int n = 0;
for (int i = 0; i <  16; i++) {
    n += sprintf (&return_binary[n], "%d", binary[i]);
}
reverseString(return_binary);
return return_binary;
}
//reverse binary string
void reverseString(char* str) { 
    int l, i; 
    char *begin_ptr, *end_ptr, ch; 
    l = strlen(str); 
    begin_ptr = str; 
    end_ptr = str; 
    for (i = 0; i < l - 1; i++) 
        end_ptr++; 
    for (i = 0; i < l / 2; i++) { 
        ch = *end_ptr; 
        *end_ptr = *begin_ptr; 
        *begin_ptr = ch; 
        begin_ptr++; 
        end_ptr--; 
    } 
} 

//******************Hex stuff**************************
char *divideString(char *str, int n) { 
int str_size = strlen(str); 
int i; 
int part_size; 
char *return_hex = malloc(sizeof(char) * 8);
part_size = str_size / n; 
for (i = 0; i< str_size; i++){ 
    if (i % part_size == 0)   
    return_hex[i] = str[i]; 
} 
//printf("%s", &return_hex[0]);
return return_hex;
} 

char *hex_search(char *instruction, struct hexadecimal *array){
int index = 0;
for(int x = 0; x<12;x++){
	if(!(strcmp(array[x].binary,instruction))){
		index = x;
		break;
	}
}
return array[index].hex;
}



//*******************Struct search Functions***********
//search r struct
char *rtype_search(char *instruction, struct rtype *array){
int index = 0;
for(int x = 0; x<12;x++){
	if(!(strcmp(array[x].r_instruction,instruction))){
		index = x;
		break;
	}
}
return array[index].r_binary;
}

//search i struct
char *itype_search(char *instruction, struct itype *array){
int index = 0;
for(int x = 0; x<17;x++){
	if(!(strcmp(array[x].i_instruction,instruction))){
		index = x;
		break;
	}
}
return array[index].i_binary;
}

//search register
char *reg_search(char *instruction, struct reg_num *array){
int index = 0;
for(int x = 0; x<32;x++){
	if(!(strcmp(array[x].reg_name,instruction))){
		index = x;
		break;
	}
}
return array[index].reg_binary;
}


//*************BOOL FOR Struct Search**************** 
//r type bool
int rtype_bool(char *instruction, struct rtype *array){
for(int x = 0; x<12;x++){
	if(!(strcmp(array[x].r_instruction,instruction))){
		return TRUE;
	}
}
return FALSE;	
}

//i type bool
int itype_bool(char *instruction, struct itype *array){
for(int x = 0; x<12;x++){
	if(!(strcmp(array[x].i_instruction,instruction))){
		return TRUE;
	}
}
return FALSE;	
}
