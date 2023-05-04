/* 
========== File Description ==========
This file is responsible for containing all of the switch statements that act as
the backbone of the medical facility user interface. These switch statements give
the users the various options that they need to use and traverse this nested system.
*/

// Necessary library includes
#include <vector>
#include <iostream>

// Necessary namespaces
using namespace std;
using json = nlohmann::json;

/* ========== Switch Statements ========== */
// Switch statement to act as the specific medical professional part of the user interface
template <typename MedicalProfessionalType>
void specificMedicalProfessionalSwitchStatement(MedicalProfessionalType& chosenMedicalProfessional, string chosenMedicalFacilityName, string chosenPatientName, string regionFilePath) {
    // Print statement used for formatting
    cout << " " << endl;

    // Initialize string to store medical professional's name
    string chosenMedicalProfessionalName = chosenMedicalProfessional.getName();

    // The infinite loop allows the user to continuously interact with the medical facility
    // management UI
    while (1) {
        // Initialize boolean value to be used to later decided if the program should go
        // back to the previous screen or not
        bool goBack = false;
        
        // Initialize variable that will represent user's choice of the options that are related
        // to the medical professional 
        int editMedicalProfessionalInformationOrViewListOfPatients = 0;

        // Print statements to help print out header of specific patient screen
        cout << "        Medical Professional Screen         " << endl;
        cout << "============================================" << endl;
        cout << "Name: " << chosenMedicalProfessional.getName() << endl;
        cout << "Type: " << chosenMedicalProfessional.getType() << endl;
        cout << "Specialization: " << chosenMedicalProfessional.getSpecialization() << endl;

        // Display the various opening choices to the user and allow them to pick one of the
        // options
        cout << "Please choose one of the following options:" << endl;
        cout << "1: Edit medical professional's specialization" << endl;
        cout << "2: List all of the patients associated with\n   the medical professional" << endl;
        cout << "3: Back" << endl;
        cout << "Selection: ";
        cin >> editMedicalProfessionalInformationOrViewListOfPatients;

        // Switch statement that will let the user either edit the information of the medical
        // professional or will list the patients that are associated with medical professional
        switch(editMedicalProfessionalInformationOrViewListOfPatients) {
            // User choose to edit the medical professional's specialization
            case 1:
            {
                // Initialize string variable that will store the medical professional's new
                // specialization
                string newMedicalProfessionalSpecialization;

                // Print statement to display header for editing medical professional's
                // specialization
                cout << " " << endl;
                cout << " Edit Medical Professional's Specialization " << endl;
                cout << "============================================" << endl;

                // Prompt user to input what the medical professional's new specialization
                cout << "Please input the medical professional's new\nspecialization:" << endl;
                cout << "Medical Professional's Specialization: ";
                getline(cin >> ws, newMedicalProfessionalSpecialization);

                // Print statement saying that medical professional's specialization has been
                // updated
                cout << "Medical Professional's specialization has\nbeen updated." << endl;

                // Call function to update the medical professional's specialization
                chosenMedicalProfessional.setSpecialization(newMedicalProfessionalSpecialization);

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // Find the specific index of the medical facility
                int indexOfMedicalFacility = indexOfMedicalFacilityInJsonArray(completeRegionJsonData, chosenMedicalFacilityName);

                // Find the specific index of the patient
                int indexOfPatient = indexOfPatientInJsonArray(completeRegionJsonData, chosenPatientName, indexOfMedicalFacility);

                // Find the specific index of the medical professional
                int indexOfMedicalProfessional = indexOfMedicalProfessionalInJsonArray(completeRegionJsonData, chosenMedicalProfessionalName, indexOfMedicalFacility, indexOfPatient);

                // Change the specialization of the medical professional
                completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][indexOfPatient]["medical professionals"][indexOfMedicalProfessional]["specialization"] = chosenMedicalProfessional.getSpecialization();

                // Set new json information into specific region file
                setJsonDataIntoRegionFile(regionFilePath, completeRegionJsonData);

                // Break statement to go back to infinite loop 
                cout << " " << endl;
                break;
            }

            // User choose to list out all of the patients that are associated with this medical
            // professional
            case 2:
            {
                // Initialize string variable that will store the medical professional's new
                // name and a string vector to store the names of all the patients associated
                // with this medical professional
                vector<string> patientsNames;
                string medicalProfessionalName = chosenMedicalProfessional.getName();

                // Print statement to display header for listing medical professional's
                // patients
                cout << " " << endl;
                cout << "   List of Medical Professional's Patients  " << endl;
                cout << "============================================" << endl;

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // For loop to traverse through all of the elements within the medical
                // facility array
                for (int i = 0; i < completeRegionJsonData["medical facilities"].size(); i++) {
                    // Create an object to store one of the elements from the medical
                    // facility array
                    json medicalFacility = completeRegionJsonData["medical facilities"][i];

                    // For loop to traverse through all of the elements within patient
                    // array
                    for (int j = 0; j < medicalFacility["patients"].size(); j++) {
                        // Create an object to store one of the elements from the patient
                        // array
                        json patient = medicalFacility["patients"][j];

                        // For loop to traverse through all of the elements within the
                        // medical professional array
                        for (int k = 0; k < patient["medical professionals"].size(); k++) {
                            // Create an object to store one of the elements of the 
                            // medical professional array
                            json medicalProfessional = patient["medical professionals"][k];
                            
                            // The name of the medical professional is within the previously
                            // generated json object, push the name of the patient into the
                            // patient name vector
                            if (medicalProfessional["name"] == medicalProfessionalName) {
                                patientsNames.push_back(patient["name"]);
                            }
                        }
                    }
                }

                // If the name vector is not 0, traverse through it and print out all the
                // saved patient names
                if (patientsNames.size() != 0) {
                    for (int i = 1; i <= patientsNames.size(); i++) {
                        cout << to_string(i) << ": " << patientsNames[i - 1] << endl;
                    }
                }
                // If it is 0 than print the following statement
                else {
                    cout << "There are no patients assigned to this\nmedical professional." << endl;
                }

                // Break statement to go back to infinite loop 
                cout << " " << endl;
                break;
            }

            // User choose to go back a page
            case 3:
            {
                // Set the boolean value that decides whether to go back to previous screen
                // or not to true
                goBack = true;
                break;
            }

            // User inputted an invalid option so they will be asked to input again 
            default:
            {
                // Print statement to inform user that they inputted an invalid option and that
                // they have to try again with a valid one
                cout << "The input that you entered was not a valid\noption! Try again and choose any of the\nthree valid options." << endl;
                cout << " " << endl;
                break;
            }
        }

        // Check boolean variable to see if program should be go back to the previous screen
        if (goBack == true) {
            // If it is true break from while loop
            break;
        }
    }
}

