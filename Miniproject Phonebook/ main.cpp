#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include<bits/stdc++.h>

using namespace std;

map<string,string > gquiz1;
#define ALPHABET_SIZE (26)

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isWordEnd;
};

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(struct TrieNode *root,  const string key)
{
    struct TrieNode *pCrawl = root;

    for (int level = 0; level < key.length(); level++)
    {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->isWordEnd = true;
}

bool search(struct TrieNode *root, const string key)
{
    int length = key.length();
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < length; level++)
    {
        int index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isWordEnd);
}

bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

void suggestionsRec(struct TrieNode* root, string currPrefix)
{
    if (root->isWordEnd)
    {
        //cout << currPrefix;
        cout<<gquiz1.find(currPrefix)->first<<"-->>";
        cout<<gquiz1.find(currPrefix)->second;
        cout << endl;
    }
    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            currPrefix.push_back(97 + i);

            suggestionsRec(root->children[i], currPrefix);
            currPrefix.pop_back();
        }
    }
}
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    bool isWord = (pCrawl->isWordEnd == true);
    bool isLast = isLastNode(pCrawl);

    if (isWord && isLast)
    {
        cout << query << endl;
        return -1;
    }


    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return 1;
    }

}

void  Contacts()
{
	cout << endl;
}

void Display()
{
    map<string, string>::iterator itr;
	cout << "\nThe current phonebook is : \n";
	cout << "\tNAME\tNUMBER\n";
	for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
}

void  trie(struct TrieNode* root,string s){


    int comp = printAutoSuggestions(root,s);

    if (comp == -1)
        cout << "No other strings found with this prefix\n";

    else if (comp == 0)
        cout << "Any contact name like this is not saved\n";

 }

void Enter(struct TrieNode* root)
{
    string name;
    cout<<"enter name"<<endl;
    cin>>name;

    if (gquiz1.find(name)!=gquiz1.end())
    {
        cout<<"contact already exists"<<endl;
        cout<<gquiz1.find(name)->second;

    }
    else if(gquiz1.find(name)==gquiz1.end() )
    {
        string ph_num;
        cout<<"enter Number"<<endl;
        cin>>ph_num;
        gquiz1.insert(pair<string,string>(name,ph_num));
        insert(root,name);
        cout << "Number is entered sucessfully";
    }
}
void Search(struct TrieNode* root)
{
    string name;
    cout<<"enter name"<<endl;
    cin>>name;

    if (gquiz1.find(name)!=gquiz1.end())
    {
        cout<<"contact Found"<<endl;
        cout<<gquiz1.find(name)->second;
        return;
    }
    else if(gquiz1.find(name)==gquiz1.end() )
    {
        trie(root,name);
        Search(root);
    }
}


int main()
{
    struct TrieNode* root = getNode();

    char ans;
    while(true)
    {
    cout<< "Enter\n1\tTo enter conatct\n2\tTo search conatct\n3\tTo see all contacts\nX\tTo exit"<<endl;
    cin>>ans;
    if(ans == 'x' || ans=='X') break;
    if (ans=='1')
    {
        Enter(root);
    }
    else if(ans=='2')
    {
        Search(root);
    }
    else if(ans=='3')
    {
        Display();
    }
    else
        cout<<"invalid input"<<endl;
    }
    
}
