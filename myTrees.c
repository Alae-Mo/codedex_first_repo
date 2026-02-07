#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct noeud
{
    int val;
    struct noeud *fg, *fd;
} noeud;

int menu()
{
    printf("1.Créer un arbre\n");
    printf("2.Affichage croissant de l'arbre\n");
    printf("3.Affichage décroissant de l'arbre\n");
    printf("4.Nombre des noeuds\n");
    printf("5.Nombre des feuilles\n");
    printf("6.Affichage croissant des feuilles\n");
    printf("7.Calcule de profondeur\n");
    printf("8.Recherche d'un élément\n");
    printf("9.Supprimer un élément\n");
    printf("10.Enregistrer l'arbre dans un fichier\n");
    printf("11.Créer un arbre depuis un fichier\n");
    printf("12.Quitter le programme\n");

    int choix;
    printf("Entrer le chiffre correspondant à l'action que vous voulez faire: ");
    scanf("%d", &choix);
    return choix;
}

noeud *creerNoeud()
{
    noeud *nv = (noeud *)malloc(sizeof(noeud));
    if (nv == NULL)
    {
        printf("Erreur d'allocation de mémoire en fonction creerNoeud() \n");
        return NULL;
    }

    printf("Valeur: ");
    scanf("%d", &nv->val);
    nv->fg = nv->fd = NULL;

    return nv;
}

void insererNoeud(noeud **rac, noeud *nv)
{
    if (*rac == NULL)
    {
        *rac = nv;
        return;
    }
    else if (nv->val > (*rac)->val)
    {
        insererNoeud(&(*rac)->fd, nv);
    }
    else if (nv->val <= (*rac)->val)
    {
        insererNoeud(&(*rac)->fg, nv);
    }
}

void creerArbre(noeud **rac)
{
    int n;
    printf("Combien d'éléments: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        noeud *nv = creerNoeud();
        insererNoeud(rac, nv);
    }
}

void afficherCroissant(noeud *rac)
{
    if (rac != NULL)
    {
        afficherCroissant(rac->fg);
        printf("Valeur: %d\n", rac->val);
        afficherCroissant(rac->fd);
    }
    return;
}

void afficherDecroissant(noeud *rac)
{
    if (rac != NULL)
    {
        afficherDecroissant(rac->fd);
        printf("Valeur: %d\n", rac->val);
        afficherDecroissant(rac->fg);
    }
    return;
}

// don't forget tzidi si nbreNoeuds=0 then printf("L'arbre est vide");
int nbreNoeuds(noeud *rac)
{
    if (rac == NULL)
    {
        return 0;
    }
    return 1 + nbreNoeuds(rac->fd) + nbreNoeuds(rac->fg);
}

// don't forget tzidi si nbreFeuilles=0 then printf("L'arbre est vide");
int nbreFeuilles(noeud *rac)
{
    if (rac == NULL)
    {
        return 0;
    }
    if (rac->fg == NULL && rac->fd == NULL)
    {
        return 1;
    }
    return nbreFeuilles(rac->fd) + nbreFeuilles(rac->fg);
}

void afficherFeuillesCrois(noeud *rac)
{
    if (rac == NULL)
    {
        // printf("L'arbre est vide\n");
        return;
    }
    if (rac->fg == NULL && rac->fd == NULL)
    {
        printf("Valeur: %d\n", rac->val);
        return;
    }
    afficherFeuillesCrois(rac->fg);
    afficherFeuillesCrois(rac->fd);
}

// don't forget to add si calculerProfondeur=0 then printf("L'arbre est vide");
int calculerProfondeur(noeud *rac)
{
    if (rac == NULL)
    {
        return 0;
    }
    int gauche = calculerProfondeur(rac->fg);
    int droite = calculerProfondeur(rac->fd);
    return 1 + (gauche > droite ? gauche : droite);
}

// don't forget to add si !calculerProfondeur then printf("L'arbre est vide ou la valeur ne figure pas dans cet arbre");
bool chercherElement(noeud *rac, int valRech)
{
    if (rac == NULL)
        return false;
    if (rac->val == valRech)
        return true;
    if (valRech < rac->val)
        return chercherElement(rac->fg, valRech);
    else
        return chercherElement(rac->fd, valRech);
}

