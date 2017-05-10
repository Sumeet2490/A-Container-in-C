#include<stdlib.h>
#include<string.h>
using namespace std;

#ifndef DEQUE_H
#define DEQUE_H

#define Deque_DEFINE(T)															\
struct Deque_##T;															\
																	\
	/* Represents an Iterator for a container */											\
	struct Deque_##T##_Iterator {													\
																	\
		T *current;														\
		T *min;															\
		T *max;															\
																	\
		/* function pointers*/													\
		void (*inc)(Deque_##T##_Iterator *);											\
		void (*dec)(Deque_##T##_Iterator *);											\
		T& (*deref)(Deque_##T##_Iterator *);											\
	};																\
																	\
	/* Increment iterator's current_size; wraps when reaches max end */								\
	void inc(Deque_##T##_Iterator* iter)												\
	{																\
		if(iter->current == iter->max)												\
		{															\
			iter->current =  iter->min;											\
		} else															\
		{															\
			iter->current++;												\
		}															\
	}																\
																	\
	/* Decrement iterator's current_size */												\
	/* It current position is the minmum, then wrap around */									\
	void dec(Deque_##T##_Iterator *iter)												\
	{																\
		if(iter->current == iter->min)												\
		{															\
			iter->current =  iter->max;											\
		}															\
		else															\
		{															\
			iter->current--;												\
		}															\
	}																\
																	\
	/* Returns the element currently being pointed by the Iterator */								\
	T& deref(Deque_##T##_Iterator* iter)												\
	{																\
		return *(iter->current);												\
	}																\
																	\
	/* Represents a Double-ended queue container */											\
	struct Deque_##T {														\
																	\
		T *aDEQ;														\
		int frnt;														\
		int rear;														\
		int current_size;													\
		int capacity;														\
		char type_name[sizeof("Deque_"#T)] = "Deque_"#T;									\
																	\
		/* function pointers*/													\
		bool (*comparator_##T)(const T&, const T&);										\
		struct Deque_##T##_Iterator it_begin;											\
		struct Deque_##T##_Iterator it_end;											\
		void (* dtor)(Deque_##T *);												\
		int (*size)(Deque_##T *);												\
		bool (*empty)(Deque_##T *);												\
		void (*push_back)(Deque_##T *, T);											\
		void (*push_front)(Deque_##T *, T);											\
		T& (*front)(Deque_##T *);												\
		T& (*back)(Deque_##T *);												\
		void (*pop_front)(Deque_##T *);												\
		void (*pop_back)(Deque_##T *);												\
		T& (*at)(Deque_##T *, int);												\
		void (*clear)(Deque_##T *);												\
		Deque_##T##_Iterator& (*begin)(Deque_##T *);										\
		Deque_##T##_Iterator& (*end)(Deque_##T *);										\
		void (*sort)(Deque_##T*, Deque_##T##_Iterator, Deque_##T##_Iterator);							\
	};																\
																	\
	/* Represents a container element to be sorted */										\
	struct Container_##T {														\
																	\
		T container_element;													\
		bool (*container_element_comparator)(const T& o1, const T& o2);								\
	};																\
																	\
	/* Comparator for the qsort function, calls the the compare function passed via the constructor */				\
	int comparatorForQsort_##T(const void* o1, const void* o2)									\
	{																\
																	\
		struct Deque_##T Deq;													\
																	\
		struct Container_##T *obj1 = (struct Container_##T*) o1;								\
		struct Container_##T *obj2 = (struct Container_##T*) o2;								\
					 												\
		bool result = obj1->container_element_comparator(obj2->container_element, obj1->container_element);			\
																	\
		if(result)														\
		{															\
			return 1;													\
		}															\
		else															\
		{															\
			return 0;													\
		}															\
	}																\
																	\
	/* Compares two iterators for their current and returns the result */								\
	bool Deque_##T##_Iterator_equal(Deque_##T##_Iterator iter1, Deque_##T##_Iterator iter2)						\
	{																\
		if(iter1.current == iter2.current)											\
		{															\
			return true;													\
		}															\
		return false;														\
	}																\
																	\
	/* Sorts the DEQ contents from Iter1 to Iter2 */										\
	void sort(Deque_##T *Deq, Deque_##T##_Iterator iter1, Deque_##T##_Iterator iter2)						\
	{																\
																	\
		/* make a copy now to reset the iterators to original position later */							\
		Deque_##T##_Iterator iter1_copy = iter1;										\
		Deque_##T##_Iterator iter2_copy = iter2;										\
																	\
		/* a loop to get the number of elements to be sorted */									\
		int counter = 0;													\
		for(counter = 0; !Deque_##T##_Iterator_equal(iter1, iter2); counter++)							\
		{															\
			iter1.inc(&iter1);												\
		}															\
																	\
		/* Reset iter1 */													\
		iter1 = iter1_copy;													\
																	\
		T *DeqCopyForSort = (T*) malloc(sizeof(T) * counter);									\
																	\
		for(int i = 0; i < counter; i++)											\
		{															\
			DeqCopyForSort[i] = iter1.deref(&iter1);									\
			iter1.inc(&iter1);												\
		}															\
																	\
		struct Container_##T *toSort = (struct Container_##T*) malloc(sizeof(struct Container_##T) * counter);			\
																	\
		for(int i = 0; i < counter; i++)											\
		{															\
			toSort[i].container_element = DeqCopyForSort[i];								\
			toSort[i].container_element_comparator = Deq->comparator_##T;							\
		}															\
																	\
		/* reset iter1 */													\
		iter1 = iter1_copy;													\
																	\
		qsort(toSort, counter, sizeof(struct Container_##T), comparatorForQsort_##T);						\
																	\
		for(int i=0; i < counter; i++) {											\
																	\
			*iter1.current = toSort[i].container_element;									\
			/*printf("sorted -> %d\n", *iter1.current);*/									\
			iter1.inc(&iter1);												\
		   															\
       		}															\
																	\
		free(DeqCopyForSort);													\
		free(toSort);														\
	}																\
																	\
	/* Doubles the capacity of DEQ, copies all elements temporarily */								\
	/* Sets the indexes to appropriate values and copies back all elements to DEQ */ 						\
	void resizeDeque(Deque_##T *Deq)												\
	{																\
		int new_capacity = Deq->capacity * 2;											\
		T* tempDEQ = (T*) malloc(sizeof(T) * new_capacity);									\
		int i = 0, j = 0;													\
																	\
		for(i = Deq->frnt; i < Deq->capacity; i++)										\
		{															\
			tempDEQ[j] = Deq->aDEQ[i];											\
			j++;														\
		}															\
																	\
		for(i = 0; i < Deq->frnt; i++)												\
		{															\
			tempDEQ[j]=Deq->aDEQ[i];											\
			j++;														\
		}															\
		Deq->frnt = 0;														\
		Deq->rear = j;														\
		Deq->capacity = new_capacity;												\
		free(Deq->aDEQ);													\
		Deq->aDEQ = tempDEQ;													\
	}																\
																	\
	/* Returns the current size of the DEQ */											\
	int size(Deque_##T *Deq) {													\
		return Deq->current_size;												\
	}																\
																	\
	/* Returns True if the current size is 0 */											\
	bool empty(Deque_##T *Deq) {													\
																	\
  		if(Deq->current_size == 0)												\
		{															\
			return true;													\
		}															\
		else															\
		{															\
			return false;													\
		}															\
	}																\
																	\
	/* Pushes the value to the BACK of the DEQ */											\
	void push_back(Deque_##T *Deq, T value) {											\
																	\
		/* Resize the DEQ if required */											\
		/* printf("max cap: %d", (Deq->rear) % Deq->capacity);	*/								\
		if((!Deq->empty(Deq)) && (Deq->frnt == (Deq->rear) % Deq->capacity))							\
		{															\
			resizeDeque(Deq);												\
		}															\
																	\
		/* Add element at the rear and increment rear */									\
  		Deq->aDEQ[Deq->rear++] = value;												\
																	\
		/* Set rear to 0 if it reaches max size of the Circular queue */							\
		if(Deq->rear == Deq->capacity)												\
		{															\
			Deq->rear = 0;													\
		}															\
																	\
		/* Increment the current size */											\
		Deq->current_size++;													\
	}																\
																	\
	/* Pushes the value to the FRONT of the DEQ */											\
	void push_front(Deque_##T *Deq, T value)											\
	{																\
		/* Resize the DEQ if required */											\
		/*printf("max cap: %d", (Deq->rear) % Deq->capacity); */								\
		if((!Deq->empty(Deq)) && (Deq->frnt == (Deq->rear) % Deq->capacity)) {							\
			resizeDeque(Deq);												\
		}															\
																	\
		if(Deq->empty(Deq))													\
		{															\
			Deq->rear++;													\
		} 															\
		else															\
		{															\
			Deq->frnt--;													\
		}															\
																	\
		if(Deq->frnt < 0)													\
		{															\
			Deq->frnt = Deq->capacity - 1;											\
		}															\
		if(Deq->rear == Deq->capacity)												\
		{															\
			Deq->rear = 0;													\
		}															\
																	\
		/* add the value and increment the current size */									\
		Deq->aDEQ[Deq->frnt] = value;  												\
		Deq->current_size++;													\
	}																\
																	\
	/* Returns the element at the FRONT of the DEQ */										\
	T& front(Deque_##T *Deq) {													\
		return Deq->aDEQ[Deq->frnt];												\
	}																\
																	\
	/* Returns the element at the BACK of the DEQ */										\
	T& back(Deque_##T *Deq) {													\
		if(Deq->rear == 0) {													\
			return Deq->aDEQ[Deq->capacity - 1]; 										\
		}															\
		return Deq->aDEQ[Deq->rear - 1];											\
	}																\
																	\
	/* Removes the element at the BACK of the DEQ */										\
	void pop_back(Deque_##T *Deq)													\
	{																\
		if(!Deq->empty(Deq))													\
		{															\
  			Deq->rear--;													\
			if(Deq->rear < 0)												\
			{														\
				Deq->rear = Deq->capacity - 1;										\
			}														\
			Deq->current_size--;												\
		}															\
	}																\
																	\
	/* Removes the element at the FRONT of the DEQ */										\
	void pop_front(Deque_##T *Deq)													\
	{																\
		if(!Deq->empty(Deq))													\
		{															\
			Deq->frnt++;													\
			if(Deq->frnt == Deq->capacity)											\
			{														\
				Deq->frnt = 0;												\
			}														\
			Deq->current_size--;												\
		}															\
	}																\
																	\
	/* Returns the element at the 'i'th position of the DEQ */									\
	T& at(Deque_##T *Deq, int i) {													\
																	\
		int position = 0;													\
		if(Deq->frnt + i >= Deq->capacity)											\
		{															\
			position = Deq->frnt + i - Deq->capacity;									\
		}															\
		else															\
		{															\
			position = Deq->frnt + i;											\
		}															\
																	\
		return Deq->aDEQ[position];												\
	}																\
																	\
	/* Clears the DEQ */														\
	void clear(Deque_##T *Deq) {													\
  		Deq->frnt = 0;														\
		Deq->rear = 0;														\
		Deq->current_size = 0;													\
	}																\
																	\
	/* Returns an Iterator pointing it to the start of the DEQ*/									\
	Deque_##T##_Iterator& begin(Deque_##T *Deq)											\
	{																\
		Deq->it_begin.min =  &Deq->aDEQ[0];											\
		Deq->it_begin.max =  &Deq->aDEQ[Deq->capacity - 1];									\
		Deq->it_begin.current = &Deq->aDEQ[Deq->frnt];										\
		return Deq->it_begin;													\
	}																\
																	\
	/* Returns an Iterator pointing it to the end of the DEQ*/									\
	Deque_##T##_Iterator& end(Deque_##T *Deq)											\
	{																\
		Deq->it_end.min =  &Deq->aDEQ[0];											\
		Deq->it_end.max =  &Deq->aDEQ[Deq->capacity - 1];									\
		Deq->it_end.current =  &Deq->aDEQ[Deq->rear];										\
		return Deq->it_end;													\
	}																\
																	\
	/* If the number or elements in both the DEQ's are unequal, then return false */						\
	/* Else traverse both the DEQs, return false for the first mismatch, else at the end return true */				\
	bool Deque_##T##_equal(Deque_##T &Deq1, Deque_##T &Deq2)									\
	{																\
  		if(Deq1.current_size != Deq2.current_size)										\
		{															\
  			return false;													\
  		}															\
																	\
		for(int i = 0; i < Deq1.current_size; i++)										\
		{															\
			if((Deq1.comparator_##T(Deq1.at(&Deq1,i), Deq2.at(&Deq2,i)) || Deq1.comparator_##T(Deq2.at(&Deq2,i), Deq1.at(&Deq1,i))))		\
			{														\
				return false;												\
			}														\
		}															\
  		return true;														\
	}																\
																	\
	/* Destructor for the DEQ, frees the dynamic array */										\
	void dtor(Deque_##T *Deq) {													\
  		free(Deq->aDEQ);													\
	}																\
																	\
	/* Destructor for the DEQ,initialises book-keeping info and all the pointers to functions */					\
	void  Deque_##T##_ctor(Deque_##T *Deq, bool (*Fptr_comparator)(const T& t1, const T& t2))					\
	{																\
																	\
		Deq->frnt = 0;														\
		Deq->rear = 0;														\
		Deq->capacity = 10000;													\
		Deq->current_size = 0;													\
	  	Deq->aDEQ = (T*) malloc(sizeof(T) * Deq->capacity);									\
		strcpy(Deq->type_name, "Deque_"#T);											\
																	\
		/* initilaise the function pointers*/											\
		Deq->comparator_##T = Fptr_comparator;											\
		Deq->dtor = dtor;													\
		Deq->size = size;													\
		Deq->clear = clear;													\
		Deq->empty = empty;													\
		Deq->push_back = push_back;												\
		Deq->push_front = push_front;												\
		Deq->pop_front = pop_front;												\
		Deq->pop_back = pop_back;												\
		Deq->front = front;													\
		Deq->back = back;													\
		Deq->at = at;														\
		Deq->begin = begin;													\
		Deq->end = end;														\
		Deq->it_begin.inc = inc;												\
		Deq->it_begin.dec = dec;												\
		Deq->it_begin.deref = deref;												\
		Deq->it_end.inc = inc;													\
		Deq->it_end.dec = dec;													\
		Deq->it_end.deref = deref;												\
		Deq->sort = sort;													\
	}																\

#endif
