#ifndef GRAPH_NODE__H
#define GRAPH_NODE__H

#include "core/dictionary.h"
#include "core/variant.h"
#include "core/typedefs.h"

class GraphNode{
	Dictionary _edges{};
	Variant _data{};

public:
	void set_edge(uint32_t node, float weight = 1.f, Variant data = Variant()){
		Dictionary edge;
		edge["weight"] = weight;
		edge["data"] = data;
		_edges[node] = edge;
	}

	void remove_edge(uint32_t node){
		if(!_edges.has(node))
			return;
		_edges.erase(node);
	}

	Dictionary get_edge(uint32_t node)const{
		Dictionary d;
		if(_edges.has(node))
			d = _edges[node];
		return d;
	}

	Array get_edge_nodes() const{
		return _edges.keys();
	}

	Array get_edges() const{
		return _edges.values();
	}

	Variant get_data()const{
		return _data;
	}

	void set_data(Variant d){
		_data = d;
	}
};

#endif