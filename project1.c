//Departmental Store Management System by Nandini Agrawal, 2K20/B5/27
#include <stdio.h>
//Two File Pointers are necessary for deletion function.
FILE *f;
FILE *fp;
//Declaration of Main Functions.
int add_good();
void view_good();
int delete_good();
void calculate_bill();
void display_good();
static int total_number;
struct good
{
    char name[20];
    char code[5];
    int quantity;
    float price;
} product[20], search_key;
main()
{
    f = fopen("good_details.txt", "r");
    int tem = 0;
    while (feof(f) == 0)
    {
        char test[20];
        fgets(test, 100, f);
        tem += 1;
    }
    fclose(f);
    total_number = (tem - 1) / 4;
    //This is done to calculate the total number of items in inventory.
    int N;
    printf(" \n \t ==============================================================\n");
    printf("  \t \t \t \t    WELCOME TO \n \t \t \n \t \t \t THE URBAN FRESH DEPARTMENTAL STORE  \n");
    printf("  \t ==============================================================\n");
    printf(" \n \n ");
    //For making the menu, concept of switch has been used. While loop will run till 6 is not pressed.
    while (1)
    {
        putchar('\n');
        putchar('\n');
        printf(" \t \t \t \t   MAIN MENU \n ");
        printf(" \n \n ");
        printf(" \t \t \t  1)Press 1 to CALCULATE BILL \n ");
        printf(" \t \t \t  2)Press 2 to ADD GOODS \n ");
        printf(" \t \t \t  3)Press 3 to DELETE GOODS \n ");
        printf(" \t \t \t  4)Press 4 to DISPLAY ALL GOODS \n ");
        printf(" \t \t \t  5)Press 5 to SEARCH GOODS \n ");
        printf(" \t \t \t  6)Press 6 to EXIT PROGRAM \n ");
        putchar('\n');
        printf(" \t \t \t  Enter your choice : ");
        scanf("%d", &N);
        switch (N)
        {
        case 1:
            printf(" \t ==============================================================\n");
            printf(" \t \t \t \t   CALCULATE BILL\n");
            printf(" \t ==============================================================\n");
            putchar('\n');
            calculate_bill();
            break;

        case 2:
            printf(" \t ==============================================================\n");
            printf(" \t \t \t \t   ADD GOODS \n");
            printf(" \t ==============================================================\n");
            putchar('\n');
            add_good();
            break;

        case 3:
            printf("\t  ==============================================================\n");
            printf(" \t \t \t \t   DELETE GOODS \n");
            printf("\t  ==============================================================\n");
            putchar('\n');
            delete_good();
            break;

        case 4:
            printf(" \t ==============================================================\n");
            printf(" \t \t \t \t   DISPLAY ALL GOODS \n");
            printf(" \t ==============================================================\n");
            putchar('\n');
            display_good();
            break;

        case 5:
            printf(" \t ==============================================================\n");
            printf(" \t \t \t \t   SEARCH GOODS \n");
            printf(" \t ==============================================================\n");
            putchar('\n');
            view_good();
            break;

        case 6:
            return 0;

        default:
            printf(" Please enter a VALID CHOICE \n");
        }
    }
}
//Function to add goods.
int add_good()
{
    f = fopen("good_details.txt", "a+");
    printf("Enter The Name Of Product: ");
    scanf("%s",product[0].name);

    printf("Enter The Code Of Product: ");
    scanf("%s",product[0].code);

    printf("Enter The Current Quantity Of Product: ");
    scanf("%d", &product[0].quantity);

    printf("Enter The Price Of Product: ");
    scanf("%f", &product[0].price);

    fprintf(f, "%s\n%s\n%d\n%f\n", product[0].name, product[0].code, product[0].quantity, product[0].price);
    fclose(f);
    printf("Product added to the system successfully!\n");
    total_number = total_number + 1;
    putchar('\n');
    return (0);
}
//Function to search goods.
view_good()
{
    int flag = 0;
    f = fopen("good_details.txt", "r");
    printf("Enter The Product Name To Be Searched: ");
    char key[20];
    scanf("%s", key);
    for (int i = 0; i < total_number; i++)
    {
        fscanf(f, "%s", search_key.name);
        if (strcmp(key, search_key.name) == 0)
        {
            printf("Product has been found! \n");
            fscanf(f, "%s%d%f", &search_key.code, &search_key.quantity, &search_key.price);
            printf("Name                \tCode \t\tCurrent Quantity\t\tPrice\n");
            printf("%-20s\t%s\t\t%-16d\t\t%f\n", search_key.name, search_key.code, search_key.quantity, search_key.price);
            flag = 1;
            break;
        }
        fseek(f, 24, 1);
    }
    fclose(f);
    if (flag == 0)
    {
        printf("Product not found!");
    }
    putchar('\n');
}
//Function to delete goods
int delete_good()
{
    f = fopen("good_details.txt", "r");
    printf("Enter The Product Name To Be Deleted: ");
    char key[20];
    scanf("%s", key);

    int key_no = 100;
    int flag = 0;
    int i;
    for (i = 0; i < total_number; i++)
    {
        fscanf(f, "%s", search_key.name);
        if (strcmp(key, search_key.name) == 0)
        {
            key_no = i;
            flag = 1;
        }
        fseek(f, 24, 1);
    }
    if (flag == 0)
    {
        printf("Product not found!");
    }
    fclose(f);
    if (flag != 0)
    {

        f = fopen("good_details.txt", "r");
        fp = fopen("temp.txt", "w");
        char str[20];
        int t = 0;
        while (feof(f) == 0)
        {
            fgets(str, 20, f);
            if (t < (key_no * 4))
            {
                fprintf(fp, "%s", str);
            }
            else if (t > ((key_no * 4) + 3) && t < (total_number * 4))
            {
                fprintf(fp, "%s", str);
            }
            t = t + 1;
        }
        fclose(f);
        fclose(fp);
        remove("good_details.txt");
        rename("temp.txt", "good_details.txt");
        total_number = total_number - 1;
        putchar('\n');
        printf("Product has been successfully deleted!");
        putchar('\n');
    }
}

