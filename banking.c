#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct bookings
{                                 // struct element mit namen bookings
    struct bookings *nextBooking; // Pointer auf den nächsten einttrag der liste
    float amount;                 // float zahl für die Megnge des betrages mit nachkommastellen
    char description[40];         // Beschreibung mit 39 Zeichen + 1 Zeichen "\0"
} T_bookings;                     // typedef name des structs

typedef struct customers
{                                   // struct element mit namen customers
    char forename[40];              // string mit dem Vornamen (39 Zeichen + 1 Zeichen "\0")
    char surname[40];               // string mit dem Nachnamen (39 Zeichen + 1 Zeichen "\0")
    struct bookings *firstBooking;  // booking Pointer der auf das erste Element aus der booking liste zeigen soll
    struct customers *nextCustomer; // customer Pointer der auf den nächsten customer in der liste zeigen soll
} T_customer;                       // typedef name des structs

T_customer *root_customer = NULL; // Wurzel der Customer liste erstellt und NULL gesetzt
T_customer *start_customer;       // start adresse der Customer liste

void addCustomer(char firstName[40], char lastName[40])
{                                                                         // Hier soll ein Kunde in die Liste hinzugefügt werden und der speicher dafür reservieren
                                                                          // es ist eine Void funktion, da keine werte zurückgegeben werden sollen
    T_customer *temp_customer = (T_customer *)malloc(sizeof(T_customer)); // Neues LE erstellt und speicher reserviert
    if (temp_customer == NULL)
        exit(-1); // Neues LE wird auf NULL Überprüft um einen eventuellen vollen speicher zu erkennen

    strcpy(temp_customer->forename, firstName); // der inhalt von firstName wird in das LE kopiert
    strcpy(temp_customer->surname, lastName);   // der inhalt von lastName wird in das LE kopiert

    temp_customer->nextCustomer = NULL; // der Pointer auf nextCustomer des neuen LE wird auf NULL gesetzt um bugs zu vermeiden
    temp_customer->firstBooking = NULL; // der Pointer auf firstBooking des neuen LE wird auf NULL gesetzt um bugs zu vermeiden

    if (root_customer == NULL) // Über prüfung ob Wurzel der Customerliste NULL ist bzw das erste LE ist
    {
        root_customer = temp_customer;  // der Wurzel wird das Neue LE zugewiesen
        start_customer = temp_customer; // dem start_customer wird der anfang der Liste zugewiesen
        return;                         // Hier wird die addCustomer funktion abgebrochen und zur main zurückgekehrt
    }

    root_customer->nextCustomer = temp_customer; // das nächste element der Wurzel wird zu der aktuellen adresse geändert
    temp_customer->nextCustomer = NULL;          // der next Pointer meines neuen LE wird auf Null gesetzt da kein weiterer eintrag nach diesem gibt
    root_customer = temp_customer;               // die wurzel wird zu der adresse des jetztigen elementes um später ein neues Element an dieses anzuhängen
}

void addBooking(int customerID, float amout, char details[40])
{ // Hier soll eine Buchung für den Kunden mit der Kennzahl customer id hinzgefügt werden mit betrag und beschreibung

    T_bookings *temp = (T_bookings *)malloc(sizeof(T_bookings)); // Das neue LE wird erstellt und der speicher dafür reserviert
    if (temp == NULL)
        exit(-1); // das neue Element wird überprüft ob der speicher voll ist

    int count = 0; // ein counter wird erstellt und 0 zugewiesen

    T_customer *customer = start_customer; // Eine Kopie wird von anfang der customer liste erstellt da man nicht auf dem Orginal arbeiten möchte

    while (customer != NULL && count < customerID)
    {                                      // Hier wird durch die customer liste iteriert und abgebrochen wenn count >= customerID
        customer = customer->nextCustomer; // customer wird das nächste element zugewiesen
        count += 1;                        // counter wird erhöht für die abbruchbedingung
    }

    temp->amount = amout;               // Der Betrag wird dem LE zugewiesen
    strcpy(temp->description, details); // Die Details werden in das LE Kopiert
    temp->nextBooking = NULL;           // Der Pointer des LE wird auf NULL gesetzt da kein folgendes element existiert

    if (customer->firstBooking == NULL)
    {                                  // Es wird überprüft ob bereits eine Buchung existiert
        customer->firstBooking = temp; // Falls keine Buchung existiert wird das Neue LE der Buchung zugewiesen
        return;                        // Die Funktion wird abgebrochen
    }

    T_bookings *bookings = customer->firstBooking; // Eine Kopie des Ersten Elementes des bookings wird erstellt

    while (bookings->nextBooking != NULL) // Es wird über die bookings Liste iteriert bis das Element das letzte ist
    {
        bookings = bookings->nextBooking; // adresse wird um eins erhöht
    }

    bookings->nextBooking = temp; // Der next Pointer des aktuellen Elementes wird auf das Neue Element gesetzt
}

