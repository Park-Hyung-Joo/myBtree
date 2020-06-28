#include <utility>
#ifndef NODE_H
#define NODE_H
template <typename _key, typename _value>
struct _obj{
	_key key;
	_value v;
	bool operator<(const _obj o)const{if(key < o.key) return true; else return false;}
	bool operator<(const _obj *po)const{if(key < po->key) return true; else return false;}
	bool operator<=(const _obj o)const{if(key <= o.key) return true; else return false;}
	bool operator<=(const _obj *po)const{if(key <= po->key) return true; else return false;}
	bool operator>(const _obj o)const {if(key > o.key) return true; else return false;}
	bool operator>(const _obj *po)const {if(key > po->key) return true; else return false;}
	bool operator>=(const _obj o)const {if(key >= o.key) return true; else return false;}
	bool operator==(const _obj o)const {if(key == o.key) return true; else return false;}
	bool operator==(const _obj *po)const {if(key == po->key) return true; else return false;}
	_obj(){}
	_obj(const std::pair<_key, _value> &o){
		key = o.first;
		v= o.second;
	}
	~_obj(){}
};

template <typename _key, typename _value>
struct _node{
    int num;
	_obj<_key, _value>* val[3];
	_node* child[4]; //if child exist -> child[0]!=NULL
	_node* parent; 
public:
	_node(void){
        parent = nullptr;
        num = 0;
		child[0] = child[1] = child[2] = child[3] = child[4] =nullptr;
    }
};
#endif