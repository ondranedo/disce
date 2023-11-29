# Operační systém
- OS zajišťuje abstrakci pro různorodý hardware
- Hardware je velice specifický, plný různých záludností
- Uživatel OS nemusí znát jak HW Pipeline funguje
	- stačí mu otevřít a zavřít valve
- Zvýšení produktivity

## Komponenty OS
### Správa procesů
- Jak spustit program
- Jak alokovat prostředky

### Správa paměti
- Přiřazení paměti
- Ochrana paměti
- Virtuální paměť

### Souborové paměti
- Vedlejší paměť (externí pro stroj)

### I/O
- Ovladače zařízení

### Síťování
### Bezpečnost
### Uživatelské rozhraní

## OS spravuje
- Uživatelské a systémové aplikace
- Instance běžícího programu - možnost aby ve stejném čase bylo spuštěno více procesů
- Nezávislé paměťové místo
- Plánováni
- Komunikace mezi procesy
- concurrency

## Organizace paměti
- Podpora multiprogramování
- Sdílení dat mezi procesy
- Stránkování
- Virtuální paměť - použití externí paměti
- **Soubor** - abstrakce pro kvantum dat
- FAT, NTFS, EXTČ
- Kopírování, vytvoření, mazání, uložení
- Pokročilé funkce: vyhledávání, zálohování, apod.
- I/O vyžaduje přesné znalosti o zařízení - ovladače zařízení

## Složité problémy pro vývoj OS
- Spolehlivost
- Zpětná kompatibilita
- Rozšiřitelnost
- Přenositelnost