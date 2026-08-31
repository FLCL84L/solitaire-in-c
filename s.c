#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

// game v2 -> latest

struct Card {
	char rank;
	char suit;
	int color;
	char face;
};

struct Node {
	struct Card *data;
	struct Node *next;
};

// inserts a char in a list (creates node))
void insertNode(struct Node *head, char rank, char suit, int color, char face){
	struct Node *temp = head;
	struct Node *new = malloc(sizeof(struct Node));
	struct Card *newCard = malloc(sizeof(struct Card));
	newCard->rank = rank;
	newCard->suit = suit;
	newCard->color = color;
	newCard->face = face;
	new->data = newCard;
	new->next = NULL;

	while(temp->next != NULL){
		temp = temp->next;
	}

	temp->next = new;
}

// prints all nodes from list
void printNode(struct Node *head){
	struct Node *temp = head;

	while(temp->next != NULL){
		temp = temp->next;
		//printf("%c\tfaceChar: %c\tfaceInt: %d\n", temp->data->rank, temp->data->face, temp->data->face);
		printf("%c\n", temp->data->rank);
	}
}

// printNode with style
void printCards(struct Node *head){
	struct Node *temp = head;
	printf("Cards:\n");

	while(temp->next != NULL){
		temp = temp->next;
		printf("\t");
		printf("\x1b[47m\x1b[%dm\033[1m",temp->data->color);
		printf(" %c %c ",temp->data->rank, temp->data->suit);
		printf("\033[0m\n");
	}
	printf("\n");
}

// returns how many nodes with value on a list
int lengthNode(struct Node *head){
	struct Node *temp = head;
	int length = 0;

	while(temp->next != NULL){
		length++;
		temp = temp->next;
	}
	return length;
}

void printTable(struct Node **t, int from){
	int c = 0;
	int cw = 0;
	int wl;
	printf("TABLE:\n");
	printf("\t  2");
	for(int i=0; i < 6;i++){
		printf("         %d", i+3);
	}
	printf("\n");
	struct Node **aux = malloc(sizeof(struct Node *)*7);
	for(int i = 0; i < 7; i++){
		aux[i] = malloc(sizeof(struct Node));
		aux[i]->next = t[i+1]->next;
	}
	if(from != -1)
		wl = lengthNode(aux[from]);

	while(c<7){
		cw++;
		c = 0;
		printf("\t");
		for(int i = 0; i < 7; i++){
			if(aux[i]->next == NULL){
				c++;
				printf("     ");
			} else {
				aux[i] = aux[i]->next;
				if(aux[i]->data->face == 49){
					printf("\x1b[47m\x1b[%dm\033[1m",aux[i]->data->color);
					printf(" %c %c ", aux[i]->data->rank, aux[i]->data->suit);
				} else {
					printf("\x1b[43m");
					printf("     ");
				}
				printf("\033[0m");
			}
			if(from == i && cw <= wl && aux[i]->data->face == 49){
				printf("%d    ", wl-cw+1);
			} else {
				printf("     ");
			}
		}
		printf("\n");
	}
}