void printCustomer()
{ // Alle Customer sollen ausgegeben werden mit der zugehörigen Kundennummer

    int count = 0; // Ein counter der die Kundennummer wird

    printf("Customers:\n"); // Einfache ausgabe des strings, die immer gedruckt wird

    T_customer *temp = start_customer; // Eine Kopie der adresse vom Anfang der Customer liste wird erstellt da man nicht auf dem Orginal arbeiten soll

    if (temp != NULL)
    { // Falls die Customer liste nicht Leer ist wird die Schleife betreten

        printf("|  #  | %-40s | %-40s |\n", "Forename", "Surname"); // Formatierte ausgabe des headers der Tabelle
        printf("---------------------------------------------------------------------------------------------\n");

        while (temp != NULL)
        { // Iteration durch die Customer liste

            printf("| %03d | %-40s | %-40s |\n", count, temp->forename, temp->surname); // Formatierte ausgabe des Kunden und zugehörige Kundennummer und Namen
            temp = temp->nextCustomer;                                                  // Die adresse des LE wird erhöht
            count++;                                                                    // Der counter wird erhöht
        }
    }
}

void printBookings(float customerID)
{ // DIe Buchungen eines bestimmten Kunden soll ausgegeben werden

    int count = 0; // counter wird erstellt

    T_customer *temp = start_customer; // Kopie der Adresse vom anfang der Customer Liste
    T_bookings *bookings;              // eine booking variable wird erstellt

    while (temp != NULL && count < customerID) // Der benutzer mit der Kundennummer customerID wird gesucht und in temp gespeichert
    {
        temp = temp->nextCustomer; // adresse von temp wird erhöht
        count += 1;                // counter wird erhöht
    }

    count = 0; // counter wird auf 0 gesetzt um als Zähler für die Bookings zu verwenden

    printf("All Bookings from %s %s:\n", temp->forename, temp->surname); // Text wird immer ausgegeben mit Name des kunden der Kundennummer

    if (temp->firstBooking != NULL)
    {                                  // Es wird überprüft ob die booking liste leer ist
        bookings = temp->firstBooking; // in die Booking Variable wird die adresse  der ersten buchung gespeichert

        printf("| %3s | %12s | %-40s |\n", "#", "Amount", "Description"); // Der Header der tabelle wird gedruckt
        printf("-----------------------------------------------------------------\n");

        while (bookings != NULL)
        {                                                                                                 // Solange eine Buchung existiert wird durch die Liste iteriert
            printf("| %03d | %10.2f %c | %-40s |\n", count, bookings->amount, 36, bookings->description); // Formatierte ausgabe der variablen
            count += 1;                                                                                   // counter wird erhöht
            bookings = bookings->nextBooking;                                                             // die adresse von booking wird erhöht
        }
    }
}

void clear()
{ // jeder reservierte speicher soll freigegeben werden

    while (root_customer != NULL) // solange die Customer liste nicht Leer ist wird durch diese Iteriert ///// FEHLER ////////
    {
        T_bookings *bookings = root_customer->firstBooking; // die adresse von dem jeweiligen Kunden seiner ersten buchung wird zwischengespeichert

        while (bookings != NULL) // Solange noch Buchungen existieren wird durch die Liste Iteriert
        {

            T_bookings *save = bookings->nextBooking; // die adresse der nächsten buchung wird in save zwischengespeichert
            free(bookings);                           // Der speicher der Aktuellen Adresse wird freigegeben
            bookings = save;                          // in bookings wird die adresse des nächsten elementes gespeichert
        }

        T_customer *customer = root_customer->nextCustomer; // Die adresse der nächsten buchung wird zwischengespeichert
        free(root_customer);                                // Der reservierte Speicher der adresse wird freigegeben
        root_customer = customer;                           // Die adresse wird um eines erhöht
    }
}

int main()
{
    char type[10], command[10], firstname[40], lastname[40], details[40];
    int customerID = 0;
    float amout = 0;
    bool exit = true;

    do
    {

        printf("> ");
        scanf("%s", type);

        if (strcmp(type, "add") == 0)
        {

            scanf("%s", command);

            if (strcmp(command, "customer") == 0)
            {

                scanf("%s %s", firstname, lastname);
                addCustomer(firstname, lastname);
            }
            else if (strcmp(command, "booking") == 0)
            {

                scanf("%d %f %s", &customerID, &amout, details);
                addBooking(customerID, amout, details);
            }
        }
        else if (strcmp(type, "list") == 0)
        {

            scanf("%s", command);

            if (strcmp(command, "customer") == 0)
            {

                printCustomer();
            }
            else if (strcmp(command, "booking") == 0)
            {

                scanf("%d", &customerID);
                printBookings(customerID);
            }
        }
        else if (strcmp(type, "exit") == 0)
        {

            clear();
            exit = false;
        }

    } while (exit);

    return 0;
}