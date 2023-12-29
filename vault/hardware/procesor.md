# Procesor
- čte instrukce z paměti, tak vykonává program 
- závisí na instrukčních sadách [[cisc_risc_mips]]
- některé procesory umí i více instrukčních sad
- program tvořen instrukcemi je převeden na strojový kód
- [[zastupci_cpu]], [[cinnost_procesoru]]

## Dělení procesorů dle typu
### MCU
- Micro-Controller Unit 
- mikrořadiče - microcontroller unit
- [[stm32f407xx]]
- slabší výkon
- široké uplatnění: pračky, ledničky, kávovary, ...
- minimální rozšiřitelnost, jedno užití

### CPU
- Central Processing Unit
- vychází z IBM PC architektur
- větší a výkonnější než **MCU** -> více tepla (ztrátový výkon), složitější patice
- jednodušší a širší rozšiřitelnost

### DSP
- Digital Signál Processing
- určité pro jeden algoritmus
- kompromis mezi CPU a MCU
- audio, zesilovače, 5G převodník, dig. osciloskop

### NPU
- Network Processing Unit
- součástí routerů, přepínačů, ...
- výrobce Broadcom a Intel
- Spory s bezpečností

### GPU
- Graphics Processing Unit
- grafické karty
- řeší výpočty na velikém počtu dat: 3D Scény, AI modely, GPGPU

### APU
- Accelerated Processing Unit
- V jednom pouzdře CPU i GPU

### SoC
- System on the chip
- GPU, CPU, RAM, DSP, ... ; vše v jednom čipu
- použity v: mobilní telefony, Apple Silicon

## Dělení procesorů dle operandu
- respektive šírky slova instrukce
- 4, 8, 16, 32, 64 bitové procesory
- většina registrů mají stejnou délku jako je šířka operandu

## Dělení procesorů dle použití
- Embedded, DSP, Univerzální
