/**
 * @file utils.hh
 * @brief Declarations of util functions.
 *
 * This file is part of the “An efficient sequence ordering counter (HW for SG)” project.
 * Given a FASTA file, the goal is to compute the number of ways to order its sequences,
 * leveraging the fact that some sequences can be subsequences of others.
 *
 * @author  Rachid Ounit, Ph.D.
 * @date    2025-02-01
 */

#ifndef UTILS_HH
#define UTILS_HH

#include <vector>
#include <cstring>
#include <set>


std::vector<std::string> extract_sequences_from_fasta_file(const char* _filename);

bool fill_adjacency_matrix_from_seqs(const std::vector<std::string>& _seqs, std::vector< std::set< int > >& _adjMatrix);

bool extract_adjacency_matrix_from_fasta_file(const char* _filename, std::vector< std::set< int > >& _adjMatrix);


#endif // UTILS_HH