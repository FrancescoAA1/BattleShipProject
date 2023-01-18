# BattleShipProject implementation: note sulle secelte implementative

AUTORI: Mattia Galassi, Enrico Disarò, Francesco Fantin

NOTA GESTIONE DELL'INPUT DA CLI

Al fine di evitare il lancio di eccezioni legate ad un input errato, si è scelto di adottare un formato rigido di inserimento
delle mosse e dei comandi di aggiunta delle navi, indicato di seguito: [lettera][numero][spazio][lettera][numero].
Pertanto, qualsiasi altro carattere inserito prima, dopo, o all'interno del comando, renderà la mossa del giocatore non valida,
il quale sarà quindi tenuto a reinserirla. 

Tale scelta implementativa è stata mantenuta anche per la lettura dei file di log. Qualora il file di log venisse manomesso e corrotto
dopo la partita effettuata, la lettura del comando modificato risulterebbe in una terminazione dell'esecuzione del programma, segnalata
dalla dicitura di file di log corrotto.