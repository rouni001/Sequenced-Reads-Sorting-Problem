/**
 * @file main.cc
 * @brief Main program.
 *
 * This file is part of the “An efficient sequence ordering counter (HW for SG)” project.
 * Given a FASTA file, the goal is to compute the number of ways to order its sequences,
 * leveraging the fact that some sequences can be subsequences of others.
 *
 * @author  Rachid Ounit, Ph.D.
 * @date    2025-02-01
 */
 
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <fstream>
#include <cstring>

#include "./seq_ordering_counter.hh"
#include "./utils.hh"
using namespace std;


bool validate(const int _argc, const char** _argv)
{
    if (_argc != 2)
    {
        std::cerr << "Usage: " << _argv[0] << " <Path of fasta file: string> "<< std::endl;
        return false;
    }
    FILE * fd = fopen(_argv[1], "r");
    if (fd == NULL)
    {
        std::cerr << "Failed to open: " <<_argv[1] << endl;
        return false;
    }
    fclose(fd);
    return true;

}


int main(const int argc, const char** argv)
{
    if (!validate(argc, argv))
    {
        std::cerr << "Failed to run " << argv[0] << endl;
        return -1;
    }

    std::vector< std::set< int > > adjMatrix; 
    if (!extract_adjacency_matrix_from_fasta_file(argv[1], adjMatrix))
    {
        std::cerr << "Failed to extract sequences/adjacency from the fasta file: " << argv[1] << std::endl;
        return -1;
    }

    SeqOrderingCounter counter(adjMatrix);
    size_t value = counter.count();

    std::cout << value << std::endl;

    return 0;
    
}