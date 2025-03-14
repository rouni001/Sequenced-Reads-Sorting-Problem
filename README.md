# Sequenced Reads Sorting Problem
This repo presents the implementation for a fast sequences sorting counter from FASTA sequences.
To determine the number of distinct ways to order a set of sequences, leveraging the fact some sequences 
may be subsequences of others, our algorithm is based on a directed graph-based approach with caching.

## Author & Date
Rachid Ounit, Ph.D.

02/07/2025

## Introduction

## Problem Definition
The problem is defined as:

We are given a fasta file (https://en.wikipedia.org/wiki/FASTA_format). For the
moment, it is enough to understand that a fasta file contains a list of entries, where
each entry is composed of two lines. First line starts with ‘>’ and contains the id of an
entry. Second line, which follows immediately, contains a sequence.

We want to sort the fasta file following this rule:

• For every entry A with sequence that is a substring of a sequence of an entry
B, A must appear before B.

### Problem Specifications

To simplify the given problem, here are some constraints:

• As the answer can be quite large, print the answer (modulo 100003)

• The fasta file contains only the entries (no empty lines or comments)

• There are no entries with identical sequence or id

• The number of entries will not exceed 30


## Problem Solution

To solve this problem, we consider a directed graph-based approach where
each sequence is a node/vertex, and if sequence A is a subsequence
of sequence B then node A is connected to node B (A <- B).
Then we add one more node, the root of this graph, which is connected
to all nodes that do not have any parent.

The problem of counting how many valid ways the sequences can be sorted
becomes now equivalent to counting the number of Ordered Sets of Nodes
(OSN) where all nodes in the graph are selected (starting by the root) and
the order in the nodes follows the adjacency matrix (i.e., node A is 
ordered by node B if and only sequence A is included in sequence B).

A directed-graph based approach is be an effective way to find the nodes
connected to a given node as well as those that are not connected to it 
including (independent nodes).

In addition, we can observe that for a set of nodes that do not connect
with each others (no edges exist among them) then the their ordering
in a OSN does not matter at all. This observation is critical for optimizing
the implementation (caching).

## Algorithm Outline

To determine how many OSN exists, we propose the following algorithm:
- Extract the n sequences from the fasta file.
- Determine the adjacency matrix (i.e. for i,j < n and i<>j, if node i is connected to node j)
- Create an empty set of visited set of nodes.
- Create an empty hash-table mapping set of nodes (ordered set) to count value (integer).
- Then recursively do:
  - Check if the count value of the current visited set is stored in the cache.
  - If not cached, we identify the nodes that can be visited next.
  - If there are no nodes left to visit (i.e., all nodes have been visited), we cache the current visited set to the count value of 1.
  - Otherwise, we visit each of these nodes (recursively) and sum the their count value computed (modulo 100003).
  - We store this sum count value in the cache and return that result.

## Algorithm

## Requirements & Execution
A C++ Compiler (g++, clang++, etc.) supporting C++11 or higher is required.

To compile the solution, run the following in terminal:
```
g++ -O3 -std=c++11 main.cc seq_ordering_counter.cc utils.cc -o counter
```

## Usage & Tests
This code was successfully tested in Linux and Mac environement.

```
./counter /path/to/your_file.fasta
```

### Contact
Feel free to email me at rachid.ounit@gmail.com
