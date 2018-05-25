
//
/*
Assignement 2: Dynamic Memory
Note all inputs are expected to be of correct types for program to work
* marks for students are of int type
* command line option -b for binary tree implementation -l for linked list
* linked list implementation is assumed default
* trees are balanced via AVL algorithm for AVL balanced binary trees
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXVALUE 255

//student struct with name field unique id field and mark array of ints and next ptr for list
struct Student {
	char name[MAXVALUE];
	int  number;
	int mark[MAXVALUE];
	struct Student* next;
}; 

//treeNode struct with name field unique id field and mark array of ints and left right ptrs for tree
struct TreeNode {
	char name[MAXVALUE];
	int number;
	int mark[MAXVALUE];
	struct TreeNode* left;
	struct TreeNode* right;
}; 

//functions for linked list implementation
struct Student* searchStudent(struct Student* list, int studentNumber);
struct Student* insert(struct Student* list, int studentNumber, char studentName[MAXVALUE]);
struct Student* removeNode(struct Student* list, int studentNumber);
struct Student* insertMark(struct Student* list, int studentNumber);
struct Student* insertMarkAuto(struct Student* list, int studentNumber, int mark);
struct Student* readFromFile(struct Student* list);
void printAll(struct Student* list);
void printIndividual(struct Student* list, int studentNumber);
void removeAll(struct Student* list);
void  saveToFile(struct Student* list);

//functions for binary tree implementation
struct TreeNode* getParent(struct TreeNode** root, struct TreeNode* child);
void printHelper(struct TreeNode** root, FILE** fp);
void saveFileTree(struct TreeNode** root);
int treeNodeHeight(struct TreeNode* node);
int balanceFactor(struct TreeNode* node);
struct TreeNode* rotateLeftLeft(struct TreeNode* node);
struct TreeNode* rotateLeftRight(struct TreeNode* node);
struct TreeNode* rotateRightRight(struct TreeNode* node);
struct TreeNode* rotateRightLeft(struct TreeNode* node);
struct TreeNode* balanceNode(struct TreeNode* node);
struct TreeNode* searchTree(struct TreeNode** root, int id);
void insertTreeMark(struct TreeNode** root, int studentNumber, int mark);
void readFileTree(struct TreeNode** root);
void insertTreeNode(struct TreeNode** root, struct TreeNode* node);
void deleteTree(struct TreeNode** root, int studentNumber);
void deleteAllTree(struct TreeNode** root);
void insertTree(struct TreeNode** root, int studentNumber, char studentName[MAXVALUE]);
void printTree(struct TreeNode** root);
void initializeMarksTree(struct TreeNode** root, int studentNumber);


int main(int argc, char** argv)
{
	int option = -1;
	char dataChoice[MAXVALUE];
	int treeChoice = 0;

	//read from command line arguments
	strcpy(dataChoice, "Linked List");
	if (argc>1)
	{
		if (strcmp(argv[1], "-b") == 0)
		{
			printf("Using binary trees to store data\n");
			treeChoice = 1;
		}
		else if (strcmp(argv[1], "-l") == 0)
		{
			printf("Using linked list to store data\n");
			treeChoice = 0;
		}
	}
	else if (argc == 1)
	{
		treeChoice = 0;
		printf("Using linked list to store data as default\n");
	}

	int studentNumber;
	char studentName[MAXVALUE];
	int mark;
	//declare list ptr for linked list
	struct Student* list;
	//declare root ptr for binar y tree
	struct TreeNode* root;
	root = NULL;

	if (treeChoice == 0) // not using binary trees
	{
		while (option != 7) // continuously ask for new input till exit same as task 1
		{
			printf("Choose from the following options:\n");
			printf("1. to introduce a new student \n");
			printf("2. to remove a student\n");
			printf("3. to print individual report\n");
			printf("4. to print all results\n");
			printf("5. to save to file\n");
			printf("6. to retrieve data from file \n");
			printf("7. to exit\n");
			printf("8. to insert a mark\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1: // insert into end of list
			{
				printf("Please Enter a student number \n");
				scanf("%d", &studentNumber); // get the number

				printf("Please enter a student name\n");
				scanf("%s", studentName);

				list = insert(list, studentNumber, studentName);
			} break;
			case 2: // delete from list
			{
				printf("Please enter a student number\n");
				scanf("%d", &studentNumber);
				list = removeNode(list, studentNumber);
			} break;
			case 3: // print individual selected
			{
				printf("Please Enter a student Number\n");
				int tempNum;
				scanf("%d", &tempNum);
				printIndividual(list, tempNum);
			}  break;
			case 4: //print all nodes
			{
				printf("Printing all records\n");
				printAll(list);
			} break;
			case 5: //save to file results.txt in local dir
			{
				printf("Storing all data in list to file results.txt\n");
				saveToFile(list); // note does not append just rewrites
			}
			break;
			case 6: //read from file results.txt if exists
			{
				printf("Retrieving data from results.txt\n");
				list = readFromFile(list);
			}
			break;
			case 7: //free all memory and exit
			{
				removeAll(list);
				return 0;
			}
			break;
			case 8: //insert a mark to added  student
			{
				printf("Please Insert a student Number\n");
				scanf("%d", &studentNumber);

				list = insertMark(list, studentNumber);
			}
			break;
			default:
				option = -1;
				break;
			}
		}
	}
	else
	{
		while (option != 7) // continuously ask for new input till exit same as task 1
		{
			printf("Choose from the following options:\n");
			printf("1. to introduce a new student \n");
			printf("2. to remove a student\n");
			printf("3. to print individual report \n");
			printf("4. to print all reports \n");
			printf("5. to save to file\n");
			printf("6. to read from file\n");
			printf("7. to exit\n");
			printf("8. to insert Mark\n");

			scanf("%d", &option);
			switch (option)
			{
			case 1: // insert and rebalance tree
			{
				printf("Please Enter a student number \n");
				scanf("%d", &studentNumber); // get the number

				printf("Please enter a student name\n");
				scanf("%s", studentName);
				//insert node into tree by unique studentNumber
				insertTree(&root, studentNumber, studentName);

				//re-balance tree if needed
				int treeHeight = treeNodeHeight(root);
				int balance = balanceFactor(root);
				printf("Height of tree is: %d \n", treeHeight);
				printf("Balance  of tree is: %d \n", balance);
				printf("Balancing tree\n");
				root = balanceNode(root);

			}break;
			case 2://delete node and rebalance
			{
				printf("Please enter a student number\n");
				scanf("%d", &studentNumber);
				//delete node from tree
				deleteTree(&root, studentNumber);

				//re-balance tree if needed
				int treeHeight = treeNodeHeight(root);
				int balance = balanceFactor(root);
				printf("Height of tree is: %d \n", treeHeight);
				printf("Balance  of tree is: %d \n", balance);
				printf("Balancing tree\n");
				root = balanceNode(root);
			}
			break;
			case 3://search tree for student and print details if found
			{
				printf("Please Enter a student Number\n");
				scanf("%d", &studentNumber);
				printf("Searching tree...\n");

				// returns node if found null if not
				struct TreeNode * temp = searchTree(&root, studentNumber);

				if (temp == NULL)
				{
					printf("Not found\n");
				}
				else {//found
					  //print everything in node
					printf("Name: %s ID: %d\n", temp->name, temp->number);
					printf("Mark: ");
					for (int i = 0; i<MAXVALUE; i++)
					{
						if (temp->mark[i]>-1)
							printf("%d\t", temp->mark[i]);
					}
					printf("\n");
				}
			}break;
			case 4:
			{
				printf("Printing all tree nodes\n");
				printTree(&root);

			}break;
			case 5:
			{
				printf("Saving to file\n");
				saveFileTree(&root);

			}break;
			case 6:
			{
				printf("Reading from file\n");
				readFileTree(&root);
			}break;
			case 7://delete all and exit
			{//if root is empty end;
				if (root == NULL)
				{
					printf("Closing \n");
					return 0;
				}
				else
				{
					deleteAllTree(&root);//will delete everything but root
					free(root);
					printf("Closing \n");
					return 0;
				}
			}break;
			case 8:
			{ // insert a new mark into tree if student exists
				printf("Please Insert a student Number\n");
				scanf("%d", &studentNumber);
				printf("Please enter a mark\n");
				scanf("%d", &mark);
				insertTreeMark(&root, studentNumber, mark);
			}
			default:
				option = -1;
				break;
			}
		}
	}

}

struct Student* insert(struct Student* list, int studentNumber, char studentName[MAXVALUE])
{ //function to insert new node into linked list
	struct Student* tempPtr = searchStudent(list, studentNumber); // null if not found
	if (tempPtr == NULL)
	{
		struct Student* curr;
		struct Student* prev;
		curr = list;
		if (curr == NULL) //list is empty
		{
			//create new node and assign fields
			curr = (struct Student*) malloc(sizeof(struct Student));
			curr->number = studentNumber;
			strcpy(curr->name, studentName);
			initializeMarks(curr);//sets all marks to -1

			list = curr;
			return list;//update list
		}
		else
		{
			while (curr != NULL)
			{
				prev = curr;
				curr = curr->next;
			} //go to end of list
			  //insert new node and assign fields
			curr = (struct Student*) malloc(sizeof(struct Student));
			prev->next = curr;
			curr->next = NULL;
			curr->number = studentNumber;
			strcpy(curr->name, studentName);
			initializeMarks(curr);

		}
		return list;
	}
	else
	{
		printf("Sorry this ID is already in data\n");
		return list;
	}
}
struct Student* insertMark(struct Student* list, int studentNumber)
{
	struct Student* ptr;
	struct Student* prev;
	int found = 0;
	ptr = list;
	prev = NULL;
	while (ptr != NULL && found != 1) // if not found and not NULL keep advancing
	{
		if (ptr->number == studentNumber)
			found = 1;
		prev = ptr;
		ptr = ptr->next; //advance list
	}
	if (found == 1)
	{
		printf("Please enter a new mark\n");
		int mark;
		scanf("%d", &mark);
		int count = 0;
		while (prev->mark[count] != -1 && count <MAXVALUE)//go to end of entered marks
		{
			count++;
		}
		prev->mark[count] = mark;//update mark
	}
	else
		printf("Sorry Student could not be found\n");
	return list; // update list
}
struct Student* insertMarkAuto(struct Student* list, int studentNumber, int mark)
{ // same as insertMark but mark already obtained from other sources
	struct Student* ptr;
	struct Student* prev;
	int found = 0;
	ptr = list;
	prev = NULL;
	while (ptr != NULL && found != 1)
	{
		if (ptr->number == studentNumber)
			found = 1;
		prev = ptr;
		ptr = ptr->next;
	}
	if (found == 1)
	{
		int count = 0;
		while (prev->mark[count] != -1)
		{
			count++;
		}
		prev->mark[count] = mark;
	}
	else
		printf("Sorry Student could not be found\n");
	return list;
}
void initializeMarks(struct Student* node)
{ //initializes empty marks to -1
	for (int i = 0; i<MAXVALUE; i++)
		node->mark[i] = -1;
}
void printAll(struct Student* list)
{
	struct Student* curr;
	curr = list;
	while (curr != NULL)//while not at the end of list
	{
		printf("ID: %d\t Name: %s\n", curr->number, curr->name); //print all fields
		int count = 0;
		printf("Marks: ");
		while (curr->mark[count] != -1) //print each mark that is set by user
		{
			printf("%d\t", curr->mark[count]);
			count++;
		}
		printf("\n");
		curr = curr->next;//advance along list
	}
}
void printIndividual(struct Student* list, int studentNumber)
{
	struct Student* curr;
	curr = list;
	while (curr != NULL)//while not at end of list
	{
		if (curr->number == studentNumber) //if found
		{
			//print fields
			printf("ID: %d\t Name: %s\n", curr->number, curr->name);
			int count = 0;
			printf("Marks: ");
			while (curr->mark[count] != -1)
			{
				printf("%d\t", curr->mark[count]);
				count++;
			}
			printf("\n ");
		}
		curr = curr->next;//advance along list
	}
}
struct Student* readFromFile(struct Student* list)
{
	FILE* fp;//create file pointer
	if (!(fp = fopen("results.txt", "r")))//will be false if fp cant be opened
		return NULL;
	
	struct Student* curr;
	struct Student* prev;
	int done = 0;
	int ok;
	char tempName[MAXVALUE];
	int tempID;
	int tempMarks[MAXVALUE];
	curr = list;
	int count = 0;

	while (curr != NULL)
	{
		// go to the end of the list
		curr = curr->next;
	} 	while (done == 0) // while not at end of file
	{//scan for name
		ok = fscanf(fp, "%s", tempName); // if read properly returns 1

		if (ok == 1) //read properly
		{
			ok = fscanf(fp, "%d", &tempID);//scan for id
			int tempMark = -1;
			if (ok == 1) //if read properly
			{
				list = insert(list, tempID, tempName); //insert new node with id
				while (ok == 1)
				{
					ok = fscanf(fp, "%d", &tempMark);//read atleast first mark
					count++;
					if (ok == 1) // if mark is there insert mark to node
						list = insertMarkAuto(list, tempID, tempMark);
				}
			}
		}
		else//error or end of file
		{
			done = 1;
		}

	}
	fclose(fp);
	return list;

}

struct Student* removeNode(struct Student* list, int studentNumber)
{
	struct Student* foundPtr = searchStudent(list, studentNumber); //returns null if not found
	if (foundPtr == NULL)
	{
		printf("Sorry student not found\n");
	}
	else
	{
		struct Student* curr;
		struct Student* prev;
		curr = list;
		prev = NULL;
		while (curr->number != studentNumber) // go thtrough list keeping track of prev
		{
			prev = curr;
			curr = curr->next;
		}// we know it is in list from search Student
		 //create temp variable to store next
		 //link prev to next and delete curr
		struct Student* temp;
		temp = curr;
		curr = curr->next;
		prev->next = curr;
		free(temp);
	}
	return list; //update list
}
void removeAll(struct Student* list)
{
	//go through list and free all nodes
	struct Student* curr;
	struct Student* temp;
	curr = list;
	if (curr != NULL)
	{ //if not empty list
		while (curr != NULL) //advance along list and free all nodes
		{
			temp = curr;
			curr = curr->next;
			free(temp);
		}
	}
	list = NULL; //set list to NULL to signify empty
}

struct Student* searchStudent(struct Student* list, int studentNumber)
{ //returns NULL if not found
  //doesnt return actual node if found (sorry misleading name I guess))
	struct Student* curr;
	struct Student* prev;
	int found = 0;
	curr = list;
	prev = NULL;
	while (curr != NULL && found != 1)
	{
		if (curr->number == studentNumber)
			found = 1;
		prev = curr;
		curr = curr->next;
	}
	if (found)
		return list;
	else
		return NULL;
}

void saveToFile(struct Student* list)
{
	/*Note could be done with fwrite but this way creates more human readable file*/
	FILE* fp;//create file pointer
	fp = fopen("results.txt", "w"); //try to open file (dont append but rewrite if it exists)

	if (fp != NULL) //if no errors
	{
		struct Student* curr = list;
		while (curr != NULL) // go through list
		{
			fprintf(fp, "%s\n", curr->name); //print out each field with a newline
			fprintf(fp, "%d\n", curr->number);

			int count = 0;

			while (curr->mark[count] != -1)
			{
				fprintf(fp, "%d\n", curr->mark[count]);
				count++;
			}

			curr = curr->next;
		}

		fclose(fp);
	}
}
void saveFileTree(struct TreeNode** root) // tree implementation of save file
{
	FILE* fp; //open file
	fp = fopen("results.txt", "wb"); //binary file
	if (fp != NULL)
	{
		if (*root == NULL)
			printf("Sorry no Tree was found\n");
		else
		{
			printHelper(root, &fp); //helper function to print recursively reference to fp sent
		}
		fclose(fp);
	}
}
void printHelper(struct TreeNode** root, FILE** fp)
{

	if ((*root) != NULL)
	{
		fwrite((*root), sizeof(struct TreeNode), 1, *fp); //use fwrite to write node
		printHelper(&((*root)->left), fp);//advance along left root recursivly
		printHelper(&((*root)->right), fp);//advance along right root recursively
	}


}
void readFileTree(struct TreeNode** root) //tree implementation of read from file
{
	FILE* fp;
	fp = fopen("results.txt", "rb");

	struct TreeNode* temp;
	struct TreeNode* temp2;
	temp = (struct TreeNode*)malloc(sizeof(struct TreeNode)); //temp treeNode

	if (fp == NULL)
	{
		printf("Could not open file\n");
	}
	else
	{
		while (fread(temp, sizeof(struct TreeNode), 1, fp) == 1)//read new tree Node
		{
			insertTreeNode(root, temp); //insert into tree
			temp = (struct TreeNode*)malloc(sizeof(struct TreeNode));//allocate new memory
		}
	}
	fclose(fp);
}

