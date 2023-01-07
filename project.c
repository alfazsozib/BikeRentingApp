#include <stdio.h>
#include <string.h>



int frontPage()
{
    int choice;

    printf("\t\t\t\t\t--------------Rent A Bike----------------\n\n\n");
    printf("Please Enter Your Choice. Choose 1 if you want to list your bike for rent and Choose 2 if you want to Rent a bike or you can choose 3 if you want to exit\n\n\n");
    printf("\t\t 1. Owner\n");
    printf("\t\t 2. Customer\n");
    printf("\t\t 3. Exit\n");
    scanf("%d",&choice);
    return choice;

}

struct OwnerData{

    char ownerName[100];
    char modelName[100];
    char address[100];
    int pricePerHr;
}data;

struct CustomerData{
    char nameOfCustomer[100];
    char pickupDate[100];
    float ridingHr;

}customer;


int setOwner()
{

    FILE* fp = fopen("./owner.txt", "a+");
    fflush(stdin);
    printf("Enter Your Name: ");
    gets(data.ownerName);
    printf("Enter Bike Model: ");
    fflush(stdin);
    gets(data.modelName);
    printf("Enter Price Per Hour (tk): ");
    scanf("%d",&data.pricePerHr);
    printf("Enter City: ");
    fflush(stdin);
    gets(data.address);
    fprintf(fp, "%s\t\t\t\t%s\t\t\t%d\t\t\t%s\n", data.ownerName,
        data.modelName, data.pricePerHr, data.address);


    printf("\nBike added to Record");

    fclose(fp);
    return 0;
}


void setCustomer()
{

    FILE* fp = fopen("./customer.txt", "a+");

    printf("Enter Your Name: ");
    fflush(stdin);
    gets(customer.nameOfCustomer);
    printf("Enter Pickup Date(DD/MM/YYYY): ");
    fflush(stdin);
    gets(customer.pickupDate);
    printf("Enter Renting Hour: ");
    scanf("%f",&customer.ridingHr);
    fprintf(fp, "%s,%s,%.2f\n", customer.nameOfCustomer,customer.pickupDate,
        customer.ridingHr);
}

int view()
{
    FILE *fp;
    char d_show[500000];
    fp = fopen("owner.txt", "r");
    printf("\nOwner\t\t\tBike\t\t\tPrice\t\t\tAddress\n");

    while( fgets(d_show,1024,fp) )
    {
        printf("%s", d_show);

    }
    printf(" \n\n");
    fclose(fp);
    return 0;
}


int search()
{

    FILE *fp,*tp,*st;
    char value=0;
    char line[200],search_string[2000];

    printf("\n\n Enter Model Name To Rent : ");
    scanf("%s",&search_string);
    fp=fopen("owner.txt","r");
    while(fgets( line, 1020, fp ) != NULL )
        {
            if(strstr(line,search_string))
            {
                tp = fopen("Memo.txt","w+");
                fputs(line,tp);
                st = fopen("Riders Record.txt","a+");
                fputs(line,st);
                //fputs(line,stdout);
                printf("\t\t\t\t\tCongratulation! %s \n\n\n",customer.nameOfCustomer);
                continue;
            }
        }
   fclose(fp);
   fclose(tp);
   bikeMemo();

}


int bikeMemo()
{
    FILE *mp;
    mp = fopen("Memo.txt","r+");

    char memo[200];
    fgets(memo,200,mp);
    char *lines = strtok(memo,"\t\t\t");
    char *line2 = strtok(NULL,"\t\t\t");
    char *price = strtok(NULL,"\t\t\t");
    int pricePerHr = atoi(price);
    float totalCost = pricePerHr*customer.ridingHr;

    printf("\t\t\t\t  ---------- Rent a Bike -------------- \t\t\t\t\t");
    printf("\n\n");
    printf("\t\t\t\t\t Name         : %s ",customer.nameOfCustomer);
    printf("\n\n");
    printf("\t\t\t\t\t Bike Model   : %s ",line2);
    printf("\n\n");
    printf("\t\t\t\t\t Cost Per Hour: %d ",pricePerHr);
    printf("\n\n");
    printf("\t\t\t\t\t Pickup Date  : %s ",customer.pickupDate);
    printf("\n\n");
    printf("\t\t\t\t\t Renting Hour : %.2f ",customer.ridingHr);
    printf("\n\n");
    printf("\t\t\t\t --------------------------------------- \n");
    printf("\t\t\t\t\t Total Cost   : %.2f \t\t\t\t\t",totalCost);
}


int main()
{

    int choice = frontPage();

    if (choice == 1)
    {
        char inp;
        setOwner();
        printf("\nIf you want to add more bikes press y otherwise press n: \n");
        scanf("%s",&inp);
        while(inp == 'y')
        {
            setOwner();
            printf("\nIf you want to add more bikes press y otherwise press n: \n");
            scanf("%s",&inp);
        }
    }
    else if(choice == 2){

        setCustomer();
        printf("\n\n\nHi %s Available Bikes Are -->> \n\n",customer.nameOfCustomer);
        view();
        printf("If you want to rent bike press 1 otherwise press 0 to exit : ");
        int a;
        scanf("%d",&a);
        if (a==1)
        {
            search();
            //bikeMemo();
        }
        else{
            printf("\n\n\n\t\t\t\t\tThanks for visiting my App. ");
        };

    }

    else if(choice == 3)
    {
        printf("Thanks for visiting my App. See you soon! ");
    }


return 0;
}
