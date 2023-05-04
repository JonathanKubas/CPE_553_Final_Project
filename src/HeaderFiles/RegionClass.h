/* 
========== File Description ==========

*/

// Necessary library includes
#include <iostream>
#include <vector>
#include "MedicalFacilityClasses.h"

// Necessary namespaces
using namespace std;

/* ========== Region Class ========== */
class Region {
private:
   string name;
   string filePath;
   vector<MedicalFacility> medicalFacilities;

public:
   // Constructor for initial reading of files during startup of script
    Region(string name, string filePath, vector<MedicalFacility> medicalFacilities) {
        this->name = name;
        this->filePath = filePath;
        this->medicalFacilities = medicalFacilities;
    }

    // Function that returns the name of the given region
    string getName() {
        return name;
    }

    // Function that returns the file path of the given region
    string getFilePath() {
        return filePath;
    }

    // Function that returns the medical facility vector of the given region
    vector<MedicalFacility> getMedicalFacilityVector() {
        return medicalFacilities;
    }

    // Function that adds a new medical facility to the medical facility vector
    template <typename MedicalFacilityType>
    void addNewFacilityToFacilityVector(MedicalFacilityType& newMedicalFacility) {
        medicalFacilities.push_back(newMedicalFacility);
    }
};