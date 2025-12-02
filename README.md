# 📂 Contact Management System using Doubly Linked List

This project is a complete implementation in the C programming language of a simple contact management system. It uses a *Doubly Linked List (LDL)* to store contact records (Name and Phone Number), allowing for efficient operations in both forward and backward directions.

This work was developed as part of the *Advanced Data Structures* module.

## 🚀 Implemented Features

The system manages contacts and includes the following essential operations:

| Function | Description | Source |
| :--- | :--- | :--- |
| creerListe | Creates and initializes the ListeContacts structure. | Creates and initializes the ListeContacts structure. |
| ajouterDebut | Adds a new contact to the beginning of the list and updates pointers/size. | Adds a new contact to the beginning of the list and updates pointers/size. |
| ajouterFin | Adds a new contact to the end of the list and updates pointers/size. | Adds a new contact to the end of the list and updates pointers/size. |
| ajouterApres | Adds a new contact after the contact with the specified name (nomCible). | Adds a new contact after the contact with the specified name (nomCible). |
| supprimerContact | Deletes the contact with the specified name, handling cases where the contact is at the head, tail, or middle of the list. | Deletes the contact with the specified name. |
| rechercherContact | Searches for a contact by name and returns a pointer to it (or NULL if not found). | Searches for a contact by name and returns a pointer to it (or NULL if not found). |
| afficherListeAvant | Displays the list from the beginning to the end (Head to Tail). | Displays the list from the beginning to the end (Head to Tail). |
| afficherListeArriere | Displays the list from the end to the beginning (Tail to Head), demonstrating the advantage of doubly linked lists. | Displays the list from the end to the beginning (Tail to Head). |
| trierListe | Sorts the list alphabetically by contact name, using a sorting algorithm of choice. | Sorts the list alphabetically by contact name. |
| viderListe | Frees all memory used by the list to prevent memory leaks. | Frees all memory used by the list. |

## ⚙️ Data Structures

The project relies on the following C structures:

```c
typedef struct Contact {
    char nom[50];
    char telephone[20];
    struct Contact* precedent;
    struct Contact* suivant;
} Contact;

typedef struct {
    Contact* tete;
    Contact* queue;
    int taille;
} ListeContacts;
