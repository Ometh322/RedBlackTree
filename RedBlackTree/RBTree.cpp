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
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void rotate_left(RBTree*& n) //поворот влево
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

void rotate_right(RBTree*& n) //поворот вправо
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

void insert_case1(RBTree*& n);

void insert_case5(RBTree*& n)//родитель - красный, дядя - черный
{

	RBTree* g = grandparent(n);
	n->parent->color = 'b'; //родитель - черный
	g->color = 'r';//цвет деда - красный
	if ((n == n->parent->left) && (n->parent == g->left)) //если n - левый ребенок и родитель - левый ребенок деда
	{
		rotate_right(g); //делаем правый поворот относительно деда
	}
	else //иначе делаем левый поворото относительно деда
		rotate_left(g);
}

void insert_case4(RBTree*& n)// 4 случай вставки, кгда родитель - красный, а дяда - черный
{
	
	RBTree* g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)) //если n - правый ребенок, и его родитель - левый ребенок деда
	{
		rotate_left(n->parent); //производим поворот влево
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right))//если n - левый ребенок, и его родитель - правый ребенок деда
	{
		rotate_right(n->parent); //производим поворот вправо
		n = n->right;
	}
	insert_case5(n);
}

void insert_case3(RBTree*& n)//3 случай вставки, когда родитель и дядя - красные 
{
	
	RBTree* u = uncle(n), *g;
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

void insert_case2(RBTree*& n) //2 случай вставки, если предок нашего элемента - черный
{

	if (n->parent->color == 'b')
		return; //все ок
	else
		insert_case3(n);
}


void insert_case1(RBTree*& n) //1 случай вставки, когда еще нет корня дерева
{
	if (n->parent == NULL)
		n->color = 'b'; //наш элемент становится корнем дерева и соответственно черным
	/*else if ((n->parent->parent) && (n->parent->parent ->parent) && (n->parent->parent ->parent->color == 'b'))
		return;*/
	else //иначе переходим к другому случаю
		insert_case2(n);
}
 
RBTree* start_node(int x) //формирование узла
{
	RBTree* n = new RBTree;
	n->inf = x;
	n->color = 'r';
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;
}

void insert(RBTree*& tr, int x) //вставка нового элемента в дерево
{
	RBTree* n = start_node(x);
	if (!tr) //если мы создаем новое дерево
	{
		insert_case1(n);//проверка условий кч дерева
		tr = n;
		
	}
	else //если дерево уже есть
	{
		while (tr)
		{
			if (n->inf > tr->inf) //если наш элемент больше - идем по правой стороне
				if (tr->right) //ищем куда вставить элемент
					tr = tr->right;
				else  //когда нашли место под вставку элемента 
				{
					n->parent = tr;
					tr->right = n;
					insert_case1(n);//выполняем проверку кч-дерева
					break;
				}
			else if (n->inf < tr->inf) //если наш элемент меньше - идем по левой стороне
				if (tr->left)
					tr = tr->left;
				else
				{
					n->parent = tr;
					tr->left = n;
					insert_case1(n); //выполняем проверку кч-дерева
					break;
				}
			else
				break;
		}
	}
	while (tr->parent) //поднимаемся на верхушку
		tr = tr->parent;
}

void inorder(RBTree* tr) //симметричный обход дерева
{
	if (tr)
	{
		inorder(tr->left);
		cout << tr->inf << tr->color << " ";
		inorder(tr->right);
	}
}

RBTree* find(RBTree* tr, int x)//поиск элемента
{
	if (!tr || x == tr->inf)
		return tr;
	if (x < tr->inf)
		return find(tr->left, x);
	else
		return find(tr->right, x);
}

RBTree* Min(RBTree* tr)//поиск минимума
{
	if (!tr->left)
		return tr;
	else
		return Min(tr->left);
}

RBTree* Max(RBTree* tr)//поиск максимума
{
	if (!tr->right)
		return tr;
	else
		return Min(tr->right);
}

RBTree* Next(RBTree* tr, int x) //поиск следующего
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

RBTree* Prev(RBTree* tr, int x) //поиск предыдущего
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

RBTree* sibling(RBTree* n)//нахождение брата
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void replace_node(RBTree*& n, RBTree*& child) //замена узла
{
	child->parent = n->parent;
	if (n == n->parent->left)
		n->parent->left = child;
	else
		n->parent->right = child;
}

void delete_one_child(RBTree*& n) //удаление одного ребенка
{
	//n имеет не более одного ненулевого потомка
}

void print(RBTree* tr, int k) { //печать красивого дерева
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
	cout << "Введите кол-во элементов: ";
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
		cout << "Упс" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	int k = int(log((float)n) / log((float)2.0));
	print(tr, k);
}