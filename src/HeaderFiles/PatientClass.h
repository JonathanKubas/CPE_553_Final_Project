/* 
========== File Description ==========
This file acts as the initialization of the Patient class.
*/

// Necessary library includes
#include <iostream>
#include <string>
#include <vector>
#include "MedicalProfessionals.h"

// Necessary namespaces
using namespace std;

/* ========== Patient Class ========== */
class Patient {
private:
    int age;
    string name;
    string illness;
    string status;
    vector<MedicalProfessional> medicalProfessionals;

public:
    // Constructor for initial reading of files during startup of script
    Patient(string name, int age, string illness, string status, vector<MedicalProfessional> medicalProfessionals) {
        this->name = name;
        this->age = age;
        this->illness = illness;
        this->status = status;
        this->medicalProfessionals = medicalProfessionals;
    }

    // Function that returns the name of the given patient
    string getName() {
        return name;
    }

    // Function that returns the age of the given patient
    int getAge() {
        return age;
    }

    // Function that returns the illness of the given patient
    string getIllness() {
        return illness;
    }

    // Function that returns the status of the given patient
    string getStatus() {
        return status;
    }

    void setIllness(string newIllness) {
        illness = newIllness;
    }

    void dischargePatient() {
        status = "Discharged";
    }

    // Function that returns the medical professional vector of the
    // given patient
    vector<MedicalProfessional> getMedicalProfessionalVector() {
        return medicalProfessionals;
    }

    // Function that adds a new medical professional object
    template <typename MedicalProfessionalType>
    void addNewMedicalProfessionalToVector(MedicalProfessionalType newMedicalProfessional) {
        medicalProfessionals.push_back(newMedicalProfessional);
    }
};