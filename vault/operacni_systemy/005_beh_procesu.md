# Běh procesu

![[proces_runtime.png]]

## NEW

- Proces je vytvořen s PCB
![[pcb.png]]

- Jsou inicializovány registry, zásobník, ...

## Ready 

- Proces je zařazen na konec fronty **FIFO**
- Pomocí dispatcheru je nahrán do procesoru (výměna všech registrů; PCB)