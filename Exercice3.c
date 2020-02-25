#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// On suppose a<b
int randInterval(int a , int b){
    return rand()%(b-a) +a;
};


struct Joueur {
	int PVie ; 
	int Mana ;
	int Attaque ;
	int Experience;
	int Niveau;
};

struct Monstres { 
	char Nom[50];
	char Desc[100];
	int PVie;
	int Attaque;
	int Decision;
	int Poison;
};
struct Sort {
	char Nom[50];
	char Desc[50];
	int Degats;
	int Cmana;
	
};
struct Sort Pest = {"pest","Empoisonne les monstres",0,5};
struct Sort Bouledefeu = {"pyroball","Inflige de gros degats aux monstre",25,5};
struct Monstres MonstreE1 = {"Ame perdue","relativement faible mais frappe fort",35,15,0,0};
struct Monstres MonstreE2 = {"Guerrier des enfers","beaucoup de points de vie mais peu d'attaque",60,10,0,0};
struct Monstres MonstreE3 = {"Satan","IL EST GIGANTESQUE !!!!",150,20,0,0};
struct Joueur Joueur1 = {100,10,15,0,1};

char Csort [50];
char destination[50];
int NbrePotions = 1;
int MonstresMort=0;
char decisionJ[50];
int NbreMonstres = 2;
char MonstreC [50];
int fin;

