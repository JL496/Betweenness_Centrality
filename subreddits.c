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
        current->next = (subreddit *) malloc(sizeof(subreddit));
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

void Print(const subreddit* head){
    if (head==NULL){
        printf(" List is emtpy.\n\n");
        return;
    } else {
        printf("\n");
        printf(" ---------------------------------------------\n");
        printf(" |Pos:|Val:|     Address:     |       Next:      |\n");
        printf(" ---------------------------------------------\n");
        PrintList(head);
        printf(" ---------------------------------------------\n");

    }
}

void PrintList(const subreddit* head){
    printf(" |%3i |%50s |%15p |%15p |\n",head->position,head->name,head,head->next);
    if (head->next == NULL){ 
        return;
    }
    PrintList(head->next);
}

void RemoveItem(subreddit** head, int n){
    subreddit * current = *head;
    subreddit * temp = NULL;
    for (int i = 0; i < n - 1; i++){
        current = current->next;
    }

    temp = current->next;
    current->next = temp->next;
    free(temp);

    while (current->next != NULL){
        current = current->next;
        current->position = current->position - 1;
    }
}

int SearchList(const subreddit* head, char * key){
    if (strcmp(head->name, key)==0){
        //printf(" Key found at Position: %i\n", head->position);
        return head->position;
    }
    if (head->next==NULL){
        return -1;
    }
    int ret = SearchList(head->next,key);
    return ret;
}
