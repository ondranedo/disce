#anki #todo
# Plánovací algoritmy
- Lze plánovat algoritmy dvěma způsoby
1. **Preemptivní**
	- OS má plnou kontrolu na procesem
	- kontrola nad všemi prostředky procesu
	- Algoritmy: SRTF, PS, RR, MQS, ...
	- Nutnost HW podpory
2. **Nepreemptivní**
	- OS nemůže spravovat proces
	- Algoritmy: SJF, FCFS, ...

## FCFS
- samostatně se nepoužívá
	- kombinace s RR, MFQS
## SJF
- hladovění
## RR

## SRTF
- preemptivní se SJF
- v případě stejných BT, FCFS

## PS
- hladovění
	- umělé navýšení priority

## MQS
- procesy se rozdělí do front
- rozdělení do skupin:
	- Interaktivní procesy
	- Procesy na pozadí