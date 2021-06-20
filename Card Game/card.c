#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    //Structure to hold the card number, card color and value of each card.

    char card;
    char type;
    int value;
    struct node* next;
} DeckCard, *Deck; 

typedef struct Stack{
    //Structure used to represent the stack of cards on the table.

    Deck head;
    int size;
}Stack;

Deck create(char card, char type, int value) {
    //Creates a card with attributes card, type, value.

    Deck deck = malloc(sizeof(DeckCard));
    deck->card=card;
    deck->type=type;
    deck->value=value;
    deck->next = NULL;
    return deck;
}

Stack* createStack(void){
    //Function that initialises the stack.

    Stack *stack = (Stack*) malloc(sizeof(Stack));
	stack->head = NULL;
	stack->size = 0;
	return stack;
}

void push(Stack *stack, char card, char type, int value){
    //Function that pushes in the stack a node with attributes card, type, value.

    if(stack==NULL){
        return;
    }
	Deck node = malloc(sizeof(Deck));
	node->card=card;
    node->type=type;
    node->value=value;
	if(stack->head==NULL || stack==NULL){
		stack->head=node;
		node->next=NULL;
		stack->size++;
	}
	else{
		node->next=stack->head;
		stack->head=node;
		stack->size++;
	}
}

void pop(Stack *stack){
    //Function that removes the top element of the stack.
	
	if(stack->head==NULL || stack==NULL){
		return;
	}

	Deck node = stack->head;
	stack->head=stack->head->next;
	free(node);
	stack->size--;
} 

void remove_newline(char* string){
    //Function that removes the newline at the end of a string, in order to compare it with other strings.
    //There are 2 variants, for Windows and Linux.

    int n = strlen(string)-1;
    if(n>0){
        if(string[n-1]=='\r'){
            string[n-1]='\0';
        }
        else if(string[n]=='\n'){
            string[n]='\0';
        }
    }
}

int min(int a, int b){
    //Returns the smaller number between two integers.

    if(a<=b) return a;
    if(b<a) return b;
}

int length(Deck deck){
    //Calculates the number of cards in a hand.

    int i = 0;
    while(deck){
        deck=deck->next;
        i++;
    }
    return i;
}

void add_first(Deck* deck, char card, char type, int value){
    //Adds card in the beginning of the deck, useful for Monogean.

    Deck add = create(card, type, value);
    add->next=*deck;
    *deck=add;
}

Deck freeDeck(Deck deck){
    Deck iter=deck;
    Deck card;
    while(iter!=NULL){
        card=iter;
        iter=iter->next;
        free(card);
    }
    return deck;
}

Deck insert(Deck deck, char card, char type, int value){
    //Function that inserts a card at the end of the list of cards.

    if(deck==NULL){
        Deck deck = malloc(sizeof(DeckCard));
        deck->card=card;
        deck->type=type;
        deck->value=value;
        deck->next=NULL;
        return deck;
    }
    Deck temp = deck;
    Deck inter = create(card,type,value);
    while(temp->next!=NULL){
        temp=temp->next;
    }
    inter->next=temp->next;
    temp->next=inter;
    return deck;
}

Deck removeCard(Deck deck, char type){
    //Removes the first card that has the given type from a deck.
    //Function uses only the type of the card because the card anf value were not important.

    Deck counter, pointer;
    counter=deck;
    if(deck==NULL){
        return deck;
    }
    if(deck->type==type){
        deck=deck->next;
        free(counter);
        return deck;
    }
    while(counter!=NULL){
        if(counter->type==type){
            pointer->next=counter->next;
            free(counter);
            return deck;
        }
        pointer=counter;
        counter=counter->next;
    }
    if(counter->type==type){
        pointer->next=NULL;
        free(counter);
        return deck;
    }
    return deck;
}

