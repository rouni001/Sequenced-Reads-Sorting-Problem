/**
 * @file utils.cc
 * @brief Implementations of util functions.
 *
 * This file is part of the “An efficient sequence ordering counter (HW for SG)” project.
 * Given a FASTA file, the goal is to compute the number of ways to order its sequences,
 * leveraging the fact that some sequences can be subsequences of others.
 *
 * @author  Rachid Ounit, Ph.D.
 * @date    2025-02-01
 */

#include <vector>
#include <iostream>
#include <set>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;


std::vector<std::string> extract_sequences_from_fasta_file(const char* _filename)
{
    std::vector<std::string> seqs;
    std::ifstream ifs(_filename);
    if (!ifs) 
    {
        std::cerr << "Error: could not open file " << _filename << std::endl;
        return seqs;
    }
    
    std::string line;
    int lineCount = 0;
    
    while (std::getline(ifs, line)) 
    {
        lineCount ++;
        if (lineCount % 2 == 1)
            continue;
        seqs.push_back(line);
    }
    ifs.close();
    return seqs;
}

bool fill_adjacency_matrix_from_seqs(const std::vector<std::string>& _seqs, std::vector< std::set< int > >& _adjMatrix)
{
    if (_seqs.size() == 0)
        return false;
    _adjMatrix.resize(_seqs.size());
    
    for (std::size_t i = 0; i < _seqs.size(); i++) 
    {
        for (std::size_t j = 0; j < _seqs.size(); j++) 
        {
            if (i == j)
                continue;
            if (_seqs[j].find(_seqs[i]) != std::string::npos) 
            {
                _adjMatrix[i].insert(j);
            }
        }
    }
    return true;
}

bool extract_adjacency_matrix_from_fasta_file(const char* _filename, std::vector< std::set< int > >& _adjMatrix)
{
    return fill_adjacency_matrix_from_seqs(extract_sequences_from_fasta_file(_filename), _adjMatrix);
}