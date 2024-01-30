# Synchronizace procesů

## Syllabus:

- producent, konzument;
- kritická sekce;
- supre smyčka;
- zamykací proměnná;
- zákaz přerušením;
- přesnén střídání;
- petersonovo řešení;
- atomická instrukce;
- binární semafor;
- obecný semafor;
- deadlock;
- starvation;
- live lock;
- inverze priorit;
- čtenáři vs písaři;
- večeřící filozofové;
- spící holič;

## Otázky v předpokladu:
- co je to proces, 
    - kde to je,
    - kde jsme se s tím setkali,
    - alternativní název;
- co je to kritická sekce,
    - proč to je,
    - jak se odesílají data na LCD v HAL knihovně,
        - kde tam dochází ke kritické sekci,
    - co řeší kritickou sekci;
- co to je atomická instrukce;
- co je to semafor,
    - kde jsme se s ním setkali,
    - FIFO,
    - čím se liší mutex od obecného semaforu;
- co je to přesné střídání, petersonovo řešení;
- co je to spin-lock, aktivní čekání vs pasivní čekání;
- co může probudit procesor k činnosti,
    - IRS, DMA interrupt;


## Struktura monologu:
- procesy;
- kritické sekce;
- kde se objevuje v HAL knihovně;
- jak řešit kritickou sekci;