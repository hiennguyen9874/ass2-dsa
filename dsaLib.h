/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>

using namespace std;


class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T> *pNext;
	L1Item() : pNext(NULL) {}
	L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
	L1Item<T>   *_pHead;// The head pointer of linked list
	L1Item<T>   *_pTail;
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List();

	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	//T&      at(int i);
	T&      operator[](int i);

	bool    find(T& a, int& idx);
	T*      find(T& a);
	//T*      findLast(T& a);
	//int     insert(int i, T& a);
	//int     remove(int i);
	//int     removeAll(T& a);

	int     push_back(T& a);
	int     insertHead(T& a);

	int     removeHead();
	int     removeLast();

	void    reverse();

	void    traverse(void(*op)(T&)) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, void*), void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}
	L1Item<T> *get_Head()
	{
		return _pHead;
	}

	L1Item<T> *get_Tail(L1Item<T> *cur)
	{
		while (cur != NULL && cur->pNext != NULL)
		{
			cur = cur->pNext;
		}
		return cur;
	}

	L1Item<T> *partition(L1Item<T> *head, L1Item<T> *end, L1Item<T> **newHead, L1Item<T> **newEnd);

	L1Item<T> *quickSortRecur(L1Item<T> *head, L1Item<T> *end);

	void quickSort()
	{
		L1Item<T> **headRef = &_pHead;
		(*headRef) = quickSortRecur(*headRef, get_Tail(*headRef));
		return;
	}
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = _pTail = new L1Item<T>(a);
	}
	else {
		L1Item<T>   *p = new L1Item<T>(a);
		_pTail->pNext = p;
		_pTail = p;
	}

	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}

// Dao nguoc list
template<class T>
void L1List<T>::reverse()
{
	L1Item<T> *prev = NULL;
	L1Item<T> *current = _pHead;
	L1Item<T> *next = NULL;
	while (current)
	{
		next = current->pNext;
		current->pNext = prev;
		prev = current;
		current = next;
	}
	_pHead = prev;
}

template<class T>
 void L1List<T>::clean()
{
	while (_pHead)
	{
		L1Item<T>*p = _pHead;
		_pHead = _pHead->pNext;
		delete p;
		_size --;
	}
}
// Huy list
template<class T>
L1List<T>::~L1List()
{
	while (_pHead)
	{
		L1Item<T>*p = _pHead;
		_pHead = _pHead->pNext;
		delete p;
		_size--;
	}
}

// Dinh nghia ham truy xuat phan tu
template<class T>
T & L1List<T>::operator[](int i)
{
	L1Item<T> *p = _pHead;
	while (p && i > 0)
	{
		p = p->pNext;
		i--;
	}
	return p->data;
}

// Tim kiem trong list
template<class T>
bool L1List<T>::find(T & a, int & idx)
{
	int i = 0;
	L1Item<T> *p = _pHead;
	while (p)
	{
		if (p->data == a)
		{
			idx = i;
			return true;
		}
		i++;
		p = p->pNext;
	}
	return false;
}

// Tim kiem trong list
template<class T>
T * L1List<T>::find(T & a)
{
	L1Item<T> *p = _pHead;
	while (p)
	{
		if (p->data == a)
			return p->data;
		p = p->pNext;
	}
	return NULL;
}

template<class T>
L1Item<T>* L1List<T>::partition(L1Item<T>* head, L1Item<T>* end, L1Item<T>** newHead, L1Item<T>** newEnd)
{
	L1Item<T> *pivot = end;
	L1Item<T> *prev = NULL, *cur = head, *tail = pivot;

	while (cur != pivot)
	{
		if (cur->data < pivot->data)
		{

			if ((*newHead) == NULL)
				(*newHead) = cur;

			prev = cur;
			cur = cur->pNext;
		}
		else
		{

			if (prev)
				prev->pNext = cur->pNext;
			L1Item<T> *tmp = cur->pNext;
			cur->pNext = NULL;
			tail->pNext = cur;
			tail = cur;
			cur = tmp;
		}
	}

	if ((*newHead) == NULL)
		(*newHead) = pivot;

	(*newEnd) = tail;

	return pivot;
}

template<class T>
L1Item<T>* L1List<T>::quickSortRecur(L1Item<T>* head, L1Item<T>* end)
{
	if (!head || head == end)
		return head;

	L1Item<T> *newHead = NULL, *newEnd = NULL;

	L1Item<T> *pivot = partition(head, end, &newHead, &newEnd);


	if (newHead != pivot)
	{
		L1Item<T> *tmp = newHead;
		while (tmp->pNext != pivot)
			tmp = tmp->pNext;
		tmp->pNext = NULL;

		newHead = quickSortRecur(newHead, tmp);

		tmp = get_Tail(newHead);
		tmp->pNext = pivot;
	}

	pivot->pNext = quickSortRecur(pivot->pNext, newEnd);

	return newHead;
}

/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
	T           _data;
	AVLNode<T>   *_pLeft, *_pRight;

	int         _bFactor;
	AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0) {}
};

