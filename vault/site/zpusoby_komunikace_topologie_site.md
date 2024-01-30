#refactor #anki 
# Způsoby komunikace
## Unicast
- Komunikace pouze dvou zařízení (server - klient)

## BroadCast
- Jedno zařízení vysílá na všechny v dané síti

## Multicast
- Jedno zařízení vysílá na N jiných zařízení

## Anycast
- Vyberte ze skupiny zařízení a následná komunikace s oným zařízením

## Topologie Síťí
- Zabývá se zapojením prvků v síti
- Fyzická x logická topologie se od sebe liší

### Bus topology
- Jedna sběrnice
- Jednoduché a levné řešení
- Může vysílat pouze jeden klient
- Dojte ke kolizi
- Kolizní doména protokol CSMA

### Ring topology
- Komunikaci zajišťuje tzv. Token, který koluje mezi stanicemi => rychlé
- Může být více tokenů
- Vlastník tokenu vysílání; ostatní naslouchají
- Eliminace kolize
- Problém při přerušení kruhu

### Token ring
- Využívá speciální paket - token k informování uzlů o možnosti komunikace
- Token je vytvořen při inicializaci sítě
- Server nebo vyčlenění stanice (AM - Aktivní monitor)
- Stav je jím monitorován a v případě ztráty/poškození, je vygenerován nový
- SM ( pohotovostní motor ) - hlídá AM a v případě nutnosti jej zastoupí -> nový AM
- Velikost 3B
- Vysílat může aktuálně prázdný token - idle
- Označený (Busy) token spolu s daty předá stanice sousedovi; předává dokud nedorazí do cíle
- Příjemce potvrdí přijaté data zasláním označeného tokenu odesílateli
- Po přijetí uvede odesílatel token do původního stavu - může vysílat další uzel

### Star topology
- Citlivé na výpadek uzlu
- V domácnosti
- Jednoduché rozšíření a řešení závad

### Tree topology
- Větší počítačové sítě

## Broadcastova adresa
- Vždy nejvyšší adresa v dane podsíti
- Oběžník
- 192.168.0.0/24 -> 192.168.0.255
- 192.168.0.0/26 -> 192.168.0.63

## CSMA
- Carrier Sense Multiple Acces
- Mnohonásobný přístup s nasloucháním nosné
- Protokol naslouchá signálu s vícenásobným přístupem
- Je užit při kolizi dat - *BUS TOPOLOGY*
- Stanice/Uzel může vysílat pokud je klid na komunikačním kanálu
- V případě kolize je nutno poslat data znovu - náhodná doba opakování

## CSMA/CD
- CSMA/Collision Detection
- V případě kolize pozastavuje vysíláni všech stanic v kolizní doméně
- Jam signál
- Po odeslání paketu pokračuje v monitoringu sítě
- Čekání náhodně dlouho dobu a opakování pokusu o vysílaní
- Malá režie při malé zátěži
- Při stoupající zátěži mlže klesat propustnost - opakování přenosu
- Využití u Ethernetu

## CSMA/CA
