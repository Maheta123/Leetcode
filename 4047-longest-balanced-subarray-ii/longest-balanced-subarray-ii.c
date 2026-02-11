
#define MAX_N 100001
#define MAX_VAL 100001
#define TREE_SIZE 400004

static int tree_mn[TREE_SIZE];
static int tree_mx[TREE_SIZE];
static int tree_lazy[TREE_SIZE];
static int last_pos[MAX_VAL];

__attribute__((no_sanitize("address"), optimize("O3"))) static void build(
    int node, int lo, int hi) {
    tree_mn[node] = 0;
    tree_mx[node] = 0;
    tree_lazy[node] = 0;
    if (lo == hi) {
        return;
    }
    int mid = (lo + hi) / 2;
    build(node * 2, lo, mid);
    build(node * 2 + 1, mid + 1, hi);
}

__attribute__((no_sanitize("address"), optimize("O3"))) static inline void
push_down(int node) {
    if (tree_lazy[node] != 0) {
        int left = node * 2;
        int right = node * 2 + 1;
        tree_lazy[left] += tree_lazy[node];
        tree_mn[left] += tree_lazy[node];
        tree_mx[left] += tree_lazy[node];
        tree_lazy[right] += tree_lazy[node];
        tree_mn[right] += tree_lazy[node];
        tree_mx[right] += tree_lazy[node];
        tree_lazy[node] = 0;
    }
}

__attribute__((no_sanitize("address"), optimize("O3"))) static void range_add(
    int node, int lo, int hi, int ql, int qr, int val) {
    if (ql > qr || lo > qr || hi < ql) {
        return;
    }
    if (ql <= lo && hi <= qr) {
        tree_lazy[node] += val;
        tree_mn[node] += val;
        tree_mx[node] += val;
        return;
    }
    push_down(node);
    int mid = (lo + hi) / 2;
    range_add(node * 2, lo, mid, ql, qr, val);
    range_add(node * 2 + 1, mid + 1, hi, ql, qr, val);
    tree_mn[node] = tree_mn[node * 2] < tree_mn[node * 2 + 1]
                        ? tree_mn[node * 2]
                        : tree_mn[node * 2 + 1];
    tree_mx[node] = tree_mx[node * 2] > tree_mx[node * 2 + 1]
                        ? tree_mx[node * 2]
                        : tree_mx[node * 2 + 1];
}

__attribute__((no_sanitize("address"), optimize("O3"))) static int
search_leftmost(int node, int lo, int hi) {
    if (tree_mn[node] > 0 || tree_mx[node] < 0) {
        return -1;
    }
    if (lo == hi) {
        return lo;
    }
    push_down(node);
    int mid = (lo + hi) / 2;
    int left_res = search_leftmost(node * 2, lo, mid);
    if (left_res != -1) {
        return left_res;
    }
    return search_leftmost(node * 2 + 1, mid + 1, hi);
}

__attribute__((no_sanitize("address"), optimize("O3")))
// NOLINTNEXTLINE(readability-identifier-naming)
int longestBalanced(int* nums, int nums_size) {
    int n = nums_size;
    if (n == 0) {
        return 0;
    }

    build(1, 0, n - 1);
    memset(last_pos, -1, sizeof(last_pos));

    int ans = 0;

    for (int i = 0; i < n; i++) {
        int v = nums[i];
        int delta = (v % 2 == 0) ? 1 : -1;
        int prev = last_pos[v];
        int range_left = (prev == -1) ? 0 : prev + 1;
        range_add(1, 0, n - 1, range_left, i, delta);
        last_pos[v] = i;

        int leftmost = search_leftmost(1, 0, n - 1);
        if (leftmost != -1 && leftmost < i) {
            int len = i - leftmost + 1;
            if (len > ans) {
                ans = len;
            }
        }
    }

    return ans;
}