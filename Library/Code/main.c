#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct
{
    char tit[100];
    char aut[100];
    char pub [100];
    char isbn[50];
    char date[50];
    int copy;
    int avcopy;
    char cat[50];
    int borrow;
} books;
typedef struct
{
    char lastn[20];
    char firstn[20];
    int id;
    char street[20];
    char city[20];
    int phone;
    int age ;
    char email[50];
} member;
typedef struct
{
    int day;
    int month;
    int yr;
} date;
typedef struct
{
    char ISBN [50];
    int ID;
    date d_b;
    date d_due;
    date d_r;
} brw;
void main2 ();
void addBook(books*);
void searchBooks(books *book,int n);
void addCopy(books *book);
void deleteBook(books*book);
void updateAvcopy(char*s,books *book,int n);
void addMember(member*m);
void borrowBook(brw*b,books*book);
void returnBook (brw *b,books*book);
void popularBooks(books*book);
void deleteMax(books*book, int c);
int readMemberFile(char *fname,member *s);
int readBorrowFile(char *fname,brw *s);
int readBookFile(char*filename,books *book);
void overdue(brw*b);
int date_cmp(date d1,date d2);
char *strarr(char*s);
int choice,m,i,j,n;



int main()
{

    books *book=malloc(sizeof(books)*100);
    printf("\t\tWelcome to the WORLD OF BOOK EXPLORATION \n");
    popularBooks(book);
    m=readBookFile("mostpopular.txt",book);
    printf("Highly recommended books!!\n");
    for(i=0; i<m; i++)
    {
        printf("%s\n",book[i].tit);
    }

    copyFile("books.txt","booksnew.txt");
    copyFile("Members.txt","Membersnew.txt");
    copyFile("brw.txt","brwnew.txt");
    main2();

    return 0;
}
void main2 ()
{
    int dest;
    books *book=malloc(sizeof(books)*100);
    brw *b=malloc(sizeof(brw)*100);
    member *m=malloc(sizeof(member)*100);
    printf("\n1)Book Management\n2)Member Management\n3)Borrow Management\n4)Administrative Actions\n5)Save and exit\n6)Exit\n");

    printf("Choose your destination :");
    scanf("%d",&dest);
    system("cls");

    switch(dest)
    {
    case (1):
    {
        printf("1)Add a book\n2)Search for a book\n3)Add a copy\n4)Delete a book\n");
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:

            system("cls");
            addBook(book);
            break;
        case 2:
            system("cls");
            searchBooks(book,1);
            break;
        case 3:
            system("cls");
            addCopy(book);
            break;
        case 4:
            system("cls");
            deleteBook(book);
            break;
        default:
            break;

        }
    }
    break;
    case 2:
    {
        printf("1)Add member\n2)Remove member\n\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            system("cls");
            addMember(m);
            break;
        case 2:
            system("cls");
            break;
        default:
            break;
        }
    }
    break;
    case 3:
    {
        printf("1)Borrow a book\n2)Return a book\n\n");
        printf("Enter option:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            system("cls");
            borrowBook(b,book);
            break;
        case 2:
            system("cls");
            returnBook(b,book);
            break;
        default:
            break;
        }
    }
    break;

    case 4:
    {
        printf("1)View the overdue books\n2)View the most popular books\n\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            system("cls");
            overdue(b);
            break;
        case 2:
            system("cls");
            popularBooks(book);
            m=readBookFile("mostpopular.txt",book);
            for(i=0; i<m; i++)
            {
                printf("Book Title:%s\nAuthor:%s\nPublisher:%s\nISBN:%s\nDate of publication:%s\nNumber of copies:%d\nNumber of available copies:%d\nNumber of borrowed times=%d\n\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].borrow);
                printf("\n");
            }
            printf("Press 1 to return to the main menu.");
            scanf("%d",&choice);
            if(choice==1)
            {
                system("cls");
                main2();
            }
            break;
        default:
            break;

        }


    }
    case 5:
        remove("booksnew.txt");
        remove("brwnew.txt");
        remove("Membersnew.txt");
        printf("Updates have been made and saved.\n\n\t\t\tThank you for visiting our WORLD!\n");
        break;
    case 6:
        printf("Are you sure you want to exit without saving ?(y=1)/(n=0):");
        scanf("%d",&choice);
        if(choice==0)
        {
            system("cls");
            main2();
        }
        else if (choice==1)
        {
            remove("books.txt");
            rename("booksnew.txt","books.txt");
            remove("brw.txt");
            rename("brwnew.txt","brw.txt");
            remove("Members.txt");
            rename("Membersnew.txt","Members.txt");
            printf("\n\t\t\tThank you for visiting our WORLD!\n");
        }
        break;
    default:
        break;
    }
}
void addBook(books *book)
{
    int m;
    m=readBookFile("books.txt",book);
    printf("Enter the required information:\n\n");
    FILE*b;
    b=fopen("books.txt","a");
    if(b!=NULL)
    {
        printf("Book's Title:");
        scanf(" %[^\n]",book[m+1].tit);
        printf("Author:");
        scanf(" %[^\n]",book[m+1].aut);
        printf("Publisher:");
        scanf(" %[^\n]",book[m+1].pub);
        printf("ISBN:");
        scanf(" %[^\n]",book[m+1].isbn);
        for(i=0; i<m+1; i++)
        {
            int r;
            char *s1,*s2;
            s1=strarr(book[m+1].isbn);
            s2=strarr(book[i].isbn);
            r=strcmp(s1,s2);
            if(r==0)
            {
                printf("Enter another ISBN:");
                scanf(" %[^\n]",book[m+1].isbn);
            }
        }
        printf("Date of publication:");
        scanf(" %[^\n]",book[m+1].date);
        printf("Number of copies:");
        scanf("%d",&book[m+1].copy);
        printf("Number of available copies:");
        scanf("%d",&book[m+1].avcopy);
        printf("Category:");
        scanf(" %[^\t\n]",book[m+1].cat);
        book[i].borrow=0;
        fprintf(b,"%s,%s,%s,%s,%s,%d,%d,%s,%d\n",book[m+1].tit,book[m+1].aut,book[m+1].pub,book[m+1].isbn,book[m+1].date,book[m+1].copy,book[m+1].avcopy,book[m+1].cat,book[m+1].borrow);

    }
    fclose(b);
    system("cls");
    printf("Book is added successfully.\n");
    printf("Press 1 to return to the main menu .");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }
}
void searchBooks(books *book,int n)
{
    int m;
    m=readBookFile("books.txt",book);
    char search[50];
    printf("Search by:\n1)Book Title\n2)Author\n3)ISBN\n4)Category\n\n");
    printf("Your choice:");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        system("cls");
        printf("Enter book's title:");
        scanf(" %[^\n]s",search);

        for(i=0; i<m; i++)
        {
            char *s1,*s2;
            s1=strarr(search);

            s2=strarr(book[i].tit);

            if (strcasecmp(s1,s2)==0)
            {
                printf("Author:%s\nPublisher:%s\nISBN:%s\nDate of publication:%s\nNumber of copies:%d\nNumber of available copies:%d\nCategory:%s\nNumber of borrowed times=%d\n\n",book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
            }
        }
        break;

    case 2:
        system("cls");
        printf("Enter the author's name:");
        scanf(" %[^\n]s",search);
        for(i=0; i<m; i++)
        {
            char*s1,*s2;
            s1=strarr(search);
            s2=strarr(book[i].aut);
            if (strcasecmp(s1,s2)==0)
            {
                printf("Book Title:%s\nPublisher:%s\nISBN:%s\nDate of publication:%s\nNumber of copies:%d\nNumber of available copies:%d\nCategory:%s\nNumber of borrowed times=%d\n\n",book[i].tit,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
            }
        }
        break;
    case 3:
        system("cls");
        printf("Enter the book's ISBN:");
        scanf(" %[^\n]s",search);
        for(i=0; i<m; i++)
        {
            char*s1,*s2;
            s1=strarr(search);
            s2=strarr(book[i].isbn);
            if (strcasecmp(s1,s2)==0)
            {
                printf("Book Title:%s\nAuthor:%s\nPublisher:%s\nDate of publication:%s\nNumber of copies:%d\nNumber of available copies:%d\nCategory:%s\nNumber of borrowed times=%d\n\n",book[i].tit,book[i].aut,book[i].pub,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
            }
        }
        break;
    case 4:
        system("cls");
        printf("Enter the book's category:");
        scanf(" %[^\n]s",search);
        for(i=0; i<m; i++)
        {
            char*s1,*s2;
            s1=strarr(search);
            s2=strarr(book[i].cat);
            if (strcasecmp(s1,s2)==0)
            {
                printf("Book Title:%s\nAuthor:%s\nPublisher:%s\nISBN:%s\nDate of publication:%s\nNumber of copies:%d\nNumber of available copies:%d\nNumber of borrowed times=%d\n\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].borrow);
            }
        }
        break;
    default:
        break;
    }
    if(n==1)
    {
        printf("Press 1 to return to the main menu .");
        scanf("%d",&choice);
        if(choice==1)
        {
            system("cls");
            main2();
        }
    }
}
void addCopy(books *book)
{
    char search [50];
    int m,nc;
    m=readBookFile("books.txt",book);
    system("cls");
    printf("Enter the book's ISBN:");
    scanf(" %[^\n]s",search);
    printf("Enter updated number of copies:");
    scanf("%d",&nc);
    for(i=0; i<m; i++)
    {
        {
            char*s1,*s2;
            s1=strarr(search);
            s2=strarr(book[i].isbn);
            if (strcasecmp(s1,s2)==0)
            {
                book[i].avcopy=(nc-book[i].copy)+book[i].avcopy;
                book[i].copy=nc;
                printf("Updated Information:\n");
                printf("Title:%s\nAuthor:%s\nPublisher:%s\nISBN:%s\nDate of publication:%s\nNumber of copies:%d\nNumber of available copies:%d\nCategory:%s\nNumber of borrowed times=%d\n\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
            }
        }
    }

    FILE *ptr2 = fopen("file2.txt","a");

    for(i=0; i<m; i++)
    {

        fprintf(ptr2,"%s,%s,%s,%s,%s,%d,%d,%s,%d\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
        fprintf(ptr2,"\n");
    }

    fclose(ptr2);
    remove("books.txt");
    rename("file2.txt","books.txt");
    printf("Press 1 to return to the main menu.");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }
}
void deleteBook(books*book)
{
    char search[50];
    int m;

    FILE *ptr2 = fopen("file2.txt","a");
    m=readBookFile("books.txt",book);
    printf("Enter book's ISBN:");
    scanf("%s",search);
    for(i=0; i<m; i++)
    {
        if(strcmp(search,book[i].isbn)!=0)

        {
            fprintf(ptr2,"%s,%s,%s,%s,%s,%d,%d,%s,%d\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
            fprintf(ptr2,"\n");
        }
    }
    fclose(ptr2);
    remove("books.txt");
    rename("file2.txt","books.txt");
    printf("Book is deleted.\n");
    printf("Press 1 to return to the main menu.");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }
}
void updateAvcopy(char*s,books *book,int n)
{

    int m;
    m=readBookFile("books.txt",book);
    for(i=0; i<m; i++)
    {
        {
            char*s1,*s2;
            s1=strarr(s);
            s2=strarr(book[i].isbn);
            if (strcasecmp(s1,s2)==0&&n==1)
            {
                book[i].avcopy--;
                book[i].borrow++;
            }
            else if (strcasecmp(s1,s2)==0&&n==2)
                book[i].avcopy++;

        }
    }

    FILE *ptr2 = fopen("file2.txt","a");

    for(i=0; i<m; i++)
    {

        fprintf(ptr2,"%s,%s,%s,%s,%s,%d,%d,%s,%d\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
        fprintf(ptr2,"\n");
    }

    fclose(ptr2);
    remove("books.txt");
    rename("file2.txt","books.txt");

}
void returnBook (brw *b,books*book)
{
    int searchid,k,d,q,h,i;
    char searchis[50];
    printf("Enter the number of returned books\n ");
    scanf("%d",&d);
    for(k=0; k<d; k++)
    {
        printf("For book %d\n",k+1);
        h=readBorrowFile("brw.txt",b);
        printf("Enter your ID\n");
        scanf("%d",&searchid);
        printf("Enter the book's ISBN code\n");
        scanf(" %[^\n]",searchis);
        date d4;

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        d4.day=tm.tm_mday;
        d4.month=tm.tm_mon + 1;
        d4.yr=tm.tm_year + 1900;
        char *s1,*s2;
        int result;
        for(q=0; q<h+1; q++)
        {
            s1=strarr(searchis);
            s2=strarr(b[q].ISBN);
            result=strcasecmp(s1,s2);

            if(searchid==b[q].ID &&result==0)
            {
                b[q].d_r.day=d4.day;
                b[q].d_r.month=d4.month;
                b[q].d_r.yr=d4.yr;
                updateAvcopy(b[q].ISBN,book,2);
            }
        }
    }
    FILE *f = fopen("file2.txt","a");

    for(i=0; i<h; i++)
    {


        fprintf(f,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",b[i].ISBN,b[i].ID,b[i].d_b.day,b[i].d_b.month,b[i].d_b.yr,b[i].d_due.day,b[i].d_due.month,b[i].d_due.yr,b[i].d_r.day,b[i].d_r.month,b[i].d_r.yr);
        fprintf(f,"\n");
    }

    fclose(f);
    remove("brw.txt");
    rename("file2.txt","brw.txt");


    printf("Press 1 to return to the main menu.");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }
}
void borrowBook(brw*b,books*book)
{
    int m1,x1,j,z,L,flag=1;
    FILE *f;
    f=fopen("brw.txt","a");
    printf("Enter the number of borrowing  members:\n");
    scanf("%d",&x1);

    for(j=0; j<x1; j++)
    {
        L=0;
        searchBooks(book,0);
        system("cls");
        z=readBorrowFile("brw.txt",b);
        printf("\nFor member %d:\n",j+1);
        printf("Enter the ISBN code:\n");
        scanf(" %[^\n]",b[z+1].ISBN);
        printf("Enter the ID:\n");
        scanf("%d",&b[z+1].ID);
        for(m1=0; m1<z+1; m1++)
        {
            if (b[z+1].ID==b[m1].ID&&b[m1].d_r.day==0)
                L++;
        }
        if(L>=3)
        {
            printf("Member can't borrow more than 3 books at a time\n ");
            flag=0;

        }
        if(flag==1)
        {

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            b[z+1].d_b.day=tm.tm_mday;
            b[z+1].d_b.month=tm.tm_mon + 1;
            b[z+1].d_b.yr=tm.tm_year + 1900;
            printf("Enter the date due to be returned dd/mm/yy: \n");
            scanf("%d/%d/%d",&b[z+1].d_due.day,&b[z+1].d_due.month,&b[z+1].d_due.yr);
            b[z+1].d_r.day=0;
            b[z+1].d_r.month=0;
            b[z+1].d_r.yr=0;
            fprintf(f,"\n");
            fprintf(f,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",b[z+1].ISBN,b[z+1].ID,b[z+1].d_b.day,b[z+1].d_b.month,b[z+1].d_b.yr,b[z+1].d_due.day,b[z+1].d_due.month,b[z+1].d_due.yr,b[z+1].d_r.day,b[z+1].d_r.month,b[z+1].d_r.yr);
            updateAvcopy(b[z+1].ISBN,book,1);
        }
    }

    printf("Press 1 to return to the main menu.");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }
}
void addMember(member*m)
{
    int h,x;
    h=readMemberFile("Members.txt",m);
    printf("%d",m[0].id);
    FILE *fp;
    fp=fopen("Members.txt","a");

    printf("Enter the number of registering members:\n");
    scanf("%d",&x);
    for(i=0; i<x; i++)
    {
        if (fp!=NULL)
        {
            printf("For user %d\n",i+1);
            printf("Enter your last name:\n");
            scanf("%s",m[h+1].lastn);
            printf("Enter your first name:\n");
            scanf("%s",m[h+1].firstn);
            printf("Enter your ID:\n");
            scanf("%d",&m[h+1].id);
            for(j=0; j<h; j++)
        {printf("%d\n",m[i].id);
            if(m[h+1].id==m[j].id)
            {
                printf("Enter another ID:");
                scanf("%ld",&m[h+1].id);
            }
        }
            printf("Enter your street name:\n");
            scanf("%s",m[h+1].street);
            printf("Enter your city:\n");
            scanf("%s",m[h+1].city);
            printf("Enter your phone number:\n");
            scanf("%ld",&m[h+1].phone);
            printf("Enter your age:\n");
            scanf("%d",&m[h+1].age);
            printf("Enter your Email:\n");
            scanf("%s",m[h+1].email);
            fprintf(fp,"%s,%s,%ld,%s,%s,%ld,%d,%s\n",m[h+1].lastn,m[h+1].firstn,m[h+1].id,m[h+1].street,m[h+1].city,m[h+1].phone,m[h+1].age,m[h+1].email);
            fprintf(fp,"\n");
        }
    }fclose(fp);
    printf("Press 1 to return to the main menu.");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }
}
int readBorrowFile(char *fname,brw *s)
{
    FILE *fp;
    int i=0;

    fp=fopen(fname,"r");
    if (fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp,"%[^,],%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",s[i].ISBN,&s[i].ID,&s[i].d_b.day,&s[i].d_b.month,&s[i].d_b.yr,&s[i].d_due.day,&s[i].d_due.month,&s[i].d_due.yr,&s[i].d_r.day,&s[i].d_r.month,&s[i].d_r.yr);
            fscanf(fp,"\n");
            i++;
        }
    }
    fclose(fp);
    return i;
}
int readMemberFile(char *fname,member *m)
{
    FILE *fp;
    int i=0;

    fp=fopen(fname,"r");
    if (fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp,"%s,%s,%d,%s,%s,%d,%d,%s",m[i].lastn,m[i].firstn,&m[i].id,m[i].street,m[i].city,&m[i].phone,&m[i].age,m[i].email);
            fscanf(fp,"\n");
            i++;
        }
    }
    fclose(fp);
    return i;
}
void popularBooks(books*book)
{

    int max,k=0;


    copyFile("books.txt","new.txt");

    FILE*mp;
    mp=fopen("mostpopular.txt","w");
    for(j=0; j<5; j++)
    {
        m=readBookFile("new.txt",book);

        max=book[0].borrow;

        for(i=0; i<m; i++)
        {
            if(book[i].borrow>max)
            {
                max=book[i].borrow;
                k=i;
            }
        }

        deleteMax(book,book[k].borrow);
        fprintf(mp,"%s,%s,%s,%s,%s,%d,%d,%s,%d\n",book[k].tit,book[k].aut,book[k].pub,book[k].isbn,book[k].date,book[k].copy,book[k].avcopy,book[k].cat,book[k].borrow);
        fprintf(mp,"\n");

    }
    fclose(mp);
}
void deleteMax(books*book, int c)
{

    int m,i;

    FILE *ptr2 = fopen("file2.txt","w");
    m=readBookFile("new.txt",book);

    for(i=0; i<m; i++)
    {
        if(book[i].borrow!=c)

        {
            fprintf(ptr2,"%s,%s,%s,%s,%s,%d,%d,%s,%d\n",book[i].tit,book[i].aut,book[i].pub,book[i].isbn,book[i].date,book[i].copy,book[i].avcopy,book[i].cat,book[i].borrow);
            fprintf(ptr2,"\n");
        }
    }
    fclose(ptr2);
    remove("new.txt");
    rename("file2.txt","new.txt");


}
int readBookFile(char* filename,books*book)
{
    FILE*p;
    int c=0;
    p=fopen(filename,"r");
    if(p!=NULL)
    {
        while(!feof(p))
        {
            fscanf(p,"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%d",book[c].tit,book[c].aut,book[c].pub,book[c].isbn,book[c].date,&book[c].copy,&book[c].avcopy,book[c].cat,&book[c].borrow);
            fscanf(p,"\n");
            c++;
        }
    }
    fclose(p);
    return c;
}
void overdue(brw*b)
{
    date d4;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    d4.day=tm.tm_mday;
    d4.month=tm.tm_mon + 1;
    d4.yr=tm.tm_year + 1900;
    printf("Today: %d/%d/%d \n", d4.day, d4.month, d4.yr);
    m=readBorrowFile("brw.txt",b);
    for(i=0; i<m; i++)
    {
        if(b[i].d_r.day==0)
        {
            int cmp = date_cmp(b[i].d_due,d4);


            if(cmp<0)

                printf("%s is an overdue book that has to be returned by the user %d.\n",b[i].ISBN,b[i].ID);

        }
    }
    printf("Do you want to return to the main menu ?(y=1)/(n=0):");
    scanf("%d",&choice);
    if(choice==1)
    {
        system("cls");
        main2();
    }

}
int date_cmp(date d1,date d2)
{

    if (d1.day == d2.day && d1.month == d2.month && d1.yr ==d2.yr)

        return 0;

    else if (d1.yr > d2.yr || d1.yr == d2.yr && d1.month > d2.month || d1.yr == d2.yr && d1.month == d2.month && d1.day > d2.day)

        return 1;

    else return -1;

}
void copyFile(char*s,char*d)
{
    char str[1000];
    FILE*p;
    int c=0;
    p=fopen(s,"r");
    FILE*t;
    t=fopen(d,"w");
    if (p!=NULL)
    {

        while(fgets(str,sizeof(str),p)!=NULL)
        {

            fprintf(t,"%s",str);
        }
    }


    fclose(p);
    fclose(t);

    return 0;
}
char *strarr(char*s)
{
    char *s1;
    s1=(char*)malloc(strlen(s));
    for(n=0, j=0; n<strlen(s); n++, j++)
    {


        if(s[n]!=' ')
            s1[j]=s[n];
        else j--;

    }
    s1[j]=0;
    return s1;
}
