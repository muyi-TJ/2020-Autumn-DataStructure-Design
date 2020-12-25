#include<iostream>
#include<time.h>
using namespace std;


struct Data
{
	long long move = 0;//赋值、交换次数
	long long cmp = 0;//比较次数
	long long time = 0;//用时
}bubble, quick, selection, heap, insertion, shell, merge, radix;

void generate(int arr[], int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
}

void BubbleSort(int nums[], const int size)
{
	bool changed = false;
	for (int i = 0; i < size - 1; i++)
	{
		changed = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			bubble.cmp++;
			if (nums[j] > nums[j + 1])
			{
				bubble.move++;
				swap(nums[j], nums[j + 1]);
				changed = true;
			}
		}
		if (!changed)
		{
			break;
		}
	}
}
//使用优化后的冒泡排序，否则运行时间过长
//时间复杂度O(n^2) 空间复杂度O(1)

void QuickSort(int nums[], const int low, const int high)
{
	if (low >= high)
		return;
	int i = low;
	int j = high + 1;
	int key = nums[low];
	while (i < j)
	{
		while (nums[--j] > key)
		{
			quick.cmp++;
			if (i == j)
			{
				break;
			}
		}//找到从右向左第一个小于key的数
		if (i == j)
		{
			break;//j所指的数为key，右侧已全部大于key
		}
		quick.move++;
		swap(nums[i], nums[j]);//否则交换，使nums[j]右侧全部大于key
		while (nums[++i] < key)
		{
			quick.cmp++;
			if (i == j)
			{
				break;
			}
		}
		if (i == j)
		{
			break;
		}
		quick.move++;
		swap(nums[i], nums[j]);//进行相反操作
	}//此时key左侧全部小于key，右侧全部大于key
	QuickSort(nums, low, j - 1);//缩小区间继续排序，直到升序排列
	QuickSort(nums, j + 1, high);
}
//递归实现快排函数
//时间复杂度 最优O(nlogn) 最差O(n^2) 平均O(nlogn)
//空间复杂度 最优O(logn) 最差O(n) 平均O(logn)


void SelectionSort(int nums[], const int size)
{
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		k = i;
		for (int j = i + 1; j < size; j++)
		{
			selection.cmp++;
			if (nums[k] > nums[j])
			{
				k = j;
			}
		}
		if (k != i)
		{
			selection.move++;
			swap(nums[k], nums[i]);
		}
	}
}
//时间复杂度 O(n^2) 空间复杂度 O(1)

void ShiftDown(int nums[], int index, int max)
{
	int child = 2 * index + 1, first = nums[index];
	while (child <= max)
	{
		heap.cmp += 3;
		if (child < max&&nums[child] < nums[child + 1])
		{
			child++;
		}//child指向较大孩子
		if (first > nums[child])
		{
			break;
		}
		else
		{
			heap.move++;
			nums[index] = nums[child];
			index = child;
			child = 2 * child + 1;
		}
	}
	heap.move++;
	nums[index] = first;
}

void HeapSort(int nums[], const int size)
{
	int i = (size - 2) / 2;
	while (i >= 0)
	{
		ShiftDown(nums, i--, size - 1);
	}
	for (i = size - 1; i > 0; i--)
	{
		heap.move++;
		swap(nums[i], nums[0]);//最大元素排到最后
		ShiftDown(nums, 0, i - 1);
	}
}
//时间复杂度 O(nlogn) 空间复杂度 O(1)

void InsertionSort(int nums[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		int key = nums[i];
		int j = i - 1;
		insertion.cmp++;//作为进入条件的比较是否忽略对结论无影响
		while (j >= 0 && nums[j] > key)
		{
			insertion.cmp++;
			insertion.move++;
			nums[j + 1] = nums[j];
			j--;
		}
		insertion.move++;
		nums[j + 1] = key;
	}
}
//时间复杂度 最优O(n) 最差O(n^2) 平均O(n^2)  
//空间复杂度 O(1)

void ShellSort(int nums[], const int size)
{
	int Sedgewick[30] =
	{ 0, 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289,
	  64769, 146305, 260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929,
	  37730305, 67084289, 150958081, 268386305, 603906049, 1073643521 };

	int index = 0, i = 0, j = 0;
	int key;
	int gap;
	while (Sedgewick[index] < size / 2)
	{
		index++;
	}
	gap = Sedgewick[index];
	while (gap > 0)
	{
		for (i = gap; i < size; i++)
		{
			j = i;
			key = nums[j];
			shell.cmp++;
			while (j >= gap && nums[j - gap] > key)
			{
				shell.cmp++;
				shell.move++;
				nums[j] = nums[j - gap];
				j -= gap;
			}
			nums[j] = key;
		}
		gap = Sedgewick[--index];
	}

}
//采用Sedgewick增量序列，取法为D=9∗4i−9∗2i+1或4i−3∗2i+1
//时间复杂度 最差O(n^4/3) 平均O(n^7/6)
//空间复杂度 O(1)

