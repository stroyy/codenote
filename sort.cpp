#include <iostream>
#include <vector>
using namespace std;
//快速排序
void quickSort(vector<int>& n,int l ,int r) {
	if (l >= r) {
		return;
	}
	int i = l-1;
	int j = r+1;
	int x = n[l + (rand() % (r - l + 1))];
	while (i < j) {
		do i++;while (n[i] < x);
		do j--;while (n[j] > x);
		if (i < j) {
			swap(n[i], n[j]);
		}
		else {
			quickSort(n, l, j);
			quickSort(n, j + 1, r);
		}
	}
	
}
//堆排序
void Heapify(vector<int>&h, int n,int i) {
	int p = i;
	int l = 2 *i +1;
	int r = 2 * i + 2;
	if (l<n && h[l] > h[p]) {
		p = l;
	}
	if (r<n && h[r] > h[p]) {
		p = r;
	}
	if (p != i) {
		swap(h[p], h[i]);
		Heapify(h, n, p);
	}
} void Print(vector<int> a) {
	for (int i = 0;i < a.size();i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
void heapSort(vector<int> &a) {
	for (int i = a.size() / 2 - 1;i >= 0;--i) {
		Heapify(a, a.size(), i);
	}
	cout << "大根堆构建完成：";
	Print(a);
	for (int i = a.size() - 1;i >= 0;--i) {
		swap(a[0], a[i]);
		Heapify(a, i, 0);
	}
	
}
//计数排序
void countSort(vector<int>& arr, int n) {
	vector<int> cnt(101, 0);
	for (int i = 0;i < n - 1;i++) {
		cnt[arr[i]]++;
	}
	
	for (int i = 0,k = 0;i <= 100;i++) {
		while (cnt[i]) {
			arr[k++] = i;
		}
	}
}
//基数排序
int get(int x, int i) {
	while (i--)
		x /= 10;
	return x % 10;
}

void radixSort(vector<int>& q, int n) {
	vector<vector<int>> cnt(10);
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 10;j++) {
			cnt[j].clear();
		}
		for (int j = 0;j < n;j++) {
			cnt[get(q[j], i)].push_back(q[j]);
		}
		for (int j = 0, k = 0;j < 10;j++) {
			for (int x : cnt[j]) {
				q[k++] = x;
			}
		}
	}
}

void bubbleSort(vector<int>& arr) {
	int j = arr.size();
	bool flag;
	do 
	{
		flag = false;
		for (int i = 1;i < j;++i) {
			if (arr[i - 1] > arr[i]) {
				swap(arr[i - 1], arr[i]);
				flag = true;
			}
		}
		j--;
	} while (flag);
}
//选择排序
void selectSort(vector<int>& arr) {
	for (int i = 0;i < arr.size()-1;i++) {
		int min = i;
		int j;
		for (j = i + 1;j < arr.size();j++) {
			if (arr[j] < arr[i]) {
				min = j;
			}
		}
		swap(arr[i], arr[min]);
		
	}
}
//插入排序
void insertSort(vector<int>& arr) {
	int length = arr.size();
	for (int i = 1;i < length ;i++) {
		int t = arr[i];
		int j;
		for(j = i - 1;j >= 0;j--) {
			if (arr[j] > t ) {
				arr[j + 1] = arr[j];
			}
			else {
				break;
			}
		}
		arr[j + 1] = t;
		
	}
}
//归并排序

void merge(vector<int>& arr,int l, int mid, int r ) {
	vector<int> brr(r - l + 1);
	brr.clear();
	int i = l;
	int j = mid + 1;
	while (i <= mid &&j<=r) {
		if (arr[i] <= arr[j]) {
			brr.push_back(arr[i++]);
		}
		else {
			brr.push_back(arr[j++]);
		}
	}
	while (i <=mid ) {
		brr.push_back(arr[i++]);
	}
	while (j <=r ) {
		brr.push_back(arr[j++]);
	}
	int k = l;
	for (int m :brr) {
		arr[k++] = m;
	}
}

void mergeSort(vector<int>& arr,int l,int r) {
	
	if (l >= r) {
		return;
	}
	int mid =  l+(r - l) / 2;
	mergeSort(arr,l, mid);
	mergeSort(arr,mid + 1, r);
	merge(arr,l, mid, r);
}


int main() {
	int n;
	cin >> n;
	vector<int> a;
	while (n) {
		int t;
		cin >> t;
		a.push_back(t);
		n--;
	}
	Print(a);
	//quickSort(a, 0, a.size()-1);
	//heapSort(a);
	//countSort(a, a.size());
	//radixSort(a, a.size());
	//bubbleSort(a);
	//selectSort(a);
	//insertSort(a);
	mergeSort(a,0,a.size()-1);
	Print(a);

	

	return 0;
}