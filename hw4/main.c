#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define CORBA 10.00
#define KEBAP 75.99
#define LAHMACUN 21.50
#define PIDE 40.00
#define DONER 55.60
#define KOLA 15.00
#define SU 5.00
#define KUNEFE 60.00
#define SUTLAC 32.50
#define BAKLAVA 61.00

void print_receipt(){
    //Terminal output part for receipt
    FILE *fp;
    char c;
    //Reads and prints 
    fp = fopen("receipt.txt", "r");
    while ((c = fgetc(fp)) != EOF){
        printf("%c", c);
    }

    fclose(fp);
}
void wtotal(int choice,int portion,float total){
//second part of the receipt
FILE *fp;
fp=fopen("receipt.txt","a");
switch (choice)
{
case 1:
        fprintf(fp, " %d* Çorba                  %.2f\n\n", portion, total);
        break;
case 2:
        fprintf(fp, " %d* Kebap                  %.2f\n\n", portion, total);
        break;
case 3:
        fprintf(fp, " %d* Lahmacun               %.2f\n\n", portion, total);
        break;
case 4:
        fprintf(fp, " %d* Pide                   %.2f\n\n", portion, total);
        break;
case 5:
        fprintf(fp, " %d* Döner                  %.2f\n\n", portion, total);
        break;
case 6: 
        fprintf(fp, " %d* Kola                   %.2f\n\n", portion, total);
        break;
case 7:
        fprintf(fp, " %d* Su                     %.2f\n\n", portion, total);
        break;
case 8:
        fprintf(fp, " %d* Künefe                 %.2f\n\n", portion, total);
        break;
case 9:
        fprintf(fp, " %d* Sütlaç                 %.2f\n\n", portion, total);
        break;
case 10:
        fprintf(fp, " %d* Baklava                %.2f\n\n", portion, total);
        break;
}

fclose(fp);
}
void receipt(){
    //First part of receipt
    //strftime part must contain array
    time_t raw_time;
    struct tm *time_info;
    char formatted_time[20];
    FILE *freceipt;
    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(formatted_time, sizeof(formatted_time), "%d.%m.%Y/%H:%M", time_info);

    freceipt = fopen("receipt.txt", "w");
    fprintf(freceipt,"220104004922        ");
    fprintf(freceipt,"%s\n", formatted_time);
    fprintf(freceipt,"------------------------------------\n");
    fprintf(freceipt," Product                  Price(TL) \n");
    fprintf(freceipt, "------------------------------------\n");
    fclose(freceipt);
}
float calc(int choice,int portion){
    //I used the define instead of reading from the file because as far as i know from the whatsapp group it is allowed.
    float total;
            switch (choice)
            {
            case 1:
                total=CORBA *portion;
                break;
            case 2:
                total = KEBAP * portion;
                break;
            case 3:
                total = LAHMACUN * portion;
                break;
            case 4:
                total = PIDE * portion;
                break;
            case 5:
                total = DONER * portion;
                break;
            case 6:
                total = KOLA * portion;
                break;
            case 7:
                total = SU * portion;
                break;
            case 8:
                total = KUNEFE * portion;
                break;
            case 9:
                total = SUTLAC * portion;
                break;
            case 10:
                total = BAKLAVA * portion;
                break;                  
            }
    return total;
}
float menu_select(float total2){
    // Last part of receipt
    // Only student discount is allowed if customer is student only otherwise check discount for 150tl limit
    FILE *fp;
    fp=fopen("receipt.txt","a");
    char student;
    float sdiscount=0,discount=0;
    printf("Are you student? (Y/N): ");
    scanf(" %c",&student);
    switch (student)
    {
    case 'Y':
    case 'y':
        fprintf(fp," Total:                    %.2f\n\n",total2);
        sdiscount=-1*(total2*12.5)/100;
        total2=total2+sdiscount;
        fprintf(fp," Student Discount:        %.2f\n\n", sdiscount);
        fprintf(fp,"------------------------------------\n");
        fprintf(fp," Price:                    %.2f\n\n",total2);
        total2=total2*1.18;
        fprintf(fp," Price + VAT:              %.2f\n\n", total2);
        break;
    case 'N':
    case 'n':
        fprintf(fp, " Total:                    %.2f\n\n", total2);
        if (total2>=150){
            discount=-0.1*total2;
            fprintf(fp, " Discount:                 %.2f\n\n", discount);
        }
        fprintf(fp, "------------------------------------\n");
        total2 = total2 +discount;
        fprintf(fp, " Price:                    %.2f\n\n", total2);
        total2 = total2 * 1.18;
        fprintf(fp, " Price + VAT:              %.2f\n\n", total2);
        break;
    default:
        printf("Invalid answer ,Try again\n");
        return menu_select(total2);
        break;
    }
    fclose(fp);
}
void wmenu(){
FILE *fp;
fp=fopen("menu.txt","w");
fprintf(fp, "Product        Price(TL)\n\n");
fprintf(fp, "Çorba          10.00\n\n");
fprintf(fp, "Kebap          75.99\n\n");
fprintf(fp, "Lahmacun       21.50\n\n");
fprintf(fp, "Pide           40.00\n\n");
fprintf(fp, "Döner          55.60\n\n");
fprintf(fp, "Kola           15.00\n\n");
fprintf(fp, "Su             5.00\n\n");
fprintf(fp, "Künefe         60.00\n\n");
fprintf(fp, "Sütlaç         32.50\n\n");
fprintf(fp, "Baklava        61.00\n\n");

fclose(fp);}
void part1(){
wmenu();//crates menu.txt
receipt();
int choice, portion;
float total = 0, total2 = 0;
// total is temporary total
// total 2 is latest version of sum operations
printf("Yemek Listesi:\n\n");
printf("1.Çorba\n\n");
printf("2.Kebap\n\n");
printf("3.Lahmacun\n\n");
printf("4.Pide\n\n");
printf("5.Döner\n\n");
printf("6.Kola\n\n");
printf("7.Su\n\n");
printf("8.Künefe\n\n");
printf("9.Sütlaç\n\n");
printf("10.Baklava\n\n");
do
{
        printf("Please choose a product (1-10): ");
        scanf("%d", &choice);
        if (choice != 0 && choice < 11)
        {
            printf("How many servings do you want? ");
            scanf("%d", &portion);
            switch (portion)
            {
            case 0:
                //stops if portion is zero
                break;
            default:
                total += calc(choice, portion);
                total2 += total;//temporary total is added to the final total 
                wtotal(choice, portion, total);
                total = 0;//seeds to new choice
                break;
            }
        }
        else
            break;
} while (choice > 0 && choice < 11 && portion != 0);
menu_select(total2);
printf("------------------------------------\n");
print_receipt();
}
void part2(){
srand(time(NULL));
char play = 'Y';
while (play == 'Y' || play == 'y')
{
        printf("Please make a choice!\n");
        printf("1: Stone, 2: Paper, 3: Scissors\n");

        int user_choice;
        scanf("%d", &user_choice);

        int computer_choice = rand() % 3 + 1;

        printf("You chose ");
        switch (user_choice)
        {
        case 1:
            printf("Stone");
            break;
        case 2:
            printf("Paper");
            break;
        case 3:
            printf("Scissors");
            break;
        default:
            printf("Invalid choice");
            break;
        }
        printf(". ");

        printf("I chose ");
        switch (computer_choice)
        {
        case 1:
            printf("Stone");
            break;
        case 2:
            printf("Paper");
            break;
        case 3:
            printf("Scissors");
            break;
        }
        printf(". ");

        if (user_choice == computer_choice){
            printf("It's a tie!\n");
        }
        else if ((user_choice == 1 && computer_choice == 3) || (user_choice == 2 && computer_choice == 1) || (user_choice == 3 && computer_choice == 2))
        {
            printf("You won!\n");
        }
        else{
            printf("I won!\n");
        }
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &play);
}
}
int main(){
part1();
part2();
return 0;
}