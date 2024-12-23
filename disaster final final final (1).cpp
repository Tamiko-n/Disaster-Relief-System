#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>  // for system()
#include <windows.h>  // for Sleep
#include <queue>
#include <fstream>
#include <functional>
#include <cctype>

#define CLEAR_SCREEN_CMD "cls"  // Windows

using namespace std;

struct FeedbackEntry {
    string userName;
    int rating; // Priority (1-10 scale)
    string suggestion;

    FeedbackEntry(const string& name, int rate, const string& sugg)
        : userName(name), rating(rate), suggestion(sugg) {}
};

class FeedbackSystem {
private:
    vector<FeedbackEntry> feedbackQueue; // Priority queue implemented using vector

    // Helper to sort the queue based on rating
    static bool compareFeedback(const FeedbackEntry& a, const FeedbackEntry& b) {
        return a.rating > b.rating; // Higher rating = higher priority
    }

    // Save all feedback to a file
    void saveFeedbackToFile() {
        ofstream file("feedback.txt"); // Open file in truncate mode
        if (file.is_open()) {
            for (const auto& feedback : feedbackQueue) {
                file << feedback.userName << "," << feedback.rating << "," << feedback.suggestion << endl;
            }
            file.close();
        }
        else {
            cout << "Error: Unable to open file for saving feedback.\n";
        }
    }
    void loadFeedbackFromFile() {
        ifstream file("feedback.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(',');
                size_t pos2 = line.rfind(',');

                // Validate the line format
                if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                    string name = line.substr(0, pos1);

                    // Try to parse the rating
                    try {
                        int rating = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                        string suggestion = line.substr(pos2 + 1);
                        feedbackQueue.push_back(FeedbackEntry(name, rating, suggestion));
                    }
                    catch (const invalid_argument&) {
                        cout << " \n";
                    }
                }
                else {
                    cout << "Warning: Skipping malformed line in feedback file.\n";
                }
            }
            file.close();

            // Sort the queue to maintain priority order
            sort(feedbackQueue.begin(), feedbackQueue.end(), compareFeedback);
        }
        else {
            cout << "\n";
        }
    }


public:
    FeedbackSystem() {
        loadFeedbackFromFile(); // Load existing feedback at startup
    }

    ~FeedbackSystem() {
        saveFeedbackToFile(); // Save feedback before program exits
    }

    // Function to add feedback
    void addFeedback(const string& name, int rating, const string& suggestion) {
        if (rating < 1 || rating > 10) {
            cout << "Invalid rating. Please provide a rating between 1 and 10.\n";
            return;
        }

        feedbackQueue.push_back(FeedbackEntry(name, rating, suggestion));

        // Sort the queue to maintain priority
        sort(feedbackQueue.begin(), feedbackQueue.end(), compareFeedback);

        cout << "Thank you, " << name << ", for your feedback!\n";
    }

    // Function to display feedback in priority order
    void displayFeedback() {
        if (feedbackQueue.empty()) {
            cout << "No feedback available.\n";
            return;
        }

        cout << "--- Feedback Priority List ---\n";
        for (const auto& feedback : feedbackQueue) {
            cout << "Name: " << feedback.userName
                << ", Rating: " << feedback.rating
                << ", Suggestion: " << feedback.suggestion << endl;
            system("pause");
        }
    }



    bool collectFeedback() {
        string userName, suggestion;
        int rating;
        char choice= ' ';

        do {
            cout << "\n--- Feedback Form ---\n";

            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, userName);

            cout << "Rate the app on a scale of 1-10: ";
            cin >> rating;

            while (cin.fail() || rating < 1 || rating > 10) {
                cin.clear();
                cout << "Invalid rating. Enter a number between 1 and 10: ";
                cin >> rating;
            }

            cout << "Any suggestions to improve? ";
            cin.ignore();
            getline(cin, suggestion);

            addFeedback(userName, rating, suggestion);


            while (choice != 'Y' && choice != 'B') {
                cout << "Press 'B' to go back: ";
                cin >> choice;
                choice = toupper(choice);
            }

            if (choice == 'B') {
                system(CLEAR_SCREEN_CMD);
                return true;
            }

        } while (choice == 'Y');
        return false; // Stay in feedback section
    }
};
class Request {
public:
    string name, phone, disasterType, severity, city, province, location, comments;
    int priority;

    Request(const string& n = "", const string& p = "", const string& d = "", const string& s = "",
        const string& c = "", const string& pr = "", const string& l = "", const string& com = "", int pri = 0)
        : name(n), phone(p), disasterType(d), severity(s), city(c), province(pr), location(l), comments(com), priority(pri) {}
};

class RescueManagementSystem {
private:
    priority_queue<Request, vector<Request>, function<bool(const Request&, const Request&)>> rescueRequests;
    const string adminEmail = "WeTheGreat@gmail.com";
    const string adminPassword = "excepthareem";


    struct Node {
        string category; // e.g., "Medical Supplies"
        string itemName; // e.g., "Aspirin"
        int quantity;
        Node* next;

        Node(string cat, string name, int qty) : category(cat), itemName(name), quantity(qty), next(nullptr) {}
    };

