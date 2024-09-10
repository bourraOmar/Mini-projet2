#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max_tache 100
int count = 0;

typedef struct
{
    int jour, mois, annee;
} deadline;

typedef struct
{
    int id;
    char titre[50];
    char description[200];
    deadline DL; // deadline
    deadline DC; // date de creation
    char statut;
} taches;
taches tache[max_tache];

void ajoutUneTache()
{
    if (count < max_tache)
    {
        int choix;
        tache[count].id = count + 1;
        printf("Identifiant: %d\n", tache[count].id);
        printf("Titre de la tache: ");
        scanf(" %[^\n]", &tache[count].titre);

        printf(" Description de la tache: ");
        scanf(" %[^\n]", &tache[count].description);

        printf("Enter le Deadline: ");
        printf("Jour : ");
        scanf("%d", &tache[count].DL.jour);
        printf("mois : ");
        scanf("%d", &tache[count].DL.mois);
        printf("année : ");
        scanf("%d", &tache[count].DL.annee);

        printf("Statut ( 1 = 'A réaliser', 2 = 'En cours de réalisation', 3 = 'Finalisée')");
        scanf(" %d", &choix);
        switch (choix)
        {
        case 1:
            strcpy(tache[count].statut,"A realiser");
            break;
        case 2:
            strcpy(tache[count].statut,"En cours de realisation");
            break;
        case 3:
            strcpy(tache[count].statut,"Finalisee");
            break;
        default:
            printf("Choix invalide.\n");
            break;
        }

        count++;
        printf("Votre tache %s a ete ajoute avec succes.\n", tache[count - 1].titre);
    }
    else
    {
        printf("Liste des taches pleine.\n");
    }
}

