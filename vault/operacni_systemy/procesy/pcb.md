#anki
# PCB
![[pcb.png]]
- pointry na **STACK**, a **HEAP** (v obrázku tři tečky)
- **memory limits** - ukládání a čtení na správná místa; údaje o paměti
- **PID** - jedinečné číslo procesu
- **program counter** - adresa další instrukce k vykonání
- Data procesu můžeme v Linuxu číst ve složce: `/proc/<id procesu>/.`
	- `/proc/<id procesu>/status` - Stav procesu [[zivot_procesu]]
## Další data v PCB
- v RTOS [[xxx_rtos]], ukládá také časy a priority
- ISR které proces mohl generovat [[xxx_inetrrup_service_routine]]
- údaje o virtuální paměti [[xxx_virtualni_pamet]]
- IPC, data o sdílených prostředcích či komunikační kanály [[xxx_ipc]]
- u některých OS existují kopie PCB - ochrana proti chybám