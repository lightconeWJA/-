#include <vector>
#include <iostream>

using namespace std;

/*
    x：第一个用于比较变量
    y：第二个用于比较变量
    a： 表示是否升序ascending
        a == true：如果 x < y 返回true
        a == false ：如果 x < y 返回false
    灵活使用异或，嗯，妙啊~~~
*/
#define COMPARE(x, y, a) ((x > y) ^ a)

void printHeap(vector<int> &heap){
    for(int i = 0; i < heap.size(); i++)
        cout<<heap[i]<<' ';
    cout<<endl<<endl;
}

void swap(int &p1, int &p2){
    int tmp = p1;
    p1 = p2;
    p2 = tmp;
}

//heapify：堆化
//构建堆的关键步骤：调整一个特定节点位置使其符合堆要求
//p：当前需要比较并(可能)调整位置的节点指针
//len：当前需要“堆化”的堆长度
void heapify(vector<int> &heap, int p, int len, bool ascending){
    int left = p * 2 + 1;
    int right = p * 2 + 2;
    int originalp = p;

    if((left < len) && COMPARE(heap[originalp], heap[left], ascending))
        originalp = left;
    if((right < len) && COMPARE(heap[originalp], heap[right], ascending))
        originalp = right;
    
    if(originalp != p){
        swap(heap[originalp], heap[p]);
        heapify(heap, originalp, len, ascending);
    }
}

void buildHeap(vector<int> &heap, int len, bool ascending){
    for(int i = (len/2) - 1; i >= 0; i--){
        heapify(heap, i, len, ascending);
    }
}

/*
    堆排序思路：
    如果要从小到大排序
    则先构建大顶堆，使得根节点一定为最大值，之后将根节点放在末尾
    重复上面步骤逐渐找出第二大、第三大……，并放在对应位置
    每次迭代处理的堆大小都会-1
    时间复杂度log(n)
    bool ascending：true代表升序排列，需要构建大顶堆
*/
void heapSort(vector<int> &heap, bool ascending){    
    int len = heap.size();
    if (len == 0) return;

    buildHeap(heap, len, ascending);

    for(int i = len - 1; i > 0; i--){
        swap(heap[0], heap[i]);
        len--;
        heapify(heap, 0, len, ascending);
    }
}

int main(void){
    vector<int> test = {4, 5, 8, 2, 3, 9, 7, 1};
    heapSort(test, true);
    for(int i = 0; i <= test.size(); i++)
        cout<<test[i]<<' ';
        cout<<endl;
    return 0;
}
