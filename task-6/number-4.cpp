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
    
};

std::ostream& operator<< (std::ostream &out, const Person &p)
{
    out << "name: " << p.name << "\n" << 
        "age: " << p.age << "\n" << "weight" << p.weight;
 
    return out;
}


int main()
{
    std::string n;
    int a;
    double w;

    std::cout << "Enter the name, age and weight of the person:";
    std::cin >> n;
    std::cin >> a;
    std::cin >> w;
    Person p1(n, a, w);
    std::cout << "Enter the name, age and weight of the person:";
    std::cin >> n;
    std::cin >> a;
    std::cin >> w;
    Person p2(n, a, w);
    std::cout << "Enter the name, age and weight of the person:";
    std::cin >> n;
    std::cin >> a;
    std::cin >> w;
    Person p3(n, a, w);

    auto path = std::experimental::filesystem::current_path();
    std::experimental::filesystem::create_directory(path / "mydir");
    std::experimental::filesystem::path path_output1 = "mydir/f1.txt";
    std::experimental::filesystem::path path_output2 = "mydir/f2.txt";
    std::experimental::filesystem::path path_output3 = "mydir/f3.txt";
    
    json j1;
    json j2;
    json j3;

    j1["Name"] = p1.name;
	j1["age"] = p1.age;
    j1["weight"] = p1.weight;

    j2["Name"] = p2.name;
	j2["age"] = p2.age;
    j2["weight"] = p2.weight;

    j3["Name"] = p3.name;
	j3["age"] = p3.age;
    j3["weight"] = p3.weight;


    std::fstream fout1(path_output1.string(), std::ios::out);
	fout1 << std::setw(4) << j1;
    std::fstream fout2(path_output2.string(), std::ios::out);
	fout2 << std::setw(4) << j2;
    std::fstream fout3(path_output3.string(), std::ios::out);
	fout3 << std::setw(4) << j3;

    return EXIT_SUCCESS;
}

