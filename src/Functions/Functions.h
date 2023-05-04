/* 
========== File Description ==========

*/

// Necessary library includes
#include <vector>
#include <sstream>
#include <iostream>
#include "../HeaderFiles/RegionClass.h"

// Necessary namespaces
using namespace std;
using json = nlohmann::json;

/* ========== Functions ========== */
// Creates a new user profile along with specified user credentials
void createNewUserProfile(string filePath, string username, string password) {
   // Open the file holding all the credential information in append mode
   ofstream filepath;
   filepath.open(filePath, ios::app);

   // Write the new username and passwords to the credential file
   filepath << endl << username << " " << password << endl;

   // Close credential file
   filepath.close();
}

// Print out all the elements of the string vector
void listElementsOfStringVector(vector<string> stringVector) {
    // If the given vector is not 0 than run through it and display
    // each element
    if (stringVector.size() != 0) {
        for (int i = 1; i <= stringVector.size(); i++) {
            cout << to_string(i) << ": " << stringVector[i - 1] << endl;
        }
    }
    // If it is 0 than print the following statement
    else {
        cout << "The list is empty" << endl;
    }
}

// Lists the names of all the objects that are within the region vector
void listObjectsWithinGivenVector(vector<Region> givenVector) {
    // If the given vector is not 0 than run through it and display
    // the names of all of the objects within it
    if (givenVector.size() != 0) {
        for (int i = 1; i <= givenVector.size(); i++) {
            cout << to_string(i) << ": " << givenVector[i - 1].getName() << endl;
        }
    }
    // If it is 0 than print the following statement
    else {
        cout << "The list is empty" << endl;
    }
}

// Lists the names of all the objects that are within the medical facility vector
void listObjectsWithinGivenVector(vector<MedicalFacility> givenVector) {
    // If the given vector is not 0 than run through it and display
    // the names of all of the objects within it
    if (givenVector.size() != 0) {
        for (int i = 1; i <= givenVector.size(); i++) {
            cout << to_string(i) << ": " << givenVector[i - 1].getName() << endl;
        }
    }
    // If it is 0 than print the following statement
    else {
        cout << "The list is empty" << endl;
    }
}

// Lists the names of all the objects that are within the patient vector
void listObjectsWithinGivenVector(vector<Patient> givenVector) {
    // If the given vector is not 0 than run through it and display
    // the names of all of the objects within it
    if (givenVector.size() != 0) {
        for (int i = 1; i <= givenVector.size(); i++) {
            cout << to_string(i) << ": " << givenVector[i - 1].getName() << endl;
        }
    }
    // If it is 0 than print the following statement
    else {
        cout << "The list is empty" << endl;
    }
}

// Lists the names of all the objects that are within the medical professional vector
void listObjectsWithinGivenVector(vector<MedicalProfessional> givenVector) {
    // If the given vector is not 0 than run through it and display
    // the names of all of the objects within it
    if (givenVector.size() != 0) {
        for (int i = 1; i <= givenVector.size(); i++) {
            cout << to_string(i) << ": " << givenVector[i - 1].getName() << endl;
        }
    }
    // If it is 0 than print the following statement
    else {
        cout << "The list is empty" << endl;
    }
}

// Converts given string value to a valid file name format
string convertNameToFileNameFormat(string regionName) {
    // Initialize various variables that will later be used to store
    // the given string as individually split words
    string word;
    string regionFileName;
    vector<string> wordsInRegionName;
    istringstream regionNameStream(regionName);

    // Create a while loop that will go through each word within the
    // previously initalized string stream
    while(regionNameStream >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word[0] = toupper(word[0]);
        wordsInRegionName.push_back(word);
    }

    // Concatenate all the strings inside string vector to one string
    // which will act as the file name for the newly created region
    regionFileName = accumulate(wordsInRegionName.begin(), wordsInRegionName.end(), string(""));

    // Return the string value that was just generated
    return regionFileName;
}

