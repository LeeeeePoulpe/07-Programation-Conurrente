#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <stdlib.h>

// Definition d'un pixel,
// chaque composante couleur est un entier entre 0 et 255
typedef struct pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} t_pixel;

// Definition d'une image
typedef struct image
	{
		t_pixel* pixel; // Pointeur sur les pixels groupés par composante couleur RVB
		int width;      // nombre de pixels horizontaux
		int height;     // nombre de pixels verticaux
	} t_image;

// Crée une image
t_image new_image(int width,int height);

// Détruit une image
void delete_image(t_image image);

// Donne accès à deux parties d'image imgA et imgB à partir de l'image img
// Partage horizontal avec un recouvrement de cover pixels
// Il y a partage des deux images avec la première
void split_image(t_image img, t_image& imgA, t_image& imgB,int cover);

// Lecture d'une image PPM depuis un fichier
// L'image est créee et doit être détruite ensuite
t_image read_image(const char* filename);

// Taille du buffer de lecture d'une image
#define maxPPMline 256

// Ecriture d'une image au format PPM
void write_image(const t_image image, const char* filename);

// Dessine un rectangle dans img en (x,y) de largeur width et hauteur height
void draw_rect(t_image img,t_pixel colour,int x,int y,int width,int height);

// Retourne le pixel de l'image à la cooordonnée (x,y)
inline
t_pixel pixel_at(t_image image,int x,int y) {
	return image.pixel[y*image.width+x];
}

// Retourne la différence absolue entre deux pixels
inline
int diff_pixel(t_pixel p1,t_pixel p2) {
	return abs(p1.red - p2.red) + abs(p1.green - p2.green) + abs(p1.blue - p2.blue);
}

// Calcule la correspondance d'une image dans une autre à une certaine position (x,y)
// du coin haut gauche de l'image query
// L'origine est en haut à gauche, x est horizontal, y vertical
// Le résultat est la somme des valeurs absolues de chaque pixels de l'image
inline
int match_image_at(t_image image,t_image query,int x,int y) {
	int match=0; // Correspondance en cours de calcul
		for(int yq=0;yq<query.height;yq++) {
			for(int xq=0;xq<query.width;xq++) {
			match += diff_pixel(pixel_at(image,x+xq,y+yq),pixel_at(query,xq,yq));
		}
	}
	return match;
}



// Recherche d'une image dans une autre,
// L'image query doit être de taille inferieure à image
// Resultat :
// match : la plus faible valeur de correspondance
// xMatch, yMatch : la position trouvée
void search_image(t_image image, t_image query,int& xMatch,int& yMatch,int& match);

#endif //IMAGE_HPP_
