#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 100
#define NAME_LENGTH 50

typedef struct {
    int patient_id;
    char name[NAME_LENGTH];
    int age;
    char ailment[NAME_LENGTH];
    int doctor_id; // Added field to store assigned doctor's ID
} Patient;

typedef struct {
    int doctor_id;
    char name[NAME_LENGTH];
    char specialty[NAME_LENGTH];
    int years_of_experience;
} Doctor;

Patient patients[MAX_PATIENTS];
Doctor doctors[MAX_DOCTORS];
int patient_count = 0;
int doctor_count = 0;

// Function to add a patient
void add_patient(int id, const char* name, int age, const char* ailment) {
    if (patient_count >= MAX_PATIENTS) {
        printf("Patient list is full.\n");
        return;
    }
    patients[patient_count].patient_id = id;
    strncpy(patients[patient_count].name, name, NAME_LENGTH);
    patients[patient_count].age = age;
    strncpy(patients[patient_count].ailment, ailment, NAME_LENGTH);
    patients[patient_count].doctor_id = -1; // No doctor assigned initially
    patient_count++;
    printf("Patient added successfully.\n");
}

// Function to view a patient
void view_patient(int id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].patient_id == id) {
            printf("Patient[ID: %d, Name: %s, Age: %d, Ailment: %s, Assigned Doctor ID: %d]\n",
                   patients[i].patient_id, patients[i].name, patients[i].age, patients[i].ailment,
                   patients[i].doctor_id);
            return;
        }
    }
    printf("Patient not found.\n");
}

// Function to delete a patient
void delete_patient(int id) {
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].patient_id == id) {
            for (int j = i; j < patient_count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patient_count--;
            printf("Patient deleted successfully.\n");
            return;
        }
    }
    printf("Patient not found.\n");
}

// Function to add a doctor
void add_doctor(int id, const char* name, const char* specialty, int years_of_experience) {
    if (doctor_count >= MAX_DOCTORS) {
        printf("Doctor list is full.\n");
        return;
    }
    doctors[doctor_count].doctor_id = id;
    strncpy(doctors[doctor_count].name, name, NAME_LENGTH);
    strncpy(doctors[doctor_count].specialty, specialty, NAME_LENGTH);
    doctors[doctor_count].years_of_experience = years_of_experience;
    doctor_count++;
    printf("Doctor added successfully.\n");
}

// Function to view a doctor
void view_doctor(int id) {
    for (int i = 0; i < doctor_count; i++) {
        if (doctors[i].doctor_id == id) {
            printf("Doctor[ID: %d, Name: %s, Specialty: %s, Experience: %d years]\n",
                   doctors[i].doctor_id, doctors[i].name, doctors[i].specialty, doctors[i].years_of_experience);
            return;
        }
    }
    printf("Doctor not found.\n");
}

// Function to delete a doctor
void delete_doctor(int id) {
    for (int i = 0; i < doctor_count; i++) {
        if (doctors[i].doctor_id == id) {
            for (int j = i; j < doctor_count - 1; j++) {
                doctors[j] = doctors[j + 1];
            }
            doctor_count--;
            printf("Doctor deleted successfully.\n");
            return;
        }
    }
    printf("Doctor not found.\n");
}

// Function to assign a doctor to a patient
void assign_doctor_to_patient(int patient_id, int doctor_id) {
    int patient_found = 0;
    int doctor_found = 0;
    for (int i = 0; i < patient_count; i++) {
        if (patients[i].patient_id == patient_id) {
            patient_found = 1;
            for (int j = 0; j < doctor_count; j++) {
                if (doctors[j].doctor_id == doctor_id) {
                    doctor_found = 1;
                    patients[i].doctor_id = doctor_id;
                    printf("Doctor %s assigned to Patient %s successfully.\n", doctors[j].name, patients[i].name);
                    return;
                }
            }
            if (!doctor_found) {
                printf("Doctor not found.\n");
                return;
            }
        }
    }
    if (!patient_found) {
        printf("Patient not found.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- PES University Hospital Management System ---\n");
        printf("1. Add Patient\n");
        printf("2. View Patient\n");
        printf("3. Delete Patient\n");
        printf("4. Add Doctor\n");
        printf("5. View Doctor\n");
        printf("6. Delete Doctor\n");
        printf("7. Assign Doctor to Patient\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int id, age, years_of_experience, patient_id, doctor_id;
        char name[NAME_LENGTH], ailment[NAME_LENGTH], specialty[NAME_LENGTH];

        switch (choice) {
            case 1:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Age: ");
                scanf("%d", &age);
                printf("Enter Ailment: ");
                scanf("%s", ailment);
                add_patient(id, name, age, ailment);
                break;
            case 2:
                printf("Enter Patient ID to View: ");
                scanf("%d", &id);
                view_patient(id);
                break;
            case 3:
                printf("Enter Patient ID to Delete: ");
                scanf("%d", &id);
                delete_patient(id);
                break;
            case 4:
                printf("Enter Doctor ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Specialty: ");
                scanf("%s", specialty);
                printf("Enter Years of Experience: ");
                scanf("%d", &years_of_experience);
                add_doctor(id, name, specialty, years_of_experience);
                break;
            case 5:
                printf("Enter Doctor ID to View: ");
                scanf("%d", &id);
                view_doctor(id);
                break;
            case 6:
                printf("Enter Doctor ID to Delete: ");
                scanf("%d", &id);
                delete_doctor(id);
                break;
            case 7:
                printf("Enter Patient ID: ");
                scanf("%d", &patient_id);
                printf("Enter Doctor ID: ");
                scanf("%d", &doctor_id);
                assign_doctor_to_patient(patient_id, doctor_id);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