// Switch statement to act as the specific patient part of the user interface
void specificPatientSwitchStatement(Patient& chosenPatient, string regionFilePath, string chosenMedicalFacilityName) {
    // Print statement used for formatting
    cout << " " << endl;

    // Initialize string to store patient's name
    string chosenPatientName = chosenPatient.getName();

    // The infinite loop allows the user to continuously interact with the medical facility
    // management UI
    while (1) {
        // Initialize boolean value to be used to later decided if the program should go
        // back to the previous screen or not
        bool goBack = false;
        
        // Initialize variable that will represent users choice to either get/edit patient
        // information or list, create, and or select a specific medical professional 
        int patientInformationOrMedicalProfessionalOptions = 0;

        // Print statements to help print out header of specific patient screen
        cout << "               Patient Screen               " << endl;
        cout << "============================================" << endl;
        cout << "Name: " << chosenPatient.getName() << endl;
        cout << "Age: " << to_string(chosenPatient.getAge()) << endl;
        cout << "Illness: " << chosenPatient.getIllness() << endl;
        cout << "Status: " << chosenPatient.getStatus() << endl;

        // Display the various opening choices to the user and allow them to pick one of the
        // options
        cout << "Please choose one of the following options:" << endl;
        cout << "1: Edit patient's illness records" << endl;
        cout << "2: Discharge patient" << endl;
        cout << "3: List all of the medical professionals\n   assigned to this patient" << endl;
        cout << "4: Assign a new medical professional to\n   patient" << endl;
        cout << "5: Select a specific medical professional" << endl;
        cout << "6: Back" << endl;
        cout << "Selection: ";
        cin >> patientInformationOrMedicalProfessionalOptions;

        // Switch statement that will either allow the user to manipulate the patient's
        // information or will list, create, or select a specific medical professional
        switch(patientInformationOrMedicalProfessionalOptions) {
            // User choose to edit the patient's illness records
            case 1:
            {
                // Initialize string variable that will store the patient's new
                // illness record
                string newPatientIllness;

                // Print statement to display header for editing patient's illness
                // records
                cout << " " << endl;
                cout << "       Edit Patient's Illness Records       " << endl;
                cout << "============================================" << endl;

                // Prompt user to input what the patient's new recorded illness is
                cout << "Please input the patient's new illness\nrecord:" << endl;
                cout << "Patient's Illness: ";
                getline(cin >> ws, newPatientIllness);

                // Call function to update the patient's illness information
                chosenPatient.setIllness(newPatientIllness);

                // Print statement saying that patient's illness records have been updated
                cout << "Patient's illness records have been updated." << endl;

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // Find the specific index of the medical facility
                int indexOfMedicalFacility = indexOfMedicalFacilityInJsonArray(completeRegionJsonData, chosenMedicalFacilityName);

                // Find the specific index of the medical facility 
                int indexOfPatient = indexOfPatientInJsonArray(completeRegionJsonData, chosenPatientName, indexOfMedicalFacility);

                // Change the illness of the specific patient within the json file
                completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][indexOfPatient]["illness"] = newPatientIllness;

                // Set new json information into specific region file
                setJsonDataIntoRegionFile(regionFilePath, completeRegionJsonData);

                // Break statement to go back to infinite loop 
                cout << " " << endl;
                break;
            }

            // User choose to discharge the patient from the medical facility
            case 2:
            {
                // Print statement to display header for discharging patient
                cout << " " << endl;
                cout << "              Discharge Patient             " << endl;
                cout << "============================================" << endl;

                // Print statement letting the user now that the patient has been
                // discharged from their given hospital and than run the discharge
                // patient function
                cout << "This patient has now been discharged." << endl;
                chosenPatient.dischargePatient();

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // Find the specific index of the medical facility
                int indexOfMedicalFacility = indexOfMedicalFacilityInJsonArray(completeRegionJsonData, chosenMedicalFacilityName);

                // Find the specific index of the medical facility 
                int indexOfPatient = indexOfPatientInJsonArray(completeRegionJsonData, chosenPatientName, indexOfMedicalFacility);

                // Change the illness of the specific patient within the json file
                completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][indexOfPatient]["status"] = chosenPatient.getStatus();

                // Set new json information into specific region file
                setJsonDataIntoRegionFile(regionFilePath, completeRegionJsonData);

                // Break statement to go back to infinite loop 
                cout << " " << endl;
                break;
            }
            
            // User choose to list all of the medical professionals that are assigned
            // to the given patient
            case 3:
            {
                // Print statement to display header for list of medical professionals
                cout << " " << endl;
                cout << "        List of Medical Professionals       " << endl;
                cout << "============================================" << endl;

                // Call function and input medical professional vector to list out all of
                // the medical professionals that are within the vector
                listObjectsWithinGivenVector(chosenPatient.getMedicalProfessionalVector());

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to assign a new medical professional to this patient
            case 4:
            {
                // Initialize variables that will be later used to create a new medical
                // professional object
                string medicalProfessionalType;
                string medicalProfessionalName; 
                string medicalProfessionalSpecialization;
                int selectMedicalProfessionalType;

                // Initialize a vector of valid medical professional types that a user is
                // allowed to later choose from
                vector<string> validMedicalProfessionalTypes = {"Doctor", "Physical Therapist", "Nurse"};

                // Print statement to display header for the creation of a new medical professional
                cout << " " << endl;
                cout << "          New Medical Professional          " << endl;
                cout << "============================================" << endl;

                // Print statements/user inputs to get information for new medical professional
                cout << "Please input the name, type, and\nspecialization of the new medical\nprofessional:" << endl;
                cout << "Medical Professional Name: ";
                getline(cin >> ws, medicalProfessionalName);
                cout << "Medical Professional Specialization: ";
                getline(cin >> ws, medicalProfessionalSpecialization);
                
                // Display the valid medical professional types that a user is allowed to chose from
                cout << "Valid Medical Professional Types: " << endl;
                listElementsOfStringVector(validMedicalProfessionalTypes);

                // Print statement and user input to store user selected medical professional type
                cout << "Selection: ";
                cin >> selectMedicalProfessionalType;

                // Print statements to let the user know that medical professional creation was successful
                cout << "Creation of new medical professional was\nsuccessful!" << endl;
                
                // If user's selection is either less than or equal to the size of the valid medical
                // professional type vector than store the necessary value within the medical professional
                // type variable
                if ((selectMedicalProfessionalType > 0) && (selectMedicalProfessionalType <= validMedicalProfessionalTypes.size())) {
                    medicalProfessionalType = validMedicalProfessionalTypes[selectMedicalProfessionalType - 1];
                }
                // If user's selected value is not in expected range, print error message and break
                // back to while loop
                else {
                    cout << "This selection is invalid. Next time please\nsubmit a valid selection." << endl;
                    cout << " " << endl;
                    break;
                }

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // Initialize a json object with the given medical professional information
                json medicalProfessionalInitializationData;
                medicalProfessionalInitializationData["type"] = medicalProfessionalType;
                medicalProfessionalInitializationData["name"] = medicalProfessionalName;
                medicalProfessionalInitializationData["specialization"] = medicalProfessionalSpecialization;

                // Find the specific index of the medical facility
                int indexOfMedicalFacility = indexOfMedicalFacilityInJsonArray(completeRegionJsonData, chosenMedicalFacilityName);

                // Find the specific index of the medical facility 
                int indexOfPatient = indexOfPatientInJsonArray(completeRegionJsonData, chosenPatientName, indexOfMedicalFacility);

                // Add medical professional json data to the medical professional array within the original
                // json object
                completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"][indexOfPatient]["medical professionals"].push_back(medicalProfessionalInitializationData);

                // Set new json information into specific region file
                setJsonDataIntoRegionFile(regionFilePath, completeRegionJsonData);
                
                // Call function that generates a new medical professional object and puts it
                // into the medical professional vector for this specific patient
                createNewMedicalProfessionalObject(chosenPatient, medicalProfessionalName, medicalProfessionalType, medicalProfessionalSpecialization);

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to select a specific medial professional
            case 5:
            {
                // Initialize variable that will be needed to select a specific medical
                // professional
                int userSelectedMedicalProfessional = 0;

                // Print statement to display header for selecting a medical professional
                cout << " " << endl;
                cout << "        Select Medical Professional         " << endl;
                cout << "============================================" << endl;
                
                // Call function and input medical professional vector to list out all of
                // the medical professionals that are within the vector
                listObjectsWithinGivenVector(chosenPatient.getMedicalProfessionalVector());

                // Print statement to have user select a specific medical professional from
                // the printed list
                cout << "Please select a specific medical\nprofessional: " << endl;
                cout << "Selection: ";
                cin >> userSelectedMedicalProfessional;

                // If user's selection is either less than or equal to the size of medical
                // professional vector, then allow the user to enter that medical professional's
                // specific home page
                if ((userSelectedMedicalProfessional > 0) && (userSelectedMedicalProfessional <= chosenPatient.getMedicalProfessionalVector().size())) {
                    // Switch statement that will bring them to the page of the medical professional they choose
                    specificMedicalProfessionalSwitchStatement(chosenPatient.getMedicalProfessionalVector()[userSelectedMedicalProfessional - 1], chosenMedicalFacilityName, chosenPatientName, regionFilePath);
                }
                /// If user's selected value is not in expected range, print error message and break
                // back to switch while loop
                else {
                    cout << "This selection is invalid. Next time please\nsubmit a valid selection." << endl;
                    cout << " " << endl;
                    break;
                }

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to go back a page
            case 6:
            {
                // Set the boolean value that decides whether to go back to previous screen
                // or not to true
                goBack = true;
                break;
            }

            // User inputted an invalid option so they will be asked to input again 
            default:
            {
                // Print statement to inform user that they inputted an invalid option and that
                // they have to try again with a valid one
                cout << "The input that you entered was not a valid\noption! Try again and choose any of the\nthree valid options." << endl;
                cout << " " << endl;
                break;
            }
        }

        // Check boolean variable to see if program should be go back to the previous screen
        if (goBack == true) {
            // If it is true break from while loop
            break;
        }
    }    
}

// Switch statement to act as the specific medical facility part of the user interface
template <typename MedicalFacilityType>
void specificMedicalFacilitySwitchStatement(MedicalFacilityType& chosenMedicalFacility, string regionFilePath) {
    // Print statement used for formatting
    cout << " " << endl;

    // Initialize string to store medical facility's name
    string chosenMedicalFacilityName = chosenMedicalFacility.getName();

    // The infinite loop allows the user to continuously interact with the medical facility
    // management UI
    while (1) {
        // Initialize boolean value to be used to later decided if the program should go
        // back to the previous screen or not
        bool goBack = false;
        
        // Initialize variable that will represent users choice to either list, create, 
        // or select a specific patient profile
        int listCreateOrSelectPatientProfile = 0;

        // Print statements to help print out header of specific medical facility screen
        cout << "           Medical Facility Screen          " << endl;
        cout << "============================================" << endl;
        cout << "Name: " << chosenMedicalFacility.getName() << endl;
        cout << "Address: " << chosenMedicalFacility.getAddress() << endl;
        cout << "Type: " << chosenMedicalFacility.getType() << endl;

        // Display the various opening choices to the user and allow them to pick one of the
        // options
        cout << "Please choose one of the following options:" << endl;
        cout << "1: List all of the patient profiles within\n   this medical facility" << endl;
        cout << "2: Create a new patient profile" << endl;
        cout << "3: Select a specific patient profile" << endl;
        cout << "4: Back" << endl;
        cout << "Selection: ";
        cin >> listCreateOrSelectPatientProfile;

        // Switch statement that will either create a new patient profile, list all the
        // saved ones, or will put the user in a specific patient's interactive page
        switch(listCreateOrSelectPatientProfile) {
            // User choose to list all of the patient profiles with the given medical
            // facility
            case 1:
            {
                // Print statement to display header for list of patient profiles
                cout << " " << endl;
                cout << "              List of Patients              " << endl;
                cout << "============================================" << endl;

                // Call function and input patient vector to list out all of
                // the patient profile that are within the vector
                listObjectsWithinGivenVector(chosenMedicalFacility.getPatientVector());

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to create a new patient profile within this medical facility
            case 2:
            {
                // Initialize variables that will be later used to create a new patient
                // object
                int patientAge;
                string patientName; 
                string patientIllness;
                string patientStatus = "Admitted";

                // Print statement to display header for the creation of a new patient profile
                cout << " " << endl;
                cout << "                 New Patient                " << endl;
                cout << "============================================" << endl;

                // Print statements/user inputs to get name, age, and illness information for new
                // patient
                cout << "Please input the name, age, and illness for\nnew patient:" << endl;
                cout << "Patient Name: ";
                getline(cin >> ws, patientName);
                cout << "Patient Age: ";
                cin >> patientAge;
                cout << "Patient Illness: ";
                getline(cin >> ws, patientIllness);

                // Print statements to let the user know that patient creation was successful
                cout << "Creation of new patient was successful!" << endl;

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // Initialize a json object with the given patient information
                json patientInitializationData;
                patientInitializationData["name"] = patientName;
                patientInitializationData["age"] = patientAge;
                patientInitializationData["illness"] = patientIllness;
                patientInitializationData["status"] = patientStatus;
                patientInitializationData["medical professionals"] = json::array();

                // Find the specific index of the medical facility within the 
                int indexOfMedicalFacility = indexOfMedicalFacilityInJsonArray(completeRegionJsonData, chosenMedicalFacilityName);

                // Add the patient json data to the patient array within the original
                // json object
                completeRegionJsonData["medical facilities"][indexOfMedicalFacility]["patients"].push_back(patientInitializationData);

                // Set new json information into specific region file
                setJsonDataIntoRegionFile(regionFilePath, completeRegionJsonData);

                // Create a vector of medical professional objects to be used in
                // the creation of the new patient object
                vector<MedicalProfessional> MedicalProfessionals;
                
                // Create and push this new region to the saved regions list 
                Patient newPatient(patientName, patientAge, patientIllness, patientStatus, MedicalProfessionals);
                chosenMedicalFacility.addNewPatientProfileToVector(newPatient);

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to select a specific patient profile
            case 3:
            {
                // Initialize variable that will be needed to select a specific patient
                // profile
                int userSelectedPatientProfile = 0;

                // Print statement to display header for selecting a patient profile
                cout << " " << endl;
                cout << "               Select Patient               " << endl;
                cout << "============================================" << endl;
                
                // Call function and input patient vector to list out all of
                // the patient profile that are within the vector
                listObjectsWithinGivenVector(chosenMedicalFacility.getPatientVector());

                // Print statement to have user select a specific patient from the printed list
                cout << "Please select a specific patient profile: " << endl;
                cout << "Selection: ";
                cin >> userSelectedPatientProfile;

                // If user's selection is either less than or equal to the size of patient vector,
                // then allow the user to enter that patient's specific home page
                if ((userSelectedPatientProfile > 0) && (userSelectedPatientProfile <= chosenMedicalFacility.getPatientVector().size())) {
                // Switch statement that will bring them to the page of the patient they choose
                specificPatientSwitchStatement(chosenMedicalFacility.getPatientVector()[userSelectedPatientProfile - 1], regionFilePath, chosenMedicalFacilityName);
                }
                /// If user's selected value is not in expected range, print error message and break
                // back to switch while loop
                else {
                    cout << "This selection is invalid. Next time please\nsubmit valid selection." << endl;
                    cout << " " << endl;
                    break;
                }

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to go back a page
            case 4:
            {
                // Set the boolean value that decides whether to go back to previous screen
                // or not to true
                goBack = true;
                break;
            }

            // User inputted an invalid option so they will be asked to input again 
            default:
            {
                // Print statement to inform user that they inputted an invalid option and that
                // they have to try again with a valid one
                cout << "The input that you entered was not a valid\noption! Try again and choose any of the\nthree valid options." << endl;
                cout << " " << endl;
                break;
            }
        }

        // Check boolean variable to see if program should be go back to the previous screen
        if (goBack == true) {
            // If it is true break from while loop
            break;
        }
    }
}

// Switch statement to act as the specific region part of the user interface
void specificRegionSwitchStatement(Region& choosenRegion) {
    // Print statement used for formatting
    cout << " " << endl;

    // Initialize string variable to hold specific region's file path
    string regionFilePath = choosenRegion.getFilePath();

    // The infinite loop allows the user to continuously interact with the medical facility
    // management UI
    while (1) {
        // Initialize boolean value to be used to later decided if the program should go
        // back to the previous screen or not
        bool goBack = false;
        
        // Initialize variable that will represent users choice to either list, create, and
        // or select a specific medical facility
        int listCreateOrSelectMedicalFacility = 0;

        // Print statements to help print out header of specific region screen
        cout << "                Region Screen               " << endl;
        cout << "============================================" << endl;
        cout << "Region: " << choosenRegion.getName() << endl;

        // Display the various opening choices to the user and allow them to pick one of the
        // options
        cout << "Please choose one of the following options:" << endl;
        cout << "1: List all of the medical facilities within\n   the region" << endl;
        cout << "2: Create a new medical facility" << endl;
        cout << "3: Select a specific medical facility" << endl;
        cout << "4: Back" << endl;
        cout << "Selection: ";
        cin >> listCreateOrSelectMedicalFacility;

        // Switch statement that will either create a new medical facility, list all the
        // saved ones, or will put the user in a specific medical facility's interactive page
        switch (listCreateOrSelectMedicalFacility) {
            // User choose to list all of the medical facilities within the given region
            case 1:
            {
                // Print statement to display header for list of medical facilities
                cout << " " << endl;
                cout << "          List of Medical Facilities        " << endl;
                cout << "============================================" << endl;

                // Call function and input medical facility vector to list out all of
                // the medical facilities that are within the vector
                listObjectsWithinGivenVector(choosenRegion.getMedicalFacilityVector());

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }
            
            // User chose to create a new medical facility within this region
            case 2:
            {
                // Initialize variables that will be later used to create a new medical
                // facility object
                string medicalFacilityType; 
                string medicalFacilityName;
                string medicalFacilityAddress;
                int selectedMedicalFacilityType;

                // Initialize a vector of valid medical facility types tha a user is
                // allowed to later choose from
                vector<string> validMedicalFacilityTypes = {"Hospital", "Urgent Care", "Rehabilitation Center"};

                // Print statement to display header for the creation of a new medical facility
                cout << " " << endl;
                cout << "             New Medical Facility           " << endl;
                cout << "============================================" << endl;

                // Print statements/user inputs to get name and address information for medical facility
                cout << "Please input the name, address, and facility\ntype for new medical facility:" << endl;
                cout << "Medical Facility Name: ";
                getline(cin >> ws, medicalFacilityName);
                cout << "Medical Facility Address: ";
                getline(cin >> ws, medicalFacilityAddress);
                
                // Display the valid medical facility types that a user is allowed to chose from
                cout << "Valid Medical Facility Types: " << endl;
                listElementsOfStringVector(validMedicalFacilityTypes);

                // Print statement and user input to store user selected medical facility type
                cout << "Selection: ";
                cin >> selectedMedicalFacilityType;
                
                // If user's selection is either less than or equal to the size of the valid medical
                // facility type vector than store the necessary value within the medical facility
                // type variable
                if ((selectedMedicalFacilityType > 0) && (selectedMedicalFacilityType <= validMedicalFacilityTypes.size())) {
                medicalFacilityType = validMedicalFacilityTypes[selectedMedicalFacilityType - 1];
                }
                // If user's selected value is not in expected range, print error message and break
                // back to switch while loop
                else {
                    cout << "This selection is invalid. Next time please\nsubmit valid selection." << endl;
                    cout << " " << endl;
                    break;
                }

                // Print statements to let the user know that medical facility creation was successful
                cout << "Creation of new medical facility was\nsuccessful!" << endl;

                // Store the initial contents of the entire json file into a json object
                json completeRegionJsonData = returnJsonDataFromRegionFile(regionFilePath);

                // Initialize a json object with the given medical facility information
                json medicalFacilityInitializationData;
                medicalFacilityInitializationData["name"] = medicalFacilityName;
                medicalFacilityInitializationData["address"] = medicalFacilityAddress;
                medicalFacilityInitializationData["type"] = medicalFacilityType;
                medicalFacilityInitializationData["patients"] = json::array();

                // Add the medical facility json data to the medical facility array within
                // the original json object
                completeRegionJsonData["medical facilities"].push_back(medicalFacilityInitializationData);

                // Set new json information into specific region file
                setJsonDataIntoRegionFile(regionFilePath, completeRegionJsonData);

                // Call function that generates a new medical facility object and puts it
                // into the medical facility vector for this specific region
                createNewMedicalFacilityObject(choosenRegion, medicalFacilityName, medicalFacilityAddress, medicalFacilityType);

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to select a specific medical facility
            case 3:
            {
                // Initialize variable that will be needed to select a specific medical
                // facility
                int userSelectedMedicalFacility = 0;

                // Print statement to display header for selecting a medical facility
                cout << " " << endl;
                cout << "           Select Medical Facility          " << endl;
                cout << "============================================" << endl;
                
                // Call function and input medical facility vector to list out all of
                // the medical facilities that are within the vector
                listObjectsWithinGivenVector(choosenRegion.getMedicalFacilityVector());

                // Print statement to have user select a specific medical facility from the printed
                // list
                cout << "Please select a specific medical facility: " << endl;
                cout << "Selection: ";
                cin >> userSelectedMedicalFacility;

                // If user's selection is either less than or equal to the size of medical facility
                // vector, then allow the user to enter that medical facility's specific home page
                if ((userSelectedMedicalFacility > 0) && (userSelectedMedicalFacility <= choosenRegion.getMedicalFacilityVector().size())) {
                    // Switch statement that will bring them to the page of the medical facility they
                    // choose
                    specificMedicalFacilitySwitchStatement(choosenRegion.getMedicalFacilityVector()[userSelectedMedicalFacility - 1], regionFilePath);
                }
                /// If user's selected value is not in expected range, print error message and break
                // back to switch while loop
                else {
                    cout << "This selection is invalid. Next time please\nsubmit valid selection." << endl;
                    cout << " " << endl;
                    break;
                }

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to go back a page
            case 4:
            {
                // Set the boolean value that decides whether to go back to previous screen
                // or not to true
                goBack = true;
                break;
            }

            // User inputted an invalid option so they will be asked to input again 
            default:
            {
                // Print statement to inform user that they inputted an invalid option and that
                // they have to try again with a valid one
                cout << "The input that you entered was not a valid\noption! Try again and choose any of the\nthree valid options." << endl;
                cout << " " << endl;
                break;
            }
        }

        // Check boolean variable to see if program should be go back to the previous screen
        if (goBack == true) {
            // If it is true break from while loop
            break;
        }
    }
}

// Allows the user to choose between creating a new medical region, listing
// the various saved medical regions, or selecting a specific one
void selectListOrCreateRegionSwitchStatement(vector<Region>& savedRegions, string currentWorkingPathOfScriptString) {
    // Print statement used for formatting
    cout << " " << endl;

    // The infinite loop allows the user to continuously interact with the medical facility
    // management UI
    while (1) {
        // Initialize boolean value to be used to later decided if the program should go
        // back to the home screen or not
        bool goBack = false;
        
        // Initialize variable that will represent users choice to either list, create, or
        // select a specific medical facility region
        int listCreateOrSelectRegion = 0;

        // Print statements to print out header from this region page
        cout << "                Region Screen               " << endl;
        cout << "============================================" << endl;

        // Display the various opening choices to the user and allow them to pick one of the
        // options
        cout << "Please choose one of the following options:" << endl;
        cout << "1: List all of the saved medical facility\n   regions" << endl;
        cout << "2: Create a new medical facility region" << endl;
        cout << "3: Select a specific medical facility region" << endl;
        cout << "4: Back" << endl;
        cout << "Selection: ";
        cin >> listCreateOrSelectRegion;

        // Switch statement that will run either create a new medical region, list all the
        // saved ones, or will put the user in a specific region's interactive page
        switch(listCreateOrSelectRegion) {
            // User choose to list all of the saved medical facility regions
            case 1:
            {
                // Print statement to display header for list of regions
                cout << " " << endl;
                cout << "               List of Regions              " << endl;
                cout << "============================================" << endl;

                // Call function and input saved region vector to list out all of
                // the saved regions that are within the vector
                listObjectsWithinGivenVector(savedRegions);

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }
            
            // User choose to create a new medical facility region
            case 2:
            {
                // Initialize variables to store region naming information
                string regionName;

                // Print statement to display header for creation of new region
                cout << " " << endl;
                cout << "                 New Region                 " << endl;
                cout << "============================================" << endl;

                // Print statements/user input to get necessary region information
                cout << "Please input the name of the new region that\nyou want to create:" << endl;
                cout << "Region Name: ";
                getline(cin >> ws, regionName);

                // If statement that checks to see if the given string is empty
                if (regionName.empty()) {
                    cout << "Given region name is invalid." << endl;
                    cout << " " << endl;
                    break;
                }
                
                // Call the function that converts the name that the user entered into
                // a valid format to be later used as the file name for the new region
                string regionFileName = convertNameToFileNameFormat(regionName);

                // Create a new region json file with the information given
                string regionFilePath = currentWorkingPathOfScriptString + "\\\\src\\RegionConfigs\\" + regionFileName + ".json";
                ofstream newRegionFile(regionFilePath);

                // Initialize a json object with the given region information
                json regionInitializationData;
                regionInitializationData["name"] = regionName;
                regionInitializationData["medical facilities"] = json::array();

                // Store this new json information into the newly created json file
                newRegionFile << regionInitializationData;

                // Create a vector of medical facility objects to be used in
                // the creation of the new region object
                vector<MedicalFacility> MedicalFacility;
                
                // Create and push this new region to the saved regions list 
                Region newRegion(regionName, regionFilePath, MedicalFacility);
                savedRegions.push_back(newRegion);

                // Print statements to let the user know that region creation was successful
                cout << "Creation of new region was successful!" << endl;

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to select a specific region 
            case 3:
            {
                // Initialize variable that will be needed to select a specific region
                int userSelectedRegion = 0;

                // Print statement to display header for selecting a region
                cout << " " << endl;
                cout << "                Select Region               " << endl;
                cout << "============================================" << endl;
                
                // Call function and input saved region vector to list out all of
                // the saved regions that are within the vector
                listObjectsWithinGivenVector(savedRegions);

                // Print statement to have user select a specific region from the printed
                // list
                cout << "Please select a specific region: " << endl;
                cout << "Selection: ";
                cin >> userSelectedRegion;

                // If user's selection is either less than or equal to size of region vector, then
                // allow the user to enter that regions specific home page
                if ((userSelectedRegion > 0) && (userSelectedRegion <= savedRegions.size())) {
                    // Switch statement that will bring the user to the region page of the region they
                    // choose
                    specificRegionSwitchStatement(savedRegions[userSelectedRegion - 1]);
                }
                // If the selection is outside the previously established range, tell the user their
                // input was invalid and than bring them back to the region page
                else {
                    cout << "This selection is invalid. Next time please\nsubmit valid selection." << endl; 
                }

                // Break statement to go back to infinite loop
                cout << " " << endl;
                break;
            }

            // User choose to go back a page
            case 4:
            {
                // Set the boolean value that decides whether to go back to previous screen
                // or not to true
                goBack = true;
                break;
            }

            // User inputted an invalid option so they will be asked to input again 
            default:
            {
                // Print statement to inform user that they inputted an invalid option and that
                // they have to try again with a valid one
                cout << "The input that you entered was not a valid\noption! Try again and choose any of the\nthree valid options." << endl;
                cout << " " << endl;
                break;
            }
        }

        // Check boolean variable to see if program should be go back to home screen
        if (goBack == true) {
            // If it is true break from while loop
            break;
        }
    }
}

// This function holds the switch statement that acts as the main homepage of this
// program
void homeScreenSwitchStatement(string credentialFilePath, string currentWorkingPathOfScriptString, vector<Region>& savedRegions) {
    // The infinite loop allows the user to continuously interact with the medical facility
    // management UI
    while (1) {
        // Initialize boolean value that will be used to later decided whether or not program
        // should be stopped
        bool shouldProgramBeStopped = false;

        // Initialize variable that will represents users choice to either create a new account
        // (creates new credentials along with other information) or manipulate region information
        int credentialsOrRegion = 0;
        
        // Print statement to print home screen banner
        cout << "                 Home Screen                " << endl;
        cout << "============================================" << endl;

        // Display the various opening choices to the user and allow them to pick one of the
        // options
        cout << "Please choose one of the following options:" << endl;
        cout << "1: Create a new user profile" << endl;
        cout << "2: List/Create/Select a specific region" << endl;
        cout << "3: Sign Out" << endl;
        cout << "Selection: ";
        cin >> credentialsOrRegion;

        // Switch statement that will run either create a new user profile or will put the user
        // in the general regions page
        switch(credentialsOrRegion) {
            // User choose to create a new user profile
            case 1:
            {
                // Initialization of new credential information variables
                string newUsername = "";
                string newPassword = "";

                // Prompt user to input new credentials
                cout << " " << endl;
                cout << "               Create New User              " << endl;
                cout << "============================================" << endl;
                cout << "Please enter credentials for the new user:" << endl;
                cout << "Username: ";
                getline(cin >> ws, newUsername);
                cout << "Password: ";
                getline(cin >> ws, newPassword);
                

                // Call function that will manually input new user's credentials into the file that
                // stores all the credential information for the UI
                createNewUserProfile(credentialFilePath, newUsername, newPassword);

                // Print statements for formatting and to let the user now the credential creation
                // was successful
                cout << "Creation of new valid user was successful!" << endl;
                cout << " " << endl;

                // Call the break statement to reenter infinite loop
                break;
            }

            // User choose to either create or select a specific medical facility region
            case 2:
            {
                // Call function that will run the next switch statement
                selectListOrCreateRegionSwitchStatement(savedRegions, currentWorkingPathOfScriptString);
                cout << " " << endl;
                break;
            }
    
            // User choose to sign out of program
            case 3:
            {
                // Set the boolean value that decides whether to exit the program or not to true
                shouldProgramBeStopped = true;
                break;
            }
            
            // User inputted an invalid option so they will be asked to input again 
            default:
            {
                // Print statement to inform user that they inputted an invalid option and that
                // they have to try again with a valid one
                cout << "The input that you entered was not a valid\noption! Try again and choose any of the\nthree valid options." << endl;
                cout << " " << endl;
                break;
            }
        }

        // Check boolean variable to see if program should be stopped
        if (shouldProgramBeStopped == true) {
            // If it is true break from while loop
            break;
        }
    }
}