Deck init(){
    //Function that initialises the deck with parameters card, type, value for each card.

    char type, card;
    int value;
    int i = 2;
    int j = 1;
    int k = 0;
    Deck deck = create('A', 's', 15);
    while(i<=52){
        if(j==0){
            type='s';
        }
        if(j==1){
            type='h';
        }
        if(j==2){
            type='c';
        }
        if(j==3){
            type='d';
        }
        if(k==0){
            card='A';
            value=15;
        }
        if(k==1){
            card='K';
            value=14;
        }
        if(k==2){
            card='Q';
            value=13;
        }
        if(k==3){
            card='J';
            value=12;
        }
        if(k==4){
            card='T';
            value=10;
        }
        if(k==5){
            card='9';
            value=9;
        }
        if(k==6){
            card='8';
            value=8;
        }
        if(k==7){
            card='7';
            value=7;
        }
        if(k==8){
            card='6';
            value=6;
        }
        if(k==9){
            card='5';
            value = 5;
        }
        if(k==10){
            card='4';
            value=4;
        }
        if(k==11){
            card='3';
            value=3;
        }
        if(k==12){
            card='2';
            value=2;
        }
        j++;
        if(j==4){
            j=0;
            k++;
        }
        i++;
        deck = insert(deck, card, type, value);
    }

    return deck;
}

