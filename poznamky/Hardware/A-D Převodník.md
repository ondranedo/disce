# A/D Převodník

## Kaskádní zapojení
- Pro 8 bit převodník by bylo potřeba až 256 komparátorů => nereálné

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
- Fáze
	- Signálem start se otevře hradlo
	- Do citace začnou proudit impulzy
	- Na přepínači je *Uvst*
	- Po konstantní dobu se integruje *Uvst***
**
	- Obsah čítače roste konstantní rychlostí
	- Po naplnění se přepne přepínač na konstantní *Uref* - opačná polarita *Uvst*
- Fáze
	- Na vstupu integrátoru je konstantní napětí opačné polarity -> začíná klesat napětí na jeho výstupu 
	- Napětí *Ui* lineárně klesá rychlosti úměrnou velikosti *Uref*

	- *Ui = 0 *-> změna výstupu komparatoru, signál "*stop*" -> zavření hradla -> hodnota uložena v čitači
	- Obsah čítače je úměrný času *Tref*, který je úměrný velikosti *Uvst*

- Měřené napětí je úměrně době druhé integrace 

