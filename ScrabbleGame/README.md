Inainte de a incepe orice task, initializez tabla de joc si o umplu de '.'
Dupa aceea, citesc numarul taskului, prin functia get_number().
get_number(): - citesc linia intr un vector folosind fgets
              - transform linia citita in numar folosind strtol

Task0 - Doar printez tabla de joc folosind functia print_board()

Task1 
    Citesc numarul de linii cu functia get_number().
    Citesc fiecare linie cu fgets().
    Pentru a separa variabilele, am ales sa folosesc functia strtol de 3 ori.
    Am ales strtol pentru ca imi ignora automat spatiile si transforma in int.
    Astfel se citeste prima valoare si pointerul este mutat cu 1 dupa valoare.
    Apoi se ignora whitespace pana la urmatorul caracter, si tot asa.
    La final, pentru ca pointerul sa fie cuvantul, mut pointerul la dreapta.
    Iau pe rand elementele din pointer si, daca sunt litere, le adaug la tabla.
    Acest lucru il fac cu isalpha() care verifica daca un caracter e litera.
    Adaugarea pe tabla se face pana dam de '\n', pus la final de fgets().
    In final, printez tabla.

Task2 
    Fac acelasi lucru ca la Task1, dar cand citesc un cuvant ii calculez scorul
    Functia add_scores() atribuie punctajul corect fiecarei litere.
    In functie de numarul liniei (adica al jucatorului), adun scorul cuvantului
    Ca sa aflu scorul folosesc score[litera - 'A']
    In final, printez cele 2 scoruri

Task3
    Pe langa ce citeam deja, mai citim 2 linii, cele pentru bonusuri, cu fgets.
    La fiecare cuvant citit verific cat de 1 si de 2 sunt sub el pe tabla bonus
    Dupa aceea aflu scorul cuvantului respectiv
    Verific daca conditiile bonus se indeplinesc, caz in care calculez bonusul.
    La scorul jucatorilor se adauga scorul cuvantului lor, inmultit cu bonusul.
    In final, printez cele 2 scoruri.

Task4
    Aflu cate litere are fiecare cuvant din words[][]
    Dupa fiecare cuvant citit, verific daca acesta se afla in words.
    Folosesc 2 conditii: sa aiba aceeasi lungime si sa fie identice.
    Dupa, iau pe rand toate cuvintele din words, cele folosite fiind ignorate.
    Iau casutele pe rand pana cand gasesc o casuta cu prima litera a cuvantului
    De acolo, verific daca poate fi pus pe orizontala si/sau pe verticala.
    Daca poate fi pus pe ambele, aleg sa fie pus pe orizontala.
    Daca gasesc pe orizontala, dau return, adica nu se ajunge la verticala.
    Inainte de a da return, printez tabla cu noul cuvant adaugat.

Task5 
    Ca la Task3, calculez scorul celor 2 jucatori.
    In plus, verific ce cuvinte au fost folosite. Parcurg cuvintele din words.
    Caut prima casuta cu prima litera a cuvantului.
    Verific daca tot cuvantul poate fi adaugat pe orizontala/verticala.
    Dupa aceea, calculez scorul cuvantului care ar putea fi adaugat.
    Scorul maxim al cuvantului este salvat, precum si coordonatele cuvantului.
    La final, verific care a fost scorul maxim si adaug acel cuvant la tabla.
    
    
