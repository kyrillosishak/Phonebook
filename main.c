#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char fname[15];
    char lname[15];
    date DOB;
    char address[40];
    char phonum[12];
    char email[20];
} contact;

int i, count = 0;
contact s[100];

void load(void);
void Search(void);
void Add(int f);
void Modify(void);
void Delete(void);
void printer(void);
void Sort(void);
void EXIT(void);
void save_data(void);
int menu(void);

int main()
{
    SetConsoleTitle("Phonebook");
    system("color 70");
    int x;
    while (1)
    {
        x = menu();
        switch (x)
        {
        case 1:
            load();
            break;

        case 2:
            Search();
            break;

        case 3:
            Add(404);
            break;

        case 4:
            Delete();
            break;

        case 5:
            Modify();
            break;

        case 6:
            printer();
            break;

        case 7:
            save_data();
            break;

        case 8:
            EXIT();
            break;

        default:
            printf("Please enter a valid number\n\n");
        }
    }
    return 0;
}

void load(void)
{
    FILE* f;
    char buff, filename[40];
    printf("Please enter file name in format filename.txt: ");
    scanf("%c", &buff);
    scanf("%{^\n]", filename);
    f = fopen(filename, "r");
    char temp[20], * token;
    if (f != NULL)
    {
        while (!feof(f))
        {
            fscanf(f, "%[^,], ", s[count].fname);

            fscanf(f, "%[^,], ", s[count].lname);

            fscanf(f, "%[^,], ", temp);
            token = strtok(temp, "/");
            s[count].DOB.day = atoi(token);
            token = strtok(NULL, "/");
            s[count].DOB.month = atoi(token);
            token = strtok(NULL, ",");
            s[count].DOB.year = atoi(token);

            fscanf(f, "%[^,], ", s[count].address);

            fscanf(f, "%[^,], ", s[count].phonum);

            fscanf(f, "%[^\n]\n", s[count].email);

            count++;
        }

        printf("Load is Done\n\n");
    }
    else
        printf("Error opening the file!! Please re-check filename and tryagain\n\n");
    fclose(f);
}

void Search(void)
{
    char entered_name[15];
    printf("Enter the last name: ");
    scanf("%s", entered_name);

    int check = 0;
    int x = strlen(entered_name);

    char srch[x];
    strcpy(srch, entered_name);

    for (i = 0; i < count; i++)
    {
        if (strcmp(srch, s[i].lname) == 0)
        {
            if (check == 0)printf("\nFound contacts :-\n");
            check = 1;

            printf("First name: %s\n", s[i].fname);
            printf("Last name: %s\n", s[i].lname);
            printf("Date of birth: %d/%d/%d\n", s[i].DOB.day, s[i].DOB.month, s[i].DOB.year);
            printf("Address: %s\n", s[i].address);
            printf("phone number: %s\n", s[i].phonum);
            printf("E-mail: %s\n\n", s[i].email);
        }
    }
    if (check == 1)
    {
        ("\nSearch is done!\n\n");
    }
    else
        printf("Name is not found!!\n\n");
}

