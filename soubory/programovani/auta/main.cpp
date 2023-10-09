#include "Database.h"

#include <iostream>

int main() {
    Database<std::string, unsigned int, float> auta = {"model", "rok","cena"};

    auta += {"skoda-scala",2023,432135};
    auta += {"renault-plio",2004,45441};
    auta += {"fiat-punto",2012,245169};
    auta += {"lada-niva",1995,245169};

    std::cout << auta.dump("cena", Sort::ASC, '|') << std::endl;

    //auta.dump_b("test.auticka");
    //auta.read_b("test.auticka");

    return 0;
}