    Node* head;

public:
    RescueManagementSystem() : head(nullptr) {
        // Insert items into the linked list categorized into three groups
        head = new Node("Medical Supplies", "Aspirin", 100);
        head->next = new Node("Medical Supplies", "Cough Syrup", 75);
        head->next->next = new Node("Medical Supplies", "Ibuprofen", 120);
        head->next->next->next = new Node("Medical Supplies", "Paracetamol", 150);
        head->next->next->next->next = new Node("Medical Supplies", "Painkillers", 90);
        head->next->next->next->next->next = new Node("Medical Supplies", "Vitamin C Tablets", 200);
        head->next->next->next->next->next->next = new Node("Medical Supplies", "Bandages", 200);
        head->next->next->next->next->next->next->next = new Node("Medical Supplies", "First Aid Kits", 50);
        head->next->next->next->next->next->next->next->next = new Node("Medical Supplies", "Gloves", 150);
        head->next->next->next->next->next->next->next->next->next = new Node("Medical Supplies", "Injections", 100);
        head->next->next->next->next->next->next->next->next->next->next = new Node("Medical Supplies", "Masks", 200);
        head->next->next->next->next->next->next->next->next->next->next->next = new Node("Medical Supplies", "Syrups", 150);
        head->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Medical Supplies", "Tablets", 300);

        head->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Ambulances", 10);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Blankets", 75);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Energy Bars", 200);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Flashlights", 50);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Ladders", 15);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Rescue Boats", 5);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Stretchers", 20);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Basic Necessities", "Water Bottles", 100);

        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Rescue Personnel", "Doctor Squads", 6);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Rescue Personnel", "Police Units", 12);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Rescue Personnel", "Rangers", 8);
        head->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = new Node("Rescue Personnel", "Rescue Squads", 10);
    }

    bool userLogin() {
        cout << "\t\t\t\t\t\t\t   --------------------------------\n";
        cout << "\t\t\t\t\t\t\t    U S E R - L O G I N - P A G E  \n";
        cout << "\t\t\t\t\t\t\t   -------------------------------- \n\n\n";
        string email, password;
        cout << "\n\n\n\n\t\t\t\t\t\tEnter your email: ";
        cin >> email;
        cout << "\n\n\t\t\t\t\t\tEnter your password: ";
        cin >> password;

        ifstream inFile("userdata.txt");
        if (!inFile.is_open()) {
            cout << "\n\n\t\t\t\t\t\tError opening user data file!\n";
            return false;
        }

        string storedEmail, storedPassword;
        while (inFile >> storedEmail >> storedPassword) {
            if (storedEmail == email && storedPassword == password) {
                cout << "\n\n\t\t\t\t\t\t\tLOGIN SUCCESSFUL!\n";
                return true;
            }
        }
        cout << "Invalid credentials.\n";
        system("pause");
        return false;
    }

    void userSignup() {
        cout << "\t\t\t\t\t\t\t   --------------------------------\n";
        cout << "\t\t\t\t\t\t\t   U S E R - S I G N U P - P A G E  \n";
        cout << "\t\t\t\t\t\t\t   -------------------------------- \n\n\n";
        string email, password;
        cout << "\n\n\n\n\t\t\t\t\t\tEnter a new email: ";
        cin >> email;
        cout << "\n\n\t\t\t\t\t\tEnter a new password: ";
        cin >> password;

        ofstream outFile("userdata.txt", ios::app);
        if (!outFile.is_open()) {
            cout << "\n\n\t\t\t\t\t\tError saving user data!\n";
            return;
        }

        outFile << email << " " << password << endl;
        cout << "\n\n\t\t\t\t\t\t\tSIGNUP SUCCESSFUL!\n";
    }

    // Admin login
    bool adminLogin() {
        cout << "\t\t\t\t\t\t\t   --------------------------------\n";
        cout << "\t\t\t\t\t\t\t   A D M I N - L O G I N - P A G E  \n";
        cout << "\t\t\t\t\t\t\t   -------------------------------- \n\n\n";
        string email, password;
        cout << "\n\n\n\n\t\t\t\t\t\tEnter admin email: ";
        cin >> email;
        cout << "\n\n\t\t\t\t\t\tEnter admin password: ";
        cin >> password;

        return email == adminEmail && password == adminPassword;
    }

    // Rescue request operations
    void addRescueRequest(const Request& req) {
        rescueRequests.push(req);
        cout << "Rescue request added.\n";
    }

    void saveRequestToFile(const Request& req) {
        ofstream outFile("dataofrequests.txt", ios::app);
        if (!outFile.is_open()) {
            cout << "Error saving request to file.\n";
            return;
        }

        outFile << req.name << "|" << req.phone << "|" << req.disasterType << "|"
            << req.severity << "|" << req.city << "|" << req.province << "|"
            << req.location << "|" << req.comments << "|" << req.priority << "\n";
        cout << "Request saved to file.\n";
    }

    void displayRequests() {
        if (rescueRequests.empty()) {
            cout << "No rescue requests available.\n";
            return;
        }

        auto tempQueue = rescueRequests;
        while (!tempQueue.empty()) {
            Request req = tempQueue.top();
            cout << "Name: " << req.name << ", Disaster: " << req.disasterType
                << ", Severity: " << req.severity << ", City: " << req.city << "\n";
            tempQueue.pop();
        }
    }

    void dispatchSupplies() {
        if (rescueRequests.empty()) {
            cout << "No requests available to dispatch.\n";
            return;
        }

        string userName;
        cout << "Enter the name of the user to dispatch supplies to: ";
        cin.ignore();
        getline(cin, userName);

        priority_queue<Request, vector<Request>, function<bool(const Request&, const Request&)>> tempQueue( rescueRequests );

        bool found = false;
        while (!rescueRequests.empty()) {
            Request req = rescueRequests.top();
            rescueRequests.pop();

            if (req.name == userName) {
                found = true;
                cout << "Dispatching supplies to " << req.name << " at " << req.location << "...\n";

                // Traverse the supply linked list and manage dispatching
                Node* temp = head;
                while (temp != nullptr) {
                    int quantity;
                    cout << "Enter quantity for " << temp->itemName << " (available: " << temp->quantity << "): ";
                    cin >> quantity;

                    if (quantity > temp->quantity) {
                        cout << "Not enough " << temp->itemName << " available. Dispatching " << temp->quantity << ".\n";
                        quantity = temp->quantity;
                    }

                    temp->quantity -= quantity;
                    temp = temp->next;
                }

                cout << "Supplies have been successfully dispatched to " << req.name << ".\n";

                // Here you can add code to log or update files
                break;
            }
            else {
                tempQueue.push(req);
            }
        }

        if (!found) {
            cout << "User not found.\n";
        }

        // Restore the remaining requests to the main queue
        rescueRequests = tempQueue;
    }

    void updateFilesAfterDispatch(const Request& dispatchedReq) {
        // Update the dataofrequests.txt file
        ifstream inFile("dataofrequests.txt");
        ofstream outFile("tempfile.txt");

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error accessing files for update.\n";
            return;
        }

        string line;
        while (getline(inFile, line)) {
            if (line.find(dispatchedReq.name) == string::npos) {
                outFile << line << "\n";
            }
        }

        inFile.close();
        outFile.close();

        // Replace original file with updated file
        remove("dataofrequests.txt");
        rename("tempfile.txt", "dataofrequests.txt");

        cout << "Dispatched request removed from file.\n";
    }

    // Supply management
  // Add a new supply to the linked list or update the quantity if it already exists
    void addSupply(const string& item, int quantity) {
        Node* temp = head;
        bool found = false;

        // Traverse the linked list to check if the item already exists
        while (temp != nullptr) {
            if (temp->itemName == item) {
                temp->quantity += quantity;  // Update quantity
                cout << "Added " << quantity << " units of " << item << ". New quantity: " << temp->quantity << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }

        // If the item doesn't exist, create a new node and add it to the list
        if (!found) {
            Node* newNode = new Node("Unknown Category", item, quantity); // category can be adjusted as needed
            newNode->next = head;
            head = newNode;
            cout << "Added " << quantity << " units of " << item << " as a new supply.\n";
        }
    }


    // Display all supplies in the linked list
    void displaySupplies() {
        cout << "--- Available Supplies ---\n";
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->itemName << ": " << temp->quantity << " units\n";
            temp = temp->next;
        }
    }


    // Rescue request form
    void rescueRequestForm() {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tR E S C U E - R E Q U E S T - F O R M";
        for (int i = 0; i < 3; ++i) {
            Sleep(1000);
            cout << ".";
            cout.flush();
        }
        system(CLEAR_SCREEN_CMD);
            Request req;
        cout << "\n\nWhat's your name?: ";
        cin >> req.name;
        cout << "\n\nPlease provide your contact number:";
        cin >> req.phone;
        cin.ignore();

        cout << "\n\nWhich city are you reporting from?: ";
        getline(cin, req.city);
        cout << "\n\nIn which province are you located?: ";
        getline(cin, req.province);
        cout << "\n\nWhat type of disaster are you reporting (e.g., Fire, Earthquake, Flood, other)?: ";
        getline(cin, req.disasterType);
        cout << "\n\nHow severe is the disaster? (low/high): ";
        getline(cin, req.severity);
        cout << "\n\nPlease specify the exact location of the disaster: ";
        getline(cin, req.location);
        cout << "\n\nIs there anything else we should know? (Add any additional comments): ";
        getline(cin, req.comments);

        req.priority = req.severity == "high" ? 2 : 1;
        cout << "\n\n\nYour rescue request has been created successfully!\n\n";
        system("pause");
        system(CLEAR_SCREEN_CMD);
        cout << "\n\t\t\t\t\t\t\t\t--- Rescue Request Summary ---\n\n";
        cout << "Name: " << req.name << endl << endl;
        cout << "Contact Number: " << req.phone << endl << endl;
        cout << "City: " << req.city << endl << endl;
        cout << "Province: " << req.province << endl << endl;
        cout << "Disaster Type: " << req.disasterType << endl << endl;
        cout << "Severity: " << req.severity << endl << endl;
        cout << "Location: " << req.location << endl << endl;
        cout << "Additional Comments: " << req.comments << endl << endl;
        cout << "Mortality: " << (req.priority == 2 ? "High" : "Low") << endl << endl;

        cout << "Do you want to submit or make changes? (submit/change): ";
        string action;
        cin >> action;
        if (action == "submit") {
            saveRequestToFile(req);
            addRescueRequest(req);

            cout << "Request submitted successfully!\n";
        }
        else if (action == "change") {
            cout << "Making changes...\n";
            rescueRequestForm();
        }
    }

    // Admin menu
    void adminMainMenu() {
        cout << "\t\t\t\t\t\t\t   --------------------------------\n";
        cout << "\t\t\t\t\t\t\t    A D M I N - M A I N - M E N U  \n";
        cout << "\t\t\t\t\t\t\t   -------------------------------- \n\n\n";
        int choice;
        do {
            cout << "\t\t\t\t\t\t\t-------A D D - S U P P L I E S-------\n";
            Sleep(500);
            cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (1)\n\n\n\n";
            Sleep(1000);
            cout << "\t\t\t\t\t\t\t-------V I E W - S U P P L I E S-------\n";
            Sleep(500);
            cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (2)\n\n\n\n";
            Sleep(1000);
            cout << "\t\t\t\t\t\t\t    -------V I E W - R E S C U E - R E Q U E S T S-------\n";
            Sleep(500);
            cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (3)\n\n\n\n";
            Sleep(1000);
            cout << "\t\t\t\t\t\t\t-------D I S P A T C H - S U P P L I E S-------\n";
            Sleep(500);
            cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (4)\n\n\n\n";
            Sleep(1000);
            cout << "\t\t\t\t\t\t\t\t------- L O G O U T -------\n";
            Sleep(500);
            cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (5)\n\n\n\n";
            Sleep(1000);
            cout << "------------------------------------------------------------ S E L E C T---A N---O P T I O N --------------------------------------------------------------:\n";
            cin >> choice;
            system(CLEAR_SCREEN_CMD);
            switch (choice) {
            case 1: {
                string item;
                int quantity;
                cout << "\n\nEnter supply name: ";
                cin >> item;
                cout << "\n\nEnter quantity: ";
                cin >> quantity;
                addSupply(item, quantity);
                system("pause");
                system(CLEAR_SCREEN_CMD);
                break;
            }
            case 2:
                displaySupplies();
                system("pause");
                system(CLEAR_SCREEN_CMD);
                break;
            case 3:
                displayRequests();
                system("pause");
                system(CLEAR_SCREEN_CMD);
                break;
            case 4:
                dispatchSupplies();
                system("pause");
                system(CLEAR_SCREEN_CMD);
                break;
            case 5:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};


void welcomePage() {
    cout << "\033[1;5;32m"; // Bold text
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t=========================================\n\n";
    cout << "\t\t\t\t\t\t*** D I S A S T E R ** M A N A G E M E N T ** S Y S T E M! ***\n\n";
    cout << "\n\t\t\t\t\t\t\t\t=========================================\n\n";
    cout << "\033[0m";    // Reset text style
    Sleep(5000);
    cout << "\033[1;5;31m";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t\t--------------------------- ";
    cout << "\n\t\t\t\t\t\t\t-D I S C O V E R M O R E- ";
    cout << "\n\t\t\t\t\t\t\t--------------------------- ";
    cout << "\033[0m";
    system("pause");
    system(CLEAR_SCREEN_CMD);
}

void showHome() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t H O M E P A G E";
    for (int i = 0; i < 3; ++i) {
        Sleep(1000);
        cout << ".";
        cout.flush();
    }
    system(CLEAR_SCREEN_CMD);
    cout << "\t\t\t\t\t\tD I S A S T E R----R E L I E F----S Y S T E M" << endl << endl;
    cout << "         A disaster relief system is a coordinated response to a disaster that provides immediate assistance and early recovery efforts to those affected:\n\n";
    Sleep(2000);
    cout << "\t\t\t\t\t\t\t\t\t--------- \n";
    cout << "\t\t\t\t\t\t\t\t\tG O A L S \n";
    cout << "\t\t\t\t\t\t\t\t\t--------- \n";

    cout << "The goals of disaster relief are to:\n";
    cout << "1. Save lives\n";
    cout << "2. Reduce health impacts\n";
    cout << "3. Ensure public safety\n";
    cout << "4. Meet basic needs\n\n";
    Sleep(2000);
    cout << "\t\t\t\t\t\t\t\t   ------------------- \n";
    cout << "\t\t\t\t\t\t\t\t   A C T I V I T I E S \n";
    cout << "\t\t\t\t\t\t\t\t   ------------------- \n";
    cout << "Disaster relief activities include:\n";
    cout << "1. Damage and needs assessments\n";
    cout << "2. Providing food, water, clothes, and shelter\n\n";
    Sleep(2000);
    cout << "\t\t\t\t\t\t   ----------------------------------------------------\n";
    cout << "\t\t\t\t\t\t   S E A R C H--A N D--R E S C U E--O P E R A T I O N S\n";
    cout << "\t\t\t\t\t\t   ----------------------------------------------------\n";
    cout << "1. Providing psychosocial support\n";
    cout << "2. Facilitating community development\n";
    cout << "3. Restoring essential services like water and power\n\n";
    Sleep(2000);
    cout << "\t\t\t\t\t\t\t\t ------------------------ \n";
    cout << "\t\t\t\t\t\t\t\t C O- O R D I N A T I O N \n";
    cout << "\t\t\t\t\t\t\t\t ------------------------ \n";
    cout << "\nA coordinated multi-agency response is vital to reduce the impact of a disaster.\n\n";
    Sleep(2000);
    cout << "\n\t\t\t\t\t\t\t\t\t--------- \n";
    cout << "\t\t\t\t\t\t\t\t\tR O L E S \n";
    cout << "\t\t\t\t\t\t\t\t\t--------- \n";
    cout << "Social workers play a crucial role in disaster relief.\n\n";
    Sleep(2000);
    cout << "Some examples of disaster relief systems include:\n";
    Sleep(2000);
    cout << "\n\t\t\t\t\t\t   **A G A K H A N--D E V E L O P M E N T--N E T W O R K\n";
    Sleep(2000);
    cout << "\n\t\t\t\t\t **P R O V I N C I A L--E M E R G E N C Y--O P E R A T I O N--C E N T R E\n";
    Sleep(2000);
    cout << "\n\t\t\t\t\t\t\t\t   **R E S Y L I A\n";
    system("pause");
}

class Queue {
private:
    struct Node {
        string data;
        Node* next;
        Node(string val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Remove an element from the queue
    string dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty. Cannot dequeue.");
        }
        Node* temp = front;
        string data = temp->data;
        front = front->next;
        if (front == nullptr) { // Queue becomes empty
            rear = nullptr;
        }
        delete temp;
        return data;
    }

    

    // Check if the queue is empty
    bool isEmpty() const {
        return front == nullptr;
    }

    // Destructor to clean up memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};


void showPrecautions() {
    Queue precautionsQueue;

    int choice;

    do {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t P R E C A U T I O N S";
        for (int i = 0; i < 3; ++i) {
            Sleep(1000);
            cout << ".";
            cout.flush();
        }
        system(CLEAR_SCREEN_CMD);
        int index = 1;

        // Display queue contents
        Queue tempQueue = precautionsQueue; // Copy the queue to iterate without modifying
        while (!tempQueue.isEmpty()) {
            cout << " " << index++ << ". " << tempQueue.dequeue() << "\n";
        }
        Sleep(500);
        cout << "\n\n\t\t\t\t\t\t\t\t   ------- F I R E -------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (1)\n\n\n\n";
        cout << "\t\t\t\t\t\t\t     ------- E A R T H Q U A K E -------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (2)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t      ------- T O R N A D O E S -------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (3)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t         ------- F L O O D -------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (4)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t\t   ------- B A C K -------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (5)\n\n\n\n";
        cout << "------------------------------------------------------------ S E L E C T---A N---O P T I O N --------------------------------------------------------------:\n";
        cin >> choice;
        system(CLEAR_SCREEN_CMD);

        switch (choice) {
        case 1:
            cout << "\t\t\t\t\t\t\t\t ----------------------------- \n";
            cout << "\t\t\t\t\t\t\t\t F I R E P R E C A U T I O N S \n";
            cout << "\t\t\t\t\t\t\t\t ----------------------------- \n\n\n";
            cout << "\t\t\t\t\t\t\t\t-------DO'S DURING THE FIRE-------\n\n";

            cout << "• Know your building's evacuation plan.\n\n";

            cout << "• Evacuate calmly and quickly whenever a fire alarm sounds.\n\n";

            cout << "• Keep important items such as medications and medical equipment handy for quick access in the event of a building evacuation.\n\n";

            cout << "• Know two ways out of any building.\n\n";

            cout << "• Before opening a door, feel it with the back of your hand. If the door is hot, do not open it.\n\n";

            cout << "• If you encounter smoke during your evacuation, stay low to the floor.\n\n";

            cout << "• Know the outside rally point for your building.\n\n";

            cout << "• In case of a smoke or fire emergency, activate the nearest fire alarm pull station, alert those around you, and from a safe location call the fire department by dialing 16, then call Public Safety at the Charles River Campus by dialing 617-353-2121 and the Control Center at the Medical Campus by dialing 617-414-6666.\n\n";

            cout << "• Make sure that hallways and stairway doors close tightly.\n\n";

            cout << "• Know the locations of fire extinguishers, fire alarm pull stations, and exits.\n\n";

            cout << "• Learn to use a fire extinguisher.\n\n";
            cout << "\033[1;5;32m";
            cout << "TO KNOW WHAT NOT TO DO... ";
            cout << "\033[0m";
            system("pause");
            system(CLEAR_SCREEN_CMD);

            cout << "\t\t\t\t\t\t\t\t-------DONT'S DURING THE FIRE-------\n\n";

            cout << "• Use candles, incense, barbecue grills or other open flames unattended.  (Note that these items are prohibited in University housing).\n\n";

            cout << "• Use halogen lamps near curtains or other combustibles. (Halogen lamps are prohibited in University housing).\n\n";

            cout << "• Hang tapestries from walls or ceilings.\n\n";

            cout << "• Leave cooking appliances unattended.\n\n";

            cout << "• Smoke in building. (Smoking is prohibited in University housing).\n\n";

            cout << "• Tamper with smoke detectors, carbon monoxide alarms, fire alarms or sprinkler systems.\n\n";

            cout << "• Ignore any building alarm.\n\n";

            cout << "• Hang anything from sprinkler heads or pipes.\n\n";

            cout << "• Foreign objects may impede the system's function.\n\n";

            cout << "• Prop fire or smoke doors open.\n\n";

            cout << "• Use elevators during an evacuation.\n\n";
            system("pause");
            system(CLEAR_SCREEN_CMD);
            break;

        case 2:
            cout << "\t\t\t\t\t\t\t\t----------------------------------------- \n";
            cout << "\t\t\t\t\t\t\t\tE A R T H Q U A K E P R E C A U T I O N S \n";
            cout << "\t\t\t\t\t\t\t\t----------------------------------------- \n\n\n";
            cout << "\t\t\t\t\t\t\t\t-------BEFORE AN EARTHQUAKE-------\n\n";

            cout << "• Follow and advocate local safe building codes for earthquake-resistant construction.\n\n";

            cout << "• Follow and advocate upgrading poorly built structures.\n\n";

            cout << "• Make a plan and be ready for an emergency.\n\n";

            cout << "• Identify the medical centers, fire fighting stations and organize rescue mock drills for the society of your area.\n\n";

            cout << "• Know the electric and water shut off locations in your house.\n\n";

            cout << "• Heavy objects, glasses, cutlery should be kept on lower shelves.\n\n";

            cout << "• Flower pots should not be kept on the parapet.\n\n";
            cout << "\033[1;5;31m";
            cout << "TO KNOW WHAT TO DO DURING EARTHQUAKE... ";
            cout << "\033[0m";
            system("pause");
            system(CLEAR_SCREEN_CMD);

            cout << "\t\t\t\t\t\t\t\t-------DURING AN EARTHQUAKE-------\n\n";
            cout << "• Keep calm and reassure others.\n\n";

            cout << "• During the event, the safest place is an open space, away from buildings.\n\n";

            cout << "• If you are indoors, take cover under a desk, table, bed, or doorways and against inside walls and staircase. Stay away from glass doors, glass panes, windows, or outside doors. Do not rush to go out of the building, to avoid the stampede.\n\n";

            cout << "• If you are outside, move away from buildings and utility wires.\n\n";

            cout << "• Once in the open, stay there till the vibrations stop.\n\n";

            cout << "• If you are in a moving vehicle, stop as quickly as possible and stay in the vehicle.\n\n";

            cout << "• Free all pets and domestic animals so that they can run outside.\n\n";

            cout << "• Do not use candles, matches or other open flames. Put out all fires.\n\n";

            cout << "\033[1;5;31m";
            cout << "TO KNOW WHAT TO DO AFTER EARTHQUAKE... ";
            cout << "\033[0m";
            system("pause");
            system(CLEAR_SCREEN_CMD);
            cout << "\t\t\t\t\t\t\t\t-------AFTER AN EARTHQUAKE-------\n\n";
            cout << "• Keep stock of drinking water, foodstuff and first-aid equipment inaccessible place.\n\n";

            cout << "• Do not spread and believe rumors.\n\n";

            cout << "• Turn on your transistor or television to get the latest information/bulletins and aftershock warnings.\n\n";

            cout << "• Provide help to others and develop confidence.\n\n";

            cout << "• Attend the injured persons and give them aid, whatever is possible, and also inform the hospital.\n\n";

            cout << "• Be prepared for aftershocks as these may strike.\n\n";

            cout << "• Close the valve of the kitchen gas stove, if it is on. If it is closed, do not open it. Do not use open flames.\n\n";

            cout << "• Do not operate electrical switches or appliances, if gas leaks are suspected.\n\n";

            cout << "• Check water pipes, electric panels and fittings. If damaged, shut off the main valves. Do not touch PVE wires of electricity.\n\n";

            cout << "• If needed, open doors and cupboards carefully as objects may fall.\n\n";
            system("pause");
            system(CLEAR_SCREEN_CMD);
            break;

        case 3:
            cout << "\t\t\t\t\t\t\t\t----------------------------------- \n";
            cout << "\t\t\t\t\t\t\t\tT O R N A D O P R E C A U T I O N S \n";
            cout << "\t\t\t\t\t\t\t\t----------------------------------- \n\n\n";
            cout << "\t\t\t\t\t\t\t\t-------DO'S DURING TORNADO-------\n\n";

            cout << "• If you are already inside a structure, go to a per-designated shelter area such as a safe room, basement, storm cellar or the lowest building level. Avoid areas near windows.\n\n";

            cout << "• Listen to a Weather Radio, regular radio or television for tornado updates. (Battery-powered devices are best, in case the electricity goes out.)\n\n";

            cout << "• Crouch as low as possible to the floor, facing down. Cover the back of your head with your hands.\n\n";

            cout << "• If you're in a mobile home, get out, even if it's tied down. You're probably safer outside, even if that means seeking shelter out in the open.\n\n";

            cout << "• If you're outside with no shelter, lie flat in a ditch or depression and cover your head with your hands. Be aware of the potential for flooding.\n\n";
            cout << "\033[1;5;31m";
            cout << "TO KNOW WHAT NOT TO DO... ";
            cout << "\033[0m";
            system("pause");
            system(CLEAR_SCREEN_CMD);

            cout << "\t\t\t\t\t\t\t\t-------DONT'S DURING TORNADO-------\n\n";

            cout << "• Don't use your car as shelter.\n\n";

            cout << "• Don't open the windows in your home. You may be exposed to flying glass if you're opening windows when the twister hits.\n\n";

            cout << "• Don't use elevators. You could get trapped if the power is lost.\n\n";

            cout << "• Don't go to the southwest corner of your shelter — most tornadoes approach from the southwest.\n\n";

            cout << "• Don't park under an overpass. It may seem like good shelter, but it can actually be more dangerous than open ground. A wind-t unnel effect can cause higher wind speeds, driving debris toward you and even propelling you out from under the overpass.\n\n";

            cout << "• Don't light candles, even after the storm has passed. Ruptured gas lines can create a fire hazard so it's better to use flashlights.\n\n";
            system("pause");
            system(CLEAR_SCREEN_CMD);
            break;

        case 4:
            cout << "\t\t\t\t\t\t\t\t------------------------------- \n";
            cout << "\t\t\t\t\t\t\t\tF L O O D P R E C A U T I O N S \n";
            cout << "\t\t\t\t\t\t\t\t-------------------------------\n\n\n";
            cout << "\t\t\t\t\t\t\t\t-------DO'S DURING FLOOD-------\n\n";

            cout << "• Raise furniture and electrical appliances.\n\n";
            cout << "• Put sandbags in the toilet bowl and cover drain holes.\n\n";

            cout << "• Keep emergency lights, phones, and inverters charged.\n\n";

            cout << "• Keep a first aid kit with extra medication.\n\n";

            cout << "• Keep food covered and eat freshly cooked or dry food.\n\n";

            cout << "• Drink boiled water or use chlorine tablets to purify water.\n\n";

            cout << "• Stay informed about flood safety tips.\n\n";

            cout << "• Scan and keep documents in digital form.\n\n";

            cout << "• Return home with caution and follow re-entry orders.\n\n";
            cout << "\033[1;5;31m";
            cout << "TO KNOW WHAT NOT TO DO... ";
            cout << "\033[0m";
            system("pause");
            system(CLEAR_SCREEN_CMD);
            cout << "\t\t\t\t\t\t\t\t-------DONT'S DURING FLOOD-------\n\n";
            cout << "• Entering floodwaters.\n\n";

            cout << "• Walking through moving water.\n\n";

            cout << "• Getting near electric poles or fallen power lines.\n\n";

            cout << "• Being in disaster areas.\n\n";

            cout << "• Driving through floodwaters.\n\n";

            cout << "• Swimming through floodwaters.\n\n";

            cout << "• Re-entering a flooded area until it's safe.\n\n";

            cout << "• Entering a flooded property unless it's structurally safe.\n\n";

            cout << "• Turning on electricity or gas supplies until they've been checked.\n\n";

            cout << "• Smoking or using open flames.\n\n";
            system("pause");
            system(CLEAR_SCREEN_CMD);
            break;
        case 5:
            cout << "Going back...\n";
            break;
        default:
            cout << "Invalid choice, try again!\n";
        }
    } while (choice != 5);
}

// Function to convert string to lowercase
void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Helpline data stored in an array of structures
struct Helpline {
    string city;
    string services[6];
};

// Array containing helpline data
Helpline helplines[] = {
    {"karachi", {"For Ambulance: Dial 1020", "For Police: Dial 15", "For Fire Brigade: Dial 16",
                 "For Rescue Services: Dial 1122", "For Edhi: Dial 115", "For Chhipa: Dial 1020"}},
    {"lahore", {"For Ambulance: Dial 1020", "For Police: Dial 15", "For Fire Brigade: Dial 1122",
                "For Rescue Services: Dial 1122", "For Edhi: Dial 115", "For Chhipa: Dial 1020"}},
    {"islamabad", {"For Ambulance: Dial 1020", "For Police: Dial 15", "For Fire Brigade: Dial 16",
                   "For Rescue Services: Dial 1122", "For Edhi: Dial 115", "For Chhipa: Dial 1020"}},
    {"rawalpindi", {"For Ambulance: Dial 1020", "For Police: Dial 15", "For Fire Brigade: Dial 16",
                    "For Rescue Services: Dial 1122", "For Edhi: Dial 115", "For Chhipa: Dial 1020"}},
                    // Add other cities similarly...
};

// Total number of helplines
const int NUM_CITIES = sizeof(helplines) / sizeof(helplines[0]);

void showHelplines() {
    string city;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tH E L P L I N E-S E R V I C E S";
    for (int i = 0; i < 3; ++i) {
        Sleep(1000);
        cout << ".";
        cout.flush();
    }
    system(CLEAR_SCREEN_CMD);
    cout << "\n\n------------------------------------------------------------ S T A Y - S A F E, S T A Y - I N F O R M E D --------------------------------------------------\n";
    Sleep(1000);
    cout << "\n\t\t\t\t\t\t                ------- HELP IS JUST A CALL AWAY! -------\n\n";
    Sleep(1000);
    cout << "\nWHERE DO YOU NEED HELP? ENTER CITY NAME:";
    cin >> city;
    system(CLEAR_SCREEN_CMD);
    // Convert city name to lowercase
    toLowerCase(city);

    // Search for the city in the array
    bool cityFound = false;
    for (int i = 0; i < NUM_CITIES; ++i) {
        if (helplines[i].city == city) {
            cityFound = true;
            cout << "\n\t\t\t\t\t\t          H E L P L I N E S - F O R - " << helplines[i].city << ":\n\n";
            for (const string& line : helplines[i].services) {
                cout << line << endl;
                cout << "\n";
            }
            break;
        }
    }

    if (!cityFound) {
        cout << "City not found. Please try again.\n";
    }

    system("pause");
}


void loginSignupMenu(RescueManagementSystem& rms, FeedbackSystem& fds);
void mainMenu(RescueManagementSystem& rms);

// Refactored login/signup menu
void loginSignupMenu(RescueManagementSystem& rms) {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tL O G I N / S I G N U P - M E N U";
    for (int i = 0; i < 3; ++i) {
        Sleep(1000);
        cout << ".";
        cout.flush();
    }
    system(CLEAR_SCREEN_CMD);
    cout << "\t\t\t\t\t\t\t     -------L O G I N / S I G N U P-------\n\n";
    bool isLoggedIn = false; // Track if user/admin is logged in
    int choice;
    do {
        system(CLEAR_SCREEN_CMD);
        cout << "\t\t\t\t\t\t\t\t-------U S E R - L O G I N -------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (1)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t\t-------U S E R - S I G N U P-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (2)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t\t-------A D M I N - L O G I N-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (3)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t\t   -------B A C K-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (4)\n\n\n\n";
        Sleep(1000);
        cout << "-------------------------------------------------------------S E L E C T---A N---O P T I O N---------------------------------------------------------------:\n";
        cin >> choice;
        system(CLEAR_SCREEN_CMD);
        switch (choice) {
        case 1:
            if (rms.userLogin()) {
                cout << "User login successful!\n";
                isLoggedIn = true;
                cout << "Congratulations! You can now fill up the rescue request form.\n";
                rms.rescueRequestForm(); // User-specific functionality
            }
            else {
                cout << "Invalid credentials. Please try again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            break;
        case 2:
            rms.userSignup();
            Sleep(1000);
            system(CLEAR_SCREEN_CMD);
            if (rms.userLogin()) {
                cout << "User login successful after signup!\n";
                isLoggedIn = true;
                rms.rescueRequestForm();
            }
            else {
                cout << "Signup complete. Please try logging in.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            break;
        case 3:
            if (rms.adminLogin()) {
                cout << "\n\n\t\t\t\t\t\t\tADMIN LOGIN SUCCESSFUL!\n";
                isLoggedIn = true;
                system("pause");
                system(CLEAR_SCREEN_CMD);
                rms.adminMainMenu();
            }
            else {
                cout << "Invalid admin credentials. Please try again.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            break;
        case 4:
            cout << "Going back...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (!isLoggedIn && choice != 4); // Continue until logged in or user exits
}


void mainMenu(RescueManagementSystem& rms, FeedbackSystem& fds) {

    int choice;
    do {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t M A I N M E N U";
        for (int i = 0; i < 3; ++i) {
            Sleep(1000);
            cout << ".";
            cout.flush();
        }
        system(CLEAR_SCREEN_CMD);
        cout << "\t\t\t\t\t\t\t\t   -------H O M E-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (1)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t\t-------P R E C A U T I O N S-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (2)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t      -------H E L P L I N E--S E R V I C E S-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (3)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t-------R E S C U E--R E Q U E S T--F O R M-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (4)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t     -------L O G I N / S I G N U P-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (5)\n\n\n\n";
        Sleep(1000);
        cout << "\t\t\t\t\t\t\t     -------F E E D B A C K-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (6)\n\n\n\n";
        Sleep(1000);

        cout << "\t\t\t\t\t\t\t\t   -------E X I T-------\n";
        Sleep(500);
        cout << "\n\t\t\t\t\t\t\t\t\tP R E S S (7)\n\n\n\n";
        Sleep(1000);
        cout << "-------------------------------------------------------------S E L E C T---A N---O P T I O N---------------------------------------------------------------:\n";
        cin >> choice;
        system(CLEAR_SCREEN_CMD);
        switch (choice) {
        case 1:
            showHome();
            break;
        case 2:
            showPrecautions();
            break;
        case 3:
            showHelplines();
            break;
        case 4:
            rms.rescueRequestForm();
            break;
        case 5:
            loginSignupMenu(rms);
            break;

        case 6: {
            int feedbackChoice;
            cout << "1. Submit Feedback\n";
            cout << "2. View Feedback\n";
            cout << "Enter your choice: ";
            cin >> feedbackChoice;

            if (feedbackChoice == 1) {
                bool goBackToMenu = fds.collectFeedback(); // Call FeedbackSystem's method
                if (goBackToMenu) {
                    break; // Exit to main menu
                }
            }
            else if (feedbackChoice == 2) {
                fds.displayFeedback();
            }
            else {
                cout << "Invalid feedback choice.\n";
            }
            break;
        }

        case 7:
            cout << "\033[1;5;32m"; // Bold text
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t=========================================\n\n";
            cout << "\t\t\t\t\t\t*** THANK YOU FOR USING DISASTER RELIEF SYSTEM. STAY SAFE! STAY INFORMED! ***\n\n";
            cout << "\n\t\t\t\t\t\t\t\t=========================================\n\n";
            cout << "\033[0m\n\n\n\n\n\n\n\n";    // Reset text style 
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);
}


int main() {

    FeedbackSystem fds;
    RescueManagementSystem rms; // Create instance
    welcomePage();
    Sleep(1000);
    showHome();
    system(CLEAR_SCREEN_CMD);
    mainMenu(rms, fds);
    return 0;
}