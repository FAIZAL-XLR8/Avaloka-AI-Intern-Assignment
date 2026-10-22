//PROBLEM-1
/*
LRU-Cache:
Implemented the LRU Cache question with a combo of unordered_map and doubly linked list to achieve average O(1) Time Complexity for both get and put operations;
Approach :
According to ques I needed to store key, value pairs and should also be able to return values quickly and also removal and insertion should be fast because of get and put ops must be O(1).We need to also maintain an order of usage effectively .An array/list wouldnt have sufficed because array searches and removes a key in worst case O(n) time.
So 1) fast access to return values quickly --> use unordered_map : returns values quickly in O(1) time which will store each key's value
2)Maintaining an order of usage where access is a specific key is not O(n) --> use doubly linked list where a node after a dummy head would represent most recently used and at the tail would be least recently used.Whenever an entry is accessed I move the node to front and removes the last node before dummy tail to remove when we reach the capacity

Handling get operation:
when a key is accessed first we see in my if it exists in map or not if it doesnt then we return -1 since no node was inserted in between two dummy nodes.Otherwise if it does exist then we retrive the node directly from its current position and then move it to the front and the nodes before and after that node's position are joined with each other

Handling the put operation : 
When inserting I considered 2 possibility
If key already exists in map -->update value and move node to front
If key is new and cache reached its capacity then remove least recently used from tail and remove from map too, otherwise just add at front and update the map for newly added node;

Constraints :
Overall T.C = O(1) and space complexity is O(C) due to map;
Conclusion : choose this comobo becuase map is fast lookup giving O(1) while doubly linked list provides efficient ordering and eviction problem which is also O(1).
*/
class LRUCache {
public:
class DoublyList {
    public : 
    DoublyList* next;
    DoublyList* prev;
    int key;
    int val;
    DoublyList(int key, int val)
    {
        this -> key = key;
        this -> val = val;
        this -> next = NULL;
        this -> prev = NULL;
    }
};
unordered_map<int,DoublyList*> mp;
DoublyList* head;
DoublyList* tail;
//least recently used will be before tail and most recently used after head
int capacity_;
    void deleteNode (DoublyList* node)
    {
        DoublyList* prev_node = node -> prev;
        DoublyList* after_node = node -> next;
        prev_node -> next = after_node;
        after_node ->prev = prev_node;

    }
    void addAtHead (DoublyList* node)
    {
        DoublyList* after_node = head->next;
        head -> next = node;
        node -> prev = head;
        after_node -> prev = node;
        node -> next = after_node;
    }
    LRUCache(int capacity) {
        head = new DoublyList (-1, -1);
        tail = new DoublyList (-1, -1);
        head -> next = tail;
        tail -> prev = head;
        capacity_ = capacity;
    }
    
    int get(int key) {
        if (!mp.count(key)) return -1;
        deleteNode(mp[key]);
        addAtHead(mp[key]);
        return mp[key] ->val;
    }
    
    void put(int key, int value) {
       if (mp.count(key))
       {
        deleteNode(mp[key]);
        
        mp[key]->val = value;
        addAtHead (mp[key]);
       }
       else
       {
         DoublyList* new_node = new DoublyList(key, value);
        if (mp.size() == capacity_)
        {
            DoublyList* to_be_del = tail -> prev;
            deleteNode(to_be_del);
            mp.erase(to_be_del->key);
            addAtHead(new_node);
        }
        else
        {
            addAtHead(new_node);
           
        }
         mp[key] = new_node;
       }
    }
};

