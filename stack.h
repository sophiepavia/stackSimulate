#ifndef DL_STACK_H
#define DL_STACK_H
#include <vector>

namespace cop4530 {

template <typename T>
	class Stack {			
		public:
			// constructor, desctructor, copy constructor
			Stack();					// default zero parameter constructor
			~Stack ();					//deconstructor
			Stack (const Stack<T>&rhs); 	//copy constructor 
			Stack(Stack<T> &&rhs);			//move constructor
			
			//copy assignment operator
			Stack<T>& operator= (const Stack <T>&rhs);
			
			//move assignment operator
			Stack<T> & operator=(Stack<T> &&rhs);
			
			//member functions
			int size() const;			//returns num of elements in stack
			bool empty() const;			//checks if stack is empty 
			void clear();				//clears stack
			
			T& top();					//returns reference to first element (can change)
			const T& top() const;		//accessor to top (can't modify) 
			
			void push(const T& x);		//add x to stack (copy)
			void push(T && x);			//add x to stack (move)
			void pop();					//removes top element
			
			// print out all elements. ofc is deliminitor
			void print(std::ostream& os, char ofc = ' ') const;		
			
		
		private:
			std::vector<T> data;		//container of stack
			
		};

		// overloading comparison operators
		template <typename T>
			bool operator== (const Stack<T>&lhs, const Stack <T>&rhs);
			
		template <typename T>
			bool operator!= (const Stack<T>&lhs, const Stack <T>&rhs);
			
		// overloading output operator
		template <typename T>
			std::ostream& operator<< (std::ostream& os, const Stack<T>& a);
			
		template <typename T>	
			bool operator<= (const Stack<T>& a, const Stack <T>& b);
		
// include the implementation file here

#include "stack.hpp"

} // end of namespace 4530

#endif
