#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PLEN 128

//储存每个节点数据
typedef struct _node{
    int count;      //编号为 clsid(cluster ID) 社区所包含的节点个数
    int clsid;      //由代表节点ID作为社区编号
    int next;       //属于同一个临时社区的下一个节点
    int prev;       //属于同一个临时社区的上一个节点
    int first;      //属于同一个社区的，除去代表节点外的第一个节点
    int eindex;     //edge_index 指向邻居链表表项的指针，该表所有元系欸但都是本节点
    double kin;     //稳定社区内部边权重之和。k_in就是算模块度公式中的节点
    double kout;    //稳定社区外部指向社区边权重之和
    double clskin;  //cluster_kin，临时社区内部边权重之和
    double clstot;  //cluster_out，稳定社区所有内外指向本社区的边权重之和
} Node;


//储存每条边数据
typedef struct _edge{
    int source;
    int target;     //target节点 指向 source节点
    int next;
    double weight;  //边权重
}Edge;


//可以看作为“路标”/总表，指向各个表
typedef struct _louvain{
    int clen;       //cindex表的长度
    int elen;       //Edge表的长度
    int nlen;       //Node表的长度
    int olen;       //这TMD是啥？整个程序就出现了两次，一次定义一次初始化，用都没用过
    int* cindex;    //指向第一个cindex表的表项
    double sumw;    //
    Node* nodes;    //指向第一个Node表的表项
    Edge* edges;    //指向第一个Edge表的表项
}Louvain;


//初始化总表，为每个表指针分配空间，初始化值
static void malloc_louvain(Louvain *lv){
    lv->cindex = (int* )calloc(lv->clen, sizeof(int));
    lv->nodes = (Node* )calloc(lv->nlen, sizeof(Node));
    lv->edges = (Edge* )calloc(lv->elen, sizeof(Edge));

    for(int i = 0; i < lv->clen; i++){
        lv->nodes[i].eindex = -1;
    }
    memset(lv->cindex, -1, lv->clen * sizeof(int));
}


// lv:  总表的指针
// I:   index
// weight: 
#define INIT_NODE(lv, I, weight) do{    \
    if(lv->cindex[I] == -1){            \
        lv->cindex[I] = I;              \
        lv->nodes[I].count = 1;         \
        lv->nodes[I].kin = 0;           \
        lv->nodes[I].clskin = 0;        \
        lv->nodes[I].clsid = I;         \
        lv->nodes[I].first = -1;        \
        lv->nodes[I].prev = -1;         \
        lv->nodes[I].next = -1;         \
    }                                   \
    lv->nodes[I].kout += weight;        \
    lv->nodes[I].clstot += weight;      \
}while(0)


// lv:  总表的指针
// l:   left
// r:   right
// ei:  edge_index
// weight: 
#define LINKEDGE(lv, l, r, ei, weight) do{  \
    lv->edges[ei].left = l;                 \
    lv->edges[ei].right = r;                \
    lv->edges[ei].weight = weight;          \
    lv->edges[ei].next = lv->nodes[l].eindex;\
    lv->nodes[l].eindex = ei;               \
    ei += 1;                                \
}while(0)


Louvain* create_louvain(const char *input){
    FILE* fp = NULL;
    if(NULL == (fp = fopen(input, "r"))){
        cout<<stderr<<" can not open input file"<<input<<endl;
        return NULL;
    }


}

//通过读取
Louvain * create_louvain_cform(const char * input){
    //读input文件
    //文件内容
    FILE * fp = NULL;
    if (NULL == (fp = fopen(input, "r"))){
        fprintf(stderr, "can not open input file \"%s\"\n", input);
        return NULL;
    }

    //初始化哈希表等一系列必要变量
    Hash * hs = hash_create(1 << 23, STRING);
    Louvain * lv = (Louvain*)calloc(1, sizeof(Louvain));
    char buffer[PLEN] = {0};
    char *string = buffer;
    int l = 0, ei = 0, r = 0;
    double weight = 1.0;

    //按行读取input文件，处理后放入哈希表中
    while (NULL != fgets(buffer, PLEN, fp)){
        string = trim(buffer, 3);
        hash_add(hs, strsep(&string, "\t"));
        hash_add(hs, strsep(&string, "\t"));
        l += 1;
    }
    
    //louvain元信息初始化
    //cindex表长度与hash表相同
    //elen长度为input文件 行数 * 2
    //node表长度与cindex相同
    //olen这个先不管，后面都不用了
    lv->clen = hash_cnt(hs);
    lv->elen = l * 2;
    lv->nlen = lv->clen;
    lv->olen = lv->elen;
    malloc_louvain(lv);

    //input文件读取位置指针重新设置到开头
    rewind(fp);
    //一行行读input
    while (NULL != fgets(buffer, PLEN, fp)){
        string = trim(buffer, 3);
        
        //从哈希表中找到source 与 target，以及边权重
        l = hash_find(hs, strsep(&string, "\t"));
        r = hash_find(hs, strsep(&string, "\t"));
        weight = atof(strsep(&string, "\t"));

        //把边权重算进总权重中
        lv->sumw += weight;   // left ---- > right ===== right ------> left
        INIT_NODE(lv, l, weight);   //
        INIT_NODE(lv, r, weight);
        LINKEDGE(lv, l, r, ei, weight);
        LINKEDGE(lv, r, l, ei, weight);
    }
    fclose(fp);
    return lv;
}
