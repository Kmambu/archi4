///////////////////////////////////////////////////////////////////////////////
// File   :  hello.c
// Date   :  decembre 2018
// Author :  Franck
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <almosmkh.h>
#include <hal_macros.h>

char *str0 = "bonjour"; 
char *str1 = "monde!";
 
pthread_t tid0, tid1;

void * th (void *arg)
{
    while (1) {
        printf("%s\n", (char *)arg);
        //display_string((char *)arg);
    }
}

void main(void) 
{
    if (pthread_create(&tid0, NULL, th, (void *)str0))
        printf("pthread_create impossible");
    if (pthread_create(&tid1, NULL, th, (void *)str1))
        printf("pthread_create impossible");
    while (1); 
}

/* 
vim: tabstop=4 : shiftwidth=4 : expandtab
*/