void Add(int f)
{
    if (f == 404)f = count;
    char buff;
    printf("Enter the first name: ");
    scanf("%14s", s[f].fname);
    while (buff != '\n') scanf("%c", &buff);
    buff = 'c';

    printf("Enter the last name: ");
    scanf("%14s", s[f].lname);
    while (buff != '\n') scanf("%c", &buff);
    buff = 'c';

    do
    {
        printf("Enter the Date Of Birth: ");
        scanf("%d%d%d", &s[f].DOB.day, &s[f].DOB.month, &s[f].DOB.year);
        while (buff != '\n') scanf("%c", &buff);
        buff = 'c';
    } while ((s[f].DOB.day < 0 || s[f].DOB.day > 31) || (s[f].DOB.month > 12 || s[f].DOB.month < 0) || (s[f].DOB.year > 2020 || s[f].DOB.year < 1900));

    printf("Enter the address: ");
    scanf("%39[^\n]", s[f].address);
    while (buff != '\n') scanf("%c", &buff);
    buff = 'c';
    int z = 0;
    do
    {
        printf("Enter the phone number e.g(01123456789): ");
        scanf("%11s", s[f].phonum);
        while (buff != '\n') scanf("%c", &buff);
        buff = 'c';
        int x;
        z = 0;
        for (x = 0; x < 11; x++)
        {

            if (!isdigit(s[f].phonum[x]))
            {
                z = 1;
                printf("Invalid Phone number\n");
            }
        }
        if (s[f].phonum[0] != '0' || s[f].phonum[1] != '1')
        {
            z = 1;
            printf("Invalid Phone number\n");
        }
    } while (z);


    int check = 0, i = 0;
    char x[20], y = '@';

    while (check == 0)
    {
        printf("Enter the email : ");
        scanf("%19s", s[f].email);
        while (buff != '\n') scanf("%c", &buff);
        buff = 'c';

        strcpy(x, s[f].email);
        int z = strlen(x);

        for (i = 0; i < z; i++)
        {
            if (x[i] == '@' && x[0] != '@')
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            printf("Invalid email!!\n");
        }
    }
    if (f == count)
    {
        count++;
        printf("Add is done successfully!\n\n");
    }
}

void Modify(void)
{
    char entered_name[15];
    printf("Enter the last name: ");
    scanf("%s", entered_name);

    int check = 0;
    int x = strlen(entered_name);

    char srch[x];
    strcpy(srch, entered_name);

    for (i = 0; i < count; i++)
    {
        if (strcmp(srch, s[i].lname) == 0)
        {
            if (check == 0)printf("\nFound contacts :-\n");
            check++;

            printf("Contact number %d\n", i);
            printf("First name: %s\n", s[i].fname);
            printf("Last name: %s\n", s[i].lname);
            printf("Date of birth: %d/%d/%d\n", s[i].DOB.day, s[i].DOB.month, s[i].DOB.year);
            printf("Address: %s\n", s[i].address);
            printf("phone number: %s\n", s[i].phonum);
            printf("E-mail: %s\n\n", s[i].email);
        }
    }

    int y[check], z = 0;
    for (i = 0; i < count; i++)
    {
        if (strcmp(srch, s[i].lname) == 0)
        {
            y[z] = i;
            z++;
        }
    }

    if (check)
    {
        int n;
        z = 1;
        while (z)
        {
            printf("Please a Enter valid Contact number: ");
            scanf("%d", &n);

            for (i = 0; i < check; i++)
            {
                if (n == y[i]) z = 0;

            }
        }

        printf("Please re-enter the data\n");
        Add(n);
        printf("\nModification complete!\n\n");
    }
    else
        printf("Name is not found!!\n\n");
}

void Delete(void)
{
    char entered_name[15];
    printf("Enter the last name: ");
    scanf("%s", entered_name);

    int check = 0;
    int x = strlen(entered_name);

    char srch[x];
    strcpy(srch, entered_name);

    for (i = 0; i < count; i++)
    {
        if (strcmp(srch, s[i].lname) == 0)
        {
            if (check == 0)printf("\nFound contacts :-\n");
            check++;

            printf("Contact number %d\n", i);
            printf("First name: %s\n", s[i].fname);
            printf("Last name: %s\n", s[i].lname);
            printf("Date of birth: %d/%d/%d\n", s[i].DOB.day, s[i].DOB.month, s[i].DOB.year);
            printf("Address: %s\n", s[i].address);
            printf("phone number: %s\n", s[i].phonum);
            printf("E-mail: %s\n\n", s[i].email);
        }
    }

    int y[check], z = 0;
    for (i = 0; i < count; i++)
    {
        if (strcmp(srch, s[i].lname) == 0)
        {
            y[z] = i;
            z++;
        }
    }

    if (check)
    {
        int n;
        z = 1;
        while (z)
        {
            printf("Please a Enter valid Contact number: ");
            scanf("%d", &n);

            for (i = 0; i < check; i++)
            {
                if (n == y[i]) z = 0;
            }
        }
        count--;
        contact p[count];
        z = 0;
        for (i = 0; i < count + 1; i++)
        {
            if (i != n)
            {
                p[z] = s[i];
                z++;
            }
        }
        for (i = 0; i < count + 1; i++)
        {
            s[i] = p[i];
        }
        printf("\nDelete complete!\n\n");
    }
    else
        printf("Name is not found!!\n\n");
}

