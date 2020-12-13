#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define BUFSIZE 256
/*LAOUAR NAOUFEL TP3B && GUZEL KADIR TP2A*/



//fonction recursuve permetant de savoir combien de case il faut pour freiner avec une vitesse donner
int factplus(int n){
	return n > 1?(n+factplus(n-1)):1;
}

//structure pour actualisé la position et la vitesse du joueur
struct joueur{
	int x;
	int y;
	int vx;
	int vy;
};

//structure pour stocker les données des checkpoints
struct objectif{
	int x;//coordonée point supérieur gauche
	int y;
	int weight;
	int height;
	int bestX;
	int bestY;
};

//fonction qui aloue une grille de taille (taille*taille)
int *create_grid(int taille){
	int *data=calloc(taille*taille,sizeof(int));
	return data;
}
//fonction qui gere le deplacement suivant
//LES PARAMETRES:
//j est la structure joueur 
//size est la taille de la grille
//TnearY et TnearX sont les coordonées du meilleur point dans le chepoint
//Ymid et Xmid sont des varaibles qui represente le x et le y 'milieux' entre notre position et l'objectif
//diff x et diff y represente la differance de case entre notre posisiton et l'objectif 
void deplacement(struct joueur *j, int size,int TnearY,int TnearX,int Ymid,int Xmid, int diffx,int diffy){
	//cas ou on est sur la meme ligne ou meme colone
	if(j->y==TnearY || j->x==TnearX){
		//meme ligne
		if(j->y==TnearY){
			if(abs(j->vy)==1){
				j->vy=0;
			}else{
				if(j->vy<0){
					j->vy++;
				}
				if(j->vy>0){
					j->vy--;
				}
			}
			j->y+=j->vy;
			//a gauche de l'objectif
			if(j->x<TnearX){
				if(j->x+j->vx<Xmid){
					j->vx++;
					j->x=j->x+j->vx;
				}else{
					if(((size-1)-TnearX)<factplus(abs(j->vx))){
						j->vx--;
					}else{
						if(abs(j->vx)%diffx!=0){
							j->vx--;
						}
					}
					if(j->vx<2){
						j->vx=1;
						if(j->x+2<TnearX){
							j->vx=2;
						}
					}
					j->x=j->x+j->vx;
				}
			//a droite de l'objectif
			}else{
				if(j->x+j->vx>Xmid){
					j->vx--;
					j->x=j->x+j->vx;
				}else{
					if(TnearX<factplus(abs(j->vx))){
						j->vx++;
					}else{
						if(abs(j->vx)%diffx!=0){
							j->vx++;
						}
					}
					if(abs(j->vx)<=2){
						j->vx=-1;
						if(j->x-2>TnearX){
							j->vx=-2;
						}
					}
					j->x=j->x+j->vx;
				}
			}
		//meme colone
		}else{
			if(abs(j->vx)==1){
				j->vx=0;
			}else{
				if(j->vx<0){
					j->vx++;
				}
				if(j->vx>0){
					j->vx--;
				}
			}
			j->x+=j->vx;
			//en haut de l'objectif
			if(j->y<TnearY){
					if(j->y+j->vy<Ymid){
						j->vy++;
						j->y=j->y+j->vy;
					}else{
						if(((size-1)-TnearY)<factplus(abs(j->vy))){
							j->vy--;
						}else{
							if(abs(j->vy)%diffy!=0){
								j->vy--;
							}
						}
						if(j->vy<2){
							j->vy=1;
							if(j->y+2<TnearY){
								j->vy=2;
							}
						}
						j->y=j->y+j->vy;
					}
			//en bas de l'objectif
			}else{
				if(j->y+j->vy>Ymid){
					j->vy--;
					j->y=j->y+j->vy;
				}else{
					if(TnearY<factplus(abs(j->vy))){
						j->vy++;
					}else{
						if(abs(j->vy)%diffy!=0){
							j->vy++;
						}
					}
					if(abs(j->vy)<2){
						j->vy=-1;
						if(j->y-2>TnearY){
							j->vy=-2;
						}
					}
					j->y=j->y+j->vy;
				}
			}
		}
	//cas ou le joueur est ni sur la meme ligne ni sur la meme colone
	}else{
		//en haut de l'objectif
		if (j->y<TnearY){
			if(j->y+j->vy<Ymid-1){
				j->vy++;
				j->y=j->y+j->vy;
			}else{
				if(((size-1)-TnearY)<factplus(abs(j->vy))){
					j->vy--;
				}else{
					if(abs(j->vy)%diffy!=0){
						j->vy--;
					}
				}
				if(j->vy<2){
					j->vy=1;
					if(j->y+2<TnearY){
						j->vy=2;
					}
				}
				j->y=j->y+j->vy;
			}
			//a droit de l'objectif
			if(j->x<TnearX){
				if(j->x+j->vx<Xmid){
					j->vx++;
					j->x=j->x+j->vx;
				}else{
					if(((size-1)-TnearX)<factplus(abs(j->vx))){
						j->vx--;
					}else{
						if(abs(j->vx)%diffx!=0){
							j->vx--;
						}
					}						
					if(j->vx<2){
						j->vx=1;
						if(j->x+2<TnearX){
							j->vx=2;
						}
					}
					j->x=j->x+j->vx;
				}
			//a gauche de l'objectif
			}else{
				if(j->x+j->vx>Xmid){
						j->vx--;
						j->x=j->x+j->vx;
				}else{
					if(TnearX<factplus(abs(j->vx))){
						j->vx++;
					}else{
						if(abs(j->vx)%diffx!=0){
							j->vx++;
						}
					}
					if(abs(j->vx)<2){
						j->vx=-1;
						if(j->x-2>TnearX){
							j->vx=-2;
						}
					}
					j->x=j->x+j->vx;
				}
			}
		//en bas de l'objectif
		}else{
			if(j->y+j->vy>Ymid){
				j->vy--;
				j->y=j->y+j->vy;
			}else{
				if(TnearY<factplus(abs(j->vy))){
						j->vy++;
				}else{
					if(abs(j->vy)%diffy!=0){
						j->vy++;
					}
				}
				if(abs(j->vy)<2){
					j->vy=-1;
					if(j->y-2>TnearY){
						j->vy=-2;
					}
				}
				j->y=j->y+j->vy;
			}
			//a gauche de l'objectif
			if(j->x<TnearX){
				if(j->x+j->vx<Xmid){
					j->vx++;
					j->x=j->x+j->vx;
				}else{
					if(((size-1)-TnearX)<factplus(abs(j->vx))){
						j->vx--;
					}else{
						if(abs(j->vx)%diffx!=0){
							j->vx--;
						}
					}
					if(j->vx<2){
						j->vx=1;
						if(j->x+2<TnearX){
							j->vx=2;
						}
					}	
					j->x=j->x+j->vx;
				}
			//a droite de l'objectif
			}else{
				if(j->x+j->vx>Xmid){
					j->vx--;
					j->x=j->x+j->vx;
				}else{
					if(TnearX<factplus(abs(j->vx))){
						j->vx++;
					}else{
						if(abs(j->vx)%diffx!=0){
							j->vx++;
						}
					}
					if(abs(j->vx)<2){
						j->vx=-1;
						if(j->x-2>TnearX){
							j->vx=-2;
						}
					}
					j->x=j->x+j->vx;
				}
			}
		}
	}
}