// Creates new medical facility object depending on the medical facility
// type that is passed
void createNewMedicalFacilityObject(Region& choosenRegion, string medicalFacilityName, string medicalFacilityAddress, string medicalFacilityType) {
    // Create a vector of patient objects to be used in the creation of
    // the new medical facility object
    vector<Patient> patients;

    // Depending on the type of medical facility, create a specific medical
    // facility object that will be stored into the medical facility vector
    if (medicalFacilityType == "Hospital") {
        Hospital medicalFacilityObject(medicalFacilityName, medicalFacilityAddress, medicalFacilityType, patients);
        choosenRegion.addNewFacilityToFacilityVector(medicalFacilityObject);
    }
    else if (medicalFacilityType == "Urgent Care") {
        UrgentCare medicalFacilityObject(medicalFacilityName, medicalFacilityAddress, medicalFacilityType, patients);
        choosenRegion.addNewFacilityToFacilityVector(medicalFacilityObject);
    }
    else {
        RehabilitationCenters medicalFacilityObject(medicalFacilityName, medicalFacilityAddress, medicalFacilityType, patients);
        choosenRegion.addNewFacilityToFacilityVector(medicalFacilityObject);
    }
}

// Creates new medical facility object depending on the medical facility
// type that is passed
void createNewMedicalProfessionalObject(Patient& choosenPatient, string medicalProfessionalName, string medicalProfessionalType, string medicalProfessionalSpecialization) {
    // Depending on the type of medical professional, create a specific medical
    // professional object that will be stored into the medical professional vector
    if (medicalProfessionalType == "Doctor") {
        Doctor medicalProfessionalObject(medicalProfessionalType, medicalProfessionalName, medicalProfessionalSpecialization);
        choosenPatient.addNewMedicalProfessionalToVector(medicalProfessionalObject);
    }
    else if (medicalProfessionalType == "Physical Therapist") {
        PhysicalTherapist medicalProfessionalObject(medicalProfessionalType, medicalProfessionalName, medicalProfessionalSpecialization);
        choosenPatient.addNewMedicalProfessionalToVector(medicalProfessionalObject);
    }
    else {
        Nurse medicalProfessionalObject(medicalProfessionalType, medicalProfessionalName, medicalProfessionalSpecialization);
        choosenPatient.addNewMedicalProfessionalToVector(medicalProfessionalObject);
    }
}

// Store json data into a variable and return
json returnJsonDataFromRegionFile(string regionFilePath) {
    // Open a specific medical facility region json file
    ifstream specificRegionFile(regionFilePath);

    // Store the initial contents of the entire json file into a json object
    json completeRegionJsonData;
    specificRegionFile >> completeRegionJsonData;

    // Close the specific json file
    specificRegionFile.close();

    // Return json object
    return completeRegionJsonData; 
}

// Set json data into json file
void setJsonDataIntoRegionFile(string regionFilePath, json completeRegionJsonData) {
    // Open a specific medical facility region json file, while also clearing it
    ofstream specificRegionFile(regionFilePath, ios::trunc);

    // Store this new json information into the specific json file
    specificRegionFile << completeRegionJsonData;

    // Close the specific json file
    specificRegionFile.close();
}

// Find index of medical facility within medical facility json array
int indexOfMedicalFacilityInJsonArray(json completeRegionJsonData, string chosenMedicalFacilityName) {
    // Initialization of variable that will store the index of a specific medical
    // facility
    int indexOfMedicalFacility;
    
    // For loop that tries to see the index value
    for (int i = 0; i < completeRegionJsonData["medical facilities"].size(); i++) {
        if (completeRegionJsonData["medical facilities"][i]["name"] == chosenMedicalFacilityName) {
            indexOfMedicalFacility = i;
        }
    }

    // Return saved index value
    return indexOfMedicalFacility;
}

// Find index of patient within patient json array
int indexOfPatientInJsonArray(json completeRegionJsonData, string chosenPatientName, int indexOfMedicalFacility) {
    // Initialization of variable that will store the index of a specific patient
    int indexOfPatient;

    // For loop that tries to see the index value
    for (int i = 0; i < completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"].size(); i++) {
        if (completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][i]["name"] == chosenPatientName) {
            indexOfPatient = i;
        }
    }

    // Return saved index value
    return indexOfPatient;
}

// Find index of medical professional within medical professional json array
int indexOfMedicalProfessionalInJsonArray(json completeRegionJsonData, string choseMedicalProfessionalName, int indexOfMedicalFacility, int indexOfPatient) {
    // Initialization of variable that will store the index of a specific medical professional
    int indexOfMedicalProfessional;

    // For loop that tries to see the index value
    for (int i = 0; i < completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][indexOfPatient]["medical professionals"].size(); i++) {
        if (completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][indexOfPatient]["medical professionals"][i]["name"] == choseMedicalProfessionalName) {
            indexOfMedicalProfessional = i;
        }
    }

    // Return saved index value
    return indexOfMedicalProfessional;
}