void displayTop(struct Node **f){
	struct Node *temp = f[0];
	struct Node *f8 = f[8];
	struct Node *f9 = f[9];
	struct Node *f10 = f[10];
	struct Node *f11 = f[11];
	int fl[4];
	fl[0] = lengthNode(f8);
	fl[1] = lengthNode(f9);
	fl[2] = lengthNode(f10);
	fl[3] = lengthNode(f11);

	while(f8->next != NULL){
		f8 = f8->next;
	}
	while(f9->next != NULL){
		f9 = f9->next;
	}
	while(f10->next != NULL){
		f10 = f10->next;
	}
	while(f11->next != NULL){
		f11 = f11->next;
	}
	while(temp->next != NULL){
		temp = temp->next;
	}
	printf("BOARD:\n\t\t    1\t      9\t        10\t  11\t    12\n\t");
	printf("\x1b[43m");
	printf("     ");
	printf("\033[0m");
	printf("     ");
	printf("\x1b[47m\x1b[%dm\033[1m", temp->data->color);
	printf(" %c %c ", temp->data->rank, temp->data->suit);
	printf("\033[0m");

	printf("     ");
	if(fl[0] == 0){
		printf("-----");
	} else {
		printf("\x1b[47m\x1b[%dm\033[1m", f8->data->color);
		printf(" %c %c ",f8->data->rank, f8->data->suit);
		printf("\033[0m");
	}
	printf("     ");
	if(fl[1] == 0){
		printf("-----");
	} else {
		printf("\x1b[47m\x1b[%dm\033[1m", f9->data->color);
		printf(" %c %c ",f9->data->rank, f9->data->suit);
		printf("\033[0m");
	}
	printf("     ");
	if(fl[2] == 0){
		printf("-----");
	} else {
		printf("\x1b[47m\x1b[%dm\033[1m", f10->data->color);
		printf(" %c %c ",f10->data->rank, f10->data->suit);
		printf("\033[0m");
	}
	printf("     ");
	if(fl[3] == 0){
		printf("-----");
	} else {
		printf("\x1b[47m\x1b[%dm\033[1m", f11->data->color);
		printf(" %c %c ",f11->data->rank, f11->data->suit);
		printf("\033[0m");
	}

	printf("\n\n\n");
}

int cycle(struct Node **head){
	struct Node *temp = head[0];
	struct Node *aux = head[0];
	struct Node *first;

	if(temp->next == NULL || temp->next->next == NULL) return 1;
	
	while(temp->next->next != NULL){
		temp = temp->next;
	}
	first = temp->next;
	first->next = aux->next;
	aux->next = first;
	temp->next = NULL;
	return 0;
}

// free mem of all nodes from list
void freeNode(struct Node *head){
	struct Node *temp = head;
	struct Node *f;

	while(temp->next != NULL){
		f = temp;
		temp = temp->next;
		free(f->data);
		free(f);
	}
	free(temp->data);
	free(temp);
}


// delete/pop by index and by rank+suit

// o ponteiro q recebe esta função ira apontar para um node que foi removido da lista. primeiro node com valor tem index = 1.
struct Node *deleteByIndex(struct Node *head, int index){
	struct Node *temp = head;
	struct Node *reNode = NULL;
	int counter = 0;

	while(temp->next != NULL){
		counter++;
		if(index == counter){
			reNode = temp->next;
			temp->next = temp->next->next;
			break;
		}
		temp = temp->next;
	}
	return reNode; // se retornar NULL nao encontrou o index
}

// retorna o endereço de um node pelo index (para o ponteiro q recebe esta função poder ver o coteudo)
struct Node *getNodeByIndex(struct Node *head, int index){
	struct Node *temp = head;
	if(index == 0){
		return temp;
	}
	struct Node *reNode;
	int counter = 0;


	while(temp->next != NULL){
		counter++;
		if(index == counter){
			reNode = temp->next;
			break;
		}
		temp = temp->next;
	}
	return reNode;
}

// embaralha a lista de nodes ordenada 
void shuffleNode(struct Node *head){
	struct Node *shuffle = malloc(sizeof(struct Node));
	struct Node *temp;
	shuffle->next = NULL;
	
	// Random Order Variables
	int *newOrder = malloc(sizeof(int) * 52);
	int length = 0;
	int exists = 0;
	int r;


	// seed the random
	srand(time(NULL));

	// Create Random Order:
	while(length != 52){
		r = (rand()%52)+1;
		exists = 0;
		for(int i = 0; i < length; i++){
			if(newOrder[i] == r){
				exists = 1;
				break;
			}
		}
		if(exists == 0){
			newOrder[length] = r;
			length++;
		}
	}


	// newOrder is the shuffled order (vector of size 52)
	
	for(int i = 0; i<52; i++){
		temp = getNodeByIndex(head, newOrder[i]); // temp aponta para um node da lista em ordem com base no index
		insertNode(shuffle, temp->data->rank, temp->data->suit, temp->data->color, temp->data->face); // e um node eh criado na shuffle com o char que esta em data do node que temp aponta
	}

	temp = head->next;
	head->next = shuffle->next;
	shuffle->next = temp;
	freeNode(shuffle); // free na mem com a lista de nodes em ordem (sobra apenas a lista embaralhada)
}

