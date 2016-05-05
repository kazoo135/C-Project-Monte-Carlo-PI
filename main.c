#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define thread_count 4

//Globals variables
double my_pi = 0;
pthread_mutex_t mutex;

//function prototype
void *estimate_pi( void* tosses);


int main()
{

    int number_of_tosses = 0;
    int thread;

    pthread_t* thread_handles;
    thread_handles = malloc(thread_count * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    //read in number of tosses
    printf("How many tosses?");
    scanf("%d",&number_of_tosses );
    printf("Total tosses %d\n", number_of_tosses);

    for(thread  = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, estimate_pi, (void*) number_of_tosses);
    for( thread= 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);
        pthread_mutex_destroy(&mutex);

        printf("Estimate of PI is: %f\n", my_pi);
       free(thread_handles);
    return 0;
}//end of main

void *estimate_pi( void* tosses){
    int i, number_in_circle;
    double x, y, distance_squared;
    int my_tosses = (int)tosses;
   srand( time(NULL) );
    for( i = 0; i < my_tosses; i++){
        x = 2 * ( rand()/( (double)RAND_MAX + 1) ) -1;
        y = 2 * ( rand()/( (double)RAND_MAX + 1) ) -1;

        distance_squared = (x * x) + (y * y);
        if(distance_squared <= 1)
            number_in_circle++;
    }
// Critical section
    pthread_mutex_lock(&mutex);
    my_pi += number_in_circle/(double)my_tosses;
    pthread_mutex_unlock(&mutex);
    printf("Number of hits %d\n", number_in_circle);
    printf("My_PI %f\n", my_pi);

    return NULL;

}// end of estimate_pi


