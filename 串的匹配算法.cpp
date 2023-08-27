#include<stdio.h>
//串的类型定义：顺序串 & 链串 
#define MAXLEN 255
//顺序串 
typedef struct SString{
	char ch[MAXLEN+1];//串一般从1开始计数，所以数组的总长要大一位
	int length; 
}SString; 

//链串 
//定义块 
#define CHUNKSIZE 80 //块的大小可由用户定义（一个结点里放多少个字符 
typedef struct Chunk{   
	char ch[CHUNKSIZE];
	struct Chunk*next;
}Chunk;
typedef struct LString{
	Chunk *head,*tail;//串的头指针和尾指针，分别指向串的头和尾 
	int curlen;//串当前的长度 
}LString;


//串的匹配：BF算法 & KMP算法
//BF算法(pos为开始查找的起点，在S上)
int Index_BF(SString S,SString T,int pos){
	int i = pos,j = 1;
	while(i <= S.length && j <= T.length){
		if(S.ch[i] == T.ch[j]){
			++i;
			++j;
		}else{
			i = i - j + 2;
			j = 1;
		}
	}
	if(j >= T.length)return i-T.length;
	else return 0; 
}

//KMP算法（pos为开始查找的起点，在S上）
//其中找nextval[j]的方法
void get_nextval(SString T,int nextval[]){
	int i = 1;
	nextval[1] = 0;
	int j = 0;
	while(i < T.length){
		if(j == 0 || T.ch[i] == T.ch[j]){
			++i;++j;
			if(T.ch[i] != T.ch[j]) nextval[i] = j;
			else nextval[i] = nextval[j];
		}
		else j = nextval[j];
	}
} 
int Index_KMP(SString S,SString T,int pos){
	int i = pos,j = 1;
	int nextval[T.length];
	get_nextval(T,nextval);
	for(int i = 1;i < T.length; i++){
		printf("%d ",nextval[i]);
	}
	while(j < S.length && j < T.length){
		if(j == 0 || S.ch[i] == T.ch[j]){
			++i;
			++j;
		}else{
			j = nextval[j];
		}
	}
	if(j > T.length) return i - T.length;
	else return 0;
} 



int main(){
	SString S = {"aabaabcac",9};
	SString T = {"abaabcac",8};
	printf("%d\n",Index_BF(S,T,1));
	printf("%d\n",Index_KMP(S,T,1));
	
}
 

 