void ajoutMultiple()
{
    int nb, i;
    printf("Entre le nombre des taches voulez-vous ajouter :");
    scanf("%d", &nb);
    if (nb > 0 && (count + nb) < max_tache)
    {
        for (i = 0; i < nb; i++)
        {
            printf("Ajout de la tache: %d \n", i + 1);
            ajoutUneTache();
        }
    }
    else
    {
        printf("vous ne pouvez pas ajouter plus de %d teaches.", max_tache - count);
    }
}
void triAlphabitique()
{
    int i, j;
    taches temp;
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(tache[i].titre, tache[j].titre) > 0)
            {
                temp = tache[i];
                tache[i] = tache[j];
                tache[j] = temp;
            }
        }
    }
}
void triDeadline()
{
    int i, j;
    taches tri;
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (tache[i] DL.annee > tache[j].DL.annee)
            {
                tri = tache[i];
                tache[i] = tache[j];
                tache[j] = tri;
            }
            else if (tache[i].DL.annee == tache[j].DL.annee && tache[i].DL.mois > tache[j].DL.mois)
            {
                tri = tache[i];
                tache[i] = tache[j];
                tache[j] = tri;
            }
            else if (tache[i].DL.annee == tache[j].DL.annee && tache[i].DL.mois == tache[j].DL.mois && tache[i].DL.jour > tache[j].DL.jour)
            {
                tri = tache[i];
                tache[i] = tache[j];
                tache[j] = tri;
            }
        }
    }
    printf("les taches ont ete tries par deadline avec succes.\n");
}
void triDeadline3j()
{
    int jours, i;
    time_t t = time(NULL);
    struct tm dt = localtime(&t);

    printf("les taches dont le deadline de 3 jours ou moins.\n");
    int j = dt.tm_mday;
    int m = dt.tm_mon + 1;
    int a = dt.tm_year + 1900;
    for (i = 0; i < count; i++)
    {
        jours = ((tache[i].DL.annee - a) * 365 + (tache[i].DL.mois - m) * 30 + (tache[i].DL.jour - j));
        if (jours > 0 && jours <= 3)
        {
            printf("Id: %d\n", tache[i].id);
            printf("titre: %d\n", tache[i].titre);
            printf("description: %d\n", tache[i].description);
            printf("Deadline: %d/%d/%d\n", tache[i].DL.jour, tache[i].DL.mois, tache[i].DL.annee);
            printf("Dead de creation: %d/%d/%d\n", tache[i].DC.jour, tache[i].DC.mois, tache[i].DC.annee);
            printf("Statut: %s\n", tache[i].statut);
        }
    }
}
void afficherTaches()
{
    int i, choix;
    if (count == 0)
    {
        printf("Aucune tache a afficher.\n");
        return;
    }
    printf("Affichage des taches.\n");
    printf("1 . trier par titre. \n");
    printf("2 . trier par deadline. \n");
    printf("3 . afficher les tache dans 3 jours ou moins\n. \n");
    printf("Choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        triAlphabitique();
        break;
    case 2:
        triDeadline();
        break;
    case 3:
        triDeadline3j();
        break;
        return;
    default:
        printf("Choix invalide.\n");
        return;
    }
    for (i = 0; i < count; i++)
    {
        printf("Identifiant: %d\n", tache[i].id);
        printf("titre: %d\n", tache[i].titre);
        printf("description: %d\n", tache[i].description);
        printf("Deadline: %d/%d/%d\n", tache[i].DL.jour, tache[i].DL.mois, tache[i].DL.annee);
        printf("Date de creation : %d/%d/%d\n", tache[i].DC.jour, tache[i].DC.mois, tache[i].DC.annee);
        printf("Statut: %s\n", tache[i].statut);
    }
}
void modifierTache()
{
    int id, choix;
    if (count == 0)
    {
        printf("Aucune tache a modifier.\n");
        return;
    }
    printf("Entrez Id de la tache a modifier: ");
    scanf("%d", &id);
    if (id <= 0 || id > count)
    {
        printf("Identifiant invalide.\n"); 
        return;
    }
    id--;
    printf("Que voulez-vous modifier?\n");
    printf("1 . Description\n");
    printf("2 . Statut\n");
    printf("3 . Deadline\n");
    printf("Choix: ");
    scanf("%d", &choix);
    {
        switch (choix)
        {
        case 1:
            printf("Entrez la nouvelle description : ");
            scanf(" %[^\n]", tache[id].description);
            printf("Description mise a jour avec succes.\n");
            break;
        case 2:
            printf("Entrez la nouvelle statut : ");
            scanf(" %[^\n]", tache[id].statut);
            printf("Statuts mise a jour avec succes.\n");
            break;
        case 3:
            printf("Nouvelle Deadline (jj/mm/aaaa): \n");
            do
            {
                printf("Jour : ");
                scanf("%d", &tache[id].DL.jour);
                printf("Mois : ");
                scanf("%d", &tache[id].DL.mois);
                printf("Annee : ");
                scanf("%d", &tache[id].DL.annee);
            } while (tache[id].DL.annee < 0);
            printf("Deadline mise a jour avec succes.\n");
            break;
        default:
            printf("Choix invlide.\n");
            break;
        }
    }
}
void tacheSupprimer()
{
    int id, i;
    if (count == 0)
    {
        printf("Aucune tache a supprimer.\n");
        return;
    }
    printf("Entrez l'identifiant de la tache a supprimer : ");
    scanf("%d", &id);
    if (id < 0 || id > count)
    {
        printf("Identifant invalide.\n");
        return;
    }
    id--;
    for (i = id; i < count; i++)
    {
        tache[i] = tache[i + 1];
    }
    count--;
    printf("La tache %d a ete supprimer avec succes.\n", id + 1);
}
void tacheRechercher()
{
    int choix, id, trouve = 0, i;
    char titre[50];
    if (count == 0)
    {
        printf("Aucune tache a supprimer.\n");
        return;
    }
    printf("Rechercher une tache par : \n");
    printf("1 . Id\n");
    printf("2 . Titlre\n");
    printf("Choix: \n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        printf("Entrez l'Id de la tache : ");
        scanf("%d", &id);
        for (i = 0; i < count; i++)
        {
            if (tache[i].id == id)
            {
                printf("tache trouver : \n");
                printf("Id: %d\n", tache[i].id);
                printf("Titre: %d\n", tache[i].titre);
                printf("Description: %d\n", tache[i].description);
                printf("Deadline: %d\n", tache[i].DL.jour, tache[i].DL.mois, tache[i].DL.annee);
                printf("Statut: %s\n", tache[i].statut);
                trouve = 1;
                break;
            }
            if (trouve != 1)
            {
                printf("Aucune tache trouver avec l'Id %d.\n", id);
            }
            break;
        }
    case 2:
        printf("Entrez l'Id de la tache : ");
        scanf("%[^\n]", titre);
        for (i = 0; i < count; i++)
        {
            if (strcmp(tache[i].titre,titre) == 0)
            {
                printf("tache trouver : \n");
                printf("Id: %d\n", tache[i].id);
                printf("Titre: %d\n", tache[i].titre);
                printf("Description: %d\n", tache[i].description);
                printf("Deadline: %d\n", tache[i].DL.jour, tache[i].DL.mois, tache[i].DL.annee);
                printf("Statut: %s\n", tache[i].statut);
                trouve = 1;
                break;
            }
            if (trouve != 1)
            {
                printf("Aucune tache trouver avec le titre %s.\n", titre);
            }
            break;
        }
    default:
        printf("Choix invalide.\n");
        break;
    }
}
void Complitation()
{
    int complete = 0, incomplete = 0, i;
    for (i = 0; i < count; i++)
    {
        if (tache[i].statut == 3)
        {
            complete++;
        }
        else if (tache[i].statut == 1 || tache[i].statut == 2)
        {
            incomplete++;
        }
    }
    printf("Nombre de tache completes : %d\n", complete);
    printf("Nombre de tache incompletes : %d\n", incomplete);
}
void afficherJR()
{ // Jour Restants
    int i, JR;
    time_t t = time(NULL);
    struct tm dt = localtime(&t);
    int j = dt.tm_mday;
    int m = dt.tm_mon + 1;
    int a = dt.tm_year + 1900;
    printf("Nombre de jours restants jusqu'au delai de chaque tache: \n");
    for (i = 0; i < count; i++)
    {
        JR = (tache[i].DL.annee - a) * 365 + (tache[i].DL.mois - m) * 30 + (tache[i].DL.jour - j);
        printf("Id: %d\n", tache[i].id);
        printf("Titre: %d\n", tache[i].titre);
        printf("Description: %d\n", tache[i].description);
        printf("Deadline: %d\n", tache[i].DL.jour, tache[i].DL.mois, tache[i].DL.annee);
        printf("Statut: %s\n", tache[i].statut);
    }
}
void tacheStutat()
{
    if (count == 0)
    {
        printf("Aucune tache pour afficher.\n");
    }
    int choix;
    printf("Statistique des Taches.\n");
    printf("1 . Afficher le nombre total de taches.\n");
    printf("2 . Afficher le nombre de taches completes et incompletes.\n");
    printf("3 . Afficher le nombre de jours restants jusqu'au delai de chaque tache.\n");
    printf("Choix: ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        system("cls");
        printf("le nombre total des taches : %d\n", count);
        break;
    case 2:
        system("cls");
        Complitation();
        break;
    case 3:
        system("cls");
        afficherJR();
        break;
    default:
        system("cls");
        printf("Choix invalide.\n");
        break;
    }
}
void menu()
{
    printf("1 - Ajouter une tache \n");
    printf("2 - Ajouter plusiers taches \n");
    printf("3 - Afficher toutes les taches\n");
    printf("4 - Modifier une tache \n");
    printf("5 - Supprimier une tache \n");
    printf("6 - Rechercher une tache \n");
    printf("7 - Afficher les statistques \n");
    printf("8 - Quitter \n");
}

int main()
{
    int choix;
    menu();
    printf("Choix: ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        system("cls");
        ajoutUneTache();
        break;
    case 2:
        system("cls");
        ajoutMultiple();
        break;
    case 3:
        system("cls");
        afficherTaches();
        break;
    case 4:
        system("cls");
        modifierTache();
        break;
    case 5:
        system("cls");
        tacheSupprimer();
        break;
    case 6:
        system("cls");
        tacheRechercher();
        break;
    case 7:
        system("cls");
        tacheStutat();
        break;
    case 8:
        printf("Vous avez Quitter le programme.\n");
        break;
    default:
        system("cls");
        printf("Choix invalide.\n");
        break;
    }
    while (choix != 8)
        ;
}