int Combat (){
	
	while (MonstresMort == 0 && Joueur1.PVie>0 ) {
		printf( "Voulez vous ATTAQUER le/les monstre(s), utiliser une POTION ou lancer un SORT ?\n");
		scanf("%s",decisionJ);
		MonstreE3.Decision = (rand()%2)+1;
		MonstreE2.Decision = (rand()%2)+1;
		MonstreE1.Decision = 2;
		if (strcmp(decisionJ,"attaquer")==0 || strcmp(decisionJ,"potion")==0 || strcmp(decisionJ,"sort")==0 ){
			
			if ( strcmp(decisionJ,"sort")==0 ){
				if ( Joueur1.Mana >= 5 ){
					printf ( "Quel sort voulez-vous lancer ? (%s/%s) ou (%s/%s) ? \n",Bouledefeu.Nom,Bouledefeu.Desc,Pest.Nom,Pest.Desc);
					scanf ("%s", Csort);
					if (strcmp (Csort,"pyroball")==0) {
						printf("Vous utilisez votre pyroball\n");
						MonstreE1.PVie = MonstreE1.PVie - Bouledefeu.Degats;
						Joueur1.Mana = Joueur1.Mana - 5;
						if ( NbreMonstres == 3){
							MonstreE2.PVie = MonstreE2.PVie - Bouledefeu.Degats;
						}
						if ( NbreMonstres == 4){
							MonstreE3.PVie = MonstreE3.PVie - Bouledefeu.Degats;
						}
					}
					
					if (strcmp (Csort,"pest")==0) {
						printf("Vous utilisez votre sort de pest\n");
						MonstreE1.Poison= MonstreE1.Poison + 4;
						Joueur1.Mana = Joueur1.Mana - 5;
						if ( NbreMonstres == 3){
							MonstreE2.Poison= MonstreE2.Poison + 4;
						}
						if ( NbreMonstres == 4){
							MonstreE3.Poison= MonstreE3.Poison + 4;
						}
					}
				}
				else {
					printf ("Vous n'avez pas assez de mana\n");
					Combat (MonstreE1);
				}
				
			}
			if ( strcmp(decisionJ,"potion")==0 ){
				if ( NbrePotions >0 ){ 
					Joueur1.PVie = Joueur1.PVie + 20;
					NbrePotions = NbrePotions -1;
				}
				else { printf ("Vous n'avez plus de potions\n");
					Combat (MonstreE1);
				}
			}		
			
			if (MonstreE2.Decision == 1 && NbreMonstres == 3){
				printf ("L'%s se soigne\n",MonstreE2.Nom);
				MonstreE2.PVie = MonstreE2.PVie + 5;
				if (MonstreE2.PVie > 100){
					MonstreE2.PVie = 100;
				}
			}
			
			if (MonstreE3.Decision == 1 && NbreMonstres == 4){
				printf ("%s a la flemme\n",MonstreE3.Nom);
				
			}
			
			if ( strcmp(decisionJ,"attaquer")==0 ){
				printf ("Vous attaquez un monstre\n");
				MonstreE1.PVie = MonstreE1.PVie - Joueur1.Attaque;
				if (NbreMonstres == 3 ){
					printf ( "Quel monstre voulez vous attaquer ? %s ou %s \n",MonstreE1.Nom,MonstreE2.Nom);
					scanf("%s",MonstreC);
					if ( strcmp(MonstreC,"ame perdue")==0 || strcmp(MonstreC,"guerrier des enfer")==0){
						if ( strcmp(MonstreC,"ame perdue")==0){
							MonstreE1.PVie = MonstreE1.PVie - Joueur1.Attaque;
						}
						if ( strcmp(MonstreC,"guerrier des enfer")==0){
							MonstreE2.PVie = MonstreE2.PVie - Joueur1.Attaque;
						}
					}
					else {
						Combat(MonstreE1,MonstreE2);
					}
				}
				if (NbreMonstres == 4 ){
					MonstreE3.PVie = MonstreE3.PVie - Joueur1.Attaque;
				}
			}
		
			if  (MonstreE1.Decision == 2){
				printf ("L'%s attaque\n",MonstreE1.Nom);
				Joueur1.PVie = Joueur1.PVie - MonstreE1.Attaque;
			}
			if  (MonstreE3.Decision == 4){
				printf ("%s attaque !!!\n",MonstreE3.Nom);
				Joueur1.PVie = Joueur1.PVie - MonstreE3.Attaque;
			}
			
			
			if  (MonstreE2.Decision == 2 && NbreMonstres == 3){
				printf ("L'%s attaque\n",MonstreE2.Nom);
				Joueur1.PVie = Joueur1.PVie - MonstreE2.Attaque;
			}
			if (MonstreE1.Decision >= 3){
				printf ("L'%s est mort\n",MonstreE1.Nom);
			}
			if (MonstreE2.Decision >= 3&& NbreMonstres == 3){
				printf ("L'%s est mort\n",MonstreE2.Nom);
			}
	
		}
		
		else { 
			printf("Veillez choisir une option valide ( elle doit etre marquee en minuscule)\n");
			
		}		
		if (NbreMonstres == 2 && MonstreE1.PVie <= 0 || NbreMonstres == 3 && MonstreE2.PVie<=0 && MonstreE1.PVie<=0){
			Joueur1.Experience = Joueur1.Experience + 5;
			NbrePotions++;
			MonstresMort++;
			printf( "Vous gagnez 5 points d'experience et 1 potion !\n");
			if (Joueur1.Niveau == 1 && Joueur1.Experience ==5 ){
				Joueur1.Niveau ++;
				printf ( "Vous gagnez un niveau ! Vous etes maintenant niveau %d !\n",Joueur1.Niveau);
				Joueur1.PVie = 100;
				Joueur1.Mana = 10;
			}
			if (MonstreE2.PVie <= 0){
				Joueur1.Experience = Joueur1.Experience + 5;
				NbrePotions = NbrePotions +2;
			}
			if (Joueur1.Niveau == 2 && Joueur1.Experience == 10 ){
				Joueur1.Niveau ++;
				printf ( "Vous gagnez un niveau ! Vous etes maintenant niveau %d !\n",Joueur1.Niveau) ;
				Joueur1.PVie = 100;
				Joueur1.Mana = 10;
			}
			
			if (Joueur1.Niveau == 3 && Joueur1.Experience == 15 ){
				Joueur1.Niveau ++;
				printf ( "Vous gagnez un niveau ! Vous etes maintenant niveau %d !\n",Joueur1.Niveau) ;
				Joueur1.PVie = 100;
				Joueur1.Mana = 10;
			}	
				
		}
		MonstreE1.PVie = MonstreE1.PVie - MonstreE1.Poison;	
		MonstreE2.PVie = MonstreE2.PVie - MonstreE2.Poison;
		MonstreE3.PVie = MonstreE3.PVie - MonstreE3.Poison;
		if (Joueur1.PVie > 100){
			Joueur1.PVie =100;
		}
		if (NbreMonstres <4)
		printf("L'%s a %d points de vie \n",MonstreE1.Nom, MonstreE1.PVie);
		
		if (NbreMonstres == 3 ){
			printf("Le %s a %d points de vie \n",MonstreE2.Nom, MonstreE2.PVie);
		}
		if (NbreMonstres == 4 ){
			printf("%s a %d points de vie \n",MonstreE3.Nom, MonstreE3.PVie);
		}
			
		printf("Il vous reste %d points de vie(s)\n",Joueur1.PVie);
		printf("Il vous reste %d potion(s)\n",NbrePotions);
		printf("Il vous reste %d points de mana(s)\n",Joueur1.Mana);
	
}
}





