#include<stdio.h>
//�������Ͷ��壺˳�� & ���� 
#define MAXLEN 255
//˳�� 
typedef struct SString{
	char ch[MAXLEN+1];//��һ���1��ʼ����������������ܳ�Ҫ��һλ
	int length; 
}SString; 

//���� 
//����� 
#define CHUNKSIZE 80 //��Ĵ�С�����û����壨һ�������Ŷ��ٸ��ַ� 
typedef struct Chunk{   
	char ch[CHUNKSIZE];
	struct Chunk*next;
}Chunk;
typedef struct LString{
	Chunk *head,*tail;//����ͷָ���βָ�룬�ֱ�ָ�򴮵�ͷ��β 
	int curlen;//����ǰ�ĳ��� 
}LString;


//����ƥ�䣺BF�㷨 & KMP�㷨
//BF�㷨(posΪ��ʼ���ҵ���㣬��S��)
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

//KMP�㷨��posΪ��ʼ���ҵ���㣬��S�ϣ�
//������nextval[j]�ķ���
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
 

 
