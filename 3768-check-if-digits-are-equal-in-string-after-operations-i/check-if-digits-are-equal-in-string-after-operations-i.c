bool hasSameDigits(char* s) {
   int n=strlen(s);
   int digits[100];

   for(int i=0;i<n;i++){
        digits[i] = s[i]- '0';
   }

    // Repeat until only two digits remain
    while (n > 2) {
        for (int i = 0; i < n - 1; i++) {
            digits[i] = (digits[i] + digits[i + 1]) % 10;
        }
        n--; // One fewer digit each round
    }

    // Check if last two digits are equal
    return digits[0] == digits[1];



    
}