int main() {
setbuf(stdout, NULL);
char buf[BUFSIZE];
// get the size
fgets(buf, BUFSIZE, stdin);
int size = atoi(buf);
//create grid
int *grid=create_grid(size);
struct joueur j;
struct objectif target;

// get the grid values
for (int i = 0; i < size * size; ++i) {
	fgets(buf, BUFSIZE, stdin);
	int value = atoi(buf);
	// TODO: do something with value
	grid[i]=value;
}
// get the position
fgets(buf, BUFSIZE, stdin);
int px = atoi(buf);
j.x=px;
fgets(buf, BUFSIZE, stdin);
int py = atoi(buf);
j.y=py;
// get the objective
fgets(buf, BUFSIZE, stdin);
int x = atoi(buf);
target.x=x;
fgets(buf, BUFSIZE, stdin);
int y = atoi(buf);
target.y=y;
fgets(buf, BUFSIZE, stdin);
int w = atoi(buf);
target.weight=w;
fgets(buf, BUFSIZE, stdin);
int h = atoi(buf);
target.height=h;
j.vx = 0;
j.vy = 0;
int check= (target.y*size)+target.x;
int bestvalue=0;
bool checkIsNew = true;
int Xmid=0;
int Ymid=0;
int diffx=0;
int diffy=0;
for (;;) {
// compute new px and new py
// TODO
//calcul les données necessaire quand on obtient un nouveaux checkpoint
if (checkIsNew){
	check= (target.y*size)+target.x;
	bestvalue=grid[check];
	target.bestX=target.x;
	target.bestY=target.y;
	//prend les coordonées du meilleur point dans le checkpoint
	for (int i = 1; i <= target.height; ++i){
		for (int l = 1; l <= target.weight; ++l){
			if(bestvalue == grid[((target.y+i-1)*size)+target.x+l-1]){
				if(    (abs(j.x-target.bestX)>abs(j.x-target.x+l-1) )  || (abs(j.y-target.bestY)>abs(j.y-target.y+i-1))  ){
					target.bestX=target.x+l-1;
					target.bestY=target.y+i-1;
				}
			}
			if(bestvalue >grid[((target.y+i-1)*size)+target.x+l-1]){
				target.bestX=target.x+l-1;
				target.bestY=target.y+i-1;
				bestvalue=grid[((target.y+i-1)*size)+target.x+l-1];
			}
		}
	}
	//calcul des DIFF et des MID
	diffx=abs(j.x-target.bestX);
	diffy=abs(j.y-target.bestY);
	Ymid=abs(j.y-target.bestY)/2;
	Xmid=abs(j.x-target.bestX)/2;
	if(j.x<target.bestX){
		Xmid=target.bestX-Xmid;
	}else{
		Xmid=target.bestX+Xmid;
	}
	if(j.y<target.bestY){
		Ymid=target.bestY-Ymid;
	}else{
		Ymid=target.bestY+Ymid;
	}
}

//deplacement
deplacement(&j,size,target.bestY,target.bestX,Ymid,Xmid,diffx,diffy);
//envoie au serveur
printf("%i\n%i\n", j.x, j.y);
checkIsNew = false;
// get the response
fgets(buf, BUFSIZE, stdin);
if (strcmp(buf, "ERROR\n") == 0) {
	break;
}
if (strcmp(buf, "FINISH\n")==0)
{
	fprintf(stderr, "Victoire!!\n");
	break;
}
if (strcmp(buf, "CHECKPOINT\n")==0){
	fprintf(stderr, "CHECKPOINT ATTEINT!\n");
	fgets(buf, BUFSIZE, stdin);
	int x = atoi(buf);
	target.x=x;
	fgets(buf, BUFSIZE, stdin);
	int y = atoi(buf);
	target.y=y;
	fgets(buf, BUFSIZE, stdin);
	int w = atoi(buf);
	target.weight=w;
	fgets(buf, BUFSIZE, stdin);
	int h = atoi(buf);
	target.height=h;
	checkIsNew=true;
}
// TODO
}
free(grid);
return 0;
}