void switchCard(struct Node *head, struct Node *dest){
	struct Node *temp = dest;
	
	while(temp->next != NULL){
		temp = temp->next;
	}

	temp->next = head->next;
	head->next = head->next->next;
	temp->next->next = NULL;
}

void turnLast(struct Node *head){
	struct Node *temp = head;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->data->face = '1';
}	


// new move function:::

int move(struct Node *head, struct Node *dest, int n,char *rank, int which){
	//return 0 = success;
	//return 1 = fail;
	struct Node *to = dest;
	struct Node *from = head;
	struct Node *toHead = dest;
	struct Node *face;
	int c;
	char v;
	int w = which;
	int flag;
	if(w == -1){
		w=0;
	} else {
		w = w-1;
	}

	for(int i = 0; i<n-1-w;i++){
		from = from->next;
	}
	if(from->next->data->rank == rank[12] && lengthNode(to) == 0){
		from->next->data->face = 49;
		to->next = from->next;
		//face = temp->next;
		from->next = NULL;
		return 0;
	}
	while(to->next != NULL){
		to = to->next;
	}
	for(int i = 0; i < 13; i++){
		if(rank[i] == to->data->rank){
			if(i == 0){
				return 1;
			} else {
				c = to->data->color;
				v = rank[i-1];
				break;
			}
		}
	}
	if(v != from->next->data->rank || from->next->data->color == c){
		return 1;
	}

	// ERROR IS HERE (down)
	//if(from->data->face == 48 && from->data != NULL)// se if from face down then face up
		//from->data->face = 49;

	//from->next->data->face = 49;
	from->next->data->face = 49;
	to->next = from->next;

	//face = to->next;
	from->next = NULL;
	if(lengthNode(head) > 1){
		from->data->face = 49;
	}
	return 0;
}


////
///
///

// old move funtion:::
/*
int move(struct Node *head, struct Node *dest, int n,char *rank, int which){
	//return 0 = success;
	//return 1 = fail;
	struct Node *temp = dest;
	struct Node *aux = head;
	struct Node *toHead = dest;
	struct Node *face;
	int c;
	char v;
	int w = which;
	if(w == -1){
		w=0;
	} else {
		w = w-1;
	}
	
	for(int i = 0; i<n-1-w;i++){
		aux = aux->next;
	}
	if(aux->next->data->rank == rank[12] && lengthNode(temp) == 0){
		aux->next->data->face = 49;
		temp->next = aux->next;
		//face = temp->next;
		aux->next = NULL;
		return 0;
	}
	while(temp->next != NULL){
		temp = temp->next;
	}
	for(int i = 0; i < 13; i++){
		if(rank[i] == temp->data->rank){
			if(i == 0){
				return 1;
			} else {
				c = temp->data->color;
				v = rank[i-1];
				break;
			}
		}
	}
	if(v != aux->next->data->rank || aux->next->data->color == c){
		return 1;
	}

	if(aux->data->face == 48)// se if aux face down then face up
		aux->data->face = 49;
	aux->next->data->face = 49;
	temp->next = aux->next;
	//face = temp->next;
	aux->next = NULL;
	return 0;
}
*/

