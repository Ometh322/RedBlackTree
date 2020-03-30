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

RBTree* grandparent(RBTree* n) //функция определения дедушки текущего элемента
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

RBTree* uncle(RBTree* n) //фнукция определения дяди текущего элемента
{
	RBTree* g = grandparent(n);
	if (g == NULL) //если нет деда, то и дяди нет
		return NULL;
	if (n->parent = g->left)
		return g->right;
	else
		return g->left;
}

void insert_case1(RBTree* n) //1 случай вставки, когда еще нет корня дерева
{
	if (n->parent == NULL)
		n->color = 'b'; //наш элемент становится корнем дерева и соответственно черным
	else //иначе переходим к другому случаю
		insert_case2(n);
}
 
void insert_case2(RBTree* n) //2 случай вставки, если предок нашего элемента - черный
{
	if (n->parent->color == 'b')
		return; //все ок
	else
		insert_case3(n);
}

void insert_case3(RBTree* n)//2 случай вставки, когда родитель и дядя - красные 
{
	RBTree* u = uncle(n), * g;
	if ((u != NULL) && (u->color == 'r')) //если дядя красный
	{
		n->parent->color = 'b'; //перекрашиваем родителя в черный
		u->color = 'b'; //дядю в черный
		g = grandparent(n); //g - дедушка n
		g->color = 'r'; //перекрашиваем деда в красный
		insert_case1(g); //и засовываем деда через 1 случай вставки
	}
	else
		insert_case4(n);
}

void insert_case4(RBTree* n)// 4 случай вставки, кгда родитель - красный, а дяда - черный
{
	RBTree* g = grandparent(n);
	if ((n == n->parent->right) && (n->parent == g->left)) //если n - правый ребенок, и его родитель - левый ребенок деда
	{
		rotate_left(n->parent); //производим поворот влево
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent = g->right))//если n - левый ребенок, и его родитель - правый ребенок деда
	{
		rotate_right(n->parent); //производим поворот вправо
		n = n->right;
	}
	insert_case5(n);
}

void rotate_left(RBTree* n) //поворот влево
{
	RBTree* pivot = n->right; //стержень - правый ребенок n
	pivot->parent = n->parent; //родитель стержня - родитель n
	if (n->parent != NULL)
	{
		if (n->parent->left == n) //если n - левый ребенок
			n->parent->left = pivot; //заменяем на стержень
		else //если n - правыйй ребенок
			n->parent->right = pivot; //заменяем на стержень
	}
	n->right = pivot->left; //правый ребенок n - левый ребенок стержня
	if (pivot->left != NULL)//если существует левый ребенок у стержня
		pivot->left->parent = n; //заменяем его родителя на n
	n->parent = pivot; //родителем n становится стержень
	pivot->left = n; //левый ребенком стержня становится n
}

void rotate_right(RBTree* n) //поворот вправо
{
	RBTree* pivot = n->left; //стержень - левый ребенок n
	pivot->parent = n->parent; //родитель стержня - родитель n
	if (n->parent != NULL)
	{
		if (n->parent->left == n) //если n - левый ребенок
			n->parent->left = pivot; //заменяем на стержень
		else //если n - правыйй ребенок
			n->parent->right = pivot; //заменяем на стержень
	}
	n->left = pivot->right; //левый ребенок n - правый ребенок стержня
	if (pivot->right != NULL)//если существует правый ребенок у стержня
		pivot->right->parent = n; //заменяем его родителя на n
	n->parent = pivot; //родителем n становится стержень
	pivot->right = n; //правый ребенком стержня становится n
}

int main() {
	
}