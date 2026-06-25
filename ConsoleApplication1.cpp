// ========================================================================
// Preprocessor: Prevent Windows.h from defining min/max macros
// which would cause conflicts with std::min / std::max.
// ========================================================================
#define NOMINMAX                         // Tells windows.h not to define the min/max macros

// ========================================================================
// Include Dear ImGui core library for immediate mode GUI.
// ========================================================================
#include "imgui/imgui.h"                // Main ImGui header (UI widgets, docking, etc.)

// ========================================================================
// Include ImGui backend for Win32 window management.
// ========================================================================
#include "imgui/imgui_impl_win32.h"     // Platform backend: ImGui ↔ Win32 API

// ========================================================================
// Include ImGui backend for DirectX 11 rendering.
// ========================================================================
#include "imgui/imgui_impl_dx11.h"      // Renderer backend: ImGui ↔ Direct3D 11

// ========================================================================
// Include Direct3D 11 core header.
// ========================================================================
#include <d3d11.h>                      // Direct3D 11 API (device, swap chain, etc.)

// ========================================================================
// Include generic text mappings for TCHAR compatibility.
// ========================================================================
#include <tchar.h>                      // Generic text mapping (TCHAR, _T, etc.)

// ========================================================================
// Link against Direct3D 11 library.
// ========================================================================
#pragma comment(lib, "d3d11.lib")       // Automatically link d3d11.lib (no need to set in project settings)

// ========================================================================
// Link against D3D compiler library (used for shader compilation).
// ========================================================================
#pragma comment(lib, "d3dcompiler.lib") // Automatically link d3dcompiler.lib (shader compiler)

// ========================================================================
// Standard library includes:
// <iostream> for console I/O (legacy console menus).
// ========================================================================
#include <iostream>                     // std::cout, std::cin, std::cerr

// ========================================================================
// <string> for std::string usage.
// ========================================================================
#include <string>                       // std::string

// ========================================================================
// <vector> for dynamic arrays.
// ========================================================================
#include <vector>                       // std::vector

// ========================================================================
// <map> for ordered associative containers.
// ========================================================================
#include <map>                          // std::map (ordered key‑value store)

// ========================================================================
// <memory> for smart pointers (std::shared_ptr, std::make_shared).
// ========================================================================
#include <memory>                       // std::shared_ptr, std::make_shared, std::unique_ptr

// ========================================================================
// <fstream> for file input/output.
// ========================================================================
#include <fstream>                      // std::ifstream, std::ofstream (file I/O)

// ========================================================================
// <sstream> for string stream operations.
// ========================================================================
#include <sstream>                      // std::stringstream, std::ostringstream, std::istringstream

// ========================================================================
// <algorithm> for algorithms like std::find_if, std::sort, std::transform.
// ========================================================================
#include <algorithm>                    // std::find, std::find_if, std::sort, std::transform

// ========================================================================
// <iomanip> for formatted I/O manipulators like std::setprecision.
// ========================================================================
#include <iomanip>                      // std::setprecision, std::fixed, std::setw, std::setfill

// ========================================================================
// <limits> for numeric_limits (used to clear input buffers).
// ========================================================================
#include <limits>                       // std::numeric_limits

// ========================================================================
// <stdexcept> for standard exception classes.
// ========================================================================
#include <stdexcept>                    // std::runtime_error, std::invalid_argument, etc.

// ========================================================================
// <chrono> for time handling (current date generation).
// ========================================================================
#include <chrono>                       // std::chrono::system_clock, std::chrono::time_point

// ========================================================================
// <cctype> for character classification (::tolower).
// ========================================================================
#include <cctype>                       // ::tolower, ::toupper, etc.

// ========================================================================
// <unordered_map> for hash-based associative containers (fast lookup).
// ========================================================================
#include <unordered_map>                // std::unordered_map (hash map)

// ========================================================================
// <unordered_set> for hash-based set (used for ID tracking).
// ========================================================================
#include <unordered_set>                // std::unordered_set (hash set)

// ========================================================================
// <random> for random number generation (salt generation).
// ========================================================================
#include <random>                       // std::random_device, std::mt19937, std::uniform_int_distribution

// ========================================================================
// <ctime> for C-style time functions (though chrono is also used).
// ========================================================================
#include <ctime>                        // C time functions (not heavily used, but available)

// ========================================================================
// Use the standard namespace to avoid prefixing with std:: everywhere.
// ========================================================================
using namespace std;                    // Import the entire std namespace into the global namespace

// -------------------- Forward Declarations --------------------
// Forward-declare classes that are used before full definition (Property, Client, etc.)
// to resolve circular dependencies and allow use in function signatures.
class Property;                          // Forward declaration of Property class
class Client;                            // Forward declaration of Client class
class Agent;                             // Forward declaration of Agent class
class Transaction;                       // Forward declaration of Transaction class
class Contract;                          // Forward declaration of Contract class

// -------------------- Enums and Constants --------------------
// Enum class for strong typing representing different property types.
enum class PropertyType { APARTMENT, VILLA, OFFICE, LAND }; // Scoped enum for property categories

// Enum class for property availability status.
enum class PropertyStatus { AVAILABLE, SOLD, RENTED };      // Scoped enum for listing status

// Enum class for client roles in transactions.
enum class ClientType { BUYER, SELLER, RENTER };            // Scoped enum for client intention

// Enum class for transaction categories (sale or rental).
enum class TransactionType { SALE, RENTAL };                // Scoped enum for transaction nature

// Enum class for user authentication roles.
enum class UserRole { ADMIN, AGENT, CLIENT };               // Scoped enum for system permissions

// -------------------- Utility Functions --------------------
// Converts PropertyType enum to human-readable string.
string propertyTypeToString(PropertyType type) {           // Returns a corresponding string for the given PropertyType
    // Switch over enum values.
    switch (type) {                                        // Branch based on the enum constant
    case PropertyType::APARTMENT: return "Apartment";      // Apartment → "Apartment"
    case PropertyType::VILLA: return "Villa";              // Villa → "Villa"
    case PropertyType::OFFICE: return "Office";            // Office → "Office"
    case PropertyType::LAND: return "Land";                // Land → "Land"
        // Default fallback for unknown values (shouldn't happen).
    default: return "Unknown";                             // Safety net for invalid values
    }
}

// Converts PropertyStatus enum to readable string.
string statusToString(PropertyStatus status) {             // Returns a string for the given status
    switch (status) {
    case PropertyStatus::AVAILABLE: return "Available";    // Available → "Available"
    case PropertyStatus::SOLD: return "Sold";              // Sold → "Sold"
    case PropertyStatus::RENTED: return "Rented";          // Rented → "Rented"
    default: return "Unknown";                             // Fallback
    }
}

// Converts ClientType enum to readable string.
string clientTypeToString(ClientType type) {               // String conversion for ClientType
    switch (type) {
    case ClientType::BUYER: return "Buyer";               // Buyer → "Buyer"
    case ClientType::SELLER: return "Seller";             // Seller → "Seller"
    case ClientType::RENTER: return "Renter";             // Renter → "Renter"
    default: return "Unknown";                            // Fallback
    }
}

// Converts UserRole enum to readable string.
string roleToString(UserRole role) {                      // String conversion for UserRole
    switch (role) {
    case UserRole::ADMIN: return "Admin";                 // Admin
    case UserRole::AGENT: return "Agent";                 // Agent
    case UserRole::CLIENT: return "Client";               // Client
    default: return "Unknown";                            // Fallback
    }
}

// Converts a string to lowercase, useful for case-insensitive comparisons.
string toLower(const string& s) {                          // Returns a lower-case copy of the input string
    // Make a copy of the string.
    string result = s;                                     // Work on a copy to keep input unchanged
    // Transform each character to lower using the global tolower function.
    transform(result.begin(), result.end(), result.begin(), ::tolower); // Apply ::tolower to each character
    return result;                                         // Return the lower-cased string
}

// Safe string to integer conversion. Returns true if successful, false otherwise.
bool safeStoi(const string& s, int& out) {                 // Converts string s to int out, returns success
    // Reject empty strings.
    if (s.empty()) return false;                           // Can't convert an empty string
    try {
        // Attempt conversion, stoi will check for trailing characters via pos.
        size_t pos;                                        // Index of first unconverted character
        out = stoi(s, &pos);                               // Convert; pos is updated by stoi
        // Only successful if the entire string was consumed.
        return pos == s.size();                            // Success if no leftover characters
    }
    catch (...) {
        // Any exception (invalid_argument, out_of_range) means conversion failed.
        return false;                                      // Catch all exceptions → failure
    }
}

// Safe string to double conversion using same pattern as safeStoi.
bool safeStod(const string& s, double& out) {               // Converts string s to double out, returns success
    if (s.empty()) return false;                            // Reject empty strings
    try {
        size_t pos;
        out = stod(s, &pos);
        return pos == s.size();                             // Only succeed if entire string is consumed
    }
    catch (...) {
        return false;                                       // Exception → failure
    }
}

// -------------------- ID Generator --------------------
// Static class to manage globally unique IDs across all entities.
class IDGenerator {                                          // All members are static, no instantiation needed
private:
    // Static unordered set to track all used IDs (across all entity types).
    static unordered_set<int> usedIDs;                       // Stores every ID ever issued
    // Static counters for next available ID per type, starting from 0.
    static int nextPropertyID;                               // Counter for property IDs
    static int nextPersonID;                                 // Counter for person IDs (Client & Agent)
    static int nextTransactionID;                            // Counter for transaction IDs
    static int nextContractID;                               // Counter for contract IDs

public:
    // Generate next property ID by incrementing the counter while skipping already used IDs.
    static int getNextPropertyID() {                         // Returns a new, unique property ID
        // Pre-increment and loop until an unused ID is found (or skip used ones).
        while (usedIDs.count(++nextPropertyID));             // Increment and check if already used; if so, continue
        // Insert the newly used ID and return it.
        usedIDs.insert(nextPropertyID);                      // Mark the ID as used
        return nextPropertyID;                               // Return the fresh ID
    }

    // Similar for person IDs (shared by Client and Agent).
    static int getNextPersonID() {                           // Generates a fresh ID for Client or Agent
        while (usedIDs.count(++nextPersonID));               // Skip already used IDs
        usedIDs.insert(nextPersonID);                        // Reserve the ID
        return nextPersonID;                                 // Return it
    }

    // Generate next transaction ID.
    static int getNextTransactionID() {                      // New unique transaction ID
        while (usedIDs.count(++nextTransactionID));          // Skip collisions
        usedIDs.insert(nextTransactionID);                   // Mark as used
        return nextTransactionID;                            // Return the ID
    }

    // Generate next contract ID.
    static int getNextContractID() {                         // New unique contract ID
        while (usedIDs.count(++nextContractID));             // Increment while ID exists in used set
        usedIDs.insert(nextContractID);                      // Reserve it
        return nextContractID;                               // Return the ID
    }

    // Explicitly mark an ID as used (e.g., when loading from file to prevent reuse).
    static void markUsedID(int id) { usedIDs.insert(id); }   // Add an ID to the used set directly

    // Set the starting point for a counter and mark that starting ID as used.
    static void setPropertyIDStart(int s) { nextPropertyID = s; usedIDs.insert(s); }      // Reset property counter and reserve s
    static void setPersonIDStart(int s) { nextPersonID = s; usedIDs.insert(s); }          // Reset person counter
    static void setTransactionIDStart(int s) { nextTransactionID = s; usedIDs.insert(s); } // Reset transaction counter
    static void setContractIDStart(int s) { nextContractID = s; usedIDs.insert(s); }     // Reset contract counter
};

// Static member definitions (out-of-class initialization required in C++).
unordered_set<int> IDGenerator::usedIDs;                      // Define the static usedIDs set (initially empty)
int IDGenerator::nextPropertyID = 0;                          // Start property IDs at 0 (first call gives 1)
int IDGenerator::nextPersonID = 0;                            // Start person IDs at 0
int IDGenerator::nextTransactionID = 0;                       // Start transaction IDs at 0
int IDGenerator::nextContractID = 0;                          // Start contract IDs at 0

// -------------------- User Class with Salted djb2 Hash --------------------
// Represents a system user with salted password hashing.
class User {
private:
    string username;              // Unique login name.
    string salt;                  // Random salt for password hashing.
    string passwordHash;          // Hashed password (hex representation).
    UserRole role;                // User's authorization role.

public:
    // Default constructor (needed for map/storage).
    User() = default;                                         // Default constructor (keeps default member values)

    // Parameterized constructor: generates salt, hashes password.
    User(const string& uname, const string& pwd, UserRole r)  // Create a user with a given name, password, and role
        : username(uname), role(r) {                          // Initialize username and role from arguments
        salt = generateSalt(16);                              // Create a 16-character random salt
        passwordHash = hashPassword(pwd, salt);               // Hash the password combined with the salt
    }

