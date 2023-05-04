/*
============================== Project Description ============================== 
With the continuous uptick in the United States' population, hospitals are seeing
an increasing amount of patients that are both entering and leaving through their
doors on a daily basis. For smaller hospitals, this doesn't seem to be as big of
an issue. However, for the hospitals that are in more densely populated areas, the
fear of either misplacing or misdiagnosing a patient is one that is constantly
hanging over the heads of the medical professionals that work at these facilities.
To help provide a solution to this dangerous situation, this program is supposed
to act as an interactive user interface that will allow the individuals working at
various medical locations to access and store medical facility and patient
information in real time. Specifics on how this script works can either be found in
the various comment chunks the are placed in several areas throughout this program
or in the README.md file that was added to this script.
*/

// Necessary library includes
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "src/Functions/Functions.h"
#include "src/SwitchStatements/SwitchStatements.h"

// Necessary using statements
using namespace std;
using json = nlohmann::json;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

/* ========== Main Program ========== */
int main() {
   // Get current working path associated with this script and initialize it within
   // a string variable
   filesystem::path currentWorkingPathOfScript = filesystem::current_path();
   string currentWorkingPathOfScriptString = currentWorkingPathOfScript.string();

   // Initialize necessary variables for credential verification
   string line = "";
   string username = "";
   string password = "";
   vector<string> usernameVector;
   vector<string> passwordVector;
   bool validCredentials = false;

   // Open the file holding all the credential information
   ifstream credentialFile;
   string credentialFilePath = currentWorkingPathOfScriptString + "\\src\\UserCredentials\\credentials.txt"; 
   credentialFile.open(credentialFilePath);

   // Print statements to help format login screen
   cout << " " << endl;
   cout << "               Login Screen               " << endl;
   cout << "==========================================" << endl;

   // Display message to user to tell them to input their credentials to gain
   // access to medical facility information
   while (validCredentials == false) {
      // Prompt user to enter their credentials
      cout << "Please input your credentials to enter the\nmedical facility manager:" << endl;
      cout << "Username: ";
      cin >> username;
      cout << "Password: ";
      cin >> password;
      
      // Loop through credential file to see if user's inputted credentials are
      // within the file
      while (getline(credentialFile, line)) {
         // Initialize temporary credential variables
         string tempUsername = "";
         string tempPassword = "";
         
         // Convert stream to a valid string
         stringstream credentialStream(line);

         // Store username and password from specific line
         credentialStream >> tempUsername;
         credentialStream >> tempPassword;

         // Append temporary username and password to end of their respective vectors
         usernameVector.push_back(tempUsername);
         passwordVector.push_back(tempPassword);
      }

      // Check to see if user's inputted credentials are in the credentials file.
      // If they are, than set valid variable to true and if not keep it as false
      for (int i = 0; i < usernameVector.size(); i++) {
         if ((usernameVector[i] == username) && (passwordVector[i] == password)) {
            validCredentials = true;
         }
      }

      // If valid variable is still false, print message to user that their inputted
      // username and password combination was not valid and that they will have to
      // try again
      if (validCredentials == false) {
         cout << "Inputted username and password pair do not exit, please try again!" << endl;
      }

      // And an extra space for formality
      cout << " " << endl;
   }

   // Now close the credentials file to avoid risk of data corruption
   credentialFile.close();

   // Initialize variables to store the file paths of region configuration files
   vector<string> regionConfigFilePaths;
   string regionConfigDirectory = currentWorkingPathOfScriptString + "\\src\\RegionConfigs";

   // Go through the entire given directory and store the file paths as strings
   for (const auto& filePath : recursive_directory_iterator(regionConfigDirectory)) {
      regionConfigFilePaths.push_back(filePath.path().string());
   }

   // Iterate through each file path, open it, store it's json data and than transform
   // that json data into a format that works with region, medical facility, patient,
   // and medical professional objects
   vector<Region> savedRegions;
   if (regionConfigFilePaths.empty() != true) {
      for (int i = 0; i < regionConfigFilePaths.size(); i++) {
         // Save the file path to a specific region json file to a string variable
         string regionConfigFilePath = regionConfigFilePaths[i];
         
         // Open the specific json file
         ifstream jsonFile;
         jsonFile.open(regionConfigFilePath);

         // Store the json data into a json object
         json jsonData;
         jsonFile >> jsonData;

         // Initialize variable to store the name of a given medical facility region
         string regionName = jsonData["name"];

         // Create a vector that will store all the medical facility objects that will
         // be generated shortly
         vector<MedicalFacility> savedMedicalFacilities;

         // Create medical facility array value to store all the information for each
         // medical facility within region
         json medicalFacilityArray = jsonData["medical facilities"];
         for (int j = 0; j < medicalFacilityArray.size(); j++) {
            // Initialize various variables for specific medical facility
            string medicalFacilityName = "";
            string medicalFacilityAddress = "";
            string medicalFacilityType = "";

            // Store the specific medical facility object within a json object
            json medicalFacility = medicalFacilityArray[j];

            // Start storing the medical facility information within the previously
            // initialized variables
            medicalFacilityName = medicalFacility["name"];
            medicalFacilityAddress = medicalFacility["address"];
            medicalFacilityType = medicalFacility["type"];

            // Create a vector that will store all the patient objects that will be
            // generated shortly
            vector<Patient> savedPatients;

            // Create patient array value to store all the information for each patient
            // within medical facility
            json patientArray = medicalFacility["patients"];
            for (int k = 0; k < patientArray.size(); k++) {
               // Initialize various variables for specific patient
               int patientAge = 0;
               string patientName = "";
               string patientIllness = "";
               string patientStatus = "";

               // Store the specific patient object within a json object
               json patient = patientArray[k];

               // Start storing the patient information within the previously initialized
               // variables
               patientName = patient["name"];
               patientAge = patient["age"];
               patientIllness = patient["illness"];
               patientStatus = patient["status"];

               // Crate medical professional array value to store all the information for
               // each medical professional associated with patient
               json medicalProfessionalArray = patient["medical professionals"];

               // Create a vector that will store all the medical professional objects that
               // will be generated shortly
               vector<MedicalProfessional> savedMedicalProfessionals;

               // For loop that will go through all medical professional objects with the
               // json file
               for (int l = 0; l < medicalProfessionalArray.size(); l++) {
                  // Initialize various variables for specific medical professional
                  string medicalProfessionalType = "";
                  string medicalProfessionalName = "";
                  string medicalProfessionalSpecialization = "";

                  // Store the specific medical professional object within a json object
                  json medicalProfessional = medicalProfessionalArray[l];

                  // Store the medical professional information within the previously
                  // initialized variables
                  medicalProfessionalType = medicalProfessional["type"];
                  medicalProfessionalName = medicalProfessional["name"];
                  medicalProfessionalSpecialization = medicalProfessional["specialization"];

                  // Depending on the type of medical professional, create a specific medical
                  // professional object that will be stored into the medical professional vector
                  if (medicalProfessionalType == "Doctor") {
                     Doctor medicalProfessionalObject(medicalProfessionalType, medicalProfessionalName, medicalProfessionalSpecialization);
                     savedMedicalProfessionals.push_back(medicalProfessionalObject);
                  }
                  else if (medicalProfessionalType == "Physical Therapist") {
                     PhysicalTherapist medicalProfessionalObject(medicalProfessionalType, medicalProfessionalName, medicalProfessionalSpecialization);
                     savedMedicalProfessionals.push_back(medicalProfessionalObject);
                  }
                  else {
                     Nurse medicalProfessionalObject(medicalProfessionalType, medicalProfessionalName, medicalProfessionalSpecialization);
                     savedMedicalProfessionals.push_back(medicalProfessionalObject);
                  }
               }

               // Create a specific patient object that will be stored into the patient vector
               Patient patientObject(patientName, patientAge, patientIllness, patientStatus, savedMedicalProfessionals);
               savedPatients.push_back(patientObject);
            }

            // Depending on the type of medical facility, create a specific medical
            // facility object that will be stored into the medical medical facility vector
            if (medicalFacilityType == "Hospital") {
               Hospital medicalFacilityObject(medicalFacilityName, medicalFacilityAddress, medicalFacilityType, savedPatients);
               savedMedicalFacilities.push_back(medicalFacilityObject);
            }
            else if (medicalFacilityType == "Urgent Care") {
               UrgentCare medicalFacilityObject(medicalFacilityName, medicalFacilityAddress, medicalFacilityType, savedPatients);
               savedMedicalFacilities.push_back(medicalFacilityObject);
            }
            else {
               RehabilitationCenters medicalFacilityObject(medicalFacilityName, medicalFacilityAddress, medicalFacilityType, savedPatients);
               savedMedicalFacilities.push_back(medicalFacilityObject);
            }
         }

         // Create a specific region object that will be stored into the region vector
         Region regionObject(regionName, regionConfigFilePath, savedMedicalFacilities);
         savedRegions.push_back(regionObject);
      }
   }

   // Print out welcome message to screen now that user is finally within the medical
   // facility management system
   cout << "           Welcome to Patient Sync!         " << endl;
   cout << "============================================" << endl;
   cout << "This interactive user interface lets medical\nprofessionals easily keep track of their\npatients and their ever changing health care\nneeds." << endl;
   cout << " " << endl;

   // Call the switch statement that will resemble the home screen of the user interface
   homeScreenSwitchStatement(credentialFilePath, currentWorkingPathOfScriptString, savedRegions);

   // Print sign out message
   cout << " " << endl;
   cout << "               Sign Out Screen              " << endl;
   cout << "============================================" << endl;
   cout << "Signing out..." << endl;

   // Final return statement
   return 0;
}