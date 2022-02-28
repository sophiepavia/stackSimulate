/*
Sophie Pavia
10/21/20
COP 4530: Homework 3
Stack Adapter Class
*/
template< typename T >
Stack< T >::Stack()
{
	//empty stack  
	data.reserve(0);
}//end stack constructor 

template< typename T >
Stack< T >::~Stack()
{
	clear();

}//end stack destructor

template< typename T >
Stack< T >::Stack(const Stack< T > &rhs)
{
	for(int i = 0; i < rhs.size(); i++)
		data.push_back(rhs.data[i]);
	
}//end copy constructor

template< typename T >
Stack< T >::Stack(Stack< T > &&rhs)
{
	for(int i = 0; i < rhs.size(); i++)
		data.push_back(rhs.data[i]);
		
	rhs.data.clear();
	
} // end move constructor

template< typename T >
Stack< T >& Stack< T >::operator=(const Stack< T > &rhs)
{
	Stack< T > copy = rhs;
	std::swap(*this,copy);
	return *this;
}//end copy assignment operator

template< typename T >
Stack< T >& Stack< T >::operator=(Stack< T > && rhs)
{
	std::swap(data, rhs.data);
	
	return *this;
}//end move assignment operator

template< typename T >
int Stack< T >::size() const
{
	return data.size();
}//end size

template< typename T >
bool Stack< T >::empty() const
{
	return size() == 0;
}//end empty

template< typename T >
void Stack< T >::clear()
{
	data.clear();
}//end clear

template< typename T >
T& Stack< T >::top()
{
	return(data.back());
}//end top

template< typename T >
const T& Stack< T >::top() const
{
	return(data[size()-1]);
}//end const top (accessor)

template< typename T >
void Stack< T >::push(const T& x)
{
	data.push_back(x);
}//end push

template< typename T >
void Stack< T >::push(T && x)
{
	data.push_back(std::move(x));
}//end push move

template< typename T >
void Stack< T >::pop()
{
	data.pop_back();
}//end pop

template< typename T >
void Stack< T >::print(std::ostream& os, char ofc) const
{
	//only print if non empty list 
	if(!empty())
	{	//while more node exist
		for(int i = 0; i < data.size(); i++)
			os << data[i] << ofc;
	}	
}//end print function

template< typename T >
bool operator==(const Stack<T> &lhs, const Stack<T> &rhs)
{
	Stack< T > l = lhs;
	Stack< T > r = rhs;
	if(lhs.size() != rhs.size())
		return false;
	//check for each element that a = b
	for(int i = 0; i < lhs.size(); i++)
	{
		if(l.top() != r.top())
			return false;
		l.pop();
		r.pop();
	}
	return true;
	
}//end operator overload ==

template< typename T >
bool operator!=(const Stack<T> & lhs, const Stack<T> &rhs)
{
	return!(lhs == rhs);
}//end operator overload !=

template <typename T>
std::ostream & operator<<(std::ostream &os, const Stack<T> &a)
{
	a.print(os);
	return os;
}//end operator overload << 

template< typename T >
bool operator<= (const Stack<T>& a, const Stack <T>& b)
{
	Stack< T > a1 = a;
	Stack< T > b1 = a;
	//if a is bigger than b 
	if(a.size() > b.size())
		return false;
	//check each element for a < b	
	for(int i = 0; i < a.size(); i++)
	{
		if(a1.top() > b1.top())
			return false;
		a1.pop();
		b1.pop();
	}
	return true;
}//end operator overload !=