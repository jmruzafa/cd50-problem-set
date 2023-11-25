#include <cs50.h>
#include <stdio.h>

int main(void) {
    // Prompt for starting population size
    int startSize;
    do {
        startSize = get_int("Enter starting population size (must be >= 9): ");
    } while (startSize < 9);

    // Prompt for ending population size
    int endSize;
    do {
        end_size = get_int("Enter ending population size (must be >= starting size): ");
    } while (endSize < startSize);

    // Calculate the number of years required
    int years = 0;
    int currentSize = endSize;
    while (currentSize < endSize) {
        currentSize = current_size + (currentSize / 3) - (currentSize / 4);
        years++;
    }

    // Print the result
    printf("Years: %d\n", years);

    return 0;
}
