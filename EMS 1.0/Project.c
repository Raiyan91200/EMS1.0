#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct emp
{
    char name[80];
    int emp_id;
    int salary;
    char password[32];
    char designation[32];
    struct personalinfo
    {

        char emailid[20];
        char ph_no[10];

    } pi;
};
int main()
{

    struct emp e;
    int recsize;
    int tot_rec;

    int c = 0;
    FILE *fp = NULL;
    FILE *ft = NULL;

    char another;
    int choice;

    char password[32];
    int id;

    // FUNCTION DECLARATIONS
    void swap(struct emp *, struct emp *);

    int checkentry(int, char[32], FILE *);

    struct emp read_rec();

    void view_rec(struct emp);

    void sort_sal_asc(FILE *, int);
    void sort_sal_desc(FILE *, int);
    fp = fopen("EMP.DAT", "rb+");

    if (fp == NULL)
    {
        fp = fopen("EMP.DAT", "wb+");
        if (fp == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }

    recsize = sizeof(e);
    printf("\n\n\n\n\t\t\t\t============="
           "============================="
           "=====================");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~");
    printf("\n\t\t\t\t==================="
           "======================================="
           "=====");
    printf("\n\t\t\t\t[|:::>:::>:::>::> "
           "EMPLOYEE MANAGEMENT SYESTEM <::<:::<:::"
           "<:::|]\t");
    printf("\n\t\t\t\t==================="
           "======================================="
           "=====");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~");
    printf("\n\t\t\t\t====================="
           "==========================================\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t"

           "\n\n\t\t\t\t");

    system("pause");
    system("cls");

    while (1)
    {

        printf("\n\n 1. Add Record");
        printf("\n 2. List Records");
        printf("\n 3. Modify Records");
        printf("\n 4. Delete Records");
        printf("\n 5. Search Records");
        printf("\n 6. Sort Records");
        printf("\n 7. Change password");
        printf("\n 8. Exit");
        printf("\n Your Choice: ");
        scanf("%d", &choice);

        switch (choice)

        {
        case 1: // ADD RECORD
            fseek(fp, 0, SEEK_END);

            another = 'y';
            while (another == 'y')
            {
                e = read_rec();

                fwrite(&e, recsize, 1, fp);

                printf("\n Add another record(y/n) ");

                fflush(stdin);

                another = getchar();
            }
            system("cls");
            break;

        case 2: // VIEW or LIST
            printf("\n==================================="
                   "============================"
                   "=================================================================");
            printf("\nNAME\t\tEMP_ID\t\tDESIGNATION\tSALARY"
                   "\t\tMAIL\t\t\t\tCONTACT\t\t\tPASSWORD\t\t\n");
            printf("====================================="
                   "============================"
                   "===============================================================\n");
            rewind(fp);
            if (fread(&e, recsize, 1, fp) == 0)
                printf(" List is empty");
            rewind(fp);
            while (fread(&e, recsize, 1, fp))
            {

                view_rec(e);
            }
            system("pause");
            system("cls");
            break;

        case 3: // MODIFY
            rewind(fp);
            if (fread(&e, recsize, 1, fp) == 0)
                printf(" List is empty");
            else
            {
                another = 'y';
                while (another == 'y')
                {
                    printf("\n Enter the employee id to modify : ");
                    scanf("%d", &id);
                    fflush(stdin);
                    printf("\n To modify you need to enter password: ");
                    scanf("%s", password);
                    rewind(fp);
                    if (checkentry(id, password, fp))
                    {
                        rewind(fp);
                        while (fread(&e, recsize, 1, fp))
                        {
                            if ((e.emp_id == id) && (strcmp(password, e.password) == 0))
                            {
                                e = read_rec();
                                fseek(fp, -recsize, SEEK_CUR);
                                fwrite(&e, recsize, 1, fp);
                                printf("\n Modification Successful ");
                                break;
                            }
                        }
                    }
                    else
                        printf("\n No Record Found");

                    printf("\n Modify another record(y/n)");
                    fflush(stdin);
                    another = getchar();
                }
            }
            system("cls");
            break;

        case 4: // DELETE
            rewind(fp);
            if (fread(&e, recsize, 1, fp) == 0)
                printf(" List is empty");
            else
            {
                another = 'y';
                while (another == 'y')
                {
                    printf("\n Enter the employee id to delete : ");
                    scanf("%d", &id);
                    fflush(stdin);
                    printf("\n To delete you need to enter employee password: ");
                    scanf("%s", password);

                    ft = fopen("Temp.dat", "wb");
                    rewind(fp);
                    if (checkentry(id, password, fp))
                    {
                        rewind(fp);
                        while (fread(&e, recsize, 1, fp) == 1)
                        {
                            if ((e.emp_id == id) && (strcmp(password, e.password) == 0))
                                continue;
                            else
                                fwrite(&e, recsize, 1, ft);
                        }

                        fclose(fp);
                        fclose(ft);

                        remove("EMP.DAT");
                        rename("Temp.dat", "EMP.DAT");

                        fp = fopen("EMP.DAT", "rb+");
                        printf("\n Record Deleted Successfully ");
                        printf("\n Delete another record(y/n)");

                        fflush(stdin);

                        another = getchar();
                    }
                    else
                    {
                        printf("\n No Record Found");
                        printf("\n Delete another record(y/n)");
                        fflush(stdin);
                        another = getchar();
                    }
                }
            }
            system("cls");
            break;

        case 5: // SEARCH
            tot_rec = 0;
            rewind(fp);
            while (fread(&e, recsize, 1, fp))
            {

                tot_rec++;
            }

            if (tot_rec == 0)
                printf("List is empty");
            else
            {
                another = 'y';
                while (another == 'y')
                {
                    fflush(stdin);

                    printf("\n Enter the employee id to search : ");
                    scanf("%d", &id);

                    rewind(fp);
                    c = 0;
                    while (fread(&e, recsize, 1, fp))
                    {
                        c++;
                        if ((e.emp_id == id))
                        {
                            fflush(stdin);
                            printf("\n Record found . Do you want to see it ?(y/n) ");
                            another = getchar();
                            if (another == 'y')
                            {
                                view_rec(e);
                                break;
                            }
                            else if (another == 'n')
                                break;
                            else
                                printf("\n Invalid Selection");
                        }
                        if (c == tot_rec)
                            printf("\n No record found.");
                    }

                    printf("\n Search another record(y/n)");
                    fflush(stdin);
                    another = getchar();
                }
            }
            system("cls");
            break;

        case 6: // SORT
            tot_rec = 0;
            rewind(fp);
            while (fread(&e, recsize, 1, fp))
            {

                tot_rec++;
            }

            if (tot_rec == 0)
                printf("List is empty");
            else
            {
                printf("\n 1. To Sort the list based on Salary\n Your Choice : ");
                scanf("%d", &choice);
                rewind(fp);
                switch (choice)
                {

                case 1: // sort salary wise

                    printf("\n 1. To Sort the list based on Salary in Ascending order\n 2. To Sort the list based on Salary in Descending order \n Your Choice : ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1: // sort salary ascending

                        sort_sal_asc(fp, tot_rec);
                        rewind(fp);

                        while (fread(&e, recsize, 1, fp))
                        {

                            view_rec(e);
                        }
                        break;
                    case 2: // sort salary descending
                        sort_sal_desc(fp, tot_rec);
                        rewind(fp);

                        while (fread(&e, recsize, 1, fp))
                        {

                            view_rec(e);
                        }
                        break;
                    default:
                        printf("invalid entry");
                    }
                    break;

                default:
                    printf("invalid entry");
                }
            }
            system("pause");
            system("cls");
            break;

        case 7: // Change Password
            rewind(fp);
            if (fread(&e, recsize, 1, fp) == 0)
                printf(" List is empty");
            else
            {
                another = 'y';
                while (another == 'y')
                {

                    printf("\n Enter the employee id to change password : ");
                    scanf("%d", &id);

                    fflush(stdin);
                    printf("\n To modify you need to enter old password: ");
                    scanf("%s", password);
                    rewind(fp);
                    if (checkentry(id, password, fp))
                    {
                        rewind(fp);
                        while (fread(&e, recsize, 1, fp))
                        {
                            if ((e.emp_id == id) && (strcmp(password, e.password) == 0))
                            {
                                fflush(stdin);

                                printf("\n Enter New Password :- ");
                                scanf("%s", e.password);
                                while (1)
                                {

                                    fflush(stdin);

                                    printf("\n Confirm New Password :- ");
                                    scanf("%s", password);

                                    if (strcmp(e.password, password) == 0)
                                        break;
                                    else
                                    {
                                        printf("\n Enter New Password :- ");
                                        scanf("%s", e.password);
                                    }
                                }
                                fseek(fp, -recsize, SEEK_CUR);
                                fwrite(&e, recsize, 1, fp);
                                printf("\n Your Password is changed Successfully ");
                                break;
                            }
                        }
                    }
                    else
                        printf("\n No record found");
                    printf("\n Change password of another record (y/n)");
                    fflush(stdin);
                    another = getchar();
                }
            }
            system("cls");
            break;
        case 8:

            fclose(fp);
            exit(0);

        default:
            printf("Invalid Entry");
        }
    }
    return 0;
}

void swap(struct emp *x, struct emp *y)
{
    struct emp temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

struct emp read_rec()
{
    struct emp e;
    char password[32];

    fflush(stdin);

    printf("\n Enter Employee Name :- ");
    scanf("%[^\n]s", e.name);

    printf("\n Enter Employee id :- ");
    scanf("%d", &e.emp_id);

    printf("\n Enter Employee designation :- ");
    scanf("%s", &e.designation);

    printf("\n Enter Employee Salary :- ");
    scanf("%d", &e.salary);
    fflush(stdin);

    printf("\n Enter Password :- ");
    scanf("%s", e.password);
    while (1)
    {

        fflush(stdin);

        printf("\n Confirm Password :- ");
        scanf("%s", password);

        if (strcmp(e.password, password) == 0)
            break;
        else
        {
            printf("\n Enter Password :- ");
            scanf("%s", e.password);
        }
    }

    fflush(stdin);

    printf("\n Enter Employee Email id :- ");
    scanf("%s", e.pi.emailid);

    printf("\n Enter Employee Phone number :- ");
    scanf("%s", e.pi.ph_no);

    return e;
}

void view_rec(struct emp e)
{

    printf("\n%s\t\t", e.name);
    printf("%d\t\t", e.emp_id);
    printf("%s\t\t", e.designation);
    printf("%d\t\t", e.salary);
    printf("%s\t\t", e.pi.emailid);
    printf("%s\t", e.pi.ph_no);
    printf("%s\t\t\n\n", e.password);
}

void sort_sal_asc(FILE *fp, int n)
{
    struct emp e;
    struct emp f;
    int i, j;
    long int recsize = sizeof(e);

    for (i = 0; i < n - 1; i++)
    {
        fread(&e, recsize, 1, fp);
        fread(&f, recsize, 1, fp);

        if (e.salary > f.salary)
        {
            swap(&e, &f); // function call

            fseek(fp, -2 * recsize, SEEK_CUR);
            fwrite(&e, recsize, 1, fp);
            fwrite(&f, recsize, 1, fp);
            rewind(fp);
            i = -1;
        }

        fseek(fp, -recsize, SEEK_CUR);
    }
}

void sort_sal_desc(FILE *fp, int n)
{
    struct emp e;
    struct emp f;
    int i, j;
    long int recsize = sizeof(e);

    for (i = 0; i < n - 1; i++)
    {
        fread(&e, recsize, 1, fp);
        fread(&f, recsize, 1, fp);

        if (e.salary < f.salary)
        {
            swap(&e, &f); // function call

            fseek(fp, -2 * recsize, SEEK_CUR);
            fwrite(&e, recsize, 1, fp);
            fwrite(&f, recsize, 1, fp);
            rewind(fp);
            i = -1;
        }

        fseek(fp, -recsize, SEEK_CUR);
    }
}

int checkentry(int id, char password[32], FILE *fp)
{
    struct emp e;
    int recsize = sizeof(e);

    while (fread(&e, recsize, 1, fp))
    {
        if ((e.emp_id == id) && strcmp(e.password, password) == 0)
        {
            return 1;
        }
    }
    return 0;
}
