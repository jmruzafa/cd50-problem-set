#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for starting population size
    int startSize;
    do
    {
        startSize = get_int("Enter starting population size (must be >= 9): ");
    } while (startSize < 9);

    // Prompt for ending population size
    int endSize;
    do
    {
        endSize = get_int("Enter ending population size (must be >= starting size): ");
    } while (endSize < startSize);

    // Calculate the number of years required
    int years = 0;
    int currentSize = startSize;
    while (currentSize < endSize)
    {
        int newLlamas = currentSize / 3;
        int passedAway = currentSize / 4;

        // Ensure there's no fractional llamas
        if (newLlamas - passedAway < 1)
        {
            newLlamas = 1;
        }

        currentSize = currentSize + newLlamas - passedAway;
        years++;
    }

    // Print the result
    printf("Years: %d\n", years);

    return 0;
}
