/* bankAccount.h simulates a simple bank account
 *
 * Joel Adams, Calvin College, Fall 2013.
 */


// Shared Variables
double bankAccountBalance = 0;

// add amount to bankAccountBalance
void deposit(double amount) {
   bankAccountBalance += amount;
}

// subtract amount from bankAccountBalance
void withdraw(double amount) {
   bankAccountBalance -= amount;
}

void cleanup() {
}

