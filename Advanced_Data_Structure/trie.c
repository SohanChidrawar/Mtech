#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define size 26

struct trie
{	struct trie* children[size];
	bool eow;
};

struct trie* root;

struct trie* createnode()
{
	struct trie* node = (struct trie*)malloc(sizeof(struct trie));
	node->eow = false;
	for(int i=0;i<size;i++)
		node->children[i]=NULL;
	return node;
}

void insert(const char* word)
{
	struct trie* curr = root;
	for(int i=0;word[i]!='\0';i++)
	{	int index = word[i]-'a';
		if(curr->children[index]==NULL)
			curr->children[index] = createnode();
		curr = curr->children[index];
	}
	curr->eow = true;
}

bool search(const char* word)
{
	struct trie* curr = root;
	for(int i=0;word[i]!='\0';i++)
	{	int index = word[i]-'a';
		if(curr->children[index]==NULL)
			return false;
		curr = curr->children[index];
	}
	return curr->eow;
}

bool prefix(const char* word)
{
	struct trie* curr = root;
	for(int i=0;word[i]!='\0';i++)
	{
		int index = word[i]-'a';
		if(curr->children[index]==NULL)
			return false;
		curr = curr->children[index];
	}
	return true;
}

int main()
{
	root = createnode();
	const char* word[] = {'and','an','andies','aunty','the','these'};
	int n = sizeof(word)/sizeof(word[0]);
	for(int i=0;i<n;i++)
	{	insert(word[i]);
		printf("Word is inserted successfully");
	}
	
	int a = search("and")
	printf(a?"Elemet found":"Element not found");

	printf("Word start with prefix th:%s",prefix("th")?"Yes":"No");
	
}
