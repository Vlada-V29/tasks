#include<iostream>
#include<vector>

void print_size_and_capacity(const std::vector<int>& v){
    std::cout << "size = " << v.size() << std::endl;
    std::cout << "capacity = " << v.capacity() << std::endl;
}

void part1();
void part2();
void part3();

int main()
{
   // part1();
    //part2();
    part3();


    return 0;
}

void part1(){
    std::vector<int> v1(3, 1);
    
    std::cout << "Now we have vector with 3 elements: " << std::endl;
    print_size_and_capacity(v1);
    

    std::cout << "\nWell, let`s add two elements: " << std::endl;
    v1.push_back(2);
    v1.push_back(2);
    print_size_and_capacity(v1);

    std::cout << "\nIt is interesting. Let`s add another two elements: " << std::endl;
    v1.push_back(3);
    v1.push_back(3);
    print_size_and_capacity(v1);

    std::cout << "\nWe saw that capacity doubled " << std::endl;
    std::cout << "\n \n " << std::endl;
}

void part2(){
    std::vector<int> v2(3, 1);
    
    std::cout << "Now we have vector with 3 elements: " << std::endl;
    print_size_and_capacity(v2);

    std::cout << "\nWell, let`s add two elements with reserve: " << std::endl;
    v2.vector::reserve(v2.size() + 2);
    v2.push_back(2);
    v2.push_back(2);
    print_size_and_capacity(v2);

    std::cout << "\nIt is not so interesting. Let`s add another two elements: " << std::endl;
    v2.vector::reserve(v2.size() + 2);
    v2.push_back(3);
    v2.push_back(3);
    print_size_and_capacity(v2);

    std::cout << "\nWe saw that capacity didn't double " << std::endl;
    std::cout << "\n \n " << std::endl;
}

void part3(){
    std::vector<int> v3(100, 1);//100 -> 10^(11)
    std::cout << "Let's break all!" << std::endl;
    std::cout << "Now we have vector: " << std::endl;
    print_size_and_capacity(v3);
    std::cout << "Let's do push_back " << std::endl;
    v3.push_back(2);
    std::cout << "Ups..." << std::endl;
    
    //???
}
