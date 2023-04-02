#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 100
char stack[MAX];
char infix[MAX],	postfix[] = "100 2-";
//float stack2[MAX];
float stack_R[MAX];
int top = -1;



int isEmpty(){
	if(top == -1)
		return 1;
	return 0;	
}
float pop(float stack[]){
	float value;
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
void push(float x, float stack[]){
	if(top==MAX-1)
        printf("\n\tSTACK bi day ");
	else
		stack[++top] = x;
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
//void inToPost(){
//
//	int i, j=0;
//	char symbol, next;
//	for(i = 0; i<strlen(infix); i++){
//			symbol = infix[i];
//		if(!khoangCach(symbol)){
//			switch(symbol){
//				case '(':
//					push(symbol);
//				break;
//				case ')':
//					while((next = pop()) != '(')// da goi pop thi top -1;
//						postfix[j++] = next;
//					break;	
//				case '+':
//				case '-':
//				case '*':
//				case '/':
//				case '%':	
//				case '^':	
//					while(!isEmpty() && uuTien(stack[top])>=uuTien(symbol))
//						postfix[j++] = pop();
//					postfix[j++] = ' '; 
//					push(symbol);
//					break;
//				default:{
//					postfix[j++] = symbol;
//					break;
//				}	
//			}
//		}
//	}
//	while(!isEmpty())
//		postfix[j++] = pop();
//	postfix[j] = '\0';	
//	
//}
//int post_Eval(){
//	int a,b;
//	char check;
//	int i =0;
//	char cat[MAX];
//	while(postfix[i+1]!= NULL){
//		if(postfix[i] >='0' && postfix[i] <='9'){
//			push(postfix[i] - '0');
//			i++;
//			
//		}
//		if(postfix[i]==' '){
//			++i;
//			char a[2]; a[0]= postfix[i]; printf("%d",a[0]);
//			char b[2];
//			while(postfix[i+1] >='0' && postfix[i+1] <='9'){
//				b[0] = postfix[i+1-'0'];
//				strcat(cat,b);
//				i++;
//			}
//			const char *str = cat; 
//   			int x; 
//   			sscanf(str, "%d", &x); 
//   			push(x);
//   			i++;
//  			
//		}
//			else{	
//			a = pop();
//			b = pop();
//			switch(postfix[i]){
//				case '+':
//					push(b+a);break;
//				case '-':
//					push(b-a);break;
//				case '*':
//					push(b*a);break;
//				case '/':
//					push(b/a);break;	
//				case '^':
//					push(pow(b,a));break;
//			}
//		}
//	}return pop();
//}
void print(){
	int i =0;
	printf("Bieu thuc da chuyen doi : ");
	while(postfix[i]){
		printf("%c", postfix[i++]);
	}
	printf("\n");
}
int main(){
//	int result;
//	printf("Nhap vao bieu thuc:  ");
//	gets(infix);
//	inToPost();
	print(); 

	float a,b;
	char check;
	int i =0;
	char cat[MAX];
	while(postfix[i]!= NULL){
		if(postfix[i] >='0' && postfix[i] <='9'){
			char a[10]; a[0]= postfix[i];
				strcpy(cat,a);
				int j = 0;
				while((postfix[i+1] >='0' && postfix[i+1] <='9')|| postfix[i+1]=='.'){
					a[j++] = postfix[i+1];
					i++;
				}
				strcat(cat,a);
		//		const char *str = cat; 
	   			float x; 
	   			sscanf(cat, "%f", &x); 
	   			push(x,stack_R);

		}
		else{
			if(postfix[i]==' '){
		 		++i;
				char a[10]; a[0]= postfix[i];
			//	puts(a);
				strcpy(cat,a);
	
				int j = 0;
				while((postfix[i+1] >='0' && postfix[i+1] <='9')|| postfix[i+1]=='.'){
					a[j++] = postfix[i+1];
					i++;
				}
				strcat(cat,a);
		//		const char *str = cat; 
	   			float x; 
	   			sscanf(cat, "%f", &x); 
	   	
	   			push(x,stack_R);
	   			
	   	
  			}else{	
				a = pop(stack_R); 
				b = pop(stack_R); 
				switch(postfix[i]){
					case '+':
						push(b+a,stack_R);break;
					case '-':
						push(b-a,stack_R);break;
					case '*':
						push(b*a,stack_R);break;
					case '/':
						push(b/a,stack_R);break;	
					case '^':
						push(pow(b,a),stack_R);break;
				}
			}
		
		}
		i++;

	}
	printf("%f",stack_R[top]);
//	printf("%d",stack_in[top-1]);
	
}