    // Generate a cryptographically non-secure random string of given length.
    static string generateSalt(size_t length = 16) {          // Returns a random alphanumeric string
        // Character set for salt (alphanumeric).
        const string chars =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Allowed characters
        random_device rd;                                    // Non-deterministic random seed provides a seed from hardware randomness.
        mt19937 gen(rd());                                   // Mersenne Twister engine seeded with rd initializes a Mersenne Twister random generator.
        uniform_int_distribution<> dis(0, static_cast<int>(chars.size()) - 1); // Uniform distribution over [0, chars.size()-1] ensures each character index is equally likely
        string salt;                                         // The salt string to build
        // Build salt string character by character.
        for (size_t i = 0; i < length; ++i)                  // Repeat length times
            salt += chars[dis(gen)];                         // Append a random character from chars
        return salt;                                         // Return the generated salt
    }

    // djb2 hash function: simple but effective for string hashing.
    static unsigned long djb2(const string& str) {           // Compute the djb2 hash of a string
        unsigned long hash = 5381;                           // Initial hash value (the "magic" constant)
        for (char c : str) {                                //  Iterates through every character in the string.
            // hash = hash * 33 + c  using bit shift optimization.
            hash = ((hash << 5) + hash) + c;                // Updates the hash by multiplying the current hash by 33 and adding the character’s ASCII value.
        }
        return hash;                                         // Return the computed hash
    }

    // Combine salt and password, compute djb2 hash, and return as hex string.
    static string hashPassword(const string& pwd, const string& salt) { // Hash the salted password
        unsigned long h = djb2(salt + pwd);                  // Concatenate salt+password and hash
        stringstream ss;                                     // Use stringstream for formatting
        // Output hash as 16-digit zero-padded hexadecimal.
        ss << hex << setw(16) << setfill('0') << h;          // Write hash as 16-char hex, padded with zeros
        return ss.str();                                     // Return the hex string
    }

    // Verify a candidate password against the stored hash.
    bool checkPassword(const string& pwd) const {            // Check if given password matches the stored hash
        return passwordHash == hashPassword(pwd, salt);      // Compare freshly computed hash with stored hash
    }

    // Change password while keeping the same salt.
    void setPassword(const string& newPwd) {                 // Update the user's password
        passwordHash = hashPassword(newPwd, salt);           // Rehash with the existing salt
    }

    // Getters.
    const string& getUsername() const { return username; }   // Return a const reference to username
    const string& getSalt() const { return salt; }           // Return a const reference to salt
    const string& getPasswordHash() const { return passwordHash; } // Return a const reference to the password hash
    UserRole getRole() const { return role; }                // Return the user's role

    // Setters (needed for deserialization from file).
    void setUsername(const string& uname) { username = uname; }  // Set username
    void setSalt(const string& s) { salt = s; }                  // Set salt (used when loading from file)
    void setPasswordHash(const string& h) { passwordHash = h; }  // Set password hash (used when loading from file)
    void setRole(UserRole r) { role = r; }                       // Set user role
};

// -------------------- Base Person Class --------------------
// Abstract base for Client and Agent, storing common attributes.
class Person {
protected:
    int id;                    // Unique ID.
    string name;               // Person's name.
    string contactInfo;        // Phone or email.

public:
    // Constructor initializes all fields.
    Person(int id, const string& name, const string& contact) // Initialize base fields
        : id(id), name(name), contactInfo(contact) {          // Member initializer list
    }

    // Virtual destructor to allow polymorphic deletion.
    virtual ~Person() = default;                               // Virtual destructor (does nothing special)

    // Default getters.
    int getID() const { return id; }                           // Return the person's ID
    string getName() const { return name; }                    // Return the person's name
    string getContactInfo() const { return contactInfo; }      // Return contact info

    // Setters.
    void setName(const string& n) { name = n; }                // Set the name
    void setContactInfo(const string& c) { contactInfo = c; }  // Set contact info

    // Virtual display for console output (can be overridden).
    virtual void display() const {                             // Print basic information to console
        cout << "ID: " << id << ", Name: " << name << ", Contact: " << contactInfo; // Output ID, name, contact
    }
};

// -------------------- Client Class --------------------
// Inherits Person, adds client-specific data like type, preferences, history.
class Client : public Person {
private:
    ClientType type;                 // BUYER, SELLER, RENTER.
    vector<int> transactionIDs;      // History of transaction IDs.

    // Preferences for property search matching.
    double budgetMin;
    double budgetMax;
    string preferredCity;
    PropertyType preferredType;
    double minArea;
    double maxArea;
    int minRooms;
    int maxRooms;
    bool hasPreferences;    // Flag indicating if preferences were set. A boolean flag to indicate whether the client has defined preferences.

public:
    // Constructor: sets default preference values to 0/empty, hasPreferences = false.
    Client(int id, const string& name, const string& contact, ClientType t)
        : Person(id, name, contact), type(t),                  // Initialize base and type
        budgetMin(0), budgetMax(0), preferredCity(""),          // Budget defaults
        preferredType(PropertyType::APARTMENT), minArea(0), maxArea(0), // Type and area defaults
        minRooms(0), maxRooms(0), hasPreferences(false) {       // Room defaults and preferences flag
    }

    // Client type getter/setter.
    ClientType getType() const { return type; }                 // Return client type
    void setType(ClientType t) { type = t; }                    // Change client type

    // Add a transaction ID to the history.
    void addTransaction(int transID) { transactionIDs.push_back(transID); } // Append transaction ID

    // Return reference to transaction history (const to protect external modification).
    const vector<int>& getTransactionHistory() const { return transactionIDs; } // Return const reference to history

    // Set budget range (turns hasPreferences true).
    void setBudget(double min, double max) { budgetMin = min; budgetMax = max; hasPreferences = true; } // Set budget and mark preferences as set
    void setPreferredCity(const string& city) { preferredCity = city; hasPreferences = true; } // Set preferred city and mark preferences set
    void setPreferredType(PropertyType t) { preferredType = t; hasPreferences = true; } // Set preferred property type
    void setAreaRange(double min, double max) { minArea = min; maxArea = max; hasPreferences = true; } // Set area range
    void setRoomsRange(int min, int max) { minRooms = min; maxRooms = max; hasPreferences = true; } // Set rooms range

    // Check if any preferences have been set.
    bool preferencesSet() const { return hasPreferences; }     // Return whether preferences have been configured

    // Getters for preferences.
    double getBudgetMin() const { return budgetMin; }          // Get minimum budget
    double getBudgetMax() const { return budgetMax; }          // Get maximum budget
    string getPreferredCity() const { return preferredCity; }  // Get preferred city
    PropertyType getPreferredType() const { return preferredType; } // Get preferred property type
    double getMinArea() const { return minArea; }              // Get minimum area
    double getMaxArea() const { return maxArea; }              // Get maximum area
    int getMinRooms() const { return minRooms; }               // Get minimum rooms
    int getMaxRooms() const { return maxRooms; }               // Get maximum rooms

    // Override display to include client-specific info.
    void display() const override {                            // Polymorphic display for Client
        Person::display();                                     // Call base class display (ID, name, contact)
        cout << ", Type: " << clientTypeToString(type)         // Print client type
            << ", Transactions: " << transactionIDs.size();    // Print number of transactions
        if (hasPreferences) {                                  // Only show preferences if set
            cout << "\n  Preferences: Budget $" << budgetMin << " - $" << budgetMax // Budget range
                << ", City: " << (preferredCity.empty() ? "Any" : preferredCity) // City or "Any"
                << ", Type: " << propertyTypeToString(preferredType) // Preferred property type
                << ", Area: " << minArea << "-" << maxArea << " sqm" // Area range
                << ", Rooms: " << minRooms << "-" << maxRooms; // Room range
        }
    }

    // --- Operator Overloads ---
    // Equality based on ID (clients are uniquely identified by ID).
    bool operator==(const Client& other) const {               // Compare two clients by ID
        return id == other.id;                                 // True if IDs match
    }

    // Stream output operator for easy printing.
    friend ostream& operator<<(ostream& os, const Client& client) { // Overloaded << for Client
        os << "ID: " << client.getID() << ", Name: " << client.getName() // Print ID, name
            << ", Contact: " << client.getContactInfo()        // Contact info
            << ", Type: " << clientTypeToString(client.type)   // Client type
            << ", Transactions: " << client.transactionIDs.size(); // Transaction count
        if (client.hasPreferences) {                           // Print preferences if set
            os << "\n  Preferences: Budget $" << client.budgetMin << " - $" << client.budgetMax
                << ", City: " << (client.preferredCity.empty() ? "Any" : client.preferredCity)
                << ", Type: " << propertyTypeToString(client.preferredType)
                << ", Area: " << client.minArea << "-" << client.maxArea << " sqm"
                << ", Rooms: " << client.minRooms << "-" << client.maxRooms;
        }
        return os;                                             // Return the stream for chaining
    }
};

// -------------------- Agent Class --------------------
// Inherits Person, represents a real estate agent with commission and assigned properties.
class Agent : public Person {
private:
    double commissionRate;                 // Percentage commission on deals.
    vector<int> assignedPropertyIDs;       // Properties currently handled.
    vector<int> salesHistoryIDs;           // Record of transactions where agent participated.

public:
    // Constructor takes id, name, contact, and commission.
    Agent(int id, const string& name, const string& contact, double commRate)
        : Person(id, name, contact), commissionRate(commRate) { // Initialize base and commission
    }

    // Commission getter/setter.
    double getCommissionRate() const { return commissionRate; } // Return commission rate
    void setCommissionRate(double rate) { commissionRate = rate; } // Set commission rate

    // Assign a property to the agent.
    void assignProperty(int propertyID) { assignedPropertyIDs.push_back(propertyID); } // Add property ID to portfolio

    // Remove property from agent's list (if exists).
    void removeProperty(int propertyID) {                       // Remove a property from portfolio
        auto it = find(assignedPropertyIDs.begin(), assignedPropertyIDs.end(), propertyID); // Find the ID
        if (it != assignedPropertyIDs.end()) assignedPropertyIDs.erase(it); // Erase if found
    }

    // Get list of assigned property IDs.
    const vector<int>& getAssignedProperties() const { return assignedPropertyIDs; } // Return const reference to portfolio

    // Record a sale/rental transaction.
    void addSale(int transactionID) { salesHistoryIDs.push_back(transactionID); } // Append to sales history

    // Get sales history.
    const vector<int>& getSalesHistory() const { return salesHistoryIDs; } // Return const reference to history

    // Display agent details.
    void display() const override {                            // Polymorphic display for Agent
        Person::display();                                     // Base info (ID, name, contact)
        cout << ", Commission Rate: " << commissionRate << "%" // Commission rate
            << ", Assigned Properties: " << assignedPropertyIDs.size() // Number of assigned properties
            << ", Sales: " << salesHistoryIDs.size();          // Number of sales recorded
    }

    // Equality operator based on ID.
    bool operator==(const Agent& other) const {               // Compare two agents by their IDs
        return id == other.id;                                // True if IDs match
    }

    // Stream output operator.
    friend ostream& operator<<(ostream& os, const Agent& agent) { // Overloaded << for Agent
        os << "ID: " << agent.id << ", Name: " << agent.name  // Print ID, name
            << ", Contact: " << agent.contactInfo             // Contact info
            << ", Commission Rate: " << agent.commissionRate << "%" // Commission
            << ", Assigned Properties: " << agent.assignedPropertyIDs.size() // Portfolio size
            << ", Sales: " << agent.salesHistoryIDs.size();   // Sales history size
        return os;                                            // Return stream for chaining
    }
};

// -------------------- Property Base Class --------------------
// Abstract base for different property types.
class Property {
protected:
    int id;                     // Unique property ID.
    string address;             // Street address.
    string city;                // City.
    PropertyType type;          // Type (Apartment, Villa, etc.).
    double area;                // Area in square meters.
    int rooms;                  // Number of rooms (0 for Land).
    double price;               // Listing price in dollars.
    int ownerID;                // Client ID of the owner (seller/landlord).
    int agentID;                // Agent ID assigned (0 if none).
    PropertyStatus status;      // Availability status.

public:
    // Constructor initializes all fields, sets status to AVAILABLE, agent to 0.
    Property(int id, const string& addr, const string& cty, PropertyType t,
        double a, int r, double p, int owner)
        : id(id), address(addr), city(cty), type(t), area(a), rooms(r), price(p), // Initialize all fields
        ownerID(owner), agentID(0), status(PropertyStatus::AVAILABLE) {           // No agent assigned, available
    }

    // Virtual destructor.
    virtual ~Property() = default;                            // Virtual destructor for polymorphism

    // Getters.
    int getID() const { return id; }                          // Return property ID
    string getAddress() const { return address; }             // Return address
    string getCity() const { return city; }                   // Return city
    PropertyType getType() const { return type; }             // Return property type
    double getArea() const { return area; }                   // Return area
    int getRooms() const { return rooms; }                    // Return number of rooms
    double getPrice() const { return price; }                 // Return price
    int getOwnerID() const { return ownerID; }                // Return owner client ID
    int getAgentID() const { return agentID; }                // Return assigned agent ID
    PropertyStatus getStatus() const { return status; }       // Return listing status

    // Setters for editable fields.
    void setAddress(const string& a) { address = a; }        // Set address
    void setCity(const string& c) { city = c; }               // Set city
    void setArea(double a) { area = a; }                      // Set area
    void setRooms(int r) { rooms = r; }                       // Set rooms
    void setPrice(double p) { price = p; }                    // Set price
    void setOwnerID(int o) { ownerID = o; }                   // Set owner client ID
    void setAgentID(int a) { agentID = a; }                   // Set agent ID
    void setStatus(PropertyStatus s) { status = s; }          // Set listing status