//Function to calculate bill
void calculate_bill()
{
    int i;
    float total_amount = 0;
    f = fopen("good_details.txt", "r");
    for (i = 0; i < total_number; i++)
    {
        fscanf(f, "%s%s%d%f", product[i].name, product[i].code, &product[i].quantity, &product[i].price);
    }
    fclose(f);
    f = fopen("good_details.txt", "r+");
    printf("Calculation of bill: \n");
    putchar('\n');
    printf("Enter item name and quantity. Write Exit to print bill. \n");
    putchar('\n');
    int j = 0, k = 0;
    i = 0;
    int flag = 0;
    int arr[20];
    int bill_quantity[20];
    while (1)
    {
        char bill_name[20];
        scanf("%s", bill_name);
        if (strcmp(bill_name, "Exit") == 0)
        {
            break;
        }
        scanf("%d", &bill_quantity[j]);
        for (i = 0; i < total_number; i++)
        {
            if (strcmp(bill_name, product[i].name) == 0)
            {
                arr[k] = i;
            }
            else
            {
                continue;
            }
        }
        if (bill_quantity[j] > product[arr[k]].quantity)
        {
            printf("Not enough quantity in inventory. Only %d units available!\n\n", product[k].quantity);
            flag = 1;
        }
        else
        {
            printf("Product added in bill. \n\n");
            flag = 0;
        }
        if (flag == 0)
        {
            k = k + 1;
            j += 1;
        }
    }
    putchar('\n');
    putchar('\n');
    printf("Printing of Bill: \n");
    putchar('\n');
    printf("S.No. Name                \tCode \t\t    Quantity    \t\tPrice\n");
    int r = 1;

    for (int m = 0; m < k; m++)
    {
        printf("%-6d%-20s\t%s\t\t    %-16d\t\t%f\n", r, product[arr[m]].name, product[arr[m]].code, bill_quantity[m], product[arr[m]].price);
        total_amount += (bill_quantity[m] * product[arr[m]].price);
        r += 1;
    }

    printf("                                                                         Total: %f\n", total_amount);
    putchar('\n');
    fclose(f);

    for (int m = 0; m < k; m++)
    {
        product[arr[m]].quantity -= bill_quantity[m];
    }
    f = fopen("good_details.txt", "r+");
    for (int g = 0; g < total_number; g++)
    {
        fprintf(f, "%s\n%s\n%d\n%f\n", product[g].name, product[g].code, product[g].quantity, product[g].price);
    }
    fclose(f);
}
//Function to display all goods in the inventory.
void display_good()
{
    int i;
    f = fopen("good_details.txt", "r");
    for (i = 0; i < total_number; i++)
    {
        fscanf(f, "%s%s%d%f", product[i].name, product[i].code, &product[i].quantity, &product[i].price);
    }
    printf("Name                \tCode \t\tCurrent Quantity\t\tPrice\n");
    for (i = 0; i < total_number; i++)
    {
        printf("%-20s\t%s\t\t%-16d\t\t%f\n", product[i].name, product[i].code, product[i].quantity, product[i].price);
    }
    fclose(f);
    putchar('\n');
}
