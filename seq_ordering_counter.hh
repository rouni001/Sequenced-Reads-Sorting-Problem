/**
 * @file SequenceCounter.hh
 * @brief Declarations for an efficient sequence ordering counter.
 *
 * This file is part of the “An efficient sequence ordering counter (HW for SG)” project.
 * Given a FASTA file, the goal is to compute the number of ways to order its sequences,
 * leveraging the fact that some sequences can be subsequences of others.
 *
 * @author  Rachid Ounit, Ph.D.
 * @date    2025-02-01
 */

#ifndef SEQ_ORDERING_COUNTER_HH
#define SEQ_ORDERING_COUNTER_HH

#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <functional>


inline void hash_combine(std::size_t& _seed, std::size_t _value)
{
    _seed ^= _value + 0x9E3779B9 + (_seed << 6) + (_seed >> 2);
}

struct SetHash 
{
    std::size_t operator()(const std::set<int>& _s) const 
    {
        std::size_t hash = 0;
        for (std::set<int>::const_iterator it = _s.begin(); it != _s.end(); ++it) 
        {
            hash_combine(hash, std::hash<int>()(*it));
        }
        return hash;
    }
};


class SeqOrderingCounter
{
    private:
        std::unordered_map< std::set< int >, size_t, SetHash >  m_cache;
        const std::vector< std::set< int > >                    m_adjMatrix;
        const size_t                                            m_moduloSize;

    public:
        SeqOrderingCounter(
            const std::vector< std::set< int > >&       _adjMatrix,
            const size_t&                               _moduloSize = 100003
        );

        ~SeqOrderingCounter();

        size_t count();

    private:
        std::set<int> find_next_vertices(std::set<int> _nodesVisited);
        
        size_t count_possible_paths_from(std::set<int>& _nodesVisited);
    
};

#endif // SEQ_ORDERING_COUNTER_HH