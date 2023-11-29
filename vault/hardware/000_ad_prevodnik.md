# AD Převodník

## Kaskádové zapojení
- Pro 8 bit převodník by bylo potřeba až 256 komparátorů => nereálné
- Sério paralelní zapojeni

## Kompenzační A/D převodník
- Automatické kompenzátory napětí
- Nejpoužívanější, jednoduché na výrobu, rychlé
- Používá D/A převodník
- Stupňuje napětí
- Obsah čítače je nulován
- S każdym impulzem je zvýšena hodnota čítače
- Výstup komparátoru je „0“ -> konec čítaní
- Hodnota převáděného napětí je uložena v paměti

## Sledovací A/D převodník
- S vratným čítačem
- Směr je řízen výstupem komparátoru
- Špatně reaguje na rychlé změny signálu
- Oscilace převodníku

## Aproximační A/D
- Doba převodu je pevná
- Vysoká přesnost
- Použiv ve voltmetrech a digitálních osciloskopech
- Vyžaduje na vstup konstantní napětí

## S dvojitou integrací
- Pomalejší, ale velmi přesný
- Odolný vůči šumu
- Převod je složen ze dvou fázi
- Převádí napětí na čas - snadné digitalizovat
- Multimetry
- Signálem start se otevře hradlo
- Do citace začnou proudit impulzy
- Na přepínači je *Uvst*
- Po konstantní dobu se integruje *Uvst*
- Obsah čítače roste konstantní rychlostí
- Po naplnění se přepne přepínač na konstantní *Uref* - opačná polarita *Uvst*
- Na vstupu integrátoru je konstantní napětí opačné polarity -> začíná klesat napětí na jeho výstupu
- Napětí *Ui* lineárně klesá rychlosti úměrnou velikosti *Uref*
- *Ui = 0* -> změna výstupu komparátoru, signál "*stop*" -> zavření hradla -> hodnota uložena v čítači
- Obsah čítače je úměrný času *Tref*, který je úměrný velikosti *Uvst*
- Měřené napětí je úměrně době druhé integrace

## Sigma delta
- Rozdělen na analogovou a digitální část
- A: jednoduchá, pomalejší - integrátor, komparátor, zdroj *Uref*, obvody pro slučování anal. Sig.
- D: složitější, rychlá - číslicová filtrace, decimace vzorkového sig.
- Vzorkovací frekvence je n-krát větší než *fmax* vstup sig.
- Klasické A/D převodníky užívají *S-K-N* teorém
- Mnohem větší počet vzorků - **oversampling**
- Vzorky jsou nahuštěné v čase - **decimace**
- Neměří amplitudu
- „Stream“ jedniček a nul
- Levné, vysoké rozlišení (24;32b), nízká spotřeba, digitální filtr, potlačuje kvantizační šum, vhodné pro audio techniku