//insert into tree recursively passing pointer to root and number + name
void insertTree(struct TreeNode** root, int studentNumber, char studentName[MAXVALUE])
{ 
	if ((*root) == NULL) //base case
	{
		printf("In if\n");
		(*root) = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		(*root)->number = studentNumber;
		strcpy((*root)->name, studentName);
		(*root)->left = NULL;
		(*root)->right = NULL;
		printf("Name: %s\n", (*root)->name);
		printf("ID: %d\n", (*root)->number);
		initializeMarksTree(root, studentNumber);

	}
	else
	{
		if ((*root)->number == studentNumber) //if already exists
		{
			printf("Sorry student number already in data\n");
		}
		else
		{
			if (studentNumber < (*root)->number) //need to search left tree
			{
				insertTree(&((*root)->left), studentNumber, studentName);
			}
			else if (studentNumber >(*root)->number) //need to search right tree
				insertTree(&((*root)->right), studentNumber, studentName);
		}
	}

}

//delete a node in binary tree by passing pointer to root ptr and student number
void deleteTree(struct TreeNode** root, int studentNumber)
{ 
	printf("Deleting \n");
	if ((*root) == NULL) //if tree is empty do nothing
	{
		printf("root is null \n");
	}
	else
	{
		if ((*root)->number > studentNumber)
		{
			deleteTree(&(*root)->left, studentNumber); //recurse down left side
		}
		else if ((*root)->number < studentNumber)
		{
			deleteTree(&(*root)->right, studentNumber); //recurse down right side
		}
		else
		{ //id of current node must be equal to studentNumber now
			if ((*root)->left == NULL && (*root)->right == NULL) //if no children
			{
				//only one node so free and set to null
				struct TreeNode* temp = (*root);
				free(temp);
				(*root) = NULL;
			}
			else if ((*root)->left == NULL) //if right child
			{
				//delete node in middle and rearange pointers
				struct TreeNode* temp = (*root);
				(*root) = (*root)->right;
				free(temp);
			}
			else if ((*root)->right == NULL)//if left child
			{
				//delete node in middle and rearange pointers
				struct TreeNode* temp = (*root);
				(*root) = (*root)->left;
				free(temp);
			}
		}
	}

}
void deleteAllTree(struct TreeNode** root)
{ //delete every node but root
	if ((*root)->left == NULL && (*root)->right == NULL)
	{ // no children so free the node and set to null
		printf("Freeing\n");
		free((*root));
		(*root) = NULL;
	}
	else
	{
		deleteAllTree(&((*root)->right)); //recurse through right side
		deleteAllTree(&((*root)->left)); // recurse through left side
	}
}


