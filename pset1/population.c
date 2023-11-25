#include <cs50.h>
#include <stdio.h>

int main(void) {
    // Prompt for starting population size
    int start_size;
    do {
        start_size = get_int("Enter starting population size (must be >= 9): ");
    } while (start_size < 9);

    // Prompt for ending population size
    int end_size;
    do {
        end_size = get_int("Enter ending population size (must be >= starting size): ");
    } while (end_size < start_size);

    // Calculate the number of years required
    int years = 0;
    int current_size = start_size;
    while (current_size < end_size) {
        current_size = current_size + (current_size / 3) - (current_size / 4);
        years++;
    }

    // Print the result
    printf("Years: %d\n", years);

    return 0;
}
