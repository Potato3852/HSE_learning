#include <stdio.h>

void insert_up(long long int arr[], long long int start, long long int end) {
    for (long long int i = start; i <= end; i++) {
        long long int key = arr[i];
        long long int j = i - 1;
        
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

void insert_down(long long int arr[], long long int start,long long int end) {
    for (long long int i = end; i >= start; i--) {
        long long int key = arr[i];
        long long int j = i + 1;
        
        while (j <= end && arr[j] > key) {
            arr[j - 1] = arr[j];
            j++;
        }
        
        arr[j - 1] = key;
    }
}
void print_array(long long int arr[], long long int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");
}

int main() {
    long long int n;
    scanf("%lld", &n);
    
    long long int arr[n];
    for (long long int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    long long int mid = n / 2;
    long long int step = 0;
    long long int left = 0, right = n - 1;
    long long int l = -1;
    printf("Step 0:\n");
    print_array(arr, n);
    while (left < mid && right >= mid) {

        l++;
        if (left < mid) {
            insert_up(arr, 0, left);
            left++;
        }
        

        if (right >= mid) {
            insert_down(arr, right, n-1);
            right--;
        }
        if(l > 0){
            printf("Step %lld:\n", l);
            print_array(arr, n);
            step++;
        }
    }

    return 0;
}