void supprimerNoeud(noeud **rac, int val)
{
    if (*rac == NULL)
        return;
    if ((*rac)->val > val)
        supprimerNoeud(&(*rac)->fg, val);
    else if ((*rac)->val < val)
        supprimerNoeud(&(*rac)->fd, val);
    else
    {
        if ((*rac)->fg == NULL && (*rac)->fd == NULL)
        {
            free(*rac);
            *rac = NULL;
        }
        else if ((*rac)->fd == NULL)
        {
            noeud *temp = *rac;
            *rac = (*rac)->fg;
            free(temp);
        }
        else if ((*rac)->fg == NULL)
        {
            noeud *temp = *rac;
            *rac = (*rac)->fd;
            free(temp);
        }
        else
        {
            noeud *successor = (*rac)->fd;
            while (successor->fg != NULL)
            {
                successor = successor->fg;
            }
            (*rac)->val = successor->val;
            supprimerNoeud(&(*rac)->fd, successor->val);
        }
    }
}

void enregistrerArbreFichier(noeud *rac, FILE *file_path)
{
    if (file_path == NULL)
    {
        printf("Erreur d'ouverture de fichier\n");
        return;
    }
    if (rac != NULL)
    {
        enregistrerArbreFichier(rac->fg, file_path);
        fprintf(file_path, "%d\n", rac->val);
        enregistrerArbreFichier(rac->fd, file_path);
    }
    return;
}

noeud *creerElementFichier(int value)
{
    noeud *nv = (noeud *)malloc(sizeof(noeud));
    if (nv == NULL)
    {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    nv->val = value;
    nv->fg = nv->fd = NULL;

    return nv;
}

void initialiserArbreFichier(noeud **rac, FILE *file_path)
{
    if (file_path == NULL)
    {
        printf("Erreur d'overture du fichier\n");
        return;
    }
    int value;
    while (fscanf(file_path, "%d", &value) == 1)
    { // 1 means true càd fscanf found %d
        noeud *nv = creerElementFichier(value);
        insererNoeud(rac, nv);
    }
}

int main()
{
    noeud *rac = NULL;
    char file_path[100] = "tree.txt";
    FILE *f;

    int choix;
    do
    {
        choix = menu();
        switch (choix)
        {
        case 1:
            printf("============Création de l'arbre============\n");
            creerArbre(&rac);
            break;

        case 2:
            printf("============Affichage croissant de l'arbre============\n");
            afficherCroissant(rac);
            break;

        case 3:
            printf("============Affichage décroissant de l'arbre============\n");
            afficherDecroissant(rac);
            break;

        case 4:
            printf("============Nombre des noeuds============\n");
            if (nbreNoeuds(rac) == 0)
                printf("L'arbre est vide");
            else
                printf("Nombre des noeuds: %d\n", nbreNoeuds(rac));
            break;

        case 5:
            printf("============Nombre des feuilles============\n");
            if (nbreFeuilles(rac) == 0)
                printf("L'arbre est vide");
            else
                printf("Nombre des feuilles: %d\n", nbreFeuilles(rac));
            break;

        case 6:
            printf("============Affichage croissant des feuilles============\n");
            afficherFeuillesCrois(rac);
            break;

        case 7:
            printf("============Calcule de la profondeur============\n");
            if (calculerProfondeur(rac) == 0)
                printf("L'arbre est vide");
            else
                printf("La profondeur est: %d\n", calculerProfondeur(rac));
            break;

        case 8:
            int valRech;
            printf("============Recherche d'un élément============\n");
            printf("Quelle est la valeur que vous recherchez: ");
            scanf("%d", &valRech);
            if (!chercherElement(rac, valRech))
                printf("L'arbre est vide ou la valeur ne figure pas dans cet arbre");
            else
                printf("La valeur recherchée figure dans l'arbre\n");
            break;

        case 9:
            int val;
            printf("============Supprimer un élément============\n");
            printf("Quelle est la valeur que vous voulez supprimer: ");
            scanf("%d", &val);
            supprimerNoeud(&rac, val);
            break;

        case 10:
            printf("============Enregistrement de l'arbre dans un fichier============\n");
            f = fopen(file_path, "w");
            if (f == NULL)
            {
                printf("Erreur d'ouverture de fichier\n");
                return 0;
            }
            enregistrerArbreFichier(rac, f);
            fclose(f);
            break;

        case 11:
            printf("============Créer un arbre depuis un fichier============\n");
            f = fopen(file_path, "r");
            if (f == NULL)
            {
                printf("Erreur d'ouverture de fichier\n");
                return 0;
            }
            rac = NULL;
            initialiserArbreFichier(&rac, f);
            fclose(f);
            break;

        case 12:
            printf("A bientôt!\n");
            return 0;
            break;

        default:
            printf("Choix invalide\n");
            break;
        }
    } while (choix != 12);

    return 0;
}