    // Pure virtual function to return a type-specific string (implemented by derived).
    virtual string getPropertyTypeStr() const = 0;            // Must be implemented by derived classes

    // Virtual display method (overridden in Land to skip rooms).
    virtual void display() const {                            // Print property information to console
        cout << "ID: " << id << ", Type: " << getPropertyTypeStr() // ID and type
            << ", Address: " << address << ", City: " << city // Address, city
            << ", Area: " << area << " sqm, Rooms: " << rooms // Area and rooms
            << ", Price: $" << fixed << setprecision(2) << price // Price formatted to 2 decimals
            << ", Owner ID: " << ownerID << ", Agent ID: " << agentID // Owner and agent IDs
            << ", Status: " << statusToString(status);        // Status string
    }

    // Equality based on ID.
    bool operator==(const Property& other) const {            // Compare properties by ID
        return id == other.id;                                // True if same ID
    }

    // Stream output operator (virtual behavior via getPropertyTypeStr).
    friend ostream& operator<<(ostream& os, const Property& prop) { // Overloaded << for Property
        os << "ID: " << prop.id << ", Type: " << prop.getPropertyTypeStr() // ID and type
            << ", Address: " << prop.address << ", City: " << prop.city // Address and city
            << ", Area: " << prop.area << " sqm, Rooms: " << prop.rooms // Area and rooms
            << ", Price: $" << fixed << setprecision(2) << prop.price // Price
            << ", Owner ID: " << prop.ownerID << ", Agent ID: " << prop.agentID // Owner/agent
            << ", Status: " << statusToString(prop.status);   // Status string
        return os;                                            // Return stream for chaining
    }
};

// -------------------- Derived Property Classes --------------------
// Apartment: inherits Property, sets type to APARTMENT.
class Apartment : public Property {
public:
    Apartment(int id, const string& addr, const string& cty,
        double a, int r, double p, int owner)
        : Property(id, addr, cty, PropertyType::APARTMENT, a, r, p, owner) { // Delegate to Property ctor with APARTMENT type
    }
    string getPropertyTypeStr() const override { return "Apartment"; } // Return "Apartment"
};

// Villa: inherits Property.
class Villa : public Property {
public:
    Villa(int id, const string& addr, const string& cty,
        double a, int r, double p, int owner)
        : Property(id, addr, cty, PropertyType::VILLA, a, r, p, owner) { // Delegate with VILLA type
    }
    string getPropertyTypeStr() const override { return "Villa"; } // Return "Villa"
};

// Office: inherits Property.
class Office : public Property {
public:
    Office(int id, const string& addr, const string& cty,
        double a, int r, double p, int owner)
        : Property(id, addr, cty, PropertyType::OFFICE, a, r, p, owner) { // Delegate with OFFICE type
    }
    string getPropertyTypeStr() const override { return "Office"; } // Return "Office"
};

// Land: special property type, rooms forced to 0, overrides display to hide rooms.
class Land : public Property {
public:
    Land(int id, const string& addr, const string& cty,
        double a, double p, int owner)
        : Property(id, addr, cty, PropertyType::LAND, a, 0, p, owner) { // Rooms always 0 for Land
    }
    string getPropertyTypeStr() const override { return "Land"; } // Return "Land"
    void display() const override {                                 // Overridden display to hide rooms
        cout << "ID: " << id << ", Type: Land, Address: " << address // ID, type, address
            << ", City: " << city << ", Area: " << area << " sqm"   // City and area
            << ", Price: $" << fixed << setprecision(2) << price    // Price
            << ", Owner ID: " << ownerID << ", Agent ID: " << agentID // Owner/agent IDs
            << ", Status: " << statusToString(status);              // Status
    }
};

// -------------------- Transaction Class --------------------
// Represents a completed sale or rental transaction.
class Transaction {
private:
    int id;                         // Unique transaction ID.
    TransactionType type;           // SALE or RENTAL.
    int propertyID;                 // ID of the involved property.
    int clientID;                   // Buyer or renter client ID.
    int ownerID;                    // Seller or landlord client ID.
    int agentID;                    // Agent involved (0 if none).
    double amount;                  // Sale price or monthly rent amount.
    double commission;              // Commission earned by agent.
    string date;                    // Date of transaction (YYYY-MM-DD).

public:
    // Constructor.
    Transaction(int id, TransactionType t, int propID, int client, int owner, int agent,
        double amt, double comm, const string& dt)
        : id(id), type(t), propertyID(propID), clientID(client), ownerID(owner), agentID(agent), // Initialize all fields
        amount(amt), commission(comm), date(dt) {                                                // Amount, commission, date
    }

    // Getters.
    int getID() const { return id; }                             // Return transaction ID
    TransactionType getType() const { return type; }             // Return transaction type
    int getPropertyID() const { return propertyID; }             // Return property ID
    int getClientID() const { return clientID; }                 // Return client (buyer/renter) ID
    int getOwnerID() const { return ownerID; }                   // Return owner (seller/landlord) ID
    int getAgentID() const { return agentID; }                   // Return agent ID
    double getAmount() const { return amount; }                  // Return amount
    double getCommission() const { return commission; }          // Return commission
    string getDate() const { return date; }                      // Return date string

    // Display transaction details.
    void display() const {                                       // Print transaction information
        cout << "Transaction ID: " << id                        // ID
            << ", Type: " << (type == TransactionType::SALE ? "Sale" : "Rental") // Type string
            << ", Property ID: " << propertyID                  // Property
            << ", Buyer/Renter ID: " << clientID                // Client
            << ", Seller/Landlord ID: " << ownerID              // Owner
            << ", Agent ID: " << agentID                        // Agent
            << ", Amount: " << fixed << setprecision(2) << amount // Amount
            << ", Commission: " << commission                    // Commission
            << ", Date: " << date;                               // Date
    }

    // Equality operator.
	bool operator==(const Transaction& other) const {            // Compare transactions by ID   2 CLIENTS ARE EQUAL IF THEY HAVE THE SAME ID
        return id == other.id;                                   // Same ID → equal
    }

    // Stream output.
    friend ostream& operator<<(ostream& os, const Transaction& trans) { //  Declares a friend function so it can access private members of Client
        os << "Transaction ID: " << trans.id                    // ID
            << ", Type: " << (trans.type == TransactionType::SALE ? "Sale" : "Rental") // Type
            << ", Property ID: " << trans.propertyID            // Property ID
            << ", Buyer/Renter ID: " << trans.clientID          // Client ID
            << ", Seller/Landlord ID: " << trans.ownerID        // Owner ID
            << ", Agent ID: " << trans.agentID                  // Agent ID
            << ", Amount: $" << fixed << setprecision(2) << trans.amount // Amount
            << ", Commission: $" << trans.commission            // Commission
            << ", Date: " << trans.date;                        // Date
        return os;                                              // Return stream for chaining
    }
};

// -------------------- Contract Class --------------------
// Represents a formal contract derived from a transaction.
class Contract {
private:
    int id;                     // Unique contract ID.
    int transactionID;          // Associated transaction ID.
    string contractType;        // "Sale Contract" or "Rental Contract".
    string date;                // Contract date.
    double amount;              // Amount specified.
    int propertyID;             // Property ID.
    int clientID;               // Client (buyer/renter) ID.
    int agentID;                // Agent ID (0 if none).
    int durationMonths;         // For rentals, the lease duration in months.

public:
    // Constructor with default duration 0 (sales).
    Contract(int id, int transID, const string& type, const string& dt,
        double amt, int propID, int client, int agent, int duration = 0)
        : id(id), transactionID(transID), contractType(type), date(dt), // Initialize members
        amount(amt), propertyID(propID), clientID(client), agentID(agent),
        durationMonths(duration) {                                      // Duration (default 0)
    }

    // Getters.
    int getID() const { return id; }                             // Return contract ID
    int getTransactionID() const { return transactionID; }       // Return associated transaction ID
    string getContractType() const { return contractType; }      // Return contract type string
    string getDate() const { return date; }                      // Return date
    double getAmount() const { return amount; }                  // Return amount
    int getPropertyID() const { return propertyID; }             // Return property ID
    int getClientID() const { return clientID; }                 // Return client ID
    int getAgentID() const { return agentID; }                   // Return agent ID
    int getDurationMonths() const { return durationMonths; }     // Return duration in months

    // Basic display.
    void display() const {                                       // Print contract summary
        cout << "Contract ID: " << id                            // ID
            << ", Type: " << contractType                        // Type
            << ", Property ID: " << propertyID                   // Property ID
            << ", Client ID: " << clientID                       // Client ID
            << ", Agent ID: " << agentID                         // Agent ID
            << ", Amount: $" << fixed << setprecision(2) << amount // Amount
            << ", Date: " << date;                               // Date
        if (durationMonths > 0) cout << ", Duration: " << durationMonths << " months"; // Duration for rentals
    }

    // Full display with resolved entity details (requires maps from agency).
    void displayFull(const map<int, shared_ptr<Property>>& propertyMap, // Takes property map to look up the property
        const map<int, shared_ptr<Client>>& clientMap,                // Client map
        const map<int, shared_ptr<Agent>>& agentMap) const {          // Agent map
        // Print header.
        cout << "\n========== CONTRACT #" << id << " ==========" << "\n"; // Header with contract ID
        cout << "Type: " << contractType << "\n";                   // Contract type
        cout << "Date: " << date << "\n";                           // Date
        cout << "Amount: $" << fixed << setprecision(2) << amount << "\n"; // Amount
        if (durationMonths > 0) cout << "Duration: " << durationMonths << " months\n"; // Duration if rental
        cout << "\n";

        // Look up and print property.
        auto propIt = propertyMap.find(propertyID);                 // Find property by ID
        if (propIt != propertyMap.end()) {                          // If found
            cout << "--- Property ---\n";
            cout << *(propIt->second) << "\n";                      // Print property via operator<<
        }

        // Look up and print client.
        auto clientIt = clientMap.find(clientID);                   // Find client by ID
        if (clientIt != clientMap.end()) {                          // If found
            cout << "--- Client ---\n";
            cout << *(clientIt->second) << "\n";                    // Print client via operator<<
        }

        // Look up and print agent if assigned.
        if (agentID != 0) {                                         // Only if an agent is assigned
            auto agentIt = agentMap.find(agentID);                  // Find agent by ID
            if (agentIt != agentMap.end()) {                        // If found
                cout << "--- Agent ---\n";
                cout << *(agentIt->second) << "\n";                 // Print agent via operator<<
            }
        }
        cout << "=========================================\n";     // Footer
    }

    // Equality based on ID.
    bool operator==(const Contract& other) const {                  // Compare contracts by ID
        return id == other.id;                                      // Same ID → equal
    }

    // Stream output.
    friend ostream& operator<<(ostream& os, const Contract& contract) { // Declares a friend function so it can access private members of Contract.
        os << "Contract ID: " << contract.id                        // ID
            << ", Type: " << contract.contractType                  // Type
            << ", Property ID: " << contract.propertyID             // Property ID
            << ", Client ID: " << contract.clientID                 // Client ID
            << ", Agent ID: " << contract.agentID                   // Agent ID
            << ", Amount: $" << fixed << setprecision(2) << contract.amount // Amount
            << ", Date: " << contract.date;                         // Date
        if (contract.durationMonths > 0) os << ", Duration: " << contract.durationMonths << " months"; // Duration
        return os;                                                  // Return stream
    }
};

// -------------------- RealEstateAgency Class --------------------
// Core business logic class that manages all entities and user authentication.
// Contains methods for both console and GUI operations.
class RealEstateAgency {
    // Grant friendship to AppGUI (defined in Gui.h) and ReportGenerator.
    friend class AppGUI;                                            // Allow AppGUI access to private members
    friend class ReportGenerator;                                   // Allow ReportGenerator access to private members

private:
    // Containers: vectors maintain insertion order; maps provide fast ID-based lookup.
    vector<shared_ptr<Property>> properties;                        // All properties (in insertion order) Each vector holds a list of objects (like a shelf with items).
    vector<shared_ptr<Client>> clients;                             // All clients
    vector<shared_ptr<Agent>> agents;                               // All agents
    vector<shared_ptr<Transaction>> transactions;                   // All transactions
    vector<shared_ptr<Contract>> contracts;                         // All contracts

    // Maps for efficient ID -> shared_ptr lookups.
    map<int, shared_ptr<Property>> propertyMap;                     // ID → Property
    map<int, shared_ptr<Client>> clientMap;                         // ID → Client
    map<int, shared_ptr<Agent>> agentMap;                      // ID → Agent You give them a key (like a property ID number), and they give you the object back
    map<int, shared_ptr<Transaction>> transactionMap;               // ID → Transaction
    map<int, shared_ptr<Contract>> contractMap;                     // ID → Contract

    // User credentials storage (username -> User).
    unordered_map<string, User> users;                              // Username → User object
    const string USERS_FILE = "users.txt";                          // File name for user persistence

