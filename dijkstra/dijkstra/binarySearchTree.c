#include <stdio.h>


typedef struct TreeNode {
	int key;
	TreeNode *leftChild;
	TreeNode *rightChild;
}TreeNode;

typedef struct Tree {
	TreeNode *root;

}Tree;

void Tree_init(Tree *Target_Tree) {
	Target_Tree->root = NULL;

}

int is_There(Tree *Target_Tree, int Item) {
	TreeNode *Cur = Target_Tree->root;

	while (1)
	{
		if (Cur->key == Item)
		{
			return 1;
		}
		if (Cur->key < Item)
		{
			if (Cur->rightChild == NULL)
				return 0;
			Cur = Cur->rightChild;
		}
		else
		{
			if (Cur->leftChild == NULL)
				return 0;
			Cur = Cur->leftChild;
		}

	}

}

void add_Node(Tree *Target_Tree, int Item) {

	TreeNode *NewNode = (TreeNode *)malloc(sizeof(TreeNode));
	if (Target_Tree->root == NULL)
	{
		Target_Tree->root = NewNode;
		NewNode->leftChild = NULL;
		NewNode->rightChild = NULL;
		NewNode->key = Item;
		return;
	}
	if (Is_There(Target_Tree, Item))
	{
		printf("�̹� ���� �ϴ� ���Դϴ�.\n");
		return;
	}
	NewNode->leftChild = NULL;
	NewNode->rightChild = NULL;
	NewNode->key = Item;
	TreeNode *Cur = Target_Tree->root;
	while (1)
	{
		if (Cur->key < Item)
		{
			if (Cur->rightChild == NULL)
			{
				Cur->rightChild = NewNode;
				return;
			}
			Cur = Cur->rightChild;
		}
		else
		{
			if (Cur->leftChild == NULL)
			{
				Cur->leftChild = NewNode;
				return;
			}
			Cur = Cur->leftChild;
		}
	}
}

int Delete_Node(Tree *Target_Tree, int Item)
{
	TreeNode *Cur2 = NULL;
	TreeNode *Cur = Target_Tree->root;
	TreeNode *Par_Parent = NULL;
	TreeNode *Parent = NULL;
	TreeNode *Child = NULL;
	TreeNode *Left_Temp = NULL;
	int Key_return = 0;
	if (!Is_There(Target_Tree, Item))
	{
		printf("���� ���Դϴ�.\n");
		return 0;
	}
	while (Cur->key != Item)
	{
		if (Item > Cur->key)
		{
			Par_Parent = Parent;
			Parent = Cur;
			Cur = Cur->rightChild;
		}
		else
		{
			Par_Parent = Parent;
			Parent = Cur;
			Cur = Cur->leftChild;
		}
	}//Ư�� �� ���� �̵�
	if (Cur->leftChild == NULL&&Cur->rightChild == NULL)//�͹̳� ����� ��
	{
		Key_return = Cur->key;
		if (Parent->leftChild == Cur)
			Parent->leftChild = NULL;
		if (Parent->rightChild == Cur)
			Parent->rightChild = NULL;
		free(Cur);
		return Key_return;
	}

	if (Cur->leftChild == NULL || Cur->rightChild == NULL)//������� �� �Ʒ��� 1���� �ڽ��� ���� ��
	{
		Child = (Cur->leftChild != NULL) ? Cur->leftChild : Cur->rightChild;

		if (Parent->leftChild == Cur)//������� ���� �θ� �� ����ڽ��� ������� ������?
			Parent->leftChild = Child;
		else
			Parent->rightChild = Child;
		Key_return = Cur->key;
		free(Cur);
		return Key_return;
	}

	if (Cur->leftChild != NULL&&Cur->rightChild != NULL)//������� �� �Ʒ��� 2�� �ڽ��� ���� ��
	{
		Cur2 = Cur;
		Cur2 = Cur2->rightChild;
		if (Cur2->leftChild == NULL)//������ ��ĭ �̵� �� ���ʿ� ��尡 ���� �� 
		{
			Left_Temp = Cur->leftChild;
			Child = Cur2;
			if (Parent->rightChild == Cur)
			{
				Parent->rightChild = Child;
				Child->leftChild = Left_Temp;
			}
			else
				if (Parent->leftChild == Cur)
				{
					Parent->leftChild = Child;
					Child->leftChild = Left_Temp;
				}
			Key_return = Cur->key;
			free(Cur);
			return Key_return;
		}
		while (Cur2->leftChild != NULL)//������ ��ĭ �̵��� ���ʿ� ��尡 ���� ��
		{
			Parent = Cur2;
			Cur2 = Cur2->leftChild;
		}
		Parent->leftChild = NULL;
		Cur->key = Cur2->key;
		free(Cur2);
	}
	return 0;
}

