// Electronics Store Management System
// Generate bills,
// Load inventory,
// Add offers,
// Add loyalty offers,
// Add employee data,
// Products details

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BILLING ---------------------------------------------

struct Bill {
    int billNumber;
    char customerName[50];
    char phoneNumber[15];
    int quantity;
    float amount;
};

// Function to create a new bill
void createBill(struct Bill *bills, int *billCount) {
    struct Bill newBill;
    
    // Initialize bill details
    newBill.billNumber = (*billCount) + 1;
    printf("Enter customer name: ");
    scanf("%s", newBill.customerName);
    printf("Enter phone number: ");
    scanf("%s", newBill.phoneNumber);
    printf("Enter quantity: ");
    scanf("%d", &newBill.quantity);
    printf("Enter amount: ");
    scanf("%f", &newBill.amount);
    
    // Save the bill to the structure
    bills[*billCount] = newBill;
    (*billCount)++;
    
    // Save the bill to the file
    FILE *file = fopen("bills.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d %s %s %d %.2f\n", newBill.billNumber, newBill.customerName, newBill.phoneNumber, newBill.quantity, newBill.amount);
        fclose(file);
        printf("Bill created successfully.\n");
    } else {
        printf("Error: Unable to open file for saving.\n");
    }
}

// Function to edit a bill
void editBill(struct Bill *bills, int billCount) {
    int billNumber;
    printf("Enter the bill number to edit: ");
    scanf("%d", &billNumber);
    
    int found = 0;
    for (int i = 0; i < billCount; i++) {
        if (bills[i].billNumber == billNumber) {
            printf("Enter new customer name: ");
            scanf("%s", bills[i].customerName);
            printf("Enter new phone number: ");
            scanf("%s", bills[i].phoneNumber);
            printf("Enter new quantity: ");
            scanf("%d", &bills[i].quantity);
            printf("Enter new amount: ");
            scanf("%f", &bills[i].amount);
            found = 1;
            
            // Update the file
            FILE *file = fopen("bills.txt", "w");
            if (file != NULL) {
                for (int j = 0; j < billCount; j++) {
                    fprintf(file, "%d %s %s %d %.2f\n", bills[j].billNumber, bills[j].customerName, bills[j].phoneNumber, bills[j].quantity, bills[j].amount);
                }
                fclose(file);
                printf("Bill edited successfully.\n");
            } else {
                printf("Error: Unable to open file for editing.\n");
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Bill not found.\n");
    }
}

// Function to delete a bill
void deleteBill(struct Bill *bills, int *billCount) {
    int billNumber;
    printf("Enter the bill number to delete: ");
    scanf("%d", &billNumber);
    
    int found = 0;
    for (int i = 0; i < *billCount; i++) {
        if (bills[i].billNumber == billNumber) {
            found = 1;
            // Delete the bill by shifting remaining bills
            for (int j = i; j < (*billCount) - 1; j++) {
                bills[j] = bills[j + 1];
            }
            (*billCount)--;
            
            // Update the file
            FILE *file = fopen("bills.txt", "w");
            if (file != NULL) {
                for (int j = 0; j < *billCount; j++) {
                    fprintf(file, "%d %s %s %d %.2f\n", bills[j].billNumber, bills[j].customerName, bills[j].phoneNumber, bills[j].quantity, bills[j].amount);
                }
                fclose(file);
                printf("Bill deleted successfully.\n");
            } else {
                printf("Error: Unable to open file for deletion.\n");
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Bill not found.\n");
    }
}

// Function to search for a bill
void searchBill(struct Bill *bills, int billCount) {
    int billNumber;
    printf("Enter the bill number to search: ");
    scanf("%d", &billNumber);
    
    int found = 0;
    for (int i = 0; i < billCount; i++) {
        if (bills[i].billNumber == billNumber) {
            printf("Bill Number: %d\n", bills[i].billNumber);
            printf("Customer Name: %s\n", bills[i].customerName);
            printf("Phone Number: %s\n", bills[i].phoneNumber);
            printf("Quantity: %d\n", bills[i].quantity);
            printf("Amount: %.2f\n", bills[i].amount);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Bill not found.\n");
    }
}

// Function to retrieve data from the file
void retrieveData(struct Bill *bills, int *billCount) {
    FILE *file = fopen("bills.txt", "r");
    if (file != NULL) {
        while (!feof(file)) {
            struct Bill newBill;
            fscanf(file, "%d %s %s %d %f", &newBill.billNumber, newBill.customerName, newBill.phoneNumber, &newBill.quantity, &newBill.amount);
            if (!feof(file)) {
                bills[*billCount] = newBill;
                (*billCount)++;
            }
        }
        fclose(file);
        printf("Data retrieved successfully.\n");
    } else {
        printf("Error: Unable to open file for retrieval.\n");
    }
}

// ------------------------------------------------------

// INVENTORY -------------------------------------------
#define MAX_PRODUCTS 100

// Structure to represent a product
struct Product {
    char name[100];
    int id;
    float price;
    int quantity;
};

// Global variables for products and product count
struct Product inventory[MAX_PRODUCTS];
int productCount = 0;

// Function to save products to a file
void saveProductsToFile() {
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%s %d %.2f %d\n", inventory[i].name, inventory[i].id, inventory[i].price, inventory[i].quantity);
    }

    fclose(file);
    printf("Inventory saved to file successfully.\n");
}

// Function to load products from a file
void loadProductsFromFile() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No inventory file found.\n");
        return;
    }

    productCount = 0;

    while (fscanf(file, "%s %d %f %d", inventory[productCount].name, &inventory[productCount].id,
                  &inventory[productCount].price, &inventory[productCount].quantity) == 4) {
        productCount++;
    }

    fclose(file);
    printf("Inventory loaded from file successfully.\n");
}

// Function to add a new product
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }

    struct Product newProduct;
    printf("Enter product name: ");
    scanf("%s", newProduct.name);
    printf("Enter product ID: ");
    scanf("%d", &newProduct.id);
    printf("Enter product price: ");
    scanf("%f", &newProduct.price);
    printf("Enter product quantity: ");
    scanf("%d", &newProduct.quantity);

    inventory[productCount] = newProduct;
    productCount++;

    printf("Product added successfully.\n");
    saveProductsToFile(); // Save the updated inventory to the file
}

