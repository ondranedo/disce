# Non-GPOS operating systems

**GPOS** - General purpose operating system

## Network operating system

- Operační systém routerů (síťových prvků)
- Pro LAN - většinou v korporátních s.
- Více funkcí než GPOS zaměřených pro komunikaci
- **Ciso IOS**

- Peer-To-Peer

## Distributed operating system

- Rozdělen mezi několik zařízení
- Připojení přes LAN/WAN
- Každý v sobě nese (hocrux) - mikrojádro s komponenty pro koordinaci
- Hocrux spolu komunikují pro zajištění funkcí OS
- Jeden uzel má plný přístup ke všem systémovým prostředkům
- Komplikované plánování a paralelní zpracování
- Uživatel nemusí mít možnost zjistit, kde je program fyzicky spuštěn, a kde je uložení souboru - řízení OS

![Non-GPOS operating systems](images/001_non_gpos.png)

## RTOS

- Systém reálného času
- Dva základní typy:
  1. **HARD** - Úlohy musí být dokončeny v určitém čase
  2. **SOFT** - Pokud vyprší deadline, je možnost úlohu ještě dokončit
- Průmyslové aplikace: Robotika, letecký průmysl, …
- Velmi jednoduchý návrh OS - rychlost, determinismus
- OChrana proti selhání
- Vyžaduje pokročilé plánování a správu paměti

## EOS

**E**mbedded **OS**

- RTOS a EOS není to samé, však EOS je také RTOS
- Limitované zdroje
- Deterministický a predikovatelný
- Co není podstatné: GUI, bezpečnost, [závisí na užití]
