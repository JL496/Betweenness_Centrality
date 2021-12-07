#ifndef __SUBREDDITS_H__
#define __SUBREDDITS_H__

typedef struct subreddit subreddit;

struct subreddit{
    int position;
    char name[50];
    subreddit* next;
};

// Functions associated with struct subreddit
int SearchList(const subreddit* head, char * key);
void DeleteList(subreddit** head);
int AddItem(subreddit** head, char * nm);

#endif