int Voyage() {
		printf ("Vous devez vaincre les force du mal afin de sauver le monde ! Ou voulez vous aller ? paradis ou enfer\n");
		scanf ("%s",destination);
		if ( strcmp( destination,"enfer")==0 || strcmp( destination,"paradis")==0 ){
			if ( strcmp( destination,"enfer")==0 ){
			printf ("Vous etes arrives en enfer\n");
			printf ("Vous rencontrez un/une %s qui est %s\n", MonstreE1.Nom, MonstreE1.Desc );
			Combat(MonstreE1);
				}
			if (strcmp( destination,"paradis")==0 ){
				fin =1 ;
				
				}
				
			}
		else {
			printf ("Destination incorrecte\n");
			Voyage ();
			}
		}
int Voyage2() {
		printf ("Ou voulez vous aller ? Dans le Tartare ( Facile) ou au Styx ( Difficile )\n");
		scanf ("%s",destination);
		if ( strcmp( destination,"tartare")==0 || strcmp( destination,"styx")==0 ){
			if ( strcmp( destination,"tartare")==0 ){
			printf ("Vous etes arrives dans le Tartare\n");
			printf ("Vous rencontrez une %s\n",MonstreE1.Nom);
			Combat(MonstreE1);
				}
			if (strcmp( destination,"styx")==0 ){
			printf ("Vous etes arrives au Styx\n");
			printf ("Vous rencontrez une %s et un %s \n",MonstreE1.Nom,MonstreE2.Nom);
			NbreMonstres = 3 ;
			Combat(MonstreE1,MonstreE2);
				}
			}
		else {
			printf ("Destination incorrecte ( doit etre marque en minuscule\n");
			Voyage2 ();
			}
	}
int Voyage3() {
		printf (" Vous arrivez devant une porte geante !\n Que voulez vous faire ? FUIR comme un lache ou affronter votre DESTINEE !\n");
		scanf ("%s",destination);
		if ( strcmp( destination,"fuir")==0 || strcmp( destination,"destinee")==0 ){
			if ( strcmp( destination,"fuir")==0 ){
			printf ("Vous avez choisi de fuir et mourrez en trébuchant sur un caillou\n");
			
				}
			if (strcmp( destination,"destinee")==0 ){
			printf ("Vous allez affronter votre destinee et ouvrez la porte\n");
			printf ("Vous ouvrez la grande porte et tombez sur %s en personne %s !!!\n",MonstreE3.Nom,MonstreE3.Desc);
			NbreMonstres = 4 ;
			Combat(MonstreE3);
			printf ("Vous avez vaincu les forces du mal et sauvez le monde mais lorsque vous courrez annoncer au monde votre victoire vous trebuchez sur un caillou et mourrez... Dommage... \n");
				}
			}
		else {
			printf ("Choix incorrect ( doit etre marque en minuscule\n");
			Voyage3 ();
			}
	}

	int main() {
		srand(time(NULL));
		//Niveau 1 
		Voyage ();
		if ( fin == 1 ){
		printf (" Felicitation vous etes arrives au paradis !! Et depuis votre comfortable nuage vous regardez le monde bruler en vous disant que ca aurait peut etre ete une bonne idee de les sauver, mais bon au moins vous vous etes tranquille\n");
		}
		else{
		//Niveau 2
		MonstreE1.PVie = 35;
		MonstresMort = MonstresMort - 1;
		Voyage2();
		
		//Niveau3
		MonstresMort = MonstresMort - 1;
		Voyage3();
		}
		return 0;
	}
	
	
	
	
	
	