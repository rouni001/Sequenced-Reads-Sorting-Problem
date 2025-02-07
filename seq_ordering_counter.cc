/**
 * @file SequenceCounter.cc
 * @brief Implementation for an efficient sequence ordering counter.
 *
 * This file is part of the “An efficient sequence ordering counter (HW for SG)” project.
 * Given a FASTA file, the goal is to compute the number of ways to order its sequences,
 * leveraging the fact that some sequences can be subsequences of others.
 *
 * @author  Rachid Ounit, Ph.D.
 * @date    2025-02-01
 */

#include <iostream>
#include <set>
#include <unordered_set>

#include "./seq_ordering_counter.hh"
using namespace std;


SeqOrderingCounter::SeqOrderingCounter(
    const std::vector< std::set< int > >&       _adjMatrix,
    const size_t&                               _moduloSize
): m_adjMatrix(_adjMatrix), m_moduloSize(_moduloSize)
{}

SeqOrderingCounter::~SeqOrderingCounter()
{}

size_t SeqOrderingCounter::count()
{
    // To estimate the number of paths, we return the count value from the root 
    // or the empty set of nodes visited:
    std::set<int> root = {};
    return SeqOrderingCounter::count_possible_paths_from(root);
}

std::set<int> SeqOrderingCounter::find_next_vertices(std::set<int> _nodesVisited)
{
    // Admissible nodes, the nodes to visit next (given the nodes already visited):
    std::set<int> next_vertexes = {};
    // Nodes that can not be visited next:
    std::set<int> posterior_vertexes = {};
    
    // First, we identify the nodes that can not be visited next given:
    for (size_t i = 0; i < m_adjMatrix.size(); i++) 
    {
        if (_nodesVisited.find(i) != _nodesVisited.end()) 
        {
            continue;
        }
        if (!m_adjMatrix[i].empty()) 
        {
            posterior_vertexes.insert(m_adjMatrix[i].begin(), m_adjMatrix[i].end());
        }
    }
    // Second, we identify the nodes admissible for the next visit:
    for (size_t i = 0; i < m_adjMatrix.size(); i++) 
    {
        if (_nodesVisited.find(i) != _nodesVisited.end()) 
        {   
            continue; 
        }
        if (posterior_vertexes.find(i) == posterior_vertexes.end()) 
        {
            next_vertexes.insert(i);
        }
    }
    
    return next_vertexes;
}


size_t SeqOrderingCounter::count_possible_paths_from(std::set<int>& _nodesVisited)
{
    // Check if this set was already visited: 
    auto cache_it = m_cache.find(_nodesVisited);
    if (cache_it != m_cache.end()) 
    {
        return cache_it->second;
    }
    
    // Find the set of admissible nodes to visit next:
    std::set<int> next_nodes = find_next_vertices(_nodesVisited);
    
    // If there are no next nodes, cache and return:
    if (next_nodes.empty()) 
    {
        m_cache[_nodesVisited] = 1;
        return 1;
    }
    
    int total_count = 0;
    // For each admissible node to visit next:
    for (int node : next_nodes) 
    {
        // add this node to the visited set.
        _nodesVisited.insert(node);
        
        // check if this set was visited before, otherwise we cache it:
        if (m_cache.find(_nodesVisited) == m_cache.end()) 
        {
            int count = count_possible_paths_from(_nodesVisited);
            m_cache[_nodesVisited] = count % m_moduloSize;
        }
        // sum the count results from the next nodes:
        total_count = (total_count + m_cache[_nodesVisited] % m_moduloSize) % m_moduloSize;
        // remove the node after visiting it:
        _nodesVisited.erase(node);
    }
    
    // Cache the summed value across the admissible nodes:
    m_cache[_nodesVisited] = total_count % m_moduloSize;
    return m_cache[_nodesVisited];
}
