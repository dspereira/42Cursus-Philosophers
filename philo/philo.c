#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// number_of_philosophers

// time_to_die              -> tempo maximo que o filosofo pode passar sem comer ou morre
// time_to_eat              -> tempo que demora para comer, precisa de 2 garfos
// time_to_sleep            -> tempo que o filosofo demora a dormir

// number_of_times_each_philosopher_must_eat -> quantidade de vezes que cada filosofo tem de comer. opecional

unsigned long get_actual_time_ms(void)
{
	struct timeval t;
    unsigned long time_ms;
    
	gettimeofday(&t, NULL);
    time_ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time_ms);
}

unsigned long time_has_passed(unsigned long start, unsigned long time)
{
    unsigned long actual;

    actual = get_actual_time_ms();
    if ((actual - start) >= time)
        return (actual);
    return (0);
}

int main (int argc, char **argv)
{
    struct timeval tm;
    unsigned long start;
    unsigned long desired;
    unsigned long stoped;
    
    start = get_actual_time_ms();
    desired = 15000;
    while(1)
    {
        stoped = time_has_passed(start, desired);
        if (stoped)
        {
            printf("started at:   %lu ms\n", start);
            printf("stoped after: %lu ms\n", stoped);
            printf("----------------------------\n");
            printf("started at:   %lu s\n", start/1000);
            printf("stoped after: %lu s\n", stoped/1000);
            printf("----------------------------\n");
            printf("passed:       %lu ms / %lu s\n", desired, desired/1000);
            break;
        }
    }
    return (0);
}
