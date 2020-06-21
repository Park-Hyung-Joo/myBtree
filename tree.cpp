#include "Tree.h"
#include "node.h"
template <typename _key, typename _value>
void Btree<_key, _value>::insert(std::pair<_key, _value> input){
    item *temp = new item;
    temp->key = input.first;
    temp->v = input.second;
    insertion(temp);
}
template <typename _key, typename _value>
bool Btree<_key, _value>::pop(_key target){
    item temp;
    temp.key = target;
    if(deletion(target) == -1) return false;
    else return true;
}
template <typename _key, typename _value>
bool Btree<_key, _value>::empty(){
    if(elementNum) return false;
    else return true;
}
template <typename _key, typename _value>
int Btree<_key, _value>::size(){
    return elementNum;
}
template <typename _key, typename _value>
void Btree<_key, _value>::clear(){
    while (elementNum > 0)
        deletion(*(root->val[0]))
}
template <typename _key, typename _value>
_value* Btree<_key, _value>::find(_key k){
    item temp;
    temp.key = k;
    
}
template <typename _key, typename _value>
_value* Btree<_key, _value>::search(item &k){
    if(elementNum==0){
        return null;
    }
    _value* temp=null;
    temp=search_sub(root,k);
    if(temp==null){
        return null;
    }
    return temp;  
}
template <typename _key, typename _value>
_value* Btree<_key, _value>::search_sub(pnode n,item &k){
    if(!n) return null;
    int i=0;
    for(i;i<n->num;i++){
        if(k<=n->val[i]){
            if(k==n->val[i]){
                return &(n->val[i]->v);
            }
            else{
                return search_sub(n->child[i],k);
            }
        }
        else;
    }
    return search_sub(n->child[i],k);
}
template <typename _key, typename _value>
void Btree<_key, _value>::adoption(pnode parent_next,int index,pnode child){
	parent_next->child[index]=child;
	child->parent=parent_next;
	return;
}
template <typename _key, typename _value>
void Btree<_key, _value>::search_for_delete(pnode n,item& target){//initial condition: T->root has children
    if(!n){
    	buffer.target=NULL;
    	return;
	}
	int i=0;
    for(i;i<n->num;i++){
        if(target<=n->val[i]){
            if(target==n->val[i]){
                buffer.target=n;
                buffer.number=i;
                return;
            }
            else{
                return search_for_delete(n->child[i],target);
            }
        }
        else;
    }
    //target->val[number] > n->val[num-1]
    return search_for_delete(n->child[i],target);
}
template <typename _key, typename _value>
void Btree<_key, _value>::delete_simple(pnode targetLeaf,int targetNumber){//delete that 
    int i=targetNumber;
    delete targetLeaf->val[targetNumber];
    targetLeaf->num--;
    for(i; i<targetLeaf->num; i++){
        targetLeaf->val[i]=targetLeaf->val[i+1];
    }
    return;
}
template <typename _key, typename _value>
int Btree<_key, _value>::find_index(pnode targetNode){//find i that (parent->child[i]==targetNode)
    //invariant: targetNode is not root (targetNode->parent!=NULL)
    pnode parent=targetNode->parent;
    int i=0;
    for(i;i<=parent->num;i++){
        if(parent->child[i]==targetNode) return i;
    }
    printf("error!! parent->num is worng!!\n");
    return -1;
}

