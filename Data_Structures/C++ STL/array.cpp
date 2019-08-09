//================
// declare arrays
//================
int arr[10];
int arr[10][10];
int arr[5] = {1, 2, 3, 4, 5};
int arr[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

//============================
// fill array using std::fill
//============================
// http://www.cplusplus.com/reference/algorithm/fill/

// 1) arrays 1D
int arr[100];
fill(arr, arr+4, -5);
fill(arr, arr+N, val);
fill(arr + offset, arr + N, val);
double arr[100];
fill(arr, arr+7, 0.999);

// 2) arrays 2D or more
int arr[100][100];
fill(&arr[0][0], &arr[0][0] + sizeof(arr), -1231);

//=========================
// fill array using memset
//=========================
int arr[100][100];
memset(arr, -1, sizeof(arr));
memset(arr, 0, sizeof(arr));
// ** only works with 0 and -1 for arryas of ints/longs
//   because memset works on bytes (same value is written on each char)
//   sizeof(arr) returns the number of bytes in arr

// in the case of char arrays, we can set any value, since
// sizeof(char) = 1 (each char uses a single byte)
char char_arr[100][100];
memset(char_arr, 'k', sizeof(char_arr));

// filling with -1/0 the first N ints in arr
int arr[MAXN];
memset(arr, -1, sizeof(int) * N);
memset(arr, 0, sizeof(int) * N);

// interesting links:
// https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new/
// https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function