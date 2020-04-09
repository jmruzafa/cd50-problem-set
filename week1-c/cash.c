#include <stdio.h>
#include <cs50.h>
#include <math.h>

int findCoins(int cents, int coin_array[], int position);

int main(void)
{
    bool error = true;
    float dollars = 0.00;
    int coin_array[4] = {25, 10, 5, 1};
    int array_size = (int)(sizeof coin_array / sizeof coin_array[0]);
    do
    {
        //ask for the changed owed
        dollars = get_float("Change owed: ");
        if (dollars >= 0)
        {
            error = false;
        }
    }
    while (error);

    //round input to cents
    int cents = round(dollars * 100);
    int coins = 0;
    //recursive function call to get coins ammount
    coins = findCoins(cents, coin_array, 0);
    printf("%i\n", coins);
}
int findCoins(int cents, int coin_array[], int position)
{
    //get number of coins of selected one
    int coins = cents / coin_array[position];
    int remain = cents % coin_array[position];
    //if there's a remainder we need to go to the next one
    if (remain != 0)
    {
        coins += findCoins(remain, coin_array, position + 1);
    }
    return coins;
}
