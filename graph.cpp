/**
 * @file graph.cpp
 * @author Jackie Wang (falwat@163.com)
 * @brief Graph implementation with c++
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022 under MIT licence
 * 
 */
#include "graph.h"
#include <fstream>
#include <iostream>
#include <vector>

Graph::~Graph()
{}

void Graph::add_node(Node *node)
{
    std::shared_ptr<Node> p(node);
    nodes[p->get_id()] = p;
}

#if !HAS_ATTRIB
void Graph::add_node(int id)
{
    std::shared_ptr<Node> p(new Node(id));
    nodes[p->get_id()] = p;
}
#else
void Graph::add_node(int id, const std::map<std::string, Variant> &attrib)
{
    std::shared_ptr<Node> p(new Node(id, attrib));
    nodes[p->get_id()] = p;
}
#endif

Node *Graph::node(int id)
{
    return nodes[id].get();
}

Edge *Graph::add_edge(int uid, int vid, double weight)
{
    if (this->nodes.find(uid) == this->nodes.end())
    {
        add_node(uid);
    }
    if (this->nodes.find(vid) == this->nodes.end())
    {
        add_node(vid);
    }
    if (has_edge(uid, vid))
    {
        this->edges[uid][vid]->weight = weight;
    }
    else
    {
        std::shared_ptr<Edge> edge(new Edge(weight));
        this->edges[uid][vid] = edge;
        this->nodes[uid]->add_edge(vid, edge.get());
    }
    return this->edges[uid][vid].get();
}

bool Graph::has_edge(int uid, int vid)
{
    if (edges.find(uid) != edges.end() && edges[uid].find(vid) != edges[uid].end())
        return true;
    else
        return false;
}

int Graph::edge_count() const
{
    int count = 0;
    for (auto &&e : edges)
    {
        count += (int)e.second.size();
    }
    return count;
}

std::set<Node *> Graph::get_neighbors(int id)
{
    std::set<Node *> neighbors;
    for (auto &&e : nodes[id]->get_edges())
    {
        neighbors.insert(nodes[e.first].get());
    }
    neighbors.erase(nodes[id].get());
    return neighbors;
}

std::tuple<double, std::list<int>> 
Graph::shortest_simple_paths(int source_id, int target_id, std::list<int> &rem_nodes)
{
    auto edges = nodes[source_id]->get_edges();
    double min_weight = INFINITY;
    int next_node_id;
    std::map<int, std::list<int>> paths;
    for (auto &&e : edges)
    {
        bool mark = false;
        for (auto &&n : rem_nodes)
        {
            if(n == e.first)
            {
                mark = true;
                break;
            }
        }
        if(mark == false)
        {
            return std::make_tuple(INFINITY, std::list<int>());
        }
        else
        {
            rem_nodes.remove(e.first);
            double sum_weight;
            if (e.first != target_id)
            {
                std::list<int> path;
                std::tie(sum_weight, path) = shortest_simple_paths(e.first, target_id, rem_nodes);
                paths[e.first] = std::move(path);
            }
            else
            {
                sum_weight = 0;
                paths[e.first] = std::list<int>();
            }
            sum_weight += e.second->weight;
            if (sum_weight < min_weight)
            {
                min_weight = sum_weight;
                next_node_id = e.first;
            }
            rem_nodes.push_back(e.first);
        }
    }
    std::list<int> path = std::move(paths[next_node_id]);
    if (min_weight != INFINITY)
    {
        path.push_front(next_node_id);
    }
    return std::make_tuple(min_weight, path);
}

std::tuple<double, std::list<int>> 
Graph::shortest_simple_paths(int source_id, int target_id)
{
    std::list<int> path;
    std::list<int> rem_nodes;
    for (auto &&n : nodes)
    {
        if (n.first != source_id)
            rem_nodes.push_back(n.first);
    }

    double sum_weight;
    std::tie(sum_weight, path) = shortest_simple_paths(source_id, target_id, rem_nodes);
    path.push_front(source_id);
    return std::make_tuple(sum_weight, path);
}