Deck inversare(Deck deck){
    //Function used to shuffle the cards.
    //Inverses the order of the cards.

    Deck prev = NULL;
    Deck current = deck;
    Deck next = deck;
    while(current!=NULL){
        next=next->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    return prev;
}

Deck intercalare(Deck deck){
    //Function used to shuffle the cards.

    Deck head1 = deck;
    Deck copy = deck;
    Deck temp;
    int i;
    for(i=0; i<25; i++){
        copy = copy->next;
    }
    Deck head2 = copy->next;
    copy->next = NULL;
    Deck actual = create(deck->card, deck->type, deck->value);
    head1 = head1->next;
    
    //head1 is the first half of the deck
    //head2 is the second half of the deck
    //inserts the first card from the first deck then alternates betweend decks.

    for(i=1; i<52; i++){
        if(i%2 == 1){
            actual = insert(actual, head2->card, head2->type, head2->value);
            if(head2->next!=NULL) head2=head2->next;
        }
        if(i%2 == 0){
            actual = insert(actual, head1->card, head1->type, head1->value);
            if(head1->next!=NULL) head1=head1->next;
        }
    }
    return actual;
}

Deck mongean(Deck deck){
    //Function used to shuffle the cards

    Deck copy = deck->next;
    Deck actual = create(deck->card, deck->type, deck->value);
    int i;
    for(i=1; i<52; i++){
        if(i%2==0){
            //insert card at the end of the deck
            actual = insert(actual, copy->card, copy->type, copy->value);
        }
        else{
            //insert card at the beginning of the deck
            add_first(&actual, copy->card, copy->type, copy->value);
        }
        if(copy->next!=NULL) copy=copy->next;
    }
    return actual;
}

Deck npiles(Deck deck, char* string){
    //Function used to shuffle the cards

    Deck actual;
    Deck copy;
    Deck temp;
    char* pointer;
    int times;
    int nr, i=0, j;
    times = strtol(string, &pointer, 0); //how many decks will we have
    while(i<times){
        copy = deck;
        nr = strtol(pointer, &pointer, 0); // read the order of the decks 1 by 1
        for(j=0; j<(52/times)*(nr-1); j++){
            copy=copy->next;
        }
        temp=copy;
        //temp becomes the first card of the n-th pack, that has to be added.

        for(j=1; j<=52/times; j++){
            if(i==0&&j==1){
                actual = create(temp->card, temp->type, temp->value);
            }
            else{
                actual = insert(actual, temp->card, temp->type, temp->value);
            }
            temp=temp->next;
        }
        i++;
    }
    return actual;
}

void razboi(Deck deck){
    //Function that simulates the "razboi" game between two players.

    FILE *f;        
    f = fopen("out", "w");
    int v1[16] = {0}, v2[16] = {0};
    int size1, size2;
    Deck p1, p2; // the decks of both players
    Deck carte1, carte2; //the current card of each player
    Deck copy;
    Deck last1, last2;
    char to_print;
    int hands = 100;
    int turn;
    int i;

    //create the 2 decks
    p1 = create(deck->card, deck->type, deck->value);
    for(i=1; i<26; i++){
        deck = deck->next;
        p1 = insert(p1, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p2 = create(deck->card, deck->type, deck->value);
    for(i=1; i<26; i++){
        deck = deck->next;
        p2 = insert(p2, deck->card, deck->type, deck->value);
    }
    
    while(hands>0){
        //the game begins

        carte1=p1;
        carte2=p2;
        if(carte1->value>carte2->value){
            p1 = insert(p1, carte1->card, carte1->type, carte1->value);
            p1 = insert(p1, carte2->card, carte2->type, carte2->value);
            p1=p1->next;
            p2=p2->next;
        }
        else if(carte2->value>carte1->value){
            p2 = insert(p2, carte2->card, carte2->type, carte2->value);
            p2 = insert(p2, carte1->card, carte1->type, carte1->value);
            p1=p1->next;
            p2=p2->next;
        }
        else{
            //if there is war between the two players
            
            Stack *stack1 = createStack();
            Stack *stack2 = createStack();
            push(stack1, p1->card, p1->type, p1->value);
            p1=p1->next;
            push(stack2, p2->card, p2->type, p2->value);
            p2=p2->next;
            turn=min(min(length(p1), carte1->value), min(length(p2), carte2->value));
            for(i=0; i<turn; i++){
                if(i==turn-1){
                    //save the last card of each player to compare them
                    last1=p1;
                    last2=p2;
                }
                if(p1!=NULL){
                    //adds first player's card to pile
                    push(stack1, p1->card, p1->type, p1->value);
                    p1=p1->next;
                }
                if(p2!=NULL){
                    //adds second player's card to pile
                    push(stack2, p2->card, p2->type, p2->value);
                    p2=p2->next;
                }
                
            }

            //2 cases, depending on who on the war
            if(last1->value>last2->value){
                for(i=0; i<=turn; i++){
                    p1 = insert(p1, stack1->head->card, stack1->head->type, stack1->head->value);
                    pop(stack1);
                }
                for(i=0; i<=turn; i++){
                    p1 = insert(p1, stack2->head->card, stack2->head->type, stack2->head->value);
                    pop(stack2);
                }
                
            }
            else{
                for(i=0; i<=turn; i++){
                    p2 = insert(p2, stack2->head->card, stack2->head->type, stack2->head->value);
                    pop(stack2);
                }
                for(i=0; i<=turn; i++){
                    p2 = insert(p2, stack1->head->card, stack1->head->type, stack1->head->value);
                    pop(stack1);
                }
            }
        }
        size1=length(p1);
        size2=length(p2);
        hands--;
        
        if(p1==NULL){
            fprintf(f, "2");
            return;
        }
        else if(p2==NULL){
            fprintf(f, "1");
            return;
        }
    }
    size1=length(p1);
    size2=length(p2);

    //2 vectors to memorize the number of cards each player has after 100 turns
    for(i=0; i<size1; i++){
        v1[p1->value]++;
        p1=p1->next;
    }
    for(i=0; i<size2; i++){
        v2[p2->value]++;
        p2=p2->next;
    }
    //See who wins after 100 turns
    for(i=15; i>0; i--){
        if(v1[i]>v2[i]){
            if(i==15){
                to_print='A';
            }
            else if(i==14){
                to_print='K';
            }
            else if(i==13){
                to_print='Q';
            }
            else if(i==12){
                to_print='J';
            }
            else if(i==10){
                to_print='T';
            }
            else if(i==9){
                to_print='9';
            }
            else if(i==8){
                to_print='8';
            }
            else if(i==7){
                to_print='7';
            }
            else if(i==6){
                to_print='6';
            }
            else if(i==5){
                to_print='5';
            }
            else if(i==4){
                to_print='4';
            }
            else if(i==3){
                to_print='3';
            }
            fprintf(f, "%d %c", 1, to_print);
            return;
        }
        else if(v2[i]>v1[i]){
            if(i==15){
                to_print='A';
            }
            else if(i==14){
                to_print='K';
            }
            else if(i==13){
                to_print='Q';
            }
            else if(i==12){
                to_print='J';
            }
            else if(i==10){
                to_print='T';
            }
            else if(i==9){
                to_print='9';
            }
            else if(i==8){
                to_print='8';
            }
            else if(i==7){
                to_print='7';
            }
            else if(i==6){
                to_print='6';
            }
            else if(i==5){
                to_print='5';
            }
            else if(i==4){
                to_print='4';
            }
            else if(i==3){
                to_print='3';
            }
            fprintf(f, "%d %c", 2, to_print);
            fclose(f);
            return;
        }
    }
}

void stone(Deck deck){
    //Function that simulates the "Rolling Stone" game between two players.

    FILE *f;        
    f = fopen("out", "w");

    Stack *stack = createStack();
    char next;
    Deck p1, p2, p3, p4; //decks of all players
    int i;
    int counter=0;
    int size1, size2, size3, size4;

    //create the 4 decks
    p1 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p1 = insert(p1, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p2 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p2 = insert(p2, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p3 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p3 = insert(p3, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p4 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p4 = insert(p4, deck->card, deck->type, deck->value);
    }
    next='d';
    Deck first, copy;
    int foundFirst, down;
    while(p1||p2||p3||p4){
        
        //until one player wins
        //the main code repeats four times so i will comment only the first one
        size1=length(p1);
        size2=length(p2);
        size3=length(p3);
        size4=length(p4);

        if(counter%4==0){
            //in case it's the first player's turn
            if(stack->head==NULL){
                //if the player adds the first card to a pile
                foundFirst=0;
                while(foundFirst==0){
                    copy=p1;
                    //calculates which is the next type of card to be played
                    if(next=='d') next='s';
                    else if(next=='s') next='h';
                    else if(next=='h') next='c';
                    else if(next=='c') next='d';
                    for(i=0; i<length(p1); i++){
                        //search the deck for the first card of that type
                        if(copy->type==next){
                            foundFirst=1;
                            first=copy;
                            break;
                        }
                        copy=copy->next;
                    }
                }
                //add card to pile and remove it from deck
                push(stack, first->card, first->type, first->value);
                p1 = removeCard(p1, first->type);
                if(p1==NULL){
                    //if the player is out of cards, he wins
                    fprintf(f, "%d", 1);
                    return;
                }
                
            }
            else{
                //if there are cards in the pile
                copy=p1;
                down=0;
                for(i=0; i<length(p1); i++){
                    //search the deck for the first card of that type
                    if(copy->type==stack->head->type){
                        push(stack, copy->card, copy->type, copy->value);
                        p1 = removeCard(p1, copy->type);
                        if(p1==NULL){
                            fprintf(f, "%d", 1);
                            return;
                        }
                        
                        down=1;
                        break;
                    }
                    copy=copy->next;
                }
                if(down==0){
                    //the case in which the player didnt have that type of card
                    while(stack->head!=NULL){
                        //take all the cards
                        p1 = insert(p1, stack->head->card, stack->head->type, stack->head->value);
                        pop(stack);
                    }
                }
            }
        }
        if(counter%4==1){
            //in case it's the second player's turn
            if(stack->head==NULL){
                foundFirst=0;
                while(foundFirst==0){
                    copy=p2;
                    if(next=='d') next='s';
                    else if(next=='s') next='h';
                    else if(next=='h') next='c';
                    else if(next=='c') next='d';
                    for(i=0; i<length(p2); i++){
                        if(copy->type==next){
                            foundFirst=1;
                            first=copy;
                            break;
                        }
                        copy=copy->next;
                    }
                }
                push(stack, first->card, first->type, first->value);
                p2 = removeCard(p2, first->type);
                if(p2==NULL){
                    fprintf(f, "%d", 2);
                    return;
                }
                
            }
            else{
                copy=p2;
                down=0;
                for(i=0; i<length(p2); i++){
                    if(copy->type==stack->head->type){
                        push(stack, copy->card, copy->type, copy->value);
                        p2 = removeCard(p2, copy->type);
                        if(p2==NULL){
                            fprintf(f, "%d", 2);
                            return;
                        }
                        
                        down=1;
                        break;
                    }
                    copy=copy->next;
                }
                if(down==0){
                    while(stack->head!=NULL){
                        p2 = insert(p2, stack->head->card, stack->head->type, stack->head->value);
                        pop(stack);
                    }
                }
            }
        }
        if(counter%4==2){
            //in case it's the three player's turn
            if(stack->head==NULL){
                foundFirst=0;
                while(foundFirst==0){
                    copy=p3;
                    if(next=='d') next='s';
                    else if(next=='s') next='h';
                    else if(next=='h') next='c';
                    else if(next=='c') next='d';
                    for(i=0; i<length(p3); i++){
                        if(copy->type==next){
                            foundFirst=1;
                            first=copy;
                            break;
                        }
                        copy=copy->next;
                    }
                }
                push(stack, first->card, first->type, first->value);
                p3 = removeCard(p3, first->type);
                if(p3==NULL){
                    fprintf(f, "%d", 3);
                    return;
                }
                
            }
            else{
                copy=p3;
                down=0;
                for(i=0; i<length(p3); i++){
                    if(copy->type==stack->head->type){
                        push(stack, copy->card, copy->type, copy->value);
                        p3 = removeCard(p3, copy->type);
                        if(p3==NULL){
                            fprintf(f, "%d", 3);
                            return;
                        }
                        
                        down=1;
                        break;
                    }
                    copy=copy->next;
                }
                if(down==0){
                    while(stack->head!=NULL){
                        p3 = insert(p3, stack->head->card, stack->head->type, stack->head->value);
                        pop(stack);
                    }
                }
            }
        }
        if(counter%4==3){
            //in case it's the fourth player's turn
            if(stack->head==NULL){
                foundFirst=0;
                while(foundFirst==0){
                    copy=p4;
                    if(next=='d') next='s';
                    else if(next=='s') next='h';
                    else if(next=='h') next='c';
                    else if(next=='c') next='d';
                    for(i=0; i<length(p4); i++){
                        if(copy->type==next){
                            foundFirst=1;
                            first=copy;
                            break;
                        }
                        copy=copy->next;
                    }
                }
                push(stack, first->card, first->type, first->value);
                p4 = removeCard(p4, first->type);
                if(p4==NULL){
                    fprintf(f, "%d", 4);
                    return;
                }
                
            }
            else{
                copy=p4;
                down=0;
                for(i=0; i<length(p4); i++){
                    if(copy->type==stack->head->type){
                        push(stack, copy->card, copy->type, copy->value);
                        p4 = removeCard(p4, copy->type);
                        if(p4==NULL){
                            fprintf(f, "%d", 4);
                            return;
                        }
                        
                        down=1;
                        break;
                    }
                    copy=copy->next;
                }
                if(down==0){
                    while(stack->head!=NULL){
                        p4 = insert(p4, stack->head->card, stack->head->type, stack->head->value);
                        pop(stack);
                    }
                }
            }
        }
        if(stack->head!=NULL) counter++;
        if(counter==4){
            counter=0;
        }
    }
    fclose(f);
}

void scarabei(Deck deck){
    //Function that simulates the "Scarabeii Egipteni" game between two players.
    //value>=12 means scarabeu
    //value = 8 means magic card
    //else, the card is basic

    FILE *f;        
    f = fopen("out", "w");
    Deck p1, p2, p3, p4;
    Stack *stack = createStack();
    int i, sens=1, counter=0;
    int p1elim=0, p2elim=0, p3elim=0, p4elim=0; //p elim=0 means the player is still in the game
    int winner; //used to see who played the last scarabeu
    int end=0;
    //initialise the 4 decks
    p1 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p1 = insert(p1, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p2 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p2 = insert(p2, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p3 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p3 = insert(p3, deck->card, deck->type, deck->value);
    }
    deck=deck->next;
    p4 = create(deck->card, deck->type, deck->value);
    for(i=1; i<13; i++){
        deck = deck->next;
        p4 = insert(p4, deck->card, deck->type, deck->value);
    }
    while(end==0){
        
        //Player is eliminated if he is out of cards and has no chance to win a card
        if(p1==NULL && winner!=0) p1elim=1;
        if(p2==NULL && winner!=1) p2elim=1;
        if(p3==NULL && winner!=2) p3elim=1;
        if(p4==NULL && winner!=3) p4elim=1;
        
        //Checks if any of the win conditions are achieved
        if(p1elim&&p2elim&&p3elim){
            fprintf(f, "%d", 4);
            end=1;
            return;
        }
        if(p2elim&&p3elim&&p4elim){
            fprintf(f, "%d", 1);
            end=1;
            return;
        }
        if(p1elim&&p3elim&&p4elim){
            fprintf(f, "%d", 2);
            end=1;
            return;
        }
        if(p1elim&&p2elim&&p4elim){
            fprintf(f, "%d", 3);
            end=1;
            return;
        }
        //the main code repeats four times so i will comment only the first one
        if(counter%4==0 && p1elim==0){
            //in case it's the first player's turn
            if((stack->head!=NULL && stack->head->value>=12) || (stack->head!=NULL && stack->head->value==8 && winner!=5)){
                //if there is a scarabeu or a magic card that was played after a scarabeu was played
                if(p1->value>=12){
                    //if the player plays a scarabeu he has the win condition for that hand
                    winner=0;
                    push(stack, p1->card, p1->type, p1->value);
                    p1=p1->next;
                }
                else if(p1->value==8){
                    //if the player plays a magic card nothing happens
                    push(stack, p1->card, p1->type, p1->value);
                    p1=p1->next;
                }
                else if(p1->value<=10 && p1->value!=8){
                    //if the player plays a normal card, the last player who played scarabeu takes the cards
                    push(stack, p1->card, p1->type, p1->value);
                    if(winner==0){
                        //if the last player to play scarabeu was the first player
                        while(stack->head!=NULL){
                            p1 = insert(p1, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=0;
                    }
                    if(winner==1){
                        //if the last player to play scarabeu was the second player
                        while(stack->head!=NULL){
                            p2 = insert(p2, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=1;
                    }
                    if(winner==2){
                        //if the last player to play scarabeu was the third player
                        while(stack->head!=NULL){
                            p3 = insert(p3, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=2;
                    }
                    if(winner==3){
                        //if the last player to play scarabeu was the fourth player
                        while(stack->head!=NULL){
                            p4 = insert(p4, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=3;
                    }
                    p1=p1->next;
                }
            }
            else if(stack->head==NULL || stack->head->value<=10){
                //if there was no scarabeu played
                if(p1->value>=12) winner=0; //if player plays scarabeu, he has the win condition for that hand
                else if(p1->value==8) sens*=-1; //if player plays magic card, the order of the players switches
                push(stack, p1->card, p1->type, p1->value);
                p1=p1->next;
            }
        }

        else if(counter%4==1 && p2elim==0){
            //in case it's the second player's turn
            if((stack->head!=NULL && stack->head->value>=12) || (stack->head!=NULL && stack->head->value==8 && winner!=5)){
                if(p2->value>=12){
                    winner=1;
                    push(stack, p2->card, p2->type, p2->value);
                    p2=p2->next;
                }
                else if(p2->value==8){
                    push(stack, p2->card, p2->type, p2->value);
                    p2=p2->next;
                }
                else if(p2->value<=10 && p2->value!=8){
                    push(stack, p2->card, p2->type, p2->value);
                    if(winner==0){
                        while(stack->head!=NULL){
                            p1 = insert(p1, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=0;
                    }
                    if(winner==1){
                        while(stack->head!=NULL){
                            p2 = insert(p2, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=1;
                    }
                    if(winner==2){
                        while(stack->head!=NULL){
                            p3 = insert(p3, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=2;
                    }
                    if(winner==3){
                        while(stack->head!=NULL){
                            p4 = insert(p4, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=3;
                    }
                    p2=p2->next;
                }
            }
            else if(stack->head==NULL || stack->head->value<=10){
                if(p2->value>=12) winner=1;
                else if(p2->value==8) sens*=-1;
                push(stack, p2->card, p2->type, p2->value);
                p2=p2->next;
            }
        }

        else if(counter%4==2 && p3elim==0){
            //in case it's the third player's turn
            if((stack->head!=NULL && stack->head->value>=12) || (stack->head!=NULL && stack->head->value==8 && winner!=5)){
                if(p3->value>=12){
                    winner=2;
                    push(stack, p3->card, p3->type, p3->value);
                    p3=p3->next;
                }
                else if(p3->value==8){
                    push(stack, p3->card, p3->type, p3->value);
                    p3=p3->next;
                }
                else if(p3->value<=10 && p3->value!=8){
                    push(stack, p3->card, p3->type, p3->value);
                    if(winner==0){
                        while(stack->head!=NULL){
                            p1 = insert(p1, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=0;
                    }
                    if(winner==1){
                        while(stack->head!=NULL){
                            p2 = insert(p2, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=1;
                    }
                    if(winner==2){
                        while(stack->head!=NULL){
                            p3 = insert(p3, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=2;
                    }
                    if(winner==3){
                        while(stack->head!=NULL){
                            p4 = insert(p4, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=3;
                    }
                    p3=p3->next;
                }
            }
            else if(stack->head==NULL || stack->head->value<=10){
                if(p3->value>=12) winner=2;
                else if(p3->value==8) sens*=-1;
                push(stack, p3->card, p3->type, p3->value);
                p3=p3->next;
            }
        }

        else if(counter%4==3 && p4elim==0){
            //in case it's the fourth player's turn
            if((stack->head!=NULL && stack->head->value>=12) || (stack->head!=NULL && stack->head->value==8 && winner!=5)){
                if(p4->value>=12){
                    winner=3;
                    push(stack, p4->card, p4->type, p4->value);
                    p4=p4->next;
                }
                else if(p4->value==8){
                    push(stack, p4->card, p4->type, p4->value);
                    p4=p4->next;
                }
                else if(p4->value<=10 && p4->value!=8){
                    push(stack, p4->card, p4->type, p4->value);
                    if(winner==0){
                        while(stack->head!=NULL){
                            p1 = insert(p1, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=0;
                    }
                    if(winner==1){
                        while(stack->head!=NULL){
                            p2 = insert(p2, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=1;
                    }
                    if(winner==2){
                        while(stack->head!=NULL){
                            p3 = insert(p3, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=2;
                    }
                    if(winner==3){
                        while(stack->head!=NULL){
                            p4 = insert(p4, stack->head->card, stack->head->type, stack->head->value);
                            pop(stack);
                        }
                        winner=5;
                        counter=3;
                    }
                    p4=p4->next;
                }
            }
            else if(stack->head==NULL || stack->head->value<=10){
                if(p4->value>=12) winner=3;
                else if(p4->value==8) sens*=-1;
                push(stack, p4->card, p4->type, p4->value);
                p4=p4->next;
            }
        }
        //counter changes if stack isnt null, so no one won the hand yet.
        if(stack->head!=NULL && sens==1) counter++;
        else if(stack->head!=NULL && sens==-1) counter--;
        if(counter==4){
            counter=0;
        }
        if(counter==-1){
            counter=3;
        }
    }
    fclose(f);
}

int main(){

    FILE *fi;
    FILE *fo;        
    fi = fopen("in", "r");
    fo = fopen("out", "w");

    Deck deck = init(); //initialise the deck
    Deck copy;

    char task[255];
    fgets(task, 255, fi);
    int i = 0;
    remove_newline(task); //used to compare the string

    char line[255];
    fgets(line, 255, fi);
    int times;
    times=atoi(line); //read how many shuffles must be done

    char *pointer;

    while(times>0){
        fgets(line, 255, fi); //read the type of shuffle that must be performed
        remove_newline(line);
        if(strcmp(line, "inversare")==0){
            deck = inversare(deck);
        }
        else if(strcmp(line, "intercalare")==0){
            deck = intercalare(deck);
        }
        else if(strcmp(line, "mongean")==0){
            deck = mongean(deck);
        }
        else{
            pointer=strchr(line, ' ');
            deck = npiles(deck, pointer);
        }
        times--;
    }
    //The tasks are executed here

    copy = deck;

    if(strcmp(task, "amestecare")==0){
        for(i=1; i<=52; i++){
            fprintf(fo, "%c%c ", copy->card, copy->type);
            copy=copy->next;
        }
    }
    else if(strcmp(task, "razboi")==0) razboi(copy);
    else if(strcmp(task, "rollingstone")==0) stone(copy);
    else if(strcmp(task, "scarabei")==0) scarabei(copy);

    deck = freeDeck(deck);

    fclose(fi);
    fclose(fo);
    return 0;
}