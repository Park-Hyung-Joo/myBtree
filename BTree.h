#include "node.h"
#include <queue>
#include <stdio.h>
template <typename _key, typename _value>
class Btree{
    int elementNum;
    using pnode = _node<_key, _value>*;
    struct pos{
        pnode target;
        int number;
    };
    using ppos = pos*;
    using item = _obj<_key, _value>;
    using node = _node<_key, _value>;
    using queue = std::queue<pnode>;
    pos buffer;
    pnode root;
    void deleteNode(pnode p){
        if (p!=NULL){
            delete p;
            p = NULL;
        }
    }
    bool isTerminal(pnode givenNode){
        if (givenNode==NULL||givenNode->child[0]==NULL){
            return true;
        }
        return false;
    }
    void adoption(pnode parent_next,int index,pnode child);

    _value* search(item &k);
    _value* search_sub(pnode n,item &k);

    pnode find_seat(pnode n,item *k);
    int insert_as_smaller_than_2(pnode target, item* k, pnode getLeft, pnode getRight);
    int insertion(item* k);
    int propagation(pnode getLeft, pnode getRight, pnode target, item* popped);
    int deletion(item& k);
    void search_for_delete(pnode n,item& target);
    int find_index(pnode targetNode);
    pnode find_successor(pnode n,int number){//find successor of n->val[number]
	    //initial condition: n has children => successor exist
        pnode successor=n->child[number+1];
        while(!isTerminal(successor)){//while temp has child
            successor=successor->child[0];
        }
        return successor;//successsor key is successor->val[0]
    };
    int propagation_delete(pnode targetNode);
    void delete_simple(pnode targetLeaf,int targetNumber);
    public:
    Btree(){root = NULL; elementNum = 0;}
    ~Btree(){
        while(elementNum > 0){
            deletion(*(root->val[0]));
        }
    }
    void insert(std::pair<_key, _value> input);
    void insert(std::vector< std::pair<_key, _value> > inputList);
    bool pop(_key target);
    bool empty();
    int size();
    void clear();
    _value* find(_key k);
};
#include "BTree.hpp"