    // Helper: get current date as YYYY-MM-DD string.
    string getCurrentDate() const {                                 // Returns today's date as string
        auto now = chrono::system_clock::now();                     // Get current time point
        time_t now_time = chrono::system_clock::to_time_t(now);     // Convert to time_t     Gets today’s date from the computer clock.
        tm ltm;                                                     // tm structure for local time
#ifdef _WIN32
        localtime_s(&ltm, &now_time);                               // Windows secure localtime
#else
        localtime_r(&now_time, &ltm);                               // POSIX localtime_r
#endif
        ostringstream oss;
        oss << put_time(&ltm, "%Y-%m-%d");                          // Format as YYYY-MM-DD
        return oss.str();                                           // Return the string
    }

public:
    // Default constructor.
    RealEstateAgency() = default;                                   // Default constructor (all containers empty)

    // -------------------- GUI Support Methods --------------------
    // Adds a property via GUI; returns true on success, sets outError on failure.
    // Allows id = 0 to auto-generate, otherwise uses provided ID after checking uniqueness.
    bool addPropertyGUI(int id, PropertyType ptype, const string& address, const string& city,
        double area, int rooms, double price, int ownerID, int agentID,
        string& outError) {                                         // GUI-friendly property addition
        // If a specific ID is provided (greater than 0), verify uniqueness and mark as used.
        if (id > 0) {                                               // User provided an explicit ID
            if (propertyMap.count(id)) {                            // Check for duplicate in map
                outError = "Property ID already exists.";           // Set error message
                return false;                                       // Failure
            }
            IDGenerator::markUsedID(id);                            // Reserve the manually chosen ID
        }
        else {
            // Auto-generate ID.
            id = IDGenerator::getNextPropertyID();                  // Generate a fresh ID
        }

        // Validate owner client exists.
        if (clientMap.find(ownerID) == clientMap.end()) {           // Look up owner ID in client map
            outError = "Owner Client ID not found.";                // Error if missing
            return false;
        }
        // Validate agent if assigned (0 means no agent).
        if (agentID != 0 && agentMap.find(agentID) == agentMap.end()) { // If agent ID provided but not found
            outError = "Agent ID not found.";
            return false;
        }

        int newID = id;                                             // Use the determined ID
        shared_ptr<Property> prop;                                  // Will hold the new property

        // Instantiate the appropriate derived class based on property type.
        switch (ptype) {                                            // Branch on property type enum
        case PropertyType::APARTMENT:
            prop = make_shared<Apartment>(newID, address, city, area, rooms, price, ownerID); // Create Apartment  make shared is Exception Safe
            break;
        case PropertyType::VILLA:
            prop = make_shared<Villa>(newID, address, city, area, rooms, price, ownerID);     // Create Villa 
            break;
        case PropertyType::OFFICE:
            prop = make_shared<Office>(newID, address, city, area, rooms, price, ownerID);    // Create Office
            break;
        case PropertyType::LAND:
            prop = make_shared<Land>(newID, address, city, area, price, ownerID);             // Create Land (no rooms)
            break;
        default:
            outError = "Invalid property type.";                    // Should never happen
            return false;
        }

        // Set agent if provided and assign the property to that agent.
        prop->setAgentID(agentID);                                  // Attach agent ID to property
        if (agentID != 0) {
            agentMap[agentID]->assignProperty(newID);               // Add property to agent's portfolio
        }

        // Add to both vector and map.
        properties.push_back(prop);                                 // Append to vector
        propertyMap[newID] = prop;                                  // Insert into map
        return true;                                                // Success
    }

    // Edit an existing property's basic fields, returns false if ID not found or validation fails.
    bool editPropertyGUI(int id, const string& address, const string& city,
        double area, int rooms, double price, int ownerID,
        string& outError) {                                         // Modify property details
        auto it = propertyMap.find(id);                             // Look for property by ID
        if (it == propertyMap.end()) {
            outError = "Property not found.";
            return false;
        }
        // Input validation.
        if (address.empty()) { outError = "Address cannot be empty."; return false; } // Address required
        if (city.empty()) { outError = "City cannot be empty."; return false; }       // City required
        if (area <= 0) { outError = "Area must be greater than zero."; return false; } // Positive area
        if (price < 0) { outError = "Price cannot be negative."; return false; }       // Non-negative price
        if (clientMap.find(ownerID) == clientMap.end()) { outError = "Owner Client ID not found."; return false; } // Owner must exist

        auto prop = it->second;                                     // Access the property
        prop->setAddress(address);                                  // Update address
        prop->setCity(city);                                        // Update city
        prop->setArea(area);                                        // Update area
        // Only update rooms for non-land properties.
        if (prop->getType() != PropertyType::LAND) prop->setRooms(rooms); // Skip rooms for Land
        prop->setPrice(price);                                      // Update price
        prop->setOwnerID(ownerID);                                  // Update owner ID

        return true;                                                // Success
    }

    // Add a client via GUI. Returns true if successful.
    bool addClientGUI(int id, const string& name, const string& contact, ClientType type,
        string& outError) {                                         // Insert a new client
        if (id > 0) {
            // Check for ID conflict across all persons (clients and agents share ID space).
            if (clientMap.count(id) || agentMap.count(id)) {        // Is ID already used as person?
                outError = "Person ID already exists.";
                return false;
            }
            IDGenerator::markUsedID(id);
        }
        else {
            id = IDGenerator::getNextPersonID();                    // Auto-generate person ID
        }

        if (name.empty()) { outError = "Client name cannot be empty."; return false; }     // Name required
        if (contact.empty()) { outError = "Contact info cannot be empty."; return false; } // Contact required

        int newID = id;
        auto client = make_shared<Client>(newID, name, contact, type); // Create client object
        clients.push_back(client);                                 // Add to vector
        clientMap[newID] = client;                                 // Add to map
        outError = "";                                             // Clear error
        return true;
    }

    // Edit client info.
    bool editClientGUI(int id, const string& name, const string& contact, ClientType type,
        string& outError) {                                         // Modify an existing client
        auto it = clientMap.find(id);                               // Find client by ID
        if (it == clientMap.end()) {
            outError = "Client not found.";
            return false;
        }
        if (name.empty()) { outError = "Client name cannot be empty."; return false; }
        if (contact.empty()) { outError = "Contact info cannot be empty."; return false; }

        auto client = it->second;
        client->setName(name);                                      // Update name
        client->setContactInfo(contact);                            // Update contact
        client->setType(type);                                      // Update type

        outError = "";
        return true;
    }

    // Add an agent.
    bool addAgentGUI(int id, const string& name, const string& contact, double commRate,
        string& outError) {                                         // Create a new agent
        if (id > 0) {
            if (agentMap.count(id) || clientMap.count(id)) {        // Check person ID uniqueness
                outError = "Person ID already exists.";
                return false;
            }
            IDGenerator::markUsedID(id);
        }
        else {
            id = IDGenerator::getNextPersonID();
        }

        if (name.empty()) { outError = "Agent name cannot be empty."; return false; }
        if (contact.empty()) { outError = "Contact info cannot be empty."; return false; }
        if (commRate < 0) { outError = "Commission rate cannot be negative."; return false; }

        int newID = id;
        auto agent = make_shared<Agent>(newID, name, contact, commRate); // Create agent   auto deduces the type as shared_ptr<Agent>
        agents.push_back(agent);                                   // Add to vector
        agentMap[newID] = agent;                                   // Add to map
        outError = "";
        return true;
    }

    // Record a sale transaction via GUI, with optional provided transaction/contract IDs.
    bool recordSaleGUI(int transID, int contractID, int propID, int clientID, int agentID,
        double salePrice, string& outError) {                       // Process a sale
        auto propIt = propertyMap.find(propID);                    // Find property
        if (propIt == propertyMap.end()) { outError = "Property not found."; return false; }
        if (propIt->second->getStatus() != PropertyStatus::AVAILABLE) { // Must be available
            outError = "Property is not available."; return false;
        }
        auto clientIt = clientMap.find(clientID);                  // Find client (buyer)
        if (clientIt == clientMap.end()) { outError = "Client not found."; return false; }
        shared_ptr<Agent> agent = nullptr;
        if (agentID != 0) {
            auto agentIt = agentMap.find(agentID);                 // Find agent if specified
            if (agentIt == agentMap.end()) { outError = "Agent not found."; return false; }
            agent = agentIt->second;
        }

        // Manage IDs: if >0, ensure uniqueness; else auto-generate.
        if (transID > 0) {
            if (transactionMap.count(transID)) { outError = "Transaction ID already exists."; return false; }
            IDGenerator::markUsedID(transID);
        }
        else {
            transID = IDGenerator::getNextTransactionID();
        }
        if (contractID > 0) {
            if (contractMap.count(contractID)) { outError = "Contract ID already exists."; return false; }
            IDGenerator::markUsedID(contractID);
        }
        else {
            contractID = IDGenerator::getNextContractID();
        }

        // Calculate commission based on agent's rate.
        double commission = 0.0;
        if (agent) {
            commission = salePrice * (agent->getCommissionRate() / 100.0); // Commission = price * (rate/100)
        }

        string date = getCurrentDate();                             // Get today's date
        int ownerID = propIt->second->getOwnerID();                 // The seller's ID
        // Create transaction object.
        auto trans = make_shared<Transaction>(
            transID, TransactionType::SALE, propID, clientID, ownerID, agentID,
            salePrice, commission, date
        );
        transactions.push_back(trans);                              // Store transaction
        transactionMap[transID] = trans;

        // Update property: mark as SOLD and transfer ownership to buyer.
        propIt->second->setStatus(PropertyStatus::SOLD);            // Property is now sold
        propIt->second->setOwnerID(clientID);                       // Buyer becomes owner
        clientIt->second->addTransaction(transID);                  // Add to buyer's history

        // Also link the transaction to the seller/owner's history.
        auto ownerIt = clientMap.find(ownerID);                     // Find original owner
        if (ownerIt != clientMap.end()) {
            ownerIt->second->addTransaction(transID);
        }

        // If an agent was involved, record the sale in their history.
        if (agent) agent->addSale(transID);

        // Create a contract.
        auto contract = make_shared<Contract>(
            contractID, transID, "Sale Contract", date, salePrice,
            propID, clientID, agentID
        );
        contracts.push_back(contract);                              // Store contract
        contractMap[contractID] = contract;

        return true;
    }

    // Record a rental transaction, similar to sale but with duration.
    bool recordRentalGUI(int transID, int contractID, int propID, int clientID, int agentID,
        double rentAmount, int durationMonths, string& outError) {   // Process a rental
        auto propIt = propertyMap.find(propID);                    // Find property
        if (propIt == propertyMap.end()) { outError = "Property not found."; return false; }
        if (propIt->second->getStatus() != PropertyStatus::AVAILABLE) { // Must be available
            outError = "Property is not available."; return false;
        }
        auto clientIt = clientMap.find(clientID);                  // Find renter
        if (clientIt == clientMap.end()) { outError = "Client not found."; return false; }
        shared_ptr<Agent> agent = nullptr;
        if (agentID != 0) {
            auto agentIt = agentMap.find(agentID);
            if (agentIt == agentMap.end()) { outError = "Agent not found."; return false; }
            agent = agentIt->second;
        }

        // Manage IDs.
        if (transID > 0) {
            if (transactionMap.count(transID)) { outError = "Transaction ID already exists."; return false; }
            IDGenerator::markUsedID(transID);
        }
        else {
            transID = IDGenerator::getNextTransactionID();
        }
        if (contractID > 0) {
            if (contractMap.count(contractID)) { outError = "Contract ID already exists."; return false; }
            IDGenerator::markUsedID(contractID);
        }
        else {
            contractID = IDGenerator::getNextContractID();
        }

        double commission = 0.0;
        if (agent) {
            commission = rentAmount * (agent->getCommissionRate() / 100.0); // Monthly commission
        }

        string date = getCurrentDate();
        int ownerID = propIt->second->getOwnerID();                 // Landlord
        auto trans = make_shared<Transaction>(
            transID, TransactionType::RENTAL, propID, clientID, ownerID, agentID,
            rentAmount, commission, date
        );
        transactions.push_back(trans);
        transactionMap[transID] = trans;

        // Mark property as rented but ownership stays with landlord.
        propIt->second->setStatus(PropertyStatus::RENTED);
        clientIt->second->addTransaction(transID);

        // Link to landlord.
        auto ownerIt = clientMap.find(ownerID);
        if (ownerIt != clientMap.end()) {
            ownerIt->second->addTransaction(transID);
        }

        if (agent) agent->addSale(transID);

        // Create rental contract with duration.
        auto contract = make_shared<Contract>(
            contractID, transID, "Rental Contract", date, rentAmount,
            propID, clientID, agentID, durationMonths
        );
        contracts.push_back(contract);
        contractMap[contractID] = contract;

        return true;
    }

