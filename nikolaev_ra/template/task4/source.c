#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#define MIN_DISCOUNT_VALUE 5
#define MAX_DISCOUNT_VALUE 50
#define STEP_FOR_DISCOUNT 5
#define DECIMAL_SHARE 0.01

// To further increase the number of products, we can simply change the value of this macro and add information about the product to the data structures
#define PRODUCTS_COUNT 7

#define PRODUCT_CODE_LENGTH 4
#define MAX_PRODUCT_NAME_LENGTH 50
#define MAX_PRODUCT_DESCRIPTION_LENGTH 100

// Structure for product description
struct sProduct
{
    char code[PRODUCT_CODE_LENGTH];
    unsigned int price;
    char name[MAX_PRODUCT_NAME_LENGTH];
    char description[MAX_PRODUCT_DESCRIPTION_LENGTH];
    unsigned int discount_value;
};

// Structure for generating a check
struct sCheck
{
    char name[MAX_PRODUCT_NAME_LENGTH];
    unsigned int unit_price;
    unsigned int count_of_products;
    unsigned int total_cost;
};

typedef struct sProduct Product;
typedef struct sCheck Check;

// Let's create an array for all products
Product products_array[PRODUCTS_COUNT] = {
    {"0023", 45, "Bread", "Rye bread, 500g, production date: 13.10.2022, expiration date: 3 days", 0},
    {"1346", 90, "Chocolate", "Bitter chocolate, 100g, production date: 10.09.2022, expiration date: 6 months", 0},
    {"3922", 180, "Juice", "Apple juice, 2l, production date: 05.06.2022, expiration date: 12 months", 0},
    {"4467", 85, "Milk", "Milk 3.4%, 930g, production date: 27.10.2022, expiration date: 7 days", 0},
    {"6832", 50, "Tea", "Black tea, 25 bags, production date: 01.07.2022, expiration date: 18 months", 0},
    {"8183", 45, "Water", "Mineral sparkling water, 1.5l, production date: 22.10.2022, expiration date: 12 months", 0},
    {"9915", 67, "Yogurt", "Greek yogurt 9%, 120g, production date: 27.10.2022, expiration date: 7 days", 0}
};

// Function to generate a discount value in a given range with a given step
int discount_generation(int min_discount_value , int max_discount_value, int step_for_discount)
{
    int discount_value = ( rand() % (max_discount_value / step_for_discount) + (min_discount_value / step_for_discount) ) * step_for_discount;
    return discount_value;
}

// Function to clear the input stream
void clean_stdin()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

// Function to generate the check
void final_check(Product arr1[], Check arr2[])
{
    // Firstly, let's calculate the total amount without discount
    unsigned int total_amount_without_discount = 0;
    for (int i = 0; i < PRODUCTS_COUNT; i++)
        total_amount_without_discount += arr1[i].price * arr2[i].count_of_products;

    // Now let's calculate the total discount amount (in parallel, we will print information about scanned products)
    unsigned int total_amount_with_discount = 0;
    for (int i = 0; i < PRODUCTS_COUNT; i++)
    {
        if (arr2[i].count_of_products > 0)
        {
            total_amount_with_discount += arr2[i].total_cost;
            printf("\"%s\" -> unit price: %d rubles -> discount: %d% -> unit price with discount: %d rubles -> count of these products: %d -> amount of all these products: %d rubles \n", arr2[i].name, arr1[i].price, arr1[i].discount_value, arr2[i].unit_price, arr2[i].count_of_products, arr2[i].total_cost);
        }
    }
    unsigned int total_discount = total_amount_without_discount - total_amount_with_discount;
    printf("\nThe total amount without discount: %d rubles\n", total_amount_without_discount);
    printf("The total amount of discount: %d rubles\n", total_discount);
    printf("The total amount for payment: %d rubles\n", total_amount_with_discount);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

}

int main()
{
    srand(time(NULL));

    // Generating discount values
    for (int i = 0; i < PRODUCTS_COUNT; i++)
        products_array[i].discount_value = discount_generation(MIN_DISCOUNT_VALUE, MAX_DISCOUNT_VALUE, STEP_FOR_DISCOUNT);

    printf("Hello!\nWelcome to the program \"Electronic Cash Register\"!\n\n");
    char cont_work;
    do
    {
        // Generating a template for check generation
        // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Check products_check[PRODUCTS_COUNT] = {
            {"Bread", 45, 0, 0},
            {"Chocolate", 90, 0, 0},
            {"Juice", 180, 0, 0},
            {"Milk", 85, 0, 0},
            {"Tea", 50, 0, 0},
            {"Water", 45, 0, 0},
            {"Yogurt", 67, 0, 0}
        };

        // Let's change the price value in the products_check array to a discounted value (Here and below we will assume that the products are arranged in arrays in alphabetical order)
        // The task says to work with rubles without kopecks, so I use rounding
        for (int i = 0; i < PRODUCTS_COUNT; i++)
            products_check[i].unit_price = products_array[i].price - round(products_array[i].price * products_array[i].discount_value * DECIMAL_SHARE);
        // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        printf("Product codes:\n\"Bread\" -> \"0023\"\n\"Chocolate\" -> \"1346\"\n\"Juice\" -> \"3922\"\n\"Milk\" -> \"4467\"\n\"Tea\" -> \"6832\"\n\"Water\" -> \"8183\"\n\"Yogurt\" -> \"9915\"\n\n");
        do
        {
            char entered_code[PRODUCT_CODE_LENGTH];
            printf("Enter the product code (to exit scan mode, enter \"quit\"): ");
            scanf("%c%c%c%c", &entered_code[0], &entered_code[1], &entered_code[2], &entered_code[3]);
            clean_stdin();

            if (entered_code[0] == 'q' && entered_code[1] == 'u' && entered_code[2] == 'i' && entered_code[3] == 't')
                break;
            else
            {
                // In this block, we compare the value of the entered code with the product codes
                unsigned int checkbox = 0;
                for (int i = 0; i < PRODUCTS_COUNT; i++)
                    if (products_array[i].code[0] == entered_code[0] && products_array[i].code[1] == entered_code[1] && products_array[i].code[2] == entered_code[2] && products_array[i].code[3] == entered_code[3])
                    {
                        printf("\nScanned product called \"%s\"\nProduct description: \"%s\"\n\n", products_array[i].name, products_array[i].description);
                        products_check[i].count_of_products++;
                        products_check[i].total_cost += products_check[i].unit_price;
                        checkbox = 1;
                    }
                if (checkbox == 0)
                    printf("Product with this code was not found. Check the entered data and try again\n\n");
            }

        } while (1);

        // Let's check if there is at least one scanned product
        unsigned int cond = 0;
        for (int i = 0; i < PRODUCTS_COUNT; i++)
        {
            if (products_check[i].count_of_products > 0)
                cond = 1;
        }
        if (cond == 0)
        {
            char act;
            printf("\nThe check is empty. To exit the program, enter 'q', and to return to scan mode, enter any other character: ");
            scanf("%c", &act);
            clean_stdin();

            if (act == 'e')
                break;
            else
                continue;
        }
        else
        {
            printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("Final check:\n\n");
            final_check(products_array, products_check);
        }

        printf("\nTo exit the program, enter 'q', and to continue using the electronic cash register, enter any other character: ");
        scanf("%c", &cont_work);
        clean_stdin();
        printf("\n");
    } while (cont_work != 'q');
    printf("Thank you for using this program. Come even later :)\n");
    return 0;
}
