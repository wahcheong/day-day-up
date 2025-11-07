// Simple factory pattern demonstration in C++
#include <iostream>
#include <memory>
#include <string>

// Product interface
class Product {
public:
    virtual ~Product() {}
    virtual std::string getName() const = 0;
};
// Concrete Product A
// Inherits from Product
class ConcreteProductA : public Product {
public:
    std::string getName() const override {
        return "ConcreteProductA";
    }
};
// Concrete Product B
// Inherits from Product
class ConcreteProductB : public Product {
public:
    std::string getName() const override {
        return "ConcreteProductB";
    }
};
// Factory class
class ProductFactory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ConcreteProductA>();
        } else if (type == "B") {
            return std::make_unique<ConcreteProductB>();
        } else {
            return nullptr;
        }
    }
};

int main() {
    // Create Product A
    auto productA = ProductFactory::createProduct("A");
    if (productA) {
        std::cout << "Created: " << productA->getName() << std::endl;
    }

    // Create Product B
    auto productB = ProductFactory::createProduct("B");
    if (productB) {
        std::cout << "Created: " << productB->getName() << std::endl;
    }

    // Attempt to create an unknown product
    auto unknownProduct = ProductFactory::createProduct("C");
    if (!unknownProduct) {
        std::cout << "Unknown product type." << std::endl;
    }

    return 0;
}
