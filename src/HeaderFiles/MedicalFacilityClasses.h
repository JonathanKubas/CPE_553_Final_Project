/* 
========== File Description ==========
This file acts as the initialization of the Medical Facility class and its
various children classes.
*/

// Necessary library includes
#include <iostream>
#include <vector>
#include "PatientClass.h"

// Necessary namespaces
using namespace std;

/* ========== Hospital Class ========== */
class MedicalFacility {
private:
    string name;
    string address;
    string type;
    vector<Patient> patients;

public:
    // Constructor for initial reading of files during startup of script
    MedicalFacility(string name, string address, string type, vector<Patient> patients) {
        this->name = name;
        this->address = address;
        this->type = type;
        this->patients = patients;
    }

    // Function that returns the name of the given medical facility
    string getName() {
        return name;
    }

    // Function that returns the address of the given medical facility
    string getAddress() {
        return address;
    }

    // Function that returns the type of the given medical facility
    string getType() {
        return type;
    }

    // Function that returns the patient vector of the given medical facility
    vector<Patient> getPatientVector() {
        return patients;
    }

    // Function that adds a new patient object 
    void addNewPatientProfileToVector(Patient newPatient) {
        patients.push_back(newPatient);
    }
};

/* ========== Hospital Class ========== */
class Hospital : public MedicalFacility {
private:
    string name;
    string address;
    string type;
    vector<Patient> patients;

public:
    // Constructor for initial reading of files during startup of script
    Hospital(string name, string address, string type, vector<Patient> patients) : MedicalFacility(name, address, type, patients) {
        this->name = name;
        this->address = address;
        this->type = type;
        this->patients = patients;
    }

    // Function that returns the name of the given medical facility
    string getName() {
        return name;
    }

    // Function that returns the address of the given medical facility
    string getAddress() {
        return address;
    }

    // Function that returns the type of the given medical facility
    string getType() {
        return "Hospital";
    }

    // Function that returns the patient vector of the given medical facility
    vector<Patient> getPatientVector() {
        return patients;
    }

    // Function that adds a new patient object 
    void addNewPatientProfileToVector(Patient newPatient) {
        patients.push_back(newPatient);
    }
};

/* ========== Hospital Class ========== */
class UrgentCare : public MedicalFacility {
private:
    string name;
    string address;
    string type;
    vector<Patient> patients;

public:
    // Constructor for initial reading of files during startup of script
    UrgentCare(string name, string address, string type, vector<Patient> patients) : MedicalFacility(name, address, type, patients) {
        this->name = name;
        this->address = address;
        this->type = type;
        this->patients = patients;
    }

    // Function that returns the name of the given medical facility
    string getName() {
        return name;
    }

    // Function that returns the address of the given medical facility
    string getAddress() {
        return address;
    }

    // Function that returns the type of the given medical facility
    string getType() {
        return "Urgent Care";
    }

    // Function that returns the patient vector of the given medical facility
    vector<Patient> getPatientVector() {
        return patients;
    }

    // Function that adds a new patient object 
    void addNewPatientProfileToVector(Patient newPatient) {
        patients.push_back(newPatient);
    }
};

/* ========== Hospital Class ========== */
class RehabilitationCenters: public MedicalFacility {
private:
    string name;
    string address;
    string type;
    vector<Patient> patients;

public:
    // Constructor for initial reading of files during startup of script
    RehabilitationCenters(string name, string address, string type, vector<Patient> patients) : MedicalFacility(name, address, type, patients) {
        this->name = name;
        this->address = address;
        this->type = type;
        this->patients = patients;
    }

    // Function that returns the name of the given medical facility
    string getName() {
        return name;
    }

    // Function that returns the address of the given medical facility
    string getAddress() {
        return address;
    }

    // Function that returns the type of the given medical facility
    string getType() {
        return "Rehabilitation Center";
    }

    // Function that returns the patient vector of the given medical facility
    vector<Patient> getPatientVector() {
        return patients;
    }

    // Function that adds a new patient object 
    void addNewPatientProfileToVector(Patient newPatient) {
        patients.push_back(newPatient);
    }
};