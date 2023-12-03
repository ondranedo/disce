#anki
# Životní cyklus procesu
![[proces_runtime.png]]
![[proces_runtime2.png]]
## New / Created
- Proces je vytvořen s PCB [[002_pcb]]
- Jsou inicializovány registry, stack, ...
- Proces čeká na zařazení do fronty **Ready** dlouhodobým plánovačem [[004_dlouhodoby_planovac]]
	- U **GPOS** automaticky schváleno
	- **RTOS** mohou zdržovat schválení [[xxx_rtos]]
## Ready 
- Proces je zařazen na konec fronty **FIFO**
- Pomocí dispatcheru (krátkodobý plánovač [[xxx_kratkodoby_planovac]]) je nahrán do procesoru (výměna všech registrů, **PCB**)

## Running
- Proces může běžet ve dvou módech:

### Uživatelský mód
- Proces nemá přístup k jádru OS
- Může přistupovat k svým datům a instrukcím
- V případě systémového voláni je proces přesunut do **kernel** módu
	- `open`, `read`, `write`, `exec`, `close`, `fork`, ... [[xxx_systemova_volani]]
	- Linux má přes 300 syscallů, Windows více než 2000

#### Restrikce
- V uživatelském módu je striktně dán adresový prostor pro proces
	- proces je limitován sám na sebe - nemůže přistupovat k dalším procesům
- Nulový přístup k HW

### Kernel mód
- Proces má přístup ke všemu v uživatelském módu
- Není limitován restrikcemi uživatelského módu
- Kompletní kontrola na procesem, HW, ...

## Waiting
- I/O operace
	- Vstup od uživatele do `stdin`
- jsou spravovány střednědobým plánovačem [[xxx_strednedoby_planovac]]
### Blocked
- Proces může být blokován když se snaží přistoupit ke kritické sekci
	- Například tiskárna: není připojena, tiskne, ...
- Blokaci mlže provést **semafor** či **mutex** [[xxx_kriticka_sekce]]

## Terminated
- Proces muže být terminován, pokud se dokončí, poslední instrukce, či je explicitně ukončen `KILL` syscallem
- I když je proces v terminovaném stavu, nachází se stále v tabulce procesů - **zombie proces**
- V terminovaném stavu proces "leží", dokud jeho rodič nepřečte jeho `exit status` pomocí `wait` syscallu
	- Pokud tak rodič neučiní, terminovaný proces leží v tabulce napořád

## SWAP varianty
- proces může být umístěn do SWAP prostoru [[xxx_swap]] je-li rozhodnuto střednědobým plánovačem
- většinou jsou do SWAPu umístěny procesy ve frontě **Ready** či **Waiting**
