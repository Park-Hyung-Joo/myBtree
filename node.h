#ifndef NODE_H
#define NODE_H
#include <utility>
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
	
};

template <typename _key, typename _value>
class _node{
    int num;
	_obj<_key, _value>* val[3];
	_node* child[4]; //if child exist -> child[0]!=NULL
	_node* parent; 
public:
	_node(void){
        temp->parent = NULL;
        temp->num = 0;
        temp->child = {NULL};
    }
};
#endif