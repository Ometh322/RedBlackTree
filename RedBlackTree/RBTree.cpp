#include <iostream>
#include <queue>

using namespace std;

class RBTree {
public:
	int inf;
	char color;
	RBTree* left;
	RBTree* right;
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
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void rotate_left(RBTree*& n) //������� �����
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

void rotate_right(RBTree*& n) //������� ������
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

void insert_case1(RBTree*& n);

void insert_case5(RBTree*& n)//�������� - �������, ���� - ������
{

	RBTree* g = grandparent(n);
	n->parent->color = 'b'; //�������� - ������
	g->color = 'r';//���� ���� - �������
	if ((n == n->parent->left) && (n->parent == g->left)) //���� n - ����� ������� � �������� - ����� ������� ����
	{
		rotate_right(g); //������ ������ ������� ������������ ����
	}
	else //����� ������ ����� �������� ������������ ����
		rotate_left(g);
}

void insert_case4(RBTree*& n)// 4 ������ �������, ���� �������� - �������, � ���� - ������
{
	
	RBTree* g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) //���� n - ������ �������, � ��� �������� - ����� ������� ����
	{
		rotate_left(n->parent); //���������� ������� �����
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right))//���� n - ����� �������, � ��� �������� - ������ ������� ����
	{
		rotate_right(n->parent); //���������� ������� ������
		n = n->right;
	}
	insert_case5(n);
}

void insert_case3(RBTree*& n)//3 ������ �������, ����� �������� � ���� - ������� 
{
	
	RBTree* u = uncle(n), *g;
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

void insert_case2(RBTree*& n) //2 ������ �������, ���� ������ ������ �������� - ������
{

	if (n->parent->color == 'b')
		return; //��� ��
	else
		insert_case3(n);
}


void insert_case1(RBTree*& n) //1 ������ �������, ����� ��� ��� ����� ������
{
	if (n->parent == NULL)
		n->color = 'b'; //��� ������� ���������� ������ ������ � �������������� ������
	/*else if ((n->parent->parent) && (n->parent->parent ->parent) && (n->parent->parent ->parent->color == 'b'))
		return;*/
	else //����� ��������� � ������� ������
		insert_case2(n);
}
 
RBTree* start_node(int x) //������������ ����
{
	RBTree* n = new RBTree;
	n->inf = x;
	n->color = 'r';
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;
}

void insert(RBTree*& tr, int x) //������� ������ �������� � ������
{
	RBTree* n = start_node(x);
	if (!tr) //���� �� ������� ����� ������
	{
		insert_case1(n);//�������� ������� �� ������
		tr = n;
		
	}
	else //���� ������ ��� ����
	{
		while (tr)
		{
			if (n->inf > tr->inf) //���� ��� ������� ������ - ���� �� ������ �������
				if (tr->right) //���� ���� �������� �������
					tr = tr->right;
				else  //����� ����� ����� ��� ������� �������� 
				{
					n->parent = tr;
					tr->right = n;
					insert_case1(n);//��������� �������� ��-������
					break;
				}
			else if (n->inf < tr->inf) //���� ��� ������� ������ - ���� �� ����� �������
				if (tr->left)
					tr = tr->left;
				else
				{
					n->parent = tr;
					tr->left = n;
					insert_case1(n); //��������� �������� ��-������
					break;
				}
			else
				break;
		}
	}
	while (tr->parent) //����������� �� ��������
		tr = tr->parent;
}

void inorder(RBTree* tr) //������������ ����� ������
{
	if (tr)
	{
		inorder(tr->left);
		cout << tr->inf << tr->color << " ";
		inorder(tr->right);
	}
}

RBTree* find(RBTree* tr, int x)//����� ��������
{
	if (!tr || x == tr->inf)
		return tr;
	if (x < tr->inf)
		return find(tr->left, x);
	else
		return find(tr->right, x);
}

RBTree* Min(RBTree* tr)//����� ��������
{
	if (!tr->left)
		return tr;
	else
		return Min(tr->left);
}

RBTree* Max(RBTree* tr)//����� ���������
{
	if (!tr->right)
		return tr;
	else
		return Min(tr->right);
}

RBTree* Next(RBTree* tr, int x) //����� ����������
{
	RBTree* n = find(tr, x);
	if (n->right)
		return Min(n->right);
	RBTree* y = n->parent;
	while (y && n == y->right)
	{
		n = y;
		y = y->parent;
	}
	return y;
}

RBTree* Prev(RBTree* tr, int x) //����� �����������
{
	RBTree* n = find(tr, x);
	if (n->left)
		return Min(n->right);
	RBTree* y = n->parent;
	while (y && n == y->left)
	{
		n = y;
		y = y->parent;
	}
	return y;
}

RBTree* sibling(RBTree* n)//���������� �����
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void replace_node(RBTree*& n, RBTree*& child) //������ ����
{
	child->parent = n->parent;
	if (n == n->parent->left)
		n->parent->left = child;
	else
		n->parent->right = child;
}

void delete_one_child(RBTree*& n) //�������� ������ �������
{
	//n ����� �� ����� ������ ���������� �������
}

void print(RBTree* tr, int k) { //������ ��������� ������
	if (!tr) cout << "Empty tree\n";
	else {
		queue<RBTree*> cur, next;
		RBTree* r = tr;
		cur.push(r);
		int j = 0;
		while (cur.size()) {
			if (j == 0) {
				for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
					cout << "  ";

			}
			RBTree* buf = cur.front();
			cur.pop();
			j++;
			if (buf) {
				cout << buf->inf << buf->color;
				next.push(buf->left);
				next.push(buf->right);
				for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
					cout << "  ";

			}

			if (!buf) {
				for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
					cout << "  ";
				cout << "  ";

			}
			if (cur.empty()) {
				cout << endl;
				swap(cur, next);
				j = 0;
				k--;
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "RUS");
	int n;
	cout << "������� ���-�� ���������: ";
	cin >> n;
	cout << endl;

	RBTree* tr = NULL;

	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		insert(tr, x);
	}
	if (tr)
		inorder(tr);
	else
		cout << "���" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	int k = int(log((float)n) / log((float)2.0));
	print(tr, k);
}