void insertTreeNode(struct TreeNode** root, struct TreeNode* node)
{ //insert an already made node into list
	struct TreeNode* curr;
	curr = (*root);
	if ((*root) == NULL) //if empty tree
		(*root) = node;//set tree to node
	else
	{
		while (curr->left != NULL && curr->right != NULL && curr->number != node->number)
		{ //while not at bottom and not found already
			if (node->number < (*root)->number)
			{   //advance along left side since node number is smaller than current number
				curr = curr->left;
			}
			else if (node->number >(*root)->number)
			{ //advance along right side since node number is bigger than current number
				curr = curr->right;
			}
		}
		if (curr->number == node->number)
			printf("Sorry student number already exists\n");
		else
		{ //at last position set to be right or left side depending on id value
			if (node->number < (*root)->number)
				curr->left = node;
			if (node->number >(*root)->number)
				curr->right = node;
		}

	}

}
void  insertTreeMark(struct TreeNode** root, int studentNumber, int mark)
{ //inserts a mark into a tree node that is already in tree
	struct TreeNode* temp = searchTree(root, studentNumber); /* returns null if not found,
															 returns node ptr if found */
	if (temp == NULL) //if cant be found
		printf("Sorry not found\n");
	else
	{
		int count = 0;
		while (temp->mark[count]>-1 && count < MAXVALUE)
		{//go through all entered marks
			count++;
		}
		temp->mark[count] = mark;
	}
}
struct TreeNode* getParent(struct TreeNode** root, struct TreeNode* child)
{ // returns the parent of node being searched for
	if ((*root)->left->number == child->number || (*root)->right->number == child->number)
		return (*root); // base case one of the children has same id as node sought after
	else if (child->number < (*root)->number) //if smaller recurse left side of tree
		return (getParent(&((*root)->left), (*root)));
	else //recurse right side of tree
		return (getParent(&((*root)->right), (*root)));
}

