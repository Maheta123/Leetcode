
#define MOD 1000000007LL

// Modular multiplicative inverses: INV[x] = x^(-1) mod (10^9+7)
// Computed via Fermat's little theorem: x^(-1) = x^(p-2) mod p
// Verification: (x * INV[x]) mod (10^9+7) = 1 for all x in [1,100]
// clang-format off
static const long long INV[101] = {
    0,         1,         500000004, 333333336, 250000002, 400000003, 166666668,
    142857144, 125000001, 111111112, 700000005, 818181824, 83333334,  153846155,
    71428572,  466666670, 562500004, 352941179, 55555556,  157894738, 850000006,
    47619048,  409090912, 739130440, 41666667,  280000002, 576923081, 370370373,
    35714286,  758620695, 233333335, 129032259, 281250002, 939393946, 676470593,
    628571433, 27777778,  621621626, 78947369,  717948723, 425000003, 658536590,
    23809524,  395348840, 204545456, 822222228, 369565220, 404255322, 520833337,
    448979595, 140000001, 784313731, 788461544, 56603774,  685185190, 763636369,
    17857143,  385964915, 879310351, 50847458,  616666671, 688524595, 564516133,
    15873016,  140625001, 30769231,  469696973, 686567169, 838235300, 579710149,
    814285720, 98591550,  13888889,  410958907, 310810813, 93333334,  539473688,
    831168837, 858974365, 202531647, 712500005, 123456791, 329268295, 84337350,
    11904762,  670588240, 197674420, 252873565, 102272728, 415730340, 411111114,
    164835166, 184782610, 43010753,  202127661, 231578949, 760416672, 268041239,
    724489801, 646464651, 570000004,
};
// clang-format on

#define MAX_SIZE 100001

static int seq[MAX_SIZE];
static int len;
static long long cumul_add;
static long long cumul_mul;
static long long cumul_inv;

typedef struct {
    char unused;
} Fancy;

static Fancy state;

// NOLINTNEXTLINE(readability-identifier-naming)
Fancy* fancyCreate(void) {
    len = 0;
    cumul_add = 0;
    cumul_mul = 1;
    cumul_inv = 1;
    return &state;
}

// NOLINTNEXTLINE(readability-identifier-naming)
void fancyAppend(Fancy* obj, int val) {
    (void)obj;
    long long shifted = MOD + val - cumul_add;
    seq[len++] = (int)((shifted * cumul_inv) % MOD);
}

// NOLINTNEXTLINE(readability-identifier-naming)
void fancyAddAll(Fancy* obj, int val) {
    (void)obj;
    cumul_add = (cumul_add + val) % MOD;
}

// NOLINTNEXTLINE(readability-identifier-naming)
void fancyMultAll(Fancy* obj, int val) {
    (void)obj;
    cumul_mul = cumul_mul * val % MOD;
    cumul_add = cumul_add * val % MOD;
    cumul_inv = cumul_inv * INV[val] % MOD;
}

// NOLINTNEXTLINE(readability-identifier-naming)
int fancyGetIndex(Fancy* obj, int idx) {
    (void)obj;
    if (idx >= len) {
        return -1;
    }
    return (int)((seq[idx] * cumul_mul + cumul_add) % MOD);
}

// NOLINTNEXTLINE(readability-identifier-naming)
void fancyFree(Fancy* obj) {
    (void)obj;
}