    // Assign an agent to a property; if agentID is 0, the property is unassigned.
    bool assignAgentGUI(int propID, int agentID, string& outError) { // Change or remove property's agent
        auto propIt = propertyMap.find(propID);                     // Find property
        if (propIt == propertyMap.end()) {
            outError = "Property not found.";
            return false;
        }
        auto agentIt = agentMap.find(agentID);                      // Find agent (agentID 0 will not find anything, which is allowed)
        if (agentIt == agentMap.end() && agentID != 0) {            // If agentID not zero but not found, error
            outError = "Agent not found.";
            return false;
        }

        // Remove property from old agent.
        int oldAgentID = propIt->second->getAgentID();              // Current agent
        if (oldAgentID != 0) {
            auto oldAgentIt = agentMap.find(oldAgentID);            // Find old agent
            if (oldAgentIt != agentMap.end()) {
                oldAgentIt->second->removeProperty(propID);         // Remove from old agent's list
            }
        }

        // Assign new agent and update agent's list.
        propIt->second->setAgentID(agentID);                        // Set new agent (0 means none)
        if (agentID != 0) {
            agentIt->second->assignProperty(propID);                // Add to new agent's portfolio
        }
        return true;
    }

    // Remove a property (only if it's AVAILABLE).
    bool removePropertyGUI(int id, string& outError) {               // Delete a property from the system
        auto it = propertyMap.find(id);                              // Find property by ID
        if (it == propertyMap.end()) {
            outError = "Property not found.";
            return false;
        }
        auto prop = it->second;
        if (prop->getStatus() != PropertyStatus::AVAILABLE) {        // Must be available to remove
            outError = "Cannot remove a property that is already sold or rented.";
            return false;
        }

        // Unassign any agent.
        int agentID = prop->getAgentID();
        if (agentID != 0) {
            auto agentIt = agentMap.find(agentID);
            if (agentIt != agentMap.end())
                agentIt->second->removeProperty(id);                // Remove from agent's portfolio
        }

        // Erase from vector (use find_if with ID predicate).
        auto vecIt = find_if(properties.begin(), properties.end(),
            [id](const shared_ptr<Property>& p) { return p->getID() == id; }); // Find in vector
        if (vecIt != properties.end())
            properties.erase(vecIt);                                 // Remove from vector
        propertyMap.erase(it);                                       // Remove from map
        return true;
    }

    // Remove a client (only if they don't own any properties).
    bool removeClientGUI(int id, string& outError) {                 // Delete a client
        auto it = clientMap.find(id);
        if (it == clientMap.end()) {
            outError = "Client not found.";
            return false;
        }

        // Check if client is still an owner of any property.
        for (const auto& p : properties) {
            if (p->getOwnerID() == id) {                             // Client is owner of some property
                outError = "Cannot remove client who still owns properties. Transfer ownership or remove properties first.";
                return false;
            }
        }

        auto vecIt = find_if(clients.begin(), clients.end(),
            [id](const shared_ptr<Client>& c) { return c->getID() == id; }); // Find in vector
        if (vecIt != clients.end())
            clients.erase(vecIt);                                    // Remove from vector
        clientMap.erase(it);                                         // Remove from map
        return true;
    }

    // Remove an agent (only if no properties are assigned to them).
    bool removeAgentGUI(int id, string& outError) {                  // Delete an agent
        auto it = agentMap.find(id);
        if (it == agentMap.end()) {
            outError = "Agent not found.";
            return false;
        }

        for (const auto& p : properties) {
            if (p->getAgentID() == id) {                             // Agent still assigned to a property
                outError = "Cannot remove agent assigned to properties. Reassign properties first.";
                return false;
            }
        }

        auto vecIt = find_if(agents.begin(), agents.end(),
            [id](const shared_ptr<Agent>& a) { return a->getID() == id; }); // Find in vector
        if (vecIt != agents.end())
            agents.erase(vecIt);                                     // Remove from vector
        agentMap.erase(it);                                          // Remove from map
        return true;
    }

    // Edit agent details.
    bool editAgentGUI(int id, const string& name, const string& contact, double commRate,
        string& outError) {                                           // Modify agent attributes
        auto it = agentMap.find(id);
        if (it == agentMap.end()) { outError = "Agent not found."; return false; }
        if (name.empty()) { outError = "Agent name cannot be empty."; return false; }
        if (contact.empty()) { outError = "Contact info cannot be empty."; return false; }
        if (commRate < 0) { outError = "Commission rate cannot be negative."; return false; }

        auto agent = it->second;
        agent->setName(name);
        agent->setContactInfo(contact);
        agent->setCommissionRate(commRate);

        outError = "";
        return true;
    }

    // -------------------- Authentication --------------------
    // Check username/password; on success sets outRole to user's role.
    bool authenticate(const string& username, const string& password, UserRole& outRole) { // Verify credentials
        auto it = users.find(username);                              // Find user by username
        if (it != users.end() && it->second.checkPassword(password)) { // If found and password matches
            outRole = it->second.getRole();                          // Set the role output parameter
            return true;                                             // Authentication success
        }
        return false;                                                // Failure
    }

    // Load users from file; if file not found, create default admin user.
    void loadUsers() {                                               // Restore users from disk
        ifstream file(USERS_FILE);                                   // Open users.txt
        if (!file.is_open()) {                                       // If file doesn't exist
            // No file exists: create default admin account.
            users["admin"] = User("admin", "admin123", UserRole::ADMIN); // Create admin/admin123
            saveUsers();                                             // Save to disk
            return;
        }

        users.clear();                                               // Clear existing users before loading
        string line;
        while (getline(file, line)) {                                // Read each line
            stringstream ss(line);
            string uname, salt, pwdHash, roleStr;
            getline(ss, uname, '|');                                 // Extract username
            getline(ss, salt, '|');                                  // Extract salt
            getline(ss, pwdHash, '|');                               // Extract password hash
            getline(ss, roleStr, '|');                               // Extract role as string

            int roleInt;
            if (!safeStoi(roleStr, roleInt)) {                       // Convert role to int
                // Corrupted line, skip.
                cerr << "Warning: skipping malformed user line: " << line << "\n"; // Warn about malformed data
                continue;
            }

            UserRole role = static_cast<UserRole>(roleInt);          // Converts the integer role into the UserRole enum 
            User user;
            user.setUsername(uname);
            user.setSalt(salt);
            user.setPasswordHash(pwdHash);
            user.setRole(role);
            users[uname] = user;                                     // Insert into users map
        }
        file.close();
    }

    // Save users to file in pipe-separated format.
    void saveUsers() {                                               // Write users to users.txt
        ofstream file(USERS_FILE);
        for (const auto& [uname, user] : users) {                    // Iterate over all users
            file << user.getUsername() << "|"                        // Username
                << user.getSalt() << "|"                             // Salt
                << user.getPasswordHash() << "|"                     // Password hash
                << static_cast<int>(user.getRole()) << "\n";         // Role as integer
        }
        file.close();
    }

    // -------------------- User Management (Admin only) --------------------
    // Add a new user via console UI.
    void addUser() {                                                 // Console interface to add a user
        string uname, pwd;
        int roleChoice;
        cout << "\n--- Add New User ---\n";
        cout << "Enter username: ";
        getline(cin, uname);                                         // Read username
        if (users.find(uname) != users.end()) {                      // Check if username taken
            cout << "Username already exists.\n";
            return;
        }
        cout << "Enter password: ";
        getline(cin, pwd);                                           // Read password
        cout << "Select role:\n1. Admin\n2. Agent\n3. Client\nChoice: ";
        cin >> roleChoice;                                           // Get role choice
        cin.ignore(numeric_limits<streamsize>::max(), '\n');         // Clear input buffer

        UserRole role;
        switch (roleChoice) {                                        // Map choice to enum
        case 1: role = UserRole::ADMIN; break;
        case 2: role = UserRole::AGENT; break;
        case 3: role = UserRole::CLIENT; break;
        default: cout << "Invalid role.\n"; return;
        }

        users[uname] = User(uname, pwd, role);                       // Create user object and store
        saveUsers();                                                 // Persist
        cout << "User added successfully.\n";
    }

    // Delete a user (cannot delete built-in admin).
    void deleteUser() {                                              // Console interface to delete a user
        string uname;
        cout << "\n--- Delete User ---\n";
        cout << "Enter username to delete: ";
        getline(cin, uname);
        if (uname == "admin") {                                      // Built-in admin is protected
            cout << "Cannot delete the built-in admin account.\n";
            return;
        }
        if (users.erase(uname)) {                                    // Try to erase from map
            saveUsers();
            cout << "User deleted.\n";
        }
        else {
            cout << "User not found.\n";
        }
    }

    // Change a user's password.
    void changeUserPassword() {                                      // Console password change
        string uname, newPwd;
        cout << "\n--- Change User Password ---\n";
        cout << "Enter username: ";
        getline(cin, uname);
        auto it = users.find(uname);
        if (it == users.end()) {
            cout << "User not found.\n";
            return;
        }
        cout << "Enter new password: ";
        getline(cin, newPwd);
        it->second.setPassword(newPwd);                              // Update password hash
        saveUsers();
        cout << "Password changed successfully.\n";
    }

    // List all registered users.
    void listUsers() {                                               // Console listing of users
        cout << "\n--- Registered Users ---\n";
        if (users.empty()) {
            cout << "No users found.\n";
            return;
        }
        for (const auto& [uname, user] : users) {
            cout << "Username: " << uname << ", Role: " << roleToString(user.getRole()) << "\n"; // Print each user
        }
    }

    // -------------------- Property Management --------------------
    // Console interface to add property.
    void addProperty() {                                             // Console dialog for adding a property
        cout << "\n--- Add New Property ---\n";
        int typeChoice;
        cout << "Select type:\n1. Apartment\n2. Villa\n3. Office\n4. Land\nChoice: ";
        cin >> typeChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        PropertyType ptype;
        switch (typeChoice) {                                        // Map choice to PropertyType
        case 1: ptype = PropertyType::APARTMENT; break;
        case 2: ptype = PropertyType::VILLA; break;
        case 3: ptype = PropertyType::OFFICE; break;
        case 4: ptype = PropertyType::LAND; break;
        default: cout << "Invalid property type.\n"; return;
        }

        string address, city;
        double area, price;
        int rooms = 0, ownerID;

        cout << "Address: ";
        getline(cin, address);
        cout << "City: ";
        getline(cin, city);
        cout << "Area (sqm): ";
        cin >> area;
        if (ptype != PropertyType::LAND) {                           // Only ask rooms if not Land
            cout << "Number of rooms: ";
            cin >> rooms;
        }
        cout << "Price: $";
        cin >> price;
        cout << "Owner (Seller) Client ID: ";
        cin >> ownerID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (clientMap.find(ownerID) == clientMap.end()) {            // Validate owner
            cout << "Error: Client ID not found.\n";
            return;
        }
        int newID = IDGenerator::getNextPropertyID();                // Generate ID
        shared_ptr<Property> prop; // Prepare a smart pointer variable that will hold the new property object once we create it.”

        switch (ptype) {                                             // Create the appropriate derived object
        case PropertyType::APARTMENT:
            prop = make_shared<Apartment>(newID, address, city, area, rooms, price, ownerID);// Creates a new Apartment object using make_shared
            break;
        case PropertyType::VILLA:
            prop = make_shared<Villa>(newID, address, city, area, rooms, price, ownerID);
            break;
        case PropertyType::OFFICE:
            prop = make_shared<Office>(newID, address, city, area, rooms, price, ownerID);
            break;
        case PropertyType::LAND:
            prop = make_shared<Land>(newID, address, city, area, price, ownerID);
            break;
        }

        properties.push_back(prop);                                  // Add to vector
        propertyMap[newID] = prop;                                   // Add to map
        cout << "Property added successfully with ID: " << newID << "\n";
    }

    // Console property edit.
    void editProperty() {                                            // Console interface to edit a property
        cout << "\n--- Edit Property ---\n";
        int id;
        cout << "Enter Property ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto it = propertyMap.find(id);
        if (it == propertyMap.end()) {
            cout << "Property not found.\n";
            return;
        }

        auto prop = it->second;
        cout << "Editing Property ID " << id << "\n";
        cout << "Leave blank to keep current value.\n";

        string input;
        cout << "New Address [" << prop->getAddress() << "]: ";
        getline(cin, input);                                         // Potentially empty → keep old
        if (!input.empty()) prop->setAddress(input);

        cout << "New City [" << prop->getCity() << "]: ";
        getline(cin, input);
        if (!input.empty()) prop->setCity(input);

        cout << "New Area [" << prop->getArea() << "]: "; // Prompts for new area size.
        getline(cin, input);
        if (!input.empty()) {
            double val;
            if (safeStod(input, val)) prop->setArea(val);
            else cout << "Invalid number, keeping previous.\n";
        }

        if (prop->getType() != PropertyType::LAND) {                 // Rooms only for non-Land
            cout << "New Rooms [" << prop->getRooms() << "]: ";
            getline(cin, input);
            if (!input.empty()) {
                int val;
                if (safeStoi(input, val)) prop->setRooms(val);
                else cout << "Invalid number, keeping previous.\n";
            }
        }

        cout << "New Price [" << prop->getPrice() << "]: ";
        getline(cin, input);
        if (!input.empty()) {
            double val;
            if (safeStod(input, val)) prop->setPrice(val);
            else cout << "Invalid number, keeping previous.\n";
        }

        cout << "New Owner ID [" << prop->getOwnerID() << "]: ";
        getline(cin, input);
        if (!input.empty()) {
            int val;
            if (safeStoi(input, val) && clientMap.find(val) != clientMap.end()) // Validate owner
                prop->setOwnerID(val);
            else
                cout << "Invalid owner ID, keeping previous.\n";
        }

        cout << "Property updated.\n";
    }

