# RTX 4 Legacy

- Podpora pro jádro ARM Cortex-M
- Celistvý RTOS pro ES
- Plánovač, mutex, události, semafor, mailobx
- Celé to řídí plánovč, ví co zpustit a kdy

## CMIS-RTOS API

- Unireverzální API pro RTOS
- Zobecnění pro registry `RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;`
- Používá některé Cortex-M instrukce

## Příkazy

    os_tsk_create((void*)fn(void), int priority);

    os_kernel_setup((void*)fn(void));

    os_sem_create

    os_sem_lock

    os_sem_unlock

>LCD je kritická sekce