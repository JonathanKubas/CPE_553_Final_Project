/* 
========== File Description ==========

*/

// Necessary library includes
#include <iostream>
#include <string>

// Necessary namespaces
using namespace std;

/* ========== Medical Professional Class ========== */
class MedicalProfessional {
private:
    string type;
    string name;
    string specialization;

public:
    // Constructor for initial reading of files during startup of script
    MedicalProfessional(string type, string name, string specialization) {
        this->type = type;
        this->name = name;
        this->specialization = specialization;
    }

    // Function that returns the name of the given medical professional
    string getName() {
        return name;
    }

    // Function that returns the specialization of the given medical professional
    string getSpecialization() {
        return specialization;
    }

    // Function that returns the type of the given medical professional
    string getType() {
        return type;
    }

    // Function that sets the new specialization of the medical professional
    void setSpecialization(string newSpecialization) {
        specialization = newSpecialization;
    }
};

/* ========== Doctor Class ========== */
class Doctor : public MedicalProfessional {
private:
    string type;
    string name;
    string specialization;

public:
    // Constructor for initial reading of files during startup of script
    Doctor(string type, string name, string specialization) : MedicalProfessional(type, name, specialization) {
        this->type = type;
        this->name = name;
        this->specialization = specialization;
    }

    // Function that returns the name of the given medical professional
    string getName() {
        return name;
    }

    // Function that returns the specialization of the given medical professional
    string getSpecialization() {
        return specialization;
    }

    // Function that returns the type of the given medical professional
    string getType() {
        return "Doctor";
    }

    // Function that sets the new specialization of the medical professional
    void setSpecialization(string newSpecialization) {
        specialization = newSpecialization;
    }
};

/* ========== Physical Therapist Class ========== */
class PhysicalTherapist : public MedicalProfessional {
private:
    string type;
    string name;
    string specialization;

public:
    // Constructor for initial reading of files during startup of script
    PhysicalTherapist(string type, string name, string specialization) : MedicalProfessional(type, name, specialization) {
        this->type = type;
        this->name = name;
        this->specialization = specialization;
    }

    // Function that returns the name of the given medical professional
    string getName() {
        return name;
    }

    // Function that returns the specialization of the given medical professional
    string getSpecialization() {
        return specialization;
    }

    // Function that returns the type of the given medical professional
    string getType() {
        return "Physical Therapist";
    }

    // Function that sets the new specialization of the medical professional
    void setSpecialization(string newSpecialization) {
        specialization = newSpecialization;
    }
};

/* ========== Nurse Class ========== */
class Nurse : public MedicalProfessional {
private:
    string type;
    string name;
    string specialization;

public:
// Constructor for initial reading of files during startup of script
    Nurse(string type, string name, string specialization) : MedicalProfessional(type, name, specialization) {
        this->type = type;
        this->name = name;
        this->specialization = specialization;
    }

    // Function that returns the name of the given medical professional
    string getName() {
        return name;
    }

    // Function that returns the specialization of the given medical professional
    string getSpecialization() {
        return specialization;
    }

    // Function that returns the type of the given medical professional
    string getType() {
        return "Nurse";
    }

    // Function that sets the new specialization of the medical professional
    void setSpecialization(string newSpecialization) {
        specialization = newSpecialization;
    }
};