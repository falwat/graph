/**
 * @file graph.h
 * @author Jackie Wang (falwat@163.com)
 * @brief Graph implementation with c++
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022 under MIT licence
 * 
 */
#if !defined(_GRAPH_H_)
#define _GRAPH_H_

#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <variant>

#ifndef HAS_ATTRIB
#define HAS_ATTRIB 1
#endif

#if HAS_ATTRIB
using Variant = std::variant<int, double, std::string>;
#endif

class Edge;

class Node
{
private:
    int id;
    std::map<int, Edge *> edges;
#if HAS_ATTRIB    
    std::map<std::string, Variant> attrib;
#endif
public:
#if !HAS_ATTRIB
    Node(int id) : id(id) {}
#else
    Node(int id, const std::map<std::string, Variant> &attrib = {}) : id(id), attrib(attrib) {}
    std::map<std::string, Variant> &get_attrib() {return attrib;}
#endif
    /**
     * @brief Get the node id
     * 
     * @return int : this->id
     */
    int get_id() {return id;}
    /**
     * @brief Add edge from this to target node
     * 
     * @param vid  : The target node id
     * @param edge : The pointer of Edge object
     */
    void add_edge(int vid, Edge *edge) {edges[vid] = edge;}
    /**
     * @brief Get the edges object
     * 
     * @return std::map<int, Edge *>& : this->edges
     */
    std::map<int, Edge *> &get_edges() {return edges;};
};


class Edge
{
public:
    double weight;
#if HAS_ATTRIB
    /**
     * @brief Edge's attributes
     */
    std::map<std::string, Variant> attrib;
#endif
public:

#if !HAS_ATTRIB
    Edge(double weight) : weight(weight) {}
#else
    Edge(double weight, const std::map<std::string, Variant> &attrib = {}) : 
        weight(weight), attrib(attrib) {}
    std::map<std::string, Variant> &get_attrib() {return attrib;}
#endif
};

/**
 * @brief Graph class
 * 
 */
class Graph
{
private:
    std::map<int, std::shared_ptr<Node>> nodes;
    std::map<int, std::map<int, std::shared_ptr<Edge>>> edges;
    std::tuple<double, std::list<int>> 
    shortest_simple_paths(int source_id, int target_id, std::list<int> &rem_nodes);
public:
    ~Graph();
    /**
     * @brief Add node to this graph
     * 
     * @param node : The pointer to Node object
     */
    void add_node(Node *node);
    
#if !HAS_ATTRIB
    void add_node(int id);
#else
    /**
     * @brief Add node to this graph
     * 
     * @param id     : node id
     * @param attrib : node attributes
     */
    void add_node(int id, const std::map<std::string, Variant> &attrib = {});
#endif
    /**
     * @brief get the pointer of node.
     * 
     * @param id     : Node id
     * @return Node* : The pointer of node
     */
    Node *node(int id);
    /**
     * @brief Add edge to this graph
     * 
     * @param uid    : Source node id
     * @param vid    : Target node id
     * @param weight : Edge weight.
     * @return Edge* : The pointer of edge
     */
    Edge *add_edge(int uid, int vid, double weight = 1.0);
    /**
     * @brief Check if the edge(uid, vid) is in this graph.
     * 
     * @param uid    : Source node id
     * @param vid    : Target node id
     * @return true  : The edge(uid, vid) is in this graph.
     * @return false : The edge(uid, vid) is not in this graph.
     */
    bool has_edge(int uid, int vid);
    /**
     * @brief Get the count of edge in this graph
     * 
     * @return int : The count of edge
     */
    int edge_count() const;
    /**
     * @brief Get the neighbors of node in this graph
     * 
     * @param id : node id
     * @return std::set<Node *> : the set of neighbors node
     */
    std::set<Node *> get_neighbors(int id);
    /**
     * @brief Get the shortest simple path from node with source_id to node with target_id
     * 
     * @param source_id : source node id.
     * @param target_id : Target node id.
     * @return std::tuple<double, std::list<int>> : 
     *      The sum of weight of the shortest simple path and a list of node in this path.
     */
    std::tuple<double, std::list<int>> shortest_simple_paths(int source_id, int target_id);
};


#endif // _GRAPH_H_
