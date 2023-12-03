## 1. Zadání

### 1.1. Jednoduchý popis

Je zadáno vypracovat úlohu, jež bude fungovat jako jednoduchá benzínová stanice. Bude možno volit mezi dvěma typy paliv **(BENAL, NAFLA)**, očividně klávesnicí (více kapitola 2.1). Ve stavu `STANDBY`, je možno vejít do skryté nabídky, umožňující změnu ceny za litr daného paliva. Po výběru pohonné hmoty (klávesa `1`, `2`), zmáčknutí klávesy `4` , začne tankováni. Ukončení tankování jo možné klávesou `6`. Poté se nám vypíše cena nutna k zaplacení, z které můžeme odejít klávesou `#` zpět do režimu `STANDBY`.

### 1.2. Limitace

Je nutno limitovat maximální objem paliva, které můžeme natankovat; stanoveno na 50 litrů PHM. Také je nutno limitovat rychlost, kterou palivo proudí; stanoveno na 0,2 litrů za sekundu.
### 2. Teoretický rozbor
### 2.1. HW + periferie

Úloha je vypracována na **STM32F407VGT6U**; práce s jedno-jádrovým **Cortex™-M4** (32 bit ARM, obrázek 2.1) pracující na taktu 168MHz. Cortex™ má: 5-ti stupňovou pipelinu, 1MB  paměť typu flash, Ethernet, 192kB interní paměti (RAM).

![](./Pasted%20image%2020231122191528.png)
Obrázek 2.1

# 2.1.1. Periferie
K **STM32F407VTG6U** je připojeno: LCD a Keyboard, které jsou připojeny k pinům na sběrnici Discovery boardu (obrázek 2.2).
![](./Pasted%20image%2020231122191947.png)

### 2.2. HW + programování

Jako IDE využíváme program Keil µVision s pomocnou knihovnou pro hardwareovou abstrakci [stm32kit](https://github.com/spsehavirov/stm32kit). Vývoj v Keil µVision 5 (Obrázek 2.3.)

![](./Pasted%20image%2020231122193700.png)
Obrázek 2.3

Programování je prováděno v jazyce C (STD 99).
### 2.3. Algoritmy

Nejsou zde užity žádné významné/zajímavé algoritmy.
### 2.4. Vývojový diagram

![carbon](./Pasted%20image%2020231122195153.png)
Obrázek 2.1

## 3. Řešení

### 3.1. Zdrojový kód s komentáři
![carbon-2.svg](carbon-2.svg)
Obrázek 2.1
### 3.2. Zajímavé sekce
```cpp
{
	setup_standby,  // nastaveni setup funkce
	none,           // nastaveni update funkce
	// Callbacky pri zmacknutych klavesach
	{{set_fuel_1, '1'},
	 {set_fuel_2, '2'}, 
	 {state_goto_next, '4'}
	 },
	 
	STATION_STANDBY, // Zbytecne nastaveni stavu
	"", // RADEK 1 LCD
	""  // RADEK 2 LCD
},
```
Obrázek 2.2
V obrázku 2.2. můžeme vidět snadnost přidání stavů díky FSM.
## 4. Závěr
### 4.1. Úspěchy/Neúspěchy a jejich řešení

Program se podařilo vyřešit úspěšně, díky užití modelu *FSM* se vývoj dělal snadno. Je nutno program "urovnat", díky "zbrklému" vývoji jsou v programu metodiky, ne příliš účinné.  Dále měření času není zcela přesné (Užít RTOS?; "Na mravence atmovkou"), magic number není ideální.
 
### 4.2. Další rozšíření úlohy

- Přidaní snadnějšího výpisu na LCD,
- Přesné měření času,
- "Urovnání" kódu,
- Více paliv (celkově více možností).