// Function to view product details
void viewProduct() {
    if (productCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    int searchId;
    printf("Enter product ID to view: ");
    scanf("%d", &searchId);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == searchId) {
            printf("Product details:\n");
            printf("Name: %s\n", inventory[i].name);
            printf("ID: %d\n", inventory[i].id);
            printf("Price: %.2f\n", inventory[i].price);
            printf("Quantity: %d\n", inventory[i].quantity);
            return;
        }
    }

    printf("Product with ID %d not found.\n", searchId);
}

// Function to edit product details
void editProduct() {
    if (productCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    int editId;
    printf("Enter product ID to edit: ");
    scanf("%d", &editId);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == editId) {
            printf("Enter new product name: ");
            scanf("%s", inventory[i].name);
            printf("Enter new product price: ");
            scanf("%f", &inventory[i].price);
            printf("Enter new product quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Product edited successfully.\n");
            saveProductsToFile(); // Save the updated inventory to the file
            return;
        }
    }

    printf("Product with ID %d not found.\n", editId);
}

// Function to delete a product
void deleteProduct() {
    if (productCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    int deleteId;
    printf("Enter product ID to delete: ");
    scanf("%d", &deleteId);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == deleteId) {
            for (int j = i; j < productCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            productCount--;
            printf("Product deleted successfully.\n");
            saveProductsToFile(); // Save the updated inventory to the file
            return;
        }
    }

    printf("Product with ID %d not found.\n", deleteId);
}

