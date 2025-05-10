#include <iostream> // Including the input output library
#include <string> // Including the string library
#include <vector> // Including the vector library

using namespace std; // Using the standard namespace

// Creating supporting classes for composition
// Class for Diet
class Diet {
private:
    string type;
public:
    Diet(const string& type) : type(type) {}
    string getType() const {
        return type;
    }
};

// Class for Habitat
class Habitat {
private:
    string description;
public:
    Habitat(const string& description) : description(description) {}
    string getDescription() const {
        return description;
    }
};

// Creating an abstract class (Animal)
class Animal {
protected:
    string name;
    int age;
    const string species;
    Diet diet; // Composition, an animal has a diet
    Habitat habitat; // Composition, an animal has a habitat

public:
    // Constructor in animal class to initialize the attributes using the this pointer
    Animal(const string& name, int age, const string& species, const Diet& diet, const Habitat& habitat)
        : species(species), diet(diet), habitat(habitat) {
        this->name = name;
        this->age = age;
    }

    // Including pure virtual functions for polymorphism
    virtual void makeSound() const = 0;
    virtual void eat() const = 0;

    // Final method to display animal information (cannot be overridden)
    virtual void displayInfo() const final {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << " years old" << endl;
        cout << "Species: " << species << endl;
        cout << "Diet type: " << diet.getType() << endl;
        cout << "Habitat description: " << habitat.getDescription() << endl;
        cout << endl;

    }
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Animal() {}
};

// Creating two subclasses of animals and implementing the pure virtual functions
// Lion subclass
class Lion : public Animal {
public:
    Lion(const string& name, int age, const Diet& diet, const Habitat& habitat)
        : Animal(name, age, "Lion", diet, habitat) {}

    void makeSound()  const override {
        cout << name << " ROARS!" << endl;
    }
    void eat() const override {
        cout << name << " eats meat." << endl;
    }
};

// Elephant subclass
class Elephant : public Animal {
public:
    Elephant(const string& name, int age, const Diet& diet, const Habitat& habitat)
        : Animal(name, age, "Elephant", diet, habitat) {}

    void makeSound() const override {
        cout << name << " TRUMPETS!" << endl;
    }
    void eat() const override {
        cout << name << " eats grasses, fruits and roots." << endl;
    }
};

// Creating a function that iterates through the zoo and calls makeSound on each animal to demonstrate polymorphism
void makeAllAnimalsSound(const vector<Animal*>& zoo) {
    for (const auto& animal : zoo) {
        animal->makeSound();
    }
}

// Main function
int main() {
    // Creating a zoo collection to store animals
    vector<Animal*> zoo;

    // Creating diet and habitat objects
    Diet carnivore("Carnivore");
    Diet herbivore("Herbivore");

    Habitat savanna("Savanna");
    Habitat forest("Forest");

    // Instantiating animals (two of each animal type) and adding them to the zoo collection
    // Lion 
    zoo.push_back(new Lion("Thor", 5, carnivore, savanna));
    zoo.push_back(new Lion("Theo", 6, carnivore, savanna));

    // Elephant 
    zoo.push_back(new Elephant("Kibo", 8, herbivore, forest));
    zoo.push_back(new Elephant("Kali", 10, herbivore, forest));

    // Making all animals sound (demonstrating polymorphism)
    cout << "All animals making sounds:" << endl;
    makeAllAnimalsSound(zoo);
    cout << endl;

    // Displaying information of all animals
    cout << "Animal Information:" << endl;
    for (const auto& animal : zoo) {
        animal->displayInfo();
    }

    // Cleaning up memory by deleting the dynamically allocated animals
    for (auto animal : zoo) {
        delete animal;
    }
    
    return 0;
}