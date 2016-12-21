#include <iostream>
#pragma once;
using namespace std;

template <class K>
struct SearchBinaryTreeNode
{
	K _key;   //关键字
	//V _value;
	SearchBinaryTreeNode *_left;
	SearchBinaryTreeNode *_right;
	SearchBinaryTreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class K>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K> Node;

public:
	SearchBinaryTree()
	{
		_root=NULL;
	}

	SearchBinaryTree(const SearchBinaryTree<K>& sbt)
	{
		_root=_Copy();
	}
	~SearchBinaryTree()
	{
		_Destroy(_root);
	}
	SearchBinaryTree<K>& operator=(const SearchBinaryTree<K> sbt)
	{
		if (this != &sbt)    //防止自赋值
		{
			SearchBinaryTree<K> tmp(sbt);
			std::swap(_root,tmp._root);
		}
		return *this;
	}

public:

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root,key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	Node *_Copy(Node *root)
	{
		Node *cur=root;
		Node *proot=NULL;//proot是拷贝的新树的根结点
		if(cur)
		{
			proot=new Node(cur->_key);
			proot->_left=_Copy(cur->_left);
			proot->_right=_Copy(cur->_right);
		}
		return proot;
	}


	

	void _Destroy(Node *root)
	{
		if(root == NULL)
			return ;
		Node *cur=root;
		if(cur)
		{
			_Destroy(cur->_left);
			_Destroy(cur->_right);
			delete cur;
			cur=NULL;
		}
	}


	bool Insert(const K& key)
	{
		if (_root==NULL)
		{
			_root=new Node(key);
			return true;
		}
		Node* cur=_root;
		Node* parent=NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent=cur;
				cur=cur->_right;
			}
			else if (cur->_key > key)
			{
				parent=cur;
				cur=cur->_left;
			}
			else
				return false;
		}
          //不存在相同的key
		if(parent->_key < key)
		{
			parent->_right=new Node(key);
			return true;
		}
		else if(parent->_key > key)
		{
			parent->_left=new Node(key);
			return true;
		}
		else
			return false;

	}

	bool Find(const K& key)
	{
		Node *cur=_root;
		while (cur)
		{
			if(cur->_key < key)
				cur=cur->_right;
			else if(cur->_key > key)
				cur=cur->_left;
			else
				return true;
		}
		return false;
	}

	bool Remove(const K& key)
	{
		Node *cur = _root;
		Node *parent = NULL;
		Node *del = NULL;
		while (cur&&cur->_key!=key)
		{
			if (cur->_key < key)
			{

				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				break;
			}
		}
		if (cur == NULL)
		{
			return false;   
		}
		if (cur->_left == NULL)
		{

			del = cur;
			if (parent == NULL)
			{
				_root = cur->_right;
			}
			else
			{

				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
		}
		else if (cur->_right==NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				cur = cur->_left;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}

		}
		else
		{
			Node *minright = cur->_right;
			while (minright->_left)
			{
				parent = minright;
				minright = minright->_left;
			}
			del = minright;
			cur->_key = minright->_key;


			if (parent->_left = minright)
				parent->_left = minright->_right;
			else
				parent->_right = minright->_right;
		}
		delete del;
		del = NULL;
		return true;
	}

bool InsertR(Node *& root , const K& key)
{
	if (root == NULL)
	{
		root = new Node(key);
		return true;
	}
	if (root->_key < key)
	{
		return InsertR(root->_right,key);
	}
	else if (root->_key > key)
	{
		return InsertR(root->_left,key);
	}
	else
		return false;
}

bool FindR(Node *& root , const K& key)
{
	if (root == NULL)
	{
		return false;
	}
	if (root->_key < key)
	{
		return FindR(root->_right,key)
	}
	else if (root->_key > key)
	{
		return FindR(root->_left,key)
	}
	else
		return true;
}



protected:
	void _InOrder(Node *root)
	{
		if(root == NULL)
			return ;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	bool _RemoveR(Node *&root , const K& key)
	{
		if (root ==NULL)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _RemoveR(root->_right,key);
		}
		else if (root->_key > key)
		{
			return _RemoveR(root->_left,key);
		}
		else
		{
			Node* del=root;
			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* parent = root;
				Node * minright = root->_right;
				while (minright->_left)
				{
					parent = minright;
					minright = minright->_left;
				}
				root->_key = minright->_key;
//
				if (parent->_right == minright)
					parent->_right = minright->_right;
				else
					parent->_left = minright->_right;
				del = minright;
			}
			delete del;
			return true;
		}
		return false;
	}

protected:
	Node *_root;
};

void test()
{
	int arr[]={5,3,4,1,7,8,2,6,0,9};
	size_t size=sizeof(arr)/sizeof(arr[0]);
	SearchBinaryTree<int> sbt;
	for (size_t i=0;i<size;i++)
	{
		sbt.Insert(arr[i]);
	}
	sbt.InOrder();
	sbt.Insert(1);
	sbt.Insert(10);
	sbt.InOrder();
	cout<<sbt.Find(1)<<endl;
	cout<<sbt.Find(7)<<endl;
	cout<<sbt.Find(20)<<endl;
	sbt.Remove(0);
	sbt.Remove(1);
	sbt.Remove(2);
	sbt.Remove(3);
	sbt.Remove(4);
    sbt.Remove(5);
	sbt.InOrder();
	sbt.Remove(6);
	sbt.Remove(7);
	sbt.Remove(8);
	sbt.Remove(9);
	sbt.InOrder();
	sbt.Remove(10);
	sbt.InOrder();
}

int main()
{
	test();
	system("pause");
	return 0;
}