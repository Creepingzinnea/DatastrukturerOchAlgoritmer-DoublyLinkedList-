#include "DoublyLinkedListNode.hpp"

namespace CommonUtilities
{
	template <class T>
	class DoublyLinkedList
	{
	public:
		// Skapar en tom lista
		DoublyLinkedList();

		// Frigör allt minne som listan allokerat
		~DoublyLinkedList();

		// Returnerar antalet element i listan
		int GetSize() const;

		// Returnerar första noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T>* GetFirst();

		// Returnerar sista noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T>* GetLast();

		// Skjuter in ett nytt element först i listan
		void InsertFirst(const T& aValue);

		// Skjuter in ett nytt element sist i listan
		void InsertLast(const T& aValue);

		// Skjuter in ett nytt element innan aNode
		void InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue);

		// Skjuter in ett nytt element efter aNode
		void InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue);

		// Plockar bort noden ur listan och frigör minne. (Det är ok att anta att
	    // aNode är en nod i listan, och inte från en annan lista)
		void Remove(DoublyLinkedListNode<T>* aNode);

		// Hittar första elementet i listan som har ett visst värde. Jämförelsen
	    // görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T>* FindFirst(const T& aValue);

		// Hittar sista elementet i listan som har ett visst värde. Jämförelsen
	    // görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T>* FindLast(const T& aValue);

		// Plockar bort första elementet i listan som har ett visst värde. 
	    // Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
	    // Returnerar true om ett element plockades bort, och false annars.
		bool RemoveFirst(const T& aValue);

		// Plockar bort sista elementet i listan som har ett visst värde.
	    // Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
	    // Returnerar true om ett element plockades bort, och false annars.
		bool RemoveLast(const T& aValue);


	private:
		DoublyLinkedListNode<T>* myFirst;
		DoublyLinkedListNode<T>* myLast;
		int mySize;

		void InsertFirstNode(DoublyLinkedListNode<T>* aNode);

	};

	template<class T>
	inline DoublyLinkedList<T>::DoublyLinkedList()
	{
		myFirst = nullptr;
		myLast = nullptr;

		mySize = 0;
	}

	template<class T>
	inline DoublyLinkedList<T>::~DoublyLinkedList()
	{
		//release memory
		DoublyLinkedListNode<T>* listPtr = myFirst;

		while (listPtr)
		{

			DoublyLinkedListNode<T>* tempNode = listPtr->myNext;
			delete listPtr;
			listPtr = tempNode;

			mySize--;
		}
		myFirst = myLast = nullptr;
	}

	template<class T>
	inline int DoublyLinkedList<T>::GetSize() const
	{
		return mySize;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::GetFirst()
	{
		return myFirst;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::GetLast()
	{
		return myLast;
	}

	template<class T>
	inline void CommonUtilities::DoublyLinkedList<T>::InsertFirstNode(DoublyLinkedListNode<T>* aNode)
	{
		//ge ett bättre namn

		myFirst = aNode; //myFirst pekar på newNode
		myLast = aNode;  //myLast pekar på newNode
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertFirst(const T& aValue)
	{

		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);

		//listan är tom
		if (myFirst == nullptr)
		{
			InsertFirstNode(newNode);
		}
		else
		{
			myFirst->myPrevious = newNode; //pekaren innan my first pekar på newNode
			newNode->myNext = myFirst; //pekaren efter newNode pekar på myFirst
			myFirst = newNode; //New node är nu först i listan

		}

		mySize++;
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);

		//listan är tom
		if (myFirst == nullptr)
		{
			InsertFirstNode(newNode);
		}
		else
		{
			myLast->myNext = newNode;
			newNode->myPrevious = myLast;
			myLast = newNode;
		}

		mySize++;
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue)
	{
		if (aNode == nullptr)
		{
			return;
		}



		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);

		if (aNode == myFirst)
		{
			myFirst = newNode; //första pekar på newNode
		}

		newNode->myNext = aNode;
		newNode->myPrevious = aNode->myPrevious;

		// If aNode has a previous node, update its next pointer to newNode
		if (aNode->myPrevious != nullptr)
		{
			aNode->myPrevious->myNext = newNode;
		}

		aNode->myPrevious = newNode;



		mySize++;
	}

	template<class T>
	inline void DoublyLinkedList<T>::InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue)
	{
		if (aNode == nullptr)
		{
			return;
		}



		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);

		if (aNode == myLast)
		{
			myLast = newNode;
		}

		newNode->myPrevious = aNode;
		newNode->myNext = aNode->myNext;

		// If aNode has a next node, update its last pointer to newNode
		if (aNode->myNext != nullptr)
		{
			aNode->myNext->myPrevious = newNode;
		}

		aNode->myNext = newNode;



		mySize++;
	}

	template<class T>
	inline void DoublyLinkedList<T>::Remove(DoublyLinkedListNode<T>* aNode)
	{
		if (aNode == nullptr)
		{
			return;
		}


		if (aNode->myPrevious != nullptr)
		{
			aNode->myPrevious->myNext = aNode->myNext;
		}
		if (aNode->myNext != nullptr)
		{
			aNode->myNext->myPrevious = aNode->myPrevious;
		}
		//If aNode is the first node
		if (aNode == myFirst)
		{
			// Gör så att aNode som är myFirst, blir den de pekar på. myNext blir myFirst och aNode försvinner.
			myFirst = aNode->myNext;
		}
		//If aNode is the last node
		if (aNode == myLast)
		{
			myLast = aNode->myPrevious;
		}

		delete aNode;
		mySize--;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::FindFirst(const T& aValue)
	{
		if (!myFirst)
		{
			return myFirst;
		}

		DoublyLinkedListNode<T>* listPtr = myFirst;

		while (listPtr)
		{
			if (listPtr->GetValue() == aValue)
			{
				return listPtr;
			}

			listPtr = listPtr->GetNext();

		}
		return nullptr;
	}

	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedList<T>::FindLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* listPtr = myLast;

		while (listPtr)
		{
			if (listPtr->GetValue() == aValue)
			{
				return listPtr;
			}

			listPtr = listPtr->GetPrevious();

		}
		return nullptr;
	}

	template<class T>
	inline bool DoublyLinkedList<T>::RemoveFirst(const T& aValue)
	{
		DoublyLinkedListNode<T>* listPtr = FindFirst(aValue);
		if (listPtr)
		{
			Remove(listPtr);
			return true;
		}
		else
		{
			return false;
		}


	}

	template<class T>
	inline bool DoublyLinkedList<T>::RemoveLast(const T& aValue)
	{
		DoublyLinkedListNode<T>* listPtr = FindLast(aValue);
		if (listPtr)
		{
			Remove(listPtr);
			return true;
		}
		else
		{
			return false;
		}


	}

}

