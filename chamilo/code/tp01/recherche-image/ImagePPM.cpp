#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>

#include "ImagePPM.hpp"

// Crée une image
t_image new_image(int width,int height) {
	t_image image;
	image.width = width;
	image.height = height;
	image.pixel = static_cast<t_pixel *>(malloc(sizeof(t_pixel)*static_cast<size_t>(width*height)));
	return image;
}

// Détruit une image
void delete_image(t_image image) {
	// Vérifie qu'elle n'a pas déjà été détruite
	if (image.pixel) {
		free(image.pixel);
		image.pixel=NULL;
		image.width=0;
		image.height=0;
	}
}

// Donne accès à deux parties d'image imgA et imgB à partir de l'image img
// Partage horizontal avec un recouvrement de cover pixels
// Il y a partage des deux images avec la première
void split_image(t_image img, t_image& imgA, t_image& imgB,int cover) {
	// imgB est la partie basse
	imgB.pixel = &img.pixel[(img.height-cover)/2*img.width];
	imgB.width = img.width;
	imgB.height = img.height+cover-(img.height+cover)/2;
	// imgA est la partie haute
	imgA.pixel = img.pixel;
	imgA.width = img.width;
	imgA.height = (img.height+cover)/ 2;
}

// Lecture d'une image PPM depuis un fichier
// L'image est créee et doit être détruite ensuite
t_image read_image(const char* filename) {
	char lineBuffer[maxPPMline];
	FILE* f = fopen(filename,"r");
	if (f==NULL) {
		perror("Impossible d'ouvrir le fichier");
		exit(EXIT_FAILURE);
	}
	// Aucune vérification sur le format PPM
	if(!fgets(lineBuffer,maxPPMline,f))
	  exit(-1);
	if(!fgets(lineBuffer,maxPPMline,f))
	  exit(-1);
	if(!fgets(lineBuffer,maxPPMline,f))
	  exit(-1);
	int width; int height;
	sscanf(lineBuffer,"%i %i",&width,&height);
	if(!fgets(lineBuffer,maxPPMline,f))
	  exit(-1);
	printf("Loading %s %ix%i\n",filename,width,height);
	// Creation de l'image
	t_image image = new_image(width,height);
	// Lecture le l'image en mémoire
	for (int i=0; i<width*height;i++) {
		// Lecture des 3 couleurs d'un pixel
		image.pixel[i].red = static_cast<unsigned char>(fgetc(f));
		image.pixel[i].green = static_cast<unsigned char>(fgetc(f));
		image.pixel[i].blue = static_cast<unsigned char>(fgetc(f));
	}
	return image;
}

// Ecriture d'une image au format PPM
void write_image(const t_image image, const char* filename) {
	// Ouverture du fichier
	FILE* f = fopen(filename,"w");
	// Cas d'erreur d'ouverture
	if (!f) {
		perror("Impossible d'ouvrir le fichier en ecriture");
		exit(EXIT_FAILURE);
	}
	// Sortie de l'entête
	fprintf(f,"P6\n# created by IUT2 Grenoble\n");
	fprintf(f,"%d %d\n255\n",image.width,image.height);
	// Sortie de tous les pixels de l'image
	int max=image.height*image.width; // nombre maxi de pixels
	for (int i = 0;i < max;i++)  {
		fputc(static_cast<char>(image.pixel[i].red),f);
		fputc(static_cast<char>(image.pixel[i].green),f);
		fputc(static_cast<char>(image.pixel[i].blue),f);
	}
}

// Dessine un rectangle dans img en (x,y) de largeur width et hauteur height
void draw_rect(t_image img,t_pixel colour,int x,int y,int width,int height) {
	// Trace lignes horizontales
	for (int i=x;i<x+width;i++) {
		img.pixel[y*img.width+i] = colour;
		img.pixel[(y+height)*img.width+i] = colour;
	}
	// Trace les lignes verticales
	for (int j=y;j<y+height;j++) {
		img.pixel[j*img.width+x] = colour;
		img.pixel[j*img.width+x+width] = colour;
	}
}

// Recherche d'une image dans une autre,
// L'image query doit être de taille inferieure à image
// Resultat :
// match : la plus faible valeur de correspondance
// xMatch, yMatch : la position trouvée
void search_image(t_image image, t_image query,int& xMatch,int& yMatch,int& match) {
	// Recherche toutes les positions possibles
	match=INT_MAX; // valeur maximum initiale pour l'algorithme du minimum
	int max = image.width-query.width; // Le nombre de lignes maximum à traiter
	for (int x=0; x<max ;x++) {
		for (int y=0; y<image.height-query.height;y++) {
			int m = match_image_at(image,query,x,y);
			if (m < match) {
				match=m;
				xMatch=x;yMatch=y;
			}
		}
		// Affiche le pourcentage de lignes traitées
		printf("\r%i%%",(x*100/(max-1)));fflush(stdout);
	}
}
