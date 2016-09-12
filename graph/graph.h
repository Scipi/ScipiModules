#ifndef GRAPH__H
#define GRAPH__H

#include "node.h"
#include "core/map.h"
#include "core/typedefs.h"
#include "core/error_list.h"
#include "core/variant.h"

#include "graph_node.h"

class Graph : public Node{
	OBJ_TYPE(Graph, Node);
	Map<uint32_t, GraphNode> _nodes;
	uint32_t _nextID{0};

public:

	Graph();

	void make_node(Variant d){
		GraphNode gn;
		gn.set_data(d);
		_nodes[_nextID] = gn;
		_nextID++;
	}

	Error connect_linear(uint32_t from, uint32_t to, float weight = 1.f, Variant data = Variant()){
		if(!_nodes.has(from) || !_nodes.has(to))
			return FAILED;
		_nodes[from].set_edge(to, weight, data);
		return OK;
	}

	Error connect_bilinear(uint32_t from, uint32_t to, float weight = 1.f, Variant data = Variant()){
		if(!_nodes.has(from) || !_nodes.has(to))
			return FAILED;
		_nodes[from].set_edge(to, weight, data);
		_nodes[to].set_edge(from, weight, data);
		return OK;
	}

	Dictionary get_node(uint32_t node){
		Dictionary d;
		if(_nodes.has(node)){
			d["id"] = node; // Redundant, but whatever
			d["data"] = _nodes[node].get_data();
			d["edges"] = _nodes[node].get_edges();
		}
		return d;
	}

	Dictionary get_edge(uint32_t from, uint32_t to){
		Dictionary d;
		if(_nodes.has(from) && _nodes[from].has_edge(to)){
			d = _nodes[from].get_edge(to);
		}
		return d;
	}

	Array get_node_neighbors(uint32_t node){
		Array a;
		if(_nodes.has(node)){
			a = _nodes[node].get_edge_nodes();
		}
		return a;
	}

};

#endif