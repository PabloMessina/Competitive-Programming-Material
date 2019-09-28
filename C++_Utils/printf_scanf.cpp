/* =================================== */
/* Input/Output with C: printf & scanf */
/* =================================== */
scanf("%d",&a); //int
scanf("%x",&a); // int in hexadecimal
scanf("%llx",&a); // long long in hexadecimal
scanf("%lld",&a); // long long int
scanf("%c",&c); // char
scanf("%s",buffer); // string without whitespaces
scanf("%f",&f); // float
scanf("%lf",&d); // double
scanf("%d %*s %d",&a,&b);  //* = consume but skip

// read until EOL
//  - EOL not included in buffer
//  - EOL is not consumed
//  - nothing is written into buffer if EOF is found
scanf(" %[^\n]",buffer); 

//reading until EOL or EOF
//  - EOL not included in buffer
//  - EOL is consumed
//  - works with EOF
char* output = gets(buffer);
if(feof(stind)) {} // EOF file found
if(output == buffer) {} // succesful read
if(output == NULL) {} // EOF found without previous chars found
//example
while(gets(buffer) != NULL) {
    puts(buffer);
    if(feof(stdin)) {
        break;
    }
}
// read single char
getchar();
while(true) {c = getchar(); if (c == EOF || c== '\n') break;}

printf("%d",a); // int
printf("%u",a); // unsigned int
printf("%lld",a); // long long int
printf("%llu",a); // unsigned long long int
printf("%c",c); // char
printf("%s",buffer); // string until \0
printf("%f",f); // float
printf("%lf",d); // double
printf("%0*.*f",x,y,f); // padding = 0, width = x, decimals = y
printf("(%.5s)\n", buffer); // print  at most the first five characters (safe to use on short strings)

// print at most first n characters (safe)
printf("(%.*s)\n", n, buffer);  // make sure that n is integer (with long long I had problems)
//string + \n
puts(buffer);

/* ===================== */
/* Reading from c string */
/* ===================== */

// same as scanf but reading from s
int sscanf ( const char * s, const char * format, ...);

/* ==================== */
/* Printing to c string */
/* ==================== */
// Same as printf but writing into str, the number of characters is returned
// or negative if there is failure
int sprintf ( char * str, const char * format, ... );
//example:
int n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
printf ("[%s] is a string %d chars long\n",buffer,n);

/* ======================= */
/* Peek last char of stdin */
/* ======================= */
bool peekAndCheck(char c) {
    char c2 = getchar();
    ungetc(c2, stdin); // return char to stdin
    return c == c2;
}