// Function to view the entire inventory
void viewInventory() {
    if (productCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("Listing all products in the inventory:\n");
    for (int i = 0; i < productCount; i++) {
        printf("Product ID: %d\n", inventory[i].id);
        printf("Name: %s\n", inventory[i].name);
        printf("Price: %.2f\n", inventory[i].price);
        printf("Quantity: %d\n", inventory[i].quantity);
        printf("---------------------------\n");
    }
}

// -----------------------------------------------------------------------------

// DISCOUNT -------------------------------------------

#define MAX_OFFERS 100

// Structure to represent an offer
struct Offer
{
    char name[100];
    int id;
    float discount;
    char category[50];
};

struct Offer offers[MAX_OFFERS];
int offerCount = 0;

// Function to add a new offer
void addOffer()
{
    if (offerCount >= MAX_OFFERS)
    {
        printf("Maximum number of offers reached. Cannot add more offers.\n");
        return;
    }

    struct Offer newOffer;
    printf("Enter offer name: ");
    scanf("%s", newOffer.name);
    printf("Enter offer ID: ");
    scanf("%d", &newOffer.id);
    printf("Enter offer discount (in percentage): ");
    scanf("%f", &newOffer.discount);
    printf("Enter discount category: ");
    scanf("%s", newOffer.category);

    offers[offerCount] = newOffer;
    offerCount++;

    printf("Offer added successfully.\n");
}

// Function to display discount categories
void displayCategories()
{
    if (offerCount == 0)
    {
        printf("No offers available.\n");
        return;
    }

    printf("Discount Categories:\n");
    for (int i = 0; i < offerCount; i++)
    {
        int categoryExists = 0;
        for (int j = 0; j < i; j++)
        {
            if (strcmp(offers[i].category, offers[j].category) == 0)
            {
                categoryExists = 1;
                break;
            }
        }
        if (!categoryExists)
        {
            printf("%s\n", offers[i].category);
        }
    }
}

// Function to update an offer
void updateOffer()
{
    if (offerCount == 0)
    {
        printf("No offers available.\n");
        return;
    }

    int updateID;
    printf("Enter offer ID to update: ");
    scanf("%d", &updateID);

    for (int i = 0; i < offerCount; i++)
    {
        if (offers[i].id == updateID)
        {
            printf("Enter new offer name: ");
            scanf("%s", offers[i].name);
            printf("Enter new offer discount (in percentage): ");
            scanf("%f", &offers[i].discount);
            printf("Enter new discount category: ");
            scanf("%s", offers[i].category);
            printf("Offer updated successfully.\n");
            return;
        }
    }

    printf("Offer with ID %d not found.\n", updateID);
}

// Function to delete an offer
void deleteOffer()
{
    if (offerCount == 0)
    {
        printf("No offers available.\n");
        return;
    }

    int deleteID;
    printf("Enter offer ID to delete: ");
    scanf("%d", &deleteID);

    for (int i = 0; i < offerCount; i++)
    {
        if (offers[i].id == deleteID)
        {
            for (int j = i; j < offerCount - 1; j++)
            {
                offers[j] = offers[j + 1];
            }
            offerCount--;
            printf("Offer deleted successfully.\n");
            return;
        }
    }

    printf("Offer with ID %d not found.\n", deleteID);
}

// Function to view all offers
void viewAllOffers()
{
    if (offerCount == 0)
    {
        printf("No offers available.\n");
        return;
    }

    printf("Listing all offers:\n");
    for (int i = 0; i < offerCount; i++)
    {
        printf("Offer ID: %d\n", offers[i].id);
        printf("Name: %s\n", offers[i].name);
        printf("Discount: %.2f%%\n", offers[i].discount);
        printf("Category: %s\n", offers[i].category);
        printf("---------------------------\n");
    }
}

// Function to save offers to a file
void saveOffersToFile()
{
    if (offerCount == 0)
    {
        printf("No offers available.\n");
        return;
    }

    FILE *file = fopen("offers.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < offerCount; i++)
    {
        fprintf(file, "%s %d %f %s\n", offers[i].name, offers[i].id, offers[i].discount, offers[i].category);
    }

    fclose(file);
    printf("Offers saved to file successfully.\n");
}

// Function to load offers from a file
void loadOffersFromFile()
{
    FILE *file = fopen("offers.txt", "r");
    if (file == NULL)
    {
        printf("No offers file found.\n");
        return;
    }

    offerCount = 0;

    while (fscanf(file, "%s %d %f %s", offers[offerCount].name, &offers[offerCount].id,
                  &offers[offerCount].discount, offers[offerCount].category) != EOF)
    {
        offerCount++;
    }

    fclose(file);
    printf("Offers loaded from file successfully.\n");
}

// --------------------------------------------------------------------------

// LOYALTY ---------------------------------------

struct Customer
{
    int id;
    char name[50];
};

struct LoyaltyOffer
{
    int id;
    char offerName[50];
    int loyaltyPointsRequired;
};

void enrollCustomer(struct Customer customers[], int *customerCount)
{
    printf("Enter customer ID: ");
    scanf("%d", &customers[*customerCount].id);
    printf("Enter customer name: ");
    scanf("%s", customers[*customerCount].name);
    (*customerCount)++;
    printf("Customer enrolled successfully!\n");
}

void removeCustomer(struct Customer customers[], int *customerCount)
{
    int idToRemove;
    printf("Enter customer ID to remove: ");
    scanf("%d", &idToRemove);

    for (int i = 0; i < *customerCount; i++)
    {
        if (customers[i].id == idToRemove)
        {
            // Shift all remaining customers to fill the gap
            for (int j = i; j < (*customerCount - 1); j++)
            {
                customers[j] = customers[j + 1];
            }
            (*customerCount)--;
            printf("Customer with ID %d removed successfully!\n", idToRemove);
            return;
        }
    }

    printf("Customer with ID %d not found!\n", idToRemove);
}

void viewAllCustomers(struct Customer customers[], int customerCount)
{
    printf("Customer List:\n");
    printf("ID\tName\n");
    for (int i = 0; i < customerCount; i++)
    {
        printf("%d\t%s\n", customers[i].id, customers[i].name);
    }
}

void addLoyaltyOffer(struct LoyaltyOffer offers[], int *offerCount)
{
    printf("Enter loyalty offer ID: ");
    scanf("%d", &offers[*offerCount].id);
    printf("Enter offer name: ");
    scanf("%s", offers[*offerCount].offerName);
    printf("Enter loyalty points required: ");
    scanf("%d", &offers[*offerCount].loyaltyPointsRequired);
    (*offerCount)++;
    printf("Loyalty offer added successfully!\n");
}

void viewLoyaltyOffers(struct LoyaltyOffer offers[], int offerCount)
{
    printf("Loyalty Offers:\n");
    printf("ID\tOffer Name\tLoyalty Points Required\n");
    for (int i = 0; i < offerCount; i++)
    {
        printf("%d\t%s\t\t%d\n", offers[i].id, offers[i].offerName, offers[i].loyaltyPointsRequired);
    }
}

void editLoyaltyOffer(struct LoyaltyOffer offers[], int offerCount)
{
    int idToEdit;
    printf("Enter loyalty offer ID to edit: ");
    scanf("%d", &idToEdit);

    for (int i = 0; i < offerCount; i++)
    {
        if (offers[i].id == idToEdit)
        {
            printf("Enter new offer name: ");
            scanf("%s", offers[i].offerName);
            printf("Enter new loyalty points required: ");
            scanf("%d", &offers[i].loyaltyPointsRequired);
            printf("Loyalty offer details updated successfully!\n");
            return;
        }
    }

    printf("Loyalty offer with ID %d not found!\n", idToEdit);
}

void deleteLoyaltyOffer(struct LoyaltyOffer offers[], int *offerCount)
{
    int idToDelete;
    printf("Enter loyalty offer ID to delete: ");
    scanf("%d", &idToDelete);

    for (int i = 0; i < *offerCount; i++)
    {
        if (offers[i].id == idToDelete)
        {
            // Shift all remaining offers to fill the gap
            for (int j = i; j < (*offerCount - 1); j++)
            {
                offers[j] = offers[j + 1];
            }
            (*offerCount)--;
            printf("Loyalty offer with ID %d deleted successfully!\n", idToDelete);
            return;
        }
    }

    printf("Loyalty offer with ID %d not found!\n", idToDelete);
}

// ----------------------------------------------------------------------------------

// EMPLOYEE -------------------------------------------

struct Employee {
    int id;
    char name[50];
    char department[50];
};


// Function to add an employee and save the details to a file
void addEmployee(struct Employee employees[], int *employeeCount, FILE *file) {
    printf("Enter employee ID: ");
    scanf("%d", &employees[*employeeCount].id);
    printf("Enter employee name: ");
    scanf("%s", employees[*employeeCount].name);
    printf("Enter employee department: ");
    scanf("%s", employees[*employeeCount].department);
    
    // Write employee details to the file
    fprintf(file, "%d %s %s\n", employees[*employeeCount].id, employees[*employeeCount].name, employees[*employeeCount].department);
    
    (*employeeCount)++;
    fflush(file); // Flush the output buffer to write data immediately
    printf("Employee added successfully!\n");
}

// Function to update employee details in the file
void updateEmployeeDetails(FILE *file, struct Employee employees[], int employeeCount) {
    int idToEdit;
    printf("Enter employee ID to edit: ");
    scanf("%d", &idToEdit);

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == idToEdit) {
            printf("Enter new name: ");
            scanf("%s", employees[i].name);
            printf("Enter new department: ");
            scanf("%s", employees[i].department);
            
            // Close the file and reopen it in write mode (truncate the file)
            fclose(file);
            file = fopen("employee.txt", "w");
            if (file == NULL) {
                perror("Error opening file");
                return;
            }

            // Write updated data to the file
            for (int j = 0; j < employeeCount; j++) {
                fprintf(file, "%d %s %s\n", employees[j].id, employees[j].name, employees[j].department);
            }

            fclose(file);
            printf("Employee details updated successfully!\n");
            return;
        }
    }

    printf("Employee with ID %d not found!\n", idToEdit);
}