void Merge(int nums[], const int left, const int middle, const int right)
{
	int i = left, j = middle + 1;
	const int size = right - left + 1;
	int* temp = new int[size];
	int k = 0;
	while (i <= middle && j <= right)
	{
		merge.cmp++;
		merge.move++;
		if (nums[i] <= nums[j])
		{
			temp[k++] = nums[i++];
		}
		else
		{
			temp[k++] = nums[j++];
		}
	}
	while (i <= middle)
	{
		merge.move++;
		temp[k++] = nums[i++];
	}
	while (j <= right)
	{
		merge.move++;
		temp[k++] = nums[j++];
	}
	k = 0;
	for (int p = left; p <= right; p++)
	{
		nums[p] = temp[k++];
	}
	delete[]temp;
}

void MergeSort(int nums[], const int left, const int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		MergeSort(nums, left, middle);
		MergeSort(nums, middle + 1, right);
		Merge(nums, left, middle, right);
	}
}
//时间复杂度 最差O(nlogn) 平均O(nlogn)
//空间复杂度 O(n)

void RadixSort(int nums[], const int size)
{
	int max = nums[0];
	int i, j, k;
	for (i = 0; i < size; i++)
	{
		if (max < nums[i])
		{
			max = nums[i];
		}
	}
	int bits = 0, presentBit = 0;
	int index = 0;
	while (max > 0)
	{
		max >>= 1;
		bits++;
	}//得到二进制位数
	int **pots = new int*[2];
	pots[0] = new int[size];
	pots[1] = new int[size];
	int potsize[] = { 0,0 };
	for (; presentBit < bits; presentBit++)
	{
		for (i = 0; i < size; i++)
		{
			//index = (nums[i] >> presentBit) % 2;
			index = (nums[i] >> presentBit) & 1;//优于余除2
			pots[index][potsize[index]++] = nums[i];
			radix.move++;
		}
		k = 0;
		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < potsize[i]; j++)
			{
				nums[k++] = pots[i][j];
				radix.move++;
			}
			potsize[i] = 0;
		}
	}
	delete[] pots[0];
	delete[] pots[1];
	delete[] pots;
}
//使用优化过的基数为2的基数排序
//时间复杂度 O(kn)
//空间复杂度 O(n)


int main()
{
	cout << "请输入要产生的随机数个数" << endl;
	int size = -1;
	cin >> size;
	if (size <= 0)
	{
		cout << "请输入大于0的整数" << endl;
		system("pause");
		return 0;
	}
	int* randomArray = new int[size];
	int* arrayToBeSorted = new int[size];
	generate(randomArray, size);
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	long long start = clock();
	BubbleSort(arrayToBeSorted, size);
	bubble.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	QuickSort(arrayToBeSorted, 0, size - 1);
	quick.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	SelectionSort(arrayToBeSorted, size);
	selection.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	HeapSort(arrayToBeSorted, size);
	heap.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	InsertionSort(arrayToBeSorted, size);
	insertion.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	ShellSort(arrayToBeSorted, size);
	shell.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	MergeSort(arrayToBeSorted, 0, size - 1);
	merge.time = clock() - start;
	memcpy(arrayToBeSorted, randomArray, size * sizeof(int));
	start = clock();
	RadixSort(arrayToBeSorted, size);
	radix.time = clock() - start;

	cout << "对于冒泡排序，比较次数为" << bubble.cmp << "  交换次数为" << bubble.move
		<< "  总体时间" << bubble.time << "毫秒" << endl
		<< "对于快速排序，比较次数为" << quick.cmp << "  交换次数为" << quick.move
		<< "  总体时间" << quick.time << "毫秒" << endl
		<< "对于选择排序，比较次数为" << selection.cmp << "  交换次数为" << selection.move
		<< "  总体时间" << selection.time << "毫秒" << endl
		<< "对于堆排序，比较次数为" << heap.cmp << "  赋值次数为" << heap.move
		<< "  总体时间" << heap.time << "毫秒" << endl
		<< "对于插入排序，比较次数为" << insertion.cmp << "  赋值次数为" << insertion.move
		<< "  总体时间" << insertion.time << "毫秒" << endl
		<< "对于希尔排序，比较次数为" << shell.cmp << "  赋值次数为" << shell.move
		<< "  总体时间" << shell.time << "毫秒" << endl
		<< "对于归并排序，比较次数为" << merge.cmp << "  赋值次数为" << merge.move
		<< "  总体时间" << merge.time << "毫秒" << endl
		<< "对于基数排序，比较次数为" << radix.cmp << "  赋值次数为" << radix.move
		<< "  总体时间" << radix.time << "毫秒" << endl;

	delete[] randomArray;
	delete[] arrayToBeSorted;
	system("pause");
	return 0;
}