int moveF(struct Node *head, struct Node *dest, char *ranks){
	struct Node *to = dest;
	struct Node *from = head;
	int flen = lengthNode(to);
	int fromlen = lengthNode(from);

	if(from->next == NULL || flen > 12){
		return 1;
	}
	while(from->next->next != NULL){
		from = from->next;
	}

	if(flen == 0){
		if(from->next->data->rank == ranks[0]){
			to->next = from->next;
			from->next = NULL;
			if(fromlen > 1)
				from->data->face = 49;
			return 0;
		}
	}else if(from->next->data->rank == ranks[flen] && from->next->data->suit == to->next->data->suit){
		while(to->next != NULL){
			to = to->next;
		}
		to->next = from->next;
		from->next = NULL;
		if(fromlen > 1)
			from->data->face = 49;
		return 0;
	}
	return 1;
}


	
// main function
int main(){
	int res; // response/result from functions ( 0 good 1 bad)

	// ponteiro duplo com 12 heads;
	// h[0] = deck
	// h[1~7] = tableaus
	// h[8~11] = foundations
	
	struct Node **h = malloc(sizeof(struct Node *)*12);
	for(int i = 0; i < 12; i++){
		h[i] = malloc(sizeof(struct Node));
		h[i]->next = NULL;
		h[i]->data = NULL;
	}

	// ranks suits and colors
	char ranks[14] = "A23456789XJQK\0";
	char suits[5] = "$%@*\0";
	char red[24] = "\x1b[47m\x1b[31m\033[1m\0u";
	char black[24] = "\x1b[47m\x1b[30m\033[1m\0";
	int color;
	// deck creation
	for(int i = 0; i < 4; i++){
		if(i%2 == 0){
		       	color = 31;
		} else {
			color = 30;
		}
			
		for(int j = 0; j < 13; j++){
			insertNode(h[0], ranks[j], suits[i], color, 48);
		}
	}


	// deck shuffle
	shuffleNode(h[0]);
	// try a second shuffle

	// cards from deck to tableau
	for(int i = 1; i < 8; i++){
		for(int j = i; j < 8 ; j++){
		       switchCard(h[0], h[j]); // switchCard takes the last card from a head and puts it on another head
		}
	}

	// turn last card of all tableau face up
	for(int i = 1; i<8;i++){
		turnLast(h[i]);
	}

	// while should start here:
	

	int op = 0;
	int err = 0;
	int from = 0;
	int to = 0;
	int which = -1;
	while(op != 789){
		system("clear");
		displayTop(h); // fix this function
		printTable(h, -1); // fix this function

		if(err == 1){
			err = 0;
			printf("\n\tinvalid option.\n");
		}


		printf("\nOPTIONS: 1) Cycle Deck\t2) move card\t789) Quit game\n\tChoose an option:");
		scanf("%d",&op);
		if(op == 1){
			res = cycle(h);
			if(res == 1){
				err=1;
				continue;
			}
		}else if(op == 2){
			printf("\tmove from:");
			scanf("%d", &from);
			if(from < 1 || from > 12){
				err = 1;
				continue;
			}
			if(from > 1 && from < 9){
				if(lengthNode(h[from-1]) > 1){
					system("clear");
					displayTop(h);
					printTable(h,from-2);
					printf("\nOPTIONS: 1) Cycle Deck\t2) move card\t789) Quit game\n\tChoose an option:2\n");
					printf("\tmove from:%d\n", from);
					printf("\tmove which:");
					scanf("%d", &which);
				}
			}

			printf("\tmove to:");
			scanf("%d", &to);
			if(to < 2 || to > 12){
				err = 1;
				continue;
			}

			if((to > 8 && to < 13)&&(from > 8 && from < 13)){
				err = 1;
				continue;
			}
			if(to == from){
				err = 1;
				continue;
			}

			if(to > 8 && to < 13){
				printf("move to foundation: move from %d to %d\n", from, to);
				res = moveF(h[from-1], h[to-1], ranks);
				if(res == 1){
					err=1;
					continue;
				}
				//scanf("%d", &to);
			}else{
				printf("move from %d to %d\n", from, to);
				res = move(h[from-1], h[to-1], lengthNode(h[from-1]), ranks, which);
				which = -1;
				if(res == 1){
					err=1;
					continue;
				}
				//scanf("%d", &to);
			}

		}else if(op == 789){
			printf("\n\tThanks for Playing!\n");
		}else {
			err=1;
		}
	}

	for(int i = 0; i < 12; i++){
		freeNode(h[i]);
	}
	return 0;
}
