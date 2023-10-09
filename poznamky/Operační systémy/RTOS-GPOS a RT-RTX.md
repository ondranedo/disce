# RTOS-GPOS a RT-RTX

## RTOS-GPOS a RT-RTX

## Názvosloví
	**Task-Úloha** - Soubor programových instrukcí
	**Thread-Vlákno **- jednotka CPU, má vlastní „program counter“ a „stack“

	**Process-Proces** - Jeden počítačový program,
	
*Note: V ****RTOS**** je často zaměňován výraz Task a Thread, mohou být považována za synonyma.*

## GPOS
**G**eneral **P**urpose **O**perating **S**ystem
- Plánuje úlohy
- Spravuje „Resourcy“
- Ovladače pro GPU, HDD, USB
- Windows, Linux, MacOS, Android, iOS
- Může na něm běžet více procesů
- Často velice důležité uživatelské UI
- Nelze zajistit okamžitou odpověď od OS uživateli, či zařízení, na podnět uživatele či zařízení
	- Toto je problém, **RTOS **je řešením

- Scheduler je nedeterministický
	- Toto je problém, **RTOS **je řešením

## Super Loopa
- Typické programováni mikro-kontroloru
- Velice výhodné pro bežné užití
- Šetří paměť a čas procesoru
- Jednoduší pro debugging
- ISR (**I**nterrupt **S**ervice **R**outine) je vhodné využít chceme-li jednu či dvě časově kriticky náročné úkony (do 1 ms), při více je vhodně využít **RTOS**
- Pokud jedna úloha trvá neobvykle dlouho může dojit k lagu

![RTOS-GPOS a RT-RTX](images/RTOS-GPOS%20a%20RT-RTX.png)![RTOS-GPOS a RT-RTX-1](images/RTOS-GPOS%20a%20RT-RTX-1.png)

## RTOS
**R**eal **T**ime **O**perating **S**ystems

- Plánuje úlohy „tasky“ __task
- Ovladače pro Wifi, Bluetooth, LCD, Led diodes
- Spravuje „resourcy“
- FreeRTOS, RTX
- Využití při kritických požadavků na čas, či při nutnosti pracovat více vstupů najednou
- Možnost volit prioritu úlohy
- Vlákna mezi sebou mohou sdílet „resourcy“
- Může být vykonávat jen jeden proces
- ISR může být využito v RTOS, pokud má ISR vyšší prioritu

![RTOS-GPOS a RT-RTX-2](images/RTOS-GPOS%20a%20RT-RTX-2.png)![RTOS-GPOS a RT-RTX-3](images/RTOS-GPOS%20a%20RT-RTX-3.png)

## RT-RTX
**R**eal **T**ime execution

- RTOS operační systém pro ARM Cortex-M zařízení
- Možnost až 254 priorit
- Podpora multithreading, a zabezpečení kritické sekce
- Každá úloha dostane vlastní vlákno, a tak je jím samým (Vlákno = Úloha)
- Každé vlákno běží dokud se neobjeví vlákno s větší prioritou
- Vlákna se stejnou prioritou jsou zaměňována round-and-robin algoritmem

[https://ece.uwaterloo.ca/~dwharder/icsrts/Keil_board/RL/Introduction/](https://ece.uwaterloo.ca/~dwharder/icsrts/Keil_board/RL/Introduction/)

[https://www.keil.com/support/man/docs/rlarm/rlarm_ar_artxarm.htm](https://www.keil.com/support/man/docs/rlarm/rlarm_ar_artxarm.htm)

