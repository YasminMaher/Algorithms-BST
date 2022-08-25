#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct  {
    char lastname[16];
    char firstname[11];
    char phone[11];
} user;


struct tree_node {
    user data;
    struct tree_node *left;
    struct tree_node *right;
};


struct tree_node * insert(struct tree_node *p, user e);
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, user e);
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]);
struct tree_node * findmin(struct tree_node *p);
void search_node(struct tree_node *p, char l[], char pho[]);
void print_tree(struct tree_node *p);
void inorderlist (struct tree_node *p);
void postorderlist(struct tree_node *p);

int main(void)
{
    int option = 0; /*Variable for option selection.*/
    user e;  /*Basic phone book entry*/
    struct tree_node *p = NULL;
    char ln[16];
    char fn[11];
    char ph[11];

    //main menu
    while (option != 8) {

        printf("MENU\n");
        printf("1. Add\n");
        printf("2. Delete\n");

        printf("4. Search\n");
        printf("5. inorderList\n");
        printf("6. preorderlist\n");
        printf("7. postorderlist\n");

        printf("8. Quit\n");

        printf("\nPlease select an option: ");
        scanf("%d", &option);

        if (option == 1) {

            printf("Please enter the last name: ");
            scanf("%s", &e.lastname);
            printf("Please enter the first name: ");
            scanf("%s", &e.firstname);
            printf("Please enter the phone number: ");
            scanf("%s", &e.phone);

            /*Create a new node.*/
            p = insert(p, e);

            printf("name added\n\n");
        }

        else if (option == 2) {

            printf("Please enter the last name: ");
            scanf("%s", &ln);
            printf("Please enter the phone number: ");
            scanf("%s", &ph);
            /*Delete a node.*/
            p = delete_node(p, ln, ph);
        }



        else if (option == 4) {

            printf("Please enter the last name: ");
            scanf("%s", &ln);
            printf("Please enter the phone number: ");
            scanf("%s", &ph);
            /*Search for a node.*/
            search_node(p, ln, ph);
        }

        else if (option == 5) {
            print_tree(p);
        }
        else if (option ==6 ){
            preorderlist (p);
        }
        else if (option == 7){
            postorderlist (p);
        }

        /*If option is 6 (Quit):*/
        else if (option == 8) {
            /*End the program.*/
            break;
        }

        else {
            /*Print error message.*/
            printf("That option does not exist. Please try again.\n\n");
        }

    }
    return 0;
}


/*Adds a node to the tree.*/
struct tree_node * insert(struct tree_node *p, user e) {
    /*If there is no root:*/
    if (p == NULL) {
        /*Create a root.*/
        p = create_node(NULL, NULL, e);
    }
    /*If there is a root, and the entry belongs before the root:*/
    else if (strcmp(e.lastname, p->data.lastname) < 0) {
        /*Add before root.*/
        p->left = insert(p->left, e);
    }
    /*If there is a root, and the entry belongs after the root:*/
    else if (strcmp(e.lastname, p->data.lastname) > 0) {
        /*Add after root.*/
        p->right = insert(p->right, e);
    }
    /*If there is a root, and the lastnames are identical: */
    else {
        /*If entry belongs before root: */
        if (strcmp(e.firstname, p->data.firstname) < 0) {
            /*Add before root.*/
            p->left = insert(p->left, e);
        }
        /*If entry belongs after root: */
        else if (strcmp(e.firstname, p->data.firstname) > 0) {
            /*Add after root.*/
            p->right = insert(p->right, e);
        }
        /*If entries are the same: */
        else {
            /*Do nothing.*/
            return p;
        }
    }
    /*Return revised tree.*/
    return p;
}

/*Creates a new node.*/
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, user e) {
    struct tree_node* newnode;
    newnode = (struct tree_node*)(malloc(sizeof(struct tree_node)));
    newnode->data = e;
    newnode->left = q;
    newnode->right = r;
    return newnode;
}

/*Deletes a node from the tree.*/
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]) {
    /*If entry is before root:*/
    if (strcmp(l, p->data.lastname) < 0 || strcmp(f, p->data.firstname) != 0) {
        /*Delete from before root.*/
        p->left = delete_node(p->left, l, f);
    }
    /*If entry is after root:*/
    else if (strcmp(l, p->data.lastname) > 0 || strcmp(f, p->data.firstname) != 0) {
        /*Delete from after root.*/
        p->right = delete_node(p->right, l, f);
    }
    /*If entry is located and has a left and right branch:*/
    else if (p->left != NULL && p->right != NULL) {
        /*Find which branch moves up in the tree.*/
        p->data = findmin(p->right)->data;
        p->right = delete_node(p->right, l, f);
        /*Confirm node deletion.*/
        printf("Record deleted successfully.\n\n");
    }
    /*If entry is located and has a left branch:*/
    else if (p->left != NULL) {
        /*Move left branch up.*/
        p = p->left;
        /*Confirm node deletion.*/
        printf("Record deleted successfully.\n\n");
    }
    /*If entry is located and has a right branch:*/
    else if (p->right != NULL) {
        /*Move right branch up.*/
        p = p->right;
        /*Confirm node deletion.*/
        printf("Record deleted successfully.\n\n");
    }
    /*If entry is not found:*/
    else {
        /*Error.*/
        printf("Record could not be found.\n\n");
    }
    /*Return revised tree.*/
    return p;
}

/*Finds the leftmost node in the right branch.*/
struct tree_node * findmin(struct tree_node *p) {
    /*If left node is not empty.*/
    if (p->left != NULL) {
        /*Go to the left node.*/
        findmin(p->left);
    }
    /*Return leftmost node.*/
    return p;
}


/*Searches for a node and retrieves data.*/
void search_node(struct tree_node *p, char l[], char pho[]) {
    /*If entry is before root:*/
    if (strcmp(l, p->data.lastname) < 0) {
        /*Check before root.*/
        search_node(p->left, l, pho);
    }
    /*If entry is after root:*/
    else if (strcmp(l, p->data.lastname) > 0) {
        /*Check after root.*/
        search_node(p->right, l, pho);
    }
    /*If last name is found and first names are different:*/
    else if (strcmp(l, p->data.lastname) == 0 && strcmp(pho, p->data.phone) != 0) {
        /*If entry is before root.*/
        if (strcmp(pho, p->data.phone) < 0) {
            /*Check before root.*/
            search_node(p->left, l, pho);
        }
        /*If entry is after root.*/
        if (strcmp(pho, p->data.phone) > 0) {
            /*Check after root.*/
            search_node(p->right, l, pho);
        }
    }
    /*If entry is located:*/
    else if (strcmp(l, p->data.lastname) == 0 && strcmp(pho, p->data.phone) == 0) {
        /*Print out data.*/
        printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone);
    }
    /*If entry is not found:*/
    else {
        /*Error.*/
        printf("Record could not be found.\n\n");
    }
}

/*Prints contents of tree. inorderlist*/
void print_tree(struct tree_node *p)
{
    /*If tree has nodes:*/
    if (p != NULL) {
        /*Print node data.*/
        print_tree(p->left);
        printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone);
        print_tree(p->right);
    }
}

void preorderlist (struct tree_node *p){
      if (p != NULL) {
        /*Print node data.*/

        printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone);
        preorderlist(p->left);
        preorderlist(p->right);

    }
}

void postorderlist (struct tree_node *p){
     if (p != NULL) {



        postorderlist(p->left);
        postorderlist(p->right);
        printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone);


}
}




