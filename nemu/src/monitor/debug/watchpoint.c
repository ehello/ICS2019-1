#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static int head_len=0;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){
	if(free_==NULL){
		printf("No free space for watchpoints!\n");
		assert(0);
	}
	++head_len;
	if(head==NULL){
		head=free_;
		free_=free_->next;
		head->next=NULL;
		head->NO=head_len;
		return head;
	}
	else{
		WP* tmp=head;
		while(tmp->next != NULL) tmp=tmp->next;
		tmp->next=free_;
		free_=free_->next;
		tmp->next->next=NULL;
		tmp->next->NO=head_len;
		return tmp->next;
	}	
}

void free_wp(int n){
	if(!n){printf("Illegal NO.\n");return;}
	if(head==NULL){printf("No watchpoints.\n");return;}
	WP* wp=head;int i=1;
	for(;i<n;++i){
		wp=wp->next;
		if(wp==NULL){printf("Illegal NO.\n");return;}
	}
	--head_len;
	if(wp==head){
		head=wp->next;
	}
	else{
		WP* tmp=head;
		while(tmp->next != wp) tmp=tmp->next;
		tmp->next=wp->next;
	}
	wp->next=free_;
	wp->val=0;
	free_=wp;
}