// Function to delete an employee from the file
void deleteEmployee(FILE *file, struct Employee employees[], int *employeeCount) {
    int idToDelete;
    printf("Enter employee ID to delete: ");
    scanf("%d", &idToDelete);

    for (int i = 0; i < *employeeCount; i++) {
        if (employees[i].id == idToDelete) {
            // Shift all remaining employees to fill the gap
            for (int j = i; j < (*employeeCount - 1); j++) {
                employees[j] = employees[j + 1];
            }
            (*employeeCount)--;
            
            // Close the file and reopen it in write mode (truncate the file)
            fclose(file);
            file = fopen("employee.txt", "w");
            if (file == NULL) {
                perror("Error opening file");
                return;
            }

            // Write updated data to the file
            for (int j = 0; j < *employeeCount; j++) {
                fprintf(file, "%d %s %s\n", employees[j].id, employees[j].name, employees[j].department);
            }

            fclose(file);
            printf("Employee with ID %d deleted successfully!\n", idToDelete);
            return;
        }
    }

    printf("Employee with ID %d not found!\n", idToDelete);
}

void viewAllEmployees(struct Employee employees[], int employeeCount) {
    printf("Employee List:\n");
    printf("ID\tName\tDepartment\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("%d\t%s\t%s\n", employees[i].id, employees[i].name, employees[i].department);
    }
}

