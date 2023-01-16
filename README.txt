# BattleShipProject implementation: note sulle secelte implementative

SCHEMA GENERALE DELLA STRUTTURA DEL PROGETTO 

TIPOLOGIE DI GIOCATORI E DIFFERENZIAZIONI

TIPOLOGIE DI NAVI E DIFFERENZIAZIONI

TIPOLOGIE DI MAPPE E DIFFERENZIAZIONI

DINAMICA DEL TURNO DI GIOCO E PARTITA 

CLASSE GAME COME CONTROLLER DI GIOCO 

MODALITA' DI GIOCO 

Come richiesto dalla consegna, una partita può essere giocata tra due computer oppure tra un utente e un computer.
Inoltre, sono disponibili funzionalità di replay, rispettivamente per la lettura di un file di log precedentemente 
creato tramite una partita (non importa di quale tipo) e per la scrittura su file di una partita (a partire da file di log). 
Per questo motivo, si è scelto di definire quattro modalità di gioco (ComputerVsComputer, PlayerVsComputer, PrintReplay, WriteReplay),
rappresentate all'interno dell'enumeratore GameMode. Il loro scopo è quello di evitare ripetizioni di codice, mantenendo uno "scheletro"
comune per la partita, e andando a distinguere a seconda dell'eseguibile scelto dall'utente.

TIPOLOGIE DI MOSSA 

STRUTTURA FILE DEL LOG E LOCAZIONE

Il file di log è composto essenzialmente da tre parti: header, comandi di aggiunta navi, mosse dei giocatori.
L'header comprende il nome dei giocatori (in ordine di partenza) e il numero di mosse stabilito all'inizio della
partita. Seguono immediatamente i comandi di aggiunta delle navi (con formato identico a quello delle mossa dei giocatori)
e, infine, le mosse effettuate ad ogni turno. 

Poichè si suppone che il file non venga ispezionato dall'utente, quanto piuttosto utilizzato esclusivamente per la modalità
replay, si è scelto di non aggiungere intestazioni o commenti all'interno del file.

I file di log vengono salvati automaticamente alla fine della partita nella cartella bin del progetto.

CONVERSIONE DA MOSSA A COPPIA DI POSIZIONI

LA CLASSE UTILITY

La classe Utility mette a disposizione metodi utilizzati da più classi e che non richiedono accesso a campi privati di queste ultime.
Per maggiori informazioni sui metodi, si vedano i commenti in Utility.h


AGGIUNTA DELLE LIBRERIE CHRONO E THREAD 

Le librerie chrono e thread si rivelano utili per rendere partite e replay fruibili dall'utente, aggiungendo pause di un secondo
prima di una mossa del computer e prima di ogni visualizzazione della mappa.

METODI DI RANDOMIZZAZIONE DELLE MOSSE 



L'USO DI FILE WRITER E REPLAY

GESTIONE DELL'INPUT DA CLI

Al fine di evitare il lancio di eccezioni legate ad un input errato, si è scelto di adottare un formato rigido di inserimento
delle mosse e dei comandi di aggiunta delle navi, indicato di seguito: [lettera][numero][spazio][lettera][numero].
Pertanto, qualsiasi altro carattere inserito prima, dopo, o all'interno del comando, renderà la mossa del giocatore non valida,
il quale sarà quindi tenuto a reinserirla. 

Tale scelta implementativa è stata mantenuta anche per la lettura dei file di log. Qualora il file di log venisse manomesso e corrotto
dopo la partita effettuata, la lettura del comando modificato risulterebbe in una terminazione dell'esecuzione del programma, segnalata
dalla dicitura di file di log corrotto.