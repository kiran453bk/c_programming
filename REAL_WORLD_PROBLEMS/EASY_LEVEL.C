#include <stdio.h>
#include <stdlib.h>

// Comparator for sorting taste values in descending order
int cmp(const void *a, const void *b) {
    const long long *x = (const long long*)a;
    const long long *y = (const long long*)b;

    if (*x < *y) return 1;   // descending order
    if (*x > *y) return -1;
    return 0;
}

int main() {
    int n;
    long long m;
    scanf("%d", &n);
    scanf("%lld", &m);

    long long v[n], d[n];
    for (int i = 0; i < n; i++) scanf("%lld", &v[i]);
    for (int i = 0; i < n; i++) scanf("%lld", &d[i]);

    // Collect all possible taste points
    // For each food type, taste decreases linearly until it becomes <= 0
    long long *tastePoints = malloc(sizeof(long long) * m);
    long long count = 0;

    for (int i = 0; i < n; i++) {
        long long t = 1;
        while (1) {
            long long taste = v[i] - d[i] * (t - 1);
            if (taste <= 0) break;
            if (count < m) {
                tastePoints[count++] = taste;
            } else {
                break;
            }
            t++;
        }
    }

    // Sort taste points in descending order
    qsort(tastePoints, count, sizeof(long long), cmp);

    // Take top m taste points
    long long result = 0;
    for (long long i = 0; i < m && i < count; i++) {
        result += tastePoints[i];
    }

    printf("%lld\n", result);

    free(tastePoints);
    return 0;
}