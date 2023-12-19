#ifndef VECTOR_H
#define VECTOR_H

// VecIterator class template definition
template< typename T >
class VecIterator
{
public:
   VecIterator( T *p = nullptr ) // default constructor
      : ptr( p )
   {
   }

   VecIterator( const VecIterator &iteratorToCopy ) // copy constructor
      : ptr( iteratorToCopy.ptr )
   {
   }

   ~VecIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const VecIterator &operator=( const VecIterator &right )
   {
      if( &right != this ) // avoid self-assignment
         ptr = right.ptr;
      return *this; // enables x = y = z, for example
   }

   bool operator==( const VecIterator &right ) const // equal to
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VecIterator &right ) const // not equal to
   {
      return ptr != right.ptr;
   }

   T& operator*() const // dereferencing operator
   {
      return *ptr;
   }

   T* operator->() const
   {
      return ptr;
   }

   VecIterator& operator++() // prefix increment operator
   {
      ++ptr;
      return *this;
   }

private:
   T *ptr = nullptr; // keep a pointer to vector
}; // end class template VecIterator

// vector class template definition
template< typename T >
class vector
{
public:
   using iterator = VecIterator< T >;

   vector(); // Default constructor

   // Copy constructor; Constructs a vector with a copy of each of the elements in x.
   vector( const vector &x );

   ~vector(); // Destroys the vector.

   const vector& operator=( const vector &x ); // assignment operator

   // Returns a pointer pointing to the first element in the vector.
   // If the vector is empty, the returned pointer shall not be dereferenced.
   iterator begin() const;

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   unsigned int size() const;

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   unsigned int capacity() const;

   // subscript operator for non-const objects returns modifiable lvalue
   T& operator[]( unsigned int n );

   // subscript operator for const objects returns rvalue
   const T& operator[]( unsigned int n ) const;

   // Adds a new element at the end of the vector,
   // after its current last element.
   // The content of val is copied to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const T val );

private:
   T *myFirst = nullptr;
   T *myLast = nullptr;
   T *myEnd = nullptr;
}; // end class template vector


// Default constructor
template< typename T >
vector< T >::vector()
{

}

// copy constructor; constructs a vector with a copy of each of the elements in x
template< typename T >
vector< T >::vector( const vector< T > &x )
{
	myFirst = new T[x.capacity()]();
	for (int i = 0; i < x.size(); i++){
		myFirst[i] = x.myFirst[i];
	}
	myLast = myFirst + x.size();
	myEnd = myFirst + x.capacity();
} // end vector copy constructor

// destructor; destroys the vector
template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const vector< T >& vector< T >::operator=( const vector< T > &x )
{
	if (myFirst != nullptr){
		delete[] myFirst;
	}
	myFirst = new T[x.capacity()]();
	for (int i = 0; i < x.size(); i++){
		*(myFirst + i) = *(x.myFirst + i);
	}
	myLast = myFirst + x.size();
	myEnd = myFirst + x.capacity();
	return *this;
} // end function operator=

template< typename T >
typename vector< T >::iterator vector< T >::begin() const
{
   return iterator( myFirst );
}

template< typename T >
typename vector< T >::iterator vector< T >::end() const
{
   return iterator( myLast );
}

template< typename T >
unsigned int vector< T >::size() const
{
   return ( myLast - myFirst );
}

template< typename T >
unsigned int vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
template< typename T >
T& vector< T >::operator[]( unsigned int n )
{
	return myFirst[n];
}

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
template< typename T >
const T& vector< T >::operator[]( unsigned int n ) const
{
	return myFirst[n];
}

template< typename T >
void vector< T >::push_back( const T val )
{
	if (capacity() == 0){
		myFirst = new T[1]();
		myLast = myEnd = myFirst + 1;
		myFirst[0] = val;
	} else if (myLast == myEnd){
		T *tempPtr = myFirst;

		int length = capacity() + 1;
		int oldSize = size();

		myFirst = new T[length]();
		for (int i = 0; i < oldSize; i++){//複製數據到新陣列
			myFirst[i] = tempPtr[i];
		}
		myFirst[oldSize] = val;
		myLast = myFirst + oldSize + 1;
		myEnd = myFirst + length;

		delete[] tempPtr;
	} else if (myLast < myEnd){
		myFirst[size()] = val;
		myLast++;
	}
}

#endif