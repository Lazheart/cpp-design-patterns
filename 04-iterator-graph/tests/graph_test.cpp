#include "graph/bfs_iterator.hpp"
#include "graph/dfs_iterator.hpp"
#include "graph/graph.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <vector>

TEST(GraphIteratorTest, BFSTraversalOrder) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    std::unique_ptr<GraphIterator> it = std::make_unique<BFSIterator>(g, 1);
    std::vector<int> result;
    while (it->hasNext()) {
        result.push_back(it->next());
    }

    const std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(result, expected);
}

TEST(GraphIteratorTest, DFSTraversalOrder) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    std::unique_ptr<GraphIterator> it = std::make_unique<DFSIterator>(g, 1);
    std::vector<int> result;
    while (it->hasNext()) {
        result.push_back(it->next());
    }

    const std::vector<int> expected = {1, 2, 4, 3};
    EXPECT_EQ(result, expected);
}

TEST(GraphIteratorTest, CyclicGraphTerminates) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(4, 1);  // cycle 1 -> 2 -> 4 -> 1
    g.addEdge(1, 3);

    // BFS
    {
        std::unique_ptr<GraphIterator> it = std::make_unique<BFSIterator>(g, 1);
        std::vector<int> result;
        while (it->hasNext()) {
            result.push_back(it->next());
        }
        EXPECT_EQ(result.size(), 4);
        EXPECT_EQ(result.front(), 1);
    }

    // DFS
    {
        std::unique_ptr<GraphIterator> it = std::make_unique<DFSIterator>(g, 1);
        std::vector<int> result;
        while (it->hasNext()) {
            result.push_back(it->next());
        }
        EXPECT_EQ(result.size(), 4);
        EXPECT_EQ(result.front(), 1);
    }
}

TEST(GraphIteratorTest, NonExistentStartNodeThrows) {
    Graph g;
    g.addEdge(1, 2);

    EXPECT_THROW(BFSIterator(g, 99), std::invalid_argument);
    EXPECT_THROW(DFSIterator(g, 99), std::invalid_argument);
}

TEST(GraphIteratorTest, DisconnectedNodesNotVisited) {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(3, 4);  // Disconnected component

    std::unique_ptr<GraphIterator> it = std::make_unique<BFSIterator>(g, 1);
    std::vector<int> result;
    while (it->hasNext()) {
        result.push_back(it->next());
    }

    const std::vector<int> expected = {1, 2};
    EXPECT_EQ(result, expected);
}

TEST(GraphIteratorTest, NextThrowsWhenEmpty) {
    Graph g;
    g.addEdge(1, 2);

    BFSIterator bfs(g, 1);
    EXPECT_EQ(bfs.next(), 1);
    EXPECT_EQ(bfs.next(), 2);
    EXPECT_FALSE(bfs.hasNext());
    EXPECT_THROW(bfs.next(), std::out_of_range);

    DFSIterator dfs(g, 1);
    EXPECT_EQ(dfs.next(), 1);
    EXPECT_EQ(dfs.next(), 2);
    EXPECT_FALSE(dfs.hasNext());
    EXPECT_THROW(dfs.next(), std::out_of_range);
}
