# CISC, RISC a MIPS

> Complex and Reduced instruction Set Computer

## CISC
- Velmi složité
- Řada x86
- Instrukce nemají stejnou délku
- Různá doba vykonání
- Pomalejší
- Snadnější na programování
- Složitější na výrobu - komplexní návrh, větší pravděpodobnost vady, problémy s vyššími frekvencemi

### pileline
1. Načtení z paměti do fronty instrukcí
2. Dekódování instrukce -> strojový kód
3. Provedení instrukce
	1. Provedení uProgramu - složen z uInstrukcí - řazena do Fronty
	2. Prováděcí jednotka
	3. Každé instrukcí odpovídá posloupnost uInstrukcí
4. Zřetězené zpracování instrukcí - **pipelining**

## MIPS
- Druh RISC
- Microprocessor without interlocking pipeline
- Možnost zpracovávat více instrukcí najednou - paraelizace bez více jader
- Stará mi se CPU - interlocking pipeline
- Stará se programátor - náročnější - bez interlocking pipeline
- Load/store architecture - instrukce mohou být používaný pouze operandy z registru
- Obsahují 32/64 bit registry
- Starší herní konzole - CISCO

### Zřetězení zpracování instrukcí
- Pipelineing - překrývání strojových instrukcí
- Rozdělení instrukce mezi jednotlivé části procesoru
- Možnost zpracovávat více instrukcí najednou
- **Minimální rozdělení:**
	1. Načtení a dekódování instrukce
	2. Provedení instrukce a případné uložení
- Rozdělení procesoru na dvě části
	1. **EU** - execution unit
	1. **BIU** - bus interface unit

- Zřetezeni se neustále vyvíjí a zlepšuje
- Na úkor zvětšení počtu provedených instrukcí se zvýší instrukční latence
- Čas provedení cele instrukce
- Při přístupu ke stejnému registru
- Kohosi se pro RTOS
- Analogie: montážní linka

### 5ti stupňová pipeline
1. Instruction fetch - načtení instrukce z paměti
2. Instruction decode - dekódování instrukce a načtení příslušných registru
3. Execute / ALU - provedení instrukce
4. MEM / Data memory acces - čtení/zapis dat v cache
5. Write back - zápis výsledku do paměti
6. Snaha CPU provést v jednom taktu jeden stupeň
7. FDE - fetch decode execute

- Problém:
		ADD 1 to R5
		COPY R5 to R6
	- CPU pozná zakázané stavy