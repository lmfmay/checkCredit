#include <cs50.h>
#include <stdio.h>

void checksum(long long number);
void checkCardType(long long number, int digcount);

int main(void)
{
    // prompt user for card number
    long long cccard;
    do
    {
        cccard = get_long_long("Number: ");
    }
    while (cccard < 1);

    // validate different numbers
    checksum(cccard);
}
// check Luhn
void checksum(long long number)
{
    int sum = 0;
    int digcount = 0;
    int digit;
    long long workingnum = number;
    // Get sum of odd digits
    while (workingnum != 0)
    {
        digit = workingnum % 10;
        sum += digit;
        digcount++;
        workingnum /= 100;
    }
    // Get sum of even digits
    workingnum = number;
    workingnum /= 10;
    while (workingnum != 0)
    {
        digit = workingnum % 10;
        digit *= 2;
        digit = (digit % 10) + (digit / 10);
        sum += digit;
        digcount++;
        workingnum /= 100;
    }

    // Validity check for sum of cc numbers
    workingnum = number;
    if (sum % 10 == 0 && (digcount == 13 || digcount == 15 || digcount == 16))
    {
        checkCardType(workingnum, digcount);
    }
    else
    {
        printf("INVALID\n");
    }
}

void checkCardType(long long number, int digcount)
{
    long long workingnum = number;
    // Get first 2 digs of ccnumber
    for (int i = 0; i < digcount - 2; i++)
    {
        workingnum /= 10;
    }
    // check Amex for 15 digits + starting with 34 or 37
    if (digcount == 15 && (workingnum == 37 || workingnum == 34))
    {
        printf("AMEX\n");
        return;
    }
    // check MasterCard for 16 digits + starting with 51, 52, 53, 54, or 55
    else if (digcount == 16 && (workingnum >= 51 && workingnum <= 55 && workingnum / 10 != 4))
    {
        printf("MASTERCARD\n");
        return;
    }
    // Get first digit of cc number
    workingnum /= 10;
    // check VISA for 13 or 16 digits + starting with 4
    if ((digcount == 13 || digcount == 16) && workingnum == 4)
    {
        printf("VISA\n");
        return;
    }
    // action if all tests fail
    else
    {
        printf("INVALID\n");
    }
}
