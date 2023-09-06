#include <stdio.h>
#include <string.h>
#include <unistd.h>  // for sleep function

#define MAX_BUSES 10
#define MAX_SEATS 50
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20

typedef struct {
    int busNumber;
    int totalSeats;
    char passengerNames[MAX_SEATS][MAX_NAME_LENGTH];
    int passengerAge[MAX_SEATS];
    char passengerPhone[MAX_SEATS][MAX_PHONE_LENGTH];
    int bookedSeats;
} Bus;

Bus buses[MAX_BUSES];
int totalBuses = 0;

void initSampleBuses() {
    // Add some sample buses
    Bus bus1 = {1, 50, {0}, {0}, {0}, 0};
    strcpy(buses[totalBuses].passengerNames[0], "Reshma"); // Change bus name
    buses[totalBuses++] = bus1;

    Bus bus2 = {2, 40, {0}, {0}, {0}, 0};
    strcpy(buses[totalBuses].passengerNames[0], "Anand"); // Change bus name
    buses[totalBuses++] = bus2;

    Bus bus3 = {3, 60, {0}, {0}, {0}, 0};
    strcpy(buses[totalBuses].passengerNames[0], "Nishmitha"); // Change bus name
    buses[totalBuses++] = bus3;
}

void viewBusList() {
    printf("Bus List:\n");
    for (int i = 0; i < totalBuses; i++) {
        printf("%d. Bus Number: %d\n", i + 1, buses[i].busNumber);
    }
    printf("\n");
}

void displayTicket(int busNumber, int seatNumber) {
    printf("Ticket Details:\n");
    printf("Bus Number: %d\n", busNumber);
    printf("Seat Number: %d\n", seatNumber + 1);
    printf("Passenger Name: %s\n", buses[busNumber - 1].passengerNames[seatNumber]);
    printf("Passenger Age: %d\n", buses[busNumber - 1].passengerAge[seatNumber]);
    printf("Passenger Phone: %s\n", buses[busNumber - 1].passengerPhone[seatNumber]);
    printf("----------------------------\n");
}

void bookTickets() {
    int busNumber, numTickets;
    printf("Enter the bus number: ");
    scanf("%d", &busNumber);

    // Search for the bus in the list
    int index = -1;
    for (int i = 0; i < totalBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Bus with number %d not found!\n", busNumber);
        return;
    }

    Bus *bus = &buses[index];

    printf("Total seats in bus %d: %d\n", busNumber, bus->totalSeats);
    printf("Enter the number of tickets to book: ");
    scanf("%d", &numTickets);

    if (bus->bookedSeats + numTickets > bus->totalSeats) {
        printf("Sorry, only %d seats are available.\n", bus->totalSeats - bus->bookedSeats);
        return;
    }

    for (int i = bus->bookedSeats; i < bus->bookedSeats + numTickets; i++) {
        printf("Enter details for Seat %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", bus->passengerNames[i]);
        printf("Age: ");
        scanf("%d", &bus->passengerAge[i]);
        printf("Phone number: ");
        scanf("%s", bus->passengerPhone[i]);

        // Display the ticket information with animation
        printf("Printing ticket...");
        fflush(stdout);
        usleep(1000000);  // Sleep for 1 second (simulate printing)
        printf("done!\n");

        // Display the ticket information immediately
        displayTicket(busNumber, i);
    }

    bus->bookedSeats += numTickets;
    printf("%d tickets booked successfully.\n", numTickets);
}

void displayTicketLater() {
    int busNumber, seatNumber;
    printf("Enter the bus number: ");
    scanf("%d", &busNumber);

    // Search for the bus in the list
    int index = -1;
    for (int i = 0; i < totalBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Bus with number %d not found!\n", busNumber);
        return;
    }

    Bus *bus = &buses[index];

    printf("Enter the seat number to display the ticket: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > bus->bookedSeats) {
        printf("Invalid seat number!\n");
        return;
    }

    // Display the ticket information
    displayTicket(busNumber, seatNumber - 1);
}

void modifyBusRecord() {
    int busNumber;
    printf("Enter the bus number: ");
    scanf("%d", &busNumber);

    // Search for the bus in the list
    int index = -1;
    for (int i = 0; i < totalBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Bus with number %d not found!\n", busNumber);
        return;
    }

    Bus *bus = &buses[index];

    printf("Total seats in bus %d: %d\n", busNumber, bus->totalSeats);
    printf("Enter the new total number of seats: ");
    scanf("%d", &bus->totalSeats);

    if (bus->totalSeats < bus->bookedSeats) {
        printf("Warning: The new total seats are less than the already booked seats!\n");
    }

    printf("Bus record modified successfully.\n");
}

void checkBusStatus() {
    int busNumber;
    printf("Enter the bus number: ");
    scanf("%d", &busNumber);

    // Search for the bus in the list
    int index = -1;
    for (int i = 0; i < totalBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Bus with number %d not found!\n", busNumber);
        return;
    }

    Bus *bus = &buses[index];

    printf("Bus Number: %d\n", bus->busNumber);
    printf("Total seats: %d\n", bus->totalSeats);
    printf("Booked seats: %d\n", bus->bookedSeats);
    printf("Passenger details:\n");
    for (int i = 0; i < bus->bookedSeats; i++) {
        printf("Seat %d: %s, Age: %d, Phone: %s\n", i + 1, bus->passengerNames[i], bus->passengerAge[i], bus->passengerPhone[i]);
    }
}

int main() {
    initSampleBuses();

    int choice;
    do {
        printf("Bus Reservation System\n");
        printf("1. View bus list\n");
        printf("2. Book tickets and display immediately\n");
        printf("3. Display ticket later\n");
        printf("4. Modify bus record\n");
        printf("5. Check bus status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewBusList();
                break;
            case 2:
                bookTickets();
                break;
            case 3:
                displayTicketLater();
                break;
            case 4:
                modifyBusRecord();
                break;
            case 5:
                checkBusStatus();
                break;
            case 6:
                printf("Thank you for using the Bus Reservation System.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
