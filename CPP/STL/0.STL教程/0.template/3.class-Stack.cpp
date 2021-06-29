#include <iostream>

using namespace std;

template<typename T>class Stack
{
private:
	T* pstk;	//堆栈数据储存指针变量
	int size;	//堆栈容量
	int top;	//栈顶指针计数器
public:
	Stack(int num);
	bool Push(T& t);
	T* Pop();
	~Stack()
	{
		delete[]pstk;
	}
};
template<typename T>Stack<T>::Stack(int num)
{
	pstk=new T[num];	//参与形参动态生成
	size =num;
	top =0;
}
template<typename T>bool Stack<T>::Push(T& t)
{
	if(top>=size)
	{
		cout<<"Stack is full."<<endl;
		return false;
	}
	pstk[top++]=t;
	return true;
}
template<typename T>T* Stack<T>::Pop()
{
	if(top==0)
	{
		cout<<"Stack if empty."<<endl;
		return NULL;
	}
	else return &pstk[--top];
}

int main()
{
	int a=10,b=12,*pa=NULL;
	Stack<int>stk(20);
	cout<<a<<"  "<<b<<endl;
	stk.Push(a);stk.Push(b);
		
	pa=stk.Pop();
	if(pa!=NULL) cout<<*pa<<endl;
	pa=stk.Pop();
	if(pa!=NULL) cout<<*pa<<endl;
	pa=stk.Pop();
	if(pa!=NULL) cout<<*pa<<endl;
	return 0;
}