void printTree(struct TreeNode** root)
{ //print tree in order (top to bottom and left to right)
	if ((*root) != NULL)
	{ //print values of current node
		printf("Name: %s\n", (*root)->name);
		printf("ID: %d\n", (*root)->number);
		printf("Marks: ");
		for (int i = 0; i<MAXVALUE; i++)
		{//print each mark entered by human
			if ((*root)->mark[i]>-1)
				printf(" %d\t", (*root)->mark[i]);
		}
		printf("\n");
		printTree(&(*root)->left);//recurse left
		printTree(&(*root)->right); // recurse right
	}
}
void initializeMarksTree(struct TreeNode** root, int studentNumber)
{
	printf("In initialize\n");
	struct TreeNode* temp = searchTree(root, studentNumber); /* returns null if not found,
															 returns node ptr if found */
	if (temp == NULL) //if cant be found
		printf("Sorry not found\n");
	else
	{
		int count = 0;
		while (count < MAXVALUE)
		{//go through all entered marks
			temp->mark[count] = -1;
			count++;
		}

	}
}
/* Following functions are used to balance the three using AVL algorithm
In this algorithm trees are only allowed to be unbalanced by a maximum of
1 height. If height differs by 2 or more tree must be re-balanced using one of four
* rotations */

int treeNodeHeight(struct TreeNode* node)
{ 	int height_left = 0;
	int height_right = 0;

	if (node->left)
		height_left = treeNodeHeight(node->left); // recurse left side
	if (node->right)
		height_right = treeNodeHeight(node->right); //recurse right side

	return height_right > height_left ? ++height_right : ++height_left;
	//return the height of the node passed into it
	//recursively increase height and keep equal with prefix ++ 
}

