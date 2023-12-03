- Symetrický zdroj napájení
- Impulzní zdroje
- Existují testery ATX zdrojů.
![[at_atx.png]]
## AT Zdroj
- zastaralé
- ±12v, ±5v
- !Důležité zapojení kabelů na základní desce
	- Černýma k sobě

## ATX Zdroj
- Navíc 3v
- Některé nemají -12v

## Další zdroje
- SFX, TFX, …

## Konektory zdroje
### Power good
- Čas kdy se napiti ve zdroj dostanou do tolerované roviny
- PW_GOOD/PW_OK, aktivován pokud je zdroj vyrovnán
- Šedý vodič

### PS_ON
- Propojení PS_ON# s COM zapne zdroj na plný výkon
- Zelený vodič

### 5VSB
- Konstanta napájení základní desky
- Elektronické zapnutí PC
- Softwarové zapnutí, Wake ON Lan, Wake ON Ring, RTC
- Výkon do 5w

## Účinnost zdroj
- Pokud je zátěž zdroje nízká - jeho efektivita je malá
- Nejlépe si zdroje vedou pro 50-75% zátěží
- 80 PLUS - 20% zátšž účinnost 80%<
- Levne zdroje učinnost ~65%
  
![[psu_efficiency.png]]
  
- : Kouknou na střídavý proud #TODO
- **PFC Filtry** - eliminují vyšší harmonické v síti
- **Head guard** - po vypnutí vyvedení tepla médiem
- **OVC**: Ochrana při nadměrném proudu větve
- **OVP**: Ochrana proti napětí
- **OPP**: Ochrana proti výkonu
- **OTP**: Ochrana proti zvýšené teplotě
- **SCP**: Ochrana pro zkratů většinou více ochran pro každou úroveň napětí