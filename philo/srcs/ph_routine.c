#include "philo.h"

void *ph_routine(void *philo)
{

    t_philo ph;

    ph = *(t_philo *) philo;
    printf("philo number: %i\n", ph.ph_number);

}