int balanceFactor(struct TreeNode* node) {
	int factor = 0;

	if (node->left) factor += treeNodeHeight(node->left);
	if (node->right) factor -= treeNodeHeight(node->right);
	//gets the difference between the left height and right height using height function
	//returns balanceFactor for AVL balanced tree
	return factor;
}

struct TreeNode* rotateLeftLeft(struct TreeNode* node)
{ 
	struct TreeNode* x = node;
	struct TreeNode* y = x->right;
	x->left = y->right;
	y->right = x;
	return(y);
}
struct TreeNode* rotateLeftRight(struct TreeNode* node)
{ 
	struct TreeNode* x = node;
	struct TreeNode* y = x->right;
	struct TreeNode* z = y->right;
	//rotate around z
	x->right = z->left;
	y->left = z->right;
	z->right = y;
	z->left = x;

	return (z); // return middle
}
struct TreeNode* rotateRightRight(struct TreeNode* node)
{
	struct TreeNode* x = node;
	struct TreeNode*y = x->right;

	x->right = y->left;
	y->left = x;
	return(y);
}

struct TreeNode* rotateRightLeft(struct TreeNode* node)
{
	
	// left subtree is right heavy must rotate twice to re-balance
	struct TreeNode *x = node;
	struct TreeNode *y = x->right;
	struct TreeNode *z = y->left;


