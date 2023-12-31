#refactor #anki
# USB
- Univerzální sériová linka
- Navrženo pro sjednocení propojovacích zařízení
- Nástupce RS-232
- Také nástupce IEEE 1284 (LPT), PS/2
- Využívá třídy
- Podpora **plug&play**
- Možnost připojení za chodu a není nutný restart
- Komunikační vzdálenost do 5m s využitím TP
- Hvězdicová architektura
- Na jeden rozbočovač 127 maximum
- Po připojení zařízení na USB proběhne enumerace
- USB logická struktura

## Hostitelský řadič
- Host controller
- Implementace SW či HW
- Společně je implementován i kořenový řadič

### Kořenový rozbočovač
- Root hub (master)
- Nejvyšší úroveň k níž se připojují zařízení
- Muže požadovat data od jednoho zařízení, ale zařízení nemůže samo vysílat
## Historie
#TODO
  
## Typy
### USB Type-C
- Uveden v roce 2014 jako univerzální konektror
- Nic negarantuje (rychlost, ...)
- Nejen pro USB standard:
- Thunderbolt 3, 4
- PCIe
- DisplayPort, HDMI, VGA
- možnost nabíjení až 100W

## Princip
- Přenáší se přes rámce (framy), kde každý má delku **1ms**
- Každý rámec má několik paketů
- Typy packetů:
	- Token,
	- Data,
	- Handshake,
	- ...
- **pozitivní potvrzování**
- pokud data přišla v pořádku posílá se **ACK** packet
- při chybě přenosu, přijímač mlčí a data se odešlou znovu
- **packet NAK**
- Když zařízení není schopno data příjmout
- většinou dočasný problém
- přenos typu **OUT**
- V případě přenosu **IN** je vyslán packet **NAK**
- **NAK** nikdy neodesílá hostitel
- Pro komunikaci mezi hostitelem a **EP** je využito **pipe**
- **Pipe** je vytvořen vždy pro jeden směr přenosu
- **typ pipe**:
	- Messages,
	- Streams
	- Inventarizace sběrnice
	- Bus enumeration

### Token packet
- definuje typ transakce na USB
- **SOF** - Start of frame
- **IN** - přenos od hostitele k zařízení
- **OUT** - přenos od zařízení k hostiteli
- **SETUP** - start řídícího přenosu

### Data packer
- samotná data, identifikátor se pravidelně mění, ošetření ztráty packetu
- přenost od LSB po MSB
- Data0
- Data1

### Handshake packet
- potvrzovací packet
- **ACK** - kladné potvrzení (data přišla v pořádku)
- **NAK** - záporné potvrzení (data nelze přijmout)
- **STALL** - využito pokud není přenos kompletní

### Preamble packet
- přepínání sběrnice mezi **Low** a **Full Speed**

### USB Zjednodušenná činnost
- po sběrnici kolují rámce, jak datové, tak servisní
- chce-li zařízení vysílat či přijímat, čeká na servisní rámec
- po potvrzení s dalším příchozím datovám rámcem může začít komunikovat
- Podpora CRC, jak HW tak SW

#### Většina přenosu dat je složena z vysílání 3 packetů
1. Hostitelský řadič vyšle USB paket popisujicí typ a směr přenosu, adresu zařízení a číslo koncového bodu
2. Zařízení nebo systém vysílají datový packet, popřípadě oznámí, že nemají co vysílat
3. Ukončení transakce nastává vysíláním handshake paketu, jímž se potvrdí úspěšnost

### Inventarizace sběrnice
## Typy přenosu
- USB rozlišuje 4 typy EP -> 4 typy přenosu
### Control transfer
- pouze pomocí pipe zprávy
- využívá k detekci a konfiguraci zařízení při jeho připojení
- vysoká priorita a hlídání chyb

### Interrupt transfer
- Tam kde se periodicky vysílá malý objem dat (myš, klávesnice)
- systém se periodicky dotazuje na nová data (cca 100ms)
- v případě chyby nastává opakování
- náročné na časování

### Isochronous Ttransfer
- probíhá v reálném čase
- nutné zajištění konstantní rychlost
- chyby se neopravují, chybná data jsou zahozena
- náročné na časování

### Bulk transfer
- Přenos většího množství dat, jež vyžadují detekci chyb, ale není časově náročná (skener, tiskárna, externí disk)
- rychlost je dána vytížením sběrnice
- opakování přenosu v případě chyb