template <class T>
class AVLTree {
	AVLNode<T> *_pRoot;
public:
	AVLTree() : _pRoot(NULL) {}
	~AVLTree() { destroy(_pRoot); }

	bool find(T& key, T* &ret) { return find(_pRoot, key, ret); }
	bool insert(T& key) { return insert(_pRoot, key); }
	bool remove(T& key) { return remove(_pRoot, key); }
	void traverseNLR(void(*op)(T&)) { traverseNLR(_pRoot, op); }
	void traverseLNR(void(*op)(T&)) { traverseLNR(_pRoot, op); }
	void traverseLRN(void(*op)(T&)) { traverseLRN(_pRoot, op); }

	// Ham tu tao
	void traverseRNL(void(*op)(T&)) { traverseRNL(_pRoot, op); }
	void traverseMinMaxLNR(T &min, T &max, void(*op)(T&)) { traverseMinMaxLNR(_pRoot, min, max, op); }
	T& getRoot() {
		return _pRoot->_data;
	}

protected:
	void destroy(AVLNode<T>* &pR);
	bool find(AVLNode<T> *pR, T& key, T* &ret);
	bool insert(AVLNode<T>* &pR, T& a);
	bool remove(AVLNode<T>* &pR, T& a);
	void traverseNLR(AVLNode<T> *pR, void(*op)(T&));
	void traverseLNR(AVLNode<T> *pR, void(*op)(T&));
	void traverseLRN(AVLNode<T> *pR, void(*op)(T&));

	void rotLeft(AVLNode<T>* &pR);
	void rotRight(AVLNode<T>* &pR);
	void rotLR(AVLNode<T>* &pR);
	void rotRL(AVLNode<T>* &pR);

	bool balanceLeft(AVLNode<T>* &pR);
	bool balanceRight(AVLNode<T>* &pR);

	// Ham tu tao
	void traverseRNL(AVLNode<T> *pR, void(*op)(T&));
	bool searchNodeRemove(AVLNode<T> &pR, AVLNode<T> *&p);
	void traverseMinMaxLNR(AVLNode<T> *pR, T min, T max, void(*op)(T&));
};

template <class T>
void AVLTree<T>::traverseRNL(AVLNode<T>* pR, void(*op)(T &))
{
	if (pR == NULL)
		return;
	traverseRNL(pR->_pRight, op);
	op(pR->_data);
	traverseRNL(pR->_pLeft, op);
}

template<class T>
void AVLTree<T>::traverseMinMaxLNR(AVLNode<T>* pR, T min, T max, void(*op)(T &))
{
	if (pR == NULL)
		return;
	traverseMinMaxLNR(pR->_pLeft, min, max, op);
	if (pR->_data >= min && pR->_data <= max)
		op(pR->_data);
	traverseMinMaxLNR(pR->_pRight, min, max, op);
}

template<class T>
void AVLTree<T>::destroy(AVLNode<T>*& pR)
{
	if (pR)
	{
		destroy(pR->_pLeft);
		destroy(pR->_pRight);
		delete pR;
	}
	pR = NULL;
}

template<class T>
bool AVLTree<T>::find(AVLNode<T>* pR, T & key, T *& ret)
{
	if (pR == NULL)
		return false;
	if (pR->_data < key)
		return find(pR->_pRight, key, ret);
	if (pR->_data > key)
		return find(pR->_pLeft, key, ret);
	if (pR->_data == key)
	{
		ret = &(pR->_data);
		return true;
	}
}

template<class T>
bool AVLTree<T>::insert(AVLNode<T>*& pR, T & a)
{
	//Cay rong
	if (pR == NULL)
	{
		pR = new AVLNode<T>(a);
		return false;
	}

	// Neu Du lieu da co trong cay
	if (pR->_data == a)
	{
		pR->_data = a;
		return true;
	}

	//Chen vao ben trai
	else if (a < pR->_data)
	{
		if (insert(pR->_pLeft, a) == false)
		{
			if (pR->_bFactor == -1)
			{
				balanceLeft(pR);
				return true;
			}
			else if (pR->_bFactor == 0)
			{
				pR->_bFactor = -1;
				return false;
			}
			else
			{
				pR->_bFactor = 0;
				return true;
			}
		}
	}
	//Chen vao ben phai
	else
	{
		if (insert(pR->_pRight, a) == false)
		{
			if (pR->_bFactor == -1)
			{
				pR->_bFactor = 0;
				return true;
			}
			else if (pR->_bFactor == 0)
			{
				pR->_bFactor = 1;
				return false;
			}
			else
			{
				balanceRight(pR);
				return true;
			}
		}
	}
	return true;
}

template<class T>
bool AVLTree<T>::searchNodeRemove(AVLNode<T>& pR, AVLNode<T>*& p)
{
	bool booler;
	if (p->_pLeft)
	{
		booler = searchNodeRemove(pR, p->_pLeft);
		if (booler == false)
		{
			if (p->_bFactor == -1)
			{
				p->_bFactor == 0;
				return true;
			}
			else if (p->_bFactor == 0)
			{
				p->_bFactor == 1;
				return false;
			}
			else
				return balanceRight(pR);
		}
		else
			return booler;
	}
	pR->_data = p->_data;
	pR = p;
	p = p->_pRight;
	return false;
}

