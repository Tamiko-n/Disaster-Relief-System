# Disaster Relief Management System 🌟  
A C++ application designed to efficiently manage and allocate disaster relief resources during emergencies. This system tracks supplies, prioritizes distribution, and ensures that critical resources reach the most urgent cases first.  

## Features 🚀  
- **Recipient Queue Management**: Handles a queue of recipients waiting for supplies.  
- **Priority Queue**: Allocates critical resources (e.g., medical supplies) based on priority.  
- **Supply Tracking**: Monitors stock levels of relief supplies in real-time.  
- **Severity-Based Allocation**: Distributes resources based on the severity of emergencies.  

## Data Structures Used 📂  
- **Queue**: To manage recipients in the order they registered.  
- **Priority Queue**: For handling supplies based on urgency (e.g., critical medical needs first).  
- **Linked List**: To store and manage recipient details efficiently.  
- **Array**: For managing stock of various supplies.  

## How It Works 🛠️  
1. **Registration**: Recipients register with their details and severity of the emergency.  
2. **Resource Allocation**:  
   - Severe cases are prioritized using a priority queue.  
   - General cases are served in a first-come, first-serve manner.  
3. **Supply Updates**: The system keeps track of stock levels, notifying when supplies run low.  
4. **Real-Time Monitoring**: Displays the current status of the recipient queue and available resources.  

## Installation and Usage 🖥️  
1. Clone the repository:  
   ```bash  
   git clone https://github.com/Tamiko-n/Disaster-Relief-System.git  
   ```  
2. Navigate to the project directory:  
   ```bash  
   cd disaster-relief-system  
   ```  
3. Compile the code:  
   ```bash  
   g++ -o Disaster-Relief-System main.cpp  
   ```  
4. Run the application:  
   ```bash  
   ./disaster_relief  
   ```  

## Requirements ✅  
- C++ Compiler (e.g., GCC)  
- Basic understanding of the command line  

## Future Enhancements 🌟  
- Integration with real-time databases for data persistence.  
- GUI development for user-friendly interactions.  
- Support for multilingual interfaces.  

## Contributions 🤝  
Feel free to fork the repository, raise issues, or submit pull requests to improve this project.  

## License 📜  
This project is licensed under the [MIT License](LICENSE).  
