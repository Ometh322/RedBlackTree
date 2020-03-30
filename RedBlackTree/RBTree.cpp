#include <iostream>

using namespace std;

struct RBTree
{
	int inf;
	char color;
	RBTree* right;
	RBTree* left;
	RBTree* parent;
};

RBTree* grandparent(RBTree* n) //������� ����������� ������� �������� ��������
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

RBTree* uncle(RBTree* n) //������� ����������� ���� �������� ��������
{
	RBTree* g = grandparent(n);
	if (g == NULL) //���� ��� ����, �� � ���� ���
		return NULL;
	if (n->parent = g->left)
		return g->right;
	else
		return g->left;
}

void insert_case1(RBTree* n) //1 ������ �������, ����� ��� ��� ����� ������
{
	if (n->parent == NULL)
		n->color = 'b'; //��� ������� ���������� ������ ������ � �������������� ������
	else //����� ��������� � ������� ������
		insert_case2(n);
}
 
void insert_case2(RBTree* n) //2 ������ �������, ���� ������ ������ �������� - ������
{
	if (n->parent->color == 'b')
		return; //��� ��
	else
		insert_case3(n);
}

void insert_case3(RBTree* n)//2 ������ �������, ����� �������� � ���� - ������� 
{
	RBTree* u = uncle(n), * g;
	if ((u != NULL) && (u->color == 'r')) //���� ���� �������
	{
		n->parent->color = 'b'; //������������� �������� � ������
		u->color = 'b'; //���� � ������
		g = grandparent(n); //g - ������� n
		g->color = 'r'; //������������� ���� � �������
		insert_case1(g); //� ���������� ���� ����� 1 ������ �������
	}
	else
		insert_case4(n);
}

void insert_case4(RBTree* n)// 4 ������ �������, ���� �������� - �������, � ���� - ������
{
	RBTree* g = grandparent(n);
	if ((n == n->parent->right) && (n->parent == g->left)) //���� n - ������ �������, � ��� �������� - ����� ������� ����
	{
		rotate_left(n->parent); //���������� ������� �����
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent = g->right))//���� n - ����� �������, � ��� �������� - ������ ������� ����
	{
		rotate_right(n->parent); //���������� ������� ������
		n = n->right;
	}
	insert_case5(n);
}

void rotate_left(RBTree* n) //������� �����
{
	RBTree* pivot = n->right; //�������� - ������ ������� n
	pivot->parent = n->parent; //�������� ������� - �������� n
	if (n->parent != NULL)
	{
		if (n->parent->left == n) //���� n - ����� �������
			n->parent->left = pivot; //�������� �� ��������
		else //���� n - ������� �������
			n->parent->right = pivot; //�������� �� ��������
	}
	n->right = pivot->left; //������ ������� n - ����� ������� �������
	if (pivot->left != NULL)//���� ���������� ����� ������� � �������
		pivot->left->parent = n; //�������� ��� �������� �� n
	n->parent = pivot; //��������� n ���������� ��������
	pivot->left = n; //����� �������� ������� ���������� n
}

void rotate_right(RBTree* n) //������� ������
{
	RBTree* pivot = n->left; //�������� - ����� ������� n
	pivot->parent = n->parent; //�������� ������� - �������� n
	if (n->parent != NULL)
	{
		if (n->parent->left == n) //���� n - ����� �������
			n->parent->left = pivot; //�������� �� ��������
		else //���� n - ������� �������
			n->parent->right = pivot; //�������� �� ��������
	}
	n->left = pivot->right; //����� ������� n - ������ ������� �������
	if (pivot->right != NULL)//���� ���������� ������ ������� � �������
		pivot->right->parent = n; //�������� ��� �������� �� n
	n->parent = pivot; //��������� n ���������� ��������
	pivot->right = n; //������ �������� ������� ���������� n
}

int main() {
	
}