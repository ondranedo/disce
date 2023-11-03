# BIOS

![BIOS](images/BIOS.png)

- Drivery pro základní desku jsou inicializovány POST (**Power on self test**) - testuje komponenty
- SETUP utilities
- Boot loader
- API pro HW
- *CMOS-RAM*

## Výrobci BIOSU

- AMI, Award, Phoenix, Open BIOS

## POST

- Beep kódy, hlasový výstup, výpis na obrazovce
- Nastaví rychlostní parametry podle hodnot v CMOSU
- POST karty
- Předá řízení boot loaderu

## Boot loader

- Hledá na HDD/SSD, MBR/GPT, zavede jej do OP

## SETUP

- Utilita pro nastavení HW
- Pouští se před POST kombinací kláves
- CMOS má pouze data, programy se nachází v E^2PROM/FLASH: Edituje data v CMOSU

## CMOS - RAM

- Complementary Metal-Oxide Semiconductor
- Obsah je při vypnutí udržován pomocí baterie 2025
- Obsah editován Sestupem