	x->right = z->left;
	y->left = z->right;
	z->right = y;
	z->left = x;

	return(z); //return middle
}
//balance the tree
struct TreeNode* balanceNode(struct TreeNode* node) {
	struct TreeNode *tmpRoot = NULL;

	//Balance children, if they exist 
	if (node->left)
		node->left = balanceNode(node->left);
	if (node->right)
		node->right = balanceNode(node->right);

	int balance = balanceFactor(node);

	if (balance >= 2) {
		//Left Heavy 	

		if (balanceFactor(node->left) <= -1) //Right heavy left side
			tmpRoot = rotateLeftRight(node);
		else //left heavy left side
			tmpRoot = rotateLeftLeft(node);

	}
	else if (balance <= -2) {
		// Right Heavy 

		if (balanceFactor(node->right) >= 1) //left heavy right side
			tmpRoot = rotateRightLeft(node);
		else //right heavy right side
			tmpRoot = rotateRightRight(node);

	}
	else {
		//Balanced no need for change
		tmpRoot = node;
	}

	return(tmpRoot);
}

//searchs through tree for node with id and returns that node
struct TreeNode* searchTree(struct TreeNode** root, int id)
{ 
	struct TreeNode* temp = *root;

	while (temp != NULL && temp->number != id)
	{
		if (id<temp->number)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}


