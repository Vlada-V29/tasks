#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>

#include "json.hpp"
using nlohmann::json;


struct Person
{
    std::string name;
    int age;
    double weight;
 
    Person():name(" "), age(0), weight(0.0){};
    Person(std::string n, int a, double w):name(n), age(a), weight(w){};
    friend std::ostream& operator<< (std::ostream &out, const Person &p);
    friend std::istream& operator<< (std::istream &in, const Person &p);
    
};

std::ostream& operator<< (std::ostream &out, const Person &p)
{
    out << "name: " << p.name << "\n" << 
        "age: " << p.age << "\n" << "weight" << p.weight;
 
    return out;
}
std::istream& operator>> (std::istream &in, Person &p)
{
    std::cout << "Enter the name, age and weight of the person:";
    in >> p.name; 
    in >> p.age >> p.weight;
 
    return in;
}


int main()
{
    
    Person* p = new Person[3];
    for(auto i = 0; i < 3; ++i)
    {
        std::cin >> p[1];
    }
    

    auto path = std::experimental::filesystem::current_path();
    std::experimental::filesystem::create_directory(path / "mydir");
    std::experimental::filesystem::path path_output1 = "mydir/f1.txt";
    std::experimental::filesystem::path path_output2 = "mydir/f2.txt";
    std::experimental::filesystem::path path_output3 = "mydir/f3.txt";

    json* j = new json[3];
    for(auto i = 0; i < 3; ++i)
    {
        j[1]["Name"] = p[1].name;
	    j[1]["age"] = p[1].age;
        j[1]["weight"] = p[1].weight;
    }

    for(auto i = 0; i < 3; ++i)
    {
        std::fstream fout1(path_output1.string(), std::ios::out);
	fout1 << std::setw(4) << j[1];
    }

    delete [] p;
    return EXIT_SUCCESS;
}

