#todo
# NON GPOS

> **GPOS** - General purpose operating system
## Network operating system
- Operační systém routerů (síťových prvků)
- Pro LAN - většinou v korporátních s.
- **Ciso IOS**
- Dva typy NOS: **Peer-To-Peer** a **Client server**
### Funkce NOS
- přidávání a spravování uživatelských účtů
- spravování přístupu ke zdrojům na síti
- spravuje komunikaci mezi zařízeními na síti
- monitoruje a kontroluje síť

### Výhody NOS
- Více funkcí než GPOS zaměřených pro komunikaci
- velice stabilní
- dobrá bezpečnost
- vzdálená správa sítě 
- jednoduché rozšíření sítě
### Nevýhody NOS
- velice drahé
- nutná častá správa serveru
- centrální lokace - porucha

## Distributed operating system
- Rozdělen mezi několik zařízení
- Připojení přes LAN/WAN
- Každý v sobě nese (hocrux) - mikrojádro s komponenty pro koordinaci
- Hocrux spolu komunikují pro zajištění funkcí OS
- Jeden uzel má plný přístup ke všem systémovým prostředkům
- Komplikované plánování a paralelní zpracování
- Uživatel nemusí mít možnost zjistit, kde je program fyzicky spuštěn, a kde je uložení souboru - řízení OS
  ![[distribute_os.png]]
  
## RTOS
[[rtos]]
- Systém reálného času
- Dva základní typy:
1. **HARD** - Úlohy musí být dokončeny v určitém čase
2. **SOFT** - Pokud vyprší deadline, je možnost úlohu ještě dokončit
- Průmyslové aplikace: Robotika, letecký průmysl, ...
- Velmi jednoduchý návrh OS - rychlost, determinismus
- Ochrana proti selhání
- Vyžaduje pokročilé plánování a správu paměti
- Zdánlivý multitasking
- Sdílení zdrojů
- Problémy se super smyčkou

## EOS
> **E**mbedded **OS**

- RTOS a EOS není to samé, však EOS je také RTOS
- Limitované zdroje
- Deterministický a predikovatelný
- Co není podstatné: GUI, bezpečnost, (závisí na užití)