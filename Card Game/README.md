# Shuffle and Play! - By Koleci Alexandru, 313CD

Program care simuleaza amestecarea pachetului de carti in patru moduri si jocul dintre mai multi jucatori pentru 3 jocuri diferite.
Am folosit structura Deck pentru a pastra pachetul de carti al fiecarui jucator.
Fiecare carte de joc este de tip Deck, are atributele card, type, value si un pointer catre urmatoarea carte din pachet.
Pentru a memora teancul de carti de pe masa la jocuri am folosit o structura de tip Stack, care retine carti de tip Deck.

## Main

Se deschid fisierele in si out, din out citim prima linie pentru a vedea ce task avem (amestecare/unul din jocuri)
Se citeste numarul de amestecari care trebuie efectuate
Se citesc tipurile de amestecari, pt fiecare se aplica functia respectiva asupra pachetului 
In functie de numele taskului, este scris pachetul sau se simuleaza unul din jocuri
La final eliberez memoria cu functia freeDeck

## Shuffles

Cele patru tipuri de amestecari sunt:

### Inversare

Se trece la dreapta cu pozitia de start din carte in carte, iar cartile de la inceput devin cele de dupa cea mai din dreapta.

### Intercalare

Se imparte pachetul in 2 pachete de 26 de carti
Cu prima carte din primul pachet initializez pachetul
Pe rand, adaug care o carte din al doilea pachet si cate o carte din primul.

### Mongean

Initializez pachetul cu prima carte din pachet
Se adauga cate o carte la inceput folosind functia add_first si una la final cu functia insert.

### Npiles

Citesc numarul de pachete si dupa ordinea in care trebuie puse
Pentru fiecare nr de ordine, caut primul pachet din acel sub-pachet si adaug toate elementele la pachetul principal

## Games

Cele trei jocuri care pot fi jucate dupa ce pachetul a fost amestecat

### Razboi

Se apeleaza functia razboi, care simuleaza jocul dintre 2 jucatori.
Sunt initializate cele doua pachete ale jucatorilor
Cat timp nu s-au jucat 100 de ture:
Fiecare jucator pune jos prima carte. Cel cu cartea mai mare ia ambele carti
Daca au acelasi numar de carti, se declara "razboi" si folosesc stiva pentru a salva cartile jucate
Compar ultimele carti jucate la razboi, si castigatorul ia pe rand toate cartile din stiva.
Daca dupa 100 de ture jocul nu se termina folosesc 2 vectori de frecventa pentru a salva nr de carti in functie de valori.

### Rolling Stone

Se apeleaza functia rollingstone, care simuleaza jocul dintre 4 jucatori
Sunt initializate cele 4 pachete ale jucatorilor
Am folosit un contor pentru a decide care jucator este la rand
Daca nu a fost jucata o carte:
    Se cauta, conform ordinii s->h->c->d, prima carte care poate fi jucata si se joaca
    Cartea este scoasa din pachete cu functia removeCard si adaugata in stiva cu functi push
Daca a fost jucata o carte: 
    Se cauta prima carte de culoarea primei carti din stiva.
    Daca e gasita, se adauga la stack si se scoate din deck.
    Daca nu e gasita, jucatorul ia toate cartile de jos
Daca pachetul este gol, jucatorul castiga.
Contorul creste daca teancul de jos nu e gol. Daca e gol, pierzatorul incepe.

### Scarabeii Egipteni

Se apeleaza functia scarabei, care simuleaza jocul dintre 4 jucatori
Sunt initializate cele 4 pachete ale jucatorilor
Am folosit un contor pentru a decide care jucator este la rand
In variabila winner retin cine a pus ultimul scarabeu
Dupa ce cineva castiga o mana, winner devine 5, valoare la care nu se poate ajunge, ca sa nu ma incurc
Scarabeu: player->value>=12
Magic card: player->value=8;
Normal card: restul
Daca este randul unui jucator neeliminat
Daca cartea de sus e scarabeu sau sunt carti de 8 care au urmat dupa un scarabeu:
    Daca prima carte din pachetul jucatorului e scarabeu, se pune jos si win conditionul este al lui.
    Daca prima carte din pachetul jucatorului e magic card, se pune jos si se continua
    Daca prima carte din pachetul jucatorului e normal card, ultimul jucator care a pus un scarbeu (winner=player number) ia cartile
    Tot cel care a luat cartile va incepe (daca stack e NULL contorul nu se schimba)
Daca cartea de sus nu e scarabeu sau daca nu s-a jucat nimic inca:
    Daca prima carte din pachetul jucatorului e scaraveu, se pune jos si win conditionul e al lui
    Daca prima carte din pachetul jucatorului e magic card, se va inversa ordinea jucatorilor
Daca jucatorul nu mai are carti si nici sanse sa ia carti (winner!=nr player), e eliminat(se updateaza variabilele p1elim, p2elim, p3elim, p4elim)
Jucatorul care ia toate cartile adversarilor castiga;