void searchEmployee(struct Employee employees[], int employeeCount) {
    int idToSearch;
    printf("Enter employee ID to search: ");
    scanf("%d", &idToSearch);

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == idToSearch) {
            printf("Employee Found:\n");
            printf("ID\tName\tDepartment\n");
            printf("%d\t%s\t%s\n", employees[i].id, employees[i].name, employees[i].department);
            return;
        }
    }

    printf("Employee with ID %d not found!\n", idToSearch);
}
// -----------------------------------------------------------------------------

int main()
{
    int choice, ch1, i, j, ch2, ch3, billCount;

    system("cls");
label:
    printf("Electronics Store Management System\n");
    printf("1) Bill Management\n2) Inventory Management\n3) Discount Management\n4) Loyalty Management\n5) Employee Management\n6) Exit \n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    system("cls");

    struct Bill bills[100];

    struct Customer customers[100];         // Assuming a maximum of 100 customers
    struct LoyaltyOffer loyaltyOffers[100]; // Assuming a maximum of 100 loyalty offers
    int customerCount = 0;
    int offerCount = 0;

    struct Employee employees[100]; // Assuming a maximum of 100 employees
    int employeeCount = 0;
    FILE *file;

    switch (choice)
    {
    case 1:
        // Bill Management

        billCount = 0;
    
        // Retrieve data from the file at program start
        retrieveData(bills, &billCount);
    
        int ch2;
        do {
            printf("\nBill Management:\n");
            printf("1. Create Bill\n");
            printf("2. Edit Bill\n");
            printf("3. Delete Bill\n");
            printf("4. Search Bill\n");
            printf("5. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &ch2);
        
            switch (ch2) {
                case 1:
                    createBill(bills, &billCount);
                    break;
                case 2:
                    editBill(bills, billCount);
                    break;
                case 3:
                    deleteBill(bills, &billCount);
                    break;
                case 4:
                    searchBill(bills, billCount);
                    break;
                case 5:
                    printf("Exiting the program.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        } while (ch2 != 5);

        goto label1;
        break;

    case 2:
        // Inventory Management

        // Load product data from the file at program start
        loadProductsFromFile();

        while (1) {
            printf("Inventory Management\n");
            printf("1) Add Product\n2) View Product\n3) Edit Product\n4) Delete Product\n5) View Inventory\n6) Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    viewProduct();
                    break;
                case 3:
                    editProduct();
                    break;
                case 4:
                    deleteProduct();
                    break;
                case 5:
                    viewInventory();
                    break;
                case 6:
                    // Save the product data to the file before exiting
                    saveProductsToFile();
                    printf("Exiting the program.\n");
                    return 0;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        }

        goto label1;
        break;

    case 3:
        // Discount Management

        loadOffersFromFile();

        while (1)
        {
            printf("\nDiscount Management System\n");
            printf("1) Add New Offer\n2) Discount Categories\n3) Update Offer\n4) Delete Offer\n5) View All Offers\n6) Save Offers to File\n7) Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                addOffer();
                break;

            case 2:
                displayCategories();
                break;

            case 3:
                updateOffer();
                break;

            case 4:
                deleteOffer();
                break;

            case 5:
                viewAllOffers();
                break;

            case 6:
                saveOffersToFile();
                break;

            case 7:
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
                break;
            }
        }

        goto label1;
        break;

    case 4:
        // Loyalty Management

        do
        {
            printf("\nLoyalty Management:");
            printf("\n1) Enroll Customers\n2) Remove Customer\n3) View all Customers\n4) Add loyalty offers\n5) View loyalty offer\n6) Edit loyalty offer\n7) Delete Loyalty Offer\n8)Exit \n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                enrollCustomer(customers, &customerCount);
                break;
            case 2:
                removeCustomer(customers, &customerCount);
                break;
            case 3:
                viewAllCustomers(customers, customerCount);
                break;
            case 4:
                addLoyaltyOffer(loyaltyOffers, &offerCount);
                break;
            case 5:
                viewLoyaltyOffers(loyaltyOffers, offerCount);
                break;
            case 6:
                editLoyaltyOffer(loyaltyOffers, offerCount);
                break;
            case 7:
                deleteLoyaltyOffer(loyaltyOffers, &offerCount);
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
            }
        } while (choice != 8);

        goto label1;
        break;

    case 5:
        // Employee Management

        file = fopen("employee.txt", "a+"); // Open the file for both appending and reading

        if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read employee details from the file and populate the employees array
    while (fscanf(file, "%d %s %s", &employees[employeeCount].id, employees[employeeCount].name, employees[employeeCount].department) == 3) {
        employeeCount++;
    }

         do {
        printf("\nEmployee Management System\n");
        printf("1) Add Employee\n");
        printf("2) Edit Employee details\n");
        printf("3) Delete Employee\n");
        printf("4) View all employees\n");
        printf("5) Search Employee\n");
        printf("6) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &employeeCount, file); // Pass the file pointer
                break;
            case 2:
                updateEmployeeDetails(file, employees, employeeCount);
                break;
            case 3:
                deleteEmployee(file, employees, &employeeCount);
                break;
            case 4:
                viewAllEmployees(employees, employeeCount);
                break;
            case 5:
                searchEmployee(employees, employeeCount);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 6);


        // Close the file when done
        fclose(file);

        goto label1;
        break;

    case 6:
        printf("Exiting the program.\n");
        break;

    default:
        printf("Invalid choice.\n");
        goto label1;
        break;
    }

label1:
    printf("If you want to go back to the dashboard, press 1.\n");
    scanf("%d", &ch1);
    system("cls");
    if (ch1 == 1)
        goto label;
    else
        printf("Exiting the program.");

    return 0;
}