    // Console remove property.
    void removeProperty() {                                          // Console dialog to remove a property
        cout << "\n--- Remove Property ---\n";
        int id;
        cout << "Enter Property ID: ";
        cin >> id;
        cin.ignore();

        auto it = propertyMap.find(id);
        if (it == propertyMap.end()) {
            cout << "Property not found.\n";
            return;
        }

        auto prop = it->second;
        int agentID = prop->getAgentID();
        if (agentID != 0) {                                          // Unassign agent if any
            auto agentIt = agentMap.find(agentID);
            if (agentIt != agentMap.end())
                agentIt->second->removeProperty(id);
        }

        auto vecIt = find_if(properties.begin(), properties.end(),
            [id](const shared_ptr<Property>& p) { return p->getID() == id; }); // Find in vector
        if (vecIt != properties.end())
            properties.erase(vecIt);                                 // Delete from vector
        propertyMap.erase(it);                                       // Delete from map

        cout << "Property removed.\n";
    }

    // List all properties using stream operator.
    void listAllProperties() {                                       // Print all properties
        cout << "\n--- All Properties ---\n";
        if (properties.empty()) {
            cout << "No properties listed.\n";
            return;
        }
        for (auto& p : properties) {
            cout << *p << "\n";                                      // Use operator<<
        }
    }

    // Simple search by city, price, type, status.
    void quickSearchProperties() {                                   // Quick property search
        cout << "\n--- Quick Search ---\n";
        cout << "Search by:\n1. Location (City)\n2. Price Range\n3. Type\n4. Status\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        vector<shared_ptr<Property>> results;
        switch (choice) {                                            // Perform the selected search
        case 1: {
            string city;
            cout << "Enter city: ";
            getline(cin, city);
            for (auto& p : properties) {
                if (p->getCity() == city) results.push_back(p);     // Exact city match
            }
            break;
        }
        case 2: {
            double minP, maxP;
            cout << "Min price: ";
            cin >> minP;
            cout << "Max price: ";
            cin >> maxP;
            for (auto& p : properties) {
                double pr = p->getPrice();
                if (pr >= minP && pr <= maxP) results.push_back(p); // Price range match
            }
            break;
        }
        case 3: {
            int t;
            cout << "Type (1=Apartment,2=Villa,3=Office,4=Land): ";
            cin >> t;
            PropertyType pt;
            switch (t) {                                             // Map user input to PropertyType
            case 1: pt = PropertyType::APARTMENT; break;
            case 2: pt = PropertyType::VILLA; break;
            case 3: pt = PropertyType::OFFICE; break;
            case 4: pt = PropertyType::LAND; break;
            default: cout << "Invalid type.\n"; return;
            }
            for (auto& p : properties) {
                if (p->getType() == pt) results.push_back(p);       // Type match
            }
            break;
        }
        case 4: {
            int s;
            cout << "Status (1=Available,2=Sold,3=Rented): ";
            cin >> s;
            PropertyStatus st;
            switch (s) {
            case 1: st = PropertyStatus::AVAILABLE; break;
            case 2: st = PropertyStatus::SOLD; break;
            case 3: st = PropertyStatus::RENTED; break;
            default: cout << "Invalid status.\n"; return;
            }
            for (auto& p : properties) {
                if (p->getStatus() == st) results.push_back(p);     // Status match
            }
            break;
        }
        default:
            cout << "Invalid choice.\n";
            return;
        }

        cout << "\nFound " << results.size() << " properties:\n";
        for (auto& p : results) {
            cout << *p << "\n";                                      // Display results
        }
    }

