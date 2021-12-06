#ifndef __SUBREDDITS_H__
#define __SUBREDDITS_H__

typedef struct subreddit subreddit;

struct subreddit{
    int position;
    char name[50];
    subreddit* next;
};

// Functions associated with struct subreddit
void Print(const subreddit* head);
void PrintList(const subreddit* head);
int SearchList(const subreddit* head, char * key);
void DeleteList(subreddit** head);
void RemoveItem(subreddit** head, int n);
int AddItem(subreddit** head, char * nm);

#endif
