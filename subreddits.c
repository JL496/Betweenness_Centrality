#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "subreddits.h"

int AddItem(subreddit** head, char * nm){
    int pos = 0;
    if (*head == NULL){
        subreddit* temp;
        temp = (subreddit*)malloc(sizeof(subreddit));
        strcpy(temp->name, nm);
        temp->position = 0;
        *head = temp;
        (*head)->next = NULL;
    } else {
        subreddit * current = *head;
        while (current->next != NULL){
            current = current->next;
        }
        pos = current->position + 1;
        current->next = (subreddit*)malloc(sizeof(subreddit));
        current->next->position = pos;
        strcpy(current->next->name, nm);
        current->next->next = NULL;    
    }
    return pos;
}

void DeleteList(subreddit** head){
    subreddit* temp;
    while (*head!=NULL){
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int SearchList(const subreddit* head, char * key){
    if (strcmp(head->name, key)==0){
        return head->position;
    }
    if (head->next==NULL){
        return -1;
    }
    int ret = SearchList(head->next,key);
    return ret;
}