    // Advanced search with multiple filters and optional sorting.
    void advancedSearchProperties() {                                // Multi-criteria search with sorting
        cout << "\n--- Advanced Property Search ---\n";
        cout << "Filter by (you can combine multiple, leave blank to skip):\n";

        string city;
        cout << "City (or press Enter to skip): ";
        getline(cin, city);

        double minPrice = -1, maxPrice = -1;
        string input;
        cout << "Min Price (press Enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            if (!safeStod(input, minPrice)) { minPrice = -1; cout << "Invalid, ignoring.\n"; } // Retain -1 as "no filter"
        }
        cout << "Max Price (press Enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            if (!safeStod(input, maxPrice)) { maxPrice = -1; cout << "Invalid, ignoring.\n"; }
        }

        double minArea = -1, maxArea = -1;
        cout << "Min Area (sqm, press Enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            if (!safeStod(input, minArea)) { minArea = -1; cout << "Invalid, ignoring.\n"; }
        }
        cout << "Max Area (sqm, press Enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            if (!safeStod(input, maxArea)) { maxArea = -1; cout << "Invalid, ignoring.\n"; }
        }

        int minRooms = -1, maxRooms = -1;
        cout << "Min Rooms (press Enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            if (!safeStoi(input, minRooms)) { minRooms = -1; cout << "Invalid, ignoring.\n"; }
        }
        cout << "Max Rooms (press Enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            if (!safeStoi(input, maxRooms)) { maxRooms = -1; cout << "Invalid, ignoring.\n"; }
        }

        PropertyType propType;
        bool typeFilter = false;
        cout << "Property Type (1=Apartment,2=Villa,3=Office,4=Land, Enter=skip): ";
        getline(cin, input);
        if (!input.empty()) {
            int t;
            if (safeStoi(input, t)) {
                typeFilter = true;
                switch (t) {
                case 1: propType = PropertyType::APARTMENT; break;
                case 2: propType = PropertyType::VILLA; break;
                case 3: propType = PropertyType::OFFICE; break;
                case 4: propType = PropertyType::LAND; break;
                default: cout << "Invalid type, ignoring.\n"; typeFilter = false;
                }
            }
        }

        PropertyStatus status;
        bool statusFilter = false;
        cout << "Status (1=Available,2=Sold,3=Rented, Enter=skip): ";
        getline(cin, input);
        if (!input.empty()) {
            int s;
            if (safeStoi(input, s)) {
                statusFilter = true;
                switch (s) {
                case 1: status = PropertyStatus::AVAILABLE; break;
                case 2: status = PropertyStatus::SOLD; break;
                case 3: status = PropertyStatus::RENTED; break;
                default: cout << "Invalid status, ignoring.\n"; statusFilter = false;
                }
            }
        }

        vector<shared_ptr<Property>> results;
        for (const auto& p : properties) {                           // Iterate all properties
            bool match = true;

            if (!city.empty() && toLower(p->getCity()) != toLower(city)) // Case-insensitive city comparison
                match = false;
            if (minPrice >= 0 && p->getPrice() < minPrice)          // Min price filter
                match = false;
            if (maxPrice >= 0 && p->getPrice() > maxPrice)          // Max price filter
                match = false;
            if (minArea >= 0 && p->getArea() < minArea)             // Min area filter
                match = false;
            if (maxArea >= 0 && p->getArea() > maxArea)             // Max area filter
                match = false;
            if (minRooms >= 0 && p->getRooms() < minRooms)          // Min rooms filter
                match = false;
            if (maxRooms >= 0 && p->getRooms() > maxRooms)          // Max rooms filter
                match = false;
            if (typeFilter && p->getType() != propType)             // Type filter
                match = false;
            if (statusFilter && p->getStatus() != status)           // Status filter
                match = false;

            if (match) results.push_back(p);                         // Collect matching properties
        }

        if (!results.empty()) {                                      // Sorting menu
            cout << "\nSort by:\n1. Price (Low to High)\n2. Price (High to Low)\n";
            cout << "3. Area (Small to Large)\n4. Area (Large to Small)\n";
            cout << "5. None\nChoice: ";
            int sortChoice;
            cin >> sortChoice;
            cin.ignore();

            switch (sortChoice) {
            case 1:
                sort(results.begin(), results.end(),
                    [](const shared_ptr<Property>& a, const shared_ptr<Property>& b) {
                        return a->getPrice() < b->getPrice();       // Ascending price
                    });
                break;
            case 2:
                sort(results.begin(), results.end(),
                    [](const shared_ptr<Property>& a, const shared_ptr<Property>& b) {
                        return a->getPrice() > b->getPrice();       // Descending price
                    });
                break;
            case 3:
                sort(results.begin(), results.end(),
                    [](const shared_ptr<Property>& a, const shared_ptr<Property>& b) {
                        return a->getArea() < b->getArea();         // Ascending area
                    });
                break;
            case 4:
                sort(results.begin(), results.end(),
                    [](const shared_ptr<Property>& a, const shared_ptr<Property>& b) {
                        return a->getArea() > b->getArea();         // Descending area
                    });
                break;
            default: break;
            }
        }

        cout << "\nFound " << results.size() << " matching properties:\n";
        for (const auto& p : results) {
            cout << *p << "\n";                                      // Display sorted results
        }
    }

    // -------------------- Client Management --------------------
    void addClient() {                                               // Console interface to add a client
        cout << "\n--- Add New Client ---\n";
        string name, contact;
        int typeChoice;
        cout << "Name: ";
        getline(cin, name);
        cout << "Contact (phone/email): ";
        getline(cin, contact);
        cout << "Type:\n1. Buyer\n2. Seller\n3. Renter\nChoice: ";
        cin >> typeChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ClientType ctype;
        switch (typeChoice) {
        case 1: ctype = ClientType::BUYER; break;
        case 2: ctype = ClientType::SELLER; break;
        case 3: ctype = ClientType::RENTER; break;
        default: cout << "Invalid client type.\n"; return;
        }

        int newID = IDGenerator::getNextPersonID();                  // Generate ID
        auto client = make_shared<Client>(newID, name, contact, ctype);
        clients.push_back(client);
        clientMap[newID] = client;

        cout << "Client added successfully. Assigned ID: " << newID << "\n";
    }

    void listAllClients() {                                          // List all clients
        cout << "\n--- All Clients ---\n";
        if (clients.empty()) {
            cout << "No clients registered.\n";
            return;
        }
        for (const auto& c : clients) {
            cout << *c << "\n";                                      // Use operator<<
        }
    }

    void searchClients() {                                           // Console client search
        cout << "\n--- Search Clients ---\n";
        cout << "Search by:\n1. Name\n2. Type\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<shared_ptr<Client>> results;
        if (choice == 1) {
            string name;
            cout << "Enter name (or part of it): ";
            getline(cin, name);
            for (const auto& c : clients) {
                if (c->getName().find(name) != string::npos)         // Substring search
                    results.push_back(c);
            }
        }
        else if (choice == 2) {
            int t;
            cout << "Type (1=Buyer, 2=Seller, 3=Renter): ";
            cin >> t;
            cin.ignore();
            ClientType ct;
            switch (t) {
            case 1: ct = ClientType::BUYER; break;
            case 2: ct = ClientType::SELLER; break;
            case 3: ct = ClientType::RENTER; break;
            default: cout << "Invalid type.\n"; return;
            }
            for (const auto& c : clients) {
                if (c->getType() == ct) results.push_back(c);
            }
        }
        else {
            cout << "Invalid choice.\n";
            return;
        }

        cout << "\nFound " << results.size() << " client(s):\n";
        for (const auto& c : results) {
            cout << *c << "\n";
        }
    }

    // -------------------- Agent Management --------------------
    void addAgent() {                                                // Console interface to add an agent
        cout << "\n--- Add New Agent ---\n";
        string name, contact;
        double commRate;
        cout << "Name: ";
        getline(cin, name);
        cout << "Contact: ";
        getline(cin, contact);
        cout << "Commission rate (%): ";
        cin >> commRate;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int newID = IDGenerator::getNextPersonID();
        auto agent = make_shared<Agent>(newID, name, contact, commRate);
        agents.push_back(agent);
        agentMap[newID] = agent;

        cout << "Agent added successfully. Assigned ID: " << newID << "\n";
    }

    void listAllAgents() {                                           // List all agents
        cout << "\n--- All Agents ---\n";
        if (agents.empty()) {
            cout << "No agents registered.\n";
            return;
        }
        for (const auto& a : agents) {
            cout << *a << "\n";
        }
    }

    void assignAgentToProperty() {                                   // Console agent assignment
        int propID, agentID;
        cout << "Enter Property ID: ";
        cin >> propID;
        cout << "Enter Agent ID: ";
        cin >> agentID;
        cin.ignore();

        auto propIt = propertyMap.find(propID);
        if (propIt == propertyMap.end()) {
            cout << "Property not found.\n";
            return;
        }
        auto agentIt = agentMap.find(agentID);
        if (agentIt == agentMap.end()) {
            cout << "Agent not found.\n";
            return;
        }

        int oldAgent = propIt->second->getAgentID();                  // Unassign previous agent
        if (oldAgent != 0) {
            auto oldIt = agentMap.find(oldAgent);
            if (oldIt != agentMap.end())
                oldIt->second->removeProperty(propID);
        }

        propIt->second->setAgentID(agentID);                          // Set new agent
        agentIt->second->assignProperty(propID);
        cout << "Agent assigned to property successfully.\n";
    }

    // -------------------- Transactions --------------------
    void recordSale() {                                              // Console sale recording
        cout << "\n--- Record Sale Transaction ---\n";
        int propID, clientID, agentID;
        double salePrice;

        cout << "Property ID: ";
        cin >> propID;
        cout << "Buyer Client ID: ";
        cin >> clientID;
        cout << "Agent ID (0 if none): ";
        cin >> agentID;
        cout << "Sale amount: $";
        cin >> salePrice;
        cin.ignore();

        auto propIt = propertyMap.find(propID);
        if (propIt == propertyMap.end()) {
            cout << "Property not found.\n";
            return;
        }
        if (propIt->second->getStatus() != PropertyStatus::AVAILABLE) {
            cout << "Property is not available for sale.\n";
            return;
        }
        auto clientIt = clientMap.find(clientID);
        if (clientIt == clientMap.end()) {
            cout << "Client not found.\n";
            return;
        }
        shared_ptr<Agent> agent = nullptr;
        if (agentID != 0) {
            auto agentIt = agentMap.find(agentID);
            if (agentIt == agentMap.end()) {
                cout << "Agent not found.\n";
                return;
            }
            agent = agentIt->second;
        }

        double commission = 0.0;
        if (agent) {
            commission = salePrice * (agent->getCommissionRate() / 100.0);
        }

        int transID = IDGenerator::getNextTransactionID();
        string date = getCurrentDate();
        int ownerID = propIt->second->getOwnerID();
        auto trans = make_shared<Transaction>(
            transID, TransactionType::SALE, propID, clientID, ownerID, agentID,
            salePrice, commission, date
        );
        transactions.push_back(trans);
        transactionMap[transID] = trans;

        propIt->second->setStatus(PropertyStatus::SOLD);
        propIt->second->setOwnerID(clientID);                        // Transfer ownership to buyer
        clientIt->second->addTransaction(transID);

        auto ownerIt = clientMap.find(ownerID);
        if (ownerIt != clientMap.end()) {
            ownerIt->second->addTransaction(transID);
        }

        if (agent) agent->addSale(transID);

        int contractID = IDGenerator::getNextContractID();
        auto contract = make_shared<Contract>(
            contractID, transID, "Sale Contract", date, salePrice,
            propID, clientID, agentID
        );
        contracts.push_back(contract);
        contractMap[contractID] = contract;

        cout << "Sale recorded. Transaction ID: " << transID << "\n";
        cout << "Contract ID: " << contractID << " generated.\n";
    }

    void recordRental() {                                            // Console rental recording
        cout << "\n--- Record Rental Transaction ---\n";
        int propID, clientID, agentID, durationMonths;
        double rentAmount;

        cout << "Property ID: ";
        cin >> propID;
        cout << "Renter Client ID: ";
        cin >> clientID;
        cout << "Agent ID (0 if none): ";
        cin >> agentID;
        cout << "Rent amount: $";
        cin >> rentAmount;
        cout << "Rental duration (months): ";
        cin >> durationMonths;
        cin.ignore();

        auto propIt = propertyMap.find(propID);
        if (propIt == propertyMap.end()) {
            cout << "Property not found.\n";
            return;
        }
        if (propIt->second->getStatus() != PropertyStatus::AVAILABLE) {
            cout << "Property is not available for rent.\n";
            return;
        }
        auto clientIt = clientMap.find(clientID);
        if (clientIt == clientMap.end()) {
            cout << "Client not found.\n";
            return;
        }
        shared_ptr<Agent> agent = nullptr;
        if (agentID != 0) {
            auto agentIt = agentMap.find(agentID);
            if (agentIt == agentMap.end()) {
                cout << "Agent not found.\n";
                return;
            }
            agent = agentIt->second;
        }

        double commission = 0.0;
        if (agent) {
            commission = rentAmount * (agent->getCommissionRate() / 100.0);
        }

        int transID = IDGenerator::getNextTransactionID();
        string date = getCurrentDate();
        int ownerID = propIt->second->getOwnerID();
        auto trans = make_shared<Transaction>(
            transID, TransactionType::RENTAL, propID, clientID, ownerID, agentID,
            rentAmount, commission, date
        );
        transactions.push_back(trans);
        transactionMap[transID] = trans;

        propIt->second->setStatus(PropertyStatus::RENTED);
        clientIt->second->addTransaction(transID);

        auto ownerIt = clientMap.find(ownerID);
        if (ownerIt != clientMap.end()) {
            ownerIt->second->addTransaction(transID);
        }

        if (agent) agent->addSale(transID);

        int contractID = IDGenerator::getNextContractID();
        auto contract = make_shared<Contract>(
            contractID, transID, "Rental Contract", date, rentAmount,
            propID, clientID, agentID, durationMonths
        );
        contracts.push_back(contract);
        contractMap[contractID] = contract;

        cout << "Rental recorded. Transaction ID: " << transID << "\n";
        cout << "Contract ID: " << contractID << " generated for " << durationMonths << " months.\n";
    }

    void listTransactions() {                                        // List all transactions
        cout << "\n--- All Transactions ---\n";
        if (transactions.empty()) {
            cout << "No transactions recorded.\n";
            return;
        }
        for (const auto& t : transactions) {
            cout << *t << "\n";
        }
    }

    // -------------------- Contract Management --------------------
    void viewContract() {                                            // Console contract view
        cout << "\n--- View Contract ---\n";
        int id;
        cout << "Enter Contract ID: ";
        cin >> id;
        cin.ignore();

        auto it = contractMap.find(id);
        if (it == contractMap.end()) {
            cout << "Contract not found.\n";
            return;
        }
        it->second->displayFull(propertyMap, clientMap, agentMap);   // Full display with entity details
    }

    void listAllContracts() {                                        // List all contracts overview
        cout << "\n--- All Contracts ---\n";
        if (contracts.empty()) {
            cout << "No contracts found.\n";
            return;
        }
        for (const auto& c : contracts) {
            cout << *c << "\n\n";                                     // Print each contract summary
        }
    }

    // -------------------- File I/O --------------------
    // Save all data to text files.
    void saveData() {                                                // Persist all data to disk
        ofstream propFile("properties.txt"), clientFile("clients.txt"),
            agentFile("agents.txt"), transFile("transactions.txt"),
            contractFile("contracts.txt");                          // Open all data files

        if (!propFile || !clientFile || !agentFile || !transFile || !contractFile) {
            cerr << "Error opening files for writing.\n";           // Could not create files
            return;
        }

        // Save properties.
        for (const auto& p : properties) {                           // Write each property
            propFile << p->getID() << "|" << p->getAddress() << "|" << p->getCity()
                << "|" << static_cast<int>(p->getType()) << "|" << p->getArea()
                << "|" << p->getRooms() << "|" << p->getPrice() << "|"
                << p->getOwnerID() << "|" << p->getAgentID() << "|"
                << static_cast<int>(p->getStatus()) << "\n";         // Pipe-delimited line
        }

        // Save clients with preferences.
        for (const auto& c : clients) {
            clientFile << c->getID() << "|" << c->getName() << "|" << c->getContactInfo()
                << "|" << static_cast<int>(c->getType())
                << "|" << c->getBudgetMin() << "|" << c->getBudgetMax()
                << "|" << c->getPreferredCity()
                << "|" << static_cast<int>(c->getPreferredType())
                << "|" << c->getMinArea() << "|" << c->getMaxArea()
                << "|" << c->getMinRooms() << "|" << c->getMaxRooms()
                << "|" << (c->preferencesSet() ? "1" : "0") << "\n"; // Include preferences flag
        }

        // Save agents.
        for (const auto& a : agents) {
            agentFile << a->getID() << "|" << a->getName() << "|" << a->getContactInfo()
                << "|" << a->getCommissionRate() << "\n";           // Simple format
        }

        // Save transactions (note: ownerID stored).
        for (const auto& t : transactions) {
            transFile << t->getID() << "|" << static_cast<int>(t->getType())
                << "|" << t->getPropertyID() << "|" << t->getClientID()
                << "|" << t->getOwnerID() << "|" << t->getAgentID() << "|" << t->getAmount()
                << "|" << t->getCommission() << "|" << t->getDate() << "\n";
        }

        // Save contracts.
        for (const auto& c : contracts) {
            contractFile << c->getID() << "|" << c->getTransactionID() << "|"
                << c->getContractType() << "|" << c->getDate() << "|"
                << c->getAmount() << "|" << c->getPropertyID() << "|"
                << c->getClientID() << "|" << c->getAgentID() << "|"
                << c->getDurationMonths() << "\n";
        }

        saveUsers();                                                 // Also save user credentials
        cout << "Data saved successfully.\n";
    }

    // Load all data from text files, rebuilding maps and relationships.
    void loadData() {                                                // Restore all data from disk
        loadUsers();                                                 // Load users first

        // Clear existing data to avoid duplicates.
        properties.clear();                                          // Empty property vector
        propertyMap.clear();                                         // Clear property map
        clients.clear();                                             // Clear clients
        clientMap.clear();                                           // etc.
        agents.clear();
        agentMap.clear();
        transactions.clear();
        transactionMap.clear();
        contracts.clear();
        contractMap.clear();

        try {
            // Load properties.
            ifstream propFile("properties.txt");
            if (propFile.is_open()) {
                string line;
                while (getline(propFile, line)) {                    // Read each line
                    stringstream ss(line);
                    string token;
                    vector<string> tokens;
                    while (getline(ss, token, '|')) tokens.push_back(token); // Split by '|'
                    if (tokens.size() >= 10) {                       // Need at least 10 fields
                        int id, typeInt, rooms, ownerID, agentID, statusInt;
                        double area, price;
                        if (!safeStoi(tokens[0], id) || !safeStoi(tokens[3], typeInt) ||
                            !safeStod(tokens[4], area) || !safeStoi(tokens[5], rooms) ||
                            !safeStod(tokens[6], price) || !safeStoi(tokens[7], ownerID) ||
                            !safeStoi(tokens[8], agentID) || !safeStoi(tokens[9], statusInt)) {
                            continue; // Skip malformed lines.
                        }
                        string addr = tokens[1], city = tokens[2];
                        PropertyType type = static_cast<PropertyType>(typeInt);
                        PropertyStatus status = static_cast<PropertyStatus>(statusInt);

                        shared_ptr<Property> prop;
                        switch (type) {                              // Create appropriate derived object
                        case PropertyType::APARTMENT: prop = make_shared<Apartment>(id, addr, city, area, rooms, price, ownerID); break;
                        case PropertyType::VILLA:     prop = make_shared<Villa>(id, addr, city, area, rooms, price, ownerID);     break;
                        case PropertyType::OFFICE:    prop = make_shared<Office>(id, addr, city, area, rooms, price, ownerID);    break;
                        case PropertyType::LAND:      prop = make_shared<Land>(id, addr, city, area, price, ownerID);            break;
                        }
                        if (prop) {
                            prop->setAgentID(agentID);               // Restore agent
                            prop->setStatus(status);                 // Restore status
                            properties.push_back(prop);
                            propertyMap[id] = prop;
                            IDGenerator::markUsedID(id);             // Register ID
                        }
                    }
                }
                propFile.close();
            }

            // Load clients.
            ifstream clientFile("clients.txt");
            if (clientFile.is_open()) {
                string line;
                while (getline(clientFile, line)) {
                    stringstream ss(line);
                    string token;
                    vector<string> tokens;
                    while (getline(ss, token, '|')) tokens.push_back(token);
                    if (tokens.size() >= 13) {                       // 13 fields
                        int id, typeInt, prefTypeInt, minRooms, maxRooms, prefSetInt;
                        double budgetMin, budgetMax, minArea, maxArea;
                        if (!safeStoi(tokens[0], id) || !safeStoi(tokens[3], typeInt) ||
                            !safeStod(tokens[4], budgetMin) || !safeStod(tokens[5], budgetMax) ||
                            !safeStoi(tokens[7], prefTypeInt) ||
                            !safeStod(tokens[8], minArea) || !safeStod(tokens[9], maxArea) ||
                            !safeStoi(tokens[10], minRooms) || !safeStoi(tokens[11], maxRooms) ||
                            !safeStoi(tokens[12], prefSetInt)) {
                            continue;
                        }
                        string name = tokens[1], contact = tokens[2], prefCity = tokens[6];
                        auto client = make_shared<Client>(id, name, contact, static_cast<ClientType>(typeInt));
                        if (prefSetInt) {                            // Restore preferences if flag set
                            client->setBudget(budgetMin, budgetMax);
                            client->setPreferredCity(prefCity);
                            client->setPreferredType(static_cast<PropertyType>(prefTypeInt));
                            client->setAreaRange(minArea, maxArea);
                            client->setRoomsRange(minRooms, maxRooms);
                        }
                        clients.push_back(client);
                        clientMap[id] = client;
                        IDGenerator::markUsedID(id);
                    }
                }
                clientFile.close();
            }

            // Load agents.
            ifstream agentFile("agents.txt");
            if (agentFile.is_open()) {
                string line;
                while (getline(agentFile, line)) {
                    stringstream ss(line);
                    string token;
                    vector<string> tokens;
                    while (getline(ss, token, '|')) tokens.push_back(token);
                    if (tokens.size() >= 4) {
                        int id; double comm;
                        if (!safeStoi(tokens[0], id) || !safeStod(tokens[3], comm)) continue;
                        auto agent = make_shared<Agent>(id, tokens[1], tokens[2], comm);
                        agents.push_back(agent);
                        agentMap[id] = agent;
                        IDGenerator::markUsedID(id);
                    }
                }
                agentFile.close();
            }

            // Load transactions.
            ifstream transFile("transactions.txt");
            if (transFile.is_open()) {
                string line;
                while (getline(transFile, line)) {
                    stringstream ss(line);
                    string token;
                    vector<string> tokens;
                    while (getline(ss, token, '|')) tokens.push_back(token);
                    if (tokens.size() >= 8) {
                        int id, typeInt, propID, clientID, ownerID = 0, agentID;
                        double amount, comm;
                        if (tokens.size() >= 9) {
                            if (!safeStoi(tokens[0], id) || !safeStoi(tokens[1], typeInt) || !safeStoi(tokens[2], propID) ||
                                !safeStoi(tokens[3], clientID) || !safeStoi(tokens[4], ownerID) || !safeStoi(tokens[5], agentID) ||
                                !safeStod(tokens[6], amount) || !safeStod(tokens[7], comm)) continue;
                            auto trans = make_shared<Transaction>(id, static_cast<TransactionType>(typeInt), propID, clientID, ownerID, agentID, amount, comm, tokens[8]);
                            transactions.push_back(trans);
                            transactionMap[id] = trans;
                            IDGenerator::markUsedID(id);
                        }
                    }
                }
                transFile.close();
            }

            // Load contracts.
            ifstream contractFile("contracts.txt");
            if (contractFile.is_open()) {
                string line;
                while (getline(contractFile, line)) {
                    stringstream ss(line);
                    string token;
                    vector<string> tokens;
                    while (getline(ss, token, '|')) tokens.push_back(token);
                    if (tokens.size() >= 8) {
                        int id, transID, propID, clientID, agentID, duration = 0;
                        double amount;
                        if (!safeStoi(tokens[0], id) || !safeStoi(tokens[1], transID) || !safeStod(tokens[4], amount) ||
                            !safeStoi(tokens[5], propID) || !safeStoi(tokens[6], clientID) || !safeStoi(tokens[7], agentID)) continue;
                        if (tokens.size() >= 9) safeStoi(tokens[8], duration); // Duration if provided
                        auto contract = make_shared<Contract>(id, transID, tokens[2], tokens[3], amount, propID, clientID, agentID, duration);
                        contracts.push_back(contract);
                        contractMap[id] = contract;
                        IDGenerator::markUsedID(id);
                    }
                }
                contractFile.close();
            }

            // Restore Relationships: assign agents to properties, link transactions to clients/agents.
            int maxPropID = 0, maxPersonID = 0, maxTransID = 0, maxContractID = 0;
            for (const auto& p : properties) {
                maxPropID = max(maxPropID, p->getID());              // Track max property ID
                if (p->getAgentID() != 0 && agentMap.count(p->getAgentID()))
                    agentMap[p->getAgentID()]->assignProperty(p->getID()); // Restore agent–property link
            }
            for (const auto& c : clients) maxPersonID = max(maxPersonID, c->getID()); // Track max person ID
            for (const auto& a : agents)  maxPersonID = max(maxPersonID, a->getID()); // Person IDs shared
            for (const auto& t : transactions) {
                maxTransID = max(maxTransID, t->getID());            // Track max transaction ID
                if (clientMap.count(t->getClientID())) clientMap[t->getClientID()]->addTransaction(t->getID()); // Link to buyer
                if (clientMap.count(t->getOwnerID()))  clientMap[t->getOwnerID()]->addTransaction(t->getID());  // Link to seller
                if (agentMap.count(t->getAgentID()))   agentMap[t->getAgentID()]->addSale(t->getID());          // Link to agent
            }
            for (const auto& c : contracts) maxContractID = max(maxContractID, c->getID()); // Track max contract ID

            // Set ID generators to avoid reusing loaded IDs.
            IDGenerator::setPropertyIDStart(maxPropID);
            IDGenerator::setPersonIDStart(maxPersonID);
            IDGenerator::setTransactionIDStart(maxTransID);
            IDGenerator::setContractIDStart(maxContractID);

            cout << "Data loaded successfully.\n";
        }
        catch (const exception& e) {
            cerr << "Critical error during data load: " << e.what() << "\n"; // Fatal error
        }
    }

    // --- Operator Overloads for Agency ---
    // += operator to add a property easily.
    RealEstateAgency& operator+=(const shared_ptr<Property>& prop) { // Quick property addition
        if (prop) {
            int id = prop->getID();
            properties.push_back(prop);                              // Add to vector
            propertyMap[id] = prop;                                  // Add to map
        }
        return *this;                                                // Return reference to allow chaining
    }

    // Subscript operator to access property by ID (returns reference to shared_ptr).
    shared_ptr<Property>& operator[](int id) {                       // Non-const property access by ID
        static shared_ptr<Property> nullPtr = nullptr;               // Static null to return for missing IDs
        auto it = propertyMap.find(id);
        if (it != propertyMap.end())
            return it->second;                                       // Return the shared_ptr from map
        return nullPtr;                                              // Return null if not found
    }

    // Const version of subscript operator.
    const shared_ptr<Property>& operator[](int id) const {           // Const version
        static shared_ptr<Property> nullPtr = nullptr;
        auto it = propertyMap.find(id);
        if (it != propertyMap.end())
            return it->second;
        return nullPtr;
    }
};