template <typename _key, typename _value>
int Btree<_key, _value>::propagation_delete(pnode targetNode){
    //loop invariant: targetNode has 0 key, 1 child
    /*
    case 0: targetNode==root
    case 1_1_1:parent has 1 key and targetNode is leftchild and rightchild is full
    case 1_1_2:parent has 1 key and targetNode is leftchild and rightchild is not full
    case 1_2_1:parent has 1 key and targetNode is rightchild and leftchild is full
    case 1_2_2:parent has 1 key and targetNode is rightchild and leftchild is not full
    case 2_1_1:parent has more than 1 key and targetNode is lastchild and left sibling is full 
    case 2_1_2:parent has more than 1 key and targetNode is lastchild and left sibling is not full  
    case 2_2_1:parent has more than 1 key and targetNode is not lastchild and right sibling is full
    case 2_2_2:parent has more than 1 key and targetNode is not lastchild and right sibling is not full  
    #lastchild: parent->child[parent->num]==targetNode
    */
   if(targetNode==root){
       root=targetNode->child[0];
       deleteNode(targetNode);
       elementNum--;
       return 0;
   }
   pnode parent=targetNode->parent;
   if(parent->num==1){

       if(parent->child[0]==targetNode){//case 1_1
           pnode sibling=parent->child[1];

           if(sibling->num==3){//1_1_1
                targetNode->val[0]=parent->val[0];
                parent->val[0]=sibling->val[0];
                adoption(targetNode,1,sibling->child[0]);

                int i;
                for(i=0;i<sibling->num-1;i++){
                	sibling->val[i]=sibling->val[i+1];
                    sibling->child[i]=sibling->child[i+1];
                }
                sibling->child[i]=sibling->child[i+1];
                sibling->child[i+1]=NULL;
                sibling->num--;
                return 0;
           }
           else{//1_1_2
                int i=0;
                targetNode->val[0]=parent->val[0];
                for(i;i<sibling->num;i++){
                    targetNode->val[i+1]=sibling->val[i];
                    adoption(targetNode,i+1,sibling->child[i]);
                }
                adoption(targetNode,i+1,sibling->child[i]);
                targetNode->num+=sibling->num;
				deleteNode(sibling);
                parent->child[1]=NULL;
                elementNum--;
                propagation_delete(parent);
           }
       }
       else{// case 1_2
           pnode sibling=parent->child[0];
           if(sibling->num==3){//1_2_1
                targetNode->child[1]=targetNode->child[0];
                targetNode->val[0]=parent->val[0];
                parent->val[0]=sibling->val[sibling->num-1];
                adoption(targetNode,0,sibling->child[sibling->num]);
				sibling->child[sibling->num]=NULL;
                sibling->num--;
                return 0;
           }
           else{//1_2_2
                sibling->num++;
                sibling->val[sibling->num-1]=parent->val[0];
               	adoption(sibling,sibling->num,targetNode->child[0]);
			    deleteNode(targetNode);
                parent->child[1]=NULL;
                elementNum--;
                propagation_delete(parent);
           }
       }
   }
   else{
       if(parent->child[parent->num]==targetNode){//case 2_1 targetNode is last child
           pnode sibling=parent->child[parent->num-1];
           if(sibling->num==3){//case 2_1_1
                targetNode->child[1]=targetNode->child[0];
                adoption(targetNode,0,sibling->child[3]);
				sibling->child[3]=NULL;
                targetNode->val[0]=parent->val[parent->num-1];
                parent->val[parent->num-1]=sibling->val[2];
                sibling->num--;
                return 0;
           }
           else{//2_1_2
                sibling->num++;
                adoption(sibling,sibling->num,targetNode->child[0]);
				sibling->val[sibling->num-1]=parent->val[parent->num-1];
                parent->child[parent->num]=NULL;//cut link between targetNode and parent
                parent->num--;
                deleteNode(targetNode);
                elementNum--;
                return 0;
           }
       }
       else{
           int index=find_index(targetNode);
           pnode sibling=parent->child[index+1];
           if(sibling->num==3){//2_2_1
                targetNode->val[0]=parent->val[index];
                adoption(targetNode,1,sibling->child[0]);
				parent->val[index]=sibling->val[0];
                int i=0;
                for(i;i<2;i++){
                    sibling->val[i]=sibling->val[i+1];
                    sibling->child[i]=sibling->child[i+1];
                }
                sibling->child[i]=sibling->child[i+1];
                sibling->num--;
                return 0;
           }
           else{//2_2_2
                targetNode->num += sibling->num;
                targetNode->val[0]=parent->val[index];
                int i;
                for(i=0;i<sibling->num;i++){
                    targetNode->val[i+1]=sibling->val[i];
                	adoption(targetNode,i+1,sibling->child[i]);
				}
                targetNode->child[i+1]=sibling->child[i];
                //fusion complete
                for(i=index;i<parent->num;i++){
                    parent->val[i]=parent->val[i+1];
                    parent->child[i+1]=parent->child[i+2];
                }
                parent->child[parent->num--]=NULL;
                deleteNode(sibling);
                elementNum--;
                return 0;
           }
       }
   }
}
template <typename _key, typename _value>
int Btree<_key, _value>::deletion(item& k){
    if(elementNum==0){
        return -1;
    }
    else if(elementNum==1){//
        int i=0;
        for(i;i<root->num;i++){
            if(k==root->val[i]){
                delete_simple(root,i);
                if(root->num==0){
                    deleteNode(root);
                    elementNum=0;
                }
                return 0;
            }
        }
        //no such key in tree
        return -1;
    }
    pnode targetLeaf;
    int targetNum;
    search_for_delete(root, k);//find where target node and key is
    if(!(buffer.target)){// tatget key dosen't exist
        return -1;
    }
    else if(isTerminal(buffer.target)){  //special case: successor dosen't exist(target is already Leaf)
		targetLeaf = buffer.target;
        targetNum = buffer.number;
    }
    else{//general case: successor exist
        targetLeaf=find_successor(buffer.target,buffer.number);
        buffer.target->val[buffer.number]=targetLeaf->val[0]; //replace target key with successor key
        targetNum=0;
    }
    //convert "detele problem" into "delete problem in Leaf"
    /*
    special case: Leaf has more than 1 key
    base below: leaf has only one key
    case 1_1_1: parent has more than 1 key, target is last child, Left sibling is full
    case 1_1_2: parent has more than 1 key, target is last child, Left sibling is not full
    case 1_2_1: parent has more than 1 key, target is not last child, right sibling is full
    case 1_2_2: parent has more than 1 key, target is not last child, right sibling is not full
    case 2_1_1: parent has 1 key, target is left child, right child is full
    case 2_1_2: parent has 1 key, target is left child, right child is not full
    case 2_2_1: parent has 1 key, target is right child, left child is full
    case 2_2_2: parent has 1 key, target is right child, left child is not full
    */ 
    if(targetLeaf->num > 1){
		delete_simple(targetLeaf,targetNum);
        return 0;
    }
    else;//targetLeaf->num==1
    pnode tempParent=targetLeaf->parent;
    if(tempParent->num > 1){//case 1: parent->num > 1 => do not need recurrence
        if(tempParent->child[tempParent->num]==targetLeaf){//case 1_1: target is last child of parent
            pnode leftSibling=tempParent->child[tempParent->num-1];
            if(leftSibling->num==3){//case 1_1_1
                targetLeaf->val[0]=tempParent->val[tempParent->num-1];
                tempParent->val[tempParent->num-1]=leftSibling->val[2];
                leftSibling->num--;
                return 0;
            }
            else{//case 1_1_2
                leftSibling->num++;
                leftSibling->val[leftSibling->num-1]=tempParent->val[tempParent->num-1];
                deleteNode(targetLeaf);
                elementNum--;
                tempParent->child[tempParent->num]=NULL;
                tempParent->num--;
                return 0;
            }
          }
        else{ //case 1_2: target is not last child of parent
            int index=find_index(targetLeaf);//tempParent->child[index]==targetLeaf
            pnode rightSibling=tempParent->child[index+1];
            if(rightSibling->num==3){//case 1_2_1
                targetLeaf->val[0]=tempParent->val[index];
                tempParent->val[index]=rightSibling->val[0];
                delete_simple(rightSibling,0);
                return 0;
            }
            else{ //case 1_2_2
                int i=rightSibling->num;
                while(i>0){
                    rightSibling->val[i]=rightSibling->val[i-1];
                    i--;
                }
                rightSibling->val[0]=tempParent->val[index];
                rightSibling->num++;
                deleteNode(targetLeaf);
                elementNum--;
                i=index;
                for(i;i<tempParent->num;i++){
                    tempParent->child[i]=tempParent->child[i+1];
                }
                tempParent->num--;
                i=index;
                for(i;i<tempParent->num;i++){
                    tempParent->val[i]=tempParent->val[i+1];
                }
                return 0;
            }
        }
    }
    else{//case 2: parent has one key propagation start if sibling is not full 
        if(tempParent->child[0]==targetLeaf){ //case 2_1
            pnode sibling=tempParent->child[1];
            if(sibling->num==3){//case 2_1_1
                targetLeaf->val[0]=tempParent->val[0];
                tempParent->val[0]=sibling->val[0];
                int i=0;
                sibling->num--;
                for(i;i<sibling->num;i++){
                    sibling->val[i]=sibling->val[i+1];
                }
                return 0;
            }
            else{//case 2_1_2
                if(sibling->num==1){
                    targetLeaf->val[0]=tempParent->val[0];
                    targetLeaf->val[1]=sibling->val[0];
                    targetLeaf->num=2;
                }
                else{
                    targetLeaf->val[0]=tempParent->val[0];
                    targetLeaf->val[1]=sibling->val[0];
                    targetLeaf->val[2]=sibling->val[1];
                    targetLeaf->num=3;
                }
                deleteNode(sibling);
                elementNum--;
                propagation_delete(T,tempParent);
                return 0;
            }
        }
        else{//case 2_2: targetLeaf is right child
            pnode sibling= tempParent->child[0]; 
            if(sibling->num==3){ //case 2_2_1
                targetLeaf->val[0]=tempParent->val[0];
                tempParent->val[1]=sibling->val[2];
                sibling->num--;
                return 0;
            }
            else{//case 2_2_2
                if(sibling->num==1){
                    sibling->val[1]=tempParent->val[0];
                    sibling->num++;
                }
                else{
                    sibling->val[2]=tempParent->val[0];
                    sibling->num++;
                }
                deleteNode(targetLeaf);
                elementNum--;
                //merge(fusion) complete
                propagation_delete(T,tempParent);
                return 0;
            }
        }
    }
}
template <typename _key, typename _value>
int Btree<_key, _value>::insertion(item* k){  

    if(elementNum==0){
    	root=new node;
    	root->num++;
    	root->val[0] = k;
    	elementNum++;
    	return 0;
	}
    //find leaf node to insert key
    pnode seat = find_seat(root,*k);
	if (!seat){ 
    	//find_seat return NULL when same key already exist
        printf("That key already exist.\n");
        return -1;
    }
    //case: seat is not full => just insert key 
    if (seat->num < 3) {
    	
        switch (seat->num) {
        case 0:// (only root exsit and it is empty)
        	seat->val[0] = k;
        case 1://loop invariant: seat->val[0] is not empty
            if (*(seat->val[0]) < k){
                seat->val[1] = k;
            }
            else{
                seat->val[1] = seat->val[0];
                seat->val[0] = k;
            }
            break;
        case 2://loop invariant: seat->val[0],[1] are not empty
            if (k < seat->val[0]) {
                seat->val[2] = seat->val[1];
                seat->val[1] = seat->val[0];
                seat->val[0] = k;
 
            }
            else if(k < seat->val[1]){
                seat->val[2] = seat->val[1];
                seat->val[1] = k;
            }
            else{
                seat->val[2] = k;
            }
            break;
        }
        seat->num++;
        return 0;
    }
    
    else{  //case: leaf node is already full => need propagation
        item* popped = new item;
        if (k < seat->val[0]){
            
            popped = seat->val[1];
            seat->val[1] = seat->val[0];
            seat->val[0] = k;
        }else if(k < seat->val[1]){
            
            popped = seat->val[1];
            seat->val[1] = k;
        }else if (k < seat->val[2]){
            
            popped = k;
        }else{
            
            popped = seat->val[2];
            seat->val[2] = k;
        }
        
        //new node for split
        pnode newRight = new node;
        
        // number of element increase
        T->elementNum++;
        seat->num = 2; //number of key of splited node is 2
        
        newRight->parent = seat->parent;
        newRight->val[0] = seat->val[2];
        newRight->num = 1;
        
        propagation(seat, newRight, seat->parent, popped); //start propagation in recursive form
        return 0;
    }
}
template <typename _key, typename _value>
int Btree<_key, _value>::propagation(pnode getLeft, pnode getRight, pnode target, item* popped){//target is not leaf
    if (target == NULL) { //child of target is root => we need new node for new root
        
        root = new node;
        elementNum++;
        //new root has 0 key -> propagation end
        insert_as_smaller_than_2(root,popped, getLeft, getRight);
        return true;
    }
    else;

    if (target->num < 3) {
        //target node is not full => propagation end
        insert_as_smaller_than_2(target,popped,getLeft,getRight);
        return true;
    }
    else;

    if (target->num == 3 ) {
        // target node is full => we need to split target node
        //split process is same with split in insert_as_smaller_than_2
        item* new_popped = new item;
        pnode newRight = new node;
        elementNum++;
        target->num = 2;
        newRight->num = 1;
        newRight->parent= target->parent;
        
        if (*popped < target->val[0]){
            // k < val[0] < val[1] < val[2]
            
            new_popped = target->val[1];
            
            newRight->val[0]=target->val[2];
            newRight->child[1]=target->child[3];
            newRight->child[1]->parent=newRight;
            newRight->child[0]=target->child[2];
            newRight->child[0]->parent=newRight;

            target->child[2]=target->child[1];
            target->child[1]=getRight;
            target->val[1]=target->val[0];
            target->val[0]=popped;
            target->val[2]=-1;

        }
		else if(*popped < target->val[1]){
            new_popped = target->val[1];
            
            newRight->val[0]=target->val[2];
            newRight->child[1]=target->child[3];
            newRight->child[1]->parent=newRight;
            newRight->child[0]=target->child[2];
            newRight->child[0]->parent=newRight;

            target->child[2]=getRight;
            target->val[1]=popped;
            target->val[2]=-1;
            
        }
		else if (*popped < target->val[2]){
            new_popped = popped;
            target->child[2] = getLeft;
            
            newRight->child[0] = getRight;
            getRight->parent=newRight;
            newRight->child[1] = target->child[3];
            newRight->child[1]->parent=newRight;
            newRight->val[0]   = target->val[2];
        }
		else{

            new_popped = target->val[2];
            
            newRight->child[0] = getLeft;
            newRight->child[0]->parent=newRight;
            newRight->child[1]= getRight;
            newRight->child[1]->parent=newRight;
            newRight->val[0]  = popped;
            
        }
        propagation(target, newRight, target->parent, new_popped); 
    }
    
    return true;
}
template <typename _key, typename _value>
int Btree<_key, _value>::insert_as_smaller_than_2(pnode target,item* k, pnode getLeft, pnode getRight){
    // target is not leaf -> (if num == 0, then target is root),(getLeft and getRight is not NULL)
    switch (target->num) {
        case 0:
            target->val[0] = k;
            target->child[0] = getLeft;
            target->child[1] = getRight;
            break;
        case 1://loop invariant: target->val[0] is not empty
            if (*(target->val[0]) < k){
                // p :  llp l   lp  m   rp  r   rrp
                //      llp l   gL  k   gR
                target->val[1] = k;
                target->child[1] = getLeft;
                target->child[2] = getRight;
            }
            else{
                target->val[1] = target->val[0];
                target->val[0] = k;
                target->child[2] = target->child[1];
                target->child[1] = getRight;
                target->child[0] = getLeft;
            }
            break;
        case 2://loop invariant: target->val[0],[1] are not empty
            if (*k < target->val[0]) {
                target->val[2] = target->val[1];
                target->val[1] = target->val[0];
                target->val[0] = k;

                target->child[3] = target->child[2];
                target->child[2] = target->child[1];
                target->child[1] = getRight;
                target->child[0] = getLeft;
 
            }
            else if(*k < target->val[1]){
                target->val[2] = target->val[1];
                target->val[1] = k;
                
                target->child[3] = target->child[2];
                target->child[2] = getRight;
                target->child[1] = getLeft;    
            }
            else{
                target->val[2] = k;
                target->child[3] = getRight;
                target->child[2] = getLeft;    
            }
            break;
    }
    target->num++;
    getLeft->parent = target;
    getRight->parent = target;

    return true;
}