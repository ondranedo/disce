#anki
# Kernel
- jádro
![[kernel.png]]

## Monolitické jádro
- Tradiční struktura OS
- Jeden program obsahuje celý kód jádra a poskytuje všechny služby OS
- Systémová volání
- Rychlé a efektivní
- Méně přenositelné a těžké na údržbu
- Malé chyby dokážou shodit celý systém
- Unix a podobné OS

## Mikro jádro
- Minimální jádro
- Zjednodušený návrh jádra - pouze privilegovaný režim
- Delegace části jádra na (deamons, servers) - moduly
- Režie pro komunikace - **IPC**
- User-space servery
- Rychlé nasazení, jednoduchá údržba
- Větší paměťová stopa
- Časté přepínání kontextu
- bezpečnější

## Hybridní řešení
- Snaha o jádro co nejmenší, však má i důležité komponenty
- Windows NT, XNU

## EXO jádro
![[exo.png]]
- experimentální 
- přímá komunikace SW s HW
	- programy provádí vlastní paměťovou alokaci
- vyvíjen MIT

## NANO
- podobné EXO jádru
- modulovatelné
- malý kód
	- bezpečnější, méně bugů
- lehce přenositelné
- malá funkcionalita
