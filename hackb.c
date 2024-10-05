#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOCTORS 100
#define MAX_PATIENTS 100
#define DOCTOR_FILENAME "doctors.txt"
#define PATIENT_FILENAME "patients.txt"

struct Doctor {
    int id;
    char name[50];
    char specialty[50];
};

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addDoctor(struct Doctor *doctors, int *totalDoctors);
void addPatient(struct Patient *patients, int *totalPatients);
void displayDoctors(struct Doctor *doctors, int totalDoctors);
void displayPatients(struct Patient *patients, int totalPatients);
void loadDoctors(struct Doctor *doctors, int *totalDoctors);
void saveDoctors(struct Doctor *doctors, int totalDoctors);
void loadPatients(struct Patient *patients, int *totalPatients);
void savePatients(struct Patient *patients, int totalPatients);
void searchDoctor(struct Doctor *doctors, int totalDoctors);
void searchPatient(struct Patient *patients, int totalPatients);

int main() {
    struct Doctor doctors[MAX_DOCTORS];
    struct Patient patients[MAX_PATIENTS];
    int totalDoctors = 0;
    int totalPatients = 0;
    int choice;

    loadDoctors(doctors, &totalDoctors);
    loadPatients(patients, &totalPatients);

    while (1) {
        printf("\nPES UNIVERSITY HOSPITAL MANAGEMENT SYSTEM :\n");
        printf("1. Add Doctor\n");
        printf("2. Add Patient\n");
        printf("3. Display Doctors\n");
        printf("4. Display Patients\n");
        printf("5. Search Doctor\n");
        printf("6. Search Patient\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDoctor(doctors, &totalDoctors);
                break;
            case 2:
                addPatient(patients, &totalPatients);
                break;
            case 3:
                displayDoctors(doctors, totalDoctors);
                break;
            case 4:
                displayPatients(patients, totalPatients);
                break;
            case 5:
                searchDoctor(doctors, totalDoctors);
                break;
            case 6:
                searchPatient(patients, totalPatients);
                break;
            case 7:
                saveDoctors(doctors, totalDoctors);
                savePatients(patients, totalPatients);
                printf("THANKS FOR VISITING !\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void addDoctor(struct Doctor *doctors, int *totalDoctors) {
    if (*totalDoctors >= MAX_DOCTORS) {
        printf("Cannot add more doctors, maximum limit reached.\n");
        return;
    }
    printf("\nEnter details for doctor %d:\n", *totalDoctors + 1);
    printf("ID: ");
    scanf("%d", &doctors[*totalDoctors].id);
    getchar(); // clear the buffer
    printf("Name: ");
    fgets(doctors[*totalDoctors].name, sizeof(doctors[*totalDoctors].name), stdin);
    doctors[*totalDoctors].name[strcspn(doctors[*totalDoctors].name, "\n")] = '\0'; 
    printf("Specialty: ");
    fgets(doctors[*totalDoctors].specialty, sizeof(doctors[*totalDoctors].specialty), stdin);
    doctors[*totalDoctors].specialty[strcspn(doctors[*totalDoctors].specialty, "\n")] = '\0'; 

    (*totalDoctors)++;
    printf("Doctor added successfully!\n");
    saveDoctors(doctors, *totalDoctors); 
}

void addPatient(struct Patient *patients, int *totalPatients) {
    if (*totalPatients >= MAX_PATIENTS) {
        printf("Cannot add more patients, maximum limit reached.\n");
        return;
    }
    printf("\nEnter details for patient %d:\n", *totalPatients + 1);
    patients[*totalPatients].id = *totalPatients + 1;
    printf("Name: ");
    getchar(); // clear the buffer
    fgets(patients[*totalPatients].name, sizeof(patients[*totalPatients].name), stdin);
    patients[*totalPatients].name[strcspn(patients[*totalPatients].name, "\n")] = '\0';
    printf("Age: ");
    scanf("%d", &patients[*totalPatients].age);
    printf("Disease: ");
    getchar(); 
    fgets(patients[*totalPatients].disease, sizeof(patients[*totalPatients].disease), stdin);
    patients[*totalPatients].disease[strcspn(patients[*totalPatients].disease, "\n")] = '\0'; 

    (*totalPatients)++;
    printf("Patient added successfully!\n");
    savePatients(patients, *totalPatients);
}

void displayDoctors(struct Doctor *doctors, int totalDoctors) {
    if (totalDoctors == 0) {
        printf("No doctors available.\n");
        return;
    }
    printf("\nList of Doctors:\n");
    for (int i = 0; i < totalDoctors; i++) {
        printf("ID: %d\n", doctors[i].id);
        printf("Name: %s\n", doctors[i].name);
        printf("Specialty: %s\n", doctors[i].specialty);
        printf("\n");
    }
}

void displayPatients(struct Patient *patients, int totalPatients) {
    if (totalPatients == 0) {
        printf("No patients available.\n");
        return;
    }
    printf("\nList of Patients:\n");
    for (int i = 0; i < totalPatients; i++) {
        printf("ID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Disease: %s\n", patients[i].disease);
        printf("\n");
    }
}

void loadDoctors(struct Doctor *doctors, int *totalDoctors) {
    FILE *file = fopen(DOCTOR_FILENAME, "r");
    if (file == NULL) {
        printf("No existing doctor data found. Starting fresh.\n");
        return;
    }
    *totalDoctors = 0;
    while (fscanf(file, "%d,%49[^,],%49[^\n]\n", &doctors[*totalDoctors].id,
            doctors[*totalDoctors].name, doctors[*totalDoctors].specialty) != EOF) {
        (*totalDoctors)++;
    }
    fclose(file);
    printf("Loaded %d doctors from file.\n", *totalDoctors);
}

void saveDoctors(struct Doctor *doctors, int totalDoctors) {
    FILE *file = fopen(DOCTOR_FILENAME, "w");
    if (file == NULL) {
        printf("Error saving doctor data!\n");
        return;
    }
    for (int i = 0; i < totalDoctors; i++) {
        fprintf(file, "%d,%s,%s\n", doctors[i].id, doctors[i].name, doctors[i].specialty);
    }
    fclose(file);
    printf("Saved %d doctors to file.\n", totalDoctors);
}

void loadPatients(struct Patient *patients, int *totalPatients) {
    FILE *file = fopen(PATIENT_FILENAME, "r");
    if (file == NULL) {
        printf("No existing patient data found. Starting fresh.\n");
        return;
    }
    *totalPatients = 0;
    while (fscanf(file, "%d,%49[^,],%d,%49[^\n]\n", &patients[*totalPatients].id,
            patients[*totalPatients].name, &patients[*totalPatients].age,
            patients[*totalPatients].disease) != EOF) {
        (*totalPatients)++;
    }
    fclose(file);
    printf("Loaded %d patients from file.\n", *totalPatients);
}

void savePatients(struct Patient *patients, int totalPatients) {
    FILE *file = fopen(PATIENT_FILENAME, "w");
    if (file == NULL) {
        printf("Error saving patient data!\n");
        return;
    }
    for (int i = 0; i < totalPatients; i++) {
        fprintf(file, "%d,%s,%d,%s\n", patients[i].id, patients[i].name,
                patients[i].age, patients[i].disease);
    }
    fclose(file);
    printf("Saved %d patients to file.\n", totalPatients);
}

void searchDoctor(struct Doctor *doctors, int totalDoctors) {
    int choice;
    printf("Search Doctor by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("Enter Doctor ID: ");
        scanf("%d", &id);
        for (int i = 0; i < totalDoctors; i++) {
            if (doctors[i].id == id) {
                printf("Doctor found:\n");
                printf("ID: %d\n", doctors[i].id);
                printf("Name: %s\n", doctors[i].name);
                printf("Specialty: %s\n", doctors[i].specialty);
                return;
            }
        }
        printf("Doctor with ID %d not found.\n", id);
    } else if (choice == 2) {
        char name[50];
        printf("Enter Doctor Name: ");
        getchar(); // clear the buffer
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        for (int i = 0; i < totalDoctors; i++) {
            if (strcmp(doctors[i].name, name) == 0) {
                printf("Doctor found:\n");
                printf("ID: %d\n", doctors[i].id);
                printf("Name: %s\n", doctors[i].name);
                printf("Specialty: %s\n", doctors[i].specialty);
                return;
            }
        }
        printf("Doctor with name %s not found.\n", name);
    } else {
        printf("Invalid choice!\n");
    }
}

void searchPatient(struct Patient *patients, int totalPatients) {
    int choice;
    printf("Search Patient by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("Enter Patient ID: ");
        scanf("%d", &id);
        for (int i = 0; i < totalPatients; i++) {
            if (patients[i].id == id) {
                printf("Patient found:\n");
                printf("ID: %d\n", patients[i].id);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Disease: %s\n", patients[i].disease);
                return;
            }
        }
        printf("Patient with ID %d not found.\n", id);
    } else if (choice == 2) {
        char name[50];
        printf("Enter Patient Name: ");
        getchar(); // clear the buffer
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        for (int i = 0; i < totalPatients; i++) {
            if (strcmp(patients[i].name, name) == 0) {
                printf("Patient found:\n");
                printf("ID: %d\n", patients[i].id);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Disease: %s\n", patients[i].disease);
                return;
            }
        }
        printf("Patient with name %s not found.\n", name);
    } else {
        printf("Invalid choice!\n");
    }
}