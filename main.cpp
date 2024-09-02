#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <string>

// Product class
class Product {
public:
    // Constructor for initializing product with name and price
    Product(const std::string& name, double price)
            : name(name), price(price) {}

    // Getter for product name
    std::string getName() const { return name; }

    // Getter for product price
    double getPrice() const { return price; }

private:
    std::string name;  // Product name
    double price;      // Product price
};

// ProductFactory class (Factory Method Pattern)
class ProductFactory {
public:
    // Static method to create and return a Product instance
    static Product createProduct(const std::string& name, double price) {
        return Product(name, price);
    }
};

// Order class
class Order {
public:
    // Add a product to the order
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    // Get the list of products in the order
    const std::vector<Product>& getProducts() const {
        return products;
    }

    // Serialize the order details into a string format for storage
    std::string serialize() const {
        std::string data;
        for (const auto& product : products) {
            data += product.getName() + "," + std::to_string(product.getPrice()) + "\n";
        }
        return data;
    }

private:
    std::vector<Product> products;  // List of products in the order
};

// OrderProcessor class (Command Pattern + Threading)
class OrderProcessor {
public:
    // Public method to process an order using threading
    static void processOrder(const Order& order) {
        std::thread processingThread(&OrderProcessor::process, order);
        processingThread.detach();  // Detach the thread to allow it to run independently
    }

private:
    // Private method for actual processing of the order
    static void process(const Order& order) {
        std::ofstream outFile("orders.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << order.serialize();  // Write order details to file
            outFile.close();
            std::cout << "Order processed and saved to file." << std::endl;
        } else {
            std::cerr << "Failed to open file for order processing." << std::endl;
        }
    }
};

// FileManager class (Singleton Pattern)
class FileManager {
public:
    // Get the singleton instance of FileManager
    static FileManager& getInstance() {
        static FileManager instance;
        return instance;
    }

    // Open a file for appending data
    void openFile(const std::string& filename) {
        file.open(filename, std::ios::app);
        if (file.is_open()) {
            std::cout << "File opened: " << filename << std::endl;
        } else {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }

    // Get the file stream for writing
    std::ofstream& getFile() { return file; }

private:
    std::ofstream file;  // File stream for writing
    FileManager() = default;  // Private constructor for singleton
    FileManager(const FileManager&) = delete;  // Delete copy constructor
    FileManager& operator=(const FileManager&) = delete;  // Delete assignment operator
};

// OrderObserver interface (Observer Pattern)
class OrderObserver {
public:
    // Pure virtual method for handling order updates
    virtual void update(const Order& order) = 0;
};

// ConcreteOrderObserver class (Concrete Observer)
class ConcreteOrderObserver : public OrderObserver {
public:
    // Implementation of the update method to handle order updates
    void update(const Order& order) override {
        std::cout << "Order updated with " << order.getProducts().size() << " products." << std::endl;
    }
};

// OrderManager class
class OrderManager {
public:
    // Add an observer to receive updates about orders
    void addObserver(OrderObserver* observer) {
        observers.push_back(observer);
    }

    // Place an order and notify all observers
    void placeOrder(const Order& order) {
        orders.push_back(order);  // Add the order to the list
        for (auto& observer : observers) {
            observer->update(order);  // Notify each observer about the order
        }
        OrderProcessor::processOrder(order);  // Process the order using a separate thread
    }

private:
    std::vector<Order> orders;  // List of orders
    std::vector<OrderObserver*> observers;  // List of observers
};

// Main function
int main() {
    // Get the singleton instance of FileManager and open a file for writing
    FileManager& fileManager = FileManager::getInstance();
    fileManager.openFile("orders.txt");

    // Create products using the ProductFactory
    Product product1 = ProductFactory::createProduct("Laptop", 999.99);
    Product product2 = ProductFactory::createProduct("Smartphone", 499.99);

    // Create an order and add products to it
    Order order;
    order.addProduct(product1);
    order.addProduct(product2);

    // Create an order manager and an observer
    OrderManager orderManager;
    ConcreteOrderObserver observer;
    orderManager.addObserver(&observer);

    // Place the order and let the order processor handle it
    orderManager.placeOrder(order);

    // Give some time for threads to finish processing
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
