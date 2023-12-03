# Přepínání kontextu
![[kontext_switch.png]]
- Více aplikací než je jader; nutno přepínat kontext
- poměrně náročná operace
- činnosti provedeny mezi přepnutím kontextu závisí na CPU a OS
- efektivnější je přepnutí uživatelských vláken; netřeba mazat **TLB**
## Kontext
- Uložení **PCB** při přepnutí kontextu [[pcb]]
- **L1** a **TLB** Cache v CPU lze zařadit do přepnutí kontextu [[xxx_strankovani]]
	- obsah není kopírován, je pouze zneplatněn

### Kdy dojde k přepnutí kontextu
- **Chyba**
- **ISR** - IO [[xxx_inetrrup_service_routine]]
	- obsluha přerušení
- **DMA** - direct memory acces [[xxx_dma]]
- Plánování dle algoritmů: [[planovaci_algoritmy]]

> Meltdown, Specter HW chyba

## HW varianta
- rychlejší, ne však o tolik
- problém při správném uložení všech registrů
	- floating point registry
- nelze aktualizovat
- nepoužíváno v OS Windows či Linuxu
## SW varianta
- používána u běžných OS
- ukládá všechny registry, či možnost volit, které registry se uloží