// -------------------- ReportGenerator Class --------------------
// Helper class to compute statistics from agency data.
class ReportGenerator {
public:
    // Structure to hold aggregated statistics.
    struct AgencyStats {
        int totalProperties = 0;
        int soldProperties = 0;
        int rentedProperties = 0;
        int availableProperties = 0;
        double totalProfit = 0.0;                       // Sum of all commissions.
        map<int, double> agentSales;                    // Agent ID -> total sales amount.
        map<int, int> agentDealCount;                   // Agent ID -> number of deals.
    };

    // Static method that computes stats from a given agency instance.
    static AgencyStats generateStats(const RealEstateAgency& agency) { // Compute statistics
        AgencyStats stats;
        stats.totalProperties = static_cast<int>(agency.properties.size()); // Total properties
        // Count properties by status.
        for (const auto& p : agency.properties) {
            if (p->getStatus() == PropertyStatus::SOLD) stats.soldProperties++;      // Sold count
            else if (p->getStatus() == PropertyStatus::RENTED) stats.rentedProperties++; // Rented count
            else stats.availableProperties++;                                         // Available count
        }

        // Sum commissions and aggregate per-agent.
        for (const auto& t : agency.transactions) {
            stats.totalProfit += t->getCommission();                 // Add commission
            if (t->getAgentID() != 0) {
                stats.agentSales[t->getAgentID()] += t->getAmount(); // Accumulate agent sales amount
                stats.agentDealCount[t->getAgentID()]++;             // Increment deal count
            }
        }
        return stats;                                                // Return the computed statistics
    }
};

// -------------------- Main Menu (now using GUI) --------------------
// Include the GUI implementation (separate header/source).
#include "Gui.h"                                                     // ImGui-based user interface definition

// -------------------- DX11 Boilerplate --------------------
// Global pointers for Direct3D 11 device and swap chain.
static ID3D11Device* g_pd3dDevice = nullptr;                        // D3D11 device
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;           // Immediate device context
static IDXGISwapChain* g_pSwapChain = nullptr;                       // Swap chain
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0; // Pending resize dimensions
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;     // Main render target view

// Function to create D3D11 device and swap chain.
bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain description.
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));                                     // Clear the struct
    sd.BufferCount = 2;                                              // Double buffering
    sd.BufferDesc.Width = 0;                                         // Use window width
    sd.BufferDesc.Height = 0;                                        // Use window height
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;               // 32-bit color format
    sd.BufferDesc.RefreshRate.Numerator = 60;                        // 60 Hz refresh rate
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;               // Allow mode switching
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                // Render target usage
    sd.OutputWindow = hWnd;                                          // Window handle
    sd.SampleDesc.Count = 1;                                         // No anti-aliasing
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;                                              // Windowed mode
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                        // Discard back buffer after present

    UINT createDeviceFlags = 0;                                      // No debug flags by default
    D3D_FEATURE_LEVEL featureLevel;                                  // To store selected feature level
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    // Try to create device with hardware driver, fallback to WARP if unsupported.
    HRESULT res = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
        featureLevelArray, 2, D3D11_SDK_VERSION, &sd,
        &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)                               // If hardware not supported, try WARP (software).
        res = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags,
            featureLevelArray, 2, D3D11_SDK_VERSION, &sd,
            &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;                                                // Failed to create device.

    // Obtain the back buffer and create a render target view.
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));          // Get back buffer texture
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView); // Create RTV
    pBackBuffer->Release();                                          // Release the temporary texture
    return true;
}

// Clean up D3D11 resources.
void CleanupDeviceD3D()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; } // Release RTV
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }                             // Release swap chain
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }         // Release device context
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }                             // Release device
}

// Create render target from swap chain back buffer (used during resize).
void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));          // Get back buffer
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView); // Create RTV
    pBackBuffer->Release();
}

// Release the current render target (must be done before resize).
void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; } // Release RTV
}

// Forward declare ImGui's Win32 message handler (implemented in imgui_impl_win32.cpp).
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // ImGui message handler

// Window procedure for Win32 messages.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Let ImGui process the message first. If it consumes it, return true.
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;                                                 // ImGui handled the message

    switch (msg)
    {
    case WM_SIZE:                                                    // Window resized
        if (g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED)
        {
            // Release old render target, resize swap chain buffers, and recreate.
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0); // Resize buffers
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        // Prevent ALT keys from activating the menu (we want to handle them via ImGui).
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;                                                // Suppress system menu activation
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);                                        // Signal application to exit
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);              // Default processing for other messages
}

// -------------------- Main ImGui Loop --------------------
int main(int, char**) {                                              // Application entry point
    // Register window class for the main window.
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L,
        GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
        L"RealEstateApp", nullptr };                                 // Fill window class with default values
    ::RegisterClassExW(&wc);                                         // Register class
    // Create the main window.
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Real Estate Agency GUI",
        WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr); // Create window

    // Initialize Direct3D.
    if (!CreateDeviceD3D(hwnd))                                      // Attempt to create D3D device
    {
        CleanupDeviceD3D();                                          // Cleanup if creation fails
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window.
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);                              // Display window
    ::UpdateWindow(hwnd);                                            // Force a paint

    // Setup Dear ImGui context.
    IMGUI_CHECKVERSION();                                            // Verify ImGui version matches headers
    ImGui::CreateContext();                                          // Create ImGui context
    ImGuiIO& io = ImGui::GetIO(); (void)io;                          // Retrieve IO object (and silence unused warning)
    // Enable keyboard navigation.
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;            // Allow keyboard control

    // Setup Dear ImGui style (dark theme).
    ImGui::StyleColorsDark();                                        // Use dark color scheme

    // Initialize platform/renderer backends.
    ImGui_ImplWin32_Init(hwnd);                                      // Initialize Win32 backend
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);          // Initialize D3D11 backend

    // Create core application logic.
    RealEstateAgency agency;                                         // Instantiate the core agency
    AppGUI gui(agency);                                              // Create the GUI wrapper (defined in Gui.h)

    bool done = false;                                               // Main loop control flag
    // Main application loop.
    while (!done)
    {
        // Poll and handle messages (exit if WM_QUIT).
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))     // Check for window messages
        {
            ::TranslateMessage(&msg);                                // Translate virtual-key messages
            ::DispatchMessage(&msg);                                 // Dispatch to window procedure
            if (msg.message == WM_QUIT)
                done = true;                                         // WM_QUIT received → exit loop
        }
        if (done)
            break;

        // Handle any pending resize.
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)               // Resize event pending?
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0); // Resize swap chain
            g_ResizeWidth = g_ResizeHeight = 0;                      // Reset pending values
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame.
        ImGui_ImplDX11_NewFrame();                                   // Start a new D3D11 frame
        ImGui_ImplWin32_NewFrame();                                  // Start a new Win32 frame
        ImGui::NewFrame();                                           // Start ImGui frame (prepares widgets)

        // Render the GUI (all widgets).
        gui.Render();                                                // Call our application's GUI drawing code

        // Render ImGui draw data.
        ImGui::Render();                                             // Generate draw data for this frame
        const float clear_color_with_alpha[4] = { 0.15f, 0.15f, 0.15f, 1.00f }; // Dark grey background
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr); // Set render target
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha); // Clear background
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());         // Submit draw commands

        // Present the frame with vsync (1 = wait for vertical blank).
        g_pSwapChain->Present(1, 0);                                 // Swap buffers with vsync
    }

    // Save data before exiting.
    agency.saveData();                                               // Persist all data to files

    // Cleanup all ImGui and D3D resources.
    ImGui_ImplDX11_Shutdown();                                       // Shutdown D3D11 backend
    ImGui_ImplWin32_Shutdown();                                      // Shutdown Win32 backend
    ImGui::DestroyContext();                                         // Destroy ImGui context

    CleanupDeviceD3D();                                              // Release D3D objects
    ::DestroyWindow(hwnd);                                           // Destroy the main window
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);              // Unregister the window class

    return 0;                                                        // Exit normally
}