#include "philo.h"

long long get_time_in_milliseconds(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
	//prendo i secondi e li moltiplico per mille per raggiungere un valore di millisecondi, divido i microsecondi per 1000

    long long milliseconds = (long long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    
    return milliseconds;
}
