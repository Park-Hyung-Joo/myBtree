# myBtree
refactoring c code assignment for b-tree into c++ code to use as my personal library

main concept is simillar with map in c++ standart library

API:

  insert(std::pair(key, value))
  
     same with insert in map
    
  pop(key)
  
     remove a node corresponding to key
    
     if there is no node with that key, return false, else return true
    
  find(key)
  
     return pointer of the value corresponding to key
    
     if there isn't, return nullptr
    
  empty()
  
     return either empty or not
    
  size()
  
     return number of nodes in tree
    
  clear()
  
     remove every nodes in tree
  
