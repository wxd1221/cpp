#include <iostream>
#include <string.h>
using namespace std;
#define swap(x, y)    \
    {                 \
        int temp = x; \
        x = y;        \
        y = temp;     \
    }

struct test
{
	int a;
	char b;
	bool operator==(const test &);
};

bool test::operator==(const test &s)
{
	return (a == s.a) && (b == s.b);
}

void swap2(int &a, int &b)
{
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void print(int s[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", s[i]);
	}
}

void bubbleSort(int s[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (s[j + 1] < s[j])
			{
				// swap(s[j + 1], s[j]);
				s[j + 1] = s[j + 1] + s[j];
				s[j] = s[j + 1] - s[j];
				s[j + 1] = s[j + 1] - s[j];
			}
		}
	}
}

void quickSort(int s[], int left, int right)
{
	int i, j;
	i = left;
	int key = s[left];
	while (left < right)
	{
		while (s[right] > key && left < right)
			right--;
		while (s[left] < key && left < right)
			left--;
		if (left < right)
		{
			s[left] = s[left] + s[right];
			s[left] = s[left] - s[right];
			s[right] = s[left] - s[right];
		}
	}
	// 交换key和s[left]的值
	s[i] = s[left];
	s[left] = key;

	quickSort(s, i, left - 1);
    quickSort(s, left + 1, right);
}

void chooseSort(int s[], int len)
{
	int minIndex;
	for (size_t i = 0; i < len; i++)
	{
		minIndex = i;
		for (size_t j = 1; j < len; j++)
		{
			if (s[j] < s[i])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(s[minIndex], s[i]);
		}
	}
}

void insertSort(int s[], int len)
{
	int tmp, i, j;
	for (i = 1; i < len; i++)
	{
		tmp = s[i];
		// 取出下一个元素，在已经排序的元素序列中从后向前扫描, 知道找到一个比s[i]小的值
		for (j = i - 1; j >= 0 && s[j] > tmp; j--)
		{
			// 如果被扫描的元素（已排序）大于新元素，将该元素后移一位
			// 直到找到已排序的元素小于或者等于新元素的位置
			s[j + 1] = s[j];
		}
		/*
        // 这样写看的清晰点
        for (j = i - 1; j >= 0; --j)
        {
			if (s[j] >= tmp)
			{
                s[j + 1] = s[j];
            }
			else
			{
				break;
			}
		}
        */

		// 循环退出的时候,j指向<tmp的值的下标, 因为把元素复制后移, 所以s[j+1]就是腾给tmp的
		s[j + 1] = tmp;
	}
}

void sink(int *s, int len, int i)
{
	while (2 * i <= len)
	{
		int lchild = 2 * i;
		if (lchild < len && s[lchild] < s[lchild +1])
		{
			lchild++;
		}
		if (s[i] > s[lchild])
		{
			break;
		}
		swap(s[i], s[lchild]);
		i = lchild;
	}
}

void heapSort(int s[], int len)
{
	// 建堆
	for (int i = len / 2; i >= 1; i--)
	{
		sink(s, len, i);
	}

	// 调整
	for (; len > 1;)
	{
		swap(s[1], s[len]);
		len--;
		sink(s, len, 1);
	}
}

int heapsortTest()
{
	int s[] = {9, 2, 4, 6, 8, 23, 3, 11};
	// int s[] = {4, 6, 8, 5, 9};
	int len = sizeof(s) / sizeof(s[0]) - 1;
	// bubbleSort(s, len);
	// chooseSort(s, len);
	// insertSort(s, len);
	heapSort(s, len);
	for (int i = 1; i <= len; i++)
		cout << s[i] << " ";
    cout << endl;
	return 0;
}



class Base
{
  public:
	virtual void f1() { cout << "Base:f1()"; };
	int m_base_arg=10;
	void f2() { cout << "Base:f2()"; };

  protected:
  private:
};

class Driver :public Base
{
  public:
	void f1() { cout << "Driver:f1()"; };
	void f2() { cout << "Driver:f2()"; };
	virtual void f3() { cout << "Driver:f3()"; };
	int m_driver_arg=10;
  protected:
  private:
};

int main(int argc, char *argv[])
{
	// cout << system("/home/m_kepler/debug/test.out") << endl;
	Base *pbase = new Driver;
	pbase->f1();
	cout << pbase->m_base_arg << endl;
	pbase->f2();
	pbase->f3();
	return 0;
}





