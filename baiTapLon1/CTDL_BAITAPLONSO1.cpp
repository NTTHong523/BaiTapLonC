#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 100
char stack[MAX];
float stack_R[MAX];
char infix[MAX],postfix[MAX];
int top, top_R = -1;

int isEmpty(){
	if(top == -1)
		return 1;
	return 0;	
}
char pop(){
	int value;
    if(top==-1){
    	printf("\nNhap sai dinh dang !");
    	exit(1);
	}
      
    else{
 		value= stack[top];
 		top = top-1;
    	return  value;  
	}
    	
}
void push(int x){
	if(top_R==MAX-1)
        printf("\n\tSTACK bi day ");
	else
		stack[++top] = x;
}
float pop_R(){
	float value;
    if(top_R==-1){
    	printf("\nNhap sai dinh dang !");
    	exit(1);
	}
      
    else{
 		value= stack_R[top_R];
 		top_R = top_R-1;
    	return  value;  
	}	
}
void push_R(float x){
	if(top_R==MAX-1)
        printf("\n\tSTACK bi day ");
	else
		stack_R[++top_R] = x;
}
int uuTien( char symbol){
	switch(symbol){
		case '^':
			return 3;
		case '/':
		case '*':
		case '%':
			return 2;
		case'+':
		case '-':
			return 1;
		default:
			return 0;
			
	}
}
int khoangCach(char c){
	if(c == ' '|| c =='\t')
		return 1;
	else
		return 0;	
}
void inToPost(){
	int i, j=0;
	char symbol, next;
	for(i = 0; i<strlen(infix); i++){
			symbol = infix[i];
		if(!khoangCach(symbol)){
			switch(symbol){
				case '(':
					push(symbol);
				break;
				case ')':
					while((next = pop()) != '(')
						postfix[j++] = next;
					break;	
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':	
				case '^':	
					while(!isEmpty() && uuTien(stack[top])>=uuTien(symbol))
						postfix[j++] = pop();
					postfix[j++] = ' '; 
					push(symbol);
					break;
				default:{
					postfix[j++] = symbol;
					break;
				}	
			}
		}
	}
	while(!isEmpty())
		postfix[j++] = pop();
	postfix[j] = '\0';	
	
}
float post_Eval(){
	float a,b;
	int i =0;
	char cat[MAX];
	while(postfix[i]!= NULL){
		if(postfix[i] >='0' && postfix[i] <='9'){
			char a[2]; a[0]= postfix[i];
			strcpy(cat,a);
			char b[10];
			int j = 0;
			while((postfix[i+1] >='0' && postfix[i+1] <='9')|| postfix[i+1]=='.'){
				b[j++] = postfix[i+1];
				i++;
			}
			strcat(cat,b);
	   		float x; 
	   		sscanf(cat, "%f", &x); 
	   		push_R(x);;
		}else{
			if(postfix[i]==' '){
		 		++i;
		 		char a[2]; a[0] = postfix[i];
				strcpy(cat,a);
				char b[10];
				int j = 0;
				while((postfix[i+1] >='0' && postfix[i+1] <='9')|| postfix[i+1]=='.'){
					b[j++] = postfix[i+1];
					i++;
				}
				strcat(cat,b);
	   			float x; 
	   			sscanf(cat, "%f", &x); 
	   			push_R(x);
  			}else{	
				a = pop_R(); 
				b = pop_R(); 
				switch(postfix[i]){
					case '+':
						push_R(b+a);break;
					case '-':
						push_R(b-a);break;
					case '*':
						push_R(b*a);break;
					case '/':
						push_R(b/a);break;	
					case '^':
						push_R(pow(b,a));break;
				}
			}
		}
		i++;
	}
	return pop_R();
}
void print(){
	int i =0;
	printf("Bieu thuc da chuyen doi : ");
	while(postfix[i]){
		printf("%c", postfix[i++]);
	}
	printf("\n");
}
int main(){
	float result;
	printf("Nhap vao bieu thuc:  ");
	gets(infix);
	inToPost();
	print(); 
	result = post_Eval();
	printf("Ket qua : ");
	printf("%.3f\n",result);

}
