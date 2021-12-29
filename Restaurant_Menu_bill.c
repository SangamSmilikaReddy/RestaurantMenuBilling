#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillheader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t   ADV. Restaurant");
    printf("\n\t  -----------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To:%s",name);
    printf("\n---------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30],int qty,float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%0.2f\t\t",qty*price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis,netTotal,cgst,grandTotal;
    dis=0.1*total;
    netTotal=total-dis;
    cgst=0.09*netTotal;
    grandTotal=netTotal+2*cgst;
    printf("---------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2","%",cgst);
    printf("\n---------------------------------------------");
    printf("\nGrand Total\t\t\t %.2f",grandTotal);
    printf("\n---------------------------------------------\n");

}
void displayMenu(){
    FILE *fmenu;
    char ch;
    fmenu=fopen("Menu trial.txt","r");
    while(!feof(fmenu)){
        ch=fgetc(fmenu);
        printf("%c",ch);
    }
    fclose(fmenu);
}


int main(){
    struct orders ord;
    struct orders order;
    int opt,choi,n,i;
    char saveBill='y',continueflag1='y',continueflag2='y';
    char name[50];
    FILE *fbill;
    while(continueflag1=='y'){
        printf("************ ");
        printf("Welcome to SNR Restaurent");
        printf("************ \n\n");
        printf("\n1.Customer");
        printf("\n2.Restaurent Serviece");
        printf("\n3.Exit");
        printf("\n\nPlease select--");
        scanf("%d",&opt);
        printf("\n\n");
        switch(opt){
            case 1:
                //system("clear");
                displayMenu();
                break;
            case 2:
                while(continueflag2=='y'){
                    float total=0;
                    int invoiceFound=0;
                    //system("clear");
                    printf("\t===========ADV. Restaurant===========");
                    printf("\n\nPlease select your prefered operation");
                    printf("\n\n1.Generate Invoice");
                    printf("\n2.Show all Invoice");
                    printf("\n3.Search Invoice");
                    printf("\n4.Exit");
                    printf("\nEnter your choice:");
                    scanf("%d",&choi);
                    fgetc(stdin);
                    switch(choi){
                        case 1:
                            //system("clear");
                            printf("\nEnter the name of the customer:\t");
                            fgets(ord.customer,50,stdin);
                            ord.customer[strlen(ord.customer)-1]=0;
                            strcpy(ord.date,__DATE__);
                            printf("\nPlease enter the number of items:\t");
                            scanf("%d",&n);
                            ord.numOfItems=n;
                            for(i=0;i<n;i++){
                                fgetc(stdin);
                                printf("\n\n");
                                printf("Please enter the item %d:\t",i+1);
                                fgets(ord.itm[i].item,20,stdin);
                                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                                printf("Please enter the quantity:\t");
                                scanf("%d",&ord.itm[i].qty);
                                printf("Please enter the unit price:\t");
                                scanf("%f",&ord.itm[i].price);
                                total += ord.itm[i].qty*ord.itm[i].price;
                            }
                            generateBillheader(ord.customer,ord.date);
                            for(i=0;i<ord.numOfItems;i++){
                                generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                            }
                            generateBillFooter(total);
                            printf("\nDo you want to save the invoice[y/n]:\t");
                            scanf("%s",&saveBill);

                            if (saveBill=='y'){
                                fbill=fopen("BillStatement.dat","ab");
                                fwrite(&ord,sizeof(struct orders),1,fbill);
                                if(fwrite != 0){
                                    printf("\nSuccessfully saved !!!");
                                }
                                else{
                                    printf("\nError saving !!*!!");
                                }
                            }
                            break;
                        case 2:
                            //system("clear");
                            fbill = fopen("BillStatement.dat","rb");
                            printf("\n  *****Your Previous Invoices*****\n");
                            while(fread(&order,sizeof(struct orders),1,fbill)==1){
                                float tot=0;
                                generateBillheader(order.customer,order.date);
                                for(i=0;i<order.numOfItems;i++){
                                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                                    tot+=order.itm[i].qty * order.itm[i].price;
                                }
                                generateBillFooter(tot);
                            }
                            fclose(fbill);
                            break;
                        case 3:
                            printf("\nEnter the name of the customer:\t");
                            // fgetc(stdin);
                            fgets(name,50,stdin);
                            name[strlen(name)-1]=0;
                            //system("clear");
                            fbill = fopen("BillStatement.dat","rb");
                            printf("\n\t****** Invoice Of the %s *****",name);
                            while(fread(&order,sizeof(struct orders),1,fbill)==1){
                                float tot=0;
                                if(!strcmp(order.customer,name)){
                                    generateBillheader(order.customer,order.date);
                                    for(i=0;i<order.numOfItems;i++){
                                        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                                        tot+=order.itm[i].qty * order.itm[i].price;
                                    }
                                    generateBillFooter(tot);
                                    invoiceFound=1;
                                }
                            }
                            if(!invoiceFound){
                                printf("\nSorry the invoice for the %s does not exists",name);
                            }
                            fclose(fbill);
                            break;

                        case 4:
                            printf("\n\t\tExiting.....\n\n");
                            exit(0);
                            break;

                        default:
                            printf("Sorry invalid option");
                            break;
                    }
                    printf("\n\nDo you want to continue the operation?[y/n]?");
                    scanf("%s",&continueflag2);
                }
                break;

        }
        printf("\n\nDo you want to continue the operation?[y/n]?");
        scanf("%s",&continueflag1);
    }


    return 0;
}