void printer(void)
{
    Sort();
    for (i = 0; i < count; i++)
    {
        printf("%s, ", s[i].fname);
        printf("%s, ", s[i].lname);
        printf("%d/%d/%d, ", s[i].DOB.day, s[i].DOB.month, s[i].DOB.year);
        printf("%s, ", s[i].address);
        printf("%s, ", s[i].phonum);
        printf("%s\n\n", s[i].email);
    }
    printf("Print is done!\n\n");
}

void Sort(void)
{
    int j, choise = 0;
    printf("1/Sort by last name\n");
    printf("2/Sort by date of birth\n");
    do
    {
        printf("Enter your choise: ");
        scanf("%d", &choise);
        i = 0;
        j = 0;
        contact temp;
        if (choise == 1)
        {
            for (i = 0; i < count; i++)
            {
                for (j = i + 1; j < count; j++)
                {
                    if (s[i].lname[0] > s[j].lname[0])
                    {
                        temp = s[i];
                        s[i] = s[j];
                        s[j] = temp;
                    }
                }
            }
        }
        else if (choise == 2)
        {
            for (i = 0; i < count; i++)
            {
                for (j = i + 1; j < count; j++)
                {
                    if (s[i].DOB.year > s[j].DOB.year)
                    {
                        temp = s[i];
                        s[i] = s[j];
                        s[j] = temp;
                    }
                    else if (s[i].DOB.year == s[j].DOB.year && s[i].DOB.month > s[j].DOB.month)
                    {
                        temp = s[i];
                        s[i] = s[j];
                        s[j] = temp;
                    }
                    else if (s[i].DOB.year == s[j].DOB.year && s[i].DOB.month == s[j].DOB.month && s[i].DOB.day > s[j].DOB.day)
                    {
                        temp = s[i];
                        s[i] = s[j];
                        s[j] = temp;
                    }
                }
            }
        }
    } while (choise != 1 && choise != 2);
}

void EXIT(void)
{
    int n;
    printf("Are you sure you want to exit? (Any unsaved data will be lost!) \n 1-yes\n 2-no\n");
    scanf("%d", &n);
    switch (n)
    {
    case 2:
        break;
    case 1:
        printf("program exit successfully!\n");
        exit(0);
    default:
        printf("Please enter a valid 1 or 2 only\n");
    }
}

void save_data(void)
{
    char buff, filename[40];
    printf("Please enter a file name in which data will be saved e.g(filename.txt): ");
    scanf("%c", &buff);
    scanf("%{^\n]", filename);
    FILE* f;
    f = fopen(filename, "w");
    printf("Saving...\n");
    for (i = 0; i < count; i++)
    {
        fprintf(f, "%s, ", s[i].fname);
        fprintf(f, "%s, ", s[i].lname);
        fprintf(f, "%d/%d/%d, ", s[i].DOB.day, s[i].DOB.month, s[i].DOB.year);
        fprintf(f, "%s, ", s[i].address);
        fprintf(f, "%s, ", s[i].phonum);
        fprintf(f, "%s\n", s[i].email);
    }
    printf("Your work has been saved!\n");
    fclose(f);
}

int menu(void)
{
    int x = 0;
    printf("Operations:\n1-Load\n2-Search\n3-Add\n4-Delete\n5-Modify\n6-Print\n7-Save\n8-Exit\nEnter number of operation:\n");
    scanf("%d", &x);
    return x;
}
