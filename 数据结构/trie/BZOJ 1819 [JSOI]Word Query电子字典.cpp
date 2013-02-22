/*
 *	分析：
 *		暴力枚举需要添加、删除以及替换的字符，然后建立trie树进行判断是否存在该字符串，然后利用
 *		trie树存的信息进行判重
 *
 * */
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int kind = 26;
const int X = 25;

#define debug puts("here");

int m,n,tot;

struct trie{
	trie *p[kind];
	int is,id; //is 用于判重，id用于标记是否有单词在这个节点结束
	trie(){
		memset(p,NULL,sizeof(p));
		is = id = 0;
	}
};

void insert(trie *t,char *s){
	int id;
	for(int i=0;s[i];i++){
		id = s[i]-'a';
		if(t->p[id]==NULL)
			t->p[id] = new trie();
		t = t->p[id];
	}
	t->is = t->id = tot;
}

int has(trie *t,char *s){ //判断是否存在字符串s
	int c = 0;
	for(int i=0;s[i];i++){
		c = s[i]-'a';
		if(t->p[c]==NULL)
			return 0;
		t = t->p[c];
	}
	if(t->id)
		return 1;
	return 0;
}

int find(trie *t,char *s,int id){ //用于判断是否存在字符串s并且s没被统计过，id在这用于判重
	int c = 0;
	for(int i=0;s[i];i++){
		c = s[i]-'a';
		if(t->p[c]==NULL)
			return 0;
		t = t->p[c];
	}
	if(t->id==0||t->is==id) //不存在单词或者已经算过一次了
		return 0;
	t->is = id;
	return 1;
}

int main(){
	int n , m;
	while(cin>>n>>m){
		tot = 10000000;

		trie * root = new trie();
		char s[X],str[X];
		
		for(int i=0;i<n;i++){
			scanf("%s",s);
			insert(root,s);
		}
		
		while(m--){
			int ans = 0;
			scanf("%s",str);

			if(has(root,str)){
				puts("-1");
				continue;
			}

			tot --;

			int len = strlen(str);

			for(int i=0;i<len;i++){	// delete
				strcpy(s,str);
				
				for(int j=i+1;j<len;j++)
					s[j-1] = str[j];
				s[len-1] = '\0';
				
				ans += find(root,s,tot);
			}

			for(int i=0;i<len;i++){	// change
				for(int j=0;j<26;j++){
					if(str[i]==j+'a')
						continue;

					strcpy(s,str);
					s[i] = j+'a';
					
					ans += find(root,s,tot);
				}
			}

			for(int i=0;i<=len;i++){ // add
				for(int j=0;j<26;j++){
					
					s[i] = j+'a';
					for(int k=0;k<i;k++)
						s[k] = str[k];
					for(int k=i;k<len;k++)
						s[k+1] = str[k];
					s[len+1] = '\0';

					ans += find(root,s,tot);
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