template<class T>
bool AVLTree<T>::remove(AVLNode<T>*& pR, T & a)
{
	bool booler;

	//Cay khong ton tai
	if (!pR)
		return true;
	//Xoa ben trai cua cay
	if (a < pR->_data)
	{
		booler = remove(pR->_pLeft, a);

		if (booler == false)
		{
			if (pR->_bFactor == -1)
			{
				pR->_bFactor = 0;
				return false;
			}
			else if (pR->_bFactor == 0)
			{
				pR->_bFactor = 1;
				return true;
			}
			else
				return balanceRight(pR);
		}
		else
			return booler;
	}
	//Xoa ben phai cua cay
	if (a > pR->_data)
	{
		booler == remove(pR->_pRight, a);
		if (booler == false)
		{
			if (pR->_bFactor == -1)
				return balanceLeft(pR);
			else if (pR->_bFactor == 0)
			{
				pR->_bFactor = 1;
				return true;
			}
			else
			{
				pR->_bFactor = 0;
				return false;
			}
		}
		else
			return booler;
	}
	else
	{
		AVLNode<T> *p = pR;
		if (pR->_pLeft == NULL)
		{
			pR = pR->_pRight;
			booler = false;
		}
		else
		{
			if (pR->_pRight == NULL)
			{
				pR = pR->_pLeft;
				booler = false;
			}
			else
			{
				booler = search(p, pR->_pRight);
				if (booler == false)
				{
					if (pR->_bFactor == 1)
					{
						pR->_bFactor = 0;
						return false;
					}
					else if (pR->_bFactor == 0)
					{
						pR->_bFactor == -1;
						return true;
					}
					else
						return balanceRight(pR);
				}
				else
					return booler;
			}
			delete p;
			return booler;
		}
	}
}

template<class T>
void AVLTree<T>::traverseNLR(AVLNode<T>* pR, void(*op)(T &))
{
	if (pR == NULL)
		return;
	op(pR->_data);
	traverseNLR(pR->_pLeft, op);
	traverseNLR(pR->_pRight, op);
}

template<class T>
void AVLTree<T>::traverseLNR(AVLNode<T>* pR, void(*op)(T &))
{
	if (pR == NULL)
		return;
	traverseLNR(pR->_pLeft, op);
	op(pR->_data);
	traverseLNR(pR->_pRight, op);
}

template<class T>
void AVLTree<T>::traverseLRN(AVLNode<T>* pR, void(*op)(T &))
{
	if (pR == NULL)
		return;
	traverseLRN(pR->_pLeft, op);
	traverseLRN(pR->_pRight, op);
	op(pR->_data);
}

//Cay con trai lech trai -> xoay phai
template<class T>
void AVLTree<T>::rotRight(AVLNode<T>*& pR)
{
	AVLNode<T> *p = pR->_pLeft;
	pR->_pLeft = p->_pRight;
	p->_pRight = pR;

	if (p->_bFactor == -1)
	{
		pR->_bFactor = 0;
		p->_bFactor = 0;
	}
	else if (p->_bFactor == 0)
	{
		p->_bFactor = 1;
		pR->_bFactor = -1;
	}
	pR = p;
}

//Cay con phai lech phai -> xoay trai	
template<class T>
void AVLTree<T>::rotLeft(AVLNode<T>*& pR)
{
	AVLNode<T> *p = pR->_pRight;
	pR->_pRight = p->_pLeft;
	p->_pLeft = pR;

	if (p->_bFactor == 0)
	{
		pR->_bFactor = 1;
		p->_bFactor = 0;
	}
	else if (p->_bFactor == 1)
	{
		p->_bFactor = 0;
		pR->_bFactor = 0;
	}
	pR = p;
}

//Cay con trai lech phai
template<class T>
void AVLTree<T>::rotLR(AVLNode<T>*& pR)
{
	rotLeft(pR->_pLeft);
	rotRight(pR);
}

//Cay con phai lech trai
template<class T>
void AVLTree<T>::rotRL(AVLNode<T>*& pR)
{
	rotRight(pR->_pRight);
	rotLeft(pR);
}

//Can bang cay lech trai
template<class T>
bool AVLTree<T>::balanceLeft(AVLNode<T>*& pR)
{
	AVLNode<T> *pLeft = pR->_pLeft;
	if (pLeft->_bFactor == -1)
	{
		rotRight(pR);
		return false;
	}
	else if (pLeft->_bFactor == 0)
	{
		rotRight(pR);
		return true;
	}
	else
	{
		rotLR(pR);
		return false;
	}
}

//Can bang cay lech phai
template<class T>
bool AVLTree<T>::balanceRight(AVLNode<T>*& pR)
{
	AVLNode<T> *pRight = pR->_pRight;
	if (pRight->_bFactor == 1)
	{
		rotLeft(pR);
		return false;
	}
	else if (pRight->_bFactor == 0)
	{
		rotLeft(pR);
		return true;
	}
	else
	{
		rotRL(pR);
		return false;
	}
}

#endif //A02_DSALIB_H
